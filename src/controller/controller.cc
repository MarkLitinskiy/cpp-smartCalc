#include "controller.h"

namespace s21 {

string CalcController::calculate(string expression, string X) {
  model->setExpression(expression);
  if (model->ValidationExpression(X, false)) {
    return model->calculate(X);
  } else {
    return model->getExpression();
  }
}

void CalcController::GraphCalculate(string expression, double xBegin,
                                    double xEnd, double step, vector<double> &x,
                                    vector<double> &y, string X) {
  model->setExpression(expression);
  model->GraphCalculation(X, xBegin, xEnd, step, x, y);
}

double CalcController::CreditCalculation(bool typeCalculation, double sumCredit,
                                         int monthTerm, int &statePay,
                                         double interestRate,
                                         double &overpayment,
                                         double &totalPay) {
  if (typeCalculation == true) {
    return model->CreditAnnuitentCalculation(sumCredit, monthTerm, interestRate,
                                             overpayment, totalPay);
  } else {
    return model->CreditDifferentCalculation(
        sumCredit, monthTerm, statePay, interestRate, overpayment, totalPay);
  }
}

double CalcController::DepositCalculation(
    double sumDeposit, int monthTerm, double interestRate, double nalogRate,
    int period, int capital, int refillCount, int refill, int withdrawalCount,
    int withdrawal, double &sumPercent, double &sumNalog) {
  return model->DepositCalculation(
      sumDeposit, monthTerm, interestRate, nalogRate, period, capital,
      refillCount, refill, withdrawalCount, withdrawal, sumPercent, sumNalog);
}

};  // namespace s21
