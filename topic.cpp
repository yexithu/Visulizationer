#include "topic.h"
#include <QDebug>

TopicNode::TopicNode()
{
    mDocumentIndeces.resize(50);

    //SetMultiColorMode();
    SetUnselectedColor();
}

TopicNode::~TopicNode()
{
}

void TopicNode::SetSingleMode()
{
    mSelectedColor = QColor(182, 43, 30, 255);
    mUnselectedColor = QColor(96, 96, 96, 200);
}

void TopicNode::SetMultiColorMode()
{
    mSelectedColor = QColor(173, 50, 109);
    int gradient = this->mDegree * 5 / graphBase->mHighestDegree;
    if (gradient == 0)
        mUnselectedColor = QColor(255, 226, 210);
    if (gradient == 1)
        mUnselectedColor = QColor(247, 168, 151);
    if (gradient == 2)
        mUnselectedColor = QColor(239, 108, 90);
    if (gradient == 3)
        mUnselectedColor = QColor(201, 52, 47);
    if (gradient >= 4)
        mUnselectedColor = QColor(152, 4, 27);
}


void TopicNode::SetNodeToolTip()
{
    QString toolTip;
    toolTip += "Topic Node\n";
    toolTip += "ID: " + QString::number(this->mNodeIndex) + "\n";
    toolTip += "Degree: " + QString::number(this->mDegree);
    this->setToolTip(toolTip);
}

QString TopicNode::GetDetail()
{
    QString detail;
    detail.append(this->toolTip() + "\n");
    detail.append("TopicWord: ");
    for (QString topicword: mTopicWords)
    {
        detail.append(topicword + " ");
    }
    detail.append("\n");

    for (int index :mDocumentIndeces)
    {
        detail.append(TopicGraph::GetDocument(index));
    }
    return detail;

}



UndirectedEdge::UndirectedEdge()
{
    SetMultiColorMode();
    SetUnselectedColor();
}

UndirectedEdge::~UndirectedEdge()
{
}

void UndirectedEdge::SetSingleMode()
{
    mSelectedColor = QColor(46, 105, 153, 255);
    mUnselectedColor = QColor(96, 96, 96, 200);
}

void UndirectedEdge::SetMultiColorMode()
{
    mSelectedColor = QColor(220, 156, 211, 200);
    int gradient = this->weight / 0.2;
    if (gradient == 0)
        mUnselectedColor = QColor(210, 236, 215);
    if (gradient == 1)
        mUnselectedColor = QColor(128, 206, 208);
    if (gradient == 2)
        mUnselectedColor = QColor(0, 174, 179);
    if (gradient == 3)
        mUnselectedColor = QColor(26, 133, 142);
    if (gradient >= 4)
        mUnselectedColor = QColor(14, 92, 104);
}


void UndirectedEdge::SetEdgeToolTip()
{
    QString toolTip;
    int *Id = this->GetNodeId();
    toolTip += "Wight: " + QString::number(this->weight) + "\n";
    toolTip += "Node: " + QString::number(Id[0]);
    toolTip += ", Node: " + QString::number(Id[1]);
    this->setToolTip(toolTip);
}
TopicGraph::TopicGraph(QObject *parent)
    :GraphBase(parent)
{
    ConstructScene();
}


QFile TopicGraph::mDocumentContentsFile;
QMap<int, qint64> TopicGraph::mIndexFileIndexMap;
TopicGraph::~TopicGraph()
{
    mDocumentContentsFile.close();
}

void TopicGraph::ConstructScene()
{
    //InitailIze ExtraInformation
    LoadNodes("GraphData/TopicGraph/Nodes.txt");
    LoadEdges("GraphData/TopicGraph/Edges.txt");
    LoadDocumentContents("GraphData/TopicGraph/DocumentContent.txt");

    this->mHighestDegree = GetHighestDegree();
    //add to scene
    ConstructOriginGraph();
    UpDateStrategy("Circular");

    for (int i = 0; i < mEdgeSize; ++i)
    {
        int *index = mEdges[i]->GetNodeIndex();
        QPointF source = mNodes[index[0]]->scenePos();
        QPointF target = mNodes[index[1]]->scenePos();

        mEdges[i]->setLine(QLineF(source, target));
        mEdges[i]->SetEdgeToolTip();
        mEdges[i]->SetMultiColorMode();
        this->addItem(mEdges[i]);
    }
    for (int i = 0; i < mNodeSize; ++i)
    {
        this->addItem(mNodes[i]);
        mNodes[i]->SetNodeToolTip();
        mNodes[i]->SetMultiColorMode();
       // qDebug() << mNodes[i]->mNodeId;
    }
}

