#ifndef TRANSFORMACAO_H
#define TRANSFORMACAO_H

#include "estrutura.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
using namespace std;

const int MAX_COLUNA_ARQUIVO = 40;


int** cria_matriz(int tamanho);
Grafo* trabalha_arquivo(char* caminho);
void escreve_grafo_graphviz(Grafo* g, bool colorir, char* caminho);
void escreve_arvore_graphviz(Grafo* g, int* arvore, char* caminho);
void escreve_componentes_graphviz(Grafo* g, list<list<int>> componentes, char* caminho);

void instancia_vertices_graphviz(Grafo* g, FILE* arquivo);
void reinicia_cores();

enum Estados
{
	INICIO,
	VERTICE,
	VERTICE_FIM,
	ARESTA,
	ARCO
};

#endif /* TRANSFORMACAO_H */
