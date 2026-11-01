/*
 * Exercise 2.9: The Madelung Constant
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <cmath>
#include <iostream>
#include <ranges>

// Function declaration

const double madelungConstant(int L)
{

    double madelung_constant{0.0};
    for (int i : std::views::iota(-L, L + 1))
    {
        for (int j : std::views::iota(-L, L + 1))
        {
            for (int k : std::views::iota(-L, L + 1))
            {
                if (i == 0 && j == 0 && k == 0)
                {
                    continue;
                }

                double r = std::sqrt(i * i + j * j + k * k);
                int exponent = std::abs(i) + std::abs(j) + std::abs(k);
                double sign = (exponent % 2 == 0) ? 1.0 : -1.0;
                madelung_constant += sign / r;
            }
        }
    }
    return madelung_constant;
}

int main()
{

    const int L{100};
    const double result{madelungConstant(L)};

    std::cout << "Madelung constant " << result << '\n';

    return 0;
}
