# libraries
import numpy as np
import matplotlib.pyplot as plt

titulo = "Número de aparição das cores"
bars = ("-1", "1002", "1004", "1195", "1204", "1201")
height = [90350, 107681, 107534, 534, 65, 0]

x_pos = np.arange(len(bars))
plt.title(titulo)
plt.bar(x_pos, height)
plt.xticks(x_pos, bars)
plt.show()





