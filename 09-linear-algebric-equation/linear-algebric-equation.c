/*
Solution of Linear Algebraic Equation using Gauss Jacobi and Gauss Seidel Method

Equations:
4x1 + x2 + 2x3 = 4
3x1 + 5x2 + x3 = 7
x1 + x2 + 3x3 = 3
*/

#include <stdio.h>
#include <math.h>

// Maximum number of iterations
#define MAX_ITR 100
// Tolerance for convergence
#define tol 0.001

// Functions representing rearranged equations for iterative methods
#define f1(x1, x2, x3) (4 - x2 - 2 * x3) / 4
#define f2(x1, x2, x3) (7 - 3 * x1 - x3) / 5
#define f3(x1, x2, x3) (3 - x1 - x2) / 3

// Function to solve using Gauss-Jacobi Method
void Gauss_jacobi(float x10, float x20, float x30)
{
    float x1, x2, x3;
    int itr = 0;

    printf("\n--- Gauss-Jacobi Method ---\n");
    printf("Iteration\t x1\t\t x2\t\t x3\n");

    // Iterative process
    do
    {
        // Calculate new values using previous iteration values
        x1 = f1(x10, x20, x30);
        x2 = f2(x10, x20, x30);
        x3 = f3(x10, x20, x30);

        // Print current iteration results
        printf("%d\t\t %.4f\t %.4f\t %.4f\n", itr + 1, x1, x2, x3);

        // Check for convergence
        if (fabs(x1 - x10) < tol && fabs(x2 - x20) < tol && fabs(x3 - x30) < tol)
            break;

        // Update values for next iteration
        x10 = x1;
        x20 = x2;
        x30 = x3;
        itr++;
    } while (itr < MAX_ITR);
}

// Function to solve using Gauss-Seidel Method
void Gauss_seidel(float x10, float x20, float x30)
{
    float x1, x2, x3;
    int itr = 0;

    printf("\n--- Gauss-Seidel Method ---\n");
    printf("Iteration\t x1\t\t x2\t\t x3\n");

    // Iterative process
    do
    {
        // Calculate new values using the most recent updates
        x1 = f1(x10, x20, x30);
        x2 = f2(x1, x20, x30);   // Use updated x1
        x3 = f3(x1, x2, x30);    // Use updated x1 and x2

        // Print current iteration results
        printf("%d\t\t %.4f\t %.4f\t %.4f\n", itr + 1, x1, x2, x3);

        // Check for convergence
        if (fabs(x1 - x10) < tol && fabs(x2 - x20) < tol && fabs(x3 - x30) < tol)
            break;

        // Update values for next iteration
        x10 = x1;
        x20 = x2;
        x30 = x3;
        itr++;
    } while (itr < MAX_ITR);
}

int main()
{
    float x10, x20, x30;

    // Input initial guesses from user
    printf("\nEnter the initial guesses: ");
    scanf("%f%f%f", &x10, &x20, &x30);

    // Call Gauss-Jacobi method
    Gauss_jacobi(x10, x20, x30);

    // Call Gauss-Seidel method
    Gauss_seidel(x10, x20, x30);

    return 0;
}