/*
 * Exercise 2.7: Catalan numbers
 *
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <string>
#include <typeinfo>

// Function declaration

/** @brief Calculates the nth Catalan number
 * @param max_val The maximum value to calculate the Catalan number for
 */
void catalan_num(int max_val);

/** @brief Checks if the input value is valid
 * @param max_val The maximum value to calculate the Catalan number for
 * @throws std::runtime_error if input is invalid
 */
void check_input_val(int max_val);

/** @brief Prompts user for input
 * @return The input string (which may be a number or 'q' to quit)
 */
std::string val_input();

int main()
{
    std::cout << "Catalan number generator" << std::endl;
    std::cout << "Input 'q' to quit" << std::endl;

    while (true)
    {

        const std::string max_val_input{val_input()};
        if (max_val_input == "q")
        {
            break;
        }
        const int max_val{std::stoi(max_val_input)};

        try
        {

            check_input_val(max_val);

            catalan_num(max_val);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. PLease enter a numeric value" << '\n'
                      << std::endl;
        }
    }
    return 0;
}

// Function definitions

void catalan_num(const int max_val)
{

    double c0{1};
    int n{1};
    while (c0 <= max_val)
    {
        double numerator = 4 * n + 2;
        double denominator = n + 2;
        double cn = (numerator / denominator) * c0;
        n++;
        c0 = cn;
    }
}

void check_input_val(int max_val)
{

    if (max_val <= 0 || typeid(int) != typeid(max_val))
    {
        throw std::runtime_error("Max value must be an integer > 0");
    }
}

std::string val_input()
{
    std::cout << "Input an integer > 0: " << std::endl;
    std::string input;
    std::cin >> input;

    return input;
}
