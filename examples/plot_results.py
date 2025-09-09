import matplotlib.pyplot as plt

# pontos fornecidos
points = [
    (1, 2),
    (2, 1),
    (3, 2),
    (7, 4),
    (5, 9),
    (6, 1),
    (0, 3),
    (4, 7),
    (8, 2),
    (3, 5)
]

# separar em listas de x e y
x_vals = [p[0] for p in points]
y_vals = [p[1] for p in points]

# plot
plt.figure(figsize=(6,6))
plt.scatter(x_vals, y_vals, color="blue")

# adicionar labels
for (x, y) in points:
    plt.text(x+0.1, y+0.1, f"({x},{y})", fontsize=8)

plt.xlabel("x")
plt.ylabel("y")
plt.title("Plot dos pontos fornecidos")
plt.grid(True)
plt.show()
