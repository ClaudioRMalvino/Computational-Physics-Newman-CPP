/**
 * @brief Exercise 2.13: Recursion
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <tuple>

//Function Declaration

/**
 * @brief:
 * Function takes an integer and calculates the nth Catalan number
 * utilizing recursion.
 *
 * @param int nth_catalan
 *
 * @return: The nth Catalan number
 */

long double catalan_recursion(int nth_catalan);

/**
 * @brief:
 *  Function calculates the greatest common divisor of two non-negative integers
 *  m and n.
 *
 * @param:
 *  int m: A positive integer
 *  int n: A positive integer
*
 * @return Greatest common divisor of m and n
 */

int greatest_common_divisor(int m, int n);

/**
 * @brief Prompts user to input the value for the nth_catalan value or
 * 'q' to quit.
 *
 *
 * @return std::string input
 */

std::string nth_catalan_prompt();

/**
 * @brief Prompts user to input the value for the inputs of
 * greatest common divisor or 'q' to quit.
 *
 *
 * @return std:tuple of strings (m_input, n_input)
 */

std::tuple<std::string, std::string> greatest_common_divisor_prompt();

/**
 * @brief Function checks that the input values are vald
 *
 * @params:
 *  int nth_catalan
 *  int m
 *  int n
 *
 * @throws std::runtime_error if inputs are invalid
 */

void check_values(int nth_catalan, int m, int n);

int main()
{
    std::cout << "Catalan number and greatest common divisor calculator"
              << '\n';
    std::cout << "Input 'q' to quit" << '\n';

    while (true)
    {
        std::string nth_catalan_input{nth_catalan_prompt()};
        if (nth_catalan_input == "q")
        {
            break;
        }
        auto [m_input, n_input] = greatest_common_divisor_prompt();
        if (m_input == "q" || n_input == "q")
        {
            break;
        }

        int nth_catalan{std::stoi(nth_catalan_input)};
        int m{std::stoi(m_input)};
        int n{std::stoi(n_input)};

        try
        {
            auto catalan_value{catalan_recursion(nth_catalan)};
            auto greatest_common_divisor_result{greatest_common_divisor(m, n)};

            std::cout << "The " << nth_catalan << "th number is "
                      << catalan_value << '\n';
            std::cout << "Greatest common divisor of " << m << " and " << n
                      << " is " << greatest_common_divisor_result << '\n';
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please try again." << '\n';
        }
    }
    return 0;
}

// Function Definitions

long double catalan_recursion(int nth_catalan)
{
    if (nth_catalan == 0)
    {
        return 1;
    }
    if (nth_catalan > 40)
    {
        throw std::runtime_error(
            "Input too large: Catalan number would overflow");
    }
    long double coefficient{(4.0L * nth_catalan - 2.0L) / (nth_catalan + 1.0L)};
    return (coefficient * catalan_recursion(nth_catalan - 1L));
}

int greatest_common_divisor(int m, int n)
{
    if (n == 0)
    {
        return m;
    }
    return greatest_common_divisor(n, (m % n));
}


std::string nth_catalan_prompt()
{
    std::cout << "Enter n for the nth Catalan number: ";

    std::string input{};
    std::cin >> input;

    return input;
}

std::tuple<std::string, std::string> greatest_common_divisor_prompt()
{
    std::cout << "Enter an integer, m: ";

    std::string input1{};
    std::cin >> input1;

    std::cout << "Enter an integer, n: ";

    std::string input2{};
    std::cin >> input2;

    return std::make_tuple(input1, input2);
}


void check_values(int nth_catalan, int m, int n)
{
    if (nth_catalan < 0)
    {
        throw std::runtime_error("The nth value must be > 0.");
    }

    if (m < 0 || n < 0)
    {
        throw std::runtime_error("m and n must be positive integers.");
    }
}
