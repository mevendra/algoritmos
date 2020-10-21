#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "list"
#include <array>
#include <queue>
#include <stdlib.h>
#include "estrutura.h"
using namespace std;

static int tempo;

//Metodos utilizados por outros metodos
void busca_em_profundidade_(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice, int* arvore, list<int>& sem_set);
void busca_em_profundidade_listas_adjacencia_(list<Vertice*>& grafo, Vertice* v);
void busca_em_largura_(int** grafo, int tamanho, list<int>& destino, int fonte);
void busca_fontes(int** grafo, int tamanho, list<int>& destino);
void colorir_apartir_de(Grafo* g,int vertice);
void descolorir(Grafo* g);
void busca_fontes_tipo(Grafo* g, char tipo, list<int>& destino);
void colorir_apartir_de_tipo (Grafo* g, int vertice, char tipo);
bool verifica_irmaos(int** grafo, int tamanho, int a, int b);

//Metodos "Finais"
extern void busca_em_largura_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz);
extern void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz);
extern void busca_em_largura(int**grafo, int tamanho, int* arvore);
extern void busca_em_profundidade(int**grafo, int tamanho, int* arvore);
extern void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino);

void encontra_casamento_irmaos(int** grafo, int tamanho, list<list<int>>& destino);

void colorir_grafo(Grafo* g);
void colorir_grafo_mat(Grafo* g);
void colorir_grafo_pat(Grafo* g);

#endif /* ALGORITMO_H*/
