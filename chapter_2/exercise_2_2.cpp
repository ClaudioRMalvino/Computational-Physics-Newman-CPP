/*
 * Exercise 2.2: Altitude of a satellite
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>

//Global constants
namespace Constant
{
constexpr double g_G{6.67E-11};       // Newton's gravitational constant
constexpr double g_mass{5.97E+24};    // Mass of the earth [kg]
constexpr double g_radius_e{6.37E+6}; // Earth's radius [m]
}

// Function forward decleration

/**
 * Function calculates the orbital height necessary to sustain
 * an orbital period
 *
 * @param period orbital period in seconds
 * @return orbital height in meters
 */
double altitude_of_satellite(double period);

/**
 * Function converts minutes to seconds
 *
 * @param minutes minutes to convert
 * @return seconds
 */
double convert_to_sec(double minutes);

int main()
{

    std::cout << "Input a orbital period in units of minutes: ";

    double minutes{};
    std::cin >> minutes;

    const double period{convert_to_sec(minutes)};

    std::cout << '\n'
              << std::setprecision(3) << "For orbital period of " << minutes
              << " minutes" << '\n'
              << "Required orbital height: " << altitude_of_satellite(period)
              << " m" << '\n';
    return 0;
}



double altitude_of_satellite(double period)
{
    const double numerator{Constant::g_G * Constant::g_mass * (period * period)};
    constexpr double denominator{4.0 * (std::numbers::pi * std::numbers::pi)};

    const double height = std::cbrt((numerator / denominator)) - Constant::g_radius_e;

    return height;
}

double convert_to_sec(double minutes)
{
    const double sec{minutes * 60.0};
    return sec;
}