/**
 * Exercise 2.12: Prime Numbers
 *
 * Textbook: Computational Physics by Mark Newman
 */

#include <iostream>
#include <stdexcept>
#include <vector>

//Function Declaration

/**
 * @brief: Function constructs a vector of prime numbers [3, max_prime_number]
 *
 * @param: integer number to construct range [3, max_prime_number]
 *
 * @return: vector of integer type prime numbers
 */

std::vector<int> prime_numbers(int max_prime_numbers);

/**
 * @brief Takes user input for the argument of prime_numbers();
 *
 * @return The input string (which may be a number or 'q' to quit)
 */

std::string get_max_prime_number();

/**
 * @brief Checks if the input value is valid
 *
 * (* - see above for parameter definition)
 * @param max_prime_number *
 *
 * @throws std::runtime_error if input is invalid
 */

void check_value(int max_prime_number);

/**
 * @brief: Prints all the elements within prime_numbers()
 *
 * @param: std::vector<int> primes
 */
void print_primes(const std::vector<int> &primes);

int main()
{
    std::cout << "Prime Number Sieve";
    std::cout << "Input 'q' to quit" << '\n';

    while (true)
    {
        auto max_prime_number_input{get_max_prime_number()};
        if (max_prime_number_input == "q")
        {
            break;
        }

        int max_prime_number{std::stoi(max_prime_number_input)};

        try
        {
            check_value(max_prime_number);
            auto primes{prime_numbers(max_prime_number)};

            print_primes(primes);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Invalid input. Please try again." << '\n';
        }
    }
    return 0;
}

//Function Definitions

std::vector<int> prime_numbers(int max_prime_number)
{
    std::vector<int> primes;
    primes.push_back(2);

    for (int i = 3; i <= max_prime_number; ++i)
    {
        bool is_prime{true};
        for (int prime : primes)
        {
            if (i % prime == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
        {
            primes.push_back(i);
        }
    }
    return primes;
}

std::string get_max_prime_number()
{
    std::cout << "Input maximum range of prime numbers to print, [3, input]: ";

    std::string input{};
    std::cin >> input;

    std::cout << '\n';

    return input;
}

void check_value(int max_prime_number)
{
    if (max_prime_number <= 3)
    {
        throw std::runtime_error("Maximum prime must be > 3");
    }
}

void print_primes(const std::vector<int> &primes)
{
    for (const int prime : primes)
    {
        std::cout << prime << " ";
    }
    std::cout << '\n';
}
