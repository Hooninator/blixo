import numpy as np


def sgemm(M, K, A, C):
    for i in range(0, M):
        for j in range(0, M):
            for k in range(0, K):
                C[i, j] += A[i, k]*A[j, k]
    return C

A = np.random.rand(10, 16)
C = np.zeros((10, 10))

C = sgemm(10, 16, A, C)
print(C)
print("================")
C2 = np.dot(A, np.transpose(A))
print(C2)
for i in range(10):
    for j in range(10):
        if C[i, j]!=C2[i, j]:
            print(f"{C[i, j]} vs {C2[i, j]}")
            break

