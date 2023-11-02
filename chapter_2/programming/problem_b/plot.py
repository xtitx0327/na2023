import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return 1.0 / (1.0 + x * x)

def polynomial_2(x):
    return 1 - 0.0384615 * x ** 2

def polynomial_4(x):
    return 1 - 0.171088 * x ** 2 + 0.00530504 * x ** 4

def polynomial_6(x):
    return 1 - 5.55112e-017 * x - 0.351364 * x ** 2 - 6.93889e-018 * x ** 3  + 0.0335319 * x ** 4 - 0.000840633 * x ** 6

def polynomial_8(x):
    return 1 + 2.77556e-017 * x - 0.528121 * x ** 2 - 6.93889e-017 * x ** 3 + 0.0981875 * x ** 4 - 0.00658016 * x ** 6 + 0.000137445 * x ** 8

x = np.linspace(-5, 5, 400)

plt.figure(figsize=(10, 6))
plt.plot(x, f(x), label='f(x) = 1/(1+x^2)', linewidth=2, color='black')
plt.plot(x, polynomial_2(x), label='n = 2', linestyle='dashed')
plt.plot(x, polynomial_4(x), label='n = 4', linestyle='dashed')
plt.plot(x, polynomial_6(x), label='n = 6', linestyle='dashed')
plt.plot(x, polynomial_8(x), label='n = 8', linestyle='dashed')
plt.title('Runge Phenomenon')
plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.grid(True)
plt.savefig('runge.png')
