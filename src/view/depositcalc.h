#ifndef SMARTCALC_VIEW_DEPOSITCALC_H
#define SMARTCALC_VIEW_DEPOSITCALC_H

#include <QDialog>

#include "controller/controller.h"

namespace Ui {
class DepositCalc;
}

namespace s21 {

class DepositCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget *parent = nullptr,
                       CalcController *originalController = nullptr);
  ~DepositCalc();

 private:
  Ui::DepositCalc *ui;
  CalcController *controller;  // - контроллер
  double depositCalc();

  void ResetInputData();
  double sumDeposit = 0;
  int monthTerm = 0;
  double interestRate = 0;
  double nalogRate = 0;
  int period = 0;
  int capital = 0;
  int refillCount = 0;
  int refill = 0;
  int withdrawalCount = 0;
  int withdrawal = 0;
  double sumPercent = 0;
  double sumNalog = 0;
 private slots:
  void on_pushButton_clicked();
};

};  // namespace s21

#endif  // SMARTCALC_VIEW_DEPOSITCALC_H
