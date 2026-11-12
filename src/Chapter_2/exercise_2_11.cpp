/**
 * @file exercise_2_11.cpp
 * @brief Exercise 2.11: Binomial coefficient
 */

#include <print>

#include "../../include/common/maths.hpp"

void printPascalsTriangle(const int num_lines);

int main()
{
    const int total{10}, choose{3}, result{120}, num_lines{20};
    if (Maths::binomialCoeff(total, choose) == result)
    {
        std::println("Function works correctly.\n{} choose {} is {}.\n", total, choose, result);
    } else
    {
        std::println("Function is incorrect.");
    }

    std::println("Printing the first {} lines of Pascal's Triangle\n", num_lines);
    printPascalsTriangle(num_lines);

    return 0;
}

void printPascalsTriangle(const int num_lines) {
    for (int line{1}; line < num_lines; ++line) {
        int chose{line + 1};
        for (int num{}; num < chose; ++num) {
            std::print("{} ", Maths::binomialCoeff(line, num));
        }
        std::println();
    }
}

//TODO: Complete exercise c).