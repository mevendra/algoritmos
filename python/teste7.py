#Verifica acertos 

#Abre aneis e separa apenas os casamentos (a2c2)
#Abre Arquivos e escreve o caminho deles

def escreve(fonte_aneis, fonte_casamentos, destino_acerto, destino_erro, destino_inc):
    destino_acerto = destino_acerto
    destino_erro = destino_erro

    arq_da = open(destino_acerto, "w")
    arq_de = open(destino_erro, "w")
    arq_di = open(destino_inc, "w")
    arq_da.close()
    arq_de.close()
    arq_di.close()
    arq_da = open(destino_acerto, "a")
    arq_de = open(destino_erro, "a")
    arq_di = open(destino_inc, "a")
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

        if dia_1 == -1 or dia_2 == -1 or dia_2 == "None" or dia_1 == "None":
            arq_di.write(aneis_txt[indice])
            indice = indice + 1
            continue

        aux_1 = dia_1.split("-")
        aux_2 = dia_2.split("-")        

        enc = False
        for i in range(len(aux_1)):
            if aux_1[i] > aux_2[i]:
                enc = True
                arq_da.write(aneis_txt[indice])
                break
            elif aux_1[i] < aux_2[i]:
                enc = True
                arq_de.write(aneis_txt[indice])
                break
        
        if not enc:
            arq_di.write(aneis_txt[indice])
        
        indice = indice + 1
        

#escreve("Fonte\\aneis_2_rede_grande.txt", "Fonte\\casamentos_rede_grande_c.txt", "Resultados\\teste7_acerto.txt", "Resultados\\teste7_erro.txt", "Resultados\\teste7_inc.txt")

#escreve("teste_acertos.txt", "casamentos_rede_grande_c.txt", "a_soma.txt", "e_soma.txt", "inc.txt")
#escreve("rede_grande_soma.txt", "casamentos_rede_grande_c.txt", "a_soma.txt", "e_soma.txt", "inc.txt")
#escreve("rede_grande_maior.txt", "casamentos_rede_grande_c.txt", "a_maior.txt", "e_maior.txt", "inc.txt")


#escreve("Fonte/a2c2_marcapata_p_grafo.txt", "Fonte/casamentos_rede_grande_c.txt", "a_pgrafo.txt", "e_pgrafo.txt", "inc_pgrafo.txt")
#escreve("Fonte/a2c2_marcapata_p_grafo_cortados.txt", "Fonte/casamentos_rede_grande_c.txt", "a_pgrafo_cortados.txt", "e_pgrafo_cortados.txt", "inc_pgrafo_cortados.txt")
#escreve("Fonte/a2c2_marcapata_soma.txt", "Fonte/casamentos_rede_grande_c.txt", "a_soma.txt", "e_soma.txt", "inc_soma.txt")
#escreve("Fonte/a2c2_marcapata_soma_cortados.txt", "Fonte/casamentos_rede_grande_c.txt", "a_soma_cortados.txt", "e_soma_cortados.txt", "inc_soma_cortados.txt")

#escreve("Fonte/a2c2_marcapata.txt", "Fonte/casamentos_rede_grande_c.txt", "a.txt", "e.txt", "inc.txt")
escreve("Fonte/teste_geracional.txt", "Fonte/casamentos_rede_grande_c.txt", "a_geral.txt", "e_geral.txt", "inc_geral.txt")


