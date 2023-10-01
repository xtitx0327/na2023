#ifndef __wxtsolver__
#define __wxtsolver__

#include <cmath>

class Function {
private:
    double (*f)(double);

public:
    Function(double (*f)(double)) : f(f) {}

    double operator()(double x) {
        return f(x);
    }
};

class EquationSolver {
protected:
    double eps;
    int maxIter;

public:
    EquationSolver(double eps = 1e-8, int maxIter = 100) : eps(eps), maxIter(maxIter) {}
    virtual double solve(Function& func, double a, double b) = 0;
    virtual double solve(Function& func, Function& derFunc, double x0) = 0;
};

class BisectionSolver : public EquationSolver {
public:
    double solve(Function& func, double a, double b) {
        int iter = 0;

        while (iter <= maxIter && fabs(func(a)) >= eps) {
            double mid = (a + b) / 2;
            if (func(a) * func(mid) > 0)
                a = mid;
            else
                b = mid;

            ++iter;
        }

        return (a + b) / 2;
    }

    double solve(Function& func, Function& derFunc, double x0) {
        throw "NotImplementedError";
        return 0.0;
    }
};

class NewtonSolver : public EquationSolver {
public:
    double solve(Function& func, Function& derFunc, double x0) {
        int iter = 0;
        double ret = x0;

        while (iter <= maxIter && fabs(func(ret)) >= eps) {
            ret = ret - func(ret) / derFunc(ret);
            ++iter;
        }

        return ret;
    }

    double solve(Function& func, double a, double b) {
        throw "NotImplementedError";
        return 0.0;
    }
};

class SecantSolver : public EquationSolver {
private:
    double delta;

public:
    SecantSolver(double delta = 1e-8, double eps = 1e-8, int maxIter = 100)
        : EquationSolver(eps, maxIter), delta(delta) {}

    double solve(Function& func, double a, double b) {
        int iter = 0;

        while (iter <= maxIter && fabs(func(b)) >= eps && fabs(b - a) >= delta) {
            double c = a - func(a) * (b - a) / (func(b) - func(a));
            a = b;
            b = c;
            ++iter;
        }

        return b;
    }

    double solve(Function& func, Function& derFunc, double x0) {
        throw "NotImplementedError";
        return 0.0;
    }
};

#endif
