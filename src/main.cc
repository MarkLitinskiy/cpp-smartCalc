#include <QApplication>

#include "view/mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::CalcModel model;
  s21::CalcController controller(&model);
  s21::MainWindow view(&controller);
  view.show();
  return a.exec();
}
