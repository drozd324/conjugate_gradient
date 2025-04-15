import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data_sol = np.loadtxt("writeup/q2sol.txt")
data_csv = pd.read_csv("writeup/q2out.csv")

N = data_csv["N"].tolist()

print("printing csv data")
print(data_csv)

print("data sol --------------")
print(data_sol)

N_index = -1
u = np.reshape(data_sol, (N[N_index], N[N_index])) 

plt.imshow(u)
cbar = plt.colorbar()  # adds a color scale bar
cbar.set_label("u(x)")
plt.title(f"plot of fuction u(x) for N = {N[N_index]}")
plt.xlabel("x")
plt.ylabel("y")
plt.savefig("writeup/q2plot.png", dpi=300)
plt.show()


#plt.clf()
#plt.figure()
#plt.plot(

