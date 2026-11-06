/**
 * @file maths.h
 * @brief Contains mathematical functions, numerical methods, or physics equations used throughout the project.
 */

#pragma once

#include <cmath>
#include <optional>
#include <stdexcept>
#include <utility>

#include "constants.h"

namespace Maths
{
    /**
     * @brief Calculates the root of a 2nd degree polynomial utilizing the quadratic formula.
     *
     * @f$  x = \frac{-b \pm \sqrt{b^2 - 4ac}}{2a} @f$
     *
     * @param a The leading coefficient
     * @param b The linear coefficient
     * @param c The constant term
     *
     * @return If the discriminant is non-negative it will return a std::tuple, else it will return a std::nullptr.
     */
    std::optional<std::pair<double,double>> quadratic(const double a, const double b, const double c)
    {
        const double discriminant { (b * b) - 4.0 * a * c };

        if (discriminant < 0.0) { return {}; }

        if (b == 0 || c == 0) { return std::pair {0.0, 0.0};}

        if (b >= 0)
        {
            const double x1{ (-b - std::sqrt(discriminant) ) / (2 * a) };
            const double x2{ (2 * c) / (-b - std::sqrt(discriminant) ) };
            return std::pair {x1, x2};
        } else
        {
            const double x1{ (2 * c) / (-b + std::sqrt(discriminant) ) };
            const double x2{ (-b + std::sqrt(discriminant) ) / (2 * a) };
            return std::pair {x1, x2};
        }
    }

    /**
     * @brief Calculates the square root at compile time utilizing the Newton-Raphson method.
     * std::sqrt is only constexpr in C++26.
     *
     * @param num The value to be square rooted.
     * @return constexpr square root of `num`.
     */
    constexpr double constexpr_sqrt(const double num) {
        if (num < 0.0) {
            throw std::invalid_argument("Cannot calculate square root of a negative number");
        }
        if (num == 0.0 || num == 1.0) {
            return num;
        }

        double current = num / 2.0;
        double previous = 0.0;

        while (current != previous) {
            previous = current;
            current = 0.5 * (current + num / current);
        }
        return current;
    }
}

namespace Physics
{
    namespace Atomic
    {
        /**
         * Calculates the binding energy of an element as a function of the element atomic number and atomic mass utilizing
         * the semi-empirical mass formula.
         *
         * @f$ B = a_{1}A - a_{2}A^{2/3} - a_{3}\frac{Z^{2}}{A^{1/3}} - a_{4}\frac{(A-2Z)^{2}}{A} + \frac{a_{5}}{A^{1/2}} @f$
         *
         * where,
         *
         * - @f$ A @f$: Mass number
         * - @f$ Z @f$: Atomic number
         * - @f$ a_{1} @f$: Volume coefficient
         * - @f$ a_{2} @f$: Surface coefficient
         * - @f$ a_{3} @f$: Coulomb coefficient
         * - @f$ a_{4} @f$: Asymmetry coefficient
         * - @f$ a_{5} @f$: Pairing coefficient
         *
         * @ return The binding energy of element with atomic number Z with mass number A in units of MeV.
         */
        double semiEmpiricalMass(const int atomic_num, const int mass_num)
            {
                double pairing_coeff{};

                if (mass_num % 2 != 0)
                {
                    pairing_coeff = 0;
                }
                if (mass_num % 2 == 0 && atomic_num % 2 == 0)
                {
                    pairing_coeff = 12;
                }
                if (atomic_num % 2 == 0 && mass_num % 2 != 0)
                {
                    pairing_coeff = -12;
                }

                double volume_term {Constants::Atomic::volume_coeff * mass_num};
                double surface_term {Constants::Atomic::surface_coeff * std::cbrt(mass_num * mass_num)};
                double coulomb_term {Constants::Atomic::coulomb_coeff * ((atomic_num * atomic_num) / std::cbrt(mass_num))};
                double asymmetry_term {Constants::Atomic::asymmetry_coeff
                    * ( ((mass_num - 2 * atomic_num) * (mass_num - 2 * atomic_num)) / mass_num )
                };
                double pairing_term {pairing_coeff / std::sqrt(mass_num)};

                return volume_term - surface_term - coulomb_term - asymmetry_term + pairing_term;
            }
    }
}
