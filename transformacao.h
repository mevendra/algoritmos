#ifndef TRANSFORMACAO_H
#define TRANSFORMACAO_H

#include "estrutura.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <stack>
using namespace std;

const int MAX_COLUNA_ARQUIVO = 40;


int** cria_matriz(int tamanho);
Grafo* trabalha_arquivo(char* caminho);
void escreve_grafo_graphviz(Grafo* g, bool colorir, char* caminho);
void escreve_arvore_graphviz(Grafo* g, int* arvore, char* caminho);
void escreve_arvore_graphviz(Grafo* g, Nodo_dominadores* raiz, bool colorir, char* caminho);
void escreve_componentes_graphviz(Grafo* g, list<list<int>> componentes, char* caminho);
void escreve_componentes_sem_elementos_graphviz(Grafo* g, list<list<int>> componentes, char* caminho);
void escreve_cores_graphviz(Grafo* g, FILE* arquivo);
void escreve_cores(Grafo* g, char* caminho);
void escreve_max_cores(Grafo* g, char* caminho);
void escreve_aneis(list<Anel*> aneis, Grafo* g, char* caminho);
void escreve_aneis_ordem(list<Anel*> aneis, Grafo* g, char* caminho);
void escreve_aneis_completo(list<Anel*> aneis, char* caminho);

void escreve_grafo_com_componentes_especiais(Grafo* g, list<list<int>> componentes, char* caminho);
void instancia_vertices_graphviz(Grafo* g, FILE* arquivo, list<int>& nao_desenhar);
void reinicia_cores();
void coloca_transicoes(int** grafo, list<Atributos_vertice*> atributos);


enum Estados
{
	INICIO,
	VERTICE,
	VERTICE_FIM,
	ARESTA,
	ARCO
};

#endif /* TRANSFORMACAO_H */
