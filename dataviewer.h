#ifndef DATAVIEWER_H
#define DATAVIEWER_H
#include <QGraphicsView>
#include <QWheelEvent>
#include <QTimeLine>
class PaperConferenceAuthorGraph;
class GraphDataScene;
class TopicGraph;
class GraphBase;
class QTextView;
class DataViewer : public QGraphicsView
{
    Q_OBJECT
public:
    DataViewer(QWidget *parent);
    ~DataViewer();

    QTextView *mEdgeDetailTextView;
    QTextView *mNodeDetailTextVIew;
public slots:
    void LayoutStrategyChanged(QString layoutName);
    void SetupPaperScene();
    void SetupTopicScene();

    void SetHandScrollMode();
    void SetRubberBandMode();
    
    GraphBase * GetScene();
private:
    GraphBase *graphScene;
private slots:
    void scalingTime(qreal x);
    void animFinished();
protected:
    void enterEvent(QEvent *);
    void wheelEvent(QWheelEvent *event);
    void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    int mNumScheduledScalings;
};
#endif