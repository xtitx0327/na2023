#include "xtspline.h"

Function :: Function (double (*f)(double x)) {
    this -> func = f;
}

double Function :: operator ()(double x) const {
    return (*func)(x);
}

Polynomial :: Polynomial (const std :: vector <double> &c) : c (c) {}

Polynomial :: Polynomial (const std :: vector <double> &x, const std :: vector <double> &y) {
    if (x.size () != y.size ())
        throw "Size mismatch";
    // 使用 Newton 插值法计算多项式的系数
    int n = x.size ();
    std :: vector <double> c (n, 0.0);
    std :: vector <double> dividedDiff (n, 0.0);
    // 初始化差分表的第一列
    for (int i = 0; i < n; ++ i)
        dividedDiff[i] = y[i];
    // 计算差分表的其余部分，并构建系数
    c[0] = dividedDiff[0];
    for (int i = 1; i < n; ++ i) {
        for (int j = 0; j < n - i; ++ j) 
            dividedDiff[j] = (dividedDiff[j + 1] - dividedDiff[j]) / (x[j + i] - x[j]);
        c[i] = dividedDiff[0];
    }
    // 将牛顿形式转为标准形式
    std :: vector <double> standard_c (n, 0.0); // 初始化为 0
    for (int i = 0; i < n; ++ i) {
        // 创建一个临时多项式，代表 c[i] * (x - x_0) * ... * (x - x_{i-1})
        std :: vector <double> temp (1, c[i]); // 初始为常数项 c[i]
        for (int j = 0; j < i; ++ j) {
            // 将 temp 乘以 (x - x_j)
            temp.push_back(0); // 增加一个零系数
            for (int k = temp.size () - 1; k > 0; -- k)
                temp[k] = temp[k - 1] - x[j] * temp[k];
            temp[0] *= -x[j]; // 更新常数项
        }
        // 将 temp 加到 standard_c 中
        for (int j = 0; j < temp.size (); ++ j)
            standard_c[j] += temp[j];
    }
    this -> c = standard_c;
}

void Polynomial :: print () const {
    for (int i = 0; i < c.size (); ++ i)
        std :: cout << c[i] << " ";
    std :: cout << std :: endl;
}

Polynomial Polynomial :: operator + (const Polynomial &p) const {
    // 计算两个多项式的和
    std :: vector <double> c (std :: max (this -> c.size (), p.c.size ()));
    for (int i = 0; i < c.size (); ++ i) {
        if (i < this -> c.size ())
            c[i] += this -> c[i];
        if (i < p.c.size ())
            c[i] += p.c[i];
    }
    return Polynomial (c);
}

Polynomial Polynomial :: operator - (const Polynomial &p) const {
    // 计算两个多项式的差
    std :: vector <double> c (std :: max (this -> c.size (), p.c.size ()));
    for (int i = 0; i < c.size (); ++ i) {
        if (i < this -> c.size ())
            c[i] += this -> c[i];
        if (i < p.c.size ())
            c[i] -= p.c[i];
    }
    return Polynomial (c);
}

Polynomial Polynomial :: operator * (const Polynomial &p) const {
    // 计算两个多项式的积
    std :: vector <double> c (this -> c.size () + p.c.size () - 1, 0.0);
    for (int i = 0; i < this -> c.size (); ++ i)
        for (int j = 0; j < p.c.size (); ++ j)
            c[i + j] += this -> c[i] * p.c[j];
    return Polynomial (c);
}

double Polynomial :: operator ()(double x) const {
    // 使用秦九韶算法计算多项式的值
    double ret = 0;
    for (int i = c.size() - 1; i >= 0; -- i) {
        ret *= x;
        ret += c[i];
    }
    return ret;
}

Polynomial Polynomial :: derivative () {
    std :: vector <double> c (this -> c.size () - 1);
    for (int i = 1; i < this -> c.size (); ++ i)
        c[i - 1] = this -> c[i] * i;
    return Polynomial (c);
}

PiecewisePolynomial :: PiecewisePolynomial (const std :: vector <Polynomial> &p, const std :: vector <double> &x) : p (p), t (x) {}

