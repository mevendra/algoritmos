#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "list"
#include <array>
#include <queue>
#include <vector>
#include <stack>
#include <stdlib.h>
#include <fstream>
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
void encontra_casamentos(Grafo* g, list<list<int>>& casamentos);
void encontra_casamentos(Grafo* g, vector<list<int>>& casamentos);

void encontra_caminhos(Atributos_vertice* fonte, Atributos_vertice* destino,list<Atributos_vertice*> caminho_atual, list<list<Atributos_vertice*>> &caminhos);
bool sao_disjuntos(list<Atributos_vertice*> caminho_a, list<Atributos_vertice*> caminho_b);
void verifica_anel(vector<list<Atributos_vertice*>> caminhos, list<Anel*> &destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas);
void encontra_aneis(list<Anel_aux*> aux, vector<list<Atributos_vertice*>> atual, list<Anel*> & destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas);
void encontra_duplas_casamentos(vector<list<int>> casamentos, list<list<list<int>>>& destino);
void encontra_combinacoes_dupla(list<list<int>> dupla_casamentos, list<list<list<int>>>& destino);
void encontra_trios_casamentos(vector<list<int>> casamentos, list<list<list<int>>>& destino);
void encontra_combinacoes_trio(list<list<int>> trio_casamentos, list<list<list<int>>>& destino);
void define_anel_aux(JuncoesDe* juncao, Anel_aux* destino);
void encontra_aneis_a1(list<JuncoesDe*> juncoes, vector<list<int>> casamentos, list<Anel*>& destino);
void encontra_aneis_a2(Grafo* g, list<JuncoesDe*> juncoes, vector<list<int>> casamentos, list<Anel*>& destino);
void encontra_aneis_a3(Grafo* g, list<JuncoesDe*> juncoes, vector<list<int>> casamentos, list<Anel*>& destino);
void casamentos_sem_juncao(vector<list<int>> casamentos, list<JuncoesDe*> juncoes, Grafo* g);

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

void encontra_arvore_denominadores(Grafo* g, Nodo_dominadores* &raiz);

#endif /* ALGORITMO_H*/
