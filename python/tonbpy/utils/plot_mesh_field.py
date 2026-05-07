# plot_mesh_field.py
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.tri as mtri
import sys

if len(sys.argv) < 2:
    print("usage: python plot_mesh_field.py <prefix>")
    sys.exit(1)

prefix = sys.argv[1]
V  = np.loadtxt(prefix + "_verts.csv", delimiter=",")   # Nx2
F  = np.loadtxt(prefix + "_faces.csv", delimiter=",", dtype=int)  # Mx3
val = np.loadtxt(prefix + "_values.csv")                # N

x, y = V[:,0], V[:,1]
tri = mtri.Triangulation(x, y, F)

plt.figure(figsize=(7,6))
# filled contours
cs = plt.tricontourf(tri, val, levels=16)
plt.colorbar(cs, label="value")

# mesh overlay
plt.triplot(tri, linewidth=0.5)

plt.gca().set_aspect('equal', adjustable='box')
plt.title("Interpolated field (vertex values)")
plt.tight_layout()
plt.show()
