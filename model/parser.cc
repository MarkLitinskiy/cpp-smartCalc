#include "Model.h"

double CalcModel::parserNumber(string::iterator& it) {
  string strNumber(it, it);
  while (whichTypeSym(*it) == TypeSym::number || *it == '.') {
    strNumber += *it;
    ++it;
  }
  --it;
  return stod(strNumber);
  // double number = 0;
  // int move = 0;
  // sscanf(expression_str, "%lf%n", number, move);
  // return number;
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
    // case '\0':
    //   current = nothing;
    //   break;
    default:
      // expression_str = "ERROR!!!";
      break;
  }
  return current;
}

CalcModel::Operation CalcModel::parserPlus(string::iterator& it) {
  bool isBeginningOfStr = (it == expression_str.begin());
  bool isPreLeftBracket = (it != expression_str.begin() && (*(it - 1) == '('));

  if (isBeginningOfStr || isPreLeftBracket) {
    return (Operation::unarPlus);
  } else {
    return (Operation::plus);
  }
  // it += 1;
}

CalcModel::Operation CalcModel::parserMinus(string::iterator& it) {
  bool isBeginningOfStr = (it == expression_str.begin());
  bool isPreLeftBracket = (it != expression_str.begin() && (*(it - 1) == '('));

  if (isBeginningOfStr || isPreLeftBracket) {
    return (Operation::unarMinus);
  } else {
    return (Operation::minus);
  }
  // it += 1;
}

CalcModel::Operation CalcModel::parserMult() {
  return (Operation::mult);
  // it += 1;
}

CalcModel::Operation CalcModel::parserDiv() {
  return (Operation::div);
  // it += 1;
}

CalcModel::Operation CalcModel::parserMod() {
  return (Operation::mod);
  // it += 1;  // зависит от оператора мод
}

CalcModel::Operation CalcModel::parserDeg() {
  return (Operation::deg);
  // it += 1;
}

CalcModel::Operation CalcModel::parserSinSqrt(string::iterator& it) {
  bool isNotEnd = (it != expression_str.end());
  bool isSin =
      (expression_str.substr(distance(expression_str.begin(), it), 3) == "sin");
  bool isSqrt = (expression_str.substr(distance(expression_str.begin(), it),
                                       4) == "sqrt");
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
  bool isNotEnd = (it != expression_str.end());
  bool isCos =
      (expression_str.substr(distance(expression_str.begin(), it), 3) == "cos");

  Operation result = Operation::nothing;
  if (isNotEnd && isCos) {
    result = (Operation::cos);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::parserTan(string::iterator& it) {
  bool isNotEnd = (it != expression_str.end());
  bool isTan =
      (expression_str.substr(distance(expression_str.begin(), it), 3) == "tan");

  Operation result = Operation::nothing;
  if (isNotEnd && isTan) {
    result = (Operation::tan);
    it += 2;
  }
  return result;
}

CalcModel::Operation CalcModel::parserAsinAcosAtan(string::iterator& it) {
  bool isNotEnd = (it != expression_str.end());
  bool isAsin = (expression_str.substr(distance(expression_str.begin(), it),
                                       4) == "asin");
  bool isAcos = (expression_str.substr(distance(expression_str.begin(), it),
                                       4) == "acos");
  bool isAtan = (expression_str.substr(distance(expression_str.begin(), it),
                                       4) == "atan");

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
  bool isNotEnd = (it != expression_str.end());
  bool isLog =
      (expression_str.substr(distance(expression_str.begin(), it), 3) == "log");
  bool isLn =
      (expression_str.substr(distance(expression_str.begin(), it), 2) == "ln");

  Operation result = Operation::nothing;
  if (isNotEnd && isLog) {
    result = (Operation::log);
    it += 2;
  } else if (isNotEnd && isLn) {
    result = (Operation::ln);
    it += 1;
  }
  return result;
}

CalcModel::Operation CalcModel::parserBrackets(string::iterator& it) {
  bool isLeftBracket =
      (expression_str.substr(distance(expression_str.begin(), it), 1) == "(");
  bool isRightBracket =
      (expression_str.substr(distance(expression_str.begin(), it), 1) == ")");

  Operation result = Operation::nothing;
  if (isLeftBracket) {
    result = (Operation::leftBracket);
    // it += 1;
  } else if (isRightBracket) {
    result = (Operation::rightBracket);
    // it += 1;
  }
  return result;
}
