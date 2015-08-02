#include "nodebase.h"
#include "graphbase.h"
#include <QDebug>
NodeBase::NodeBase()
{
    mDegree = 0;
}

NodeBase::~NodeBase()
{
}

QVariant NodeBase::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged && scene())
    {
        //qDebug() << "ItemValueChange";
        // value is the new position.
        this->graphBase->NodePositionChangeFeedBack(this);
    }
    
    if (change == ItemSelectedChange && scene())
    {
        //qDebug() << "Node " << this->mNodeIndex << this->isSelected();
        this->graphBase->NodeSelectedChangeFeedBack(this);
    }
    /*if (change == ItemVisibleChange && scene())
    {
        qDebug() << "Node VisibleChange" << this->mNodeIndex << this->isVisible();
        this->graphBase->NodeVisibleChangeFeedBack(this);
    }*/
    return QGraphicsItem::itemChange(change, value);
}