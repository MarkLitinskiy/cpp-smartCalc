#include "Model.h"

int main() {
  CalcModel ex("1+2*3^sin(0.4)^3*2+1");
  ex.parserToStack();
  ex.printStack();

  // ex.validationExpression();
}

void CalcModel::printStack() {
  printf("Стек чисел:\n");
  while (!stackOfNumbers.empty()) {
    printf("%lf ", stackOfNumbers.top());
    stackOfNumbers.pop();
  }
  printf("\nСтек операторов:\n");
  while (!stackOfSym.empty()) {
    cout << static_cast<int>(stackOfSym.top()) << endl;
    stackOfSym.pop();
  }
}

CalcModel::CalcModel(string str) { expression_str = str; }

// int CalcModel::validationExpression() {
//   symbol_table.add_variable("x", x);
//   symbol_table.add_constants();
//   expression.register_symbol_table(symbol_table);
//   if (!parser.compile(expression_str, expression)) {
//     printf("Compilation ERROR: %s\n", parser.error().c_str());
//     return 1;
//   } else {
//     printf("Compilation Ok!\n");
//     return 0;
//   }
// }

void CalcModel::parserToStack() {
  auto it = expression_str.begin();
  for (; it != expression_str.end(); ++it) {
    TypeSym currentSym = whichTypeSym(*it);
    if (currentSym == TypeSym::number) {
      stackOfNumbers.push(parserNumber(it));
      // if ((it + 1) == expression_str.end())
      //   polshCalculate(stackOfSym.top(), it);
    } else if (currentSym == TypeSym::operation) {
      polshCalculate(parserOperator(it), it);
    } else if (currentSym == TypeSym::exponential) {
      // exponential();
    } else if (currentSym == TypeSym::constant) {
    }
  }
  while (!stackOfSym.empty()) {  // Если строка закончилась, а в стеке
                                 // операторов ещё есть значения
    polshCalculate(stackOfSym.top(), it);
  }
}

// CalcModel::operationConfig CalcModel::fillOperationConfig(Priority prior,
//                                                           Operation oper) {
//   operationConfig op{};
//   op.prior = prior;
//   op.oper = oper;
//   return op;
// }

CalcModel::TypeSym CalcModel::whichTypeSym(char sym) {
  if (sym >= 48 && sym <= 57) {
    return TypeSym::number;
  } else if (sym == 'X' || sym == 'P') {
    return TypeSym::constant;
  } else if (sym == 'E') {
    return TypeSym::exponential;
  } else {
    return TypeSym::operation;
  }
}

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
    // case (Operation::end):
    //   result = 100;
    //   break;
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
    // printf("%d %d %d\n", !stackOfSym.empty(), findPriority(stackOfSym.top()),
    //   findPriority(current));
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
    if ((it) != expression_str.end()) {
      stackOfSym.push(current);
    }
  } else if (current == Operation::rightBracket) {
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
  } else {
    stackOfSym.push(current);
  }
}

void CalcModel::stackUnarOperation(Operation current) {
  double lastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  lastNumber = unarOperation(lastNumber, current);
  stackOfSym.pop();
  stackOfNumbers.push(lastNumber);
}

void CalcModel::stackDoubleOperation(Operation current) {
  double lastNumber = 0, preLastNumber = 0;
  lastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  preLastNumber = stackOfNumbers.top();
  stackOfNumbers.pop();
  lastNumber = doubleOperation(lastNumber, preLastNumber, current);
  stackOfSym.pop();
  stackOfNumbers.push(lastNumber);
}

double CalcModel::unarOperation(double numb, Operation current) {
  double result = 0;

  switch (current) {
    case (Operation::unarMinus):
      result = numb * (-1);
      break;
    case (Operation::unarPlus):
      result = numb;
      break;
    case (Operation::sqrt):
      result = sqrt(numb);
      break;
    case (Operation::sin):
      result = sin(numb);
      break;
    case (Operation::cos):
      result = cos(numb);
      break;
    case (Operation::tan):
      result = tan(numb);
      break;
    case (Operation::asin):
      result = asin(numb);
      break;
    case (Operation::acos):
      result = acos(numb);
      break;
    case (Operation::atan):
      result = atan(numb);
      break;
    case (Operation::log):
      result = log10(numb);
      break;
    case (Operation::ln):
      result = log(numb);
      break;
  }
  return result;
}

double CalcModel::doubleOperation(double lastNumb, double preLastNumb,
                                  Operation current) {
  double result = 0;
  switch (current) {
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