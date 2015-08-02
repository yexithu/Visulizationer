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

PaperConferenceAuthorGraph::PaperConferenceAuthorGraph(QObject *parent)
    :GraphBase(parent)
{
    
    ConstructScene();
}

PaperConferenceAuthorGraph::~PaperConferenceAuthorGraph()
{
}

void PaperConferenceAuthorGraph::ConstructScene()
{
    //InitialLize ExtraInfomation
    LoadNodes("GraphData/PaperConferenceAuthorGraph/Nodes.txt");
    LoadEdges("GraphData/PaperConferenceAuthorGraph/Edges.txt");

    //add to scene
    ConstructOriginGraph();
    UpDateStrategy("Circular");

   
    for (int i = 0; i < mEdgeSize; ++i)
    {
        int *index = mEdges[i]->GetNodeIndex();
        QPointF source = mNodes[index[0]]->scenePos();
        QPointF target = mNodes[index[1]]->scenePos();
        
        mEdges[i]->setLine(QLineF(source, target));
        this->addItem(mEdges[i]);
    }
    for (int i = 0; i < mNodeSize; ++i)
    {
        this->addItem(mNodes[i]);
    }
    
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
            PaperNode *paperNode = new PaperNode(index, nodeId, AcademicNode::Paper, year, viewColor, idString, viewLabel, viewLayout);
            paperNode->mAuthors = author;
            paperNode->mDataFrom = dateFrom;
            paperNode->mPageFrom = pageFrom;
            paperNode->mPaperTitle = detail;
            paperNode->mPaperTitleShort = detailShort;
            paperNode->graphBase = this;
            
            this->mNodes.push_back(paperNode);
            tea.push_back(paperNode);
        }

        if (typeString.at(0) == 'c')
        {
            ConferenceNode *conferenceNode= new ConferenceNode(index, nodeId, AcademicNode::Paper, year, viewColor, idString, viewLabel, viewLayout);
            conferenceNode->mConferenceName = detail;
            conferenceNode->mConferenceNameShort = detailShort;
            conferenceNode->graphBase = this;
            this->mNodes.push_back(conferenceNode);
        }

        if (typeString.at(0) == 'a')
        {
            AuthorNode *authorNode = new AuthorNode(index, nodeId, AcademicNode::Paper, year, viewColor, idString, viewLabel, viewLayout);
            authorNode->mAuthorName = detail;
            authorNode->mAuthorNameShort = detail;
            authorNode->graphBase = this;
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
            DirectedEdge *directedEdge = new DirectedEdge;
            directedEdge->mEdgeIndex = index;
            directedEdge->mNodeId[0] = source;
            directedEdge->mNodeId[1] = target;
            directedEdge->mNodeIndex[0] = this->mNodeIdHashIndex.value(source);
            directedEdge->mNodeIndex[1] = this->mNodeIdHashIndex.value(target);

            mNodes[directedEdge->mNodeIndex[0]]->mDegree++;
            mNodes[directedEdge->mNodeIndex[1]]->mDegree++;
            mNodes[directedEdge->mNodeIndex[0]]->mConnectedEdges.push_back(directedEdge);
            mNodes[directedEdge->mNodeIndex[1]]->mConnectedEdges.push_back(directedEdge);
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

        this->mNodes[i]->setX(randX);
        this->mNodes[i]->setY(randY);
    } 
}
