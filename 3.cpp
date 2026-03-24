#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

bool solveGauss(double A[3][3], double b[3], double x[3]) {
    double aug[3][4];

    // Формируем расширенную матрицу
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            aug[i][j] = A[i][j];
        }
        aug[i][3] = b[i];
    }

    // Прямой ход
    for (int k = 0; k < 3; k++) {
        // Поиск главного элемента
        int maxRow = k;
        for (int i = k + 1; i < 3; i++) {
            if (abs(aug[i][k]) > abs(aug[maxRow][k])) {
                maxRow = i;
            }
        }

        // Перестановка строк
        if (maxRow != k) {
            for (int j = k; j < 4; j++) {
                swap(aug[k][j], aug[maxRow][j]);
            }
        }

        if (abs(aug[k][k]) < 1e-12) return false;

        double pivot = aug[k][k];
        for (int j = k; j < 4; j++) {
            aug[k][j] /= pivot;
        }

        for (int i = 0; i < 3; i++) {
            if (i != k) {
                double factor = aug[i][k];
                for (int j = k; j < 4; j++) {
                    aug[i][j] -= factor * aug[k][j];
                }
            }
        }
    }

    for (int i = 0; i < 3; i++) {
        x[i] = aug[i][3];
    }

    return true;
}

double det3x3(double A[3][3]) {
    return A[0][0] * (A[1][1] * A[2][2] - A[1][2] * A[2][1]) -
        A[0][1] * (A[1][0] * A[2][2] - A[1][2] * A[2][0]) +
        A[0][2] * (A[1][0] * A[2][1] - A[1][1] * A[2][0]);
}

bool inverse3x3(double A[3][3], double inv[3][3]) {
    double d = det3x3(A);
    if (abs(d) < 1e-12) return false;

    inv[0][0] = (A[1][1] * A[2][2] - A[1][2] * A[2][1]) / d;
    inv[0][1] = (A[0][2] * A[2][1] - A[0][1] * A[2][2]) / d;
    inv[0][2] = (A[0][1] * A[1][2] - A[0][2] * A[1][1]) / d;

    inv[1][0] = (A[1][2] * A[2][0] - A[1][0] * A[2][2]) / d;
    inv[1][1] = (A[0][0] * A[2][2] - A[0][2] * A[2][0]) / d;
    inv[1][2] = (A[0][2] * A[1][0] - A[0][0] * A[1][2]) / d;

    inv[2][0] = (A[1][0] * A[2][1] - A[1][1] * A[2][0]) / d;
    inv[2][1] = (A[0][1] * A[2][0] - A[0][0] * A[2][1]) / d;
    inv[2][2] = (A[0][0] * A[1][1] - A[0][1] * A[1][0]) / d;

    return true;
}
double matrixNorm(double A[3][3]) {
    double maxNorm = 0;
    for (int j = 0; j < 3; j++) {
        double colSum = 0;
        for (int i = 0; i < 3; i++) {
            colSum += abs(A[i][j]);
        }
        if (colSum > maxNorm) maxNorm = colSum;
    }
    return maxNorm;
}
void printResidual(double A[3][3], double x[3], double b[3]) {
    cout << "\nНевязка |Ax - b|:" << endl;
    for (int i = 0; i < 3; i++) {
        double sum = 0;
        for (int j = 0; j < 3; j++) {
            sum += A[i][j] * x[j];
        }
        cout << "Строка " << i + 1 << ": " << abs(sum - b[i]) << endl;
    }
}
void printMatrix(double A[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << A[i][j] << " ";
        }
        cout << endl;
    }
}
void printVector(double v[3], const char* name) {
    cout << name << " = [";
    for (int i = 0; i < 3; i++) {
        cout << v[i];
        if (i < 2) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << fixed << setprecision(10);

    cout << "ЗАДАНИЕ 1" << endl;

    double A1[3][3] = {
        {1.00, 0.80, 0.64},
        {1.00, 0.90, 0.81},
        {1.00, 1.10, 1.21}
    };

    double b1[3] = {
        erf(0.80),
        erf(0.90),
        erf(1.10)
    };

    cout << "\nМатрица A1:" << endl;
    printMatrix(A1);

    cout << "\nВектор b1:" << endl;
    cout << "erf(0.80) = " << b1[0] << endl;
    cout << "erf(0.90) = " << b1[1] << endl;
    cout << "erf(1.10) = " << b1[2] << endl;

    double x[3];
    if (solveGauss(A1, b1, x)) {
        printVector(x, "Решение x");

        double invA1[3][3];
        if (inverse3x3(A1, invA1)) {
            double normA = matrixNorm(A1);
            double normInvA = matrixNorm(invA1);
            double cond = normA * normInvA;

            cout << "\nОбусловленность матрицы:" << endl;
            cout << "||A|| = " << normA << endl;
            cout << "||A^(-1)|| = " << normInvA << endl;
            cout << "cond(A) = " << cond << endl;
        }

        // Невязка
        printResidual(A1, x, b1);

        // Сумма решений
        double sumX = x[0] + x[1] + x[2];
        double erf1 = erf(1.0);

        cout << "\nСумма x1 + x2 + x3 = " << sumX << endl;
        cout << "erf(1.0) = " << erf1 << endl;
        cout << "Разность = " << abs(sumX - erf1) << endl;

    }
    else {
        cout << "Система не имеет решения!" << endl;
    }

    cout << "\nЗАДАНИЕ 2" << endl;

    double A2[3][3] = {
        {0.1, 0.2, 0.3},
        {0.4, 0.5, 0.6},
        {0.7, 0.8, 0.9}
    };

    double b2[3] = { 0.1, 0.3, 0.5 };

    cout << "\nМатрица A2:" << endl;
    printMatrix(A2);
    printVector(b2, "Вектор b");

    double detA2 = det3x3(A2);
    cout << "\nОпределитель A2 = " << detA2 << " (матрица вырожденная)" << endl;

    cout << "\nСтрока 3 - Строка 2 = ";
    for (int j = 0; j < 3; j++) {
        cout << A2[2][j] - A2[1][j] << " ";
    }

    cout << "\nСтрока 2 - Строка 1 = ";
    for (int j = 0; j < 3; j++) {
        cout << A2[1][j] - A2[0][j] << " ";
    }

    cout << "\nСтроки линейно зависимы" << endl;

    cout << "\nb3 - b2 = " << b2[2] - b2[1] << endl;
    cout << "b2 - b1 = " << b2[1] - b2[0] << endl;

    if (abs((b2[2] - b2[1]) - (b2[1] - b2[0])) < 1e-10) {
        cout << "система сщвместна" << endl;
        cout << "\nСистема имеет бесконечно много решений" << endl;
    }
    else {
        cout << "Правые части НЕ удовлетворяют соотношению => система НЕСОВМЕСТНА" << endl;
    }
}