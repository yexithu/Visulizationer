#ifndef NODEBASE_H
#define NODEBASE_H
#include "graphicsnodeitem.h"
#include <vector>
using std::vector;
class EdgeBase;
class GraphBase;
class NodeBase : public GraphicsNodeItem
{
public:
    NodeBase();
    ~NodeBase();

    static inline QString GetStem(const QString &origin)
    {
        int index = origin.indexOf(':');
        QString temp = origin.right(origin.length() - index - 2);
        int mark = 0;
        return temp;
    }

    virtual QString GetDetail() = 0;
protected:
    GraphBase *graphBase;
    int mNodeIndex;
    int mNodeId;
    int mDegree;

    vector<EdgeBase *> mConnectedEdges;
    QColor mPainterColor;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    virtual void SetNodeToolTip() = 0;
    
private:
    
    friend class PaperConferenceAuthorGraph;
    friend class TopicGraph;
    friend class GraphBase;
};
#endif