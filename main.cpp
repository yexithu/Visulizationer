#include "visualizationer.h"
#include <QtWidgets/QApplication>

#include "paperconferenceauthor.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Visualizationer w;
    w.show();

    return a.exec();
}
