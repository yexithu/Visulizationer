#include "graphbase.h"
#include "edgebase.h"
#include "nodebase.h"
#include <QTimeLine>
#include <QGraphicsView>
#include <QDebug>

GraphBase::GraphBase(QObject *parent)
    :QGraphicsScene(parent)
{
    
    
}

GraphBase::~GraphBase()
{
    for (NodeBase *node : mNodes)
    {
        delete node;
    }
    for (EdgeBase *edge : mEdges)
    {
        delete edge;
    }
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

int GraphBase::GetHighestDegree()
{
    int result = -1;
    for (NodeBase *node:mNodes)
    {
        if (node->mDegree > result)
        {
            result = node->mDegree;
        }
    }
    return result;
}

void GraphBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //UpdateViewPort();
    QGraphicsScene::mousePressEvent(event);
}
void GraphBase::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //UpdateViewPort();
    QGraphicsScene::mouseMoveEvent(event);
}
void GraphBase::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //UpdateViewPort();
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

void GraphBase::NodePositionChangeFeedBack(NodeBase *node)
{
    for (EdgeBase *edgeBase : node->mConnectedEdges)
    {
        int *index = edgeBase->GetNodeIndex();
        QPointF source = mNodes[index[0]]->scenePos();
        QPointF target = mNodes[index[1]]->scenePos();

        edgeBase->setLine(QLineF(source, target));
    }
}

void GraphBase::NodeSelectedChangeFeedBack(NodeBase *node)
{
    //qDebug() << "Selected Number" << this->selectedItems().size();
    //qDebug() << "Selected FeedBack" << node->mNodeIndex << node->isSelected();
    if (!node->isSelected())
    {
        node->SetSelectedColor();
    }
    else
    {
        node->SetUnselectedColor();
    }
    
    for (EdgeBase *edgeBase : node->mConnectedEdges)
    {
        int *index = edgeBase->GetNodeIndex();
        int other = (index[0] == node->mNodeIndex) ? index[1] : index[0];
        if (mNodes[other]->isSelected() || 
            !mNodes[node->mNodeIndex]->isSelected())
        {
            edgeBase->SetSelectedColor();
        }
        else
        {
            edgeBase->SetUnselectedColor();
        }
    }
}

void GraphBase::NodeVisibleChangeFeedBack(NodeBase *node)
{
    //qDebug() << "VIsible FeedBack" << node->mNodeIndex << node->isVisible();
    for (EdgeBase *edgeBase : node->mConnectedEdges)
    {
        int *index = edgeBase->GetNodeIndex();
        int other = (index[0] == node->mNodeIndex) ? index[1] : index[0];
        //qDebug() << mNodes[node->mNodeIndex]->isSelected() << "  " << mNodes[other]->isSelected();
        if (!mNodes[other]->isVisible() ||
            !mNodes[node->mNodeIndex]->isVisible())
        {
            edgeBase->setVisible(false);
        }
        else
        {
            edgeBase->setVisible(true);
        }
    }
}


void GraphBase::FliterByDegree(int degree)
{
    for (NodeBase * node: mNodes)
    {
        if (node->mDegree < degree)
        {
            if (node->isSelected())
            {
                node->setSelected(false);
            }
        }
        if (node->mDegree >= degree)
        {
            if (!node->isSelected())
            {
                node->setSelected(true);
            }
        }
    }
}

void GraphBase::FindByDegree(int value)
{
    for (NodeBase * node : mNodes)
    {
        if (node->mDegree != value)
        {
            if (node->isSelected())
            {
                node->setSelected(false);
            }
        }
        else
        {
            if (!node->isSelected())
            {
                node->setSelected(true);
            }
        }
    }
}

void GraphBase::FocusOnSelected()
{
    qDebug() << "Focus On Selected";
    for (NodeBase *node : mNodes)
    {
        if (node->isSelected())
        {
            if (!node->isVisible())
            {
                node->setEnabled(true);
                node->setVisible(true);
                NodeVisibleChangeFeedBack(node);
            }
        }
        else
        {
            if (node->isVisible())
            {
                node->setEnabled(false);
                node->setVisible(false);
                NodeVisibleChangeFeedBack(node);
            }
        }
    }
    
}

