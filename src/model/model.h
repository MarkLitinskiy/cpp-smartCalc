#ifndef SMARTCALC_MODEL_CALCMODEL_H
#define SMARTCALC_MODEL_CALCMODEL_H

#include <math.h>

#include <iostream>
#include <stack>
#include <string>

#include "validator_lib/exprtk.hpp"

namespace s21 {

#define PI 3.1415926535897932384626433832795028841971

using namespace std;

class CalcModel {
  typedef exprtk::symbol_table<double> symbol_table_t;
  typedef exprtk::expression<double> expression_t;
  typedef exprtk::parser<double> parser_t;

  enum class Operation {
    kPlus = '+',          // 43
    kMinus = '-',         // 45
    kMult = '*',          // 42
    kDiv = '/',           // 47
    kMod = '%',           // 37
    kDeg = '^',           // 94
    kUnarMinus = '~',     // 126
    kUnarPlus = '@',      // 64
    kSqrt = 'q',          // 113
    kSin = 's',           // 115
    kCos = 'c',           // 99
    kTan = 't',           // 116
    kAsin = 'y',          // 121
    kAcos = 'u',          // 105
    kAtan = 'i',          // 14
    kLog = 'g',           // 103
    kLn = 'n',            // 110
    kLeftBracket = '(',   // 40
    kRightBracket = ')',  // 41

    kNothing = '\0',  // 0
    kError = -1       // -1
  };

  enum class TypeSym { kNumber, kConstant, kExponential, kOperation, kVariable };

 public:
  CalcModel() : expression_str(""){};
  explicit CalcModel(string str);
  string getExpression() const;
  void setExpression(string str);

  /// @brief Вычисляет полученное выражение и записывает результат в
  /// expression_str
  string calculate(string X);

  /// @brief Проверка входящего выражения насинтаксические ошибки
  /// @return true - всё хорошо, false - не хорошо
  bool ValidationExpression(string X, bool isGraf);
  void GraphCalculation(string X, double xBegin, double xEnd, double step,
                        vector<double>& x, vector<double>& y);
  double CreditAnnuitentCalculation(double sumCredit, int monthTerm,
                                    double interestRate, double& overpayment,
                                    double& totalPay) noexcept;
  double CreditDifferentCalculation(double sumCredit, int monthTerm,
                                    int& statePay, double interestRate,
                                    double& overpayment,
                                    double& totalPay) noexcept;
  double DepositCalculation(double sumDeposit, int monthTerm,
                            double interestRate, double nalogRate, int period,
                            int capital, int refillCount, int refill,
                            int withdrawalCount, int withdrawal,
                            double& sumPercent, double& sumNalog) noexcept;

 private:
  stack<double> stackOfNumbers{};  // стек для чисел
  stack<Operation> stackOfSym{};   // стек для операторов
  string expression_str{};  // оригинальное выражение из контроллера
  string expressionToCalculate{};  // выражение, с которым будем работать
  double x{};  // переменная X в выражении

  symbol_table_t symbol_table;  // объекты, необходимые валидатору
  expression_t expression;
  parser_t parser;

  /// @brief Замена X на указанное число
  void InsertX(string X);
  bool MyValidator(string X, bool isGraf);
  string ReformatStr(string str);

  /// @brief Определяет тип символа - число, константа, экспоненциальное
  /// выражение, операция
  /// @param sym текущий символ выражения
  /// @return тип символа в значении перечисления TypeSym
  TypeSym WhichTypeSym(char sym) const;

  /// @brief Парсинг числа из строки
  /// @param it итератор текущего символа в строке выражения
  /// @return найденное число
  double ParserNumber(string::iterator& it);

  /// @brief Главный метод парсинга оператора из строки, вызывает соответсвующий
  /// метод для каждого оператора
  /// @param it итератор текущего символа в строке выражения
  /// @return тип оператора в значении перечисления Operation
  Operation ParserOperator(string::iterator& it);

  // индивидуальные методы под парсинг каждого оператора и сдвиг итератора в
  // строке на соответствующее значение
  Operation ParserPlus(string::iterator& it);
  Operation ParserMinus(string::iterator& it);
  Operation ParserMult();
  Operation ParserDiv();
  Operation ParserMod();
  Operation ParserDeg();
  Operation ParserSinSqrt(string::iterator& it);
  Operation ParserCos(string::iterator& it);
  Operation ParserTan(string::iterator& it);
  Operation ParserAsinAcosAtan(string::iterator& it);
  Operation ParserLogLn(string::iterator& it);
  Operation ParserBrackets(string::iterator& it);

  // методы для вычисления выражения

  void CalculateExponentialNumber(string::iterator& it);

  /// @brief Проводит вычисления в стеках исходя из следующих ситуаций:
  /// 1. Если стек операций пуст/встретилась открывающая скобка;
  /// 2. Приоритет текущей операции <= предыдущей в стеке;
  /// 3. Текущий оператор - звкрывающая скобка;
  void PolshCalculate(Operation current, string::iterator& it);

  /// @brief Приоритет текущей операции <= предыдущей в стеке. Вычисляет
  /// операции в стеке, пока приоритет текущей операции не станет > предыдущей в
  /// стеке
  void CurrentLessOrEqualStack(Operation current, string::iterator& it);
  /// @brief екущий оператор - звкрывающая скобка. Расчёт до тех пор, пока не
  /// найдётся открывающая скобка
  void CurrentIsRightBracket();
  int FindPriority(Operation op);
  void StackUnarOperation(Operation current);
  void StackDoubleOperation(Operation current);
  double ExecuteOperation(double lastNumb, double preLastNumb,
                          Operation current);
};

};  // namespace s21

#endif  // SMARTCALC_MODEL_CALCMODEL_H
