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


    void SetNodeColor(QColor color);
protected:
    double mRadius;
    QColor mSelectedColor;
    QColor mUnselectedColor;

    QColor *mPaintColor;
    //被选中时候的颜色
    virtual void SetSelectedColor();
    //未被选中时候的颜色
    virtual void SetUnselectedColor();
    //颜色方案改变
    virtual void SetSingleMode() = 0;
    virtual void SetMultiColorMode() = 0;
    
};
#endif