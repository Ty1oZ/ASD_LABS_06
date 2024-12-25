#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

const int INF = 1e10; 

void reduceRows(vector<vector<int>>& matrix, int& cost) {
    for (int i = 0; i < matrix.size(); ++i) {
        int rowMin = INF;
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] < rowMin) rowMin = matrix[i][j];
        }
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] != INF) {
                matrix[i][j] -= rowMin;
            }
        }
        if (rowMin != INF) {
            cost += rowMin;
        }
    }
}

void reduceColumns(vector<vector<int>>& matrix, int& cost) {
    for (int j = 0; j < matrix[0].size(); ++j) {
        int colMin = INF;
        for (int i = 0; i < matrix.size(); ++i) {
            if (matrix[i][j] < colMin) colMin = matrix[i][j];
        }
        for (int i = 0; i < matrix.size(); ++i) {
            if (matrix[i][j] != INF) { 
                matrix[i][j] -= colMin;
            }
        }
        if (colMin != INF) {
            cost += colMin;
        }
    }
}

vector<pair<int, pair<int, int>>> evaluateZeros(const vector<vector<int>>& matrix) {
    vector<pair<int, pair<int, int>>> zeroEvaluations; 

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            if (matrix[i][j] == 0) {
                int rowMin = INF;
                int colMin = INF;

                for (int k = 0; k < matrix.size(); ++k) {
                    if (k != j && matrix[i][k] < rowMin) rowMin = matrix[i][k];
                }

                for (int k = 0; k < matrix.size(); ++k) {
                    if (k != i && matrix[k][j] < colMin) colMin = matrix[k][j];
                }

                int penalty = (rowMin == INF ? 0 : rowMin) +
                    (colMin == INF ? 0 : colMin);

                zeroEvaluations.emplace_back(penalty, make_pair(i, j));
            }
        }
    }

    return zeroEvaluations;
}

void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            if (elem == INF) {
                cout << setw(7) << "INF";
            }
            else {
                cout << setw(7) << elem;
            }
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> matrix = {
        {INF, 20, 30, 10, 11},
        {15, INF, 16, 4, 2},
        {3, 5, INF, 2, 4},
        {19, 6, 18, INF, 3},
        {16, 4, 7, 16, INF}
    };

    cout << "The original matrix:" << '\n';
    printMatrix(matrix);

    int cost = 0;

    reduceRows(matrix, cost);
    cout << "\nThe matrix after row reduction:" << '\n';
    printMatrix(matrix);

    
    reduceColumns(matrix, cost);
    cout << "\nThe matrix after reduction by columns:" << '\n';
    printMatrix(matrix);

    cout << "\nCurrent value: " << cost << '\n';

    auto zeroEvaluations = evaluateZeros(matrix);
    cout << "\nEvaluation of zeros (penalties):" << '\n';
    for (const auto& eval : zeroEvaluations) {
        cout << "Penalty: " << eval.first << ", Position: (" << eval.second.first << ", " << eval.second.second << ")" << '\n';
    }

    return 0;
}