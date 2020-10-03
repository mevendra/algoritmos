tamanho = 10

executar: algoritmo.h algoritmo.cpp main.cpp
	g++ -o programa algoritmo.h algoritmo.cpp main.cpp
	./programa $(tamanho)
