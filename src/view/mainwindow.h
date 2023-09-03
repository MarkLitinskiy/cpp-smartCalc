#ifndef SMARTCALC_VIEW_MAINWINDOW_H
#define SMARTCALC_VIEW_MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <string>

#include "controller/controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace s21 {

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(CalcController *c = nullptr, QWidget *parent = nullptr);
  ~MainWindow();
  QString getResultFromController(QString expression, QString X);

 private slots:
  void on_pushButton_Equal_clicked();
  void digits_numbersOperators();
  void constants();
  void clear();

  void on_pushButton_Graph_clicked();

  void on_pushButton_CreditCalc_clicked();

  void on_pushButton_DeposCalc_clicked();

 private:
  Ui::MainWindow *ui;
  CalcController *controller;

  QString expressionView{};
  string expressionModel{};
};

};      // namespace s21
#endif  // SMARTCALC_VIEW_MAINWINDOW_H
