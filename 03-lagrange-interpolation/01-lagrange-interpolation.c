# include <stdio.h>

# define N 10

// Function to perform Lagrange interpolation
float lagrange_interpolation(float x[], float y[], int n, float xp) {
    float L[N];
    float yp = 0.0f;
    for (int i = 0; i < n; i++) {
        L[i] = 1.0f;
        for (int j = 0; j < n; j++) {
            if (j != i) {
                L[i] *= (xp - x[j]) / (x[i] - x[j]);
            }
        }
        yp += y[i] * L[i];
    }

    // Print the Lagrange basis polynomials
    printf("Lagrange basis polynomials:\n");
    for (int i = 0; i < n; i++)
    {
        printf("L[%d] = %.2f\n", i, L[i]);
    }
    
    return yp;
}

// Main function
int main(int argc, char const *argv[])
{
    float x[N], y[N], xp, yp;
    int i, j, n;

    printf("Enter the number of data points: ");
    scanf("%d", &n);

    printf("Enter the data points (x y):\n");
    for (i = 0; i < n; i++)
    {
        scanf("%f %f", &x[i], &y[i]);
    }

    printf("Enter the value of x for interpolation: ");
    scanf("%f", &xp);

    yp = lagrange_interpolation(x, y, n, xp);
    printf("\nThe interpolated value at x = %.2f is y = %.2f\n", xp, yp);

    return 0;
}
