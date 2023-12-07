import matplotlib.pyplot as plt

# Data from the MATLAB code
x_2 = [-0.1875, -0.125, -0.0625, 0.0625, 0.125, 0.1875]
y_2 = [0, 0, 0, 0, 0, 0]

# Plotting
plt.scatter(x_2, y_2, s=7, c='blue', label='Subnormal numbers')
plt.legend()
plt.title('picture B2')
plt.savefig('problem_b2.png')
