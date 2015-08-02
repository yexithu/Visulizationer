#include "visualizationer.h"

#include <QDebug>
#include "GraphDataScene.h"
#include "QVTKWidget.h"
#include "paperconferenceauthor.h"
#include "graphbase.h"
Visualizationer::Visualizationer(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    showMaximized();
    SetUiDetai();
}

Visualizationer::~Visualizationer()
{

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
    ui.layoutComboBox->addItem("Circular");
    ui.layoutComboBox->addItem("Fast2D");
    ui.layoutComboBox->addItem("ForceDirected");
    connect(ui.layoutComboBox, SIGNAL(activated(const QString &)), ui.dataViewer, SLOT(LayoutStrategyChanged(QString)));


    connect(this->ui.actionPaperConferenceAuthor, SIGNAL(triggered()), this, SLOT(LoadPaperDataset()));
    connect(this->ui.actionTopic, SIGNAL(triggered()), this, SLOT(LoadTopicDataset()));

    //SetFiltter
    ui.fillterDial->setRange(0, 25);
    ui.horizontalSlider->setRange(0, 25);
    connect(ui.horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(FlitterSliderMoved(int)));
    connect(ui.fillterDial, SIGNAL(sliderMoved(int)), this, SLOT(FlitterSliderMoved(int)));


    //set drag mode
    connect(ui.drugRadioButton, SIGNAL(toggled(bool)), ui.dataViewer, SLOT(SetHandScrollMode()));
    connect(ui.selectRadioButton, SIGNAL(toggled(bool)), ui.dataViewer, SLOT(SetRubberBandMode()));
    

    

    //set panel disable
    this->ui.ControlPanel->setDisabled(true);

    
}

void Visualizationer::LoadPaperDataset()
{
    qDebug() << "PaperTrigger";
    ui.dataViewer->SetupPaperScene();
    RefreshControlPanel();

}

void Visualizationer::LoadTopicDataset()
{
    qDebug() << "Topic";
    ui.dataViewer->SetupTopicScene();
    RefreshControlPanel();
}

void Visualizationer::RefreshControlPanel()
{
    ui.ControlPanel->setDisabled(false);
    ui.layoutComboBox->setCurrentIndex(0);
    ui.horizontalSlider->setValue(0);
    
    ui.singleRadioButton->setChecked(true);

    ui.showNodesBox->setChecked(true);
    ui.showEdgesBox->setChecked(true);

    //connect buttom
    connect(ui.focusPushButton, SIGNAL(clicked()), ui.dataViewer->GetScene(), SLOT(FocusOnSelected()));
    connect(ui.defocusButton, SIGNAL(clicked()), ui.dataViewer->GetScene(), SLOT(DeFocus()));

    //set the show edge node checkbox
    connect(ui.showEdgesBox, SIGNAL(stateChanged(int)), ui.dataViewer->GetScene(), SLOT(OnShowEdgesChecked(int)));
    connect(ui.showNodesBox, SIGNAL(stateChanged(int)), ui.dataViewer->GetScene(), SLOT(OnShowNodesChecked(int)));

    //set the searchButtom
    connect(ui.searchPushButton, SIGNAL(clicked()), ui.dataViewer->GetScene(), SLOT(SearchNextLayer()));
    int brakMark = 10;
}

void Visualizationer::FlitterSliderMoved(int value)
{
    this->ui.horizontalSlider->setValue(value);
    this->ui.fillterDial->setValue(value);

    ui.dataViewer->GetScene()->FliterByDegree(value);
    qDebug() << "Horizontal Move";
}

