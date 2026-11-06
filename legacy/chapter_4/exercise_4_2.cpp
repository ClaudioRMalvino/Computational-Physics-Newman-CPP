/**
 * Exercise 4.2: Quadratic Equations
 *
 *
 * Textbook: Computational Physics by Mark Newman
 */


#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include <sstream>

// Function Declaration

/**
 * Function calculates the solutions for the quadratic equation with numerical
 * errors due to accuracy and precision.
 *
 * @param discriminant the discriminant of the quadratic equation
 * a*x^2 + b*x + c = 0
 * @param a
 * @param b
 * @param c
 *
 * @return a tuple of two pairs, each pair containing the solutions for the
 * standard quadratic formula and the alternative quadratic formula respectively.
 */
std::pair<std::pair<double, double>, std::pair<double, double>>
quadratic_eq_witherror( double discriminant,
                        double a,
                        double b,
                        double c);

/**
 * Function calculates the solutions for the quadratic equation without
 * numerical errors due to accuracy and precision.
 *
 * @param discriminant the discriminant of the quadratic equation
 * a*x^2 + b*x + c = 0
 * @param a
 * @param b
 * @param c
 *
 * @return a std::pair containing the solutions for without numerical errors
 */
std::pair<double, double> quadratic_eq(
                                double discriminant,
                                double a,
                                double b,
                                double c);

/**
 *
 * @return a tuple of strings containing the input prompt for the coefficiants
 * a, b, and c of the quadratic equation.
 */
std::tuple<std::string, std::string, std::string> input_prompt();

/**
 * Function prints the results of the calculations.
 *
 * @param standard_with_error a pair containing the solutions for the standard
 * quadratic formula with numerical errors
 * @param alt_with_error a pair containing the solutions for the alternative
 * quadratic formula with numerical errors
 * @param solution_without_error a pair containing the solutions for the
 */
void print_results( std::pair<double, double> standard_with_error,
                    std::pair<double, double> alt_with_error,
                    std::pair<double, double> solution_without_error);

/**
 * Function checks if the discriminant is real or imaginary and then returns
 * the value if it is real
 * 
 * @param a
 * @param b
 * @param c
 *
 * @return the value of the discriminant if it is real, otherwise it throws a
 * runtime error
 */
double checkAndCalculate_discriminant(double a, double b, double c);

int main()
{
    std::cout << "Quadratic Equation Calculator" << '\n';

    while (true)
    {
        auto [a, b, c] { input_prompt() };
        if (a == "q" || b == "q" || c == "q")
        {
            break;
        }
        // Convert the input strings to doubles
        double a_val { std::stod(a) };
        double b_val { std::stod(b) };
        double c_val { std::stod(c) };
        const double discriminant { checkAndCalculate_discriminant(a_val, b_val, c_val) };
        auto [standard_with_error, alt_with_error] {
            quadratic_eq_witherror(discriminant, a_val, b_val, c_val)
        };

        auto solution_without_error {
            quadratic_eq(discriminant, a_val, b_val, c_val)
        };

        print_results(  standard_with_error,
                        alt_with_error,
                        solution_without_error);
    }


    return 0;
}

// Function Definition

std::pair<std::pair<double, double>, std::pair<double, double>>
quadratic_eq_witherror( double discriminant,
                        double a,
                        double b,
                        double c)
{

    double sqrd_discriminant { std::sqrt(discriminant) };
    double two_a { 2 * a };
    double two_c { 2 * c };
    
    // Solutions for the standard quadratic formula
    double x00 { (-b + sqrd_discriminant) / (two_a) };
    double x01 { (-b - sqrd_discriminant) / (two_a) };

    // Solutions for the alternative quadratic formula
    double x10 { two_c / (-b - sqrd_discriminant) };
    double x11 { two_c / (-b + sqrd_discriminant) };

    std::pair standard_with_error { x00, x01 };
    std::pair alt_with_error { x10, x11 };

    return std::pair(standard_with_error, alt_with_error);
}

std::pair<double, double> quadratic_eq(double discriminant,
                                double a,
                                double b,
                                double c)
{

    double x1 {};
    double x2 {};
    double two_a { 2 * a };
    double sqrd_discriminant { std::sqrt(discriminant) };
    double two_c { 2 * c };
    
    if (b >= 0)
    {
        // Use standard formula for the first root
        x1 = (-b - sqrd_discriminant ) / (two_a);
        // Use the alternatice formula for the second root
        x2 = (two_c) / (-b - sqrd_discriminant);
    } else
    {
        // Use the alternative formula for the first root
        x1 = (two_c )/ (-b + sqrd_discriminant);
        x2 = (-b + sqrd_discriminant) / (two_a);
    }
    return std::pair(x1, x2);
}

std::tuple<std::string, std::string, std::string> input_prompt()
{
    std::cout << "Input the coefficients a, b, and c of the quadratic equation"
              << " in the form a b c" << '\n';
    std::cout << "a, b, and c must be real numbers" << '\n';
    std::cout << "a, b, and c must be separated by spaces" << '\n';
    std::cout << "Input 'q' to quit" << '\n';

    std::string line;
    std::getline(std::cin, line);
    
    std::istringstream iss(line);
    std::string a, b, c;
    iss >> a >> b >> c;
    
    return std::make_tuple(a, b, c);
}

void print_results(std::pair<double, double> standard_with_error,
                   std::pair<double, double> alt_with_error,
                   std::pair<double, double> solution_without_error)
{
    std::cout << std::setprecision(8) << "Solutions with errors" << '\n';
    std::cout << "Standard formula: x = [" << standard_with_error.first << ", "
              << standard_with_error.second << "]" << '\n'
              << "Alternative Formula: x = [" << alt_with_error.first << ", "
              << alt_with_error.second << "]" << '\n';
    std::cout << "Solutions without errors \n"
              << "x = [" << solution_without_error.first << ", "
              << solution_without_error.second << "]" << '\n';
}

double checkAndCalculate_discriminant(double a, double b, double c)
{
    double discriminant { b * b - 4 * a * c };

    if (discriminant < 0)
    {
        std::runtime_error("The discriminant can't be negative");
    }
    if (discriminant == 0)
    {
        std::runtime_error("The discriminant can't be zero");
    }

    return discriminant;
}