/*
 * Exercise 2.3: Converting Cartesian coordinates to polar coordinates
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <string>
#include <tuple>

// Forward function declarations

/** Converts cartesian coordinates to polar coordinates
 *
 * @param x x coordinate
 * @param y y coordinate
 * @return tuple of r and theta
 */
std::tuple<double, double> cart_to_polar(double x, double y);

/** Asks for user input to define the x position and returns a string
 *
 * @return string
 */
std::string get_x_pos();

/** Asks for user input to define the y position and returns a string
 *
 * @return string
 */
std::string get_y_pos();

int main()
{
    std::cout << "Cartesian Coordinate to Polar Coordinate Converter" << '\n';

    // Loop which performs the required actions to define (x,y) and returns
    // values for (r, theta).
    while (true)
    {

        auto inputx{get_x_pos()};
        if (inputx == "q")
        {
            break;
        }

        auto inputy{get_y_pos()};
        if (inputy == "q")
        {
            break;
        }

        try
        {

            // Converts our stings to doubles for the purpose of cart_to_polar(x,y)
            const double x = std::stod(inputx);
            const double y = std::stod(inputy);

            auto [r, theta] = cart_to_polar(x, y);

            std::cout << '\n'
                      << "(r: " << r << ", theta: " << theta << ")" << '\n';
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please enter numeric value" << '\n';
        }
    }
    return 0;
}

std::tuple<double, double> cart_to_polar(double x, double y)
{

    constexpr double pi{std::numbers::pi};

    // Calculates the distance from the origin at point (x,y)
    const double r = std::sqrt((x * x) + (y * y) );

    // Calculates the angle at point (x/y) from the axis and converts to degrees
    const double theta = std::atan(y / x) * (180.0 / pi);

    return std::make_tuple(r, theta);
}

// get_x_pos asks for user input to define the x position and returns a string
std::string get_x_pos()
{

    std::cout << "Enter x: ";
    std::string inputx;
    std::cin >> inputx;
    return inputx;
}
// get_y_pos asks for user input to define the y position and returns a string
std::string get_y_pos()
{

    std::cout << "Enter y: ";
    std::string inputy;
    std::cin >> inputy;
    return inputy;
}
