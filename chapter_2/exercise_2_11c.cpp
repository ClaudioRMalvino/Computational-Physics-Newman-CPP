/**
* @file exercise_2_11c.cpp
* @brief Exercise 2.11: Binomial Coefficients part c)
*
* From: Computational Physics by Mark Newman
*/


#include <cmath>
#include <iomanip>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>


//Function Declaration

/**
 * @brief Function takes an vector array of double type values and calculates
 * the sum of all values in the vector array.
 *
 * @param arr: An vector array of doubles
 *
 * @return The sum of all elements in the vector array
 */

double sum(std::vector<double> &arr);

/**
 * @brief Calculates the factorial of an integer
 *
 * @params x: The integer to calculate factorial for
 *
 * @return
 *  x!
 */
double factorial(int x);

/**
 * @brief Calculates the binomial coefficient (n choose k)
 *
 * @param n: The total number of items
 * @param k: The number of items to choose
 *
 * @return The bionomial coefficient (n choose k)
 */
double binomial_coefficient(int n, int k);

/**
 * @brief Function calculates the probability that an unbiased coin tossed
 * n times wil come up heads or tails k times
 *
 * @param num_tosses: The number of simulated tosses of the coin
 * @param target: The number of times the coin will come up heads or tails
 *
 * @return Probability of getting heads or tails K or more times
 */
double unbiased_coin_toss(int num_tosses, int target);

/**
 * @brief Function calculates the probability that it comes up heads or tails
 * K or more times
 *
 * @param num_tosses: The number of simulated tosses of the coin
 * @param target: The number of times the coin will come up head/tails K num
 * of times
 *
 * @return Probability of getting heads or tails K or more times
 */
double prob_k_or_more(int num_tosses, int target);

/**
 * @brief Prompts for and reads the value of total number of
 * tosses from user input
 *
 * @return The input string (which may be a number or 'q' to quit)
 */
std::string get_num_tosses();

/**
 * @brief Prompts for and reads the value of the total number of target
 * heads or tails from user input
 *
 * @return The input string (which may be a number or 'q' to quit)
 */
std::string get_target();

/**
 * @brief Checks if the input values num_tosses and target are valid
 *
 * (* - see above for parameter definition)
 * @param num_tosses *
 * @param target *
 *
 * @throws std::runtime_error if inputs are invalid
 */
void check_values(int num_tosses, int target);

/**
 * @brief Prints results of unbiased_coin_toss and prob_k_or_more
 */
void print_results(double probability1,
                   double probability2,
                   int num_tosses,
                   int target);

int main()
{
    std::cout << "Unbiased Coin Toss Simulator" << '\n'
              << "Input 'q' to quit" << '\n';

    while (true)
    {
        const std::string num_tosses_input{get_num_tosses()};
        if (num_tosses_input == "q")
        {
            break;
        }

        const std::string target_input{get_target()};
        if (target_input == "q")
        {
            break;
        }

        const int num_tosses{std::stoi(num_tosses_input)};
        const int target{std::stoi(target_input)};

        try
        {
            check_values(num_tosses, target);

            const double prob1{unbiased_coin_toss(num_tosses, target)};
            const double prob2{prob_k_or_more(num_tosses, target)};

            print_results(prob1, prob2, num_tosses, target);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please try again." << '\n';
        }
    }
    return 0;
}

// Function Definitions

double sum(std::vector<double> &arr)
{
    double result = 0.0;
    for (double num : arr)
    {
        result += num;
    }

    return result;
}

double factorial(int x)
{
    double value = 1.0;
    for (int i : std::views::iota(1, x + 1))
    {
        value *= i;
    }
    return value;
}

double binomial_coefficient(int n, int k)
{
    if (k == 0)
    {
        return 1;
    }
    const double numerator{factorial(n)};
    const double denominator{factorial(k) * factorial(n - k)};
    const double binomial_coef{numerator / denominator};

    return binomial_coef;
}


double unbiased_coin_toss(int num_tosses, int target)
{
    const double probability{binomial_coefficient(num_tosses, target) *
                       (std::pow(0.5, num_tosses))};
    return probability;
}

double prob_k_or_more(int num_tosses, int K)
{
    std::vector<double> values;

    for (int i : std::views::iota(K, num_tosses + 1))
    {
        values.push_back(unbiased_coin_toss(num_tosses, i));
    }

    const double probability = sum(values);

    return probability;
}

std::string get_num_tosses()
{
    std::cout << "Input number of coin tosses: ";

    std::string input{};
    std::cin >> input;

    return input;
}

std::string get_target()
{
    std::cout << "Input number of desired heads/tails: ";

    std::string input{};
    std::cin >> input;

    return input;
}

void check_values(int num_tosses, int target)
{
    if (num_tosses <= 0)
    {
        throw std::runtime_error("number of tosses must be > 0");
    }

    if (target <= 0)
    {
        throw std::runtime_error("number of desired heads/tails must be > 0");
    }
}

void print_results(double probability1,
                   double probability2,
                   int num_tosses,
                   int target)
{
    std::cout << std::setprecision(3) << '\n'
              << "Probability of " << target << " heads/tails out of "
              << num_tosses << " tosses: " << (probability1 * 100.0) << "%";

    std::cout << "Probability of getting heads/tails " << target
              << " times or more: " << (probability2 * 100.0) << "%" << '\n';
}
