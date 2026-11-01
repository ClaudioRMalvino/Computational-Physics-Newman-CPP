/**
 * Exercise 3.6: Feigenbaum Plot
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <iostream>
#include <print>
#include <ranges>
#include <vector>
#include "../third_party/matplotlibcpp.h"

// Forward function declaration

std::vector<double> logistic_map(double x_0, double r_val, int iterations);

std::vector<std::pair<double, double>> feigenbaum_values(
    double r_min, double r_max, double step_r, double x_0, int iterations);

std::array<double, 5> user_input();

void feigenbaum_plot(
    const std::vector<double> x_data, const std::vector<double> y_data);

int main()
{
    auto [r_min, r_max, step_r, x_0, iterations] = user_input();

    auto zipped_values = feigenbaum_values(
        r_min, r_max, step_r, x_0, iterations);

    std::vector<double> x_vals;
    std::vector<double> r_vals;

    for (std::pair<double,double> pair : zipped_values)
    {
        r_vals.push_back(pair.first);
        x_vals.push_back(pair.second);
    }

    feigenbaum_plot(r_vals, x_vals);
    return 0;
}

// Function definitions

std::vector<double> logistic_map(double x_0, double r_val, int iterations)
{
    std::vector<double> logistics_values(iterations);
    logistics_values[0] = x_0;
    for (int i = 1; i < iterations; i++)
    {
        logistics_values[i] = r_val * logistics_values[i - 1] *
                            (1 - logistics_values[i - 1]);
    }

    return logistics_values;
}

std::vector<std::pair<double, double>> feigenbaum_values(
    double r_min, double r_max, double step_r, double x_0, int iterations)
{
    std::vector<std::vector<double>> x_values;
    std::vector<double> r_values;
    std::vector<std::pair<double, double>> x_pairs;
    for (double i = r_min ; i < r_max; i += step_r)
    {
        r_values.push_back(i);
    }
    for (double i : r_values)
    {
        x_values.push_back(logistic_map(x_0, i, iterations));
        for (auto j : x_values)
        {
            for (auto k : j)

                x_pairs.push_back(std::make_pair(i, k));
        }
        x_values.clear();
    }
    return x_pairs;
}
std::array<double, 5> user_input()
{
    std::array<double, 5> user_values;
    std::cout << "Enter r_min, r_max, step_r, x_0, iterations: ";
    std::cin >> user_values[0] >> user_values[1] >> user_values[2] >> user_values[3] >> user_values[4];
    return user_values;
}

void feigenbaum_plot(
        const std::vector<double> x_data, const std::vector<double> y_data)
{
    namespace plt = matplotlibcpp;
    plt::backend("Agg");

    plt::figure_size(1000, 600);

    // Create a map for plot formatting options
    std::map<std::string, std::string> keywords;
    keywords["color"] = "black";
    keywords["marker"] = ",";
    keywords["linestyle"] = "";  // No line, only markers
    keywords["markersize"] = "0.1";
    keywords["alpha"] = "0.4";

    plt::plot(x_data, y_data, keywords);

    plt::title("Feigenbaum Plot");
    plt::xlabel("r");
    plt::ylabel("x(r)");

    plt::save("../chapter_3/exercise_3_6_feigenbaum_plot.jpeg");
    std::cout << "Plot saved as exercise_3_6_feigenbaum_plot.jpeg" << '\n';
}
