#ifndef EDGEBASE_H
#define EDGEBASE_H
#include "graphicsedgeitem.h"
#include <QTimeLine>
class GraphBase;
class EdgeBase :public GraphicsEdgeItem
{
public:
    EdgeBase();
    ~EdgeBase();
    inline int *GetNodeIndex()
    {
        return this->mNodeIndex;
    }
    inline int *GetNodeId()
    {
        return this->mNodeId;
    }
protected:
    //defult
    //0 the source, 1the target
    int mEdgeIndex;
    int mNodeId[2];
    int mNodeIndex[2];

    GraphBase *graphBase;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);

    virtual void SetEdgeToolTip() = 0;

private:
    friend class GraphBase;
    friend class TopicGraph;
    friend class PaperConferenceAuthorGraph;
};

#endif