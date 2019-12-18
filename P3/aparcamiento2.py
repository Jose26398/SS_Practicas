from matplotlib import pyplot as plt

c_values1 = [0.001671, 0.002937, 0.003491, 0.007858, 0.0205443]
c_values2 = [0.002071, 0.002562, 0.001119, 0.001464, 0.002939]
n_ejecuciones = list(range(5))



plt.plot(n_ejecuciones, c_values1)
plt.plot(n_ejecuciones, c_values2)
plt.xlabel('Ejecución')
plt.ylabel('% de tiempo ocioso')
plt.tight_layout()
plt.savefig(f"tiempos.png")
