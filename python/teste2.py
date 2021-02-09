#Remove listas que tenham elementos repetidos
def rem_repetidos(fonte, destino):
    arq_d = open(destino, "w")
    arq_d.close()
    arq_d = open(destino, "a")
    arq_f = open(fonte, "r")

    lista_f = []
    lista_d = []

    for x in arq_f:
        x1 = x.replace("\n", "")
        x2 = x1.split(" ")
        lista_f.append(x2)

    print(len(lista_f))
    for x in lista_f:
        adicionar = True
        for y in range(len(x) - 1):
            for z in range(y + 1, len(x)):
                if x[y] == x[z]:
                    adicionar = False
        if adicionar:
            lista_d.append(x)

    for x in lista_d:
        str = ""
        i = 1
        for y in x:
            str += y
            if i < len(x):
                str += " "
                i += 1
        str += "\n"
        arq_d.write(str)

rem_repetidos("Fonte\\aneis_2_s.txt", "Resultados\\teste2_aneis_2_s")
rem_repetidos("Fonte\\a2c2_s.txt", "Resultados\\teste2_a2c2")

rem_repetidos("Resultados\\teste1", "Resultados\\teste2")