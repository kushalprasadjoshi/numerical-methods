#include <stdio.h>
#include <math.h>

# define N 1000 // Number of subintervals for numerical integration

// Function to calculate the integral of a function using the trapezoidal rule
double trapezoidal_rule(double (*f)(double), double a, double b, int n) {
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    
    for (int i = 1; i < n; i++) {
        sum += f(a + i * h);
    }
    
    return sum * h;
}

// Function to calculate the integral of a function using Simpson's 1/3 rule
double simpsons_13_rule(double (*f)(double), double a, double b, int n) {
    if (n % 2 != 0) {
        n++; // n must be even for Simpson's rule
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    
    for (int i = 1; i < n; i++) {
        if (i % 2 == 0) {
            sum += 2 * f(a + i * h);
        } else {
            sum += 4 * f(a + i * h);
        }
    }
    
    return sum * h / 3;
}

// Function to calculate the integral of a function using Simpson's 3/8 rule
double simpsons_38_rule(double (*f)(double), double a, double b, int n) {
    if (n % 3 != 0) {
        n += 3 - (n % 3); // n must be a multiple of 3 for Simpson's 3/8 rule
    }
    double h = (b - a) / n;
    double sum = f(a) + f(b);
    
    for (int i = 1; i < n; i++) {
        if (i % 3 == 0) {
            sum += 2 * f(a + i * h);
        } else {
            sum += 3 * f(a + i * h);
        }
    }
    
    return sum * h * 3 / 8;
}

// Example function to integrate
double example_function(double x) {
    return 1 / x; // Example: f(x) = 1/x, note this function is not defined at x = 0
}

// Main function
int main() {
    double a = 1.0; // Lower limit of integration
    double b = 2.0; // Upper limit of integration
    int n = N;    // Number of subintervals

    // Calculate the integral using the all rules
    double trapezoidal_result = trapezoidal_rule(example_function, a, b, n);
    double simpson_13_result = simpsons_13_rule(example_function, a, b, n);
    double simpson_38_result = simpsons_38_rule(example_function, a, b, n);
    
    // Print the result
    printf("The integral of f(x) from %.2f to %.2f is approximately:\n", a, b);
    printf("1. Trapezoidal Rule: %.6f\n", trapezoidal_result);
    printf("2. Simpson 1/3 Rule: %.6f\n", trapezoidal_result);
    printf("3. Simpson 3/8 Rule: %.6f\n", trapezoidal_result);
    
    return 0;
}