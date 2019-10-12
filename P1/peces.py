import os
import re
from matplotlib import pyplot as plt

plt.tight_layout()

# Ruta de tu ejecutable con respecto al script.
EXECUTABLE_PATH = './pesesitos'

output_name = os.path.basename(EXECUTABLE_PATH)

def plot(x, y, x_label, y_label, capturados=None):
    plt.plot(x, y)
    if capturados:
        plt.title(f"Peces grandes capturados: {capturados}")
    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.savefig(f"./plots/{output_name}/{output_name}_{y_label}.png")
    plt.clf()

# Expresion regulares de los valores a buscar.
pattern = re.compile(r'\t([0-9]+)\t(.*?)\t(.*?)\n')
#capturados = re.compile(r'Peces capturados durante la simulacion: (.*?)$')

# Ejecuta el comando y guarda el resultado en una variable.
result = os.popen(EXECUTABLE_PATH).read()

# Busca todos los valores y los mapea a floats ya que son strings
# y para dibujarlos tienen que ser numeros.
days, smalls, bigs = zip(*[s for s in re.findall(pattern, result)])
days = list(map(int, days))
smalls = list(map(float, smalls))
bigs = list(map(float, bigs))
#peces_capturados = re.findall(capturados, result)[0]

plot(smalls, bigs, 'Pequeños', 'Grandes')
plot(days, smalls, 'Dia', 'Peces pequeños')
plot(days, bigs, 'Dia', 'Peces grandes')

