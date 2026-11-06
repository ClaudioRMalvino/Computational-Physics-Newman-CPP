/**
 * @file exercise_2_5.cpp
 * @brief Exercise 2.5: Quantum potential step
 *
 * Computational Physics by Mark Newman
 */

#include <print>
#include <stdexcept>

#include "../../include/common/constants.h"
#include "../../include/common/maths.hpp"

/// Holds variables that define the system
namespace System {
    constexpr double p_mass{Constants::Quantum::electron_mass_c}; ///< Mass of particle [ eV / c^2]
    constexpr double p_energy{10.0};                              ///< Energy of particle [ eV * s]
    constexpr double potential_energy{9.0};                       ///< Potential energy of step [ eV ]
};

/**
 * @brief Calculates the wavevector of the particle prior to interacting with the potential step.
 *
 * @f$ k_{1} = \sqrt{ 2 * M * E } / \hbar @f$,
 *
 * where,
 *
 * - @f$ M @f$: Mass of the particle
 * - @f$ E @f$: Energy of the particle
 * - @f$ \hbar @f$: Reduced Planck constant
 *
 * @return The wavevector of the particle before interaction
 */
constexpr double wavevector_k1();

/**
 * @brief Calculates the wavevector of the particle prior to interacting with the potential step.
 *
 * @f$ k_{2} = \sqrt{ 2 * M * (E - V) } / \hbar @f$
 *
 * where,
 *
 * - @f$ M @f$: Mass of the particle
 * - @f$ E @f$: Energy of the particle
 * - @f$ V @f$: Potential energy of the system
 * - @f$ \hbar @f$: Reduced Planck constant
 *
 * @return The wavevector of the particle after interaction
 */
constexpr double wavevector_k2();

/**
 * Calculates the probability of particle transmission (going over the potential step).
 *
 * @f$ T = (4 k_{1} k_{2}) / ( k_{1} + k_{2} )^{2}  @f$
 *
 * where,
 *
 * - @f$ k_{1} @f$: Wavevector prior to interaction
 * - @f$ k_{2} @f$: Wavevector post interaction
 */
constexpr double calcTransmissionProb();

/**
 * Calculates the probability of particle reflection (bouncing against the potential step).
 *
 * @f$ R = ( (k_{1}- k_{2}) / (k_{1} + k_{2}) )^{2} @f$
 *
 * where,
 *
 * - @f$ k_{1} @f$: Wavevector prior to interaction
 * - @f$ k_{2} @f$: Wavevector post interaction
 */
constexpr double calcReflectionProb();

int main() {

    std::println(
        "Particle of mass {:.3e} eV and energy {:.2f} eV interacting with potential step of {:.2f} eV",
        System::p_mass,
        System::p_energy,
        System::potential_energy
    );
    std::println("Probability of Transmission: {:.2f}", calcTransmissionProb());
    std::println("Probability of Reflection: {:.2f}", calcReflectionProb());
    return 0;
}

constexpr double wavevector_k1()
{
    return Maths::constexpr_sqrt(2.0 * System::p_mass * System::p_energy) / Constants::Quantum::h_bar_eV;
}

constexpr double wavevector_k2() {
    return Maths::constexpr_sqrt(2.0 * System::p_mass * (System::p_energy - System::potential_energy)) / Constants::Quantum::h_bar_eV;
}

constexpr double calcTransmissionProb()
{
    constexpr double numerator { (4.0 * (wavevector_k1() * wavevector_k2())) };
    constexpr double denominator { (wavevector_k1() + wavevector_k2()) * (wavevector_k1() + wavevector_k2()) };
    return numerator / denominator;
}

constexpr double calcReflectionProb()
{
    constexpr double numerator { wavevector_k1() - wavevector_k2() };
    constexpr double denominator { wavevector_k1() + wavevector_k2() };
    constexpr double frac { numerator / denominator };
    return frac * frac;
}
