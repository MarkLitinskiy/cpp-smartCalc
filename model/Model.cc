#include "Model.h"

//int main() {
//  CalcModel ex("4-2E3*2");
//  ex.parserToStack();
//  ex.printStack();
//}

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

void CalcModel::parserToStack() {
  auto it = expression_str.begin();
  for (; it != expression_str.end(); ++it) {
    TypeSym currentSym = whichTypeSym(*it);
    if (currentSym == TypeSym::number) {
      stackOfNumbers.push(parserNumber(it));
    } else if (currentSym == TypeSym::operation) {
      polshCalculate(parserOperator(it), it);
    } else if (currentSym == TypeSym::exponential) {
      calculateExponentialNumber(it);
    } else if (currentSym == TypeSym::constant) {
      stackOfNumbers.push(PI);
    }
  }
  while (!stackOfSym.empty()) {  // Если строка закончилась, а в стеке
                                 // операторов ещё есть значения
    polshCalculate(stackOfSym.top(), it);
  }
}

void CalcModel::calculateExponentialNumber(string::iterator& it) {
  double mantiss = 0, count = 0, result = 0;
  it++;
  stackOfNumbers.push(parserNumber(it));
  count = stackOfNumbers.top();
  stackOfNumbers.pop();
  mantiss = stackOfNumbers.top();
  stackOfNumbers.pop();
  result = mantiss * pow(10, count);
  stackOfNumbers.push(result);
}

CalcModel::TypeSym CalcModel::whichTypeSym(char sym) {
  if (sym >= 48 && sym <= 57) {
    return TypeSym::number;
  } else if (sym == 'P') {
    return TypeSym::constant;
  } else if (sym == 'E') {
    return TypeSym::exponential;
  } else {
    return TypeSym::operation;
  }
}
