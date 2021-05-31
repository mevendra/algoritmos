#Abre Arquivos na forma 
#NUMERO 
#numero numero relacao
#...

#e

#*Nome daRede
#*Vertices
#ID numero triangulo/elipse

#Adiciona no final do arquivo na forma
#*Edges
#id id
#...
#*Arcs
#id id
#...

def escreve(fonte, destino):
    a_destino = open(destino, "r")
    a_fonte = open(fonte, "r")

    arcos = []
    arestas = []

    for x in a_fonte:
        x2 = x.replace("\n", "")
        x1 = x2.split(" ")
        if len(x1) < 3:
        	continue
        if x1[2] == "co":
        	arcos.append(x1)
        elif x1[2] == "ca":
        	arestas.append(x1)
        else:
        	print(x)
        
    hm = {}	
    for x in a_destino:
    	x1 = x.split(" ")
    	if len(x1) > 1:
    		hm[x1[1]] = x1[0]	
    		
    
    a_destino.close()
    a_destino = open(destino, "a")

    a_destino.write("*Edges\n")
    for x in arestas:
    	valor1 = x[0]
    	valor2 = x[1]
    	linha = ""
    	linha += str(hm[valor1])
    	linha += " "
    	linha += str(hm[valor2])
    	linha += "\n"
    	a_destino.write(linha)
    	
    a_destino.write("*Arcs\n")
    for x in arcos:
    	valor1 = x[0]
    	valor2 = x[1]
    	linha = ""
    	linha += str(hm[valor1])
    	linha += " "
    	linha += str(hm[valor2])
    	linha += "\n"
    	a_destino.write(linha)
        
escreve("redes/ap/ap-arcs-edges.txt", "ap.txt")         
escreve("redes/chacobo/chacobo-arcs-edges-ponto-de-vista-feminino.txt", "chacobo_fem.txt")       
escreve("redes/chacobo/chacobo-arcs-edges-ponto-de-vista-masculino.txt", "chacobo_mas.txt")       
escreve("redes/deni/deni-arcs-edges.txt", "deni.txt")        
escreve("redes/im/im-arcs-edges.txt", "im.txt")        
escreve("redes/kraho/Kraho2016-arcs-edges.txt", "kraho.txt")       
escreve("redes/xv/xv-arcs-edges.txt", "xv.txt")        
escreve("redes/zo/zo-arcs-edges.txt", "zo.txt")
