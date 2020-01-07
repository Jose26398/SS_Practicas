import os
import re
import sys
from matplotlib import pyplot as plt

# Ruta de tu ejecutable con respecto al script.
EXECUTABLE_PATH = 'depredadores.exe'

# Expresiones regulares de los valores a buscar.
depredadores_pattern = re.compile(r'Depredadores: ([0-9]+\.[0-9]+)')
presas_pattern = re.compile(r'Presas: ([0-9]+\.[0-9]+)')
tiempo_pattern = re.compile(r'Tiempo: ([0-9]+\.[0-9]+)')

# Input parameters
try:
    a11 = float(sys.argv[1])
    a12 = float(sys.argv[2])
    a21 = float(sys.argv[3])
    a22 = float(sys.argv[4])
    x 	= float(sys.argv[5])
    y 	= float(sys.argv[6])
except IndexError:
    print("Numero de argumentos invalido")
    exit()

# Ejecuta el comando y guarda el resultado en una variable.
cmd = f"{EXECUTABLE_PATH} {a11} {a12} {a21} {a22} {x} {y}"
result = os.popen(cmd).read()

# Busca todos los valores y los mapea a floats o enteros ya que son strings
# y para dibujarlos tienen que ser numeros.
depredadores = list(map(float, re.findall(depredadores_pattern, result)))
presas = list(map(float, re.findall(presas_pattern, result)))
tiempo = list(map(float, re.findall(tiempo_pattern, result)))

# Dibuja los datos
plt.plot(tiempo, depredadores, label="Depredadores")
plt.plot(tiempo, presas, label="Presas")

plt.xlabel('Tiempo')
plt.ylabel('Poblacion')

plt.tight_layout()

# Guarda la gráfica con el nombre del ejecutable y los parametros dados.
plt.legend(title='Poblacion', loc='upper right')
plt.savefig(f"doc/img/4-a12-{int(x)}-{int(y)}.png")
plt.show()


# # Dibuja los datos plano x-y
# plt.plot(presas, depredadores)

# plt.xlabel('Presas')
# plt.ylabel('Depredadores')

# plt.tight_layout()

# # Guarda la gráfica con el nombre del ejecutable y los parametros dados.
# plt.savefig(f"doc/img/4-a12-{int(x)}-{int(y)}.png")
# plt.show()