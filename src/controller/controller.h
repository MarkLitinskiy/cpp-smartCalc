#ifndef SMARTCALC_CONTROLLER_CALCCONTROLLER_H
#define SMARTCALC_CONTROLLER_CALCCONTROLLER_H

#include <string>

#include "../model/model.h"

namespace s21 {

class CalcController {
 public:
  CalcController(CalcModel *m) : model(m){};
  string calculate(string expression, string X);
  void GraphCalculate(string expression, double xBegin, double xEnd,
                      double step, vector<double> &x, vector<double> &y,
                      string X);
  double CreditCalculation(bool typeCalculation, double sumCredit,
                           int monthTerm, int &statePay, double interestRate,
                           double &overpayment, double &totalPay);
  double DepositCalculation(double sumDeposit, int monthTerm,
                            double interestRate, double nalogRate, int period,
                            int capital, int refillCount, int refill,
                            int withdrawalCount, int withdrawal,
                            double &sumPercent, double &sumNalog);

 private:
  CalcModel *model;
};

};  // namespace s21

#endif  // SMARTCALC_CONTROLLER_CALCCONTROLLER_H
