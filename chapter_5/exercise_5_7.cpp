/**
 * Exercise 5.7: Solving for int_{0}^{1} sin^2{sqrt{100x}}dx
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cassert>
#include <cmath>
#include <iostream>
#include "integration_methods.hpp"

// Forward function declarations

/**
 * @brief Function calculates for sin^2(sqrt(100*x))
 * @param x_val
 * @return returns the solution of the function at position x_val
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
    const double lower_limit {0.0};
    const double upper_limit {1.0};
    const double epsilon {1.0e-6};
    double prev_slices {1.0};

    while (true)
    {
        std::cout << "N = " << prev_slices << '\n';
        double next_slices {2.0 * prev_slices};
        double prev_integration {
            trapezoidal_rule(func, prev_slices, lower_limit, upper_limit)
        };
        double next_integration {
            trapezoidal_rule(func, next_slices, lower_limit, upper_limit)
        };
        double error {error_estimation(prev_integration, next_integration)};

        std::cout << "Integral = " << prev_integration << '\n';
        std::cout << "N = " << next_slices << '\n';
        std::cout << "Integral = " << next_integration << '\n';
        std::cout << "Estimated error = " << error << '\n';
        if (error < epsilon)
        {
            break;
        }
        prev_slices = next_slices;
    }
    return 0;
}

double func(double x_val)
{
    assert(x_val >= 0);
    const double argument {std::sqrt(100.0 * x_val)};

    return (std::sin(argument) * std::sin(argument));
}

double error_estimation(double integral_val1, double integral_val2)
{
    return 0.333 * (std::abs(integral_val2 - integral_val1));
}
