#include <stdio.h>
#include <math.h>

#define SIZE 10 // Size of the array
#define TOLERANCE 0.00001 // Tolerance for  comparison of successive iterations
#define MAX_ITERATIONS 1000 // Maximum number of iterations for convergence

// Macro to find the array size
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Function to find the maximum value in a vetor
double max_absolute_value(const double arr[SIZE], size_t size) {
    double max_val = fabs(arr[0]);
    for (size_t i = 1; i < size; i++) {
        if (fabs(arr[i]) > max_val) {
            max_val = fabs(arr[i]);
        }
    }
    return max_val;
}

// Function to user input a square matrix
void inputMatrix(double A[SIZE][SIZE], size_t size) {
    printf("Enter the elements of the matrix (%zu x %zu):\n", size, size);
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            scanf("%lf", &A[i][j]);
        }
    }
}

// Function to user input an initial guess for the eigenvector
void inputInitialGuess(double X[SIZE], size_t size) {
    printf("Enter the initial guess for the eigenvector (size %zu):\n", size);
    for (size_t i = 0; i < size; i++) {
        scanf("%lf", &X[i]);
    }
}

// Function for matrix-vector multiplication
void matrixVectorMultiply(const double A[SIZE][SIZE], const double X[SIZE], double Y[SIZE], size_t size) {
    for (size_t i = 0; i < size; i++) {
        Y[i] = 0.0f;
        for (size_t j = 0; j < size; j++) {
            Y[i] += A[i][j] * X[j];
        }
    }
}

// Function to normalize a matrix
void normalize(double X[SIZE], size_t size) {
    // Find the maximum absolute value in the vector
    double max_val = max_absolute_value(X, size);
    if (max_val == 0.0) return; // Avoid division by zero
    for (size_t i = 0; i < size; i++) {
        X[i] /= max_val;
    }
}

// Power method to find the dominant eigenvalue and eigenvector
void powerMethod(const double A[SIZE][SIZE], double X[SIZE], size_t size  ) {
    double Y[SIZE];
    int iterations = 0;

    printf("***************************************************************************\n");
    printf("Power Method to find the dominant eigenvalue and eigenvector:\n");

    // Iterate until convergence or maximum iterations reached
    while (iterations < MAX_ITERATIONS) {
        // Multiply the matrix A with the vector X
        matrixVectorMultiply(A, X, Y, size);

        // Find the value of lambda (dominant eigenvalue)
        double lambda = max_absolute_value(Y, size);

        // Normalize the resulting vector Y
        normalize(Y, size);

        // Print the current iteration and the resulting vector in table format
        printf("Iteration %d: ", iterations + 1);
        for (size_t i = 0; i < size; i++) {
            printf("%lf ", Y[i]);
        }
        printf("\t: lambda = %lf", lambda);
        printf("\n");

        // Check for convergence
        double norm_diff = 0.0f;
        for (size_t i = 0; i < size; i++) {
            norm_diff += fabs(Y[i] - X[i]);
        }

        // If the change is within the tolerance, we have converged
        if (norm_diff < TOLERANCE) {
            break;
        }

        // Update X to be the new vector Y
        for (size_t i = 0; i < size; i++) {
            X[i] = Y[i];
        }

        iterations++;
    }

    printf("***************************************************************************\n");

    printf("Converged after %d iterations.\n", iterations);
    printf("Dominant eigenvector:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%lf ", X[i]);
    }
    printf("\n");
}

// Driver code
int main(int argc, char const *argv[])
{
    double A[SIZE][SIZE], X[SIZE], Y[SIZE];
    int n;
    // Take user input for the size of the matrix
    printf("Enter the size of the matrix (max %d): ", SIZE);
    scanf("%d", &n);

    // Check if the user provided a valid size for the matrix
    if (n > SIZE || n <= 0) {
        printf("Invalid size. Please enter a value between 1 and %d.\n", SIZE);
        return 1;
    }   
    
    // Input the matrix
    inputMatrix(A, n);

    // Initialize the first guess for the eigenvector
    inputInitialGuess(X, n);

    // Perform the power method to find the dominant eigenvalue and eigenvector
    powerMethod(A, X, n);

    return 0;
}

