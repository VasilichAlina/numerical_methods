#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double fact(int x)
{
    if (x == 0 || x == 1) return 1.0;

    double p = 1.0;
    for (int i = 2; i <= x; i++)
    {
        p *= i;
    }
    return p;
}

double func(double x)
{
    const double sqrt_pi = sqrt(3.1415); 
    const double k = 2.0 / sqrt_pi;

    int n = 0;
    double sum = 0.0;
    double term;

    while (true)
    {
        term = (pow(-1, n) * pow(x, 2 * n + 1)) / (fact(n) * (2 * n + 1));
        double prev_sum = sum;
        sum += term;

        if (prev_sum == sum) break;
        n++;

        if (n > 1000) {
            cout << "Достигнут лимит итераций для x = " << x << endl;
            break;
        }
    }
    return k * sum;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(10);  

    double test_x[] = { 0.5, 1.0, 5.0, 10.0 };

    for (int i = 0; i < 4; i++)
    {
        double myfunc = func(test_x[i]);
        double realfunc = erf(test_x[i]);

        cout << endl;
        cout << "x = " << test_x[i] << endl;
        cout << "Мой erf:   " << myfunc << endl;
        cout << "Точный erf: " << realfunc << endl;
        cout << "Погрешность: " << scientific << (myfunc - realfunc) << fixed << endl;
    }

    cout << "для x >= 5 погрешность большая из-за ошибок округления" << endl;

    return 0;
}