double PiecewisePolynomial :: operator ()(double x) const {
    if (x < this -> t[0] || x > this -> t.back ())
        throw "Out of range";
    for (int i = 0; i < this -> t.size () - 1; ++ i)
        if (x >= this -> t[i] && x <= this -> t[i + 1])
            return this -> p[i](x);
    throw "Out of range";
}

void PiecewisePolynomial :: print (bool showExtraInfo) const {
    if (showExtraInfo)
        std :: cout << "Number of segments: " << (p.size ()) + 1 << std :: endl;
    for (int i = 0; i < p.size (); ++ i) {
        if (showExtraInfo)
            std :: cout << "Interval " << i + 1 << " [" << t[i] << ", " << t[i + 1] << "]" << std :: endl;
        else
            std :: cout << t[i] << " " << t[i + 1] << std :: endl;
        p[i].print ();
    }
}

PiecewisePolynomial PiecewisePolynomial :: derivative () {
    std :: vector <Polynomial> p (this -> p.size ());
    for (int i = 0; i < p.size (); ++ i)
        p[i] = this -> p[i].derivative ();
    return PiecewisePolynomial (p, this -> t);
}

Curve :: Curve (const std :: vector <Function *> &f) {
    if (f.size () != dim)
        throw "Dimension mismatch";

    for (int i = 0; i < f.size (); ++ i)
        this -> params.push_back (f[i]);
}

std :: vector <double> Curve :: operator ()(double t) const {
    std :: vector <double> ret (dim);
    for (int i = 0; i < dim; ++ i)
        ret[i] = (*params[i])(t);
    return ret;
}

std :: vector <double> Spline :: operator ()(double t) const {
    std :: vector <double> ret (dim);
    for (int i = 0; i < dim; ++ i)
        ret[i] = p[i](t);
    return ret;
}

void Spline :: print (bool showExtraInfo) const {
    std :: cout << dim << " " << p[0].getNumberOfIntervals () << std :: endl;
    for (int i = 0; i < dim; ++ i) {
        if (showExtraInfo)
            std :: cout << "Dimension " << i + 1 << std :: endl;
        (this -> p)[i].print (showExtraInfo);
    }
}

