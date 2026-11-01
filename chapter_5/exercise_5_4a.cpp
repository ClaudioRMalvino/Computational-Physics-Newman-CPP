/**
 * Exercise 5.4 Part a): The diffraction limit of a telescope
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include "../third_party/matplotlibcpp.h"
#include "integration_methods.h"
#include <array>
#include <cmath>
#include <iostream>

#include <vector>

// Namespaces

namespace plt = matplotlibcpp;

// Forward function declarations

/**
 * Function plots the values for bessel_j() from x: [0, 21) and n: [0, 3)
 * @param xs
 * @param values
 */
void plot_bessel_function(std::vector<double> xs, auto values);

int main() {

  std::vector<double> xs, ns;

  for (int i = 0; i < 21; i += 1) {
    xs.push_back(i);
  }
  for (double i = 0; i < 3; i += 1) {
    ns.push_back(i);
  }
  std::array<std::array<double, 21>, 3> values;

  for (int i = 0; i < 3; i += 1) {
    for (int j = 0; j < 21; j += 1) {
      values[i][j] = ext_simpson_rule_bessel_j(static_cast<double>(i),
                                               static_cast<double>(j));
    }
  }
  plot_bessel_function(xs, values);
  return 0;
}

// Function definitions

void plot_bessel_function(std::vector<double> xs, auto values) {
  plt::backend("Agg");
  try {
    plt::title("Bessel Functions $J_{0}(x), J_{1}(x), J_{2}(x)$");
    plt::plot(xs, values[0], "b-", xs, values[1], "r-", xs, values[2], "g-");
    // plt::legend( {"$J_{0}(x)$", "$J_{1}(x)$", "$J_{2}(x)$"} );
    plt::xlabel("x");
    plt::ylabel("J(x)");
    plt::ylim(-1.5, 1.5);
    plt::show();
    plt::save("../chapter_5/exercise_5_4a_plot.png");
    std::cout << "Plot saved as exercise_5_4a_plot.svg" << '\n';
  } catch (const std::exception &e) {
    std::cerr << "Could not create plot: " << e.what() << '\n';
  }
}
