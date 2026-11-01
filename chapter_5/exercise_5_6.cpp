/**
 * Exercise 5.6 Error on Simpson's Rule
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include "integration_methods.hpp"

// Forward functon declaration

/**
 * @brief Solves for the function x^4 - 2.0 * x + 1
 * @param x_val the value along the x-axis
 * @return returns a double as result of the calculation
 */
double func(double x_val);

/**
 * @brief Function calculates the error estimation
 * @param integral_val1 The value of the first integration
 * @param integral_val2 The value of the second integration
 * @return the error estimation for a calculated integral
 */
double error_estimation(double integral_val1, double integral_val2);
int main()
{

    const double num_slice1 {10.0};
    const double num_slice2 {20.0};
    const double num_slice3 {1000.0};
    const double lower_bound {0.0};
    const double upper_bound {2.0};

    const double integral_val1 {
        trapezoidal_rule(func, num_slice1, lower_bound, upper_bound)
    };
    const double integral_val2 {
        trapezoidal_rule(func, num_slice2, lower_bound, upper_bound)
    };
    const double accurate_val{
        trapezoidal_rule(func, num_slice3, lower_bound, upper_bound)
    };

    std::cout << "Accurate value with N = 1000: " << accurate_val << '\n';
    std::cout << "Error estimation: "
            << error_estimation(integral_val1, integral_val2) << '\n';

    return 0;
}

// Function definitions

double func(double x_val)
{
    double x_val_raised { x_val * x_val * x_val * x_val };
    return x_val_raised - (2.0 * x_val) + 1.0;
}

double error_estimation(double integral_val1, double integral_val2)
{
    return 0.333 * (std::abs(integral_val2 - integral_val1));
}
