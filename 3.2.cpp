#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    
    // Машинная точность для типа double
    const double eps_m = 2.22e-16;

    int n;
    cout << "Введите размерность системы n: ";
    cin >> n;

    if (n < 2) return 1;

    // Коэффициенты (a - нижняя, b - главная, c - верхняя диагонали, d - правая часть)
    vector<double> a(n), b(n), c(n), d(n);
    // Массивы для хранения накопленной погрешности (delta) каждого коэффициента
    vector<double> da(n, 0.0), db(n, 0.0), dc(n, 0.0), dd(n, 0.0);

    cout << "Введите элементы (через пробел или Enter):\n";
    for (int i = 0; i < n; i++) {
        cout << "Уравнение " << i + 1 << " (A[i], B[i], C[i], D[i]): ";
        if (i == 0) a[i] = 0; else cin >> a[i];
        cin >> b[i];
        if (i == n - 1) c[i] = 0; else cin >> c[i];
        cin >> d[i];
        
        // Погрешность ввода (начальная погрешность представления числа)
        da[i] = abs(a[i]) * eps_m;
        db[i] = abs(b[i]) * eps_m;
        dc[i] = abs(c[i]) * eps_m;
        dd[i] = abs(d[i]) * eps_m;
    }

    // Прогоночные коэффициенты и их погрешности
    vector<double> P(n), Q(n), dP(n), dQ(n);

    // Прямая прогонка (для первого узла)
    P[0] = -c[0] / b[0];
    // Расчет погрешности P[0] (деление): суммируем относительные погрешности
    dP[0] = abs(P[0]) * (dc[0]/abs(c[0] + 1e-20) + db[0]/abs(b[0] + 1e-20));
    
    Q[0] = d[0] / b[0];
    dQ[0] = abs(Q[0]) * (dd[0]/abs(d[0] + 1e-20) + db[0]/abs(b[0] + 1e-20));

    // Цикл прямой прогонки
    for (int i = 1; i < n; i++) {
        double znam = b[i] + a[i] * P[i - 1];
        // Погрешность знаменателя (сложение и умножение)
        double d_znam = db[i] + (abs(a[i] * P[i-1]) * (da[i]/abs(a[i]+1e-20) + dP[i-1]/abs(P[i-1]+1e-20)));
        
        if (i < n - 1) {
            P[i] = -c[i] / znam;
            dP[i] = abs(P[i]) * (dc[i]/abs(c[i]+1e-20) + d_znam/abs(znam+1e-20));
        }
        
        Q[i] = (d[i] - a[i] * Q[i - 1]) / znam;
        // Погрешность числителя
        double d_chisl = dd[i] + (abs(a[i] * Q[i-1]) * (da[i]/abs(a[i]+1e-20) + dQ[i-1]/abs(Q[i-1]+1e-20)));
        dQ[i] = abs(Q[i]) * (d_chisl/abs(d[i] - a[i]*Q[i-1] + 1e-20) + d_znam/abs(znam+1e-20));
    }

    // Обратная прогонка и расчет погрешности X
    vector<double> x(n), dx(n);
    x[n - 1] = Q[n - 1];
    dx[n - 1] = dQ[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        x[i] = P[i] * x[i + 1] + Q[i];
        // Погрешность: сумма погрешности произведения (P*X) и погрешности Q
        double d_prod = abs(P[i] * x[i+1]) * (dP[i]/abs(P[i]+1e-20) + dx[i+1]/abs(x[i+1]+1e-20));
        dx[i] = d_prod + dQ[i];
    }

    // Вывод результатов с учетом погрешности
    cout << "\nРезультаты (x_i ± delta_i):\n";
    cout << fixed << setprecision(10);
    for (int i = 0; i < n; i++) {
        cout << "x[" << i + 1 << "] = " << setw(12) << x[i] 
             << "  ±  " << scientific << dx[i] << endl;
    }

    return 0;
}
