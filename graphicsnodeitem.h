#ifndef GRAPHICSNODEITEM_H
#define GRAPHICSNODEITEM_H
#include <QGraphicsItem>
#include <QGraphicsScene>
#include "graphicsnodeitem.h"
class DataScene;
class GraphicsNodeItem :public QGraphicsItem
{
public:
    
    enum ItemType { NodeItem = QGraphicsItem::UserType + 1 };
    int type() { return NodeItem; }
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    QColor mPaintColor;
    GraphicsNodeItem(int index, int radius);
    ~GraphicsNodeItem();
    
    DataScene *datascene;
    
    
private:
    int mIndex;
    double mRadius;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};
#endif