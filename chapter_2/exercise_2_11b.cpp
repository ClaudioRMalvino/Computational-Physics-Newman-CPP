/**
 * @file exercise_2_11b.cpp
 * @brief Exercise 2.11: Bionmial Coefficients Part b)
 *
 * From: Computational Physics by Mark Newman
 */

#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

// Namespace declaration
namespace mp = boost::multiprecision;

// Function Declaration
/**
 * @brief Calculates the factorial of an integer
 * @param x The integer to calculate factorial for
 * @return The factorial as a mp::cpp_int
 */
mp::cpp_int factorial(int x);

/**
 * @brief Calculates the binomial coefficient (n choose k)
 * @param n The total number of items
 * @param k The number of items to choose
 * @return The binomial coefficient as a mp::cpp_int
 */
mp::cpp_int binomial_coefficient(int n, int k);

/**
 * @brief Prompts for and reads the value of n from user input
 * @return The input string (which may be a number or 'q' to quit)
 */
std::string N_input();

/**
 * @brief Function utilizes binomial_coefficient to calculate and print
 * Pascal's triangle.
 * @param N The max number of rows
 * @return cout values of Pascal's triangle up to row N
 * */
void pascals_triangle(int N);

/**
 * @brief Checks if the input values n and k are valid
 * @param n The total number of items
 * @param k The number of items to choose
 * @throws std::runtime_error if inputs are invalid
 */
void check_value(int N);

int main()
{

    std::cout << "Pascal's Triangle Generator" << '\n';

    while (true)
    {
        const std::string Ninput{N_input()};
        if (Ninput == "q")
        {
            break;
        }
        const int N {std::stoi(Ninput)};

        try
        {

            check_value(N);
            pascals_triangle(N);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. PLease enter a numeric value" << '\n'
                      << std::endl;
        }
    }
    return 0;
}

// Function Definitions

mp::cpp_int factorial(int x)
{

    mp::cpp_int f = 1;
    for (int i : std::views::iota(1, x + 1))
    {
        f *= i;
    }
    return f;
}

mp::cpp_int binomial_coefficient(int n, int k)
{

    if (k == 0)
    {
        return 1;
    }
    else
    {
        mp::cpp_int numerator = factorial(n);
        mp::cpp_int denominator =
            factorial(k) * factorial(n - k);
        mp::cpp_int binomial_coef = numerator / denominator;
        return binomial_coef;
    }
}

std::string N_input()
{
    std::cout << "Input an integer for number of rows to be generated: ";
    std::string input;
    std::cin >> input;

    return input;
}


void pascals_triangle(int N)
{

    int n = 1;
    std::cout << n << std::endl; // prints first row
    while (n < N)
    {
        std::vector<mp::cpp_int> triangle;
        for (int K : std::views::iota(0, n + 1))
        {
            triangle.push_back(binomial_coefficient(n, K));
        }
        n += 1;

        // Print the triangle row
        for (const auto &num : triangle)
        {
            std::cout << num << " ";
        }
        std::cout << std::endl;
    }
}

void check_value(int N)
{
    if (N <= 0)
    {
        throw std::runtime_error("n must be a positive integer");
    }
}
