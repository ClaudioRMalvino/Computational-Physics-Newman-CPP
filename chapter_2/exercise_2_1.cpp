/*
Exercise 2.1: Another ball dropped from a tower

Textbook: Computational Physics by Mark Newman
*/

#include <cmath>
#include <iomanip>
#include <iostream>

namespace Constants
{
constexpr double gravity{9.81};
}

int main()
{

    std::cout << "Input height in meters: ";
    double h{}; // height [m]
    std::cin >> h;

    double traveltime { sqrt((2 * h) / Constants::gravity) }; // calculates travel time

    std::cout << "Total travel time: " << std::fixed << std::setprecision(2)
              << traveltime << " s";

    return 0;
}
