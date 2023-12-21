#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>

std :: vector <double> x, y;
// n represents the degree of the polynomial, while N represents the number of data points
const int n = 2, N = 21;

// Gauss elimination
std :: vector <double> GE (std :: vector <std :: vector <double>> A, std :: vector <double> b, int n) {
    std :: vector <double> x (n, 0);
    for (int i = 0; i < n; ++ i) {
        // Find the pivot
        int pivot = i;
        for (int j = i + 1; j < n; ++ j)
            if (fabs (A [j][i]) > fabs (A [pivot][i]))
                pivot = j;
        // Swap the pivot row with the current row
        for (int j = i; j < n; ++ j)
            std :: swap (A [i][j], A [pivot][j]);
        std :: swap (b [i], b [pivot]);
        // Eliminate the current column
        for (int j = i + 1; j < n; ++ j) {
            double ratio = A [j][i] / A [i][i];
            for (int k = i; k < n; ++ k)
                A [j][k] -= ratio * A [i][k];
            b [j] -= ratio * b [i];
        }
    }
    // Back substitution
    for (int i = n - 1; i >= 0; -- i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++ j)
            sum += A [i][j] * x [j];
        x [i] = (b [i] - sum) / A [i][i];
    }
    return x;
}

// QR decomposition, returns x such that Rx = c
std :: vector <double> QR (std :: vector <std :: vector <double>> A, std :: vector <double> b, int n) {
    std :: vector <double> x (n, 0);
    std :: vector <std :: vector <double>> Q (n, std :: vector <double> (n, 0)), R (n, std :: vector <double> (n, 0));
    // Calculate Q and R
    for (int i = 0; i < n; ++ i) {
        for (int j = 0; j < i; ++ j) {
            double sum = 0;
            for (int k = 0; k < n; ++ k)
                sum += A [k][i] * Q [k][j];
            R [j][i] = sum;
            for (int k = 0; k < n; ++ k)
                A [k][i] -= sum * Q [k][j];
        }
        double norm = 0;
        for (int j = 0; j < n; ++ j)
            norm += A [j][i] * A [j][i];
        norm = sqrt (norm);
        for (int j = 0; j < n; ++ j)
            Q [j][i] = A [j][i] / norm;
        R [i][i] = norm;
    }
    // Solve Rx = Q^Tb
    std :: vector <double> c (n, 0);
    for (int i = 0; i < n; ++ i) {
        double sum = 0;
        for (int j = 0; j < n; ++ j)
            sum += Q [j][i] * b [j];
        c [i] = sum;
    }
    // Back substitution
    for (int i = n - 1; i >= 0; -- i) {
        double sum = 0;
        for (int j = i + 1; j < n; ++ j)
            sum += R [i][j] * x [j];
        x [i] = (c [i] - sum) / R [i][i];
    }
    return x;
}

std :: vector <double> DST (std :: vector <double> x, std :: vector <double> y, int n, int N) {
    // Calculate DST (discrete least square) via normal equations
    std :: vector <double> a (n + 1, 0), c (n + 1, 0);
    std :: vector <std :: vector <double>> G (n + 1, std :: vector <double> (n + 1, 0));
    for (int i = 0; i <= n; ++ i)
        for (int j = 0; j <= n; ++ j) {
            double sum = 0;
            for (int k = 0; k < N; ++ k)
                sum += pow (x [k], i + j);
            G [i][j] = sum;
        }
    for (int i = 0; i <= n; ++ i) {
        c [i] = 0;
        for (int j = 0; j < N; ++ j)
            c [i] += y [j] * pow (x [j], i);
    }
    // Use QR decomposition, instead of Gauss elimination
    a = QR (G, c, n + 1);
    return a;
}

int main (int argc, char *argv []) {
    if (argc != 3) {
        std :: cout << "Input & output filename expected!" << std :: endl;
        return 0;
    }

    freopen (argv [1], "r", stdin);
    freopen (argv [2], "w", stdout);

    for (int i = 0; i < N; ++ i) {
        double x_i;
        std :: cin >> x_i;
        x.push_back (x_i);
    }
    for (int i = 0; i < N; ++ i) {
        double y_i;
        std :: cin >> y_i;
        y.push_back (y_i);
    }


    std :: vector <double> a = DST (x, y, n, N);
    for (int i = 0; i <= n; ++ i)
        std :: cout << a [i] << " ";
    std :: cout << std :: endl;

    fclose (stdin);
    fclose (stdout);

    return 0;
}