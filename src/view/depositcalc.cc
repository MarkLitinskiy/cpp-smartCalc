#include "depositcalc.h"

#include "ui_depositcalc.h"

namespace s21 {
DepositCalc::DepositCalc(QWidget *parent, CalcController *originalController)
    : QDialog(parent), ui(new Ui::DepositCalc), controller(originalController) {
  ui->setupUi(this);
  setWindowFlags(
      Qt::Dialog |
      Qt::MSWindowsFixedSizeDialogHint);  // для ограничения расширения окна
  connect(ui->pushButton, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
}

DepositCalc::~DepositCalc() { delete ui; }

void DepositCalc::on_pushButton_clicked() {
  resetInputData();
  if (ui->checkBox_capital->isChecked())  // капитализация
    capital = 1;
  else
    capital = 0;
  ui->lineEdit_sumDepositEnd->setText(
      QString::number(controller->depositCalculation(
          sumDeposit, monthTerm, interestRate, nalogRate, period, capital,
          refillCount, refill, withdrawalCount, withdrawal, sumPercent,
          sumNalog)));
  ui->lineEdit_sumPercent->setText(QString::number(sumPercent));
  ui->lineEdit_sumNalog->setText(QString::number(sumNalog));
}

void DepositCalc::resetInputData() {  // для обновления значений всех
                                      // переменных
  sumDeposit = ui->spinBox_sumDeposit->text().toDouble();
  monthTerm = ui->spinBox_monthTerm->value();
  interestRate = ui->doubleSpinBox_interestRate->value() / 100;
  nalogRate = ui->doubleSpinBox_nalogRate->value() / 100;

  if (ui->comboBox_period->currentIndex() == 0)  // периодичность выплат
    period = 1;
  else if (ui->comboBox_period->currentIndex() == 1)
    period = 3;
  else if (ui->comboBox_period->currentIndex() == 2) {
    period = 0;
  }

  if (ui->comboBox_refill->currentIndex() == 0)  // периодичность пополнений
    refillCount = -1;
  else if (ui->comboBox_refill->currentIndex() == 1)
    refillCount = 1;
  else if (ui->comboBox_refill->currentIndex() == 2)
    refillCount = 3;
  else if (ui->comboBox_refill->currentIndex() == 3)
    refillCount = 6;
  else if (ui->comboBox_refill->currentIndex() == 4)
    refillCount = 12;
  refill = ui->spinBox_refill->value();

  if (ui->comboBox_withdrawal->currentIndex() == 0)  // периодичность снятий
    withdrawalCount = -1;
  else if (ui->comboBox_withdrawal->currentIndex() == 1)
    withdrawalCount = 1;
  else if (ui->comboBox_withdrawal->currentIndex() == 2)
    withdrawalCount = 3;
  else if (ui->comboBox_withdrawal->currentIndex() == 3)
    withdrawalCount = 6;
  else if (ui->comboBox_withdrawal->currentIndex() == 4)
    withdrawalCount = 12;
  withdrawal = ui->spinBox_withdrawal->value();
  sumPercent = 0;
  sumNalog = 0;
}
};  // namespace s21
