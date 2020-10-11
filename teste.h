#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int MAX_COLUNA_ARQUIVO = 40;

void testar_busca_largura(int** grafo, int tamanho);
void testar_busca_profundidade(int** grafo, int tamanho);
void testar_busca_largura_listas(int** grafo, int tamanho);
void testar_busca_largura_listas(std::list<Vertice*>& grafo);
void testar_componentes_conexas(int** grafo, int tamanho);
void testar_colorir_grafo(Grafo* grafo);
int** cria_matriz(int tamanho);
Grafo* trabalha_arquivo(char* caminho);


enum Estados
{
	INICIO,
	VERTICE,
	VERTICE_FIM,
	ARESTA,
	ARCO
};
