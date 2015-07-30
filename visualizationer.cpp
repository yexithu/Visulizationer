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
/*
    PaperConferenceAuthorGraph paperConferenceAuthorGraph;
    dataviewer = new DataViewer;*/
   

    ui.graphicsView->setRenderHint(QPainter::Antialiasing);
    QBrush backGround(QColor(15, 15, 15), Qt::BrushStyle::SolidPattern);
    ui.graphicsView->setBackgroundBrush(backGround);
    ui.graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui.graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //this->resize(QSize(500, 500));
    
    //setVTKWidget();

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