
#Abre aneis e separa apenas os casamentos (a2c2)
#Abre Arquivos e escreve o caminho deles

def escreve_casamentos(fonte, destino):
    arq_d = open(destino, "w")
    arq_d.close()
    arq_d = open(destino, "a")
    arq_f = open(fonte, "r")

    lista = []
    i = 0
    for x in arq_f:
        i = i + 1
        if i == 1:
            continue
        if i >= 3:
            str = "\n"
        else:
            str = ""
        x1 = x.split(", ")
        str += x1[12]
        str += ", "
        str += x1[13]
        str += ", "
        str += x1[0]

        arq_d.write(str)

escreve_casamentos("Fonte\\aneis_2_rede_grande.txt", "Fonte\\aneis_2_rede_grande_c.txt")