PiecewisePolynomial PPSpline :: SplineImpl (BoundaryCondition bc, const std :: vector <double> &f, const std :: vector <double> &t, double da, double db) {
    if (order != 1 && order != 3)
        throw "Order must be 1 or 3";
    if (f.size () != t.size ())
        throw "Size mismatch";
    int N = f.size ();
    std :: vector <Polynomial> _c (N - 1);
    if (order == 1) {
        // 一阶样条函数
        for (int j = 0; j < N - 1; ++ j) {
            // 计算每一段的系数
            std :: vector <double> x (2), y (2);
            x[0] = t[j]; x[1] = t[j + 1];
            y[0] = f[j]; y[1] = f[j + 1];
            _c[j] = Polynomial (x, y);
        }
        return PiecewisePolynomial (_c, t);
    } else {
        if (bc == BC_NONE)
            throw "Boundary condition must be given";
        // 三阶样条函数
        // 构造二阶差商表
        std :: vector <double> dividedDiff (N - 1); // dividedDiff[i] 代表 f[t_i,t_{i + 1}]
        for (int i = 0; i < N - 1; ++ i)
            dividedDiff[i] = (f[i] - f[i + 1]) / (t[i] - t[i + 1]);
        // 构造三阶差商表
        std :: vector <double> dividedDiff2 (N - 2); // dividedDiff2[i] 代表 f[t_i,t_{i + 1},t_{i + 2}]
        for (int i = 0; i < N - 2; ++ i)
            dividedDiff2[i] = (dividedDiff[i + 1] - dividedDiff[i]) / (t[i + 2] - t[i]);
        // 取等距节点时，lambda 和 mu 都取 0.5，否则应另外计算
        std :: vector <double> lambda (N - 2);
        std :: vector <double> mu (N - 2);
        for (int i = 0; i < N - 2; ++ i) {
            mu[i] = (t[i + 1] - t[i]) / (t[i + 2] - t[i]);
            lambda[i] = (t[i + 2] - t[i + 1]) / (t[i + 2] - t[i]);
        }
        // 根据边界条件，构造方程组右侧向量，并修改 B[0] 和 B[N - 3] 的值
        std :: vector <double> B (N - 2);
        if (bc == BC_COMPLETE_CUBIC) {
            // 完全三次样条，端点一阶导数由 da 和 db 给定
            for (int i = 0; i < N - 2; ++ i)
                B[i] = 3 * mu[i] * dividedDiff[i + 1] + 3 * lambda[i] * dividedDiff[i];
            B[0] -= da * lambda[0];
            B[N - 3] -= db * mu[N - 3];
        } else if (bc == BC_NATURAL) {
            // 自然样条，端点二阶导数为零
            for (int i = 0; i < N - 2; ++ i)
                B[i] = 6 * dividedDiff2[i];
        } else if (bc == BC_SECOND_DERIVATIVE) {
            // 给出二阶导数的三次样条，由 da 和 db 给出
            for (int i = 0; i < N - 2; ++ i)
                B[i] = 6 * dividedDiff2[i];
            B[0] -= da * lambda[0];
            B[N - 3] -= db * mu[N - 3];
        }
        // 用追赶法求解方程组，M 为解向量，对角线元素为 2，对角线下方元素为 lambda[0] 到 lambda[N - 3]，对角线上方元素为 mu[0] 到 mu[N - 3]
        std :: vector <double> M = chaseMethod (N - 2, mu, std :: vector <double> (N - 2, 2), lambda, B);
        // 计算每一段的系数
        if (bc == BC_COMPLETE_CUBIC) {
            std :: vector <double> _M (N);
            _M[0] = da;
            for (int i = 0; i < N - 2; ++ i)
                _M[i + 1] = M[i];
            _M[N - 1] = db;
            for (int i = 0; i < N - 1; ++ i) {
                std :: vector <double> coe (4);
                coe[0] = f[i];
                coe[1] = _M[i];
                coe[2] = (3 * dividedDiff[i] - 2 * _M[i] - _M[i + 1]) / (t[i + 1] - t[i]);
                coe[3] = (_M[i] + _M[i + 1] - 2 * dividedDiff[i]) / (t[i + 1] - t[i]) / (t[i + 1] - t[i]);
                // 转化为标准形式
                Polynomial base ({0}), power ({1});
                for (int j = 0; j < 4; ++ j) {
                    Polynomial temp ({ coe[j] });
                    temp = temp * power;
                    base = base + temp;
                    power = power * Polynomial ({-t[i], 1});
                }
                _c[i] = base;
            }
        } else if (bc == BC_SECOND_DERIVATIVE || bc == BC_NATURAL) {
            std :: vector <double> _M (N);
            _M[0] = bc == BC_NATURAL ? 0 : da;
            for (int i = 0; i < N - 2; ++ i)
                _M[i + 1] = M[i];
            _M[N - 1] = bc == BC_NATURAL ? 0 : db;
            for (int i = 0; i < N - 1; ++ i) {
                std :: vector <double> coe (4);
                coe[0] = f[i];
                coe[1] = dividedDiff[i] - (_M[i + 1] + 2 * _M[i]) / 6 * (t[i + 1] - t[i]);
                coe[2] = _M[i] / 2;
                coe[3] = (_M[i + 1] - _M[i]) / 6 / (t[i + 1] - t[i]);
                // 转化为标准形式
                Polynomial base ({0}), power ({1});
                for (int j = 0; j < 4; ++ j) {
                    Polynomial temp ({ coe[j] });
                    temp = temp * power;
                    base = base + temp;
                    power = power * Polynomial ({-t[i], 1});
                }
                _c[i] = base;
            }
        }
        // _c 为每一段的多项式
        return PiecewisePolynomial (_c, t);
    }
}

