import numpy as np

def symm_og(A, B, C, n, m, k, alpha=1.0, beta=1.0):
    for j in range(n):
                    for i in range(m-1, -1, -1):
                        temp1 = alpha*B[i][j]
                        temp2 = 0
                        #print(f'{i}, {j}')
                        for k in range(i+1, m):
                            #print(f'{k}')
                            C[k][j] = C[k][j] + temp1*A[k][i]
                            temp2 = temp2 + B[k][j]*(A[k][i])
                        if beta==0:
                            C[i][j] = temp1*A[i][i]+ alpha*temp2
                        else:
                            C[i][j] = beta*C[i][j] + temp1*A[i][i] + alpha*temp2
    return C

def symm_test(A, B, C, M, N, K):

    # j indexes the rows of A and the rows of B
    for j in range(N):
        # i indexes the columns of A
        for i in range(M):
            # k indexes the columns of B
            for k in range(M - ((M - 1 - i) + 1)):
                C[(k + ((M - 1 - i) + 1)), j] += B[(M - 1 - i), j] * A[(k + ((M - 1 - i) + 1)), (M - 1 - i)]
                C[(M - 1 - i), j] += A[j, (M - 1 - i)] * B[j, (k + ((M - 1 - i) + 1))]
            C[(M - 1 - i), j] += B[(M - 1 - i), j]*A[(M - 1 - i), (M - 1 - i)]
    
    return C

A = np.array([[2, 2, 2, 2],
              [2, 2, 2, 2],
              [2, 2, 2, 2],
              [2, 2, 2, 2]])

B = np.array([[3, 3, 3, 3],
              [3, 3, 3, 3],
              [3, 3, 3, 3],
              [3, 3, 3, 3]])

C_1 = np.zeros((4, 4))
C_2 = np.zeros((4, 4))

C_test = symm_test(A, B, C_1, 4, 4, 4)

print(C_test)

C_correct = symm_og(A, B, C_2, 4, 4, 4)

print(C_correct)

print(np.dot(A, B))