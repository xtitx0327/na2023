import matplotlib.pyplot as plt
import numpy as np

# Define the interval
x = np.linspace(0.99, 1.01, 101)

# Define the functions
def f(x):
    return x**8 - 8*x**7 + 28*x**6 - 56*x**5 + 70*x**4 - 56*x**3 + 28*x**2 - 8*x + 1

def g(x):
    return (((((((x - 8)*x + 28)*x - 56)*x + 70)*x - 56)*x + 28)*x - 8)*x + 1

def h(x):
    return (x - 1)**8

# Calculate the function values
f_values = f(x)
g_values = g(x)
h_values = h(x)

# Plot the functions
plt.figure(figsize=(14, 7))

# Plot f(x)
plt.subplot(1, 3, 1)
plt.plot(x, f_values, label='f(x)')
plt.title('f(x)')
plt.xlabel('x')
plt.ylabel('f(x)')
plt.grid(True)

# Plot g(x)
plt.subplot(1, 3, 2)
plt.plot(x, g_values, label='g(x)', color='orange')
plt.title('g(x)')
plt.xlabel('x')
plt.ylabel('g(x)')
plt.grid(True)

# Plot h(x)
plt.subplot(1, 3, 3)
plt.plot(x, h_values, label='h(x)', color='green')
plt.title('h(x)')
plt.xlabel('x')
plt.ylabel('h(x)')
plt.grid(True)

# Adjust layout to prevent overlap
plt.tight_layout()

# Show the plots
plt.savefig('problem_a.png')