#include "model.h"

namespace s21 {

string CalcModel::getExpression() const { return expression_str; }

void CalcModel::setExpression(string str) { expression_str = str; }

CalcModel::CalcModel(string str) { expression_str = str; }

string CalcModel::calculate(string X) {
  double result = 0;
  insertX(X);
  auto it = expressionToCalculate.begin();
  for (; it != expressionToCalculate.end(); ++it) {
    TypeSym currentSym = whichTypeSym(*it);
    if (currentSym == TypeSym::number) {
      stackOfNumbers.push(parserNumber(it));
    } else if (currentSym == TypeSym::operation) {
      polshCalculate(parserOperator(it), it);
    } else if (currentSym == TypeSym::exponential) {
      calculateExponentialNumber(it);
    } else if (currentSym == TypeSym::constant) {
      stackOfNumbers.push(PI);
      ++it;
    }
  }
  while (!stackOfSym.empty()) {  // Если строка закончилась, а в стеке
                                 // операторов ещё есть значения
    polshCalculate(stackOfSym.top(), it);
  }

  result = stackOfNumbers.top();
  while (!stackOfNumbers.empty()) {  // очистка стека с числами
    stackOfNumbers.pop();
  }

  return reformatStr(to_string(result));
}

string CalcModel::reformatStr(string str) {
  if (str[str.size() - 1] == '0') {
    for (size_t i = str.size() - 1; str[i] == '0'; i--) str.erase(i, 1);
  }
  if (str[str.size() - 1] == '.') {
    str.erase(str.size() - 1, 1);
  }
  return str;
}

void CalcModel::insertX(string X) {
  expressionToCalculate = expression_str;
  for (int i = 0; i != (int)expressionToCalculate.size(); ++i) {
    if (expressionToCalculate[i] == 'X') {
      if (X.front() == '-' && (expressionToCalculate[i - 1] == '-' ||
                               expressionToCalculate[i - 1] == '+')) {
        expressionToCalculate.erase(i - 1, 1);
      }
      expressionToCalculate.erase(i, 1);
      expressionToCalculate.insert(i, X);
    }
  }
}

void CalcModel::calculateExponentialNumber(string::iterator& it) {
  double mantiss = 0, count = 0, result = 0;
  ++it;
  if (*it == '-') {
    ++it;
    stackOfNumbers.push(-1 * parserNumber(it));
  } else if (*it == '+') {
    ++it;
    stackOfNumbers.push(parserNumber(it));
  } else {
    stackOfNumbers.push(parserNumber(it));
  }
  count = stackOfNumbers.top();
  stackOfNumbers.pop();
  mantiss = stackOfNumbers.top();
  stackOfNumbers.pop();
  result = mantiss * pow(10, count);
  stackOfNumbers.push(result);
}

CalcModel::TypeSym CalcModel::whichTypeSym(char sym) const {
  if (sym >= 48 && sym <= 57) {
    return TypeSym::number;
  } else if (sym == 'p') {
    return TypeSym::constant;
  } else if (sym == 'E') {
    return TypeSym::exponential;
  } else if (sym == 'X') {
    return TypeSym::variable;
  } else {
    return TypeSym::operation;
  }
}

void CalcModel::graphCalculation(string xValue, double xBegin, double xEnd,
                                 double step, vector<double>& x,
                                 vector<double>& y) {
  double Y = 0;
  if (validationExpression(xValue, true)) {
    for (double X = xBegin; X <= xEnd; X += step) {
      if (X < 0.1 && X > -0.1) {
        X = 0;
      }
      if (xValue == "") {
        Y = stod(calculate(to_string(X)));
      } else {
        Y = stod(calculate(xValue));
      }
      x.push_back(X);
      y.push_back(Y);
    }
    x.erase(
        x.begin());  // удаление самого первого элемента массива, который (0,0)
    y.erase(y.begin());
  }
}

};  // namespace s21
