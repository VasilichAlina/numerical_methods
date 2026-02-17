#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double compute_s(double x, double epsilon = 3e-8)
{
    double sum = 0.0;
    double term;
    int k = 1;

    while (true)
    {
        double k3 = pow(static_cast<double>(k), 3);
        double sqrt_plus = sqrt(k3 + x);
        double sqrt_minus = sqrt(k3 - x);

        term = -2.0 * x / (sqrt(k3 * k3 - x * x) * (sqrt_minus + sqrt_plus));

        double prev_sum = sum;
        sum += term;

        if (abs(term) < epsilon && k > 100) break;
        if (prev_sum == sum) break;

        k++;

        if (k > 1000000) {
            cout << "Достигнут лимит итераций для x = " << x << endl;
            break;
        }
    }

    cout << "Потребовалось членов ряда: " << k << endl;
    return sum;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(10);

    double x_values[] = { 0.5, 0.999999999 };

    for (int i = 0; i < 2; i++)
    {
        double x = x_values[i];


        double result = compute_s(x);

        cout << "s(x) = " << x_values[i] << result << endl;
    }
}