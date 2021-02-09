#Abre Arquivos e escreve o caminho deles

def escreve_caminho(fonte, destino):
    arq_d = open(destino, "w")
    arq_d.close()
    arq_d = open(destino, "a")
    arq_f = open(fonte, "r")

    lista = []

    for x in arq_f:
        x1 = x.split(", ")
        x2 = x1[9].split(" ")
        try:
            x2.remove("")
            lista.append(x2)
        except:
            print("Elemento nao removido")

    for x in lista:
        str = ""
        i = 1
        for y in x:
            str += y
            if i < len(x):
                str += " "
                i += 1
        str += "\n"
        arq_d.write(str)

#escreve_caminho("Fonte\\a2c2.txt", "Fonte\\a2c2_s.txt")
escreve_caminho("Fonte\\aneis_2.txt", "Fonte\\aneis_2_s.txt")
escreve_caminho("Fonte\\aneis_2_c1.txt", "Fonte\\aneis_2_c1_s.txt")
