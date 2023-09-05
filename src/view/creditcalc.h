#ifndef SMARTCALC_VIEW_CREDITCALC_H
#define SMARTCALC_VIEW_CREDITCALC_H

#include <math.h>

#include <QDialog>

#include "controller/controller.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr,
                      CalcController *originalController = nullptr);
  ~CreditCalc();

 private slots:
  void on_pushButton_result_clicked();

 private:
  Ui::CreditCalc *ui;
  CalcController *controller;  // - контроллер
  void ResetInputData();
  void AnnuitentCalculation();
  void DifferentCalculation();
  double CreditAnnuitentCalculation();
  double CreditDifferentCalculation();
  double sumCredit = 0;
  int monthTerm = 0;
  double interestRate = 0;
  double overpayment = 0;
  double totalPay = 0;
  int statePay = 0;
};

};  // namespace s21

#endif  // SMARTCALC_VIEW_CREDITCALC_H
