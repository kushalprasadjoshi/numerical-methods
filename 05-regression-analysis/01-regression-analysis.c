# include <stdio.h>
# include <math.h>

// Define maximum size of the arrays
# define SIZE 20

// Macro to get the length of an array (for statically sized arrays)
#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof((arr)[0]))

// Enum for regression type
typedef enum {
    LINEAR = 1,
    EXPONENTIAL, // y = a * exp(bx)
    LOGARITHMIC, // y = a + b*ln(x)
    POWER        // y = a * x^b
} RegressionType;

// Global variables for regression coefficients
double slope_m = 0.0, intercept_c = 0.0;

// Function to calculate the summation of an array
double summation(double arr[], int n) {
    double sum = 0.0;
    for(int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

// Function to calculate the summation of products of two arrays
double summation_product(double arr1[], double arr2[], int n) {
    double sum = 0.0;
    for(int i = 0; i < n; i++) {
        sum += arr1[i] * arr2[i];
    }
    return sum;
}

// Function to calculate the summation of squares of an array
double summation_square(double arr[], int n) {
    double sum = 0.0;
    for(int i = 0; i < n; i++) {
        sum += arr[i] * arr[i];
    }
    return sum;
}

// Regression analysis function: fits a regression model to the data points
void regression_fit(double x[], double y[], int n, RegressionType type) {
    if (n <= 0) {
        printf("No data points provided.\n");
        return;
    }

    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    double m = 0.0, c = 0.0;

    // Arrays for transformed data (for transcendental regression)
    double X[SIZE], Y[SIZE];

    switch(type) {
        case LINEAR:
            // Linear regression: y = m*x + c
            sum_x = summation(x, n);
            sum_y = summation(y, n);
            sum_xy = summation_product(x, y, n);
            sum_x2 = summation_square(x, n);

            m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
            c = (sum_y - m * sum_x) / n;

            printf("Linear Regression: y = (%.4lf)x + (%.4lf)\n", m, c);
            break;

        case EXPONENTIAL:
            // Exponential regression: y = a * exp(bx)
            // Take ln(y) = ln(a) + b*x
            for(int i = 0; i < n; i++) {
                X[i] = x[i];
                if (y[i] <= 0) {
                    printf("Error: y[%d] <= 0, cannot take log for exponential regression.\n", i);
                    return;
                }
                Y[i] = log(y[i]);
            }
            sum_x = summation(X, n);
            sum_y = summation(Y, n);
            sum_xy = summation_product(X, Y, n);
            sum_x2 = summation_square(X, n);

            m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x); // b
            c = (sum_y - m * sum_x) / n; // ln(a)
            printf("Exponential Regression: y = (%.4lf) * exp(%.4lf * x)\n", exp(c), m);
            break;

        case LOGARITHMIC:
            // Logarithmic regression: y = a + b*ln(x)
            for(int i = 0; i < n; i++) {
                if (x[i] <= 0) {
                    printf("Error: x[%d] <= 0, cannot take log for logarithmic regression.\n", i);
                    return;
                }
                X[i] = log(x[i]);
                Y[i] = y[i];
            }
            sum_x = summation(X, n);
            sum_y = summation(Y, n);
            sum_xy = summation_product(X, Y, n);
            sum_x2 = summation_square(X, n);

            m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x); // b
            c = (sum_y - m * sum_x) / n; // a
            printf("Logarithmic Regression: y = (%.4lf) + (%.4lf) * ln(x)\n", c, m);
            break;

        case POWER:
            // Power regression: y = a * x^b
            // Take ln(y) = ln(a) + b*ln(x)
            for(int i = 0; i < n; i++) {
                if (x[i] <= 0 || y[i] <= 0) {
                    printf("Error: x[%d] <= 0 or y[%d] <= 0, cannot take log for power regression.\n", i, i);
                    return;
                }
                X[i] = log(x[i]);
                Y[i] = log(y[i]);
            }
            sum_x = summation(X, n);
            sum_y = summation(Y, n);
            sum_xy = summation_product(X, Y, n);
            sum_x2 = summation_square(X, n);

            m = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x); // b
            c = (sum_y - m * sum_x) / n; // ln(a)
            printf("Power Regression: y = (%.4lf) * x^(%.4lf)\n", exp(c), m);
            break;

        default:
            printf("Invalid regression type.\n");
            return;
    }

    // Update global variables for prediction
    slope_m = m;
    intercept_c = c;
}

// Prediction function for different regression types
double regression_predict(double x, RegressionType type) {
    switch(type) {
        case LINEAR:
            return slope_m * x + intercept_c;
        case EXPONENTIAL:
            return exp(intercept_c) * exp(slope_m * x); // y = a * exp(bx)
        case LOGARITHMIC:
            if (x <= 0) {
                printf("Error: x <= 0, cannot take log for prediction.\n");
                return NAN;
            }
            return intercept_c + slope_m * log(x); // y = a + b*ln(x)
        case POWER:
            if (x <= 0) {
                printf("Error: x <= 0, cannot take log for prediction.\n");
                return NAN;
            }
            return exp(intercept_c) * pow(x, slope_m); // y = a * x^b
        default:
            printf("Invalid regression type for prediction.\n");
            return NAN;
    }
}

// Driver function
int main() {
    double x[SIZE], y[SIZE];
    int n, choice;

    // Input number of data points
    printf("Enter the number of data points (max %d): ", SIZE);
    scanf("%d", &n);

    // Input data points
    printf("Enter the x and y values:\n");
    for(int i = 0; i < n; i++) {
        printf("x[%d]: ", i);
        scanf("%lf", &x[i]);
        printf("y[%d]: ", i);
        scanf("%lf", &y[i]);
    }

    // Select regression type
    printf("\nSelect regression type:\n");
    printf("1. Linear (y = m*x + c)\n");
    printf("2. Exponential (y = a*exp(bx))\n");
    printf("3. Logarithmic (y = a + b*ln(x))\n");
    printf("4. Power (y = a*x^b)\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    RegressionType reg_type = (RegressionType)choice;

    // Perform regression analysis (Also update global variables)
    regression_fit(x, y, n, reg_type);

    // Example prediction
    double x_predict;
    printf("\nEnter a value of x to predict y: ");
    scanf("%lf", &x_predict);
    double y_predict = regression_predict(x_predict, reg_type);
    if (!isnan(y_predict))
        printf("Predicted value of y for x = %.4lf is: %.4lf\n", x_predict, y_predict);
    else
        printf("Prediction failed due to invalid input.\n");

    return 0;
}