import os
import re
import sys
from matplotlib import pyplot as plt

# Ruta de tu ejecutable con respecto al script.
EXECUTABLE_PATH = './incremento-fijo'

# Expresiones regulares de los valores a buscar.
c_pattern = re.compile(r'Porcentaje de tiempo ocioso: ([0-9]+\.[0-9]+)')
avg_pattern = re.compile(r'Número medio de clientes en cola: ([0-9]+\.[0-9]+)')

# Input parameters
try:
    simulation_time = int(sys.argv[1])
    x = float(sys.argv[2])
    vision = float(sys.argv[3])
except IndexError:
    print("Numero de argumentos invalido")
    exit()

c_values = []
avg_distances = []
for i in range(1,6):
	# Ejecuta el comando y guarda el resultado en una variable.
	cmd = f"{EXECUTABLE_PATH} {simulation_time} {x} {vision}"
	result = os.popen(cmd).read()

	# Busca todos los valores y los mapea a floats o enteros ya que son strings
	# y para dibujarlos tienen que ser numeros.
	c_values.append(list(map(float, re.findall(c_pattern, result))))
	avg_distances.append(list(map(float, re.findall(avg_pattern, result))))
	n_ejecuciones = list(range(150))


	# Buscar valor optimo de la distancia media y su valor de c.
	# best_distance = min(avg_distances)
	# best_c = c_values[avg_distances.index(best_distance)]

	# print(f"Mejor posicion inicial: {best_c}")
	# print(f"Mejor distancia: {best_distance}")

	# Dibuja los datos
	x = x*2
	vision = vision*2

for i in range(5):
	plt.plot(n_ejecuciones, c_values[i])

plt.xlabel('Ejecución')
plt.ylabel('% de tiempo ocioso')
plt.tight_layout()

# Guarda la gráfica con el nombre del ejecutable y los parametros dados.
output_name = os.path.basename(EXECUTABLE_PATH)
plt.savefig(f"{output_name}_{simulation_time}-{x}-{vision}-ocioso.png")
plt.show()

# Dibuja los datos
for i in range(5):
	plt.plot(n_ejecuciones, avg_distances[i])
plt.xlabel('Ejecución')
plt.ylabel('Número de clientes en cola')
plt.tight_layout()

# Guarda la gráfica con el nombre del ejecutable y los parametros dados.
output_name = os.path.basename(EXECUTABLE_PATH)
plt.savefig(f"{output_name}_{simulation_time}-{x}-{vision}-cola.png")