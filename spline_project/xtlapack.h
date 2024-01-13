#ifndef _XTLAPACK_H_
#define _XTLAPACK_H_

#include <vector>

// 追赶法求解三对角方程组
std :: vector <double> chaseMethod (int n, const std :: vector <double> &a, const std :: vector <double> &diag, const std :: vector <double> &b, const std :: vector <double> &B);

// 列主元高斯消去法求解一般的线性方程组
std :: vector <double> GaussEliminate (int n, const std :: vector <std :: vector <double>> &A, const std :: vector <double> &b);

#endif