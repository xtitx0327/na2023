import subprocess
import matplotlib.pyplot as plt
import numpy as np

def get_cpp_output():
    # 调用 C++ 程序
    result = subprocess.run(['./problem_c'], stdout=subprocess.PIPE)
    return result.stdout.decode('utf-8')

def plot_data(data):
    for n, points in data.items():
        x_vals = [point[0] for point in points]
        y_vals = [point[1] for point in points]
        plt.plot(x_vals, y_vals, label=f'n={n}')

    # Plot the original function
    x = np.linspace(-1, 1, 400)
    y = [1.0 / (1.0 + 25.0 * xi**2) for xi in x]
    plt.plot(x, y, label='f(x)', color='black', linestyle='--')
    
    plt.title('Chebyshev Interpolation vs. Original Function')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.grid(True)
    plt.savefig('chebyshev.png')
    plt.show()

output = get_cpp_output()
lines = output.split('\n')

data = {}
current_n = None

for line in lines:
    if "n =" in line:
        current_n = int(line.split('=')[1].strip()[:-1])
        data[current_n] = []
    elif "x =" in line:
        parts = line.split(',')
        x_val = float(parts[0].split('=')[1])
        y_val = float(parts[2].split('=')[1])
        data[current_n].append((x_val, y_val))

plot_data(data)