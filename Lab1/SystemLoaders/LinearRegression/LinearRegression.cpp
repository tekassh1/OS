#include <iostream>
#include <stdio.h>
#include <vector>
#include <filesystem>

class Regression {

  std::vector<float> x;
  std::vector<float> y;

  float coeff;

  float constTerm;

  float sum_xy;
  float sum_x;
  float sum_y;
  float sum_x_square;
  float sum_y_square;

  float predict(float x) { return coeff * x + constTerm; }

  float errorSquare() {
    float ans = 0;
    for (int i = 0; i < x.size(); i++) {
      ans += ((predict(x[i]) - y[i]) * (predict(x[i]) - y[i]));
    }
    return ans;
  }

  float errorIn(float num) {
    for (int i = 0; i < x.size(); i++) {
      if (num == x[i]) {
        return (y[i] - predict(x[i]));
      }
    }
    return 0;
  }

  void calculateCoefficient() {
    float N = x.size();
    float numerator = (N * sum_xy - sum_x * sum_y);
    float denominator = (N * sum_x_square - sum_x * sum_x);
    if (denominator == 0)
      denominator = 0 + 0.001;
    coeff = numerator / denominator;
  }

  void calculateConstantTerm() {
    float N = x.size();
    float numerator = (sum_y * sum_x_square - sum_x * sum_xy);
    float denominator = (N * sum_x_square - sum_x * sum_x);
    if (denominator == 0)
      denominator = 0 + 0.001;
    constTerm = numerator / denominator;
  }

  int sizeOfData() { return x.size(); }

  float coefficient() {
    if (coeff == 0)
      calculateCoefficient();
    return coeff;
  }

  float constant() {
    if (constTerm == 0)
      calculateConstantTerm();
    return constTerm;
  }

  void calcBestFittingLines() {
    if (coeff == 0 && constTerm == 0) {
      calculateCoefficient();
      calculateConstantTerm();
    }
  }

  void PrintBestFittingLine() {
    if (coeff == 0 && constTerm == 0) {
      calculateCoefficient();
      calculateConstantTerm();
    }
    std::cout << "The best fitting line is y = " << coeff << "x + " << constTerm
              << std::endl;
  }

public:
  Regression()
      : coeff(0), constTerm(0), sum_y(0), sum_y_square(0), sum_x_square(0),
        sum_x(0), sum_xy(0) {}

  void takeInput(int n, std::istream& stream) {
    x.reserve(n);
    y.reserve(n);

    for (int i = 0; i < n; i++) {
      char comma;
      float xi;
      float yi;
      stream >> xi >> comma >> yi;
      sum_xy += xi * yi;
      sum_x += xi;
      sum_y += yi;
      sum_x_square += xi * xi;
      sum_y_square += yi * yi;
      x.push_back(xi);
      y.push_back(yi);
    }
  }

  void showData() {
    for (int i = 0; i < 62; i++) {
      printf("_");
    }
    printf("\n\n");
    printf("|%15s%5s %15s%5s%20s\n", "X", "", "Y", "", "|");

    for (int i = 0; i < x.size(); i++) {
      printf("|%20f %20f%20s\n", x[i], y[i], "|");
    }

    for (int i = 0; i < 62; i++) {
      printf("_");
    }
    printf("\n");
  }

  void run_regression(std::filesystem::path path) {
    freopen(path.c_str(), "r", stdin);

    int n;
    std::cin >> n;

    this->takeInput(n, std::cin);
    this->calcBestFittingLines();
  }
};