import matplotlib.pyplot as plt

# Data
x_1 = [-3.5, -3, -2.5, -2, -1.75, -1.5, -1.25, -1, -0.875, -0.75, -0.625, -0.5, 0, 0.5, 0.625, 0.75, 0.875, 1, 1.25, 1.5, 1.75, 2, 2.5, 3, 3.5]
y_1 = [0] * 25

# Plot
plt.scatter(x_1, y_1, 7, color='blue', label='Normal numbers')
plt.legend()
plt.title('picture B1')
plt.savefig('problem_b1.png')
