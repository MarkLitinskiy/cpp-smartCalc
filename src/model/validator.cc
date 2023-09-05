#include "model.h"

namespace s21 {

bool CalcModel::ValidationExpression(string X, bool isGraf) {
  expressionToCalculate = expression_str;
  symbol_table.add_variable("X", x);
  symbol_table.add_constants();
  expression.register_symbol_table(symbol_table);
  if (!parser.compile(expression_str, expression)) {
    expression_str = parser.error().c_str();
    return false;
  } else if (!MyValidator(X, isGraf)) {
    return false;
  }
  return true;
}

bool CalcModel::MyValidator(string X, bool isGraf) {
  vector<Operation> operations{Operation::kNothing};
  for (auto it = expressionToCalculate.begin();
       it < expressionToCalculate.end(); ++it) {
    if (*it == '/' && *(it + 1) == '/') {
      expression_str = "ERR: Два оператора деления!";
      return false;
    } else if (*it == '+' && *(it + 1) == '+') {
      expression_str = "ERR: Два оператора суммы!";
      return false;
    } else if (*it == '-' && *(it + 1) == '-') {
      expression_str = "ERR: Два оператора разности!";
      return false;
    } else if (((*it < 48 || *it > 57) && *(it + 1) == '.') ||
               (it == expressionToCalculate.begin() && *it == '.')) {
      expression_str = "ERR: Некорректная дробь!";
      return false;
    } else if (*it == 'x') {
      expression_str = "ERR: Неопознанный символ!";
      return false;
    } else if (*it == ' ') {
      expression_str = "ERR: Вводите выражение без пробелов!";
      return false;
    } else if (*it == 'X' && X == "" && isGraf == false) {
      expression_str = "ERR: X не задан!";
      return false;
    }
  }
  return true;
}

};  // namespace s21
