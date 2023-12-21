import numpy as np

def hilbert_matrix(n):
    """Create a Hilbert matrix of size n x n."""
    H = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            H[i, j] = 1.0 / (i + j + 1)
    return H

def solve(n):
    H = hilbert_matrix(n + 1)
    b1 = np.zeros(n + 1)
    b2 = np.zeros(n + 1)
    tmp = 0

    for i in range(1, n + 2):
        b1[i - 1] = (-1) ** (i - 1)
        if i >= 2:
            for j in range(1, i):
                tmp += (-1) ** (j + i - 1) / j
        b2[i - 1] = tmp
        tmp = 0

    beta = np.linalg.solve(H, b1)
    gamma = np.linalg.solve(H, b2)
    print("beta =", beta)
    print("gamma =", gamma)

    b_ln2 = b1 * np.log(2) + b2
    alpha_ln2 = np.linalg.solve(H, b_ln2)
    print("alpha_ln2 =", alpha_ln2)

    b_float = b1 * 0.69315 + b2
    alpha_float = np.linalg.solve(H, b_float)
    print("alpha_float_0.69315 =", alpha_float)

    print(f"The condition number of Hilbert matrix of order {n + 1} is", np.linalg.cond(H, 2))

    a = 1e-10
    tikhA = a * np.eye(n+1) + H.T @ H
    tikhB = H.T @ b_float
    alpha_float_tikh = np.linalg.solve(tikhA, tikhB)
    print("alpha_float by tikhonov regularization is", alpha_float_tikh)

for n in range(6):
    print("n = ", n + 1)
    solve(n)
