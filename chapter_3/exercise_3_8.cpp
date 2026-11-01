/**
 * @file exercise_3_8 .cpp
 * @brief Exercise 3.8: Least-square fitting and the photoelectric effect
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>
#include "../third_party/matplotlibcpp.h"

// Namespace declerations
namespace plt = matplotlibcpp;
namespace Constants
{
const double planckConst{6.626E-34}; // Planck's constant [J s]
const double electronCharge{1.602E-19}; // Coulomb's constant [C]
}

// Function Declarations
std::pair<std::vector<double>, std::vector<double>> load_data();

double averageXVals(const std::vector<double>& x_vals);

double averageYVals(const std::vector<double>& y_vals);

double averageXValsSqrd(const std::vector<double>& x_vals);

double averageXYVals(
    const std::vector<double>& x_vals,
    const std::vector<double>& y_vals);

double calcSlope(
    double average_x_vals,
    double average_y_vals,
    double average_x_vals_sqrd,
    double average_xy_vals);

double yIntercept(
    double average_x_vals,
    double average_y_vals,
    double average_x_vals_sqrd,
    double average_xy_vals
);

std::vector<double> fitLine(
    double slope,
    double y_intercept,
    const std::vector<double>& x_vals);

double percentError(double experimental, double theoretical);

void plot_data(
    const std::vector<double>& x_data,
    const std::vector<double>& y_data,
    const std::vector<double>& fitted_line);

int main()
{
    const auto [x_data, y_data] = load_data();
    const double average_x_vals {averageXVals(x_data)};
    const double average_y_vals {averageYVals(y_data)};
    const double average_x_vals_sqrd {averageXValsSqrd(x_data)};
    const double average_xy_vals {averageXYVals(x_data, y_data)};
    const double slope {calcSlope(
        average_x_vals,
        average_y_vals,
        average_x_vals_sqrd,
        average_xy_vals)};
    const double y_intercept {yIntercept(
        average_x_vals,
        average_y_vals,
        average_x_vals_sqrd,
        average_xy_vals)};

    const std::vector<double> fitted_line {fitLine(
        slope,
        y_intercept,
        x_data)};
    const double experimental_planck {slope * Constants::electronCharge};

    std::cout << "Experimental Planck's constant: " << experimental_planck << '\n';
    std::cout << "Theoretical Planck's constant: " << Constants::planckConst << '\n';
    std::cout << "Percent error: " << percentError(experimental_planck, Constants::planckConst) << '\n';

    plot_data(x_data, y_data, fitted_line);
    std::cout << "Plot saved as exercise_3_8_plot.svg" << '\n';
    return 0;
}

// Function Definitions
std::pair<std::vector<double>, std::vector<double>> load_data()
{
    std::vector<double> x_data, y_data;
    std::ifstream file("../data/millikan.txt");
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: ../data/millikan.txt");
    }
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty()) {continue;}
        std::istringstream iss(line);
        double x_val, y_val;
        if (iss >> x_val >> y_val) {
            x_data.push_back(x_val);
            y_data.push_back(y_val);
        }
    }
    return make_pair(x_data, y_data);
}

double averageXVals(const std::vector<double>& x_vals)
{
    double sum{0.0};
    for (double x : x_vals)
    {
        sum += x;
    }
    return sum / x_vals.size();
}

double averageYVals(const std::vector<double>& y_vals)
{
    double sum{0.0};
    for (double y : y_vals)
    {
        sum += y;
    }
    return sum / y_vals.size();
}
double averageXValsSqrd(const std::vector<double>& x_vals)
{
    double sum{0.0};
    for (double x : x_vals)
    {
        sum += x * x;
    }
    return sum / x_vals.size();
}
double averageXYVals(
    const std::vector<double>& x_vals,
    const std::vector<double>& y_vals)
{
    double sum{0.0};
    for (int i = 0; i < x_vals.size(); i++)
    {
        sum += x_vals[i] * y_vals[i];
    }
    return sum / x_vals.size();
}

double calcSlope(
    double average_x_vals,
    double average_y_vals,
    double average_x_vals_sqrd,
    double average_xy_vals)
{
    return (average_xy_vals - (average_x_vals * average_y_vals))
    / (average_x_vals_sqrd - (average_x_vals * average_x_vals));
}

double yIntercept(
    double average_x_vals,
    double average_y_vals,
    double average_x_vals_sqrd,
    double average_xy_vals)
{
    return ((average_x_vals_sqrd * average_y_vals) - (average_x_vals * average_xy_vals))
    / (average_x_vals_sqrd - (average_x_vals * average_x_vals));
}

std::vector<double> fitLine(
    double slope,
    double y_intercept,
    const std::vector<double>& x_vals)
{
    std::vector<double> fitted_line;
    for (double x : x_vals)
    {
        double line = (slope * x) + y_intercept;
        fitted_line.push_back(line);
    }
    return fitted_line;
}

double percentError(double experimental, double theoretical)
{
    return (std::abs(experimental - theoretical) / experimental) * 100.0;
}

void plot_data(
    const std::vector<double>& x_data,
    const std::vector<double>& y_data,
    const std::vector<double>& fitted_line)
{
    plt::backend("Agg");
    plt::scatter(x_data, y_data);
    plt::plot(x_data, fitted_line, "r");
    plt::title("Photoelectric Effect");
    plt::xlabel("Frequency (Hz)");
    plt::ylabel("Voltage (V)");
    plt::save("../chapter_3/exercise_3_8_plot.svg");
    std::cout << "Plot saved as exercise_3_8_plot.svg" << '\n';
}






