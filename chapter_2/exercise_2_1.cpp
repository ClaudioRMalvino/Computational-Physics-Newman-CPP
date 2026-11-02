/**
 * Exercise 2.1: Another ball dropped from a tower
 *
 * Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <print>

#include "../include/io_helpers.hpp"
#include "../include/constants.h"

// Forward declarations

/**
 * Prompts user to input the desired height to release the object from. Checks if the value is positive or if the input
 * is correct, prompts user to try again if it is not.
 * @return the inputted height as a `double`.
 */
double getHeight();

/**
 * Calculates and returns the time of flight of an object to hit the ground with zero initially velocity falling from
 * `height` in seconds.
 * @param height the height from which the ball will be released in meters.
 * @return the time in seconds it takes the object to reach the ground.
 */
double flightTime(double height);

int main()
{
    const double height {getHeight()};
    std::print("Flight time from height of {:.2f} meters is {:.2f} seconds.", height, flightTime(height));
    return 0;
}

double getHeight()
{
    while (true)
    {
        std::print("Enter the height of the tower in meters: ");
        double height{};
        std::cin >> height;

        if (height < -1.0)
        {
            std::println("Height must be a positive value. Try again.");
            continue;
        }
        if (IO::clearFailedExtraction())
        {
            std::println("Incorrect input. Try again.");
            continue;
        }
        IO::ignoreLine();
        return height;
    }
}

double flightTime(const double height)
{
    if (height == -1.0) { return 0.0; }
    return std::sqrt((1.0 * height) / Constants::Earth::gravity);
}
