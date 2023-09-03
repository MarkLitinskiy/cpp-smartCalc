#include "model.h"

namespace s21 {

double CalcModel::parserNumber(string::iterator& it) {
  string strNumber(it, it);
  while (whichTypeSym(*it) == TypeSym::number || *it == '.') {
    strNumber += *it;
    ++it;
  }
  --it;
  return stod(strNumber);
}

CalcModel::Operation CalcModel::parserOperator(string::iterator& it) {
  Operation current = Operation::nothing;
  switch (*it) {
    case '+':
      current = parserPlus(it);
      break;
    case '-':
      current = parserMinus(it);
      break;
    case '*':
      current = parserMult();
      break;
    case '/':
      current = parserDiv();
      break;
    case '%':
      current = parserMod();
      break;
    case '^':
      current = parserDeg();
      break;
    case 's':
      current = parserSinSqrt(it);
      break;
    case 'c':
      current = parserCos(it);
      break;
    case 't':
      current = parserTan(it);
      break;
    case 'a':
      current = parserAsinAcosAtan(it);
      break;
    case 'l':
      current = parserLogLn(it);
      break;
    case '(':
      current = parserBrackets(it);
      break;
    case ')':
      current = parserBrackets(it);
      break;
  }
  return current;
}

CalcModel::Operation CalcModel::parserPlus(string::iterator& it) {
  bool isBeginningOfStr = (it == expressionToCalculate.begin());
  bool isPreLeftBracket =
      (it != expressionToCalculate.begin() && (*(it - 1) == '('));
  bool isPreLeftOper =
      (*(it - 1) == '*' || *(it - 1) == '/' || *(it - 1) == '^');

  if (isBeginningOfStr || isPreLeftBracket || isPreLeftOper) {
    return (Operation::unarPlus);
  } else {
    return (Operation::plus);
  }
}

CalcModel::Operation CalcModel::parserMinus(string::iterator& it) {
  bool isBeginningOfStr = (it == expressionToCalculate.begin());
  bool isPreLeftBracket =
      (it != expressionToCalculate.begin() && (*(it - 1) == '('));
  bool isPreLeftOper =
      (*(it - 1) == '*' || *(it - 1) == '/' || *(it - 1) == '^');

  if (isBeginningOfStr || isPreLeftBracket || isPreLeftOper) {
    return (Operation::unarMinus);
  } else {
    return (Operation::minus);
  }
}

CalcModel::Operation CalcModel::parserMult() { return (Operation::mult); }

CalcModel::Operation CalcModel::parserDiv() { return (Operation::div); }

CalcModel::Operation CalcModel::parserMod() { return (Operation::mod); }

CalcModel::Operation CalcModel::parserDeg() { return (Operation::deg); }

CalcModel::Operation CalcModel::parserSinSqrt(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isSin = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 3) == "sin");
  bool isSqrt = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "sqrt");
  Operation result = Operation::nothing;
  if (isNotEnd && isSin) {
    result = (Operation::sin);
    it += 2;
  } else if (isNotEnd && isSqrt) {
    result = (Operation::sqrt);
    it += 3;
  }
  return result;
}

CalcModel::Operation CalcModel::parserCos(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isCos = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 3) == "cos");

  Operation result = Operation::nothing;
  if (isNotEnd && isCos) {
    result = (Operation::cos);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::parserTan(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isTan = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 3) == "tan");

  Operation result = Operation::nothing;
  if (isNotEnd && isTan) {
    result = (Operation::tan);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::parserAsinAcosAtan(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isAsin = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "asin");
  bool isAcos = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "acos");
  bool isAtan = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "atan");

  Operation result = Operation::nothing;
  if (isNotEnd && isAsin) {
    result = (Operation::asin);
    it += 3;
  } else if (isNotEnd && isAcos) {
    result = (Operation::acos);
    it += 3;
  } else if (isNotEnd && isAtan) {
    result = (Operation::atan);
    it += 3;
  }
  return result;
}

CalcModel::Operation CalcModel::parserLogLn(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isLog = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 5) == "log10");
  bool isLn = (expressionToCalculate.substr(
                   distance(expressionToCalculate.begin(), it), 3) == "log");

  Operation result = Operation::nothing;
  if (isNotEnd && isLog) {
    result = (Operation::log);
    it += 4;
  } else if (isNotEnd && isLn) {
    result = (Operation::ln);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::parserBrackets(string::iterator& it) {
  bool isLeftBracket =
      (expressionToCalculate.substr(distance(expressionToCalculate.begin(), it),
                                    1) == "(");
  bool isRightBracket =
      (expressionToCalculate.substr(distance(expressionToCalculate.begin(), it),
                                    1) == ")");

  Operation result = Operation::nothing;
  if (isLeftBracket) {
    result = (Operation::leftBracket);
  } else if (isRightBracket) {
    result = (Operation::rightBracket);
  }
  return result;
}

};  // namespace s21
