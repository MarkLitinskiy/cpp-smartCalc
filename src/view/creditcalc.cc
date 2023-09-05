#include "creditcalc.h"

#include "ui_creditcalc.h"

namespace s21 {

CreditCalc::CreditCalc(QWidget *parent, CalcController *originalController)
    : QDialog(parent), ui(new Ui::CreditCalc), controller(originalController) {
  ui->setupUi(this);
}

CreditCalc::~CreditCalc() { delete ui; }

void CreditCalc::on_pushButton_result_clicked() {
  ResetInputData();
  if (ui->radioButton_annuitent->isChecked()) {  // определение типа
    AnnuitentCalculation();
  }
  if (ui->radioButton_different->isChecked()) {
    DifferentCalculation();
  }
}

void CreditCalc::ResetInputData() {  // для обновления значений всех
                                     // переменных
  sumCredit = ui->spinBox_sumCredit->text().toDouble();
  monthTerm = ui->spinBox_monthTerm->text().toInt();
  interestRate = (ui->doubleSpinBox_interestRate->text().toDouble()) / 100 / 12;
  overpayment = 0;
  totalPay = 0;
  statePay = 0;
}

void CreditCalc::AnnuitentCalculation() {
  ui->tableWidget_monthlyPayment->setRowCount(
      monthTerm);  // задаём параметры таблицы
  ui->tableWidget_monthlyPayment->setColumnCount(1);
  ui->tableWidget_monthlyPayment->setHorizontalHeaderLabels(QStringList()
                                                            << "Сумма выплаты");
  for (int i = 0; i < monthTerm; i++) {  // расчёт ежемесячных выплат
    QTableWidgetItem *tbl = new QTableWidgetItem(QString::number(
        controller->CreditCalculation(true, sumCredit, monthTerm, statePay,
                                      interestRate, overpayment, totalPay),
        'f', 3));
    ui->tableWidget_monthlyPayment->setItem(0, i, tbl);
  }
  ui->lineEdit_overpayment->setText(QString::number(overpayment, 'f', 3));
  ui->lineEdit_totalPay->setText(QString::number(totalPay, 'f', 3));
}

void CreditCalc::DifferentCalculation() {
  statePay = monthTerm - 1;
  ui->tableWidget_monthlyPayment->setRowCount(
      monthTerm);  // задаём параметры таблицы
  ui->tableWidget_monthlyPayment->setColumnCount(1);
  ui->tableWidget_monthlyPayment->setHorizontalHeaderLabels(QStringList()
                                                            << "Сумма выплаты");
  for (int i = monthTerm - 1; i >= 0; i--) {  // расчёт ежемесячных выплат
    QTableWidgetItem *tbl = new QTableWidgetItem(QString::number(
        controller->CreditCalculation(false, sumCredit, monthTerm, statePay,
                                      interestRate, overpayment, totalPay),
        'f', 3));
    ui->tableWidget_monthlyPayment->setItem(0, i, tbl);
  }
  if (monthTerm != 0) overpayment = overpayment - sumCredit;

  ui->lineEdit_overpayment->setText(QString::number(overpayment, 'f', 3));
  ui->lineEdit_totalPay->setText(QString::number(totalPay, 'f', 3));
}

};  // namespace s21
