#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Норма вектора (максимальная)
double norm(const vector<double>& v) {
    double max = 0.0;
    for (double x : v)
        if (fabs(x) > max) max = fabs(x);
    return max;
}

// Вычисление невязки r = b - A*x
vector<double> residual(const vector<vector<double>>& A, const vector<double>& b, const vector<double>& x) {
    int n = A.size();
    vector<double> r(n, 0.0);
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        for (int j = 0; j < n; j++)
            sum += A[i][j] * x[j];
        r[i] = b[i] - sum;
    }
    return r;
}

// Метод Якоби
void jacobi(const vector<vector<double>>& A, const vector<double>& b, vector<double> x, double eps, int maxIter) {
    int n = A.size();
    vector<double> x_new(n);
    cout << "МЕТОД ЯКОБИ" << endl;;
    cout << "Начальное приближение: ";
    for (double v : x) cout << v << " ";
    cout << "\n\n";

    for (int iter = 0; iter < maxIter; iter++) {
        for (int i = 0; i < n; i++) {
            double sum = 0.0;
            for (int j = 0; j < n; j++)
                if (j != i)
                    sum += A[i][j] * x[j];
            x_new[i] = (b[i] - sum) / A[i][i];
        }

        vector<double> r = residual(A, b, x_new);
        double norm_r = norm(r);
        cout << "Итерация " << iter + 1 << " | Норма невязки = " << norm_r << endl;

        if (norm_r < eps) {
            cout << "Результат : " << endl;
            for (int i = 0; i < n; i++)
                cout << "x[" << i + 1 << "] = " << fixed << setprecision(8) << x_new[i] << endl;
            cout << "Достигнуто за " << iter + 1 << " итераций\n";
            return;
        }
        x = x_new;
    }
    cout << "! Достигнут максимум итераций\n";
}

// Метод Зейделя

void seidel(const vector<vector<double>>& A, const vector<double>& b, vector<double> x, double eps, int maxIter) {
    int n = A.size();
    cout << "МЕТОД ЗЕЙДЕЛЯ" << endl;;
    cout << "Начальное приближение: ";
    for (double v : x) cout << v << " ";
    cout << "\n\n";

    for (int iter = 0; iter < maxIter; iter++) {
        vector<double> x_old = x;
        for (int i = 0; i < n; i++) {
            double sum1 = 0.0, sum2 = 0.0;
            for (int j = 0; j < i; j++)
                sum1 += A[i][j] * x[j];
            for (int j = i + 1; j < n; j++)
                sum2 += A[i][j] * x_old[j];
            x[i] = (b[i] - sum1 - sum2) / A[i][i];
        }

        vector<double> r = residual(A, b, x);
        double norm_r = norm(r);
        cout << "Итерация " << iter + 1 << " | Норма невязки = " << norm_r << endl;

        if (norm_r < eps) {
            cout << "Результат : " << endl;;
            for (int i = 0; i < n; i++)
                cout << "x[" << i + 1 << "] = " << fixed << setprecision(8) << x[i] << endl;
            cout << "Достигнуто за " << iter + 1 << " итераций\n";
            return;
        }
    }
    cout << " Достигнут максимум итераций\n";
}

int main() {
    setlocale(LC_ALL, "rus");
       vector<vector<double>> A = {
        {12.14,  1.32, -0.78, -2.75},
        {-0.89, 16.75,  1.88, -1.55},
        {2.65,  -1.27, -15.64, -0.64},
        {2.44,   1.52,  1.93, -11.43}
    };

    vector<double> b = { 14.78, -12.14, -11.65, 4.26 };

    double eps = 1e-6;
    int maxIter = 200;

    // Различные начальные приближения
    vector<vector<double>> startVectors = {
        {0, 0, 0, 0},
        {1, 1, 1, 1},
        {10, -10, 5, -5},
        {100, 100, 100, 100}
    };

    for (auto& x0 : startVectors) {
        cout << endl;

        cout << " Начальное приближение: ";
        for (double v : x0) cout << v << " ";
        cout << endl;
        cout << endl;
        jacobi(A, b, x0, eps, maxIter);
        cout << endl;
        seidel(A, b, x0, eps, maxIter);
    }

    return 0;
}