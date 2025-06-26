#include <stdio.h>
#include <math.h>

// Define the function to integrate here
double f(double x) {
    // Example: integrate sin(x)
    return sin(x);
}

// Romberg integration function
double romberg(double (*func)(double), double a, double b, int n) {
    double R[n][n];
    int i, j, k;
    double h = b - a;

    // R[i][0]
    for (i = 0; i < n; i++) {
        int N = 1 << i; // 2^i
        double sum = 0.0;
        double step = h / N;
        for (k = 1; k < N; k += 2) {
            sum += func(a + k * step);
        }
        if (i == 0)
            R[i][0] = (func(a) + func(b)) * h / 2.0;
        else
            R[i][0] = 0.5 * R[i-1][0] + sum * step;
    }

    // Richardson extrapolation
    for (i = 1; i < n; i++) {
        for (j = 1; j <= i; j++) {
            R[i][j] = R[i][j-1] + (R[i][j-1] - R[i-1][j-1]) / (pow(4, j) - 1);
        }
    }

    return R[n-1][n-1];
}

int main() {
    double a, b;
    int n;

    printf("Enter lower limit a: ");
    scanf("%lf", &a);
    printf("Enter upper limit b: ");
    scanf("%lf", &b);
    printf("Enter number of levels (e.g., 4 or 5): ");
    scanf("%d", &n);

    double result = romberg(f, a, b, n);
    printf("Romberg integration result: %.10lf\n", result);

    return 0;
}