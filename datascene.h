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
class DataScene: public QGraphicsScene
{
    Q_OBJECT
public:
    friend class DataViewer;
    DataScene(QObject *parent = 0);
    ~DataScene();
    bool isActivateFlag = true;
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

#endif