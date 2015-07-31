/*

#ifndef DATASCENE_H
#define DATASCENE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QList>
#include <QPoint>
#include <QGraphicsView>
#include "paperconferenceauthor.h"
#include "graphicsnodeitem.h"

class DataViewer;
class GraphDataScene: public QGraphicsScene
{
    Q_OBJECT
public:
    friend class DataViewer;
    GraphDataScene(QObject *parent = 0);
    ~GraphDataScene();
    bool isActivateFlag;
private:
    
    QList<GraphicsNodeItem *> mNodeGuis;
    QList<QGraphicsLineItem *> mEdgeGuis;
    PaperConferenceAuthorGraph *mPaperConferenceAuthorGraph;
    QPen paintPen;
    QBrush paintBrush;
        
    bool dragSceneFlag;
    
    QPointF drugOffset; 
    QPointF viewPortCenter;
    QGraphicsItem *pointItem;

    void updateViewPort();
    void SetUpForPaper();
    void ConstructScene();
    void UpdataEdgePosition();
    void UpdataAllPosition();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    
};

#endif*/