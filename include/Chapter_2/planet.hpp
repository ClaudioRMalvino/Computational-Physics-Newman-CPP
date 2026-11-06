/**
 * @file planet.hpp
 * @brief File contains the Planet class which is utilized in exercise_2_6.cpp.
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <numbers>
#include <print>
#include <stdexcept>
#include <utility>

#include "../common/conversions.h"
#include "../common/constants.h"
#include "../common/maths.hpp"

using namespace Constants;

/**
 * @brief Represents a planet orbiting a star.
 *
 */
class Planet
{
    public:

        double aphelion_dist{};            ///< Aphelion distance from sun [ m ]
        double aphelion_vel{};             ///< Velocity at aphelion [ m/s ]
        double solar_mass{};               ///< Mass of the planet [ kg ]
        double orbital_period{};           ///< Planetary orbital period [ s ]
        double orbital_eccentricty{};      ///< Orbital eccentricty [ dimensionless ]
        double perihelion_vel{};           ///< Velocity at perihelion [ m/s ]
        double perihelion_dist{};          ///< Perihelion distance from Sun [ m ]
        double semi_major_axis{};          ///< Semi-major axis [ m ]
        double semi_minor_axis{};          ///< Semi-minor axis [ m ]

        /**
         * @brief Default constructor utilizes the solar mass, perihelion velocity and distance to calculate all
         * necessary planetary orbital characteristics.
         *
         * @param solar_mass
         * @param perihelion_vel
         * @param perihelion_dist
         */
        Planet(const double solar_mass, const double perihelion_vel, const double perihelion_dist)
            : solar_mass{solar_mass}, perihelion_vel{perihelion_vel}, perihelion_dist{perihelion_dist}
        {
          if (solar_mass <= 0.0 || perihelion_dist <= 0 || perihelion_vel <= 0)
          {
              throw std::invalid_argument(
                  "Planet mass, perihelion distance, and perihelion velocity must be greater than zero."
              );
          }

          calcAphelion();
          calcSemiMajorAxis();
          calcSemiMinorAxis();
          calcOrbitalPeriod();
          calcOrbitalEccentricity();
        }

        Planet (Planet& other) = default;
        ~Planet() = default;

        /**
         * @brief Calculates the aphelion velocity and distance.
         *
         */
        void calcAphelion()
        {
            const double linear_term {(2.0 * Astro::newtons_grav * solar_mass) / (perihelion_dist * perihelion_vel)};
            const double constant_term {
                (perihelion_vel * perihelion_vel) - (2 * Astro::newtons_grav * solar_mass) / (perihelion_dist)
            };

            const auto roots = Maths::quadratic(1.0, -linear_term, -constant_term);

            if (roots) {
                std::print("Quadratic results: {} , {} ", roots->first, roots->second);
                std::print("min root: {} ", std::min(roots->first, roots->second));
                aphelion_vel = std::min(roots->first, roots->second);
                aphelion_dist = (perihelion_vel * perihelion_dist) / aphelion_vel;
            }
        }

        /**
         * @brief Calculates the semi-major axis.
         */
        void calcSemiMajorAxis()
        {
            semi_major_axis = 0.5 * (perihelion_dist + aphelion_dist);
        }

        /**
         * @brief Calculates the semi-minor axis.
         */
        void calcSemiMinorAxis()
        {
            semi_minor_axis = std::sqrt(perihelion_dist * aphelion_dist);
        }

        /**
         * @brief Calculates the orbital period.
         */
        void calcOrbitalPeriod()
        {
            double numerator {2 * std::numbers::pi * semi_major_axis * semi_minor_axis};
            double denominator {perihelion_dist * perihelion_vel};
            orbital_period = numerator / denominator;
        }

        /**
         * @brief Calculates the orbital eccentricity.
         */
        void calcOrbitalEccentricity()
        {
            double numerator {aphelion_dist - perihelion_dist};
            double denominator {aphelion_dist + perihelion_dist};
            orbital_eccentricty = numerator / denominator;
        }

        void printProperties()
        {
            std::println("--------------------------------------------------------");
            std::println("Mass: {:.3e} kg", solar_mass);
            std::println("Orbital period: {:.2f} yr", orbital_period / Conversions::Chrono::sec_to_yrs);
            std::println("Perihelion velocity: {:.4e} m/s", perihelion_vel);
            std::println("Perihelion distance: {:.4e} m", perihelion_dist);
            std::println("Aphelion velocity: {:.4e} m/s", aphelion_vel);
            std::println("Aphelion distance: {:.4e} m", aphelion_dist);
            std::println("Orbital eccentricity: {:.4f} ", orbital_eccentricty);
            std::println("Semi-major axis: {:.4e} m", semi_major_axis);
            std::println("Semi-minor axis: {:.4e} m", semi_minor_axis);
        }
};
