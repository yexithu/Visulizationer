#ifndef GRAPHICSEDGEITEM_H
#define GRAPHICSEDGEITEM_H
#include <QGraphicsLineItem>
#include <QPen>
class GraphDataScene;
class QPen;
class GraphicsEdgeItem : public QGraphicsLineItem
{
public:
    GraphicsEdgeItem();
    ~GraphicsEdgeItem();

    enum ItemType {EdgeItem = QGraphicsItem::UserType + 2};
    int type(){ return EdgeItem; }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
    void setPen(const QPen &pen);
private:
    QPen mPaintPen;
    GraphDataScene *graphDataScene;
protected:
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

#endif // !GRAPHICSEDGEITEM_H
