#include "edgebase.h"
#include "graphbase.h"
#include <QGraphicsSceneEvent>
#include <QDebug>
EdgeBase::EdgeBase()
{
    this->setAcceptHoverEvents(true);
}

EdgeBase::~EdgeBase()
{

}
void EdgeBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::RightButton)
    {
        graphBase->UpdateEdgeDetailTextView(this);
    }
    GraphicsEdgeItem::mousePressEvent(event);
}