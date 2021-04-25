#Verifica acertos se for utilizado ordem que os casamentos ocorrem

#Abre aneis e separa apenas os casamentos (a2c2)
#Abre Arquivos e escreve o caminho deles

def escreve(fonte_aneis, fonte_casamentos, destino_acerto, destino_erro):
    ad = "5"
    destino_erro = ad + destino_erro
    destino_acerto = ad + destino_acerto
    
    arq_da = open(destino_acerto, "w")
    arq_de = open(destino_erro, "w")
    arq_da.close()
    arq_de.close()
    arq_da = open(destino_acerto, "a")
    arq_de = open(destino_erro, "a")
    arq_aneis = open(fonte_aneis, "r")
    arq_casamentos = open(fonte_casamentos, "r")    
    
    aneis = []
    aneis_txt = []
    casamentos = []

    for x in arq_aneis:
        x1 = x.replace("\n", "")
        x2 = x1.split(", ")
        aneis.append(x2)
        aneis_txt.append(x)

    for x in arq_casamentos:
        x1 = x.replace("\n", "")
        x2 = x1.replace(",", "")
        x3 = x2.split(" ")
        casamentos.append(x3)

    indice = 0
    for x in aneis:
        if indice == 0:
            indice = indice + 1
            continue

        casamento_1_1 = x[12].split(" ")[0]
        casamento_1_2 = x[12].split(" ")[1]
        casamento_2_1 = x[13].split(" ")[0]
        casamento_2_2 = x[13].split(" ")[1]

        dia_1 = -1
        dia_2 = -1       
        
        primeiro = False
        segundo = False
        for y in casamentos:
            aux_1 = y[0]
            aux_2 = y[1]
            aux_dia = y[2]

            if (aux_1 == casamento_1_1 and aux_2 == casamento_1_2) or (aux_2 == casamento_1_1 and aux_1 == casamento_1_2):
                dia_1 = aux_dia
                if segundo:
                    break
                else:
                    primeiro = True

            if (aux_1 == casamento_2_1 and aux_2 == casamento_2_2) or (aux_2 == casamento_2_1 and aux_1 == casamento_2_2):
                dia_2 = aux_dia
                if primeiro:
                    break
                else:
                    segundo = True

        
        if segundo:
            aux = dia_1
            dia_1 = dia_2
            dia_2 = aux

        if dia_1 == -1 or dia_2 == -1 :#or dia_2 == "None" or dia_1 == "None":
            indice = indice + 1
            continue
            
        if dia_1 == "None" and dia_2 == "None":
            indice = indice + 1
            continue
        if dia_1 == "None":
            arq_de.write(aneis_txt[indice])
            indice = indice + 1
            continue
        elif dia_2 == "None":
            arq_da.write(aneis_txt[indice])
            indice = indice + 1
            continue

        aux_1 = dia_1.split("-")
        aux_2 = dia_2.split("-")

        enc = True
        for i in range(len(aux_1)):
            if aux_1[i] > aux_2[i]:
                arq_da.write(aneis_txt[indice])
                enc = False
                break
            elif aux_1[i] < aux_2[i]:
                arq_de.write(aneis_txt[indice])
                enc = False
                break
           
        #Datas iguais é acerto     
        if enc:
        	arq_da.write(aneis_txt[indice])
        
        indice = indice + 1
        

#escreve("Fonte\\aneis_2_rede_grande.txt", "Fonte\\casamentos_rede_grande_c.txt", "Resultados\\teste8_acerto.txt", "Resultados\\teste8_erro.txt")


escreve("rede_grande_soma.txt", "casamentos_rede_grande_c.txt", "a_acaso.txt", "e_acaso.txt")
