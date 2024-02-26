#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

vector<double> gaussMethod(vector<vector<double>>& matrix) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    // Приведение матрицы к треугольному виду
    for (int i = 0; i < rows - 1; i++) {
        if (matrix[i][i] == 0) {
            for (int j = i + 1; j < rows; j++) {
                if (matrix[j][i] != 0) {
                    swap(matrix[i], matrix[j]);
                    break;
                }
            }
        }

        if (matrix[i][i] == 0) {
            throw runtime_error("System of equations has no solutions");
        }

        for (int j = i + 1; j < rows; j++) {
            double factor = matrix[j][i] / matrix[i][i];
            for (int k = i; k < cols; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
        }
    }

    // Обратный ход
    vector<double> solution(rows);
    for (int i = rows - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < cols - 1; j++) {
            sum += matrix[i][j] * solution[j];
        }
        if (matrix[i][i] == 0) {
            throw runtime_error("System of equations has no solutions");
        }
        solution[i] = (matrix[i][cols - 1] - sum) / matrix[i][i];
    }

    return solution;
}

int main() {
    vector<vector<double>> matrix = {{3, 3, 3, 3},
                                     {3, 3, 2, 3},
                                     {1, 3, 3, 3} };

    try {
        vector<double> solution = gaussMethod(matrix);

        // Вывод решения
        for (int i = 0; i < solution.size(); i++) {
            cout << "x" << (i + 1) << " = " << solution[i] << endl;
        }
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}