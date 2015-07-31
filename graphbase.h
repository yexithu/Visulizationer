#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <iostream>
#include <QPoint>
#include <QString>
#include <QColor>
using namespace std;

class NodeBase
{
public:
    NodeBase();
    ~NodeBase();

protected:
    int mNodeId;
    int mRadius;
    int mDegree;
    QPointF mAbsPosition;
    QColor mNodeColor;

public:
    inline QPointF GetPoint()
    {
        return mAbsPosition;
    }
    inline int GetRadius()
    {
        return mRadius;
    }
    static inline QString GetStem(const QString &origin)
    {
        int index = origin.indexOf(':');
        QString temp = origin.right(origin.length() - index - 2);
        int mark = 0;
        return temp;
    }
};


class EdgeBase
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
    //defualt
    //0 the source 1 the target
    int mEdgeIndex;
    int mNodeId[2];
    int mNodeIndex[2];
};



class GraphBase
{
public:
    GraphBase();
    ~GraphBase();
    int mNodeSize;
    int mEdgeSize;
private:

protected:

};


#endif