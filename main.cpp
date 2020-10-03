#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[]) {
	std::list<int> destino;
	int tamanho;
	srand(time(NULL));

	if (argc == 1) {
		tamanho = 10;
	}else if (argc<1){
		return 0;
	}else{
		tamanho = atoi(argv[1]);
	}

	int ** a= new int*[tamanho];
	for (int i = 0; i < tamanho; i++)
		a[i] = new int[tamanho];
	int h;
	for (int i = 0; i < tamanho; i++) {
		for(int y = 0; y < tamanho; y++) {
			if (i == y) {
				a[i][y] = 0;
			}else{
				h = rand() % 10;
				switch(tamanho>6) {
					case(true):
						if (h < 1) {
							a[y][i] = 1;
							a[i][y] = 1;
						} else {
							a[y][i] = 0;
							a[i][y] = 0;	
						}
					break;
					case(false):
						if (h < 3) {
							a[y][i] = 1;
							a[i][y] = 1;
						} else {
							a[y][i] = 0;
							a[i][y] = 0;	
						}
					break;
				}
				
			}
		}
	}

	int busca = rand() % tamanho;
	printf("Matriz:\n");
	for(int i = 0; i < tamanho; i++) {
		for(int y = 0; y < tamanho; y++) {
			printf("%d ", a[i][y]);
		}
		printf("\n");
	}
	busca_em_profundidade(a,tamanho,destino,busca);
	printf("Busca_em_profundidade(%d):\n", busca);
	for(int i: destino)
		printf("%d ",i);

	destino.clear();

	busca_em_largura(a,tamanho,destino,busca);
	printf("\nBusca_em_largura(%d):\n", busca);
	for(int i: destino)
		printf("%d ",i);
	printf("\n");
	

	//teste componentes conexas
	std::list<std::list<int>> destino_;

	busca_componentes_conexas(a, tamanho,destino_);
	for(std::list<int> m: destino_)
	{
		printf("Proximo componente:\n");
		for(int i: m)
		{
			printf("%d ", i);
				
		}
		printf("\n");
	}
	return 0;
}
