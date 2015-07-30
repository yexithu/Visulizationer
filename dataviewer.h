#ifndef DATAVIEWER_H
#define DATAVIEWER_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>
#include "datascene.h"
class DataViewer : public QGraphicsView
{
    Q_OBJECT
public:
    DataViewer(QWidget *parent);
    ~DataViewer();

private:
    DataScene *scene;
private slots:
    void scalingTime(qreal x);
    void animFinished();
protected:
    void wheelEvent(QWheelEvent *event);
    int mNumScheduledScalings;
};
#endif