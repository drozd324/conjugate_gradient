import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

data_sol = np.loadtxt("writeup/q2sol.txt")
data_csv = pd.read_csv("writeup/q2out.csv")

N = data_csv["N"].tolist()
u = np.reshape(data_sol, (N[-1], N[-1])) 

plt.imshow(u)
plt.colorbar()  # adds a color scale bar
plt.title("imshow() Example")
plt.xlabel("X-axis")
plt.ylabel("Y-axis")
plt.show()

#x = y = np.linspace(0, 1, num_grid_pts//2)
#X, Y = np.meshgrid(x, y)
#
##Z = np.sin(np.sqrt(X**2 + Y**2))
#Z = np.array(u).reshape(N[-2], N[-2])
#
## Create a 3D surface plot
#fig = plt.figure(figsize=(10, 6))
#ax = fig.add_subplot(111, projection='3d')
#surf = ax.plot_surface(X, Y, Z, cmap='viridis')
#
## Add a color bar and labels
#fig.colorbar(surf)
#ax.set_title("3D Surface Plot")
#ax.set_xlabel("X-axis")
#ax.set_ylabel("Y-axis")
##ax.set_zlabel("Z-axis (sin(sqrt(X^2 + Y^2)))")
#
#plt.show()
