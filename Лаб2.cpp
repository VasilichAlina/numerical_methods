#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

void solveQuadratic(double a, double b, double c) {
    cout << "\nРешение уравнения: " << a << " x^2 + " << b << " x + " << c << " = 0" << endl;

    if (a == 0 && b == 0 && c == 0) {
        cout << "Все комплексные числа являются корнями" << endl;    }

    if (a == 0 && b == 0) {
        cout << "Нет решений (c = " << c << " != 0)" << endl;    }

    if (a == 0) {
        cout << "Линейное уравнение, корень: x = " << -c / b << endl;    }

    double maxVal = max(fabs(a), max(fabs(b), fabs(c)));
    if (maxVal > 1e30) {
        double scale = maxVal / 1e10;
        a /= scale;
        b /= scale;
        c /= scale;
        cout << "Выполнено масштабирование коэффициентов" << endl;
    }

    double minVal = min(fabs(a), min(fabs(b), fabs(c)));
    if (minVal < 1e-30) {
        double scale = maxVal / 1e10;
        a *= scale;
        b *= scale;
        c *= scale;
        cout << "Выполнено масштабирование коэффициентов (машинные нули)" << endl;
    }


    double d = b * b - 4 * a * c;

    if (d < 0) {
        double realPart = -b / (2 * a);
        double imagPart = sqrt(-d) / (2 * a);
        cout << "Комплексные корни:" << endl;
        cout << "x1 = " << realPart << " + " << imagPart << "i" << endl;
        cout << "x2 = " << realPart << " - " << imagPart << "i" << endl;
    }
    else if (d == 0) {
        double x = -b / (2 * a);
        cout << "Кратный корень: x = " << x << endl;
    }
    else {
        double sqrt_d = sqrt(d);
        double x1, x2;

        if (b >= 0) {
            x1 = (-b - sqrt_d) / (2 * a);
        }
        else {
            x1 = (-b + sqrt_d) / (2 * a);
        }

        x2 = c / (a * x1);

        if (x1 > x2) {
            double temp = x1;
            x1 = x2;
            x2 = temp;
        }

        cout << "Действительные корни:" << endl;
        cout << "x1 = " << x1 << endl;
        cout << "x2 = " << x2 << endl;

        double f1 = a * x1 * x1 + b * x1 + c;
        double f2 = a * x2 * x2 + b * x2 + c;
        double maxResidual = max(fabs(f1), fabs(f2));

        if (maxResidual > 1e-12) {
            cout << "Точность: требуется повышенная точность" << endl;
            cout << "Невязка: " << maxResidual << endl;
        }
        else {
            cout << "Точность: удовлетворительная (невязка < 1e-12)" << endl;
        }
        if (fabs(f1) > 1e-10 || fabs(f2) > 1e-10) {
            cout << "Уравнение чувствительное, погрешность: " << fmax(fabs(f1), fabs(f2)) << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "rus");
    cout.precision(10);
    cout << "\nСлучай 1 ";
    solveQuadratic(1, -1000, 1);

    cout << "\nСлучай 2 ";
    solveQuadratic(6, 5, -4);

    cout << "\nСлучай 3 ";
    solveQuadratic(6e30, 5e30, -4e30);

    cout << "\nСлучай 4";
    solveQuadratic(1e-50, -1e30, 1e30);

    cout << "\nСлучай 5 ";
    solveQuadratic(1, -4, 3.9999999);

    cout << "\nКомплексные корни ";
    solveQuadratic(1, 2, 5);

    cout << "\nЛинейное уравнение ";
    solveQuadratic(0, 2, -4);

    cout << "\nКратный корень ";
    solveQuadratic(1, -2, 1);

    return 0;
}