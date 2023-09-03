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
    plus = '+',          // 43
    minus = '-',         // 45
    mult = '*',          // 42
    div = '/',           // 47
    mod = '%',           // 37
    deg = '^',           // 94
    unarMinus = '~',     // 126
    unarPlus = '@',      // 64
    sqrt = 'q',          // 113
    sin = 's',           // 115
    cos = 'c',           // 99
    tan = 't',           // 116
    asin = 'y',          // 121
    acos = 'u',          // 105
    atan = 'i',          // 14
    log = 'g',           // 103
    ln = 'n',            // 110
    leftBracket = '(',   // 40
    rightBracket = ')',  // 41

    nothing = '\0',  // 0
    error = -1       // -1
  };

  enum class TypeSym { number, constant, exponential, operation, variable };

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
  bool validationExpression(string X, bool isGraf);
  void graphCalculation(string X, double xBegin, double xEnd, double step,
                        vector<double>& x, vector<double>& y);
  double creditAnnuitentCalculation(double sumCredit, int monthTerm,
                                    double interestRate, double& overpayment,
                                    double& totalPay) noexcept;
  double creditDifferentCalculation(double sumCredit, int monthTerm,
                                    int& statePay, double interestRate,
                                    double& overpayment,
                                    double& totalPay) noexcept;
  double depositCalculation(double sumDeposit, int monthTerm,
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
  void insertX(string X);
  bool myValidator(string X, bool isGraf);
  string reformatStr(string str);

  /// @brief Определяет тип символа - число, константа, экспоненциальное
  /// выражение, операция
  /// @param sym текущий символ выражения
  /// @return тип символа в значении перечисления TypeSym
  TypeSym whichTypeSym(char sym) const;

  /// @brief Парсинг числа из строки
  /// @param it итератор текущего символа в строке выражения
  /// @return найденное число
  double parserNumber(string::iterator& it);

  /// @brief Главный метод парсинга оператора из строки, вызывает соответсвующий
  /// метод для каждого оператора
  /// @param it итератор текущего символа в строке выражения
  /// @return тип оператора в значении перечисления Operation
  Operation parserOperator(string::iterator& it);

  // индивидуальные методы под парсинг каждого оператора и сдвиг итератора в
  // строке на соответствующее значение
  Operation parserPlus(string::iterator& it);
  Operation parserMinus(string::iterator& it);
  Operation parserMult();
  Operation parserDiv();
  Operation parserMod();
  Operation parserDeg();
  Operation parserSinSqrt(string::iterator& it);
  Operation parserCos(string::iterator& it);
  Operation parserTan(string::iterator& it);
  Operation parserAsinAcosAtan(string::iterator& it);
  Operation parserLogLn(string::iterator& it);
  Operation parserBrackets(string::iterator& it);

  // методы для вычисления выражения

  void calculateExponentialNumber(string::iterator& it);

  /// @brief Проводит вычисления в стеках исходя из следующих ситуаций:
  /// 1. Если стек операций пуст/встретилась открывающая скобка;
  /// 2. Приоритет текущей операции <= предыдущей в стеке;
  /// 3. Текущий оператор - звкрывающая скобка;
  void polshCalculate(Operation current, string::iterator& it);

  /// @brief Приоритет текущей операции <= предыдущей в стеке. Вычисляет
  /// операции в стеке, пока приоритет текущей операции не станет > предыдущей в
  /// стеке
  void currentLessOrEqualStack(Operation current, string::iterator& it);
  /// @brief екущий оператор - звкрывающая скобка. Расчёт до тех пор, пока не
  /// найдётся открывающая скобка
  void currentIsRightBracket();
  int findPriority(Operation op);
  void stackUnarOperation(Operation current);
  void stackDoubleOperation(Operation current);
  double executeOperation(double lastNumb, double preLastNumb,
                          Operation current);
};

};  // namespace s21

#endif  // SMARTCALC_MODEL_CALCMODEL_H
