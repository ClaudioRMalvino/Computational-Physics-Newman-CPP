/**
 * @file exercise_2_2.cpp
 * @brief Exercise 2.2: Altitude of a satellite
 *
 * Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <numbers>
#include <print>
#include <string>
#include <unordered_map>
#include <utility>

#include "../../include/io/io_helpers.hpp"
#include "../../include/common/constants.h"

// Forward declarations

/**
 * Extracts user input and converts the user input to the correct value in seconds as a function of
 * user inputted units.
 *
 * Ex. 24 hr -> 86,400 sec
 *
 * @return: returns a std::pair where first = period converted in to seconds, second = the user inputted unit.
 */
std::pair<double, std::string> getOrbitalPeriod();

/**
 * Converts the inputted period into seconds if provided in  units other than `sec`.
 *
 * @param period the user inputted orbital period.
 * @param unit the user inputted unit of time.
 *
 * @return the period converted to units of seconds.
 */
double convertPeriodToSec( const double period, const std::string& unit);

/**
 * Calculates the orbital altitude of a satellite around Earth given a period [s] using
 *
 * @f$ h \;=\; \sqrt[3]{\frac{G M T^{2}}{4\pi^{2}}} - R @f$
 *
 * where,
 *
 * - T: Orbital period
 * - G: Newton's gravitational constant
 * - M: Earth's mass
 * - R: Earth's Radius
 *
 * @param period the orbital period of the object in seconds.
 * @return the orbital altitude of the object in meters.
 */
double calcOrbitalAlt(const double period, const std::string& unit);

namespace Data
{

    std::unordered_map<std::string, int> units = { {"hr", 0}, {"min", 1}, {"sec", 2}  };
}

int main()
{
    const std::pair<double, std::string> usr_input { getOrbitalPeriod() };
    const double altitude { calcOrbitalAlt(usr_input.first, usr_input.second) };
    std::println(
        "The required altitude to maintain a period of {:.2f} {} is {:.3e} m.",
        usr_input.first,
        usr_input.second,
        altitude
    );
    return 0;
}

std::pair<double, std::string> getOrbitalPeriod()
{
    while (true)
    {
        std::print("Enter the desired orbital period in hr, min, sec (ex. 24 hr): ");
        double period{};
        std::string unit{};
        std::cin >> period >> unit;

        if (period < 0.0)
        {
            std::println("Period must be a positive value. Try again.");
            continue;
        }
        if (!Data::units.contains(unit))
        {
            std::println("Unit of time must be 'hr', 'min', or 'sec' (ex. 24 hr). Try again.");
            continue;
        }
        if (IO::clearFailedExtraction())
        {
            std::println("Incorrect input. Try again.");
            continue;
        }
        IO::ignoreLine();
        return std::make_pair(period, unit);

    }
}

double convertPeriodToSec( const double period, const std::string& unit)
{
    switch (Data::units[unit])
    {
    case 0:
        // Convert hr to sec
        return period * 60.0 * 60.0;
    case 1:
        // Converts min to sec
        return period * 60.0;
    default:
        // Keeps as sec if provided as sec
        return period;
    }
}

double calcOrbitalAlt(const double period, const std::string& unit)
{
    using namespace Constants;

    const double conv_period{convertPeriodToSec(period, unit)};

    const double numerator { Astro::newtons_grav * Earth::mass * (conv_period * conv_period) };
    const double denominator { 4.0 * (std::numbers::pi * std::numbers::pi) };
    return std::cbrt(numerator / denominator) - Earth::radius;

}
