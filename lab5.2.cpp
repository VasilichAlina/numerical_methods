#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    vector<double> x = { 3, 5, 7, 9, 11, 13 };
    vector<double> y = { 26, 76, 150, 240, 360, 500 };
    int n = 6;

    //1
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < n; i++) {
        sum_x += x[i]; sum_y += y[i];
        sum_xy += x[i] * y[i]; sum_x2 += x[i] * x[i];
    }
    double b_lin = (n * sum_xy - sum_x * sum_y) / (n * sum_x2 - sum_x * sum_x);
    double a_lin = (sum_y - b_lin * sum_x) / n;

    //2
    double sum_lnx = 0, sum_lny = 0, sum_lnx2 = 0, sum_lnx_lny = 0;
    for (int i = 0; i < n; i++) {
        sum_lnx += log(x[i]); sum_lny += log(y[i]);
        sum_lnx2 += log(x[i]) * log(x[i]);
        sum_lnx_lny += log(x[i]) * log(y[i]);
    }
    double b_pow = (n * sum_lnx_lny - sum_lnx * sum_lny) / (n * sum_lnx2 - sum_lnx * sum_lnx);
    double a_pow = exp((sum_lny - b_pow * sum_lnx) / n);

    //3
    double sum_lny_exp = 0, sum_x_lny = 0;
    for (int i = 0; i < n; i++) {
        sum_lny_exp += log(y[i]);
        sum_x_lny += x[i] * log(y[i]);
    }
    double ln_b = (n * sum_x_lny - sum_x * sum_lny_exp) / (n * sum_x2 - sum_x * sum_x);
    double a_exp = exp((sum_lny_exp - ln_b * sum_x) / n);
    double b_exp = exp(ln_b);

    //4
    double sx3 = 0, sx4 = 0, sxy_q = 0, sx2y = 0;
    for (int i = 0; i < n; i++) {
        double x2 = x[i] * x[i];
        sx3 += x2 * x[i]; sx4 += x2 * x2;
        sxy_q += x[i] * y[i]; sx2y += x2 * y[i];
    }

    //Метод Крамера
    double det = n * (sum_x2 * sx4 - sx3 * sx3) - sum_x * (sum_x * sx4 - sx3 * sum_x2) + sum_x2 * (sum_x * sx3 - sum_x2 * sum_x2);
    double det_a = sum_y * (sum_x2 * sx4 - sx3 * sx3) - sum_x * (sxy_q * sx4 - sx3 * sx2y) + sum_x2 * (sxy_q * sx3 - sum_x2 * sx2y);
    double det_b = n * (sxy_q * sx4 - sx3 * sx2y) - sum_y * (sum_x * sx4 - sx3 * sum_x2) + sum_x2 * (sum_x * sx2y - sxy_q * sum_x2);
    double det_c = n * (sum_x2 * sx2y - sxy_q * sx3) - sum_x * (sum_x * sx2y - sxy_q * sum_x2) + sum_y * (sum_x * sx3 - sum_x2 * sum_x2);

    double a_q = det_a / det; double b_q = det_b / det; double c_q = det_c / det;

    cout << fixed << setprecision(2);
    cout << "1. Линейная: y = " << a_lin << " + " << b_lin << " * x" << endl;
    cout << "2. Степенная: y = " << a_pow << " * x^" << b_pow << endl;
    cout << "3. Показательная: y = " << a_exp << " * " << b_exp << "^x" << endl;
    cout << "4. Квадратичная: y = " << a_q << " + " << b_q << " * x + " << c_q << " * x^2" << endl << endl;

    double e_lin = 0, e_pow = 0, e_exp = 0, e_q = 0;
    for (int i = 0; i < n; i++) {
        e_lin += pow(y[i] - (a_lin + b_lin * x[i]), 2);
        e_pow += pow(y[i] - (a_pow * pow(x[i], b_pow)), 2);
        e_exp += pow(y[i] - (a_exp * pow(b_exp, x[i])), 2);
        e_q += pow(y[i] - (a_q + b_q * x[i] + c_q * x[i] * x[i]), 2);
    }

    cout << "СУММАРНЫЕ ПОГРЕШНОСТИ (S):" << endl;
    cout << "Линейная:      " << e_lin << endl;
    cout << "Степенная:     " << e_pow << endl;
    cout << "Показательная: " << e_exp << endl;
    cout << "Квадратичная:  " << e_q << endl;
}