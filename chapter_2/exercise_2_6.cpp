/*
 * Exercise 2.6: Planetary Orbit
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <numbers>
#include <string>
#include <vector>

namespace Constant
{
// Global constants
constexpr double g_sunMass{1.9891E+30}; // Mass of the sun
constexpr double g_G{6.6738E-11}; // Newton's gravitational constant
constexpr double g_pi{std::numbers::pi}; // Pi
}

// Function declarations

/** Calculates the velocity at aphelion (v2) and distance from the Sun at
 * aphelion (l2) for a given perihelion velocity (v1) and perihelion distance
 * (l1).
 *
 * @param v1 perihelion velocity
 * @param l1 perihelion distance
 * @return tuple of v2 and l2
 */
double v2(double v1, double l1);

/** Calculates the distance from the Sun at aphelion (l2) for a given
 * perihelion velocity (v1) and perihelion distance (l1) and velocity at
 * aphelion (v2).
 *
 * @param v1 perihelion velocity
 * @param l1 perihelion distance
 * @param v2 velocity at aphelion
 * @return l2
 */
double l2(double v1, double l1, double v2);

/** Calculates the semi-major axis for a given distance from the sun at aphelion
 * (v2) and perihelion distance (l1).
 *
 * @param l1 perihelion distance
 * @param l2 distance from the Sun at aphelion
 * @return semi-major axis
 */
double semiMajorAxis(double l1, double l2);

/** Calculates the semi-minor axis for a given distance from the sun at aphelion
 * (l2) and perihelion distance (l1).
 *
 * @param l1 perihelion distance
 * @param l2 distance from the Sun at aphelion
 * @return semi-minor axis
 */
double semiMinorAxis(double l1, double l2);

/** Calculates the orbital period for a given semi-major axis, semi-minor axis,
 * perihelion velocity (v1) and perihelion distance (l1).
 *
 * @param semi_major_axis semi-major axis
 * @param semi_minor_axis semi-minor axis
 * @param l1 perihelion distance
 * @param v1 perihelion velocity
 * @return orbital period
 */
double orbital_period(double semi_major_axis,
                    double semi_minor_axis, double l1, double v1);

/** Calculates the orbital eccentricity for a given perihelion distance (l1) and
 * velocity at aphelion (v2).
 *
 * @param l1 perihelion distance
 * @param l2 distance from the Sun at aphelion
 * @return orbital eccentricity
 */
double orbital_eccentricity(double l1, double l2);

/** Asks for user input to define the perihelion velocity (v1) and perihelion
 * distance (l1) and returns a string.
 *
 * @return string containing the input
 */
std::string v1_input();
std::string l1_input();

/** Checks if the input is valid.
 *
 * @param v1 perihelion velocity
 * @param l1 perihelion distance
 * @throws std::runtime_error if the input is invalid
 */
void check_v1_l1(double v1, double l1);

int main()
{

    std::cout << "Orbital Properties Calculator" << '\n'
              << "Input 'q' to quit" << '\n';

    while (true)
    {

        std::string inputv1{v1_input()};
        if (inputv1 == "q")
        {
            break;
        }
        const double v1{std::stod(inputv1)};

        std::string inputl1{l1_input()};
        if (inputl1 == "q")
        {
            break;
        }
        const double l1{std::stod(inputl1)};

        try
        {

            check_v1_l1(v1, l1);

            const double v2_val{v2(v1, l1)};
            const double l2_val{l2(v1, l1, v2_val)};
            const double semi_major_val{semiMajorAxis(l1, l2_val)};
            const double semi_minor_val{semiMinorAxis(l1, l2_val)};
            const double orbital_period_val{
                orbital_period(semi_major_val, semi_minor_val, l1, v1)};
            const double ecc{orbital_eccentricity(l1, l2_val)};

            std::cout << std::scientific << std::setprecision(4) << '\n'
                      << "Velocity at aphelion (v2) = " << v2_val << " m/s"
                      << '\n';

            std::cout << std::scientific << std::setprecision(4)
                      << "Distance from Sun at aphelion (l2) = " << l2_val
                      << " m" << '\n';

            std::cout << std::fixed << std::setprecision(2)
                      << "Orbital period (T) = " <<
                          orbital_period_val/(365 * 24 * 3600)
                      << " years" << '\n';

            std::cout << std::scientific << std::setprecision(4)
                      << "Orbital eccentricity = " << ecc << '\n';
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please enter numeric value" << '\n';
                      
        }
    }
    return 0;
}

// Function definitions

double v2(double v1, double l1)
{
    std::vector<double> solutions;

    const double b{-(((2 * Constant::g_G * Constant::g_sunMass) / (v1 * l1)))};
    const double c{-(v1 * v1) + ((2 * Constant::g_G * Constant::g_sunMass) / (l1))};

    // calculates v2 utilziing the quadratic formula

    const double v2plus{(-b + std::sqrt((b * b) - 4 * c)) / 2.0};
    solutions.push_back(v2plus);

    const double v2minus{(-b - std::sqrt((b * b) - 4 * c)) / 2.0};
    solutions.push_back(v2minus);

    return *std::min_element(solutions.begin(), solutions.end());
}

double l2(double v1, double l1, double v2)
{
    return (l1 * v1) / std::abs(v2);
}

double semiMajorAxis(double l1, double l2)
{
    return (0.5) * (l1 + l2);
}

double semiMinorAxis(double l1, double l2)
{
    return std::sqrt(l1 * l2);
}

double orbital_period(double semi_major_axis,
                    double semi_minor_axis, double l1, double v1)
{

    const double numerator = 2 * Constant::g_pi * a * b;
    const double denominator = l1 * v1;

    return numerator / denominator;
}

double orbital_eccentricity(double l1, double l2)
{
    return (l2 - l1) / (l2 + l1);
}

std::string v1_input()
{

    std::cout << "Input perihelion velocity in m/s (v1): ";
    std::string inputv1;
    std::cin >> inputv1;
    return inputv1;
}


std::string l1_input()
{

    std::cout << "Input perihelion distance in meters (l1): ";
    std::string inputl1;
    std::cin >> inputl1;
    return inputl1;
}

void check_v1_l1(double v1, double l1)
{

    if (v1 < 0 || l1 < 0)
    {
        throw std::runtime_error("v1 and l1 must be greater than 0.");
    }
}
