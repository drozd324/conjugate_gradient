import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

colors = [
    "tab:blue",
    "tab:orange",
    "tab:green",
    "tab:red",
    "tab:purple",
    "tab:brown",
    "tab:pink",
    "tab:gray",
    "tab:olive",
    "tab:cyan"]

for k, N in enumerate([10**j for j in range(1, 5)]):

	A = np.zeros((N, N))
	for i in range(N):
		for j in range(N):
			A[i,j] = (N - abs(i - j)) / N

	residuals = np.loadtxt(f"writeup/q3out{N}.txt")

	eigenvals = np.linalg.eig(A)[0]
	sqrt_kappa = np.sqrt(eigenvals[0] / eigenvals[-1])

	e_0 = np.linalg.norm(residuals[0] - residuals[-1])
	e_k = lambda k : 2*((((sqrt_kappa - 1) / (sqrt_kappa + 1) ) )**k) * abs(e_0)
	
	iterator = []
	i = 1
	while i < residuals.shape[0]:
		iterator.append(i)
		i *= 2
		
	norm_res = [np.linalg.norm(residuals[j]) for j in iterator]
	iterations = np.array([j for j in iterator])

	#norm_res = [np.linalg.norm(residuals[j]) for j in range(residuals.shape[0])]
	#iterations = np.array([j for j in range(residuals.shape[0])])

	plt.semilogx(iterations, norm_res, "o-", label=f"N={N}", color=colors[k])
	plt.semilogx(iterations, e_k(iterations), "o--", label=f"error bound N={N}", color=colors[k])

plt.legend()
plt.xlabel("iteration")
plt.ylabel("error")
plt.savefig("writeup/q3plot.png", dpi=300)
plt.show()
