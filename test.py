import scipy
import numpy as np

N = 10
A = np.zeros((N, N))
b = np.ones(N)
x = np.zeros(N)

for i in range(N):
	for j in range(N):
		A[i,j] = (N - abs(i - j)) / N

sol = scipy.sparse.linalg.cg(A, b)

print(sol[0].tolist())
