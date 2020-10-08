#include "teste.h"
void testa_busca_largura(int** grafo, int tamanho) 
{
	printf("\nTestando busca em largura: \n");
	int* arvore = new int[tamanho];
	int num_raiz = 0;
	busca_em_largura(grafo, tamanho, arvore);

	printf("Arvore: \n");
	for (int i = 0; i < tamanho; i++)
	{	
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", arvore[i]);
	}
	printf("\nNumero de raizes: %d\n", num_raiz);
}
void testa_busca_profundidade(int** grafo, int tamanho)
{
	printf("\nTestando busca em profundidade: \n");
	int* arvore = new int[tamanho];
	int num_raiz = 0;
	busca_em_profundidade(grafo, tamanho, arvore);

	printf("Arvore: \n");
	for (int i = 0; i < tamanho; i++)
	{	
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", arvore[i]);
	}
	printf("\nNumero de raizes: %d\n", num_raiz);
}
void testa_busca_largura_listas(int** grafo, int tamanho) {}
void testa_busca_largura_listas(std::list<Vertice*>& grafo) {}
void testa_componentes_conexas(int** grafo, int tamanho) 
{
	printf("\nTestando busca de componentes conexas\n");
	list<list<int>> destino;

	busca_componentes_conexas(grafo, tamanho, destino);
	for(list<int> m: destino)
	{
		printf("Proximo componente:\n");
		for(int i: m)
		{
			printf("%d ", i);
				
		}
		printf("\n");
	}
}

int** cria_matriz(int tamanho)
{
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
	return a;
}

int main(int argc, char* argv[]) {
	int tamanho;
	srand(time(NULL));

	if (argc == 1) {
		tamanho = 10;
	}else if (argc<1){
		return 0;
	}else{
		tamanho = atoi(argv[1]);
	}


	int** grafo = cria_matriz(tamanho);
	testa_busca_largura(grafo, tamanho);
	testa_busca_profundidade(grafo, tamanho);
	testa_componentes_conexas(grafo, tamanho);

	return 0;

}