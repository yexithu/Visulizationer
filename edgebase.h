#ifndef EDGEBASE_H
#define EDGEBASE_H
#include "graphicsedgeitem.h"

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

private:

};

#endif