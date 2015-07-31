#include "paperconferenceauthor.h"
#include <QDebug>
#include <QStringList>
#include <vtkVector.h>
AcademicNode::AcademicNode(int nodeIndex, int nodeId, Type type, int myear,
    QColor viewColor, QString academicId, QString viewLable, double viewLayout[3])
{
    this->mNodeIndex = nodeIndex;
    this->mNodeId = nodeId;
    this->mType = type;
    this->mYear = myear;
    this->mViewColor = viewColor;
    this->mAcademicId = academicId;
    this->mViewLable = viewLable;
    this->mViewLayout = viewLayout;
}

AcademicNode::~AcademicNode()
{
}

QColor AcademicNode::GetViewColor(const QString &origin)
{
    
    QString sub = NodeBase::GetStem(origin);
    sub = sub.mid(1, sub.length() - 2);
    QStringList list = sub.split(',');
    int r = list[0].toInt();
    int g = list[1].toInt();
    int b = list[2].toInt();
    int a = list[3].toInt();

    return QColor(r, g, b, a);
}

void AcademicNode::GetViewLayout(double * viewLayout,const QString &origin)
{
    QString sub = NodeBase::GetStem(origin);
    sub = sub.mid(1, sub.length() - 2);
    QStringList list = sub.split(',');
    viewLayout[0] = list[0].toDouble();
    viewLayout[1] = list[1].toDouble();
    viewLayout[2] = list[2].toDouble();
}

PaperNode::PaperNode(int nodeIndex, int nodeId, Type type, int myear,
    QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]) :
    AcademicNode(nodeIndex, nodeId, type, myear, viewColor, academicId, viewLable, viewLayout)
{
    
    this->mType = Paper;
}

PaperNode::~PaperNode()
{
}

ConferenceNode::ConferenceNode(int nodeIndex, int nodeId, Type type, int myear,
    QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]) :
    AcademicNode(nodeIndex, nodeId, type, myear, viewColor, academicId, viewLable, viewLayout)
{
    this->mType = Conference;
}

ConferenceNode::~ConferenceNode()
{
}


AuthorNode::AuthorNode(int nodeIndex, int nodeId, Type type, int myear,
    QColor viewColor, QString academicId, QString viewLable, double viewLayout[3]) :
    AcademicNode(nodeIndex, nodeId, type, myear, viewColor, academicId, viewLable, viewLayout)
{
    this->mType = Author;
}

AuthorNode::~AuthorNode()
{
}


DirectedEdge::DirectedEdge()
{
}

DirectedEdge::~DirectedEdge()
{
}

PaperConferenceAuthorGraph::PaperConferenceAuthorGraph()
{
    LoadNodes("GraphData/PaperConferenceAuthorGraph/Nodes.txt");
    LoadEdges("GraphData/PaperConferenceAuthorGraph/Edges.txt");

    ConstructOriginGraph();
}

PaperConferenceAuthorGraph::~PaperConferenceAuthorGraph()
{
}

