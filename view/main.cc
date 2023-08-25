#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcModel model;
    CalcController controller(&model);
    MainWindow view(&controller);
    view.show();
    return a.exec();
}
