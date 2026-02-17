#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;
const double PI = 3.141592653589793;  

double direct_sum(int N, double& last_term)
{
    double sum = 0.0;
    for (int n = 1; n <= N; n++)
    {
        last_term = 1.0 / (n * n + 1);
        sum += last_term;
    }
    return sum;
}

double transformed_sum(double epsilon, int& terms_used) 
{
    const double PI2_6 = PI * PI / 6.0;
    const double PI4_90 = pow(PI, 4) / 90.0;

    double sum_correction = 0.0;
    int n = 1;
    terms_used = 0;

    while (true)
    {
        double term = 1.0 / (n * n * n * n * (n * n + 1.0));
        double prev_sum = sum_correction;
        sum_correction += term;
        terms_used++;

        if (abs(term) < epsilon) break;
        if (prev_sum == sum_correction) break;

        n++;
        if (n > 10000) break;
    }

    return (PI2_6 - PI4_90) + sum_correction;
}

double exact_value()
{
    double e_pi = exp(PI);
    double e_minus_pi = exp(-PI);
    double coth_pi = (e_pi + e_minus_pi) / (e_pi - e_minus_pi);
    return (PI * coth_pi - 1.0) / 2.0;
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(12);

    double epsilon = 1e-10;
    double exact = exact_value();

    cout << "Прямое суммирование:" << endl;
    double last;
    double sum_direct = direct_sum(1000000, last);
    cout << "  Членов: 1 000 000" << endl;
    cout << "  Последний член: " << scientific << last << fixed << endl;
    cout << "  Сумма: " << sum_direct << endl;
    cout << "  Погрешность: " << scientific << (sum_direct - exact) << fixed << endl << endl;

    cout << "Преобразованное суммирование:" << endl;
    int terms;
    double sum_trans = transformed_sum(epsilon, terms);
    cout << "  Членов поправки: " << terms << endl;
    cout << "  Сумма: " << sum_trans << endl;
    cout << "  Точное значение: " << exact << endl;
    cout << "  Погрешность: " << scientific << (sum_trans - exact) << fixed << endl << endl;

    cout << "Сравнение скорости сходимости:" << endl;
    cout << "  Исходный ряд:     > 1000000 членов" << endl;
    cout << "  Преобразованный:  " << terms << " членов" << endl;
    cout << "  Ускорение:        в " << 1e10 / terms << " раз" << endl;


}