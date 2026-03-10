#include <iostream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

struct QuadraticRoots {
    double x1;           
    double x2;           
    bool isComplex;      
    double realPart;     
    double imagPart;     
    int status;          
    string message;      
};

QuadraticRoots solveQuadratic(double a, double b, double c) {
    QuadraticRoots result;
    result.status = 0;
    result.isComplex = false;

    const double EPS = 1e-12; 

    if (fabs(a) < EPS) {
        if (fabs(b) < EPS) {
            if (fabs(c) < EPS) {
                result.status = 3;
                result.message = "Бесконечно много решений (0=0)";
            }
            else {
                result.status = 2;
                result.message = "Нет решений (противоречие)";
            }
            return result;
        }

        result.x1 = result.x2 = -c / b;
        result.status = 1;
        result.message = "Линейное уравнение (a=0)";
        return result;
    }

    double maxCoeff = max(fabs(a), max(fabs(b), fabs(c)));
    double scale = 1.0;

    if (maxCoeff > 1e154) {
        scale = 1e-154;
        result.message = "Применено масштабирование (уменьшение)";
    }
    else if (maxCoeff < 1e-154 && maxCoeff > 0) {
        scale = 1e154;
        result.message = "Применено масштабирование (увеличение)";
    }
    else {
        result.message = "Стандартное вычисление";
    }

    double sa = a * scale;
    double sb = b * scale;
    double sc = c * scale;

    double D = sb * sb - 4.0 * sa * sc;

    if (isinf(D) || isnan(D)) {
        result.status = -1;
        result.message = "Переполнение при вычислении дискриминанта";
        return result;
    }

    if (D < -EPS) {
        result.isComplex = true;
        result.realPart = -sb / (2.0 * sa);
        result.imagPart = sqrt(-D) / (2.0 * sa);
        result.message += " (комплексные корни)";
        return result;
    }

    if (fabs(D) < EPS) {
        result.x1 = result.x2 = -sb / (2.0 * sa);
        result.message += " (кратные корни)";
        return result;
    }

    double sqrtD = sqrt(D);
    double x_big; 

    if (sb > 0) {
        x_big = (-sb - sqrtD) / (2.0 * sa);
    }
    else {
        x_big = (-sb + sqrtD) / (2.0 * sa);
    }

    double x_small = (sc / sa) / x_big;
    if (fabs(x_small) < fabs(x_big)) {
        result.x1 = x_small;
        result.x2 = x_big;
    }
    else {
        result.x1 = x_big;
        result.x2 = x_small;
    }

    return result;
}

double checkResidual(double a, double b, double c, double x) {
    return fabs(a * x * x + b * x + c);
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(10);
    cout << "\nСлучай 2" << endl;
    double a1 = 6.0, b1 = 5.0, c1 = -4.0;
    cout << "Уравнение: " << a1 << "x^2 + " << b1 << "x + " << c1 << " = 0" << endl;

    QuadraticRoots res1 = solveQuadratic(a1, b1, c1);
    cout << "Результат: " << res1.message << endl;
    cout << "x1 = " << res1.x1 << ", x2 = " << res1.x2 << endl;
    cout << "Точные значения: 0.5, -1.3333333333" << endl;
    cout << "Невязка для x1: " << scientific << checkResidual(a1, b1, c1, res1.x1) << fixed << endl;
    cout << "Невязка для x2: " << scientific << checkResidual(a1, b1, c1, res1.x2) << fixed << endl;

    cout << "\nСлучай 3" << endl;
    double a2 = 6e30, b2 = 5e30, c2 = -4e30;
    cout << "Уравнение: " << a2 << "x^2 + " << b2 << "x + " << c2 << " = 0" << endl;

    QuadraticRoots res2 = solveQuadratic(a2, b2, c2);
    cout << "Результат: " << res2.message << endl;
    cout << "x1 = " << res2.x1 << ", x2 = " << res2.x2 << endl;
    cout << "Ожидаемые: 0.5, -1.3333333333" << endl;
    cout << "Невязка для x1: " << scientific << checkResidual(a2, b2, c2, res2.x1) << fixed << endl;
    cout << "Невязка для x2: " << scientific << checkResidual(a2, b2, c2, res2.x2) << fixed << endl;

    cout << "\nСлучай 4" << endl;
    double a3 = 1e-30, b3 = -1e-30, c3 = 1e-30;
    cout << "Уравнение: " << a3 << "x^2 + " << b3 << "x + " << c3 << " = 0" << endl;

    QuadraticRoots res3 = solveQuadratic(a3, b3, c3);
    cout << "Результат: " << res3.message << endl;
    cout << "x1 = " << res3.x1 << ", x2 = " << res3.x2 << endl;
    cout << "Ожидаемые: x1 ~ 1, x2 ~ 1e30 (большой корень может быть за пределами)" << endl;
    cout << "Невязка для x1: " << scientific << checkResidual(a3, b3, c3, res3.x1) << fixed << endl;

    cout << "\nСлучай 5" << endl;
    double a4 = 1.0, b4 = -4.0, c4 = 3.9999999;
    cout << "Уравнение: " << a4 << "x^2 + " << b4 << "x + " << c4 << " = 0" << endl;

    QuadraticRoots res4 = solveQuadratic(a4, b4, c4);
    cout << "Результат: " << res4.message << endl;
    cout << "x1 = " << res4.x1 << ", x2 = " << res4.x2 << endl;
    cout << "Точные значения: 1.999683772, 2.000316228" << endl;
    cout << "Невязка для x1: " << scientific << checkResidual(a4, b4, c4, res4.x1) << fixed << endl;
    cout << "Невязка для x2: " << scientific << checkResidual(a4, b4, c4, res4.x2) << fixed << endl;

    cout << "\nКомплексные корни" << endl;
    double a5 = 1.0, b5 = 2.0, c5 = 5.0;
    cout << "Уравнение: " << a5 << "x^2 + " << b5 << "x + " << c5 << " = 0" << endl;

    QuadraticRoots res5 = solveQuadratic(a5, b5, c5);
    cout << "Результат: " << res5.message << endl;
    if (res5.isComplex) {
        cout << "x1 = " << res5.realPart << " - " << fabs(res5.imagPart) << "i" << endl;
        cout << "x2 = " << res5.realPart << " + " << fabs(res5.imagPart) << "i" << endl;
    }
    cout << "Точные значения: -1 - 2i, -1 + 2i" << endl;

    cout << "\n Линейное уравнение (a=0)" << endl;
    double a6 = 0.0, b6 = 2.0, c6 = -4.0;
    cout << "Уравнение: "  << b6 << "x + " << c6 << " = 0" << endl;

    QuadraticRoots res6 = solveQuadratic(a6, b6, c6);
    cout << "Результат: " << res6.message << endl;
    if (res6.status == 1) {
        cout << "x = " << res6.x1 << endl;
    }
}