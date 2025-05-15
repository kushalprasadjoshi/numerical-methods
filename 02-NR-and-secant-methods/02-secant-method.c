#include <stdio.h>
#include <math.h>

#define TOLERANCE 0.001
#define MAX_ITERATIONS 1000

// Calculatet the value of the function
double f(double x)
{
    return x * x - x - 1; // Example function: f(x) = x^2 - x - 1
}

// Secant method
double secant(double a, double b)
{
    double x0 = a;
    double x1 = b;
    double x2;
    int iterations = 0;

    // Print the header for the table
    printf("\nSecant Method\n");
    printf("Iteration\t x0\t\t x1\t\t f(x0)\t\t f(x1)\t\t x2\t\t f(x2)\n");
    printf("-----------------------------------------------------------------------------------------------------------\n");

    while (iterations < MAX_ITERATIONS)
    {
        double fx0 = f(x0);
        double fx1 = f(x1);

        if (fabs(fx1) < TOLERANCE)
        {
            return x1; // Root found
        }

        x2 = (x0 * fx1 - x1 * fx0) / (fx1 - fx0); // Update the guess

        x0 = x1; // Update the guess for the next iteration
        x1 = x2; // Update the guess for the next iteration
        iterations++;

        // Print the current details in table format
        printf("%d \t\t%.6lf\t%.6lf\t%.6lf\t%.6lf\t%.6lf\t%.6lf\n", iterations, x0, x1, fx0, fx1, x2, f(x2));
    }

    printf("Maximum iterations reached. No solution found.\n");
    return NAN; // Maximum iterations reached, no solution found
}

// Driver method
int main(int argc, char const *argv[])
{
    double a, b;

    // Get the initial guess from the user - Ensure derivative is not zero
    do
    {
        printf("Enter initial guesses (a b): ");
        scanf("%lf %lf", &a, &b);

        // Check if 
        if (f(a) == f(b))
        {
            printf("Invalid initial guesses. Denominator can't be zero.\n");
            continue; // Ask for a new guess
        }
        else {
            printf("Initial guesses accepted: %lf, %lf\n", a, b);
            break; // Valid initial guess
        }
    } while (1);

    // Call the Secant method
    double root = secant(a, b);

    // Print the footer of the table
    printf("-----------------------------------------------------------------------------------------------------------\n");
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
