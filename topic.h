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

    QString GetDetail();
    friend class TopicGraph;
private:
protected:
    QStringList mTopicWords;
    vector<int> mDocumentIndeces;

    //��ɫ�����ı�
    virtual void SetSingleMode();
    virtual void SetMultiColorMode();

    virtual void SetNodeToolTip();
};


class UndirectedEdge :public EdgeBase
{
public:
    UndirectedEdge();
    ~UndirectedEdge();
    friend class TopicGraph;
private:
    double weight;
protected:
    //��ɫ�����ı�
    virtual void SetSingleMode();
    virtual void SetMultiColorMode();

    virtual void SetEdgeToolTip();
};

class TopicGraph : public GraphBase
{
public:
    TopicGraph(QObject *parent);
    ~TopicGraph();
    
    static QString GetDocument(int index);
private:

    void LoadNodes(QString nodeInFileName);
    void LoadEdges(QString edgeInFileName);
    void LoadDocumentContents(QString documentInFileName);

    static QFile mDocumentContentsFile;
    static QMap<int, qint64> mIndexFileIndexMap;
protected:
    virtual void UpdateEndPosition(QString strategyName);
    virtual void ConstructScene();
};


#endif // !TOPIC_H
