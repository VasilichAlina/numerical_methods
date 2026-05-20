#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    const int n = 5;

    vector<double> alpha(n + 1), beta(n + 1), gamma(n + 1), b(n + 1);
    vector<double> c(n + 1), d(n + 1), x(n + 1);
    vector<double> d_alpha(n + 1), d_beta(n + 1), d_gamma(n + 1), d_b(n + 1);
    vector<double> d_c(n + 1), d_d(n + 1), d_x(n + 1);

    double init_err = 0.0001;

    alpha[2] = -2.0; alpha[3] = 2.0;  alpha[4] = 1.0;  alpha[5] = 3.0;
    beta[1] = 1.0;  beta[2] = 4.0;  beta[3] = -2.0; beta[4] = 1.0;  beta[5] = -1.0;
    gamma[1] = 3.0;  gamma[2] = -1.0; gamma[3] = 1.0;  gamma[4] = 1.0;
    b[1] = 5.0;  b[2] = 1.0;  b[3] = 3.0;  b[4] = -2.0; b[5] = -1.0;

    for (int i = 1; i <= n; ++i) {
        d_alpha[i] = init_err; d_beta[i] = init_err; d_gamma[i] = init_err; d_b[i] = init_err;
    }

    cout << fixed << setprecision(6);
    cout << "прямая прогонка" << endl;

    c[2] = -gamma[1] / beta[1];
    d_c[2] = abs(c[2]) * (d_gamma[1] / abs(gamma[1]) + d_beta[1] / abs(beta[1]));

    d[2] = b[1] / beta[1];
    d_d[2] = abs(d[2]) * (d_b[1] / abs(b[1]) + d_beta[1] / abs(beta[1]));

    cout << "c2 = " << c[2] << " err = " << d_c[2] << endl;
    cout << "d2 = " << d[2] << " err = " << d_d[2] << endl;

    for (int i = 2; i <= n - 1; ++i) {
        double prod1 = alpha[i] * c[i];
        double d_prod1 = abs(prod1) * (d_alpha[i] / abs(alpha[i]) + d_c[i] / abs(c[i]));

        double denom = prod1 + beta[i];
        double d_denom = d_prod1 + d_beta[i];

        c[i + 1] = -gamma[i] / denom;
        d_c[i + 1] = abs(c[i + 1]) * (d_gamma[i] / abs(gamma[i]) + d_denom / abs(denom));

        double prod2 = alpha[i] * d[i];
        double d_prod2 = abs(prod2) * (d_alpha[i] / abs(alpha[i]) + d_d[i] / abs(d[i]));

        double num2 = b[i] - prod2;
        double d_num2 = d_b[i] + d_prod2;

        d[i + 1] = num2 / denom;
        d_d[i + 1] = abs(d[i + 1]) * (d_num2 / abs(num2) + d_denom / abs(denom));

        cout << "c" << i + 1 << " = " << c[i + 1] << " err = " << d_c[i + 1] << endl;
        cout << "d" << i + 1 << " = " << d[i + 1] << " err = " << d_d[i + 1] << endl;
    }

    cout << "обратная прогонка"<< endl;

    double prod_n = alpha[n] * c[n];
    double d_prod_n = abs(prod_n) * (d_alpha[n] / abs(alpha[n]) + d_c[n] / abs(c[n]));

    double denom_n = prod_n + beta[n];
    double d_denom_n = d_prod_n + d_beta[n];

    double num_n = b[n] - alpha[n] * d[n];
    double d_num_n = d_b[n] + (abs(alpha[n] * d[n]) * (d_alpha[n] / abs(alpha[n]) + d_d[n] / abs(d[n])));

    x[n] = num_n / denom_n;
    d_x[n] = abs(x[n]) * (d_num_n / abs(num_n) + d_denom_n / abs(denom_n));
    cout << "x" << n << " = " << x[n] << " err = " << d_x[n] << endl;

    for (int i = n - 1; i >= 1; --i) {
        double prod_x = c[i + 1] * x[i + 1];
        double d_prod_x = abs(prod_x) * (d_c[i + 1] / abs(c[i + 1]) + d_x[i + 1] / abs(x[i + 1]));

        x[i] = prod_x + d[i + 1];
        d_x[i] = d_prod_x + d_d[i + 1];
        cout << "x" << i << " = " << x[i] << " err = " << d_x[i] << endl;
    }
}
