#ifndef SMARTCALC_VIEW_GRAPHWINDOW_H
#define SMARTCALC_VIEW_GRAPHWINDOW_H

#include <QDialog>
#include <QVector>
#include <vector>

#include "mainwindow.h"
#include "qcustomplot_lib/qcustomplot.h"

namespace Ui {
class graphWindow;
}
namespace s21 {
class graphWindow : public QDialog {
  Q_OBJECT

 public:
  explicit graphWindow(QWidget *parent = nullptr, QString str = "",
                       CalcController *originalController = nullptr,
                       QString X = "");
  ~graphWindow();
  QString *graph;

 private slots:
  void on_pushButton_2_clicked();
  void on_pushButton_clicked();

 private:
  Ui::graphWindow *ui;
  CalcController *controller;  // - контроллер
  double xBegin = 0, xEnd = 0, step = 0, X = 0,
         Y = 0;  // область отображения X, h - шаг между двумя точками, X -
                 // заполнение вектора
  int N = 0;     // кол-во точек
  void reloadSize();
  void printGraph();
  QString expression = "";
  vector<double> x = {0}, y = {0};
  QString xValue = 0;
};

};  // namespace s21

#endif  // SMARTCALC_VIEW_GRAPHWINDOW_H
