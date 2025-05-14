#include <stdio.h>
#include <math.h>
#define TOLERANCE 0.0001

double f(double x)
{
    // function: f(x) = x^2 - x - 2
    return x * x - x - 2;

    // function: f(x) = x - e^-x
    // return x - exp(-x);

    // function: f(x) = x e^x - cos(x)
    // return x * exp(x) - cos(x);

    // function: f(x) = x log10(x) - 1.2
    // return x * log10(x) - 1.2;
}

int main(int argc, char const *argv[])
{
    double a, b, x, fa, fb, fx; // Initial guesses and function values
    int iter = 0;                // Iteration counter

    // Get the initial valid guesses from the user
    while (1)
    {
        // Input the initial guesses
        printf("\nEnter the initial guesses a and b: ");
        scanf("%lf %lf", &a, &b);

        // Get the function values at the initial guesses
        fa = f(a);
        fb = f(b);

        // Check if the initial guesses are valid
        if (fa * fb > 0)
        {
            printf("Invalid initial guesses. f(a) and f(b) must have opposite signs.\n");
        }
        else
        {
            printf("Valid initial guesses.\n");
            break;
        }
    }

    // False position method
    printf("\nFalse Position Method:\n");
    printf("Iteration\t a\t\t b\t\t x\t\t f(x)\t\t |f(x)|\n");
    printf("------------------------------------------------------------------------------------------\n");
    do
    {
        // Calculate the midpoint
        x = (a * fb - b * fa) / (fb - fa);
        fx = f(x);

        // Print the current iteration values
        printf("%d\t\t %.6f\t %.6f\t %.6f\t %.6f\t %.6f\n", iter, a, b, x, fx, fabs(fx));

        // Check if the root is found or if the tolerance is met
        if (fabs(fx) < TOLERANCE || fabs(b - a) < TOLERANCE)
            break;

        // Update the guesses based on the function values
        if (fa * fx < 0)
        {
            b = x;
            fb = fx;
        }
        else
        {
            a = x;
            fa = fx;
        }

        iter++;

    } while (1);

    printf("------------------------------------------------------------------------------------------\n");
    // Print the final result
    printf("Root found: x = %.6f, f(x) = %.6f\n", x, fx);

    return 0;
}
