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
   
    void setPen(const QPen &pen);
private:
    QPen mPaintPen;
    GraphDataScene *graphDataScene;

};

#endif // !GRAPHICSEDGEITEM_H
