# libraries
import numpy as np
import matplotlib.pyplot as plt


def chart(fonte):
	arq_f = open(fonte, "r")
	nome = []
	numero_aneis = []
	A1LSC = []
	A1LCC = []
	A1P = []
	A2L = []
	A2P = []
	A3 = []

	for x in arq_f:
		x1 = x.replace("\n", "")
		x1 = x1.replace("s,", ",")
		x1 = x1.replace(" ", "")
		x1 = x1.replace(".txt", "")
		x2 = x1.split(",")

		if len(x2) > 8:
			if x2[0] != "Nome":
				nome.append(x2[0])
				numero_aneis.append(x2[1])
				A1LSC.append(x2[2])
				A1LCC.append(x2[3])
				A1P.append(x2[4])
				A2L.append(x2[5])
				A2P.append(x2[6])
				A3.append(x2[7])


	for x in range(len(nome)):
		bars = ("A1LSC", "A1LCC", "A1P", "A2L", "A2P", "A3")
		height = [float(A1LSC[x]), float(A1LCC[x]), float(A1P[x]), float(A2L[x]), float(A2P[x]), float(A3[x])]

		x_pos = np.arange(len(bars))
		plt.title(nome[x] + "_" + numero_aneis[x])
		plt.bar(x_pos, height)
		plt.xticks(x_pos, bars)
		plt.show()



#chart("Resultados/medias_brasilplural.txt")
chart("Resultados/medias_lapesd.txt")