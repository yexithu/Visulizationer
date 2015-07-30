#ifndef DATASCENE_H
#define DATASCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QList>
#include <QPoint>
#include <QGraphicsView>
#include "paperconferenceauthor.h"

class DataScene: public QGraphicsScene
{
    Q_OBJECT
public:
    DataScene(QObject *parent = 0);
    ~DataScene();
    
private:
    
    QList<QGraphicsEllipseItem *> mNodeGuis;
    QList<QGraphicsLineItem *> mEdgeGuis;
    PaperConferenceAuthorGraph *mPaperConferenceAuthorGraph;
    QPen paintPen;
    QBrush paintBrush;
    void ConstructScene();
    bool dragSceneFlag;
    
    QPointF drugOffset;
    QPointF viewPortCenter;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
};

#endif