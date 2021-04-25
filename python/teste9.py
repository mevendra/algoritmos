#Verifica acertos 

#Abre aneis e separa apenas os casamentos (a2c2)
#Abre Arquivos e escreve o caminho deles

def escreve(fonte_aneis, fonte_casamentos, info):
    ad = "i_"
    info = ad + info

    arq_di = open(info, "w")
    arq_di.close()
    arq_di = open(info, "a")
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
        for y in casamentos:
            aux_1 = y[0]
            aux_2 = y[1]
            aux_dia = y[2]

            if (aux_1 == casamento_1_1 and aux_2 == casamento_1_2) or (aux_2 == casamento_1_1 and aux_1 == casamento_1_2):
                dia_1 = aux_dia
                continue

            if (aux_1 == casamento_2_1 and aux_2 == casamento_2_2) or (aux_2 == casamento_2_1 and aux_1 == casamento_2_2):
                dia_2 = aux_dia
                continue

        if dia_1 == -1 or dia_2 == -1:  # or dia_2 == "None" or dia_1 == "None":
            indice = indice + 1
            continue

        if dia_1 == "None" and dia_2 == "None": #Casamentos sem data
            #arq_di.write(aneis_txt[indice])
            indice = indice + 1
            continue

        if dia_1 == "None" or dia_2 == "None": #Casamentos com apenas uma data
            #arq_di.write(aneis_txt[indice])
            indice = indice + 1
            continue

        if dia_1 == "1916-08-03" or dia_2 == "1916-08-03":
            print ("Achou")


        aux_1 = dia_1.split("-")
        aux_2 = dia_2.split("-")        

        enc = False

        if aux_1[0] == aux_2[0]:
            enc = True
            #arq_di.write(aneis_txt[indice])
            
            if aux_1[1] == aux_2[1]:
                enc = True
                #arq_di.write(aneis_txt[indice])

                if (aux_2[2] == aux_1[2]):
                    enc = True
                    #arq_di.write(aneis_txt[indice])                
            
        
        #if not enc:
            #arq_di.write(aneis_txt[indice]) #Casamentos com datas iguais
        
        indice = indice + 1
        

#escreve("Fonte\\aneis_2_rede_grande.txt", "Fonte\\casamentos_rede_grande_c.txt", "Resultados\\teste7_acerto.txt", "Resultados\\teste7_erro.txt", "Resultados\\teste7_inc.txt")

escreve("rede_grande_soma.txt", "casamentos_rede_grande_c.txt", "igual_ano_mes_dia.txt")
#escreve("rede_grande_soma.txt", "casamentos_rede_grande_c.txt", "a_soma.txt", "e_soma.txt", "inc.txt")
#escreve("rede_grande_maior.txt", "casamentos_rede_grande_c.txt", "a_maior.txt", "e_maior.txt", "inc.txt")