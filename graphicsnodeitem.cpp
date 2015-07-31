#include "graphicsnodeitem.h"
#include <QPainter>
#include <QDebug>
#include "datascene.h"
GraphicsNodeItem::GraphicsNodeItem(int index, int radius) :mIndex(index), mRadius(radius)
{
    mPaintColor = QColor(Qt::white);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
}

GraphicsNodeItem::~GraphicsNodeItem()
{
}

QRectF GraphicsNodeItem::boundingRect() const
{
    return QRectF(-mRadius, -mRadius, 2 * mRadius, 2 * mRadius);
}

void GraphicsNodeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
    painter->setPen(mPaintColor);
    painter->setBrush(QBrush(mPaintColor, Qt::BrushStyle::SolidPattern));
    painter->drawEllipse(QRectF(QPointF(-mRadius, -mRadius), QPointF(mRadius, mRadius)));
    scene()->update();
}

QVariant GraphicsNodeItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemScenePositionHasChanged && scene())
    {
        qDebug() << "ItemValueChange";
            // value is the new position.
        QPointF newPos = value.toPointF();
    }
    return QGraphicsItem::itemChange(change, value);
}