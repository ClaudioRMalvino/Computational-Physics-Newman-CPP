/**
 * @file exercise_2_9.cpp
 * @brief Exercise 2.9: The Madelung constant
 */

#include <cmath>
#include <omp.h>
#include <print>
#include <ranges>

#include "../../include/common/constants.h"
#include "../../include/common/maths.hpp"

///< Holds system variables
namespace System
{
    constexpr int L_atoms {1000};         ///< Number of atoms in the system
}

using namespace Constants;

/**
 * @brief Calculates the Madelung constant for a central atom cubic NaCl as a function of the number of atoms in the
 * system. Utilizes OpenMP to parallelize the O(N^3) loop.
 *
 * The sign is positive when (i + j + k) is even (for sodium) and negatiove when odd (for chlorine).
 *
 * @f$ V(i,j,k) = \pm \frac{ e }{ 2 \pi \epsilon_{0} a \sqrt{i^{2} + j^{2} + k^{2}} } @f$,
 * \n
 * @f$ V_{total} = \sum\limits_{ i,j,k=-L }^{ L } \; V(i,j,k) = \frac{ e }{ 2 \pi \epsilon_{0} a } M @f$,
 *
 * where,
 *
 * - @f$ e @f$: electron charge
 * - @f$ \epsilon_{0} @f$: vacuum permitivity
 * - @f$ a @f$: lattice constant
 *
 */
double madelungConstant(const int num_atoms);


int main()
{
    omp_set_num_threads(8);
    std::print("Madelung Constant for NaCl: {:.3f}", madelungConstant(System::L_atoms));
    return 0;
}

double madelungConstant(const int num_atoms)
{
    double madelung_constant{0.0};
    double start {omp_get_wtime()};
    int max_threads {omp_get_max_threads()};

    #pragma omp parallel for reduction(+:madelung_constant) collapse(2)
    for (int i = -num_atoms; i <= num_atoms; ++i)
    {
        for (int j = -num_atoms; j <= num_atoms; ++j)
        {
            for (int k = -num_atoms; k <= num_atoms; ++k)
            {
                if (!(i == 0 && j == 0 && k == 0))
                {
                    double dist {std::sqrt((i * i) + (j * j) + (k * k))};
                    madelung_constant += ((i + j + k) % 2 == 0) ? 1.0 / dist : -1.0 / dist;
                }
            }
        }
    }

    double finish = omp_get_wtime();
    std::println("Wall time with {} threads: {:.3f} seconds", max_threads, finish - start);
    return std::abs(madelung_constant);
}
