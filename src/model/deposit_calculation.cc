#include "model.h"

namespace s21 {

/// @brief Вычисление суммы на вкладе к концу срока работы вклада, суммы налога,
/// начисленных процентов
/// @param sumDeposit начальная сумма вклада
/// @param monthTerm срок размещения вклада в месяцах
/// @param interestRate процентная годовая ставка в в десятичном виде
/// @param nalogRate налоговая ставка, высчитываемая в конце срока вклада
/// @param period периодичность выплат процентов - может быть 1 - раз в месяц, 3
/// - раз в квартал, 0 - в конце срока вклада
/// @param capital капитализация (сложные проценты) 0 - включено, 1 - выключено
/// @param refillCount периодичность пополнений при капитализации (1 - раз в
/// месяц или 3 - раз в квартал)
/// @param refill размер пополнений
/// @param withdrawalCount периодичность снятий средств при капитализации (1 -
/// раз в месяц или 3 - раз в квартал)
/// @param withdrawal размер снимаемых средств
/// @param sumPercent сумма начисленных процентов в конце срока вклада
/// @param sumNalog сумма налога в конце работы вклада
/// @return сумма на вкладе к концу срока
double CalcModel::DepositCalculation(double sumDeposit, int monthTerm,
                                     double interestRate, double nalogRate,
                                     int period, int capital, int refillCount,
                                     int refill, int withdrawalCount,
                                     int withdrawal, double &sumPercent,
                                     double &sumNalog) noexcept {
  double sumDepositEnd = 0;
  if (capital == 0) {  // простые проценты
    sumPercent = (sumDeposit * interestRate * monthTerm / 12);
    sumNalog = nalogRate * sumPercent;
    sumDepositEnd = sumDeposit + sumPercent - sumNalog;
  } else if (capital == 1) {  // сложные проценты (капитализация)
    sumDepositEnd = sumDeposit;
    double currentPercent = 0;
    for (int i = 0, periodCurrent = 0, refillCurrent = 0, withdrawalCurrent = 0;
         i <= monthTerm;
         i++, periodCurrent++, refillCurrent++, withdrawalCurrent++) {
      if (refillCurrent == refillCount) {  // наступило время пополнения
        sumDepositEnd += refill;
        refillCurrent = 0;
      }
      if (withdrawalCurrent == withdrawalCount) {  // наступило время снятия
        sumDepositEnd -= withdrawal;
        withdrawalCurrent = 0;
      }
      if (periodCurrent == period) {  // капитализация процентов
        if (period == 1)
          currentPercent = (sumDepositEnd * interestRate * monthTerm / 12) / 12;
        if (period == 3)
          currentPercent = (sumDepositEnd * interestRate * monthTerm / 4) / 12;
        sumDepositEnd += currentPercent;
        sumPercent += currentPercent;
        periodCurrent = 0;
      }
    }
    sumNalog = nalogRate * sumPercent;
    sumDepositEnd -= sumNalog;
  }
  return sumDepositEnd;
}

};  // namespace s21
