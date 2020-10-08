tamanho = 10

executar: *.h *.cpp
	g++ -o programa *.h *.cpp
	./programa $(tamanho)

limpar:
	rm *.h.gch

compilar:
	g++ -o programa *.h *.cpp