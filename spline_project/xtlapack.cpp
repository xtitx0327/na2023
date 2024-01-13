#include "xtlapack.h"
#define abs(x) ((x) > 0 ? (x) : -(x))

std :: vector <double> chaseMethod (int n, const std :: vector <double> &a, const std :: vector <double> &diag, const std :: vector <double> &b, const std :: vector <double> &B) {
    // 用追赶法求解三对角方程组。n 为方程组阶数，a 为下方对角元（n - 1 阶），diag 为对角元（n 阶），c 为上方对角元（n - 1阶），B 为方程组右侧向量
    std :: vector <double> M (n); // M 为解向量
    std :: vector <double> alpha (n - 1), beta (n - 1);
    alpha[0] = a[0] / diag[0];
    beta[0] = B[0] / diag[0];
    for (int i = 1; i < n - 1; ++ i) {
        alpha[i] = a[i] / (diag[i] - alpha[i - 1] * b[i - 1]);
        beta[i] = (B[i] - beta[i - 1] * b[i - 1]) / (diag[i] - alpha[i - 1] * b[i - 1]);
    }
    M[n - 1] = (B[n - 1] - beta[n - 2] * b[n - 2]) / (diag[n - 1] - alpha[n - 2] * b[n - 2]);
    for (int i = n - 2; i >= 0; -- i)
        M[i] = beta[i] - alpha[i] * M[i + 1];
    return M;
}

std::vector<double> GaussEliminate(int n, const std::vector<std::vector<double>>& A, const std::vector<double>& b) {
    std::vector<std::vector<double>> augmentedMatrix(n, std::vector<double>(n + 1));

    // 构建增广矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmentedMatrix[i][j] = A[i][j];
        }
        augmentedMatrix[i][n] = b[i];
    }

    // 高斯消元
    for (int i = 0; i < n; ++i) {
        // 首先找到主元素的位置
        int pivotRow = i;
        for (int j = i + 1; j < n; ++j) {
            if (abs(augmentedMatrix[j][i]) > abs(augmentedMatrix[pivotRow][i])) {
                pivotRow = j;
            }
        }

        // 交换当前行和主元素所在行
        if (pivotRow != i) {
            std::swap(augmentedMatrix[i], augmentedMatrix[pivotRow]);
        }

        // 将当前主元素归一化
        double pivot = augmentedMatrix[i][i];
        for (int j = i; j <= n; ++j) {
            augmentedMatrix[i][j] /= pivot;
        }

        // 消元
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                double factor = augmentedMatrix[j][i];
                for (int k = i; k <= n; ++k) {
                    augmentedMatrix[j][k] -= factor * augmentedMatrix[i][k];
                }
            }
        }
    }

    // 提取解向量
    std::vector<double> x(n);
    for (int i = 0; i < n; ++i) {
        x[i] = augmentedMatrix[i][n];
    }

    return x;
}