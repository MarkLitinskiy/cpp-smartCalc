#include "Model.h"

int CalcModel::findPriority(Operation op) {
  int result = -1;
  switch (op) {
    case (Operation::plus):
    case (Operation::minus):
      result = 1;
      break;
    case (Operation::mult):
    case (Operation::div):
    case (Operation::mod):
      result = 2;
      break;
    case (Operation::deg):
      result = 3;
      break;
    case (Operation::unarMinus):
    case (Operation::unarPlus):
    case (Operation::sqrt):
    case (Operation::sin):
    case (Operation::cos):
    case (Operation::tan):
    case (Operation::asin):
    case (Operation::acos):
    case (Operation::atan):
    case (Operation::log):
    case (Operation::ln):
      result = 4;
      break;
    case (Operation::leftBracket):
    case (Operation::rightBracket):
      result = 0;
      break;
    default:
      result = -1;
      break;
  }
  return result;
}

void CalcModel::polshCalculate(Operation current, string::iterator& it) {
  if (stackOfSym.empty() || current == Operation::leftBracket) {
    stackOfSym.push(current);
  } else if ((findPriority(current) <= findPriority(stackOfSym.top())) &&
             current != Operation::rightBracket) {
    currentLessOrEqualStack(current, it);

  } else if (current == Operation::rightBracket) {
    currentIsRightBracket();
  } else {
    stackOfSym.push(current);
  }
}

void CalcModel::currentLessOrEqualStack(Operation current,
                                        string::iterator& it) {
  do {
    if (parserOperator(it) == Operation::deg &&
        (stackOfSym.top() == Operation::deg))
      continue;

    if (findPriority(stackOfSym.top()) == 4) {
      stackUnarOperation(stackOfSym.top());
    } else {
      stackDoubleOperation(stackOfSym.top());
    }
  } while (!stackOfSym.empty() &&
           findPriority(current) <= findPriority(stackOfSym.top()) &&
           current != Operation::deg);
  if ((it) != expression_str.end()) stackOfSym.push(current);
}

void CalcModel::currentIsRightBracket() {
  while (stackOfSym.top() != Operation::leftBracket) {
    if (findPriority(stackOfSym.top()) == 4) {
      stackUnarOperation(stackOfSym.top());
    } else {
      stackDoubleOperation(stackOfSym.top());
    }
  }
  stackOfSym.pop();
  if (!stackOfSym.empty() && stackOfSym.top() == Operation::unarMinus) {
    double temp = stackOfNumbers.top() * (-1);
    stackOfNumbers.pop();
    stackOfNumbers.push(temp);
    stackOfSym.pop();
  }
}

void CalcModel::stackUnarOperation(Operation current) {
  double lastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  lastNumber = executeOperation(lastNumber, 0, current);
  stackOfSym.pop();
  stackOfNumbers.push(lastNumber);
}

void CalcModel::stackDoubleOperation(Operation current) {
  double lastNumber = 0, preLastNumber = 0;
  lastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  preLastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  lastNumber = executeOperation(lastNumber, preLastNumber, current);
  stackOfSym.pop();
  stackOfNumbers.push(lastNumber);
}

double CalcModel::executeOperation(double lastNumb, double preLastNumb,
                                   Operation current) {
  double result = 0;

  switch (current) {
    case (Operation::unarMinus):
      result = lastNumb * (-1);
      break;
    case (Operation::unarPlus):
      result = lastNumb;
      break;
    case (Operation::sqrt):
      result = sqrt(lastNumb);
      break;
    case (Operation::sin):
      result = sin(lastNumb);
      break;
    case (Operation::cos):
      result = cos(lastNumb);
      break;
    case (Operation::tan):
      result = tan(lastNumb);
      break;
    case (Operation::asin):
      result = asin(lastNumb);
      break;
    case (Operation::acos):
      result = acos(lastNumb);
      break;
    case (Operation::atan):
      result = atan(lastNumb);
      break;
    case (Operation::log):
      result = log10(lastNumb);
      break;
    case (Operation::ln):
      result = log(lastNumb);
      break;
    case (Operation::plus):
      result = lastNumb + preLastNumb;
      break;
    case (Operation::minus):
      result = preLastNumb - lastNumb;
      break;
    case (Operation::mult):
      result = preLastNumb * lastNumb;
      break;
    case (Operation::div):
      result = preLastNumb / lastNumb;
      break;
    case (Operation::deg):
      result = pow(preLastNumb, lastNumb);
      break;
    case (Operation::mod):
      result = s21_fmod(preLastNumb, lastNumb);
      break;
    case (Operation::nothing):
        result = -1;
      break;
  case (Operation::leftBracket):
      result = -1;
    break;
  case (Operation::rightBracket):
      result = -1;
    break;
  }
  return result;
}

double CalcModel::s21_fmod(double x, double y) {
  double result;

  if (y == 0.0) {
    result = (0.0 / 0.0);
  } else if (y == (1.0 / 0.0) || y == (-1.0 / 0.0)) {
    result = x;
  } else {
    if (x / y < 0) {
      result = x - ceil(x / y) * y;
    } else {
      result = x - floor(x / y) * y;
    }
  }
  return result;
}
