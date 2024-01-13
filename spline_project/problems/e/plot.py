import sys
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

def read_polynomials(file_path):
    with open(file_path, 'r') as file:
        d, N = map(int, file.readline().split())
        polynomials = []
        for _ in range(d):
            dim_polynomials = []
            for _ in range(N):
                a, b = map(float, file.readline().split())
                coefficients = [float(c) for c in file.readline().split()]
                dim_polynomials.append((a, b, np.poly1d(coefficients[::-1])))
            polynomials.append(dim_polynomials)
        return d, N, polynomials

def evaluate_polynomial(t, poly_interval):
    for a, b, poly in poly_interval:
        if a <= t <= b:
            return poly(t)
    return None

def plot_curve(d, N, polynomials, filename = "plot.png"):
    plt.clf()
    t_values = np.linspace(min(a for dim in polynomials for a, _, _ in dim), 
                           max(b for dim in polynomials for _, b, _ in dim), 1000)

    if d == 1:
        for a, b, _ in polynomials[0]:
            t_segment = np.linspace(a, b, 100)
            y_values = [evaluate_polynomial(t, polynomials[0]) for t in t_segment]
            plt.plot(t_segment, y_values)
            plt.scatter([a, b], [evaluate_polynomial(a, polynomials[0]), evaluate_polynomial(b, polynomials[0])], color='red')
        plt.xlabel('t')
        plt.ylabel('f(t)')
    elif d == 2:
        for i in range(N):
            a, b, _ = polynomials[0][i]
            t_segment = np.linspace(a, b, 100)
            x_values = [evaluate_polynomial(t, polynomials[0]) for t in t_segment]
            y_values = [evaluate_polynomial(t, polynomials[1]) for t in t_segment]
            plt.plot(x_values, y_values)
            plt.scatter([evaluate_polynomial(a, polynomials[0]), evaluate_polynomial(b, polynomials[0])], 
                        [evaluate_polynomial(a, polynomials[1]), evaluate_polynomial(b, polynomials[1])], color='red')
            # 进一步绘制关于y轴对称的曲线，将多项式中奇数次项的系数取反，偶数次项的系数保持不变
            x_values = [-x for x in x_values]
            plt.plot(x_values, y_values)
            plt.scatter([-evaluate_polynomial(a, polynomials[0]), -evaluate_polynomial(b, polynomials[0])],
                        [evaluate_polynomial(a, polynomials[1]), evaluate_polynomial(b, polynomials[1])], color='red')
        plt.xlabel('x(t)')
        plt.ylabel('y(t)')
    elif d == 3:
        fig = plt.figure()
        ax = fig.add_subplot(111, projection='3d')
        for i in range(N):
            a, b, _ = polynomials[0][i]
            t_segment = np.linspace(a, b, 100)
            x_values = [evaluate_polynomial(t, polynomials[0]) for t in t_segment]
            y_values = [evaluate_polynomial(t, polynomials[1]) for t in t_segment]
            z_values = [evaluate_polynomial(t, polynomials[2]) for t in t_segment]
            ax.plot(x_values, y_values, z_values)
            ax.scatter([evaluate_polynomial(a, polynomials[0]), evaluate_polynomial(b, polynomials[0])], 
                       [evaluate_polynomial(a, polynomials[1]), evaluate_polynomial(b, polynomials[1])], 
                       [evaluate_polynomial(a, polynomials[2]), evaluate_polynomial(b, polynomials[2])], color='red')
        ax.set_xlabel('x(t)')
        ax.set_ylabel('y(t)')
        ax.set_zlabel('z(t)')

    plt.savefig(filename)

# 主程序
if __name__ == "__main__":
    filenames = ["10.txt", "40.txt", "160.txt"]

    for filename in filenames:
        d, N, polynomials = read_polynomials(filename)
        plot_curve(d, N, polynomials, filename[:-4])