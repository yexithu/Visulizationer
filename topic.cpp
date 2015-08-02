#include "topic.h"
#include <QDebug>
TopicNode::TopicNode()
{
    mDocumentIndeces.resize(50);
}

TopicNode::~TopicNode()
{
}

UndirectedEdge::UndirectedEdge()
{
}

UndirectedEdge::~UndirectedEdge()
{
}

TopicGraph::TopicGraph(QObject *parent)
    :GraphBase(parent)
{
    ConstructScene();
}

TopicGraph::~TopicGraph()
{
}

void TopicGraph::ConstructScene()
{
    //InitailIze ExtraInformation
    LoadNodes("GraphData/TopicGraph/Nodes.txt");
    LoadEdges("GraphData/TopicGraph/Edges.txt");
    LoadDocumentContents("GraphData/TopicGraph/DocumentContent.txt");

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
        qDebug() << source << target;
    }
    for (int i = 0; i < mNodeSize; ++i)
    {
        this->addItem(mNodes[i]);
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

    int breakMark = 0;

}