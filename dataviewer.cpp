#include "dataviewer.h"
#include "GraphDataScene.h"
#include "graphbase.h"
#include "paperconferenceauthor.h"
#include "topic.h"
DataViewer::DataViewer(QWidget *parent)
    :QGraphicsView()
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
    this->setRenderHint(QPainter::Antialiasing);
    this->graphScene = NULL;
    QBrush backGround(QColor(15, 15, 15), Qt::BrushStyle::SolidPattern);
    this->setBackgroundBrush(backGround);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    mNumScheduledScalings = 0;
    //setCursor(Qt::PointingHandCursor);
}

DataViewer::~DataViewer()
{
}


void DataViewer::wheelEvent(QWheelEvent * event)
{
    int numDegrees = event->delta() / 8;
    int numSteps = numDegrees / 15; // see QWheelEvent documentation
    mNumScheduledScalings += numSteps;
    if (mNumScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
        mNumScheduledScalings = numSteps;
    QTimeLine *anim = new QTimeLine(350, this);
    anim->setUpdateInterval(20);

    connect(anim, SIGNAL(valueChanged(qreal)), SLOT(scalingTime(qreal)));
    connect(anim, SIGNAL(finished()), SLOT(animFinished()));
    anim->start();
    //QWidget::wheelEvent(event);
}

void DataViewer::scalingTime(qreal x)
{
    qreal factor = 1.0 + qreal(mNumScheduledScalings) / 300.0;
    scale(factor, factor);
}

void DataViewer::animFinished()
{

    if (mNumScheduledScalings > 0)
        mNumScheduledScalings;
    else
        mNumScheduledScalings++;
    sender()->~QObject();
}

void DataViewer::LayoutStrategyChanged(QString layoutName)
{
    this->graphScene->UpDateStrategy(layoutName);
    
}

void DataViewer::SetupPaperScene()
{
    if (this->graphScene != NULL)
    {
        delete graphScene;
    }
    this->graphScene = new PaperConferenceAuthorGraph(this);
    setScene(graphScene);
}

void DataViewer::SetupTopicScene()
{
    if (this->graphScene != NULL)
    {
        delete graphScene;
    }
    this->graphScene = new TopicGraph(this);
    setScene(graphScene);
}

void DataViewer::enterEvent(QEvent *event)
{

    QGraphicsView::enterEvent(event);
}

void DataViewer::mousePressEvent(QMouseEvent *event)
{
    /*if (event->button() == Qt::RightButton)
    {
        if (this->dragMode() == RubberBandDrag)
        {
            setDragMode(ScrollHandDrag);
            this->mousePressEvent(event);
        }
    }
    */
    QGraphicsView::mousePressEvent(event);
}

void DataViewer::mouseReleaseEvent(QMouseEvent *event)
{
    /*if (event->button() == Qt::RightButton)
    {
        setDragMode(QGraphicsView::RubberBandDrag);
    }
    */
    QGraphicsView::mouseReleaseEvent(event);
}



GraphBase * DataViewer::GetScene()
{
    return this->graphScene;
}

void DataViewer::SetHandScrollMode()
{
    this->setDragMode(QGraphicsView::ScrollHandDrag);
}

void DataViewer::SetRubberBandMode()
{
    this->setDragMode(QGraphicsView::RubberBandDrag);
}