PPSpline :: PPSpline (int dim, int order, const Function &f, double a, double b, BoundaryCondition bc, int N, double da, double db) : Spline (dim, order) {
    if (a >= b)
        throw "Invalid interval";
    if (N <= 1)
        throw "Invalid number of intervals";
    
    std :: vector <double> t (N), _f (N);
    for (int j = 0; j < N; ++ j) {
        t[j] = a + (b - a) * j / (N - 1);
        _f[j] = f(t[j]);
    }
    this -> p = { SplineImpl (bc, _f, t, da, db) };
}

PPSpline :: PPSpline (int dim, int order, const Function &f, const std :: vector <double> &t, BoundaryCondition bc, double da, double db) : Spline (dim, order) {
    if (dim != 1)
        throw "Dimension must be 1";
    if (t.size () <= 1)
        throw "Invalid number of intervals";
    
    std :: vector <double> _f (t.size ());
    for (int j = 0; j < t.size (); ++ j)
        _f[j] = f(t[j]);
    this -> p = { SplineImpl (bc, _f, t, da, db) };
}

PPSpline :: PPSpline (int dim, int order, const std :: vector <std :: vector <double> > &points, BoundaryCondition bc) : Spline (dim, order) {
    if (points.size () <= 1)
        throw "Invalid number of intervals";
    if (points[0].size () != dim)
        throw "Dimension mismatch";
    
    std :: vector <double> t;
    // 使用累积弦长法来产生行止点
    t.push_back (0);
    for (int i = 1; i < points.size (); ++ i) {
        double dist = 0;
        static double totalDist = 0;
        for (int j = 0; j < points[i].size (); ++ j)
            dist += (points[i][j] - points[i - 1][j]) * (points[i][j] - points[i - 1][j]);
        dist = sqrt (dist);
        totalDist += dist;
        t.push_back (totalDist);
    }

    // 对每个维度分别产生样条曲线
    for (int i = 0; i < dim; ++ i) {
        std :: vector <double> _f;
        for (int j = 0; j < points.size (); ++ j)
            _f.push_back (points[j][i]);
        (this -> p).push_back (SplineImpl (bc, _f, t, 0.0, 0.0));
    }
}

double BSpline :: BSplineBasis (int i, int k, double x) const {
    if (!k)
        return t[i - 1] < x && x <= t[i];
    else
        return (x - t[i - 1]) / (t[i + k - 1] - t[i - 1]) * BSplineBasis (i, k - 1, x) + (t[i + k] - x) / (t[i + k] - t[i]) * BSplineBasis (i + 1, k - 1, x);
}

double BSpline :: BSplineBasisDerivative (int i, int k, double x) const {
    return k * BSplineBasis (i, k - 1, x) / (t[i + k - 1] - t[i - 1]) - k * BSplineBasis (i + 1, k - 1, x) / (t[i + k] - t[i]);
}

double BSpline :: BSplineBasisSecondDerivative (int i, int k, double x) const {
    return k * BSplineBasisDerivative (i, k - 1, x) / (t[i + k - 1] - t[i - 1]) - k * BSplineBasisDerivative (i + 1, k - 1, x) / (t[i + k] - t[i]);
}

