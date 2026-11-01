#ifndef INTEGRATION_METHODS_HPP
#define INTEGRATION_METHODS_HPP

#include <cmath>
#include <numbers>

// Namespace decleration

namespace Constant
{
    const double pi {3.14159};
}

/**
 * @brief Function template utilizes the trapezoidal rule to integrate a function
 * over an upper and lower bound of integration, with an accuracy dependent on
 * the number of slices.
 * @tparam Func
 * @param func  A function definition which represents the integrand
 * @param num_slices The number of slices with which to perform the integration,
 * the larger num_slices is the greater the accuracy
 * @param lower_bound The lower bounds of integration
 * @param upper_bound The upper bound of integration
 * @return double: result of integration along the lower and upper bounds
 */
template<typename Func>
double trapezoidal_rule(Func func, int num_slices, double lower_bound, double upper_bound)
{
    const double step_h {(upper_bound - lower_bound) / num_slices};
    double init_val {0.5*func(lower_bound) + 0.5*func(upper_bound)};

    for (int k = 1; k < num_slices; k++)
    {
        init_val += func(lower_bound + k * step_h);
    }

    return step_h * init_val;
}

/**
 * @brief This function template holds methods of integration via the
 * extended simpson's rule
 * @tparam Func
 * @param func Pass a function into the template to integrate
 * @param lower_bound The lower bound of integration
 * @param upper_bound The upper bound of integration
 * @param num_slices The number of lsices for integration, as num_slices grows,
 * so too does the accuracy
 * @return returns the result of integration
 */
template<typename Func>
double ext_simpson_rule(Func func, double lower_bound, double upper_bound, int num_slices) {
    const double width = (upper_bound - lower_bound) / num_slices;
    const double constant = width / 3.0;
    
    double integral = constant * (func(lower_bound) + func(upper_bound));
    double odds = 0.0;
    double evens = 0.0;
    
    for (int i = 1; i < num_slices; i += 2) {
        odds += func(lower_bound + (i * width));
    }
    for (int i = 2; i < num_slices; i += 2) {
        evens += func(lower_bound + (i * width));
    }
    
    integral += constant * (4 * odds + 2 * evens);
    return integral;
}

/**
 * @brief Calculates for the Bessel function of the first kind in trigonometric
 * representation
 * @param order the order of the function
 * @param x_val the value along the x_axis
 * @param theta the angle
 * @return returns the value of the Bessel function of the first kind
 */
inline double bessel_j(double order, double x_val, double theta) {
    return std::cos(order * theta - x_val * std::sin(theta));
}


inline double integrate_bessel_j(double order, double x_val) {
    auto bessel_func = [order, x_val](double theta) {
        return bessel_j(order, x_val, theta);
    };
    
    const double coeff = 1.0 / Constant::pi;
    const int num_slices = 7000;
    const double result = ext_simpson_rule(
        bessel_func, 0.0, Constant::pi, num_slices);
    
    return coeff * result;
}

#endif