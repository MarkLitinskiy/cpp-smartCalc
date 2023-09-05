#include "model.h"

namespace s21 {

double CalcModel::ParserNumber(string::iterator& it) {
  string strNumber(it, it);
  while (WhichTypeSym(*it) == TypeSym::kNumber || *it == '.') {
    strNumber += *it;
    ++it;
  }
  --it;
  return stod(strNumber);
}

CalcModel::Operation CalcModel::ParserOperator(string::iterator& it) {
  Operation current = Operation::kNothing;
  switch (*it) {
    case '+':
      current = ParserPlus(it);
      break;
    case '-':
      current = ParserMinus(it);
      break;
    case '*':
      current = ParserMult();
      break;
    case '/':
      current = ParserDiv();
      break;
    case '%':
      current = ParserMod();
      break;
    case '^':
      current = ParserDeg();
      break;
    case 's':
      current = ParserSinSqrt(it);
      break;
    case 'c':
      current = ParserCos(it);
      break;
    case 't':
      current = ParserTan(it);
      break;
    case 'a':
      current = ParserAsinAcosAtan(it);
      break;
    case 'l':
      current = ParserLogLn(it);
      break;
    case '(':
      current = ParserBrackets(it);
      break;
    case ')':
      current = ParserBrackets(it);
      break;
  }
  return current;
}

CalcModel::Operation CalcModel::ParserPlus(string::iterator& it) {
  bool isBeginningOfStr = (it == expressionToCalculate.begin());
  bool isPreLeftBracket =
      (it != expressionToCalculate.begin() && (*(it - 1) == '('));
  bool isPreLeftOper =
      (*(it - 1) == '*' || *(it - 1) == '/' || *(it - 1) == '^');

  if (isBeginningOfStr || isPreLeftBracket || isPreLeftOper) {
    return (Operation::kUnarPlus);
  } else {
    return (Operation::kPlus);
  }
}

CalcModel::Operation CalcModel::ParserMinus(string::iterator& it) {
  bool isBeginningOfStr = (it == expressionToCalculate.begin());
  bool isPreLeftBracket =
      (it != expressionToCalculate.begin() && (*(it - 1) == '('));
  bool isPreLeftOper =
      (*(it - 1) == '*' || *(it - 1) == '/' || *(it - 1) == '^');

  if (isBeginningOfStr || isPreLeftBracket || isPreLeftOper) {
    return (Operation::kUnarMinus);
  } else {
    return (Operation::kMinus);
  }
}

CalcModel::Operation CalcModel::ParserMult() { return (Operation::kMult); }

CalcModel::Operation CalcModel::ParserDiv() { return (Operation::kDiv); }

CalcModel::Operation CalcModel::ParserMod() { return (Operation::kMod); }

CalcModel::Operation CalcModel::ParserDeg() { return (Operation::kDeg); }

CalcModel::Operation CalcModel::ParserSinSqrt(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isSin = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 3) == "sin");
  bool isSqrt = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "sqrt");
  Operation result = Operation::kNothing;
  if (isNotEnd && isSin) {
    result = (Operation::kSin);
    it += 2;
  } else if (isNotEnd && isSqrt) {
    result = (Operation::kSqrt);
    it += 3;
  }
  return result;
}

CalcModel::Operation CalcModel::ParserCos(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isCos = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 3) == "cos");

  Operation result = Operation::kNothing;
  if (isNotEnd && isCos) {
    result = (Operation::kCos);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::ParserTan(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isTan = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 3) == "tan");

  Operation result = Operation::kNothing;
  if (isNotEnd && isTan) {
    result = (Operation::kTan);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::ParserAsinAcosAtan(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isAsin = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "asin");
  bool isAcos = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "acos");
  bool isAtan = (expressionToCalculate.substr(
                     distance(expressionToCalculate.begin(), it), 4) == "atan");

  Operation result = Operation::kNothing;
  if (isNotEnd && isAsin) {
    result = (Operation::kAsin);
    it += 3;
  } else if (isNotEnd && isAcos) {
    result = (Operation::kAcos);
    it += 3;
  } else if (isNotEnd && isAtan) {
    result = (Operation::kAtan);
    it += 3;
  }
  return result;
}

CalcModel::Operation CalcModel::ParserLogLn(string::iterator& it) {
  bool isNotEnd = (it != expressionToCalculate.end());
  bool isLog = (expressionToCalculate.substr(
                    distance(expressionToCalculate.begin(), it), 5) == "log10");
  bool isLn = (expressionToCalculate.substr(
                   distance(expressionToCalculate.begin(), it), 3) == "log");

  Operation result = Operation::kNothing;
  if (isNotEnd && isLog) {
    result = (Operation::kLog);
    it += 4;
  } else if (isNotEnd && isLn) {
    result = (Operation::kLn);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::ParserBrackets(string::iterator& it) {
  bool isLeftBracket =
      (expressionToCalculate.substr(distance(expressionToCalculate.begin(), it),
                                    1) == "(");
  bool isRightBracket =
      (expressionToCalculate.substr(distance(expressionToCalculate.begin(), it),
                                    1) == ")");

  Operation result = Operation::kNothing;
  if (isLeftBracket) {
    result = (Operation::kLeftBracket);
  } else if (isRightBracket) {
    result = (Operation::kRightBracket);
  }
  return result;
}

};  // namespace s21
