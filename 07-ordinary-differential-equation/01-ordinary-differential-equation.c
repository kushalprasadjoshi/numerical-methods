#include <stdio.h>
#include <math.h>

// Define function
#define f(x, y) x + y

// Enum for different methods
typedef enum
{
    RK1 = 1,
    RK2,
    RK4
} Method;

// Runge-Kutta 1st Order Method
void RK1Meth(float x0, float y0, float h, float xn)
{
    int step = 0;
    float x = x0, y = y0;
    printf("Solution using Runge-Kutta 1st Order Method:\n");
    printf("\nStep\t   x\t\t   y\t\tf(x, y)\n");
    printf("---------------------------------------------------\n");
    while (x < xn) // To include xn if x reaches it
    {
        printf("%d\t%8.4f\t%10.6f\t%10.6f\n", step, x, y, x + y);
        y = y + h * (x + y);
        x = x + h;
        step++;
    }
    printf("---------------------------------------------------\n");
    printf("Approximate value of y at x = %.4f is %.6f\n", xn, y);
}

// Runge-Kutta 2nd Order Method
void RK2Meth(float x0, float y0, float h, float xn)
{
    int step = 0;
    float x = x0, y = y0;
    printf("Solution using Runge-Kutta 2nd Order Method:\n");
    printf("\nStep\t   x\t\t   y\t\tf(x, y)\n");
    printf("---------------------------------------------------\n");
    while (x < xn) // To include xn if x reaches it
    {
        printf("%d\t%8.4f\t%10.6f\t%10.6f\n", step, x, y, x + y);
        float k1 = h * (x + y);
        float k2 = h * (x + h + (y + k1));
        y = y + 0.5 * (k1 + k2);
        x = x + h;
        step++;
    }
    printf("---------------------------------------------------\n");
    printf("Approximate value of y at x = %.4f is %.6f\n", xn, y);
}

// Runge-Kutta 4th Order Method
void RK4Meth(float x0, float y0, float h, float xn)
{
    int step = 0;
    float x = x0, y= y0;
    printf("Solution using Runge-Kutta 4th Order Method:\n");
    printf("\nStep\t   x\t\t   y\t\tf(x, y)\n");
    printf("---------------------------------------------------\n");
    while(x < xn) // To include xn if x reaches it
    {
        float k1 = h * (x + y);
        float k2 = h * (x + h / 2 + (y + k1 / 2));
        float k3 = h * (x + h / 2 + (y + k2 / 2));
        float k4 = h * (x + h + (y + k3));
        printf("%d\t%8.4f\t%10.6f\t%10.6f\n", step, x, y, x + y);
        y = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        x = x + h;
        step++;
    }
}

// Driver code
int main()
{
    float x0 = 0, y0 = 1, h = 0.2, xn;
    printf("Enter the value of x at which you want to find y: ");
    scanf("%f", &xn);

    // Select method
    Method choice;
    printf("Select method:\n");
    printf("1. Runge-Kutta 1st Order\n");
    printf("2. Runge-Kutta 2nd Order\n");
    printf("3. Runge-Kutta 4th Order\n");
    scanf("%d", &choice);

    switch (choice) // Switch statement to select method
    {
    case 1:
        RK1Meth(x0, y0, h, xn);
        break;
    case 2:
        RK2Meth(x0, y0, h, xn);
        break;
    case 3:
        RK4Meth(x0, y0, h, xn);
        break;

    default:
        printf("Invalid choice. Please select a valid method.\n");
        break;
    }

    return 0;
}

