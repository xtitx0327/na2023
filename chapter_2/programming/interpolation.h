#ifndef __wxtsolver__
#define __wxtsolver__

#include <vector>
#include <cmath>
#include <iostream>

template <typename DT>
class Polynomial {
protected:
    int degree;
    std :: vector <DT> coefficients;
public:
    Polynomial() {}
    // 从低次到高次传递系数
    Polynomial(int _degree, std::vector<DT> _coefficients) : degree(_degree), coefficients(std :: vector<DT>(_coefficients)) {}


    ~ Polynomial() {
        coefficients.clear();
    }

    DT evaluate(DT x) {
        DT result = 0;
        DT temp = 1;
        for (int i = 0; i <= degree; ++i) {
            result += coefficients[i] * temp;
            temp *= x;
        }
        return result;
    }

    void print() {
        bool isZero = true;
        for (int i = 0; i <= degree; ++ i) {
            if (coefficients[i] == 0)
                continue;
            isZero = false;
            if (!isZero && i > 0)
                if (coefficients[i] >= 0)
                    std :: cout << " + ";
                else
                    std :: cout << " - ";
            std :: cout << fabs(coefficients[i]);
            if (i == 1)
                std :: cout << " x";
            else if (i > 1)
                std :: cout << " x^" << i;
        }
        if (isZero)
            std :: cout << "0";
        std :: cout << std :: endl;
    }

    Polynomial derivative() {
        std :: vector <DT> new_coefficients(degree, 0);
        for (int i = 1; i <= degree; ++ i)
            new_coefficients[i - 1] = coefficients[i] * i;
        return Polynomial(degree - 1, new_coefficients);
    }

    Polynomial operator = (const Polynomial &p) {
        degree = p.degree;
        coefficients = p.coefficients;
        return *this;
    }

    Polynomial operator + (const Polynomial &p) const {
        int max_degree = std::max(degree, p.degree);
        std :: vector <DT> new_coefficients(max_degree + 1, 0);

        for (int i = 0; i <= degree; ++ i)
            new_coefficients[i] += coefficients[i];

        for (int i = 0; i <= p.degree; ++ i)
            new_coefficients[i] += p.coefficients[i];

        return Polynomial(max_degree, new_coefficients);
    }

    Polynomial operator - (const Polynomial &p) const {
        int max_degree = std :: max(degree, p.degree);
        std :: vector <DT> new_coefficients(max_degree + 1, 0);

        for (int i = 0; i <= degree; ++ i)
            new_coefficients[i] += coefficients[i];

        for (int i = 0; i <= p.degree; ++ i)
            new_coefficients[i] -= p.coefficients[i];

        return Polynomial(max_degree, new_coefficients);
    }

    Polynomial operator * (const Polynomial &p) const {
        int new_degree = degree + p.degree;
        std :: vector <DT> new_coefficients(new_degree + 1, 0);
        for (int i = 0; i <= degree; ++ i)
            for (int j = 0; j <= p.degree; ++ j)
                new_coefficients[i + j] += coefficients[i] * p.coefficients[j];
        return Polynomial(new_degree, new_coefficients);
    }
};

// 计算 Newton 插值多项式
template <typename DT>
Polynomial <DT> newtonInterpolation(const std :: vector<DT>& x, const std :: vector<DT>& f) {
    int n = x.size();
    std :: vector <std :: vector <DT>> dividedDifference(n, std :: vector <DT>(n, 0));
    for (int i = 0; i < n; ++ i)
        dividedDifference[i][0] = f[i];
    for (int i = 1; i < n; ++ i)
        for (int j = 0; j < n - i; ++ j)
            dividedDifference[j][i] = (dividedDifference[j + 1][i - 1] - dividedDifference[j][i - 1]) / (x[j + i] - x[j]);
    Polynomial <DT> result = Polynomial <DT>(0, {dividedDifference[0][0]});
    Polynomial <DT> term = Polynomial <DT>(0, {1});
    for (int i = 1; i < n; i++) {
        term = term * Polynomial <DT>(1, {-x[i - 1], 1});
        result = result + term * Polynomial <DT>(0, {dividedDifference[0][i]});
    }
    return result;
}


// 直接计算 point 处的 Newton 插值结果
template <typename DT>
DT newtonInterpolation(const std :: vector<DT>& x, const std :: vector<DT>& f, DT point) {
    int n = x.size();
    std :: vector <std :: vector<DT>> diff(n, std :: vector <DT>(n));

    for (int i = 0; i < n; ++ i)
        diff[i][0] = f[i];

    for (int j = 1; j < n; ++ j)
        for (int i = 0; i < n - j; ++ i)
            diff[i][j] = (diff[i + 1][j - 1] - diff[i][j - 1]) / (x[i + j] - x[i]);

    DT result = f[0];
    for (int i = 1; i < n; ++ i) {
        DT term = diff[0][i];
        for (int j = 0; j < i; ++ j) {
            term = term * (point - x[j]);
        }
        result += term;
    }
    return result;
}

// Hermit 插值，但只处理每个节点均给出一阶导数的情况
template <typename DT>
Polynomial<DT> hermiteInterpolation(const std::vector<DT>& x, const std::vector<DT>& f, const std::vector<DT>& df) {
    int n = x.size();
    std::vector<DT> z(2*n);
    std::vector<DT> q(2*n, 0);

    for (int i = 0; i < n; i++) {
        z[2*i] = x[i];
        z[2*i + 1] = x[i];
        q[2*i] = f[i];
        q[2*i + 1] = f[i];
    }
    
    for (int i = 1; i < 2*n; i++) {
        if (i % 2 == 1) {
            q[i] = df[i / 2];
        } else if (z[i] != z[i - 1]) {
            q[i] = (f[i/2] - f[i/2 - 1]) / (x[i/2] - x[i/2 - 1]);
        }
    }

    for (int i = 2; i < 2*n; i++) {
        for (int j = 2*n - 1; j >= i; j--) {
            q[j] = (q[j] - q[j - 1]) / (z[j] - z[j - i]);
        }
    }

    Polynomial<DT> result(0, {q[0]});
    Polynomial<DT> term(0, {1});
    for (int i = 1; i < 2*n; i++) {
        term = term * Polynomial<DT>(1, {-z[i - 1], 1});
        result = result + term * Polynomial<DT>(0, {q[i]});
    }
    return result;
}


#endif