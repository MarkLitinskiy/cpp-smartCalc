#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "view/creditcalc.h"
#include "view/depositcalc.h"
#include "view/graphwindow.h"

namespace s21 {

MainWindow::MainWindow(CalcController *c, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), controller(c) {
  ui->setupUi(this);
  QApplication::setWindowIcon(QIcon(":/icon/icon.ico"));  // иконка приложения
  QPixmap pix(":/image2/img2.jpg");
  int w = ui->image->width();
  int h = ui->image->height();
  ui->image->setPixmap(pix.scaled(w, h, Qt::KeepAspectRatio));

  /*Цифры*/
  for (auto it : ui->buttonGroupNumbers->buttons()) {
    connect(it, SIGNAL(clicked()), this, SLOT(digits_numbersOperators()));
  }
  /*Операторы*/
  for (auto it : ui->buttonGroupOperators->buttons()) {
    connect(it, SIGNAL(clicked()), this, SLOT(digits_numbersOperators()));
  }
  /*Константы*/
  connect(ui->pushButton_Pi, SIGNAL(clicked()), this, SLOT(constants()));
  connect(ui->pushButton_Exp, SIGNAL(clicked()), this, SLOT(constants()));
  /*Очистка*/
  connect(ui->pushButton_C, SIGNAL(clicked()), this, SLOT(clear()));
  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(clear()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::digits_numbersOperators() {  // обработка кнопок цифр и
                                              // операторов
  if (ui->lineEdit_Expression->text().left(3) ==
      "ERR") {  // если последняя операция ошибка - стираем строку
    ui->lineEdit_Expression->setText("");
  }
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  expression = ui->lineEdit_Expression->text() + button->text();
  if ((button->text()).length() > 1) {  // Для сложных операторов
    expression += "(";
  }
  ui->lineEdit_Expression->setText(expression);
}

void MainWindow::constants() {  // обработка кнопок-констант
  if (ui->lineEdit_Expression->text().left(3) ==
      "ERR") {  // если последняя операция ошибка - стираем строку
    ui->lineEdit_Expression->setText("");
  }
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  if (button->text() == "E")
    expression = ui->lineEdit_Expression->text() + "E";
  else if (button->text() == "Pi")
    expression = ui->lineEdit_Expression->text() + "pi";

  ui->lineEdit_Expression->setText(expression);
}

void MainWindow::clear() {  // очистка дисплея
  QPushButton *button = (QPushButton *)sender();
  QString expression = "\0";
  expression = ui->lineEdit_Expression->text();
  if (button->text() == "C")
    expression.resize(expression.size() - 1);
  else if (button->text() == "AC")
    expression.clear();
  ui->lineEdit_Expression->setText(expression);
}

QString MainWindow::getResultFromController(QString expression, QString X) {
  string std_expression = expression.toStdString();
  string fromBackEnd = controller->calculate(std_expression, X.toStdString());
  QString answer = QString::fromStdString(fromBackEnd);
  return answer;
}

void MainWindow::on_pushButton_Equal_clicked() {
  //  if (ui->lineEdit_X->text() == "") {
  //    ui->lineEdit_X->setText("0");
  //  }
  ui->lineEdit_Expression->setText(getResultFromController(
      ui->lineEdit_Expression->text(), ui->lineEdit_X->text()));
}

void MainWindow::on_pushButton_Graph_clicked() {
  graphWindow window = graphWindow(nullptr, ui->lineEdit_Expression->text(),
                                   controller, ui->lineEdit_X->text());
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_CreditCalc_clicked() {
  CreditCalc window = CreditCalc(nullptr, controller);
  window.setModal(true);
  window.exec();
}

void MainWindow::on_pushButton_DeposCalc_clicked() {
  DepositCalc window = DepositCalc(nullptr, controller);
  window.setModal(true);
  window.exec();
}

};  // namespace s21
