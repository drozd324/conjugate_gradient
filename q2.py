import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data_sol = np.loadtxt("writeup/q2sol.txt")
data_csv = pd.read_csv("writeup/q2out.csv")

N = data_csv["N"].tolist()
u = np.reshape(data_sol, (N[-1], N[-1])) 

plt.imshow(u)
cbar = plt.colorbar()  # adds a color scale bar
cbar.set_label("u(x)")
#plt.title("plot of fuction u(x)")
plt.xlabel("x")
plt.ylabel("y")
plt.savefig("writeup/q2plot.png", dpi=300)
plt.show()
