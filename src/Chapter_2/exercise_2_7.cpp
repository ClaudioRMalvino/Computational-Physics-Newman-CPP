/**
 * @file exercise_2_7.cpp
 * @brief Exercise 2.7: Catalan numbers
 *
 * Computational Physics by Mark Newman
 */

#include <iostream>
#include <print>

#include "../../include/io/io_helpers.hpp"

/**
 * @brief Prompts user to input a max number of Catalan numbers to print..
 *
 * @return The user inputted max number.
 */
int userInput();

/**
 * @brief Prints all Catalan numbers from n = [0, max_num].
 *
 * @f$ C_{n+1} = \frac{4n + 2}{n + 2} C_{n}, \; C_{0} = 1
 *
 * @param max_num The maximum number of Catalan numbers to print.
 */
void catalanNumber(const int max_num);

int main()
{
    int usr_max_num {userInput()};
    catalanNumber(usr_max_num);
    return 0;
}

int userInput()
{
    while (true)
    {
        std::print("Input max number: ");
        int input_num{};
        std::cin >> input_num;
        std::println();

        if (input_num <=0 )
        {
            std::print("Max number must be greater than zero. Try again.");
            continue;
        }
        if (IO::clearFailedExtraction())
        {
            std::print("Invalid input. Try again.");
        }
        IO::ignoreLine();

        return input_num;
    }
}

void catalanNumber(const int max_num)
{
    double curr_num{1.0};

    for (int nth{0}; nth < max_num; ++nth)
    {
        std::print("curr_num = {}, ", curr_num);
        double next_num { ((4.0 * static_cast<double>(nth) + 2.0) / (static_cast<double>(nth) + 2.0)) * curr_num };
        curr_num = next_num;
        std::print("next_num = {}, ", next_num);
        std::println("C_{} = {}, ",nth + 1, next_num);
    }
}
