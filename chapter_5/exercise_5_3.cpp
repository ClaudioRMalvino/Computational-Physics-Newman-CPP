/**
 * Exercise 5.3: Integrating \int{0}^{x} e^{-t^{2}} dt
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <iomanip>
#include "../third_party/matplotlibcpp.h"
#include <stdexcept>
#include <string>
#include <tuple>

// Namespaces

namespace plt = matplotlibcpp;

// Forward function declarations

/**
 * Calculates f(x) = e^{-t^{2}}
 * @param val
 * @return
 */
double func(double val);

/**
 * Function calculates an integral utilizing the Extended Simpson Rule from
 * [0, upper_bound]
 * @param upper_bound Upper limit of integrations
 * @param num_slices  Number of slices
 * @param width Width of steps
 * @return The area under the function
 */
double extSimpsonRule(
                        double upper_bound,
                        double num_slices,
                        double width);
/**
 * Function prompts user to input values for the width of step, the number
 * of slices, and the upper limit of integration.
 * Will also perform value checks to catch input errors.
 * @return a vector of three string elements
 */
std::tuple<double, double, double> inputPromptsAndConversion();

/**
 *
 * @param result
 * @param upper_limit
 * @param num_slices
 */
void printResults( double result, double upper_limit, double num_slices);

/**
 * Function checks for the validity of the user inputs
 * @param upper_limit
 * @param num_slices
 * @param width
 *
 */
void valueChecks(double upper_limit, double num_slices, double width);

/** Plots the function f(x) = e^{-t^{2}} using matplotlib-cpp
 *
 * @param upper_limit
 */
void plot_func(double upper_limit);

int main()
{
    while (true)
    {
        auto [upper_limit,
            width,
            num_slices ] = inputPromptsAndConversion();

        try
        {
            valueChecks(upper_limit,num_slices, width);
            double result { extSimpsonRule(
                upper_limit,
                num_slices,
                width
                ) };

            printResults(result, upper_limit, num_slices);
            plot_func(upper_limit);

        } catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please try again." << '\n';
        }
    }

    return 0;
}

// Function definitions

double func(double val)
{
    return std::exp(- (val * val));
}

double extSimpsonRule(
    double upper_bound,
    double num_slices,
    double width)
{
    double constant = width / 3.0;
    double integral = constant * (func(upper_bound) + func(0.0));
    double odds { 0.0 };
    double evens { 0.0 };

    for (int i = 1; i < num_slices; i += 2)
    {
        odds += func(i*width);
    }
    for (int i = 2; i < num_slices; i += 2)
    {
        evens += func(i*width);
    }
    integral += constant * (4*odds + 2*evens);
    return integral;
}

std::tuple<double, double, double> inputPromptsAndConversion()
{

    std::cout << "Enter 'q' to quit." << '\n';

    std::cout << " Enter upper limit of integration: ";
    std::string upper_limit_input;
    std::cin >> upper_limit_input;

    if (upper_limit_input == "q")
    {
        std::exit(0);
    }
    double upper_limit { std::stod(upper_limit_input) };

    std::cout << " Enter width of steps: ";
    std::string width_input;
    std::cin >> width_input;
    if (width_input == "q")
    {
        std::exit(0);
    }
    double width { std::stod(width_input) };

    std::cout << " Enter number of slices: ";
    std::string slices_input;
    std::cin >> slices_input;
    if (slices_input == "q")
    {
        std::exit(0);
    }
    double slices { std::stod(slices_input) };

    return std::make_tuple(upper_limit, width, slices);
}

void printResults(double result, double upper_limit, double num_slices)
{
    std::cout << "Result of integrating e^{-t^{2}}dt from [0, "
            << upper_limit << "] with " << num_slices << " slices: " << result
            << '\n';
}

void valueChecks(double upper_limit, double width, double num_slices)
{
    if (upper_limit <= 0.0  || width <= 0.0 || num_slices <= 0.0)
    {
        throw std::runtime_error("All parameters must be > 0");
    }
}

void plot_func(double upper_limit)
{

    plt::backend("Agg");
    std::vector<double> xs, ys;
    const double start {0.0};
    double end { upper_limit };
    const int num_points { 1000 };

    for (int i = 0; i < num_points; ++i)
    {
        double value = start + ((end - start) * i / (num_points -1));
        xs.push_back(value);
        ys.push_back(std::exp(- (value * value)));
    }
    try
    {
        plt::plot(xs, ys, "b-");
        plt::title("(f(x) = e^{-x^{2}})");
        plt::xlabel("x");
        plt::ylabel("y");
        plt::ylim(0.0, 1.5);

        plt::save("../chapter_5/exercise_5_3_plot.png");
        std::cout << "Plot saved as exercise_5_3_plot.png" << '\n';
    } catch (const std::exception &e)
    {
        std::cerr << "Could not create plot: " << e.what() << '\n';
    }
}


