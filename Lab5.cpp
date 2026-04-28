

//													TASK 1

//#include <iostream>
//#include <vector>
//#include <cmath>
//#include <iomanip>
//
//using namespace std;
//
//const double  M_PI = 3.1415926535;
//// Исходная функция Runge
//double f(double x) {
//    return 1.0 / (1.0 + 25.0 * x * x);
//}
//
//// Вычисление значения полинома Лагранжа в точке x_target
//double lagrange(double x_target, const vector<double>& x, const vector<double>& y) {
//    double result = 0;
//    int n = x.size();
//    for (int i = 0; i < n; i++) {
//        double term = y[i];
//        for (int j = 0; j < n; j++) {
//            if (i != j) {
//                term *= (x_target - x[j]) / (x[i] - x[j]);
//            }
//        }
//        result += term;
//    }
//    return result;
//}
//
//int main() {
//    int n;
//    cout << "Enter number of nodes (n): ";
//    cin >> n;
//
//    vector<double> x_nodes(n), y_nodes(n);
//
//    // 1. Узлы (выберите нужный вариант, раскомментировав его)
//    for (int i = 0; i < n; i++) {
//        // а) Равноотстоящие узлы
//        //x_nodes[i] = -1.0 + i * (2.0 / (n - 1));
//
//        // б) Чебышевские узлы (раскомментируйте, если нужны они)
//        x_nodes[i] = cos(M_PI * (2.0 * i + 1.0) / (2.0 * n)); 
//
//        y_nodes[i] = f(x_nodes[i]);
//    }
//
//    // 2. Генерация данных для Excel (100 точек для плавности графика)
//    cout << "\nx\tf(x)\tLagrange(x)\n";
//    cout << fixed << setprecision(5);
//    for (int i = 0; i <= 100; i++) {
//        double cur_x = -1.0 + i * (2.0 / 100.0);
//        cout << cur_x << "\t" << f(cur_x) << "\t" << lagrange(cur_x, x_nodes, y_nodes) << endl;
//    }
//
//    return 0;
//}




//							TASK 2 
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

using namespace std;

// Структура для хранения коэффициентов сплайна
struct SplineTuple {
    double a, b, c, d, x;
};

// Функция Рунге из задания 2.1
double f_runge(double x) {
    return 1.0 / (1.0 + 25.0 * x * x);
}

// Построение кубического сплайна (условия из методички: S''(x0)=S''(xn)=0)
void buildSpline(const vector<double>& x, const vector<double>& y, vector<SplineTuple>& s) {
    int n = (int)x.size();
    s.assign(n, { 0, 0, 0, 0, 0 });
    for (int i = 0; i < n; ++i) {
        s[i].x = x[i];
        s[i].a = y[i];
    }

    vector<double> h(n), alpha(n), l(n), mu(n), z(n);
    for (int i = 0; i < n - 1; ++i) h[i] = x[i + 1] - x[i];

    for (int i = 1; i < n - 1; ++i)
        alpha[i] = (3.0 / h[i]) * (s[i + 1].a - s[i].a) - (3.0 / h[i - 1]) * (s[i].a - s[i - 1].a);

    l[0] = 1.0; mu[0] = 0.0; z[0] = 0.0;
    for (int i = 1; i < n - 1; ++i) {
        l[i] = 2.0 * (x[i + 1] - x[i - 1]) - h[i - 1] * mu[i - 1];
        mu[i] = h[i] / l[i];
        z[i] = (alpha[i] - h[i - 1] * z[i - 1]) / l[i];
    }

    l[n - 1] = 1.0; z[n - 1] = 0.0; s[n - 1].c = 0.0;
    for (int j = n - 2; j >= 0; --j) {
        s[j].c = z[j] - mu[j] * s[j + 1].c;
        s[j].b = (s[j + 1].a - s[j].a) / h[j] - h[j] * (s[j + 1].c + 2.0 * s[j].c) / 3.0;
        s[j].d = (s[j + 1].c - s[j].c) / (3.0 * h[j]);
    }
}

// Вычисление значения сплайна в точке x_target
double evaluateSpline(const vector<SplineTuple>& s, double x_target) {
    int n = (int)s.size();
    int i = 0;
    if (x_target <= s[0].x) i = 0;
    else if (x_target >= s[n - 1].x) i = n - 2;
    else {
        for (int j = 0; j < n - 1; j++) {
            if (x_target >= s[j].x && x_target <= s[j + 1].x) { i = j; break; }
        }
    }
    double dx = x_target - s[i].x;
    return s[i].a + s[i].b * dx + s[i].c * dx * dx + s[i].d * dx * dx * dx;
}

int main() {
    setlocale(LC_ALL, "Russian");
    cout << fixed << setprecision(5);

    // --- ПУНКТ 1: Сплайн для функции f(x) на [-1, 1] ---
    int n_val;
    cout << "Введите число узлов n для функции Рунге (например, 10): ";
    cin >> n_val;

    vector<double> x_r(n_val), y_r(n_val);
    for (int i = 0; i < n_val; i++) {
        x_r[i] = -1.0 + i * (2.0 / (n_val - 1));
        y_r[i] = f_runge(x_r[i]);
    }
    vector<SplineTuple> s_runge;
    buildSpline(x_r, y_r, s_runge);

    cout << "\n=== ЗАДАНИЕ 2.1: СПЛАЙН ДЛЯ f(x) ===\n";
    cout << "x;f(x);Spline(x)\n";
    for (int i = 0; i <= 40; i++) {
        double cx = -1.0 + i * (2.0 / 40.0);
        cout << cx << ";" << f_runge(cx) << ";" << evaluateSpline(s_runge, cx) << "\n";
    }

    // --- ПУНКТ 2: Сплайн по таблице ---
    vector<double> x_table = { 2.0, 3.0, 5.0, 7.0 };
    vector<double> y_table = { 4.0, -2.0, -3.0, 6.0 };
    vector<SplineTuple> s_table;
    buildSpline(x_table, y_table, s_table);

    cout << "\n=== ЗАДАНИЕ 2.2: СПЛАЙН ПО ТАБЛИЦЕ ===\n";
    cout << "x;Spline(x)\n";
    for (double cx = 2.0; cx <= 7.01; cx += 0.25) {
        cout << cx << ";" << evaluateSpline(s_table, cx) << "\n";
    }

    return 0;
}