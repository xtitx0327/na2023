#ifndef _XTSPLINE_H_
#define _XTSPLINE_H_

#include <vector>
#include <iostream>
#include <cmath>

#include "xtlapack.h"

class Function {
    private:
        double (*func)(double x);
    public:
        Function () {}
        Function (double (*f)(double x));
        virtual double operator()(double x) const;
        virtual ~Function () {}
};

class Polynomial : public Function {
    private:
        // 多项式系数，从低到高
        std :: vector <double> c;
    public:
        Polynomial () {}
        // 通过传入系数构造多项式
        Polynomial (const std :: vector <double> &c);
        // 通过 Newton 插值构造多项式
        Polynomial (const std :: vector <double> &x, const std :: vector <double> &y);
        // 多项式的加、减、乘运算
        Polynomial operator + (const Polynomial &p) const;
        Polynomial operator - (const Polynomial &p) const;
        Polynomial operator * (const Polynomial &p) const;
        virtual double operator ()(double x) const;
        void print() const;
        virtual ~Polynomial () {}
        Polynomial derivative ();
};

class PiecewisePolynomial : public Function {
    private:
        // 每一段的多项式
        std :: vector <Polynomial> p;
        // 每一段的起点及最后的终点（长度为 p.size () + 1）
        std :: vector <double> t;
    public:
        PiecewisePolynomial () {}
        // 通过传入每一段的多项式及起点和终点构造分段多项式
        PiecewisePolynomial (const std :: vector <Polynomial> &p, const std :: vector <double> &t);
        virtual double operator ()(double x) const;
        void print (bool showExtraInfo = false) const;
        int getNumberOfIntervals () const { return p.size (); }
        PiecewisePolynomial derivative ();
        ~PiecewisePolynomial () {}
};

class Curve {
    private:
        std :: vector <Function *> params;
    protected:
        int dim;
    public:
        Curve (int dim) : dim (dim) {}
        Curve (const std :: vector <Function *> &f);
        Function operator [](int i) const { return *(params[i]); }
        std :: vector <double> operator ()(double t) const;
        virtual ~Curve () {}
};

enum BoundaryCondition {
    BC_NONE,
    BC_COMPLETE_CUBIC,
    BC_SECOND_DERIVATIVE,
    BC_NATURAL,
};

class Spline : public Curve {
    private:
        // 样条的实际实现，由子类实现
        virtual PiecewisePolynomial SplineImpl (BoundaryCondition bc, const std :: vector <double> &f, const std :: vector <double> &t, double da, double db) = 0;
    protected:
        // 每一维的样条函数
        std :: vector <PiecewisePolynomial> p;
        // 每一维的样条函数的多项式阶数
        int order;
    public:
        Spline (int dim, int order) : Curve (dim), order (order) {}
        Spline (int dim, int order, const std :: vector <PiecewisePolynomial> &p) : Curve (dim), order (order), p (p) {}
        std :: vector <double> operator ()(double t) const;
        void print(bool showExtraInfo = false) const;
        ~Spline () {}
};

class PPSpline : public Spline {
    private:
        PiecewisePolynomial SplineImpl (BoundaryCondition bc, const std :: vector <double> &f, const std :: vector <double> &t, double da, double db);
    public:
        // 通过对一元函数拟合构造样条函数，可以选择给出节点数进行均匀插值，也可以给出节点；在 BC_COMPLETE_CUBIC 和 BC_SECOND_DERIVATIVE 时，还要给出边界的一阶或二阶导数
        PPSpline (int dim, int order, const Function &f, double a, double b, BoundaryCondition bc = BC_NONE, int N = 100, double da = 0.0, double db = 0.0);
        PPSpline (int dim, int order, const Function &f, const std :: vector <double> &t, BoundaryCondition bc = BC_NONE, double da = 0.0, double db = 0.0);
        // 通过对高维空间中散点拟合构造样条函数
        PPSpline (int dim, int order, const std :: vector <std :: vector <double> > &points, BoundaryCondition bc = BC_NONE);
        ~PPSpline () {}
};

class BSpline : public Spline {
    private:
        PiecewisePolynomial SplineImpl (BoundaryCondition bc, const std :: vector <double> &f, const std :: vector <double> &t, double da, double db);
        std :: vector <double> t;
        // 计算 B 样条基函数 B_i^k 在 x 处的值
        double BSplineBasis (int i, int k, double x) const;
        // 计算 B 样条基函数 B_i^k 在 x 处的导数
        double BSplineBasisDerivative (int i, int k, double x) const;
        // 计算 B 样条基函数 B_i^k 在 x 处的二阶导数
        double BSplineBasisSecondDerivative (int i, int k, double x) const;
    public:
        // 通过对一元函数拟合构造样条函数，可以选择给出节点数进行均匀插值，也可以给出节点
        BSpline (int dim, int order, const Function &f, double a, double b, int N = 100);
        BSpline (int dim, int order, const Function &f, const std :: vector <double> &t);
        // 通过对高维空间中散点拟合构造样条函数
        BSpline (int dim, int order, const std :: vector <std :: vector <double> > &points);
        ~BSpline () {}
};

#endif