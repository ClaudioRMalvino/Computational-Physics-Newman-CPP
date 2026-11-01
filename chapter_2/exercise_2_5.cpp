/*
 * Exercise 2.5: Quantum Potential Step
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

namespace Constant
{
// Global constants
constexpr double g_m{0.5109989461};  // Mass of electron [eV]
constexpr double g_h_bar{6.5821196}; // Reduced Planck constant [eV*s]
}

// Forward function declarations

/** Calculates the wavevector k1 for a given energy
 * @param energy energy of electron in eV
 * @return wavevector k1
 */
double k1(double energy);

/** Calculates the wavevector k2 for a given energy and potential step
 * @param energy energy of electron in eV
 * @param potential energy of potential step in eV
 * @return wavevector k2
 */
double k2(double energy, double potential);

/** Calculates the transmission probability for a given wavevector k1 and k2
 * @param k1 wavevector k1
 * @param k2 wavevector k2
 * @return transmission probability
 */
double T(double k1, double k2);

/** Calculates the reflection probability for a given wavevector k1 and k2
 * @param k1 wavevector k1
 * @param k2 wavevector k2
 * @return reflection probability
 */
double R(double k1, double k2);

/** Prompts user for energy
 * @return energy input
 */
std::string E_input();

/** Prompts user for potential step
 * @return potential step input
 */
std::string V_input();

int main()
{

    std::cout << "Calculating transimission and reflection probabilities"
              << '\n'
              << "Input 'q' to quit" << '\n';

    while (true)
    {
        const std::string inputE{E_input()};
        if (inputE == "q")
        {
            break;
        }
        const double energy = std::stod(inputE);

        const std::string inputV{V_input()};
        if (inputV == "q")
        {
            break;
        }
        const double potential = std::stod(inputV);

        if (energy <= potential)
        {
            const double k{-k1(energy)};
            std::cout << std::fixed << std::setprecision(3)
                      << "wavevector: " << k
                      << ", Probability of reflection: 100%" << '\n';
        }
        else
        {
            std::cout << "\nGiven an electron of mass " << Constant::g_m
                      << " eV, initial energy " << energy
                      << " eV and potential step " << potential << "eV: \n";

            const double k1_val{k1(energy)};
            const double k2_val{k2(energy, potential)};

            std::cout << std::fixed << std::setprecision(1)
                      << "Probability of reflection: "
                      << R(k1_val, k2_val) * 100.0
                      << "% || wavevector: " << std::setprecision(3) << -k1_val
                      << '\n';

            std::cout << std::fixed << std::setprecision(1)
                      << "Probability of transmission: "
                      << T(k1_val, k2_val) * 100.0
                      << "% || wavevector: " << std::setprecision(3) << k2_val
                      << '\n';
        }
    }
    return 0;
}

// Function definitions

double k1(const double energy)
{
    return std::sqrt(2 * Constant::g_m * energy / Constant::g_h_bar);
}

double k2(const double energy, const double potential)
{
    return std::sqrt(2 * Constant::g_m * (energy - potential)
                        / Constant::g_h_bar);
}

double R(double k1, double k2)
{
    const double k_diff = k1 - k2;
    const double k_sum = k1 + k2;
    return (k_diff * k_diff) / (k_sum * k_sum);
}

double T(double k1, double k2)
{

    double k_sum = k1 + k2;
    return (4 * k1 * k2) / (k_sum * k_sum);
}

std::string E_input()
{

    std::cout << '\n' << "Input energy of electron in eV: ";
    std::string inputE;
    std::cin >> inputE;
    return inputE;
}

std::string V_input()
{

    std::cout << '\n' << "Input energy of potential step in eV: ";
    std::string inputV;
    std::cin >> inputV;
    return inputV;
}
