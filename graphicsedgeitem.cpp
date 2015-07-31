#include "graphicsedgeitem.h"
void GraphicsEdgeItem::setPen(const QPen &pen)
{
    this->mPaintPen = pen;
    QGraphicsLineItem::setPen(mPaintPen);
}

GraphicsEdgeItem::GraphicsEdgeItem()
{
    mPaintPen.setColor(Qt::white);
    mPaintPen.setWidth(0);
    QGraphicsLineItem::setPen(mPaintPen);
    
}

GraphicsEdgeItem::~GraphicsEdgeItem()
{
}