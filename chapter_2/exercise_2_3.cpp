
/**
 * Exercise 2.3: Convert two-dimensional Cartesian coordinates to its corresponding polar coordinates.
 *
 * Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <numbers>
#include <print>

#include "../include/io_helpers.hpp"

struct Cartesian
{
    double x{};
    double y{};
};

struct Polar
{
    double r{};
    double theta_degrees{};
};

Cartesian getPos();
Polar calcPolarCoords(const Cartesian xy_coords);

int main()
{
    Cartesian xy_coords = getPos();
    Polar polar_coords = calcPolarCoords(xy_coords);

    std::println(
        "2D Cartesian ({:.3f}, {:.3f}) -> Polar Coordinates ({:.3f}, {:.3f})",
        xy_coords.x,
        xy_coords.y,
        polar_coords.r,
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

        Cartesian coords {x_pos, y_pos};

        return coords;
    }
}

Polar calcPolarCoords(const Cartesian xy_coords)
{
    Polar polar_coords;
    polar_coords.r = std::hypot(xy_coords.x, xy_coords.y);
    polar_coords.theta_degrees = std::atan2( xy_coords.y, xy_coords.x) * (180.0 / std::numbers::pi);
    return polar_coords;
}
