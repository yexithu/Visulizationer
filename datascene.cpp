
#include "datascene.h"
#include "dataviewer.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QDebug>
DataScene::DataScene(QObject *parent)
    : QGraphicsScene(parent)
{
    paintPen.setWidth(0);
    paintPen.setColor(Qt::white);
    paintPen.setStyle(Qt::PenStyle::SolidLine);
    paintBrush.setColor(Qt::white);
    paintBrush.setStyle(Qt::BrushStyle::SolidPattern);
    dragSceneFlag = false;
    pointItem = NULL;
    
}

DataScene::~DataScene()
{
}


void DataScene::ConstructScene()
{
    int start = clock();
    for (int i = 0; i < mPaperConferenceAuthorGraph->mEdgeSize; ++i)
    {
        QGraphicsLineItem *lineItem;
        int *index = mPaperConferenceAuthorGraph->mEdges[i].GetNodeIndex();
        QPointF source = mPaperConferenceAuthorGraph->mNodes[index[0]].GetPoint();
        QPointF target = mPaperConferenceAuthorGraph->mNodes[index[1]].GetPoint();
        lineItem = this->addLine(source.x(), source.y(), target.x(), target.y(), paintPen);
        this->mEdgeGuis.append(lineItem);
    }
    qDebug() << "ConstructTime" << clock() - start;
    paintPen.setColor(Qt::white);
    for (int i = 0; i < mPaperConferenceAuthorGraph->mNodeSize; ++i)
    {
        GraphicsNodeItem *ellipseItem;
        QPointF ellipsCenter = mPaperConferenceAuthorGraph->mNodes[i].GetPoint();
        int radius = mPaperConferenceAuthorGraph->mNodes[i].GetRadius();
        QPointF diaog = QPointF(radius,radius);
        ellipseItem = new GraphicsNodeItem(i, radius);
        this->addItem(ellipseItem);
        ellipseItem->setPos(ellipsCenter);
        this->mNodeGuis.append(ellipseItem);
    }
    
}

void DataScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        qDebug() << "LeftPressed" << endl;
        QPointF itemPoint = event->scenePos();
        pointItem = this->itemAt(itemPoint, QTransform());
        if (pointItem != NULL)
        {
            qDebug() << pointItem << pointItem->scenePos();
        }
        
    }
    QGraphicsScene::mousePressEvent(event);
}

void DataScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //if (event->button() == Qt::MouseButton::LeftButton)
    {
        qDebug() << "LeftButtomMoveEvent" << endl;
        if (pointItem != NULL)
        {
            qDebug() << event->scenePos() << endl;
            UpdataEdgePosition();
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DataScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::LeftButton)
    {
        if (pointItem != 0)
        {
            qDebug() << pointItem << pointItem->scenePos();
            UpdataEdgePosition();
            pointItem = NULL;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void DataScene::UpdataEdgePosition()
{
    int start = clock();
    for (int i = 0; i < mEdgeGuis.size(); ++i)
    {
        int *index = mPaperConferenceAuthorGraph->mEdges[i].GetNodeIndex();
        QPointF source = mNodeGuis[index[0]]->scenePos();
        QPointF target = mNodeGuis[index[1]]->scenePos();
        mEdgeGuis[i]->setPen(paintPen);
        mEdgeGuis[i]->setLine(QLineF(source, target));
    }
    this->update();

    qDebug() << "Time" << clock() - start;
}

void DataScene::updateViewPort()
{
    QGraphicsView view = this->views()[0];
    QRect viewPort = view.viewport()->rect();
    QPoint r1, r2;
    r1 = viewPort.topLeft();
    r2 = viewPort.bottomRight();

    update(QRectF(view.mapToScene(r1), view.mapToScene(r2)));

}

void DataScene::SetUpForPaper()
{
    mPaperConferenceAuthorGraph = new PaperConferenceAuthorGraph;
    mPaperConferenceAuthorGraph->UpDateStrategy("Circular");
    ConstructScene();
}

void DataScene::UpdataAllPosition()
{
    int start = clock();
    for (int i = 0; i < mEdgeGuis.size(); ++i)
    {
        int *index = mPaperConferenceAuthorGraph->mEdges[i].GetNodeIndex();
        QPointF source = mPaperConferenceAuthorGraph->mNodes[index[0]].GetPoint();
        QPointF target = mPaperConferenceAuthorGraph->mNodes[index[1]].GetPoint();
        mEdgeGuis[i]->setPen(paintPen);
        mEdgeGuis[i]->setLine(QLineF(source, target));
    }
    paintPen.setColor(Qt::white);
    for (int i = 0; i < mPaperConferenceAuthorGraph->mNodeSize; ++i)
    {
        QPointF ellipsCenter = mPaperConferenceAuthorGraph->mNodes[i].GetPoint();
        mNodeGuis[i]->setPos(ellipsCenter);
    }
    this->updateViewPort();
}