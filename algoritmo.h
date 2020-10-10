#include "list"
#include <array>
#include <queue>
#include <stdlib.h>

#include "estrutura.h"

using namespace std;

static int tempo;

void busca_em_profundidade_(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice, int* arvore, list<int>& sem_set);
void busca_em_largura_(int** grafo, int tamanho, list<int>& destino, int fonte);

extern void busca_em_largura_listas_adjascencia(list<Vertice*>& grafo, Arvore* raiz);
extern void busca_em_profundidade_listas_adjascencia(list<Vertice*>& grafo, Arvore* raiz);

extern void busca_em_largura(int**grafo, int tamanho, int* arvore);

extern void busca_em_profundidade(int**grafo, int tamanho, int* arvore);

extern void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino);
