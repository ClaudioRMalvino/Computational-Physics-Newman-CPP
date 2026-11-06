/**
 * @file exercise_2_4.cpp
 * @brief Exercise 2.4: Calculate light year travel from a distance x at a fraction of the speed of light.
 *
 * Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <print>

#include "../../include/common/conversions.h"
#include "../../include/common/constants.h"
#include "../../include/io/io_helpers.hpp"

struct Exercise2_4_UserInput
{
    double velocity{}; ///< Velocity as a fraction of the speed of light
    double distance{}; ///< Distance in light years
};

struct Exercise2_4_Results
{
    double proper_time{}; ///< Time from passenger reference frame
    double dilated_time{}; ///< Time from the observer on Earth
};

/**
 * @brief Prompts user to input the distance traveled in light years and the velocity as a fraction of the speed of
 * light (Ex: 0.99).
 *
 * @return UserInput struct which holds the user defined distance and velocity.
 */
Exercise2_4_UserInput getVelAndDist();

/**
 * @brief Calculates the Lorentz Factor given a velocity as a fraction of the speed of light.
 *
 * gamma = sqrt( 1 - (v)^2),
 *
 * @f$ \gamma = \sqrt{1 - v^{2}} @f$
 *
 * @return The Lorentz factor given a velocity as a fraction of the speed of light.
 */
double lorentzFactor(const double velocity);

/**
 * @brief Calculates the elapsed time from the reference frame of an observer on Earth given a total travel distance
 * and a velocity as a fraction of the speed of light.
 *
 * @f$ \Delta t = \frac{\Delta x}{ \Delta v} @f$
 *
 * where,
 *
 * - @f$ \Delta t @f$: Elapsed time
 * - @f$ \Delta x @f$: Total distance from Earth
 * - @f$ \Delta v @f$: Velocity
 *
 * @return Elapsed time from an observer on Earth.
 */
double earthRefFrame(const double distance, const double velocity);

/**
 * @brief Calculates the elapsed time from the reference from of an observer on a space ship given a total travel
 * distance and a velocity as a fraction of the speed of light.
 *
 * @f$ \Delta \tau = \Delta t \;/\; \gamma @f$
 *
 * where,
 * - @f$ \Delta \tau @f$: Proper time
 * - @f$ \Delta t @f$: Dilated time
 * - @f$ \gamma @f$: Lorentz factor
 *
 * @return Proper time from an observer in the space ship.
 */
double shipRefFrame(const double distance, const double velocity);

int main()
{
    Exercise2_4_UserInput user_input{getVelAndDist()};
    Exercise2_4_Results results{};
    results.dilated_time = earthRefFrame(user_input.distance, user_input.velocity);
    results.proper_time = shipRefFrame(user_input.distance, user_input.velocity);
    std::println(
        "Elapsed time from Earth reference frame: {:.2f} years\n", results.dilated_time / Conversions::Chrono::sec_to_yrs
    );
    std::println(
        "Elapsed time from ship's reference frame: {:.2f} years\n", results.proper_time / Conversions::Chrono::sec_to_yrs
    );
    return 0;
}

Exercise2_4_UserInput getVelAndDist()
{
    while (true)
    {
        std::print("Input the travel distance in light years from Earth: ");
        double distance{};
        std::cin >> distance;
        std::println();

        std::print("Input the velocity of the ship as a fraction of the speed of like (Ex: 0.99): ");
        double velocity{};
        std::cin >> velocity;
        std::println();

        if (velocity < 0.0 || velocity > 1.0)
        {
            std::println("Velocity must be a a fraction between [0, 1]. Try again.");
        }
        if (distance <= 0)
        {
            std::println("Distance must be a positive values. Try again");
            continue;
        }

        if (IO::clearFailedExtraction())
        {
            std::println("Incorrect input. Please try again.");
            continue;
        }

        IO::ignoreLine();
        return {velocity, distance};
    }
}

double lorentzFactor(const double velocity)
{
    return 1.0 / std::sqrt(1.0 - (velocity * velocity));
}

double earthRefFrame(const double distance_lyr, const double velocity)
{
    const double distance_meters {distance_lyr * Conversions::Length::lyr_to_meters};
    const double speed {velocity * Constants::Astro::speed_of_light};
    return distance_meters / speed;
}

double shipRefFrame(const double distance, const double velocity)
{
    return earthRefFrame(distance, velocity) / lorentzFactor(velocity);
}
