import os
import re
import sys
from matplotlib import pyplot as plt

# Ruta de tu ejecutable con respecto al script.
EXECUTABLE_PATH = './puerto'
EXECUTABLE_PATH2 = './puerto-mej'

# Expresiones regulares de los valores a buscar.
c_pattern = re.compile(r'Numero medio de barcos en cola de llegadas: media\(([0-9]+\.[0-9]+)\)')

# Input parameters
try:
    simulation_time = int(sys.argv[1])
except IndexError:
    print("Numero de argumentos invalido")
    exit()

c_values = []
c_values2 = []
nbca = 0
nbca2 = 0
num_sim = 25

for x in range(100):
	# Ejecuta el comando y guarda el resultado en una variable.
	cmd = f"{EXECUTABLE_PATH} {simulation_time}"
	result = os.popen(cmd).read()
	c_values.append(list(map(float, re.findall(c_pattern, result))))

	cmd = f"{EXECUTABLE_PATH2} {simulation_time}"
	result = os.popen(cmd).read()
	c_values2.append(list(map(float, re.findall(c_pattern, result))))


for i in range(1,num_sim):
	print(i)
	for x in range(100):
		# Ejecuta el comando y guarda el resultado en una variable.
		cmd = f"{EXECUTABLE_PATH} {simulation_time}"
		result = os.popen(cmd).read()
		c_values[x] += (list(map(float, re.findall(c_pattern, result))))

		cmd = f"{EXECUTABLE_PATH2} {simulation_time}"
		result = os.popen(cmd).read()
		c_values2[x] += (list(map(float, re.findall(c_pattern, result))))

# No hace falta hacer la media para saber si uno será más grande que otro
for j in range(len(c_values)):
	if (c_values[j] < c_values2[j]):
		nbca+=1
	else:
		nbca2+=1

print("NBCA_A: ", (nbca), "%\t\tNBCA_B: ", (nbca2), "%" )
