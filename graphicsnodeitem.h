/*
node基类 只处理与gui有关的事情
NodeBase决定有关属性
留下itemchange接口
*/







#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "graphicsnodeitem.h"
class GraphDataScene;
class GraphicsNodeItem :public QGraphicsItem
{
public:
    GraphicsNodeItem();
    ~GraphicsNodeItem();

    
    enum ItemType { NodeItem = QGraphicsItem::UserType + 1 };
    int type() { return NodeItem; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);


    QColor mPaintColor;    
    void SetNodeColor(QColor color);
protected:
    double mRadius;
    
};
#endif