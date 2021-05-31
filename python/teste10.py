#Abre Arquivos na forma 
#NUMERO 
#numero sexo infos
#...

#Escreve na forma
#*Nome daRede
#*Vertices
#ID numero triangulo/elipse

def escreve(fonte, destino, nome_rede):
    a_destino = open(destino, "w")
    a_fonte = open(fonte, "r")

    s1 = []

    for x in a_fonte:
        x1 = x.split(" ")
        s1.append(x1)

    a_destino.write("*" + nome_rede + "\n")
    a_destino.write("*Vertices\n")
    i = 0
    for x in s1:
        if i == 0:
        	i = i + 1
        	continue
        linha = ""
        linha += str(i)
        linha += " "
        linha += x[0]
        linha += " "
        if x[1] == "m":
        	linha += "triangle"
        else:
	        linha += "ellipse"
        linha += "\n"
        a_destino.write(linha)
        i = i + 1
        
escreve("redes/ap/ap.txt", "ap.txt", "ap")         
escreve("redes/chacobo/chacobo.txt", "chacobo.txt", "Chacobo")        
escreve("redes/deni/deni.txt", "deni.txt", "deni")        
escreve("redes/im/im.txt", "im.txt", "im")        
escreve("redes/kraho/Kraho2016.txt", "kraho.txt", "Kraho")       
escreve("redes/xv/xv.txt", "xv.txt", "xv")        
escreve("redes/zo/zo.txt", "zo.txt", "zo")