void PaperConferenceAuthorGraph::LoadNodes(QString nodeInFileName)
{
    QFile inFile(nodeInFileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    QString buffer;
    
    int index = -1;
    while (true)
    {
        ++index;
        int nodeId;
        buffer = inFile.readLine();
        nodeId = buffer.toInt();
        
        if (nodeId == 0)
        {
            this->mNodeSize = index;
            break;
        }
        //Type
        buffer = inFile.readLine();
        QString typeString = NodeBase::GetStem(buffer);

        int year;
        buffer = inFile.readLine();
        year = NodeBase::GetStem(buffer).toInt();
        
        QString author;
        int dateFrom;
        if (typeString.at(0) == 'p')
        {
            buffer = inFile.readLine();
            author = NodeBase::GetStem(buffer);

            buffer = inFile.readLine();
            dateFrom = NodeBase::GetStem(buffer).toInt();
        }

        QString idString;
        buffer = inFile.readLine();
        idString = NodeBase::GetStem(buffer).toInt();

        int pageFrom = 0;
        QString detail;
        QString detailShort;
        buffer = inFile.readLine();
        if (typeString.at(0) == 'p')
        {
            if ((buffer.at(2) == 'g'))
            {
                pageFrom = NodeBase::GetStem(buffer).toInt();
                buffer = inFile.readLine();
            }
        }
        detail = NodeBase::GetStem(buffer);
        buffer = inFile.readLine();
        detailShort = NodeBase::GetStem(buffer);

        buffer = inFile.readLine();
        QColor viewColor = AcademicNode::GetViewColor(buffer);

        buffer = inFile.readLine();
        QString viewLabel = NodeBase::GetStem(buffer);

        double viewLayout[3];
        buffer = inFile.readLine();
        AcademicNode::GetViewLayout(viewLayout, buffer);

        if (typeString.at(0) == 'p')
        {
            PaperNode paperNode(index, nodeId, AcademicNode::Paper, year, viewColor, idString, viewLabel, viewLayout);
            paperNode.mAuthors = author;
            paperNode.mDataFrom = dateFrom;
            paperNode.mPageFrom = pageFrom;
            paperNode.mPaperTitle = detail;
            paperNode.mPaperTitleShort = detailShort;

            
            this->mNodes.push_back(paperNode);
        }

        if (typeString.at(0) == 'c')
        {
            ConferenceNode conferenceNode(index, nodeId, AcademicNode::Paper, year, viewColor, idString, viewLabel, viewLayout);
            conferenceNode.mConferenceName = detail;
            conferenceNode.mConferenceNameShort = detailShort;
            this->mNodes.push_back(conferenceNode);
        }

        if (typeString.at(0) == 'a')
        {
            AuthorNode authorNode(index, nodeId, AcademicNode::Paper, year, viewColor, idString, viewLabel, viewLayout);
            authorNode.mAuthorName = detail;
            authorNode.mAuthorNameShort = detail;
            this->mNodes.push_back(authorNode);
        }
        inFile.readLine();

        this->mNodeIdHashIndex.insert(nodeId, index);
/*
        qDebug() << nodeId << " " << year << "  " << author << endl;
        qDebug() << dateFrom << "  " << idString << "  " << pageFrom << endl;
        qDebug() << detail << "  " << detailShort << endl;
        qDebug() << viewColor << "  " << viewLabel << "  " << viewLayout[0] << endl;*/
    } 
    inFile.close();
    
}
void PaperConferenceAuthorGraph::LoadEdges(QString edgeInFileName)
{
    QFile inFile(edgeInFileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);
    int index = -1;

    QString buffer;
    while (true)
    {
        QStringList list;
        buffer = inFile.readLine();
        list = buffer.split(QRegExp("\\s+"));
        if (list.size() == 1)
        {
            this->mEdgeSize = this->mEdges.size();
            break;
        }
        else
        {
            int source;
            int target;
            source = list[0].toInt();
            target = list[1].toInt();
            DirectedEdge directedEdge;
            directedEdge.mEdgeIndex = index;
            directedEdge.mNodeId[0] = source;
            directedEdge.mNodeId[1] = target;
            directedEdge.mNodeIndex[0] = this->mNodeIdHashIndex.value(source);
            directedEdge.mNodeIndex[1] = this->mNodeIdHashIndex.value(target);
            this->mEdges.push_back(directedEdge);
            //qDebug() << source << "  " << target << endl;
        }
    }
}
void PaperConferenceAuthorGraph::SetTestPos()
{
    for (int i = 0; i < this->mNodeSize; ++i)
    {
        double randX;
        double randY;
        randX = rand() % 500;
        randY = rand() % 500;

        this->mNodes[i].mAbsPosition.setX(randX);
        this->mNodes[i].mAbsPosition.setY(randY);
    } 
}

void PaperConferenceAuthorGraph::ConstructOriginGraph()
{
    this->mOriginGraph = vtkSmartPointer<vtkMutableDirectedGraph>::New();

    vector<vtkIdType> vtkNodes;
    for (vtkIdType i = 0; i < this->mNodeSize; ++i)
    {
        vtkIdType aNode = mOriginGraph->AddVertex();
        vtkNodes.push_back(aNode);
    }

    for (vtkIdType i = 0; i < this->mEdgeSize; ++i)
    {
        int *vtkIndex = this->mEdges[i].GetNodeIndex();
        mOriginGraph->AddEdge(vtkNodes[vtkIndex[0]],vtkNodes[vtkIndex[1]]);
    }

    mStoredLayout = vtkSmartPointer<vtkGraphLayout>::New();
    mStoredLayout->SetInputData(mOriginGraph);
}

void PaperConferenceAuthorGraph::UpDateStrategy(QString strategyName)
{
    if (strategyName == "Circular")
    {
        vtkSmartPointer<vtkCircularLayoutStrategy> circularStrategy
            = vtkSmartPointer<vtkCircularLayoutStrategy>::New();
        mStoredLayout->SetLayoutStrategy(circularStrategy);
    }
    if (strategyName == "ForceDirected")
    {
        vtkSmartPointer<vtkForceDirectedLayoutStrategy> forceStrategy
            = vtkSmartPointer<vtkForceDirectedLayoutStrategy>::New();
        mStoredLayout->SetLayoutStrategy(forceStrategy);
    }
    if (strategyName == "Fast2D")
    {
        vtkSmartPointer<vtkFast2DLayoutStrategy> fastStrategy
            = vtkSmartPointer<vtkFast2DLayoutStrategy>::New();
        mStoredLayout->SetLayoutStrategy(fastStrategy);
    }

    mStoredLayout->Update();
    mOutPutGraph = mStoredLayout->GetOutput();
    double pos[3];
    for (int i = 0; i < mNodeSize; ++i)
    {
        mOutPutGraph->GetPoint(i, pos);
        this->mNodes[i].mAbsPosition.setX(pos[0] * 600);
        this->mNodes[i].mAbsPosition.setY(pos[1] * 600);
    }
}

