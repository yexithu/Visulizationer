#ifndef DATAVIEWER_H
#define DATAVIEWER_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>
class PaperConferenceAuthorGraph;
class GraphDataScene;
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
    PaperConferenceAuthorGraph *paperConferenceAuthorGraph;
private slots:
    void scalingTime(qreal x);
    void animFinished();
protected:
    void wheelEvent(QWheelEvent *event);
    int mNumScheduledScalings;
};
#endif