#ifndef TOPIC_H
#define TOPIC_H
#include "nodebase.h"
#include "graphbase.h"
#include "edgebase.h"
#include <QFile>
class TopicNode : public NodeBase
{
public:
    TopicNode();
    ~TopicNode();

    friend class TopicGraph;
private:
protected:
    QStringList mTopicWords;
    vector<int> mDocumentIndeces;
};


class UndirectedEdge :public EdgeBase
{
public:
    UndirectedEdge();
    ~UndirectedEdge();
    friend class TopicGraph;
private:
    double weight;
};

class TopicGraph : public GraphBase
{
public:
    TopicGraph(QObject *parent);
    ~TopicGraph();
    
private:

    void LoadNodes(QString nodeInFileName);
    void LoadEdges(QString edgeInFileName);
    void LoadDocumentContents(QString documentInFileName);

    QFile mDocumentContentsFile;
    QMap<int, qint64> mIndexFileIndexMap;
protected:
    virtual void ConstructScene();
};


#endif // !TOPIC_H
