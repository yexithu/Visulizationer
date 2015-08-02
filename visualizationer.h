#ifndef VISUALIZATIONER_H
#define VISUALIZATIONER_H
#include "stdafx.h"
#include <vtkSmartPointer.h>

#include <QtWidgets/QMainWindow>
#include <QtWidgets>

#include "ui_visualizationer.h"
#include "dataviewer.h"

class Visualizationer : public QMainWindow
{
    Q_OBJECT

public:
    Visualizationer(QWidget *parent = 0);
    ~Visualizationer();

private:
    Ui::VisualizationerClass ui;
    void SetUiDetai();
    void RefreshControlPanel();

private slots:
    void LoadPaperDataset();
    void LoadTopicDataset();

    void FlitterSliderMoved(int value);
protected:
    void paintEvent(QPaintEvent *pe);
};

#endif // VISUALIZATIONER_H
