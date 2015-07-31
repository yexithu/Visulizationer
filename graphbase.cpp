#include "graphbase.h"
#include "edgebase.h"
#include "nodebase.h"
#include <QGraphicsView>
GraphBase::GraphBase(QObject *parent)
    :QGraphicsScene(parent)
{
    
    
}

GraphBase::~GraphBase()
{
}

void GraphBase::ConstructOriginGraph()
{
    this->mOriginGraph = vtkSmartPointer<vtkMutableDirectedGraph>::New();

    vector<vtkIdType> vtkNodes;
    for (vtkIdType i = 0; i < this->mNodeSize; ++i)
    {
        vtkIdType aNode = mOriginGraph->AddVertex();
        vtkNodes.push_back(aNode);
    }

    for (vtkIdType i = 0; i < this->mEdgeSize; ++i)
    {
        int *vtkIndex = this->mEdges[i]->GetNodeIndex();
        mOriginGraph->AddEdge(vtkNodes[vtkIndex[0]],vtkNodes[vtkIndex[1]]);
    }

    mStoredLayout = vtkSmartPointer<vtkGraphLayout>::New();
    mStoredLayout->SetInputData(mOriginGraph);
}

/* 直接改变位置*/

void GraphBase::UpDateStrategy(QString strategyName)
{
    if (strategyName == "Circular")
    {
        vtkSmartPointer<vtkCircularLayoutStrategy> circularStrategy
            = vtkSmartPointer<vtkCircularLayoutStrategy>::New();
        mStoredLayout->SetLayoutStrategy(circularStrategy);
    }
    if (strategyName == "ForceDirected")
    {
        vtkSmartPointer<vtkForceDirectedLayoutStrategy> forceStrategy
            = vtkSmartPointer<vtkForceDirectedLayoutStrategy>::New();
        mStoredLayout->SetLayoutStrategy(forceStrategy);
    }
    if (strategyName == "Fast2D")
    {
        vtkSmartPointer<vtkFast2DLayoutStrategy> fastStrategy
            = vtkSmartPointer<vtkFast2DLayoutStrategy>::New();
        mStoredLayout->SetLayoutStrategy(fastStrategy);
    }

    mStoredLayout->Update();
    mOutPutGraph = mStoredLayout->GetOutput();
    double pos[3];
    for (int i = 0; i < mNodeSize; ++i)
    {
        mOutPutGraph->GetPoint(i, pos);
        this->mNodes[i]->setX(pos[0] * 600);
        this->mNodes[i]->setY(pos[1] * 600);
    }
    for (int i = 0; i < mEdgeSize; ++i)
    {
        int *index = mEdges[i]->GetNodeIndex();
        QPointF source = mNodes[index[0]]->scenePos();
        QPointF target = mNodes[index[1]]->scenePos();

        mEdges[i]->setLine(QLineF(source, target));
    }
}

void GraphBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    UpdateViewPort();
    QGraphicsScene::mousePressEvent(event);
}
void GraphBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    UpdateViewPort();
    QGraphicsScene::mouseMoveEvent(event);
}
void GraphBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    UpdateViewPort();
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphBase::UpdateViewPort()
{
    QGraphicsView view = this->views()[0];
    QRect viewPort = view.viewport()->rect();
    QPoint r1, r2;
    r1 = viewPort.topLeft();
    r2 = viewPort.bottomRight();

    update(QRectF(view.mapToScene(r1), view.mapToScene(r2)));
}