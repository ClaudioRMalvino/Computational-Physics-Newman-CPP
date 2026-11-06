/**
 * @file exercise_2_3.cpp
 * @brief Exercise 2.3: Convert two-dimensional Cartesian coordinates to its corresponding polar coordinates.
 *
 * Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <print>

#include "../../include/common/conversions.h"
#include "../../include/io/io_helpers.hpp"

struct Cartesian
{
    double x{}; ///< Position on the x-axis
    double y{}; ///< Position on the y-axis
};

struct Polar
{
    double radius{}; ///< Radius from the center
    double theta_degrees{}; ///< Angle in degrees
};

/**
 * @brief Requests the user to input an x and y position.
 * @return Cartesian struct with the user defined x and y positions.
 */
Cartesian getPos();

/**
 * @brief Converts 2D Cartesian coordinates into polar coordinates using
 *
 * @f$ r = \sqrt{ x^{2} + y^{2} } @f$
 * \n
 * \n
 * @f$ \theta = \arctan{ y / x } @f$
 *
 * @return Polar coordinates converted from xy_coords.
 */
Polar calcPolarCoords(const Cartesian xy_coords);

int main()
{
    Cartesian xy_coords = getPos();
    Polar polar_coords = calcPolarCoords(xy_coords);

    std::println(
        "2D Cartesian ({:.3f}, {:.3f}) -> Polar Coordinates (r: {:.3f}, theta: {:.3f})",
        xy_coords.x,
        xy_coords.y,
        polar_coords.radius,
        polar_coords.theta_degrees
    );

    return 0;
}

Cartesian getPos()
{
    while (true) {
        double x_pos{}, y_pos{};

        std::print("Input x-position: ");
        std::cin >> x_pos;
        std::println();

        std::print("Input y-position: ");
        std::cin >> y_pos;
        std::println();

        if (IO::clearFailedExtraction())
        {
            std::println("Incorrect input. Try again.");
            continue;
        }
        IO::ignoreLine();

        Cartesian coords{ x_pos, y_pos };
        return coords;
    }
}

Polar calcPolarCoords(const Cartesian xy_coords)
{
    Polar polar_coords;
    polar_coords.radius = std::hypot(xy_coords.x, xy_coords.y);
    polar_coords.theta_degrees = std::atan2( xy_coords.y, xy_coords.x) * Conversions::Length::radian_to_degrees;
    return polar_coords;
}
