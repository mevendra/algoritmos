def media(fonte1, destino, nome_rede, numero_aneis):
    tamanho = 12
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

    indice = 0
    for x in arq_f1:
      x1 = x.replace("\n", "")
      x1 = x.replace("s,", ",")
      x2 = x1.split(", ")
      if len(x2) > 4:
       nome.append(x2[0])
       anel.append(x2[1])
       algoritmo_1_linear_s_cores.append(x2[2])
       algoritmo_1_linear.append(x2[3])
       algoritmo_1_paralelo.append(x2[4])
       algoritmo_2_linear.append(x2[5])
       algoritmo_2_paralelo.append(x2[6])
       algoritmo_3.append(x2[7])

    a1lsc = 0
    a1lcc = 0
    a1p = 0
    a2l = 0
    a2p = 0
    a3 = 0

    contagem = 0
    melhor = ""
    for i in range(len(nome)):
      x = nome[i]
      y = anel[i]
      if x == nome_rede and y == numero_aneis:
        contagem = contagem + 1
        a1lsc = a1lsc + float(algoritmo_1_linear_s_cores[i])
        a1lcc = a1lcc + float(algoritmo_1_linear[i])
        a1p = a1p + float(algoritmo_1_paralelo[i])
        a2l = a2l + float(algoritmo_2_linear[i])
        a2p = a2p + float(algoritmo_2_paralelo[i])
        a3 = a3 + float(algoritmo_3[i])

    if contagem == 0:
    	contagem = 1
    	
    a1lsc = round(a1lsc / contagem, 3)
    a1lcc = round(a1lcc / contagem, 3)
    a1p = round(a1p / contagem, 3)
    a2l = round(a2l / contagem, 3)
    a2p = round(a2p / contagem, 3)
    a3 = round(a3 / contagem, 3)
    
    x = min(a1lsc, a1lcc, a1p, a2l, a2p, a3)
    if x == a1lsc:
     	melhor = "A1L_Sem_Cores"
    elif x == a1lcc:
      	melhor = "A1L_Com_Cores"
    elif x == a1p:
      	melhor = "A1P"
    elif x == a2l:
     	melhor = "A2L"
    elif x == a2p:
     	melhor = "A2P"
    elif x == a3:
     	melhor = "A3"
    else:
     	melhor = "Erro"
     	
    linha = nome_rede
    linha += ", "
    linha += numero_aneis
    linha += ", "
    linha += str(a1lsc)
    linha += ", "
    linha += str(a1lcc)
    linha += ", "
    linha += str(a1p)
    linha += ", "
    linha += str(a2l)
    linha += ", "
    linha += str(a2p)
    linha += ", "
    linha += str(a3)
    linha += ", "
    linha += melhor
    linha += "\n"

    arq_d.write(linha)


    print (linha)



    
fonte = "Resultados/resultados_testes.txt"
destino = "Resultados/medias.txt"
arq = open(destino, "w")
a = "Nome, Numero_Casamentos, Algoritmo_1_Linear_Sem_Cores, Algoritmo_1_Linear_Com_Cores, Algoritmo_1_Paralelo, Algoritmo_2_Linear, Algoritmo_2_Paralelo, Algoritmo_3, Melhor\n\n"
arq.write(a)
arq.close()

media(fonte, destino, "ap.txt", "1")
media(fonte, destino, "Arara4MaqPar.txt", "1")
media(fonte, destino, "chacobo_fem.txt", "1")
media(fonte, destino, "chacobo_mas.txt", "1")
media(fonte, destino, "deni.txt", "1")
media(fonte, destino, "EN4MaqPar.txt", "1")
media(fonte, destino, "im.txt", "1")
media(fonte, destino, "kraho.txt", "1")
media(fonte, destino, "marcapata.txt", "1")
media(fonte, destino, "mbya.txt", "1")
media(fonte, destino, "xv.txt", "1")
media(fonte, destino, "zo.txt", "1")

arq = open(destino, "a")
arq.write("\n\n")
arq.close()

media(fonte, destino, "ap.txt", "2")
media(fonte, destino, "Arara4MaqPar.txt", "2")
media(fonte, destino, "chacobo_fem.txt", "2")
media(fonte, destino, "chacobo_mas.txt", "2")
media(fonte, destino, "deni.txt", "2")
media(fonte, destino, "EN4MaqPar.txt", "2")
media(fonte, destino, "im.txt", "2")
media(fonte, destino, "kraho.txt", "2")
media(fonte, destino, "marcapata.txt", "2")
media(fonte, destino, "mbya.txt", "2")
media(fonte, destino, "xv.txt", "2")
media(fonte, destino, "zo.txt", "2")






