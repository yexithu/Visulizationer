#ifndef NODEBASE_H
#define NODEBASE_H
#include "graphicsnodeitem.h"
class EdgeBase;
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
protected:
    int mNodeIndex;
    int mNodeId;
    int mDegree;
    QColor mPainterColor;
private:
    vector<EdgeBase *> mConnectedEdges;
};
#endif