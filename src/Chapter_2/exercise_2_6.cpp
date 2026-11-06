/**
 * @file exercise_2_6.cpp
 * @brief Exercise 2.6: Planetary orbits
 *
 * Computational Physics by Mark Newman
 */

#include <iostream>
#include <print>

#include "../../include/Chapter_2/planet.hpp"
#include "../../include/io/io_helpers.hpp"

struct Exercise_2_6_UserInput
{
    double user_solar_mass{};             ///< User inputted Solar [ kg ]
    double user_perihelion_vel{};         ///< User inputted planetary perihelion velocity  [ m/s ]
    double user_perihelion_dist{};        ///< User inputted planetary perihelion distance [ m/s ]
};

/**
 * @brief Prompts the user to input the solar mass, planetary perihelion velocity and distance.
 */
Exercise_2_6_UserInput getInputs()
{
    while (true)
    {
        std::print("Input orbiting solar mass [ kg ] : ");
        double usr_mass {};
        std::cin >> usr_mass;
        std::println();

        std::print("Input planetary perihelion velocity [ m/s ] : ");
        double usr_peri_vel{};
        std::cin >> usr_peri_vel;
        std::println();

        std::print("Input planetary perihelion distance [ m ] : ");
        double usr_peri_dist{};
        std::cin >> usr_peri_dist;
        std::println();

        if (usr_mass <= 0 || usr_peri_vel <= 0 || usr_peri_dist <= 0)
        {
            std::print(
                "Planetary mass, perihelion velocity, and perihelion distance must be greater than zero. Try Again."
            );
            continue;
        }

        if (IO::clearFailedExtraction())
        {
            std::print("Incorrect input. Try again.");
            continue;
        }
        IO::ignoreLine();

        return {usr_mass, usr_peri_vel, usr_peri_dist};
    }
}

int main()
{
    Exercise_2_6_UserInput input {getInputs()};
    Planet usr_planet(input.user_solar_mass, input.user_perihelion_vel, input.user_perihelion_dist);
    usr_planet.printProperties();

    return 0;
}
