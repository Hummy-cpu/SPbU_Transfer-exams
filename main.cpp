#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>


// определитель методом Гаусса
double det(std::vector<std::vector<double>>& matrix, int n) {
    double d = 1.0;
    const double eps = 1e-9; // обработка нуля
    for (int i = 0; i < n; ++i) {
        // выбор элемента, который поместим на диагональ
        int pivot = i;
        for (int j = i + 1; j < n; ++j) {
            if (std::abs(matrix[j][i]) > std::abs(matrix[pivot][i])) {
                pivot = j;
            }
        }// std::abs - модуль числа
        // если есть нулевая строка, то det = 0 сразу
        if (std::abs(matrix[pivot][i]) < eps) {
            return 0.0;
        }
        // Если нашли строку лучше, меняем их местами и меняем знак определителя
        if (i != pivot) {
            swap(matrix[i], matrix[pivot]);
            d = -d;
        }
        // Умножаем определитель на диагональный элемент
        d *= matrix[i][i];
        // обнуляем элементы под диагональю
        for (int j = i + 1; j < n; ++j) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < n; ++k) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }
    return d;
}

int main() {
    std::ifstream infile("input.txt");
    double res = 0;
    int n = 0;
    if (!(infile >> n)) {
        std::cerr << "Ошибка чтения размера матрицы N" << std::endl;
        return 1;
    }
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n));
    for (int i = 0; i < n; ++i) {  //считываем элементы
        for (int j = 0; j < n; ++j) {
            if (!(infile >> matrix[i][j])) {
                std::cerr << "Ошибка: Недостаточно элементов! " << n << "x" << n << std::endl;
                return 1;
            }
        }
    } 
    infile.close();
    res = det(matrix, n);
    std::cout << res << std::endl;
}
