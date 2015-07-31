#include "dataviewer.h"
#include "GraphDataScene.h"
#include "paperconferenceauthor.h"
DataViewer::DataViewer(QWidget *parent)
    :QGraphicsView()
{
    this->setDragMode(QGraphicsView::ScrollHandDrag);
    this->setRenderHint(QPainter::Antialiasing);
    QBrush backGround(QColor(15, 15, 15), Qt::BrushStyle::SolidPattern);
    this->setBackgroundBrush(backGround);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    
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
    this->paperConferenceAuthorGraph->UpDateStrategy(layoutName);
    
}

void DataViewer::SetupPaperScene()
{
    this->paperConferenceAuthorGraph = new PaperConferenceAuthorGraph(this);
    setScene(paperConferenceAuthorGraph);
}