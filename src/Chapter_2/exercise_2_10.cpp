/**
 * @file exercise_2_10.cpp
 * @brief Exercise 2.10: The semi-empirical mass formula
 *
 * Computational Physics by Mark Newman
 */

#include <iostream>
#include <limits>
#include <print>
#include <utility>

#include "../../include/Chapter_2/periodic_table.h"
#include "../../include/common/maths.hpp"
#include "../../include/io/io_helpers.hpp"

///< Struct holds user inputs
struct Exercise_2_10Input
{
    char usr_option;          ///< User selected option (a, b, or c)
    int usr_atomic_num{};     ///< Atomic number, Z
    int usr_mass_num{};       ///< Mass number, A
};

/**
 * @brief Prompts the user to provide an option (a, b, c) for what they would like to calculate and then asks for an
 * atomic number, Z, or mass number, A, or both depending on the option selected.
 * Then runs the function pertaining to the respective choice and provides it the inputs the user was prompted for.
 *
 * @return Struct with the user defined choices.
 */
Exercise_2_10Input userInputPrompt();

/**
 * @brief Prompts user to provide an option ('a', 'b', or 'c')./n
 * Where,
 *
 * - a: Calculates the binding energy and binding energy per nucleon for a given atomic number and mass number.
 * - b: Calculates for and provides the most stable isotope of a given element with atomic number, Z.
 * - c: Calculates for and provides the most stable isotope for each element with atom number Z = [1, 100].
 *
 * @return the user inputted choice.
 */
char usrOptionPrompt();

/**
 *@brief Provides the necessary prompts if the user in usrOptionPrompt() returns 'a'. Asks the user to input a value for
 * atomic number, Z, and mass number, A.
 *
 * @return a pair, where: first->atomic number, second->mass number.
 */
std::pair<int, int> usrOptionAPrompt();

/**
 *@brief Provides the necessary prompt if the user in usrOptionPrompt() returns 'b'. Asks the user to input a value for
 * atomic number, Z.
 *
 * @return the return value of optionBStableIsotope().
 */
int usrOptionBPrompt();

/**
 * @brief Calculates and prints the binding energy and binding energy per nucleon of the element with atomic number Z
 * and mass number A utilziing the semi-empirical mass formula.
 */
void optionABindingEnergy(const int atomic_num_Z, const int mass_num_A);

/**
 * @brief Calculates and prints the binding energy and binding energy per nucleon of the most stable isotope of element with
 * atomic number Z from the range of mass number A = [Z, 3Z] utilizing the semi-empirical mass formula.
 */
void optionBStableIsotope(const int atomic_num_Z);

/**
 * @brief Calculates and prints the binding energy and binding energy per nucleon of the most stable isotope of each element
 * ranging from Z = [1, 100] utilizing the semi-empirical mass formula.
 */
void optionCStableIsotopePerElement();

int main()
{
    Exercise_2_10Input usr_input{userInputPrompt()};

    if (usr_input.usr_option == 'a')
    {
        optionABindingEnergy(usr_input.usr_atomic_num, usr_input.usr_mass_num);
    }
    if (usr_input.usr_option == 'b')
    {
        optionBStableIsotope(usr_input.usr_atomic_num);
    }
    if (usr_input.usr_option == 'c')
    {
        optionCStableIsotopePerElement();
    }
    return 0;
}

Exercise_2_10Input userInputPrompt()
{
    char final_option{usrOptionPrompt()};

    if (final_option == 'a')
    {
       const auto [final_atomic_num, final_mass_num] = usrOptionAPrompt();
       return {final_option, final_atomic_num, final_mass_num};
    }

    if (final_option == 'b')
    {
        return {final_option, usrOptionBPrompt(), 0};
    }

    if (final_option == 'c')
    {
        return {final_option, 0, 0};
    }

    return {' ', 0, 0};
}

char usrOptionPrompt()
{
    while (true)
        {
            char option;
            std::println("Please select one of the following options: ");
            std::println(
                "a) Calculate the binding energy and binding energy per nucleon for given atomic mass, A, and atomic number, Z."
            );
            std::println(
                "b) Calculate the most stable isotope for atomic number, Z."
            );
            std::println(
                "c) Calculate most stable isotope for each Z = [1, 100]."
            );

            std::cin >> option;

            if (option != 'a' && option != 'b' && option != 'c')
            {
                std::println("Please input 'a', 'b', or 'c'. Try again.");
                continue;
            }

            if (IO::clearFailedExtraction()) {
                std::println("Incorrect input. Please try again.");
                continue;
            }
            IO::ignoreLine();

            return option;
        }
}

std::pair<int, int> usrOptionAPrompt() {

    while (true)
    {
        std::print("Input atomic number, Z: ");
        int atomic_num;
        std::cin >> atomic_num;
        std::println();

        std::print("Input atomic mass, A: ");
        int mass_num;
        std::cin >> mass_num;

        if (atomic_num < 1 || mass_num < 1) {
            std::println("Atomic number and mass must be greater than or equal to 1.");
            continue;
        }

        if (IO::clearFailedExtraction())
        {
            std::println("Incorrect input. Please try again.");
            continue;
        }
        IO::ignoreLine();

        return {atomic_num, mass_num};
    }
}

int usrOptionBPrompt()
{
    while (true)
    {
        std::print("Input atomic number, Z: ");
        int atomic_num;
        std::cin >> atomic_num;
        std::println();

        if (atomic_num < 1) {
            std::println("Atomic number and must be greater than or equal to 1.");
            continue;
        }

        if (IO::clearFailedExtraction())
        {
            std::println("Incorrect input. Please try again.");
            continue;
        }
        IO::ignoreLine();

        return atomic_num;
    }
}

void optionABindingEnergy(const int atomic_num_Z, const int mass_num_A)
{
    const double binding_energy{Physics::Atomic::semiEmpiricalMass(atomic_num_Z, mass_num_A)};
    std::println(
        "Element: {} \nAtomic Number: {} \nAtomic Mass: {} \nBinding Energy: {:.3f} MeV \nBinding Energy per Nucleon: {:.3f} MeV",
        PeriodicTable::period_table[atomic_num_Z],
        atomic_num_Z,
        mass_num_A,
        binding_energy,
        binding_energy / mass_num_A
    );
}

void optionBStableIsotope(const int atomic_num_Z)
{
    double max_BE_per_nucleon {-std::numeric_limits<double>::infinity()};
    int max_atomic_mass{};

    for (int atomic_mass_A{atomic_num_Z}; atomic_mass_A <= 3 * atomic_num_Z; ++atomic_mass_A)
    {
        double BE_per_nucleon { Physics::Atomic::semiEmpiricalMass(atomic_num_Z, atomic_mass_A) / atomic_mass_A };

        if (BE_per_nucleon > max_BE_per_nucleon)
        {
            max_BE_per_nucleon = BE_per_nucleon;
            max_atomic_mass = atomic_mass_A;
        } else
        {
            break;
        }

    }

    std::println("Most stable Isotope of {}", PeriodicTable::period_table[atomic_num_Z]);
    std::println(
            "Atomic Number: {} \nAtomic Mass: {} \nBinding Energy: {:.3f} MeV \nBinding Energy per Nucleon: {:.3f} MeV",
            atomic_num_Z,
            max_atomic_mass,
            max_BE_per_nucleon,
            max_BE_per_nucleon / max_atomic_mass
        );
}

void optionCStableIsotopePerElement()
{
    for (int atomic_num_Z{1}; atomic_num_Z <= 100; ++atomic_num_Z)
    {
        optionBStableIsotope(atomic_num_Z);
        std::println();
    }
}
