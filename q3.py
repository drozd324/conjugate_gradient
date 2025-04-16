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

for k, N in enumerate([10**j for j in range(1, 4)]):

	A = np.zeros((N, N))
	for i in range(N):
		for j in range(N):
			A[i,j] = (N - abs(i - j)) / N

	eigenvals = np.linalg.eig(A)[0]
	sqrt_kappa = np.sqrt(eigenvals[0] / eigenvals[-1])

	error = np.loadtxt(f"writeup/q3out{N}.txt")
	print(f"len of file = {len(error)}")
	e_k = lambda k : 2*((((sqrt_kappa - 1) / (sqrt_kappa + 1) ) )**k) * abs(error[0])
	
	iterator = []
	i = 1
	while i < len(error):
		iterator.append(i)
		i *= 2
		
	iterations = np.array([j for j in iterator])
	error = [error[j] for j in iterator]

	#iterations = np.arange(0, len(error), 1);

	plt.semilogx(iterations, error, "-", label=f"N={N}", color=colors[k])
	plt.semilogx(iterations, e_k(iterations), "--", label=f"error bound N={N}", color=colors[k])

plt.legend()
plt.xlabel("iteration")
plt.ylabel("error")
plt.savefig("writeup/q3plot.png", dpi=300)
plt.show()
