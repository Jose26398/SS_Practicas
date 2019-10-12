import os
import re
import sys
from prettytable import PrettyTable
from matplotlib import pyplot as plt

# Ruta de tu ejecutable con respecto al script.
EXECUTABLE_PATH = './radares'
MAX_REPUESTOS = 30
SIMULATIONS_TIME = [1000]

# Expresion regular para sacar el porcentaje de desprotección
percentage_pattern = re.compile(r'La media del porcentaje de tiempo de desproteccion es: (.*?)\n')
std_pattern = re.compile(r'La desviacion tipica del porcentaje de tiempo de desproteccion es: (.*?)\n')

# Input parameters
try:
    num_radares = int(sys.argv[1])
    vmin = float(sys.argv[2])
    vmax = float(sys.argv[3])
    tiempo_fallo = float(sys.argv[4])
    tiempo_fin = float(sys.argv[5])
except IndexError:
    print("Numero de argumentos invalido")
    exit()

table = PrettyTable()
table.field_names = ["Años", "Repuestos", "Porcentaje", "Desviacion"]
for field in table.field_names:
    table.align[field] = "r"


repuestos = [x for x in range(1, MAX_REPUESTOS + 1)]
percentages = []

for n_sim in SIMULATIONS_TIME:
    for r in repuestos:
        cmd = f"{EXECUTABLE_PATH} {num_radares} {r} {vmin} {vmax} {tiempo_fallo} {tiempo_fin} {n_sim}"
        result = os.popen(cmd).read()
        percentage = float(re.findall(percentage_pattern, result)[0])
        desv_tipica = float(re.findall(std_pattern, result)[0])
        percentages.append(percentage)
        if percentage < 1:
            table.add_row([n_sim, r, percentage, desv_tipica])

    # Dibuja los datos
    plt.plot(repuestos, percentages)
    plt.xlabel('Numero de repuestos')
    plt.ylabel('Porcentaje desproteccion')
    plt.tight_layout()

    # Guarda la gráfica con el nombre del ejecutable y los parametros dados.
    output_name = os.path.basename(EXECUTABLE_PATH)
    plt.savefig(f"./plots/{output_name}/{output_name}_{n_sim}_{vmax}_2.png")
    plt.clf()
    percentages.clear()

print(table)