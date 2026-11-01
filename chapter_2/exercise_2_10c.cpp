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
#include <string>
#include <vector>

// Function declaration

double E_per_nucleon(int atomic_num, double atomic_mass, double a5);
std::vector<double> semi_empirical_mass(int atomic_num);
std::string atomic_num_input();
void check_atomic_num(int atomic_num);
void print_results(int atomic_num);

int main()
{

    std::cout
        << "Nuclear Binding Energy Calculator (semi-empirical mass approx)"
        << '\n';
    std::cout << "Input 'q' to quit" << '\n';

    while (true)
    {

        auto atomic_numinput{atomic_num_input()};
        if (atomic_numinput == "q")
        {
            break;
        }
        const int atomic_num = std::stoi(atomic_numinput);

        try
        {

            check_atomic_num(atomic_num);
            print_results(atomic_num);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please enter a numeric value" << '\n'
                      << '\n';
        }
    }
    return 0;
}

// Function definitions

/* Function calculates the approximate nuclear binding energy per nucleon
 * of an atom with atmoic number atomic_num and mass number atomic_mass.
 * Utilizes the semi-empirical mass formula.
 *
 * Returns binding energy per nucleon (B/atomic_mass) in units of MeV
 */
double E_per_nucleon(int atomic_num, double atomic_mass, double a5)
{

    const double a1{15.8};  // [MeV]
    const double a2{18.3};  // [MeV]
    const double a3{0.714}; // [MeV]
    const double a4{23.2};  // [MeV]

    const double term1 = a1 * atomic_mass - a2 * std::pow(atomic_mass, 2.0 / 3.0);
    const double term2 = a3 * ( (atomic_num * atomic_num) / (std::pow(atomic_mass, 1.0 / 3.0)));
    const double term3 = (a4 * (std::pow(atomic_mass - 2 * atomic_num, 2))) / atomic_mass;
    const double term4 = a5 / std::sqrt(atomic_mass);

    const double binding_energy = term1 - term2 - term3 + term4;

    return binding_energy / atomic_mass;
}

/* Function provides the logical steps towards defining the value a5
 *  for E_per_nucleon parameter. It further calculates the most stable nucleus
 *  by running through all values of atomic_mass in [atomic_num, 3atomic_num].
 *
 *  Returns the max binding energy per nuclean and its corresponding isotope atomic_mass
 */

std::vector<double> semi_empirical_mass(int atomic_num)
{

    std::vector<double> values;
    std::vector<double> results;
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
    double max_binding_energy = *max_it;
    int index = std::distance(values.begin(), max_it);
    double most_stable_atomic_mass = atomic_mass_values[index];
    results.push_back(max_binding_energy);
    results.push_back(most_stable_atomic_mass);

    return results;
}

// Function prompts user to input a value for atomic_num
std::string atomic_num_input()
{

    std::cout << "Input atomic number (atomic_num): ";
    std::string input;
    std::cin >> input;

    return input;
}

// Function checks if the input values for atomic_mass and atomic_num are within bounds
void check_atomic_num(int atomic_num)
{

    if (atomic_num <= 0)
    {
        throw std::runtime_error("atomic_num must be > 0");
    }
}

void print_results(int atomic_num)
{

    auto results = semi_empirical_mass(atomic_num);
    std::cout << '\n' << "atomic_masstomic number: " << atomic_num << '\n';
    std::cout << std::fixed << std::setprecision(4)
              << "Largest binding energy per nucleon: " << results[0] << " MeV"
              << '\n';
    std::cout << std::fixed << std::setprecision(2)
              << "Most stable isotope: " << results[1] << " u" << '\n'
              << '\n';
}
