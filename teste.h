#ifndef MAIN_H
#define MAIN_H

#include "algoritmo.h"
#include "transformacao.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void testar_busca_largura(Grafo* grafo);
void testar_busca_profundidade(Grafo* grafo);
void testar_busca_largura_listas(Grafo* grafo);
void testar_busca_profundidade_listas(Grafo* grafo);
void testar_componentes_conexas(Grafo* grafo);
void testar_colorir_grafo(Grafo *grafo);
void testar_colorir_grafo_mat(Grafo* grafo);
void testar_colorir_grafo_pat(Grafo* grafo);

#endif /* MAIN_H */