void TopicGraph::LoadNodes(QString nodeInFileName)
{
    QFile inFile(nodeInFileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QString buffer;
    QStringList indexList;
    int index = -1;
    while (true)
    {
        ++index;
        TopicNode *topicNode = new TopicNode;
        topicNode->mNodeIndex = index;
        buffer = inFile.readLine();
        topicNode->mNodeId = buffer.toInt();
        if (topicNode->mNodeId == 0)
        {
            this->mNodeSize = index;
            break;
        }
        buffer = inFile.readLine();
        buffer = NodeBase::GetStem(buffer);
        topicNode->mTopicWords = buffer.split(QRegExp("\\s+"));
        topicNode->mTopicWords.pop_back();

        buffer = inFile.readLine();
        buffer = NodeBase::GetStem(buffer);
        indexList = buffer.split(QRegExp("\\s+"));
        indexList.pop_back();
        for (int i = 0; i < indexList.size(); ++i)
        {
            topicNode->mDocumentIndeces[i] = indexList[i].toInt();
        }
        topicNode->graphBase = this;
        this->mNodes.push_back(topicNode);
        mNodeIdHashIndex.insert(topicNode->mNodeId, topicNode->mNodeIndex);
        inFile.readLine();
        //qDebug() << topicNode->mNodeIndex << "  " << topicNode->mNodeId;
    }

    inFile.close();

}

void TopicGraph::LoadEdges(QString edgeInFileName)
{
    QFile inFile(edgeInFileName);
    inFile.open(QIODevice::ReadOnly | QIODevice::Text);

    int index = -1;
    QString buffer;
    QStringList numberList;
    while (true)
    {
        ++index;
        
        buffer = inFile.readLine();
        numberList = buffer.split(QRegExp("\\s+"));
        int source, target;
        source = numberList[0].toInt();
        if (source == 0)
        {
            this->mEdgeSize = index;
            break;
        }
        target = numberList[1].toInt();
        UndirectedEdge *edge = new UndirectedEdge;
        edge->graphBase = this;
        edge->weight = numberList[2].toDouble();
        edge->mEdgeIndex = index;
        edge->mNodeId[0] = source;
        edge->mNodeId[1] = target;
        edge->mNodeIndex[0] = this->mNodeIdHashIndex.value(source);
        edge->mNodeIndex[1] = this->mNodeIdHashIndex.value(target);

        mNodes[edge->mNodeIndex[0]]->mDegree++;
        mNodes[edge->mNodeIndex[1]]->mDegree++;
        mNodes[edge->mNodeIndex[0]]->mConnectedEdges.push_back(edge);
        mNodes[edge->mNodeIndex[1]]->mConnectedEdges.push_back(edge);

        this->mEdges.push_back(edge);
        //qDebug() << index << "  " << source << " " << target;
    }
    inFile.close();
}

void TopicGraph::LoadDocumentContents(QString documentInFileName)
{
    mDocumentContentsFile.setFileName(documentInFileName);
    mDocumentContentsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    
    int documentId;
    qint64 filePos;
    QString buffer;
    while (true)
    {
        
        buffer = mDocumentContentsFile.readLine();
        int documentId = buffer.toInt();
        if (documentId == 0)
        {
            break;
        }
        filePos = mDocumentContentsFile.pos();
        mIndexFileIndexMap.insert(documentId, filePos);
        mDocumentContentsFile.readLine();
        mDocumentContentsFile.readLine();
        mDocumentContentsFile.readLine();
    }

/*
    mDocumentContentsFile.seek(mIndexFileIndexMap.value(19));
    buffer = mDocumentContentsFile.readLine();
    qDebug() << buffer;

    mDocumentContentsFile.seek(mIndexFileIndexMap.value(33));
    buffer = mDocumentContentsFile.readLine(98611);
    qDebug() << buffer;*/

}
QString TopicGraph::GetDocument(int index)
{
    QString document, buffer;
    mDocumentContentsFile.seek(mIndexFileIndexMap.value(19));
    buffer = mDocumentContentsFile.readLine();
    document.append(buffer + "\n");
    buffer = mDocumentContentsFile.readLine();
    document.append(buffer + "\n");
   
    return document;
}
void TopicGraph::UpdateEndPosition(QString strategyName)
{
    double pos[3];
    mAnimationEndPosition.clear();
    for (int i = 0; i < mNodeSize; ++i)
    {
        QPointF endPos;
        //ban flag

        mOutPutGraph->GetPoint(i, pos);
        if (strategyName == "Circular")
        {
            endPos.setX(pos[0] * 300);
            endPos.setY(pos[1] * 300);
        }
        if (strategyName == "ForceDirected")
        {
            endPos.setX(pos[0] * 600);
            endPos.setY(pos[1] * 600);
        }
        if (strategyName == "Fast2D")
        {
            endPos.setX(pos[0] * 34 - 17);
            endPos.setY(pos[1] * 44 + 14.3);
        }
        mAnimationEndPosition.push_back(endPos);
    }
}