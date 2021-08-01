def ler_resultados(fonte1, destino):
    tamanho = 300

    arq_d = open(destino, "w")
    arq_d.close()
    arq_d = open(destino, "a")
    arq_f1 = open(fonte1, "r")

    nome = []
    anel = []
    algoritmo_1_linear = []
    algoritmo_1_linear_s_cores = []
    algoritmo_1_paralelo = []
    algoritmo_2_linear = []
    algoritmo_2_paralelo = []
    algoritmo_3 = []
    melhor = []

    nome = nome + [0] * (tamanho - len(nome))
    anel = anel + [0] * (tamanho - len(anel))
    algoritmo_1_linear = algoritmo_1_linear + ["0"] * (tamanho - len(algoritmo_1_linear))
    algoritmo_1_linear_s_cores = algoritmo_1_linear_s_cores + ["0"] * (tamanho - len(algoritmo_1_linear_s_cores))
    algoritmo_1_paralelo = algoritmo_1_paralelo + ["0"] * (tamanho - len(algoritmo_1_paralelo))
    algoritmo_2_linear = algoritmo_2_linear + ["0"] * (tamanho - len(algoritmo_2_linear))
    algoritmo_2_paralelo = algoritmo_2_paralelo + ["0"] * (tamanho - len(algoritmo_2_paralelo))
    algoritmo_3 = algoritmo_3 + ["0"] * (tamanho - len(algoritmo_3))
    melhor = melhor + [0] * (tamanho - len(melhor))

    a = "Nome, Numero_Casamentos, Algoritmo_1_Linear_Sem_Cores, Algoritmo_1_Linear_Com_Cores, Algoritmo_1_Paralelo, Algoritmo_2_Linear, Algoritmo_2_Paralelo, Algoritmo_3, Melhor\n\n"
    arq_d.write(a)

    indice = 0
    for x in arq_f1:
        x1 = x.replace("\n", "")
        x2 = x1.split(" ")
        primeiro = x2[0]

       	if primeiro == "./a.out":
       		nome_ = x2[1]
       		anel_ = x2[2]
       		nome[indice] = nome_
       		anel[indice] = anel_

       	elif primeiro == "Algoritmo":
       		segundo = x2[1]
       		if segundo == "1":
       			terceiro = x2[2]
       			if terceiro == "Paralelo,":
       				tempo = x2[4]
       				algoritmo_1_paralelo[indice] = tempo
       			else:
       				quarto = x2[3]
       				tempo = x2[6]
       				if quarto == "Com":
       					algoritmo_1_linear [indice] = tempo
       				else:
       					algoritmo_1_linear_s_cores[indice] = tempo
       		elif segundo == "2":
       			terceiro = x2[2]
       			tempo = x2[4]
       			if terceiro == "Linear,":
       				algoritmo_2_linear[indice] = tempo
       			else:
       				algoritmo_2_paralelo[indice] = tempo
       		else:
       			tempo = x2[4]
       			algoritmo_3[indice] = tempo
       	elif primeiro == "Terminou!":
       		x = min((algoritmo_1_linear_s_cores[indice]), (algoritmo_1_linear[indice]), (algoritmo_1_paralelo[indice]), (algoritmo_2_linear[indice]), (algoritmo_2_paralelo[indice]), (algoritmo_3[indice]))
       		if x == (algoritmo_1_linear_s_cores[indice]):
       			melhor[indice] = "A1L_Sem_Cores"
       		elif x == (algoritmo_1_linear[indice]):
       			melhor[indice] = "A1L_Com_Cores"
       		elif x == (algoritmo_1_paralelo[indice]):
       			melhor[indice] = "A1P"
       		elif x == (algoritmo_2_linear[indice]):
       			melhor[indice] = "A2L"
       		elif x == (algoritmo_2_paralelo[indice]):
       			melhor[indice] = "A2P"
       		elif x == (algoritmo_3[indice]):
       			melhor[indice] = "A3"

       		indice = indice + 1
       	elif primeiro == "makefile:43:":
       		nome[indice] = "Erro"
       		anel[indice] = "Erro"
       		algoritmo_1_linear[indice] = "Erro"
       		algoritmo_1_linear_s_cores[indice] = "Erro"
       		algoritmo_1_paralelo[indice] = "Erro"
       		algoritmo_2_linear[indice] = "Erro"
       		algoritmo_2_paralelo[indice] = "Erro"
       		algoritmo_3[indice] = "Erro"
       		melhor[indice] = "Erro"
       		indice = indice + 1
    
    for i in range(indice):
    	linha = ""
    	linha += str(nome[i])
    	linha += ", "
    	linha += str(anel[i])
    	linha += ", "
    	linha += str(algoritmo_1_linear_s_cores[i])
    	linha += ", "
    	linha += str(algoritmo_1_linear[i])
    	linha += ", "
    	linha += str(algoritmo_1_paralelo[i])
    	linha += ", "
    	linha += str(algoritmo_2_linear[i])
    	linha += ", "
    	linha += str(algoritmo_2_paralelo[i])
    	linha += ", "
    	linha += str(algoritmo_3[i])
    	linha += ", "
    	linha += str(melhor[i])
    	linha += "\n"

    	if nome[i] == "zo.txt" and anel[i] == "2":
    		linha += "\n\n\n"

    	arq_d.write(linha)


    
ler_resultados("Fonte/nohup_brasilplural_e.out", "Resultados/resultados_testes_brasilplural_e.txt")
#ler_resultados("Fonte/nohup_brasilplural.out", "Resultados/resultados_testes_brasilplural.txt")
#ler_resultados("Fonte/nohup_lapesd.out", "Resultados/resultados_testes_lapesd.txt")





