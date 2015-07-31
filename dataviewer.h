#ifndef DATAVIEWER_H
#define DATAVIEWER_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>
class PaperConferenceAuthorGraph;
class DataScene;
class DataViewer : public QGraphicsView
{
    Q_OBJECT
public:
    DataViewer(QWidget *parent);
    ~DataViewer();
public slots:
    void LayoutStrategyChanged(QString layoutName);
    void SetupPaperScene();
    
private:
    DataScene *dataScene;
private slots:
    void scalingTime(qreal x);
    void animFinished();
protected:
    void wheelEvent(QWheelEvent *event);
    int mNumScheduledScalings;
};
#endif