/**
 * Exercise 3.1: Plotting experimental data
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <fstream>
#include <iostream>
#include <ranges>
#include "../third_party/matplotlibcpp.h"
#include <sstream>
#include <vector>

// Namespace declaration
namespace plt = matplotlibcpp;

// Function Declarations

/** Loads data from a file and returns a pair of vectors containing the x and y data
 *
 * @param filename
 * @return pair of vectors containing the x and y data
 */
std::pair<std::vector<double>, std::vector<double>> load_data(const std::string& filename);

/** Calculates the running average of a vector
 *
 * @param window
 * @param y_k
 * @return
 */
std::vector<double> running_avg( int window, const std::vector<double> &y_k);

/** Plots the data
 *
 * @param x_data
 * @param y_data
 * @param y_avg
 */
void plot_data(const std::vector<double> &x_data,
            const std::vector<double> &y_data,
            const std::vector<double> &y_avg);

int main()
{
    const int window {5};
    const auto [x_data, y_data] = load_data("../data/sunspots.txt");
    const auto y_avg = running_avg(window, y_data);
    plot_data(x_data, y_data, y_avg);

    return 0;
}

// Function Definitions

std::pair<std::vector<double>, std::vector<double>> load_data(const std::string& filename)
{
    std::vector<double> x_data, y_data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
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

    return {x_data, y_data};
}

std::vector<double> running_avg( int window, const std::vector<double> &y_k)
{
    std::vector<double> y_avg;
    const double mu {1.0 / (2.0 * window + 1.0)};

    for (int k : std::views::iota(5, static_cast<int>(y_k.size() - 5) ))
    {
        double sum{0.0};
        for (int i : std::views::iota(-window, window + 1))
        {
            sum += y_k[k + i];
        }
        y_avg.push_back(sum * mu);
    }
    return y_avg;
}

void plot_data(const std::vector<double> &x_data,
                const std::vector<double> &y_data,
                const std::vector<double> &y_avg)
{

    plt::backend("Agg");

    const std::vector x_slice_1000(x_data.begin(), x_data.begin() + 1000);
    const std::vector y_slice_1000(y_data.begin(), y_data.begin() + 1000);
    const std::vector x_slice_5_995(x_data.begin() + 5, x_data.begin() + 995);
    const std::vector yavg_slice_5_995(y_avg.begin() + 5, y_avg.begin() + 995);

    plt::plot(x_slice_1000, y_slice_1000);
    plt::plot(x_slice_5_995, yavg_slice_5_995);
    plt::title("Sunspots vs Time");
    plt::xlabel("t, months");
    plt::ylabel("Number of Observed Sunspots");
    plt::save("../chapter_3/exercise_3_1_plot.svg");
    std::cout << "Plot saved as exercise_3_1_plot.svg" << '\n';
}