/*
 * Ex_posercise 2.4: Calculating travel time form two different reference frames
 * at relativistic speeds.
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace Constant
{
// Global constant
constexpr double g_c = 299792458.0; // Speed of light [m/s]
}

// Forward function declerations

/**
 * @brief Function calculates the time it takes to travel a distance x at a
 * fraction of the speed of light v*c from Earth reference point
 * @param x_pos_pos the distances travelled [m]
 * @param velocity the speed as a fraction of the speed of light [m/s]
 * @return
 */
double earth_ref_frame(double x_pos_pos, double velocity);

/**
* @brief Function calculates the time it takes to travel a distance x at a
 * fraction of the speed of light v*c from the ship's reference frame
 * @param x_pos_pos the distances travelled [m]
 * @param velocity velocity as a fraction of the speed of light [m/s]
 * @return
 */
double ship_ref_frame(double x_pos_pos, double velocity);

/**
 * @brief Prompts user to input the given velocity
 * @return
 */
std::string get_velocity();

/**
 * @brief Prompts user to input the distance travelled
 * @return
 */
std::string get_distance();

/**
 * @brief
 * @param velocity
 */
void check_velocity(double velocity);
void check_distance(double x_pos_pos);

int main()
{

    std::cout << "Calculating travel time from Earth reference frame and"
              << " passenger reference frame." << '\n'
              << "Input 'q' to quit" << '\n';

    while (true)
    {

        auto input_x_pos{get_distance()};
        if (input_x_pos == "q")
        {
            break;
        }

        auto input_vel{get_velocity()};
        if (input_vel == "q")
        {
            break;
        }

        try
        {
            constexpr double conversion{31556952.};

            const double x_pos= std::stod(input_x_pos);
            const double velocity = std::stod(input_vel);

            check_distance(x_pos);
            check_velocity(velocity);

            const auto earth_frame{earth_ref_frame(x_pos, velocity)
                                            / conversion};
            const auto ship_frame{ship_ref_frame(x_pos, velocity)
                                            / conversion};

            std::cout << '\n'
                      << "Travel time from Earth reference frame: "
                      << std::fixed << std::setprecision(2) << earth_frame
                      << " years" << '\n'
                      << "Travel time from ship reference frame: " << std::fixed
                      << std::setprecision(2) << ship_frame << " years"
                      << '\n';
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please enter numeric value" << '\n';
        }
    }
    return 0;
}

// Function definitions

// Function calculates the time it takes to travel distance x_pos at a fraction
// of the speed of light from Earth reference point.
double earth_ref_frame(double x_pos, double velocity)
{
    const double x_pos_meters{x_pos * 9.460730E+15};
    double beta = velocity * Constant::g_c;
    return x_pos_meters / beta;
}

// Function calculates the proper time from the reference cframe of the
// passenger on the ship traversing a distance x_pos at a velocity a fraction of
// the speed of light.
double ship_ref_frame(double x_pos, double velocity)
{
    const double gamma = 1 / std::sqrt(1 - (velocity * velocity));
    return earth_ref_frame(x_pos, velocity) / gamma;
}

// get_distance asks for user input to define the distance travelled
// in light years and returns a string
std::string get_distance()
{

    std::cout << "Enter distance in lightyears: ";
    std::string inputx_pos;
    std::cin >> inputx_pos;
    return inputx_pos;
}

// get_velocity asks for user input to define the velocity of the spaceship
// and returns a string
std::string get_velocity()
{

    std::cout << '\n'
              << "Enter velocity as a fraction of the speed"
              << " of light (number from (0, 1]) ): ";
    std::string inputv;
    std::cin >> inputv;
    return inputv;
}

void check_velocity(double velocity)
{
    if (velocity <= 0 || velocity > 1)
    {
        throw std::runtime_error("Velocity must be between (0,1]");
    }
}

void check_distance(double x_pos)
{
    if (x_pos < 0)
    {
        throw std::runtime_error("Velocity must be between > 0");
    }
}
