#ifndef CALCMODEL_H
#define CALCMODEL_H

#include <math.h>

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class CalcModel {
#define PI 3.1415926535897932384626433832795028841971
  // #define E 2.7182818284590452353602874713526624977572

  enum class Operation {
    plus = '+',          // 43
    minus = '-',         // 45
    mult = '*',          // 42
    div = '/',           // 3
    mod = '%',           // 4
    deg = '^',           // 5
    unarMinus = '~',     // 6
    unarPlus = '@',      // 7
    sqrt = 'q',          // 8
    sin = 's',           // 9
    cos = 'c',           // 10
    tan = 't',           // 11
    asin = 'y',          // 12
    acos = 'u',          // 13
    atan = 'i',          // 14
    log = 'g',           // 15
    ln = 'n',            // 16
    leftBracket = '(',   // 40
    rightBracket = ')',  // 41

    nothing = '\0'
  };

  enum class TypeSym { number, constant, exponential, operation };

 public:
  CalcModel() : expression_str(""){};
  CalcModel(string str);

  // private:
  // double x;  // переменная X в выражении
  stack<double> stackOfNumbers;
  stack<Operation> stackOfSym;
  string expression_str;  // принимаемое выражение из контроллера

  TypeSym whichTypeSym(char sym);
  void parserToStack();
  double parserNumber(string::iterator& it);
  Operation parserOperator(string::iterator& it);

  Operation parserPlus(string::iterator& it);
  Operation parserMinus(string::iterator& it);
  Operation parserMult();
  Operation parserDiv();
  Operation parserMod();
  Operation parserDeg();
  Operation parserSinSqrt(string::iterator& it);
  Operation parserCos(string::iterator& it);
  Operation parserTan(string::iterator& it);
  Operation parserAsinAcosAtan(string::iterator& it);
  Operation parserLogLn(string::iterator& it);
  Operation parserBrackets(string::iterator& it);

  void printStack();

  void calculateExponentialNumber(string::iterator& it);
  void polshCalculate(Operation current, string::iterator& it);
  void currentLessOrEqualStack(Operation current, string::iterator& it);
  void currentIsRightBracket();
  int findPriority(Operation op);
  void stackUnarOperation(Operation current);
  void stackDoubleOperation(Operation current);
  double executeOperation(double lastNumb, double preLastNumb,
                          Operation current);

  double s21_fmod(double x, double y);
};

#endif  // CALCMODEL_H
