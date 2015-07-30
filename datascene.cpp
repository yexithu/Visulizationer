
#include "datascene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QDebug>
DataScene::DataScene(QObject *parent)
    : QGraphicsScene(parent)
{
    paintPen.setWidth(0.1);
    paintPen.setColor(Qt::white);
    paintPen.setStyle(Qt::PenStyle::SolidLine);
    paintBrush.setColor(Qt::white);
    paintBrush.setStyle(Qt::BrushStyle::SolidPattern);
    this->mPaperConferenceAuthorGraph = new PaperConferenceAuthorGraph;
    mPaperConferenceAuthorGraph->UpDateStrategy("Circular");
    //mPaperConferenceAuthorGraph->UpDateStrategy("ForceDirected");
    //mPaperConferenceAuthorGraph->UpDateStrategy("Fast2D");
    ConstructScene();
}

DataScene::~DataScene()
{
}


void DataScene::ConstructScene()
{
    for (int i = 0; i < mPaperConferenceAuthorGraph->mEdgeSize; ++i)
    {
        QGraphicsLineItem *lineItem;
        int *index = mPaperConferenceAuthorGraph->mEdges[i].GetNodeIndex();
        QPointF source = mPaperConferenceAuthorGraph->mNodes[index[0]].GetPoint();
        QPointF target = mPaperConferenceAuthorGraph->mNodes[index[1]].GetPoint();
        lineItem = this->addLine(source.x(), source.y(), target.x(), target.y(), paintPen);
        this->mEdgeGuis.append(lineItem);
    }

    paintPen.setColor(Qt::white);
    for (int i = 0; i < mPaperConferenceAuthorGraph->mNodeSize; ++i)
    {
        QGraphicsEllipseItem *ellipseItem;
        QPointF ellipsCenter = mPaperConferenceAuthorGraph->mNodes[i].GetPoint();
        int radius = mPaperConferenceAuthorGraph->mNodes[i].GetRadius();
        QPointF diaog = QPointF(radius,radius);
        ellipseItem = this->addEllipse(QRectF(ellipsCenter - diaog, ellipsCenter + diaog), paintPen, paintBrush);
        this->mNodeGuis.append(ellipseItem);
    }
}

void DataScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MouseButton::MiddleButton)
    {
        qDebug() << "MousePress Mid" << endl;
/*
        dragSceneFlag = true;
        QPoint vcenter = this->views()[0]->viewport()->rect().center();
        viewPortCenter = this->views()[0]->mapToScene(vcenter);
        qDebug() << "ViewCenter" << viewPortCenter;
        qDebug() << "SceneCenter" << this->sceneRect().center();
        drugOffset = event->scenePos();*/
    }
}

void DataScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "Moving" << endl;
    if (dragSceneFlag)
    {
/*
        qDebug() << "Drugging" << endl;
        viewPortCenter = viewPortCenter - event->scenePos() + drugOffset;
        this->views()[0]->centerOn(viewPortCenter);*/
    }
}

void DataScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << "release" << endl;
    if (event->button() == Qt::MouseButton::MiddleButton)
    {
/*
        qDebug() << "MousePress Mid" << endl;
        dragSceneFlag = false;*/
    }
}