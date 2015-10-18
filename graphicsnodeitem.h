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


    void SetNodeColor(QColor color);
protected:
    double mRadius;
    QColor mSelectedColor;
    QColor mUnselectedColor;

    QColor *mPaintColor;
    //��ѡ��ʱ�����ɫ
    virtual void SetSelectedColor();
    //δ��ѡ��ʱ�����ɫ
    virtual void SetUnselectedColor();
    //��ɫ�����ı�
    virtual void SetSingleMode() = 0;
    virtual void SetMultiColorMode() = 0;
    
};
#endif