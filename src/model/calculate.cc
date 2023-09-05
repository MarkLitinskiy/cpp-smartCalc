#include "model.h"

namespace s21 {

int CalcModel::FindPriority(Operation op) {
  int result = -1;
  switch (op) {
    case (Operation::kPlus):
    case (Operation::kMinus):
      result = 1;
      break;
    case (Operation::kMult):
    case (Operation::kDiv):
    case (Operation::kMod):
      result = 2;
      break;
    case (Operation::kDeg):
      result = 3;
      break;
    case (Operation::kUnarMinus):
    case (Operation::kUnarPlus):
    case (Operation::kSqrt):
    case (Operation::kSin):
    case (Operation::kCos):
    case (Operation::kTan):
    case (Operation::kAsin):
    case (Operation::kAcos):
    case (Operation::kAtan):
    case (Operation::kLog):
    case (Operation::kLn):
      result = 4;
      break;
    case (Operation::kLeftBracket):
    case (Operation::kRightBracket):
      result = 0;
      break;
    default:
      result = -1;
      break;
  }
  return result;
}

void CalcModel::PolshCalculate(Operation current, string::iterator& it) {
  if (stackOfSym.empty() || current == Operation::kLeftBracket) {
    stackOfSym.push(current);
  } else if ((FindPriority(current) <= FindPriority(stackOfSym.top())) &&
             current != Operation::kRightBracket) {
    CurrentLessOrEqualStack(current, it);

  } else if (current == Operation::kRightBracket) {
    CurrentIsRightBracket();
  } else {  // если приоритет текущего оператора > последнего в
            // стеке, просто добавляем его в стек
    stackOfSym.push(current);
  }
}

void CalcModel::CurrentLessOrEqualStack(Operation current,
                                        string::iterator& it) {
  do {
    if (ParserOperator(it) == Operation::kDeg &&
        (stackOfSym.top() == Operation::kDeg))
      continue;  // если две степени идут подряд, нужно чтобы вторая не
                 // считалась, а записывалась в стек до момента, пока
                 // степени не закончатся, только затем вынимаем степени по
                 // одной и вычисляем

    if (FindPriority(stackOfSym.top()) == 4) {
      StackUnarOperation(stackOfSym.top());
    } else {
      StackDoubleOperation(stackOfSym.top());
    }
  } while (!stackOfSym.empty() &&
           FindPriority(current) <= FindPriority(stackOfSym.top()) &&
           current !=
               Operation::kDeg);  // повторяем пока приоритет текущего оператора
                                 // <= последнему в стеке, но ^ считаются справа
                                 // налево, поэтому исключение

  if ((it) != expressionToCalculate.end())
    stackOfSym.push(current);  // кладём текущий оператор в стек только
                               // пока строка не закончилась
}

void CalcModel::CurrentIsRightBracket() {
  while (stackOfSym.top() != Operation::kLeftBracket) {
    if (FindPriority(stackOfSym.top()) == 4) {
      StackUnarOperation(stackOfSym.top());
    } else {
      StackDoubleOperation(stackOfSym.top());
    }
  }
  stackOfSym.pop();  // удаление открывающей скобки
  if (!stackOfSym.empty() && stackOfSym.top() == Operation::kUnarMinus) {
    double temp = stackOfNumbers.top() * (-1);  // обработка унарного минуса
    stackOfNumbers.pop();
    stackOfNumbers.push(temp);
    stackOfSym.pop();
  }
}

void CalcModel::StackUnarOperation(Operation current) {
  double lastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  lastNumber = ExecuteOperation(lastNumber, 0, current);
  stackOfSym.pop();
  stackOfNumbers.push(lastNumber);
}

void CalcModel::StackDoubleOperation(Operation current) {
  double lastNumber = 0, preLastNumber = 0;
  lastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  preLastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  lastNumber = ExecuteOperation(lastNumber, preLastNumber, current);
  stackOfSym.pop();
  stackOfNumbers.push(lastNumber);
}

double CalcModel::ExecuteOperation(double lastNumb, double preLastNumb,
                                   Operation current) {
  double result = 0;

  switch (current) {
    case (Operation::kUnarMinus):
      result = lastNumb * (-1);
      break;
    case (Operation::kUnarPlus):
      result = lastNumb;
      break;
    case (Operation::kSqrt):
      result = sqrt(lastNumb);
      break;
    case (Operation::kSin):
      result = sin(lastNumb);
      break;
    case (Operation::kCos):
      result = cos(lastNumb);
      break;
    case (Operation::kTan):
      result = tan(lastNumb);
      break;
    case (Operation::kAsin):
      result = asin(lastNumb);
      break;
    case (Operation::kAcos):
      result = acos(lastNumb);
      break;
    case (Operation::kAtan):
      result = atan(lastNumb);
      break;
    case (Operation::kLog):
      result = log10(lastNumb);
      break;
    case (Operation::kLn):
      result = log(lastNumb);
      break;
    case (Operation::kPlus):
      result = lastNumb + preLastNumb;
      break;
    case (Operation::kMinus):
      result = preLastNumb - lastNumb;
      break;
    case (Operation::kMult):
      result = preLastNumb * lastNumb;
      break;
    case (Operation::kDiv):
      result = preLastNumb / lastNumb;
      break;
    case (Operation::kDeg):
      result = pow(preLastNumb, lastNumb);
      break;
    case (Operation::kMod):
      result = fmod(preLastNumb, lastNumb);
      break;
    case (Operation::kNothing):
      result = -1;
      break;
    case (Operation::kLeftBracket):
      result = -1;
      break;
    case (Operation::kRightBracket):
      result = -1;
      break;
    case (Operation::kError):
      result = -1;
      break;
  }
  return result;
}

}  // namespace s21
