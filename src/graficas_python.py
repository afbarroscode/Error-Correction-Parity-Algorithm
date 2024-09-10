import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

def limite_shannon(qber_values):
    return [(-1) * qber * np.log2(qber) + (-1) * (1 - qber) * np.log2(1 - qber) if qber != 0 and qber != 1 else 0 for qber in qber_values]

# Leer los datos del archivo CSV
QBER = [round(x, 3) for x in np.arange(0.01, 0.101, 0.001)]
QBER_h = [round(x, 3) for x in np.arange(0, 1.001, 0.001)]
h = limite_shannon(QBER)
h_grafica = limite_shannon(QBER_h)
SKR_bb84 = [1 - 2 * valor for valor in h]
bitsexpuestos = pd.read_csv('/home/alberto/Documentos/bbbss/figures/bitsexpuestos.csv')
bits_ideales = [1000000*valor for valor in h]
eficiencia = pd.read_csv('/home/alberto/Documentos/bbbss/figures/eficiencia.csv')
tasa = pd.read_csv('/home/alberto/Documentos/bbbss/figures/tasa.csv')

# Graficar entropia de Shannon
plt.figure()
plt.plot(QBER_h, h_grafica, color='red')
plt.grid(True)
plt.title('Entropia binaria de Shannon')
plt.xlabel('$\epsilon$')
plt.ylabel('$h(\epsilon)$')
plt.show()

# Graficar Btts expuestos
plt.figure()
plt.plot(bitsexpuestos['x'], bitsexpuestos['y'], color='red', linestyle='--', marker='o', label = 'Protocolo BBBSS')
plt.plot(QBER, bits_ideales, color='blue', label = 'Caso ideal (BB84)')
plt.grid(True)
plt.title('Bits expuestos en canal público')
plt.xlabel('$\epsilon$')
plt.ylabel('Número de bits expuestos')
plt.legend()
plt.show()

# Graficar efiencia
plt.figure()
plt.plot(eficiencia['x'], eficiencia['y'], color='red', linestyle='--',marker='o')
plt.grid(True)
plt.title('Eficiencia de reconciliacion')
plt.xlabel('$\epsilon$')
plt.ylabel('f')
plt.show()

# Graficar tasa
plt.figure()
plt.plot(tasa['x'], tasa['y'], marker='o', color='red', linestyle='--', label = 'Protocolo BBBSS')
plt.plot(QBER, SKR_bb84, color='blue', label = 'Caso ideal (BB84)')
plt.grid(True)
plt.title('Tasa de generación de claves')
plt.xlabel('$\epsilon$')
plt.ylabel('SKR(bps)')
plt.legend()
plt.show()