void GraphBase::DeFocus()
{
    qDebug() << "De Focus";
    for (NodeBase *node : mNodes)
    {
        if (!node->isVisible())
        {
            node->setVisible(true);
            node->setEnabled(true);
            NodeVisibleChangeFeedBack(node);
        }
    }
}


void GraphBase::OnShowNodesChecked(int checkstate)
{
    for (NodeBase *node: mNodes)
    {
        if (checkstate == Qt::Checked)
        {
            this->addItem(node);
        }
        else
        {
            this->removeItem(node);
        }
    }    
}

void GraphBase::OnShowEdgesChecked(int checkstate)
{
    for (EdgeBase *edge : mEdges)
    {
        if (checkstate == Qt::Checked)
        {
            this->addItem(edge);
        }
        else
        {
            this->removeItem(edge);
        }
    }
}

void GraphBase::SearchNextLayer()
{
    for (QGraphicsItem *selectedNode:selectedItems())
    {
        NodeBase * node = qgraphicsitem_cast<NodeBase *>(selectedNode);
        for (EdgeBase *edge: node->mConnectedEdges)
        {
            int *index = edge->GetNodeIndex();
            int other = (index[0] == node->mNodeIndex) ? index[1] : index[0];
            if (!mNodes[other]->isVisible())
            {
                mNodes[other]->setEnabled(true);
                mNodes[other]->setVisible(true);
                NodeVisibleChangeFeedBack(mNodes[other]);
            }
            if (!mNodes[other]->isSelected())
            {
                mNodes[other]->setSelected(true);
            }
        }
    }
}



void GraphBase::UpDateStrategy(QString strategyName)
{

    //存入原来的位置
    this->mAnimationStartPosition.clear();
    for (NodeBase *node : mNodes)
    {
        node->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, false);
        mAnimationStartPosition.push_back(node->scenePos());
    }

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


    UpdateEndPosition(strategyName);
    QTimeLine *animation = new QTimeLine();
    animation->setUpdateInterval(50);
    connect(animation, SIGNAL(valueChanged(qreal)), this, SLOT(OnAnimation(qreal)));
    connect(animation, SIGNAL(finished()), this, SLOT(OnAnimationEnd()));
    
    animation->start();
}





void GraphBase::OnAnimation(qreal value)
{
    
    for (int i = 0; i < mNodeSize; ++i)
    {
        QPointF pos = value *mAnimationEndPosition[i] + (1 - value) * mAnimationStartPosition[i];
        mNodes[i]->setPos(pos);
    }
    for (int i = 0; i < mEdgeSize; ++i)
    {
        int *index = mEdges[i]->GetNodeIndex();
        QPointF source = mNodes[index[0]]->scenePos();
        QPointF target = mNodes[index[1]]->scenePos();

        mEdges[i]->setLine(QLineF(source, target));
    }

}

void GraphBase::OnAnimationEnd()
{
    for (NodeBase *node: mNodes)
    {
        node->setFlag(QGraphicsItem::ItemSendsScenePositionChanges, true);
    }
    mAnimationEndPosition.clear();
    mAnimationStartPosition.clear();
    sender()->~QObject();
}

void GraphBase::SetSingleColorMode()
{
    for (NodeBase *node : mNodes)
    {
        node->SetSingleMode();
    }
    for (EdgeBase *edge :mEdges)
    {
        edge->SetSingleMode();
    }
}

void GraphBase::SetMultiColorMode()
{
    for (NodeBase *node : mNodes)
    {
        node->SetMultiColorMode();
    }
    for (EdgeBase *edge : mEdges)
    {
        edge->SetMultiColorMode();
    }
}


void GraphBase::UpdateEdgeDetailTextView(EdgeBase *edge)
{
    emit UpdateEdgeDetail(edge->toolTip());
}

void GraphBase::UpdateNodeDetailTextView(NodeBase *node)
{
    emit UpdateNodeDetail(node->GetDetail());
}