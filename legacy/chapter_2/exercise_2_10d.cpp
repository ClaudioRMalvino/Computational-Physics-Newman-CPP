/*
 * Exercise 2.10 Part c): The semi-empirical mass formula
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <vector>

// Function declaration
/** @brief Calculates the approximate nuclear binding energy per nucleon
 * of an atom with atomic number atomic_num and mass number atomic_mass.
 * Utilizes the semi-empirical mass formula.
 *
 * @param atomic_num The atomic number
 * @param atomic_mass The atomic mass
 * @param a5 The a5 parameter
 *
 * @returns binding energy per nucleon (B/atomic_mass) in units of MeV
 */
constexpr double E_per_nucleon(int atomic_num, double atomic_mass, double a5);

void semi_empirical_mass();

int main()
{

    std::cout
        << "Nuclear binding_energyinding Energy Calculator (semi-empirical mass approx)"
        << std::endl;
    semi_empirical_mass();

    return 0;
}

// Function definitions

constexpr double E_per_nucleon(int atomic_num, double atomic_mass, double a5)
{
    constexpr double a1{15.8};  // [MeV]
    constexpr double a2{18.3};  // [MeV]
    constexpr double a3{0.714}; // [MeV]
    constexpr double a4{23.2};  // [MeV]

    const double term1 = a1 * atomic_mass - a2 * std::pow(atomic_mass, 2.0 / 3.0);
    const double term2 = a3 * ((atomic_num * atomic_num) / std::pow(atomic_mass, 1.0 / 3.0));
    const double term3 = (a4 * ((atomic_mass - 2 * atomic_num)*(atomic_mass - 2 * atomic_num)))
                        / atomic_mass;
    const double term4 = a5 / std::sqrt(atomic_mass);

    const double binding_energy = term1 - term2 - term3 + term4;

    return binding_energy / atomic_mass;
}

void semi_empirical_mass()
{

    for (int atomic_num : std::views::iota(1, 101))
    { // 1 to 100 inclusive
        std::vector<double> values;
        std::vector<double> atomic_mass_values;
        for (double atomic_mass : std::views::iota(atomic_num, 3 * atomic_num + 1))
        {
            double a5;
            if (std::fmod(atomic_mass, 2.0) != 0.0)
            {
                a5 = 0.0;
            }
            else if (atomic_num % 2 == 0)
            {
                a5 = 12.0;
            }
            else
            {
                a5 = -12.0;
            }
            values.push_back(E_per_nucleon(atomic_num, atomic_mass, a5));
            atomic_mass_values.push_back(atomic_mass);
        }

        auto max_it = std::max_element(values.begin(), values.end());
        const double max_binding_energy = *max_it;
        const int index = std::distance(values.begin(), max_it);
        const double most_stable_atomic_mass = atomic_mass_values[index];

        // Prints the calculated values for each element
        std::cout << '\n' << "atomic_masstomic number: " << atomic_num << '\n';
        std::cout << std::fixed << std::setprecision(4)
                  << "Highest binding energy per nucleon: " << max_binding_energy
                    << " MeV "<< '\n';
        std::cout << std::fixed << std::setprecision(2)
                  << "Most stable isotope: " << most_stable_atomic_mass
                    << " u" << '\n';
        std::cout << "----------------------------------------------------\n"
                  << '\n';
    }
}
