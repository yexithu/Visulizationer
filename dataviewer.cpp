#include "dataviewer.h"

DataViewer::DataViewer(QWidget *parent)
    :QGraphicsView()
{
    DataScene *scene = new DataScene(this);
    this->setScene(scene);

    
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

