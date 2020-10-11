tamanho = 10

executar: *.h *.cpp
	g++ *.h *.cpp
	./a.out $(tamanho)
	make limpar

limpar:
	rm *.h.gch
	rm a.out

compilar:
	g++ -o programa *.h *.cpp