#include "graphicsedgeitem.h"
#include <QCursor>
void GraphicsEdgeItem::setPen(const QPen &pen)
{
    this->mPaintPen = pen;
    QGraphicsLineItem::setPen(mPaintPen);
    
}

GraphicsEdgeItem::GraphicsEdgeItem()
{
/*
    mPaintPen.setColor(Qt::white);
    mPaintPen.setWidth(0);
    QGraphicsLineItem::setPen(mPaintPen);*/
    
}

GraphicsEdgeItem::~GraphicsEdgeItem()
{
}

void GraphicsEdgeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    this->setPen(QPen(*mPaintColor, 1));
    QGraphicsLineItem::paint(painter, option, widget);
}


void GraphicsEdgeItem::SetSelectedColor()
{
    this->mPaintColor = &mSelectedColor;
}

void GraphicsEdgeItem::SetUnselectedColor()
{
    this->mPaintColor = &mUnselectedColor;
}