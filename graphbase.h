/*
存有信息
1.Node
2.Edge
处理Gui交互
*/



#ifndef GRAPHBASE_H
#define GRAPHBASE_H

#include <iostream>
#include <QPoint>
#include <QString>
#include <QColor>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <vtkSmartPointer.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkGraphLayout.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkForceDirectedLayoutStrategy.h>
#include <vtkFast2DLayoutStrategy.h>

using namespace std;
class NodeBase;
class EdgeBase;
class GraphBase : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphBase(QObject *parent = 0);
    ~GraphBase();
    bool isActiveFlag;

    void UpDateStrategy(QString strategyName);

    void NodePositionChangeFeedBack(NodeBase *node);
    void NodeSelectedChangeFeedBack(NodeBase *node);
    void NodeVisibleChangeFeedBack(NodeBase *node);
    void FliterByDegree(int degree);

public slots:
    void FocusOnSelected();
    void DeFocus();

    void OnShowNodesChecked(int chekstate);
    void OnShowEdgesChecked(int chekstate);

    void SearchNextLayer();
private:
    
protected:
    int mNodeSize;
    int mEdgeSize;
    vector<NodeBase *> mNodes;
    vector<EdgeBase *> mEdges;
    vtkSmartPointer<vtkMutableDirectedGraph> mOriginGraph;
    vtkSmartPointer<vtkGraphLayout> mStoredLayout;
    vtkSmartPointer<vtkGraph> mOutPutGraph;
    QHash<int, int> mNodeIdHashIndex;

    void ConstructOriginGraph();
    void UpdateViewPort();
    virtual void ConstructScene() = 0;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    
    
};
#endif