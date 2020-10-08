#include "algoritmo.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void testa_busca_largura(int** grafo, int tamanho);
void testa_busca_profundidade(int** grafo, int tamanho);
void testa_busca_largura_listas(int** grafo, int tamanho);
void testa_busca_largura_listas(std::list<Vertice*>& grafo);
void testa_componentes_conexas(int** grafo, int tamanho);
int** cria_matriz(int tamanho);