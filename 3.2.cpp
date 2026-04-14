#include <iostream>
#include <vector>
#include <iomanip>
#include <clocale>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    cout << " метод прогонки \n";
    cout << "Решение системы с трёхдиагональной матрицей\n\n";

    // Ввод размера системы
    int n;
    cout << "Введите размерность системы n: ";
    cin >> n;

    if (n < 2) {
        cout << "Ошибка: размерность должна быть >= 2\n";
        return 1;
    }

    // Объявление массивов для коэффициентов
    vector<double> a(n, 0.0);     // нижняя диагональ (α)
    vector<double> b(n, 0.0);     // главная диагональ (β)
    vector<double> c(n, 0.0);     // верхняя диагональ (γ)
    vector<double> d(n, 0.0);     // правая часть

    // Ввод главной диагонали
    cout << "\nВведите элементы главной диагонали B[i] (i = 1.." << n << "):\n";
    for (int i = 0; i < n; i++) {
        cout << "B[" << i + 1 << "] = ";
        cin >> b[i];
    }

    // Ввод верхней диагонали
    cout << "\nВведите элементы верхней диагонали C[i] (i = 1.." << n - 1 << "):\n";
    for (int i = 0; i < n - 1; i++) {
        cout << "C[" << i + 1 << "] = ";
        cin >> c[i];
    }

    // Ввод нижней диагонали
    cout << "\nВведите элементы нижней диагонали A[i] (i = 2.." << n << "):\n";
    for (int i = 1; i < n; i++) {
        cout << "A[" << i + 1 << "] = ";
        cin >> a[i];
    }

    // Ввод правой части
    cout << "\nВведите правую часть d[i] (i = 1.." << n << "):\n";
    for (int i = 0; i < n; i++) {
        cout << "d[" << i + 1 << "] = ";
        cin >> d[i];
    }

    // Вывод введённой системы
    cout << "\n введенная система \n";
    for (int i = 0; i < n; i++) {
        if (i > 0) cout << a[i] << "*x" << i << " + ";
        cout << b[i] << "*x" << i + 1;
        if (i < n - 1) cout << " + " << c[i] << "*x" << i + 2;
        cout << " = " << d[i] << endl;
    }

    // --- МЕТОД ПРОГОНКИ ---
    cout << "\n решение метоодом прогонки \n";

    // Массивы для прогоночных коэффициентов
    vector<double> p(n, 0.0);  // коэффициенты P (c_i в методичке)
    vector<double> q(n, 0.0);  // коэффициенты Q (d_i в методичке)
    vector<double> x(n, 0.0);  // решение

    // Прямая прогонка
    p[1] = -c[0] / b[0];
    q[1] = d[0] / b[0];

    cout << "\nПрямая прогонка:\n";
    cout << "p[2] = " << p[1] << ", q[2] = " << q[1] << endl;

    for (int i = 2; i < n; i++) {
        double denom = a[i] * p[i - 1] + b[i - 1];
        if (abs(denom) < 1e-10) {
            cout << "Ошибка: деление на ноль!\n";
            return 1;
        }
        p[i] = -c[i - 1] / denom;
        q[i] = (d[i - 1] - a[i] * q[i - 1]) / denom;
        cout << "p[" << i + 1 << "] = " << p[i] << ", q[" << i + 1 << "] = " << q[i] << endl;
    }

    // Обратная прогонка
    double denom = a[n - 1] * p[n - 1] + b[n - 1];
    if (abs(denom) < 1e-10) {
        cout << "Ошибка: деление на ноль!\n";
        return 1;
    }
    x[n - 1] = (d[n - 1] - a[n - 1] * q[n - 1]) / denom;

    cout << "\nОбратная прогонка:\n";
    cout << "x[" << n << "] = " << x[n - 1] << endl;

    for (int i = n - 2; i >= 0; i--) {
        x[i] = p[i + 1] * x[i + 1] + q[i + 1];
        cout << "x[" << i + 1 << "] = " << x[i] << endl;
    }

    // Вывод решения
    cout << "\n решение системы \n";
    for (int i = 0; i < n; i++) {
        cout << "x" << i + 1 << " = " << fixed << setprecision(6) << x[i] << endl;
    }

    // Проверка решения
    cout << "\n невязка \n";
    double max_residual = 0.0;

    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        if (i > 0) sum += a[i] * x[i - 1];
        sum += b[i] * x[i];
        if (i < n - 1) sum += c[i] * x[i + 1];

        double residual = abs(sum - d[i]);
        max_residual = max(max_residual, residual);

        cout << "Ур-е " << i + 1 << ": " << sum << " = " << d[i]
            << " | невязка: " << scientific << residual << endl;
    }

    cout << "\nМаксимальная невязка: " << scientific << max_residual << endl;

}