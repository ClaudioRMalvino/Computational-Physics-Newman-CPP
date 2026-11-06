/**
 * @file exercise_3_3 .cpp
 * @brief Exercise 3.3: Curve Plotting
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include "../third_party/matplotlibcpp.h"

namespace plt = matplotlibcpp;

std::vector<std::vector<double>> load_data_2d(const std::string& filename);
void plot_data(const std::vector<std::vector<double>>& data);

int main()
{
    try {
        auto data = load_data_2d("../data/stm.txt");
        plot_data(data);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}

std::vector<std::vector<double>> load_data_2d(const std::string& filename)
{
    std::vector<std::vector<double>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::vector<double> row;
        std::istringstream iss(line);
        double value;
        
        while (iss >> value) {
            row.push_back(value);
        }
        
        if (!row.empty()) {
            data.push_back(row);
        }
    }
    
    return data;
}

void plot_data(const std::vector<std::vector<double>>& data)
{
    if (data.empty() || data[0].empty()) {
        throw std::runtime_error("Empty data");
    }
    
    int rows = data.size();
    int cols = data[0].size();
    
    // Convert 2D vector to flat array for imshow
    std::vector<float> flat_data;
    flat_data.reserve(rows * cols);
    
    for (const auto& row : data) {
        for (double val : row) {
            flat_data.push_back(static_cast<float>(val));
        }
    }
    
    plt::backend("Agg");
    plt::imshow(flat_data.data(), rows, cols, 1);  // 1 = grayscale
    plt::title("2D Hexagonal Lattice Structure");
    plt::xlabel("x");
    plt::ylabel("y");
    plt::save("../chapter_3/exercise_3_2_plot.svg");
}