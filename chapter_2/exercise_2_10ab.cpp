/*
 * Exercise 2.10 Parts a) & b): The semi-empirical mass formula
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>

// Function declaration

/** @brief Calculates the semi-empirical mass formula for a given atomic number
 * and mass number.
 *
 *@param atomic_numThe atomic number
 *@param atomic_mass The atomic mass
 *@param a5 The a5 parameter
 *
 * @returns binding energy in units of MeV
 */
double semi_empirical_mass_formula(int atomic_num, double atomic_mass, double a5);

/** @brief Calculates the semi-empirical mass formula for a given atomic number
 * and mass number.
 *
 *@param atomic_num The atomic number
 *@param atomic_mass The atomic mass
 *
 * @returns binding energy in units of MeV
 */
double semiEmpiricalMass(int atomic_num, double atomic_mass);

/** @brief Prompts user to input a value for atomic_num
 *
 * @returns the input value for atomic_num
 */
std::string inputAtomicNum();

/** @brief Prompts user to input a value for atomic_mass
 *
 * @returns the input value for atomic_mass
 */
std::string inputAtomicMass();

/** @brief Checks if the input values for atomic_mass and are within bounds
 *
 * @param atomic_num The atomic number
 * @param atomic_mass The atomic mass
 * @throws std::runtime_error if input is invalid
 */
void checkAtomicMass_AtomicNum(int atomic_num, double atomic_mass);
void printResults(int atomic_num, double atomic_mass, double B);

int main()
{

    std::cout
        << "Nuclear Binding Energy Calculator (semi-empirical mass approx)"
        << '\n';
    std::cout << "Input 'q' to quit" << '\n';

    while (true)
    {

        const std::string input_atomic_num{inputAtomicNum()};
        if (input_atomic_num == "q")
        {
            break;
        }
        const int atomic_num { std::stoi(input_atomic_num) };

        const std::string input_atomic_mass{inputAtomicMass()};
        if (input_atomic_mass == "q")
        {
            break;
        }
        const double atomic_mass { std::stod(input_atomic_mass) };

        try
        {

            checkAtomicMass_AtomicNum(atomic_num, atomic_mass);
            const double B {semiEmpiricalMass(atomic_num, atomic_mass)};
            printResults(atomic_num, atomic_mass, B);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please enter a numeric value" << '\n';
        }
    }
    return 0;
}

// Function definitions

double semiEmpiricalMass_formula(int atomic_num, double atomic_mass, double a5)
{

    constexpr double a1{15.8};  // [MeV]
    constexpr double a2{18.3};  // [MeV]
    constexpr double a3{0.714}; // [MeV]
    constexpr double a4{23.2};  // [MeV]

    double term1 = a1 * atomic_mass - a2 * std::pow(atomic_mass, 2.0 / 3.0);
    double term2 = a3 * ((std::pow(atomic_num, 2)) /
                    (std::pow(atomic_mass, 1.0 / 3.0)));
    double term3 = (a4 * (std::pow(atomic_mass - 2 * atomic_num, 2)))
                    / atomic_mass;
    double term4 = a5 / std::sqrt(atomic_mass);

    double binding_energy = term1 - term2 - term3 + term4;

    return binding_energy;
}

double semiEmpiricalMass(int atomic_num, double atomic_mass)
{

    double a5;

    if (std::fmod(atomic_mass, 2.0) != 0.0)
    {
       const double a5{0.0};
    }
    else if (atomic_num% 2 == 0)
    {
        const double a5{12.0};
    }
    else
    {
        const double a5{-12.0};
    }

    return semi_empirical_mass_formula(atomic_num, atomic_mass, a5);
}

// Function prompts user to input a value for atomic_num
std::string atomicNumInput()
{

    std::cout << "Input atomic number (atomic_num): ";
    std::string input;
    std::cin >> input;

    return input;
}

// Function prompts user to input a value for atomic_mass
std::string atomicMassInput()
{

    std::cout << "Input atomic mass (atomic_mass): ";
    std::string input;
    std::cin >> input;

    return input;
}


void checkAtomicMass_AtomicNum(int atomic_num, double atomic_mass)
{

    if (atomic_mass <= 0 || atomic_num<= 0)
    {
        throw std::runtime_error("atomic_mass and atomic_nummust be > 0");
    }
}

void printResults(int atomic_num, double atomic_mass, double binding_energy)
{

    const double B_per_nucleon{binding_energy / atomic_mass};

    std::cout << '\n' << "Atomic number: " << atomic_num<< '\n';
    std::cout << "Atomic mass: " << atomic_mass << " u" << '\n';
    std::cout << std::fixed << std::setprecision(2)
              << "Approx nuclear binding energy: " << binding_energy
              << " MeV" << '\n';
    std::cout << std::fixed << std::setprecision(2)
              << "Binding energy per nucleon: " << B_per_nucleon << " MeV"
              << '\n';

}
