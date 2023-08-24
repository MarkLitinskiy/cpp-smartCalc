#include "Model.h"

int main() {
  CalcModel ex("(2.1+4.6)/8*(-1)");
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
  for (auto it = expression_str.begin(); it != expression_str.end(); ++it) {
    TypeSym currentSym = whichTypeSym(*it);
    if (currentSym == TypeSym::number) {
      stackOfNumbers.push(parserNumber(it));
    } else if (currentSym == TypeSym::operation) {
      polshCalculate(parserOperator(it));
    } else if (currentSym == TypeSym::exponential) {
      // exponential();
    } else if (currentSym == TypeSym::constant) {
    }
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
    default:
      result = -1;
      break;
  }
  return result;
}

void CalcModel::polshCalculate(Operation current, string::iterator& it) {
  if (stackOfSym.empty() || current == Operation::leftBracket) {
    stackOfSym.push(current);
  } else if ((findPriority(stackOfSym.top()) <= findPriority(current) ||
              (it + 1) == expression_str.end()) &&
             current != Operation::rightBracket) {
    // while (){
    //     if (findPriority((*symStack)->sym) == 4) {
    //         stackUnarOperation(numbersStack, symStack);
    //       } else {
    //         stackDoubleOperation(numbersStack, symStack);
    //       }
    // }
  } else if (current == Operation::rightBracket) {
  }
}