/**
 * Exercise 5.2: Utilizing the Extended Simpson Rule
 *
 * Textbook: Computational Physics by Mark Newman
 */
#include<array>
#include<cmath>
#include <iomanip>
#include "integration_methods.hpp"
#include<iostream>

// Namespaces
namespace Constant
{
    constexpr double actual { 4.4 };
    constexpr double upper_bound { 2.0 };
    constexpr double lower_bound { 0.0 };
    constexpr std::array<double, 3> num_slices = {10.0, 100.0, 1000.0};
}

// Forward declarations


/**
 * Function calculates the percent error between the numerical value and the
 * actual value
 * @param numerical
 * @param actual
 * @return percent error
 */
double per_error(double numerical, double actual);

/**
 * Prints the results of the calculations
 */
void print_results();

int main()
{
    print_results();
    return 0;
}

// Function definitions


double per_error(double numerical, double actual)
{
    return (std::abs(numerical - actual) / actual ) * 100.0;
}

void print_results()
{
    for (double num_slice : Constant::num_slices)
    {
        auto func = [](double x_val) {return std::pow(x_val, 4) - 2*x_val + 1;
        };
        double result = ext_simpson_rule(
            func,
            Constant::lower_bound,
            Constant::upper_bound,
            num_slice);
        double percent_error = per_error(result, Constant::actual);

        std::cout << std::fixed << std::setprecision(5);
        std::cout << "For N = " << num_slice << '\n';
        std::cout << "Result = " << result << '\n';
        std::cout << "Error = " << percent_error << " % " << '\n';
    }

}
