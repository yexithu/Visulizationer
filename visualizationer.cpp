#include "visualizationer.h"

#include <QDebug>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkGlyph2D.h>
#include <vtkGlyphSource2D.h>
#include <vtkGraphLayout.h>
#include <vtkGraphLayoutView.h>
#include <vtkGraphToPolyData.h>
#include <vtkMutableDirectedGraph.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSimple2DLayoutStrategy.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkForceDirectedLayoutStrategy.h>
#include <vtkRenderWindow.h>
#include <vtkTreeOrbitLayoutStrategy.h>
#include <vtkSimple3DCirclesStrategy.h>
#include <vtkPassThroughLayoutStrategy.h>
#include "vtkCylinderSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkProperty.h"
#include "vtkCamera.h"
#include "datascene.h"
#include "QVTKWidget.h"
#include "paperconferenceauthor.h"

Visualizationer::Visualizationer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    SetUiDetai();
}

Visualizationer::~Visualizationer()
{

}


void Visualizationer::setVTKWidget()
{
        
    // This starts the event loop and as a side effect causes an initial render.
    

    // Exiting from here, we have to delete all the instances that
    // have been created.
}

void Visualizationer::paintEvent(QPaintEvent *pe)
{
    QPainter painter(this);
    QBrush backBlack(QColor(62, 62, 62), Qt::BrushStyle::SolidPattern);
    painter.setBrush(backBlack);

    painter.drawRect(0, 0, width(), height());
}

void Visualizationer::SetUiDetai()
{
    ui.comboBox->addItem("Circular");
    ui.comboBox->addItem("Fast2D");
    ui.comboBox->addItem("ForceDirected");
    connect(ui.comboBox, SIGNAL(activated(const QString &)), ui.dataViewer, SLOT(LayoutStrategyChanged(QString)));


    connect(this->ui.actionPaperConferenceAuthor, SIGNAL(triggered()), this, SLOT(LoadPaperDataset()));
    connect(this->ui.actionTopic, SIGNAL(triggered()), this, SLOT(LoadTopicDataset()));
}

void Visualizationer::LoadPaperDataset()
{
    qDebug() << "PaperTrigger";
    ui.dataViewer->SetupPaperScene();

}

void Visualizationer::LoadTopicDataset()
{
    qDebug() << "Topic";
}

