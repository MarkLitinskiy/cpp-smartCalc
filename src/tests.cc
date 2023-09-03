#include <gtest/gtest.h>

#include <cmath>
#include <iostream>

#include "model/Model.h"

#define EPS 1e-4

using namespace std;

s21::CalcModel example;

TEST(Calc, Exp1) {
  string src = "4^acos(1.2/4)/tan(2*1.2)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = -6.31492;
  EXPECT_TRUE(fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp2) {
  string src = "2+2";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 4;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp3) {
  string src = "123+0.456";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 123.456;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp4) {
  string src = "log10(-2)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = NAN;
  EXPECT_TRUE(std::isnan(res) && std::isnan(real_result));
}

TEST(Calc, Exp5) {
  string src = "-(-1)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 1;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp6) {
  string src = "cos(10%2.2)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 0.362358;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp7) {
  string src = "sqrt(log(10))";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 1.517427;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp8) {
  string src = "atan(10)+sin(10)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 0.92710;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp9) {
  string src = "asin(1)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 1.570796;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp10) {
  string src = "10-20*(-10)";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 210;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp14) {
  string src = "2^3^2";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 512.0;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Exp15) {
  string src = "4E3";
  example.setExpression(src);
  EXPECT_TRUE(example.validationExpression("0", false));
  double res = stod(example.calculate("0"));
  double real_result = 4000.0;
  EXPECT_TRUE(std::fabs(res - real_result) <= EPS);
}

TEST(Calc, Graphic) {
  string src = "10*X+4";
  vector<double> x;
  vector<double> y;
  example.setExpression(src);
  example.graphCalculation("", -10, 10, 0.1, x, y);

  EXPECT_TRUE(std::fabs(y.back() - 104) <= EPS);
  EXPECT_TRUE(std::fabs(x.back() - 10) <= EPS);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
