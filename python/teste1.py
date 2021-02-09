#Escreve em s3 os elementos de s1 que não estão em s2
def verifica(fonte1, fonte2, destino):
    arq_d = open(destino, "w")
    arq_d.close()
    arq_d = open(destino, "a")
    arq_f1 = open(fonte1, "r")
    arq_f2 = open(fonte2, "r")

    s1 = []
    s2 = []
    s3 = []

    for x in arq_f1:
        x1 = x.replace("\n", "")
        x2 = x1.split(" ")
        s1.append(x2)

    for x in arq_f2:
        x1 = x.replace("\n", "")
        x2 = x1.split(" ")
        s2.append(x2)

    i = 1
    c = 1
    print("Calculando...")
    for x in s1:
        i += 1
        if i % 2063 == 0:
            str = "Ainda Calculando"
            str += "%s" % c
            str += " ..."
            print(str)
            c += 1

        if s2.__contains__(x):
            s2.remove(x)
            continue
        else:   #Verifica se tem o mesmo elemento com ordens diferentes
            encontrou = False
            for y in s2:
                if len(x) != len(y):
                    continue

                ver = True
                for u in x:
                    if y.__contains__(u):
                        continue
                    else:
                        ver = False
                        break

                if ver:
                    encontrou = True
                    break

            if not encontrou:
                s3.append(x)


    for x in s3:
        str = ""
        i = 1
        for y in x:
            str += y
            if i < len(x):
                str += " "
                i += 1
        str += "\n"
        arq_d.write(str)

verifica("Fonte\\aneis_2_s.txt", "Fonte\\a2c2_s.txt", "Resultados\\teste1")

verifica("Fonte\\aneis_2_c1_s.txt", "Fonte\\aneis_2_s.txt", "Resultados\\teste1_c1")



