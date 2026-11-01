/**
 * Exercise 3.2: Plotting curves
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <format>
#include <numbers>
#include <vector>
#include "../third_party/matplotlibcpp.h"

// Namespace declaration
namespace plt = matplotlibcpp;

//  Constants
constexpr double Pi  = std::numbers::pi;

// Function Declarations
/** Calculates the values of the Deltoid Curve
 *
 * @return
 */
std::pair<std::vector<double>, std::vector<double>> deltoidCurve();

/** Calculates the values of the Galilean Spiral
 *
 * @return
 */
std::pair<std::vector<double>, std::vector<double>> galileanSpiral();

/** Calculates the values of the Feys Function
 *
 * @return
 */
std::pair<std::vector<double>, std::vector<double>> feysFunction();

/** Plots the curves
 *
 * @param func
 * @param titles
 */
void plotFunctions(
        std::array<std::pair<std::vector<double>, std::vector<double>>, 3> func,
        std::array<std::string, 3>&titles);

int main()
{
    const std::array<std::pair<std::vector<double>, std::vector<double>>, 3> functions = {
        deltoidCurve(), galileanSpiral(), feysFunction()
    };
    std::array<std::string, 3> titles = {
        "Deltoid Curve", "Galilean Spiral", "Feys Function"
    };
    plotFunctions(functions, titles);
    return 0;
}

// Function Definitions

std::pair<std::vector<double>, std::vector<double>> deltoidCurve()
{
    std::vector<double> x_data, y_data;
    for (double theta = 0.0; theta < 2.0 * Pi; theta += 0.01)
    {
        x_data.push_back(2.0  * std::cos(theta) + std::cos(2.0 *  theta));
        y_data.push_back(2.0  * std::sin(theta) - std::sin(2.0 *  theta));
    }
    return make_pair(x_data, y_data);
}

std::pair<std::vector<double>, std::vector<double>> galileanSpiral()
{
    std::vector<double> x_data, y_data;
    for (double theta = 0.0; theta < 10.0 * Pi; theta += 0.01)
    {
        x_data.push_back((theta  * theta) * std::cos(theta));
        y_data.push_back((theta  * theta) * std::sin(theta));
    }
    return make_pair(x_data, y_data);
}

std::pair<std::vector<double>, std::vector<double>> feysFunction()
{
    std::vector<double> x_data, y_data;
    for (double theta = 0.0; theta < 24.0 * Pi; theta += 0.01)
    {
        double radius {std::exp(std::cos(theta)) - 2.0 * std::cos(4 * theta) + std::pow(std::sin(theta/12.0), 5)};
        x_data.push_back(radius * cos(theta));
        y_data.push_back(radius * sin(theta));
    }
    return make_pair(x_data, y_data);
}

void plotFunctions(
    std::array<std::pair<std::vector<double>, std::vector<double>>,  3> func,
    std::array<std::string, 3>& titles)
{
    for (int i = 0; i < func.size(); i++)
    {
        plt::backend("Agg");
        plt::plot(func[i].first, func[i].second, "b");
        plt::title(titles[i]);
        plt::xlabel("x");
        plt::ylabel("y");
        plt::save(std::format("../chapter_3/{}.svg", titles[i]));
        std::cout << "Plot saved as " << titles[i] <<".svg" << '\n';
    }

}