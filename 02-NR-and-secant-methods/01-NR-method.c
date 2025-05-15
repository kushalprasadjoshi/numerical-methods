#include <stdio.h>
#include <math.h>

#define TOLERANCE 0.001
#define MAX_ITERATIONS 1000

// Calculatet the value of the function
double f(double x)
{
    return x * x - x - 1; // Example function: f(x) = x^2 - x - 1
}

// Calculate the derivative of the function
double f_prime(double x)
{
    return 2 * x - 1; // Derivative of the function: f'(x) = 2x - 1
}

// Newton-Raphson method
double newton_raphson(double initial_guess)
{
    double x0 = initial_guess;
    double x1;
    int iterations = 0;

    // Print the header for the table
    printf("\nNewton-Raphson Method\n");
    printf("Iteration\t x\t\t f(x)\t\t f'(x)\n");
    printf("----------------------------------------------------------\n");

    while (iterations < MAX_ITERATIONS)
    {
        double fx0 = f(x0);
        double fpx0 = f_prime(x0);

        if (fabs(fx0) < TOLERANCE)
        {
            return x0; // Root found
        }

        if (fabs(fpx0) < TOLERANCE)
        {
            printf("Derivative is too small. No solution found.\n");
            return NAN; // Derivative is too small, no solution found
        }

        x1 = x0 - fx0 / fpx0; // Update the guess

        x0 = x1; // Update the guess for the next iteration
        iterations++;

        // Print the current details in table format
        printf("%d \t\t%.6lf, \t%.6lf, \t%.6lf\n", iterations, x0, fx0, fpx0);
    }

    printf("Maximum iterations reached. No solution found.\n");
    return NAN; // Maximum iterations reached, no solution found
}

// Driver method
int main(int argc, char const *argv[])
{
    double initial_guess;

    // Get the initial guess from the user - Ensure derivative is not zero
    do
    {
        printf("Enter an initial guess: ");
        scanf("%lf", &initial_guess);

        // Check if the derivative at the initial guess is zero
        if (f_prime(initial_guess) == 0)
        {
            printf("The derivative at the initial guess is zero. Please enter a different guess.\n");
            continue; // Ask for a new guess
        }
        else
        {
            printf("Initial guess accepted: %lf\n", initial_guess);
            break; // Valid initial guess
        }
    } while (1);

    // Call the Newton-Raphson method
    double root = newton_raphson(initial_guess);

    // Print the footer of the table
    printf("----------------------------------------------------------\n");
    if (!isnan(root))
    {
        printf("Root found: %lf\n", root);
    }
    else
    {
        printf("No root found.\n");
    }

    return 0;
}
