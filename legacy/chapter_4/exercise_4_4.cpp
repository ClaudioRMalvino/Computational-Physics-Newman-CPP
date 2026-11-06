/**
 * @file exercise_4_4.cpp
 * @brief Exercise 4.4: Calculating Integrals
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include "../third_party/matplotlibcpp.h"
#include <string>
#include <vector>

// Namespaces

namespace plt = matplotlibcpp;

namespace Constant
{
    constexpr double actual_value { 1.57079632679 };
}

// Forward declarations
/**
 * Function to calculate the integral of the function f(x) = (1 - x^2)^(1/2)
 * @param num_slices number of slices to use in the numerical integration
 *
 * @return integral value
 */
double integral( int num_slices);

/**
 * Function to calculate the error between the numerical and actual value
 * @param numerical numerical value
 * @param actual actual value
 *
 * @return error value
 */
double per_error(double numerical, double actual);

/**
 * Function to prompt user for number of slices
 *
 * @return number of slices
 */
std::string input_num_slices();

/**
 * Function to print the results of the numerical integration
 * @param numerical numerical value
 * @param error error value
 */
void print_results(double numerical, double error);

/**
 * Plots the function f(x) = (1 - x^2)^(1/2) using matplotlib-cpp
 *
 * @param num_slices
 */
void plot_func(double num_slices);

int main()
{
    plt::backend("Agg");

    std::cout << "Calculating Integral of (1 - x^2)^(1/2) from [-1, 1]" << '\n';

    while (true)
    {
        auto input { input_num_slices() };
        if ( input == "q" )
        {
            break;
        }
        const int num_slices { std::stoi(input) };
        if (num_slices <= 0)
        {
            std::cerr << "Invalid input. The number of slices must be > 0"
                        << '\n';
        }
        else
        {
            const double numerical { integral(num_slices) };
            const double error { per_error(numerical, Constant::actual_value) };
            print_results( numerical, error);
            plot_func(num_slices);
        }
    }
    return 0;
}

// Function definitions

double integral( int num_slices )
{
    double h { 2.0 / num_slices };
    double I { 0.0 };
    for ( int i = 0; i < num_slices; ++i )
    {
        double x = -1.0 + (h * i);
        double y = std::sqrt(1 - (x * x) );
        I += h * y;
    }
    return I;
}

double per_error(double numerical, double actual)
{
    return std::abs( ( numerical - actual ) / actual) * 100.0;
}

std::string input_num_slices()
{
    std::cout << "Input 'q' to quit" << '\n';
    std::cout << "Input number of slices: " << '\n';
    std::string input;
    std::cin >> input;
    return input;
}

void print_results(double numerical, double error)
{
    std::cout << std::fixed << std::setprecision(3) << "Results " << '\n';
    std::cout << "-------------------------------------" << '\n';
    std::cout << "Numerical value: " << numerical << '\n';
    std::cout << "Actual value: " << Constant::actual_value << '\n';
    std::cout << "Error: " << error << "%" << '\n';
}

void plot_func(double num_slices)
{
    std::vector<double> x, y;

    for (int i = 0; i < num_slices; ++i)
    {
        double x_val = -1.0 + (2.0 * i / num_slices);
        x.push_back(x_val);
        y.push_back(std::sqrt(1 - x_val * x_val));
    }
    try
    {
        plt::plot(x, y, "b-");
        plt::title("(f(x) = sqrt(1 - x^2)");
        plt::xlabel("x");
        plt::ylabel("y");
        plt::ylim(0.0, 1.5);

        plt::save("../chapter_4/semicircle_plot.png");
        std::cout << "Plot saved as semicircle_plot.png" << '\n';
    } catch (const std::exception &e)
    {
        std::cerr << "Could not create plot: " << e.what() << '\n';
    }

}