PiecewisePolynomial BSpline :: SplineImpl (BoundaryCondition bc, const std :: vector <double> &f, const std :: vector <double> &t, double da, double db) {
    if (dim > 3)
        throw "Dimension unsupported";
    (this -> t).clear ();
    for (int i = order; i >= 1; -- i)
        (this -> t).push_back (t[0] - i);
    for (int i = 0; i < t.size (); ++ i)
        (this -> t).push_back (t[i]);
    for (int i = 1; i <= order; ++ i)
        (this -> t).push_back (t[t.size () - 1] + i);
    int N = f.size ();
    std :: vector <std :: vector <double>> A (N + order - 1, std :: vector <double> (N + order - 1, 0.0));
    std :: vector <double> B (N + order - 1, 0.0);
    if (order == 3) {
        // 构造方程组
        for (int i = 0; i < N; ++ i) {
            for (int j = 0; j < order; ++ j)
                A[i][i + j] = BSplineBasis (i + j + 1, order, t[i]);
            B[i] = f[i];
        }
        // 默认使用自然边界条件
        for (int i = 0; i < order; ++ i) {
            A[N][i] = BSplineBasisSecondDerivative (i + 1, order, t[0]);
            A[N + 1][N - 1 + i] = BSplineBasisSecondDerivative (N + i, order, t[N - 1]);
            B[N] = 0;
            B[N + 1] = 0;
        }
    } else if (order == 2) {
        A[0][0] = BSplineBasis (1, order, t[0]);
        A[0][1] = BSplineBasis (2, order, t[0]);
        B[0] = f[0];
        for (int i = 0; i < N - 1; ++ i) {
            double m = (t[i] + t[i + 1]) / 2;
            A[i + 1][i] = BSplineBasis (i + 1, order, m);
            A[i + 1][i + 1] = BSplineBasis (i + 2, order, m);
            A[i + 1][i + 2] = BSplineBasis (i + 3, order, m);
            B[i + 1] = f[i + 1];
        }
        A[N][N - 1] = BSplineBasis (N, order, t[N - 1]);
        A[N][N] = BSplineBasis (N + 1, order, t[N - 1]);
        B[N] = f[N - 1];
    }
    // 求解方程组
    std :: vector <double> coe;
    if (order > 1)
        coe = GaussEliminate (N + order - 1, A, B);
    else
        coe = f;
    // 构建返回结果的逐段多项式
    std :: vector <Polynomial> c (N - 1);
    for (int i = 0; i < N - 1; ++ i) {
        // 算基函数太麻烦了，不如取几个点来插值
        std :: vector <double> x (order + 1), y (order + 1);
        for (int j = 0; j <= order; ++ j) {
            x[j] = t[i] + (t[i + 1] - t[i]) * j / order;
            y[j] = 0;
            for (int k = 0; k < N + order - 1; ++ k)
                y[j] += coe[k] * BSplineBasis (k + 1, order, x[j]);
        }
        c[i] = Polynomial (x, y);
    }
    return PiecewisePolynomial(c, t);
}

BSpline :: BSpline (int dim, int order, const Function &f, double a, double b, int N) : Spline (dim, order) {
    if (a >= b)
        throw "Invalid interval";
    if (N <= 1)
        throw "Invalid number of intervals";
    
    std :: vector <double> t (N), _f (N);
    for (int j = 0; j < N; ++ j) {
        t[j] = a + (b - a) * j / (N - 1);
        _f[j] = f(t[j]);
    }
    this -> p = { SplineImpl (BC_NONE, _f, t, 0, 0) };
}

BSpline :: BSpline (int dim, int order, const Function &f, const std :: vector <double> &t) : Spline (dim, order) {
    if (dim != 1)
        throw "Dimension must be 1";
    if (t.size () <= 1)
        throw "Invalid number of intervals";
    
    std :: vector <double> _f (t.size ());
    for (int j = 0; j < t.size (); ++ j)
        _f[j] = f(t[j]);
    this -> p = { SplineImpl (BC_NONE, _f, t, 0, 0) };
}

BSpline :: BSpline (int dim, int order, const std :: vector <std :: vector <double> > &points) : Spline (dim, order) {
    if (points.size () <= 1)
        throw "Invalid number of intervals";
    if (points[0].size () != dim)
        throw "Dimension mismatch";
    
    std :: vector <double> t;
    // 使用累积弦长法来产生行止点
    t.push_back (0);
    for (int i = 1; i < points.size (); ++ i) {
        double dist = 0;
        static double totalDist = 0;
        for (int j = 0; j < points[i].size (); ++ j)
            dist += (points[i][j] - points[i - 1][j]) * (points[i][j] - points[i - 1][j]);
        dist = sqrt (dist);
        totalDist += dist;
        t.push_back (totalDist);
    }

    // 对每个维度分别产生样条曲线
    for (int i = 0; i < dim; ++ i) {
        std :: vector <double> _f;
        for (int j = 0; j < points.size (); ++ j)
            _f.push_back (points[j][i]);
        (this -> p).push_back (SplineImpl (BC_NONE, _f, t, 0, 0));
    }
}