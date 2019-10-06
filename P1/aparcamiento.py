import os
import re
import sys
from matplotlib import pyplot as plt

# Ruta de tu ejecutable con respecto al script.
EXECUTABLE_PATH = 'aparcamiento.exe'

# Expresiones regulares de los valores a buscar.
c_pattern = re.compile(r'INFORME PARCIAL->Posicion inicial: \(([0-9]+)\)')
avg_pattern = re.compile(r'Distancia al punto de destino: media ([0-9]+\.[0-9]+),')
avg_destipica = re.compile(r'Desviacion tipica: ([0-9]+\.[0-9]+)')

# Input parameters
try:
    simulation_time = int(sys.argv[1])
    x = int(sys.argv[2])
    vision = int(sys.argv[3])
    ocupacion = float(sys.argv[4])
except IndexError:
    print("Numero de argumentos invalido")
    exit()

# Ejecuta el comando y guarda el resultado en una variable.
cmd = f"{EXECUTABLE_PATH} {simulation_time} {x} {vision} {ocupacion}"
result = os.popen(cmd).read()

# Busca todos los valores y los mapea a floats o enteros ya que son strings
# y para dibujarlos tienen que ser numeros.
c_values = list(map(int, re.findall(c_pattern, result)))
avg_distances = list(map(float, re.findall(avg_pattern, result)))
avg_desviaciones = list(map(float, re.findall(avg_destipica, result)))

# Ejecuta el comando y guarda el resultado en una variable.
cmd = f"{EXECUTABLE_PATH} {simulation_time} {x} {vision} 0.9"
result = os.popen(cmd).read()

# Busca todos los valores y los mapea a floats o enteros ya que son strings
# y para dibujarlos tienen que ser numeros.
c_values1 = list(map(int, re.findall(c_pattern, result)))
avg_distances1 = list(map(float, re.findall(avg_pattern, result)))
avg_desviaciones1 = list(map(float, re.findall(avg_destipica, result)))

# Ejecuta el comando y guarda el resultado en una variable.
cmd = f"{EXECUTABLE_PATH} {simulation_time} {x} {vision} 0.95"
result = os.popen(cmd).read()

# Busca todos los valores y los mapea a floats o enteros ya que son strings
# y para dibujarlos tienen que ser numeros.
c_values2 = list(map(int, re.findall(c_pattern, result)))
avg_distances2 = list(map(float, re.findall(avg_pattern, result)))
avg_desviaciones2 = list(map(float, re.findall(avg_destipica, result)))



# Buscar valor optimo de la distancia media y su valor de c.
best_distance = min(avg_distances)
best_c = c_values[avg_distances.index(best_distance)]

print(f"Mejor posicion inicial: {best_c}")
print(f"Mejor distancia: {best_distance}")

best_desviation = min(avg_desviaciones)
best_c = c_values[avg_desviaciones.index(best_desviation)]

print(f"Mejor posicion inicial: {best_c}")
print(f"Mejor desviación típica: {best_desviation}")



# Dibuja los datos
plt.plot(c_values, avg_distances, label="75%")
# plt.plot(c_values1, avg_distances1, label="90%")
# plt.plot(c_values2, avg_distances2, label="95%")
plt.xlabel('Posición inicial (c)')
plt.ylabel('Distancia media al destino (x)')
# plt.legend(title='Ocupación', loc='upper right')
plt.tight_layout()

# Guarda la gráfica con el nombre del ejecutable y los parametros dados.
plt.savefig(f"doc/img/x-100-10-90.png")
plt.show()



# Dibuja los datos
plt.plot(c_values, avg_desviaciones, label="75%")
# plt.plot(c_values1, avg_desviaciones1, label="90%")
# plt.plot(c_values2, avg_desviaciones2, label="95%")
plt.xlabel('Posición inicial (c)')
plt.ylabel('Desviación típica')
# plt.legend(title='Ocupación', loc='upper right')
plt.tight_layout()

# Guarda la gráfica con el nombre del ejecutable y los parametros dados.
plt.savefig(f"doc/img/dt-100-10-90.png")
plt.show()
