#include "graphicsnodeitem.h"
#include <QPainter>
#include <QDebug>
#include "GraphDataScene.h"
#include <QCursor>
GraphicsNodeItem::GraphicsNodeItem()
{
    mRadius = 4;
    //mPaintColor = QColor(Qt::white);
    this->setFlag(QGraphicsItem::ItemIsMovable, true);
    this->setFlag(QGraphicsItem::ItemIsSelectable, true);
    this->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
    this->setCursor(QCursor(Qt::PointingHandCursor));
    /*this->setFlag(QGraphicsItem::ItemSendsSelectedChange, true);*/
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
    painter->setPen(*mPaintColor);
    painter->setBrush(QBrush(*mPaintColor, Qt::BrushStyle::SolidPattern));
    painter->drawEllipse(QRectF(QPointF(-mRadius, -mRadius), QPointF(mRadius, mRadius)));
    scene()->update();
}

void GraphicsNodeItem::SetNodeColor(QColor color)
{
    *mPaintColor = color;
}



void GraphicsNodeItem::SetSelectedColor()
{
    this->mPaintColor = &mSelectedColor;
}

void GraphicsNodeItem::SetUnselectedColor()
{
    this->mPaintColor = &mUnselectedColor;
}