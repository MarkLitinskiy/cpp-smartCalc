#include "graphwindow.h"

#include <iostream>

#include "ui_graphwindow.h"

namespace s21 {

graphWindow::graphWindow(QWidget *parent, QString str,
                         CalcController *originalController, QString X)
    : QDialog(parent),
      ui(new Ui::graphWindow),
      controller(originalController),
      xValue(X) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
  expression = str;
  ReloadSize();
  QString toStr = QString::number(xBegin, 'g', 7);
  PrintGraph();
}

graphWindow::~graphWindow() { delete ui; }

void graphWindow::PrintGraph() {
  controller->GraphCalculate(expression.toStdString(), xBegin, xEnd, step, x, y,
                             xValue.toStdString());

  QVector<double> qX(x.begin(), x.end());
  QVector<double> qY(y.begin(), y.end());
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(qX, qY);
  ui->widget->replot();
}

void graphWindow::on_pushButton_2_clicked() {
  ReloadSize();
  PrintGraph();
}

void graphWindow::ReloadSize() {
  step = ui->doubleSpinBox_step->value();
  xBegin = ui->doubleSpinBox_Xmin->value();
  xEnd = ui->doubleSpinBox_Xmax->value() + step;

  ui->widget->xAxis->setRange(ui->doubleSpinBox_Xmin->value() - 5,
                              ui->doubleSpinBox_Xmax->value() + 5);
  ui->widget->yAxis->setRange(ui->doubleSpinBox_Ymin->value() - 5,
                              ui->doubleSpinBox_Ymax->value() + 5);
  ui->widget->xAxis->setLabel("x");
  ui->widget->yAxis->setLabel("y");
}

void graphWindow::on_pushButton_clicked() { close(); }

};  // namespace s21
