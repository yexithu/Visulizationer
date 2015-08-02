/*
node���� ֻ������gui�йص�����
NodeBase�����й�����
����itemchange�ӿ�
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