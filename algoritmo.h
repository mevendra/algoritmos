#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "list"
#include <array>
#include <queue>
#include <vector>
#include <stack>
#include <stdlib.h>
#include "estrutura.h"
#include "lista.h"
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

void ordem_topologica(Atributos_vertice* fonte, queue<Atributos_vertice*>& destino);
bool contem(int elem, list<int> fonte);
void encontrar_casamentos_ordenados(int k, list<int>& atual, list<int>& fonte, list<list<int>>& destino);
void encontra_casamentos(Grafo* g, list<list<int>>& casamentos);
void encontra_conjuntos_casamentos(list<list<int>> casamentos, int k, list<list<list<int>>> &destino);
void encontra_pares(queue<list<int>> fonte, list<list<int>> atual, int v_atual, int v_primeiro, list<list<list<int>>> &destino);

//Metodos "Finais"
extern void busca_em_largura_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz);
extern void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz);
extern void busca_em_largura(int**grafo, int tamanho, int* arvore);
extern void busca_em_profundidade(int**grafo, int tamanho, int* arvore);
extern void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino);
void encontrar_combinacoes(list<int> fonte, list<int>& atual, list<list<int>>& destino);

void encontra_casamento_irmaos(int** grafo, int tamanho, list<list<int>>& destino);

void colorir_grafo(Grafo* g);
void colorir_grafo_mat(Grafo* g);
void colorir_grafo_pat(Grafo* g);

void define_max_cores(Grafo* g);

void encontra_juncoes(Grafo* g, list<Juncao*>& destino);
void encontra_juncoes(Grafo* g, list<JuncoesDe*>& destino);
void encontra_aneis(Grafo* g, list<Anel*> & destino, int numero_casamentos);
#endif /* ALGORITMO_H*/
