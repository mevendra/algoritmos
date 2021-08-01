#ifndef ALGORITMO_H
#define ALGORITMO_H

#include "estrutura.h"
#include "transformacao.h"

#include <semaphore.h>
#include <thread>
#include <mutex>
#include <fstream>
#include <climits>

static int tempo;
extern bool com_cores;

static clock_t tempo_encontra_anel_p = clock();
static clock_t tempo_verifica_anel = tempo_encontra_anel_p;
static clock_t tempo_encontra_anel = tempo_encontra_anel_p;
static clock_t tempo_copia_caminhos = tempo_encontra_anel_p;
static clock_t tempo_procura_caminhos = tempo_encontra_anel;
static clock_t tempo_sao_disjuntos = tempo_encontra_anel;

//Metodos utilizados por outros metodos
//0
void busca_em_profundidade(int** grafo, int tamanho, Atributos_profundidade* Vertices[], int vertice, int* arvore, list<int>& sem_set);
void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, Vertice* v);
void busca_em_largura(int** grafo, int tamanho, list<int>& destino, int fonte);

//1
bool verifica_irmaos(int** grafo, int tamanho, int a, int b);

//2
void busca_fontes(int** grafo, int tamanho, list<int>& destino);
void colorir_apartir_de(Grafo* g,int vertice);
void busca_fontes_tipo(Grafo* g, char tipo, list<int>& destino);
void colorir_apartir_de_tipo (Grafo* g, int vertice, char tipo);

//3
void define_super_sob_folhas(Grafo* g, list<int> &id_folhas);
void podar_folhas(Grafo* g);
void copiar(Grafo* g, Grafo* &destino);
void init_map(Grafo* g);
void encontra_raizes(Grafo* g, list<Vertice*>& destino);
template<typename T>
void ordem_topologica(Vertice* fonte, T& destino);
void ordem_topologica(Vertice* fonte, stack<Vertice*>& destino);
void procedimento_min_max(Vertice* f, Vertice* a, set<int> colors);

//4
void encontra_juncoes(Grafo* g, list<Juncao*>& destino);
void encontra_juncoes(Grafo* g, list<JuncoesDe*>& destino);

//5
void procedimento_dominadores(Grafo* g, vector<Vertice*> u, Vertice* s, vector<Vertice*> &dominadores_imediatos);
void cobertura_dominadores(Grafo* g, vector<Vertice*> u, Vertice* s, vector<Vertice*>& fd);

//6
;

//7
void passar_geracao_filhos(Vertice* v);
void passar_geracao_pais(Vertice* v);
void encontra_folhas(Grafo* g, list<Vertice*>& destino);


void encontra_caminhos_cores_especificas(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<list<Vertice*>> &caminhos, set<int> cores, int numero);
//8
void encontra_casamentos(Grafo* g, vector<list<int>>& casamentos);
void encontra_aneis_a1(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos, list<Anel*>& destino);
void encontra_aneis_a2(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos, list<Anel*>& destino);
void encontra_aneis_a3(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos, list<Anel*>& destino);
void encontra_duplas_casamentos(vector<list<int>> casamentos, list<list<list<int>>>& destino);
void encontra_combinacoes_dupla(list<list<int>> dupla_casamentos, list<list<list<int>>>& destino);
void encontra_trios_casamentos(vector<list<int>> casamentos, list<list<list<int>>>& destino);
void encontra_combinacoes_trio(list<list<int>> trio_casamentos, list<list<list<int>>>& destino);
void define_anel_aux(JuncoesDe* juncao, Anel_aux* destino);
void encontra_caminhos(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<list<Vertice*>> &caminhos);
bool sao_disjuntos(list<Vertice*> caminho_a, list<Vertice*> caminho_b);
void encontra_aneis(list<Anel_aux*> aux, vector<list<Vertice*>> atual, list<Anel*> & destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas);
void verifica_anel(vector<list<Vertice*>> caminhos, list<Anel*> &destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas);

//9
void encontra_aneis_coloridos(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino);
void encontra_combinacoes(vector<list<int>> casamentos,	list<list<list<int>>> &conjuntos, int numero_casamentos);
void encontra_pares_vertices(Juncoes* juncoes, list<list<list<int>>> conjuntos, set<Par*, par_cmp> &destino);
void encontra_caminhos_coloridos(set<Par*, par_cmp> &pares, short numero_threads, vector<vector<list<Caminho*>>> &destino);
void encontra_caminhos_coloridos_t(set<Par*, par_cmp> pares, int numero_cores, vector<vector<list<Caminho*>>> &destino);
void encontra_caminhos_coloridos_task(set<Par*, par_cmp> &pares, set<Par*, par_cmp>::iterator &iterator, vector<vector<list<Caminho*>>> &destino, int grao);
void encontra_caminhos_cores_especificas(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<Caminho*> &caminhos, set<int> cores, int cores_restantes);
void define_anel_aux_coloridos(JuncoesDe* juncao, Anel_aux* destino, vector<vector<list<Caminho*>>> &caminhos);
void define_anel_aux_coloridos_t(JuncoesDe* juncao, Anel_aux* destino, vector<vector<list<Caminho*>>> &caminhos);
set<int> soma(set<int> a, set<int> b);
void encontra_aneis_coloridos(list<Anel_aux*> aux, vector<list<Vertice*>> &atual, list<Anel*> & destino, list<list<int>> &casamentos, list<Juncao*> &juncoesUtilizadas, int numero_cores, set<int> &cores, int maior_caminho, int menor_caminho);
void encontra_aneis_coloridos_t(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino, int numero_cores);

//10
void thread_encontra_aneis_vetor(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino, int grao);
void thread_encontra_aneis_procurando(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, list<Anel*> &destino, int grao);

//Metodos "Finais"
//0
void busca_em_largura_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz);
void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz);
void busca_em_largura(int**grafo, int tamanho, int* arvore);
void busca_em_profundidade(int**grafo, int tamanho, int* arvore);
void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino);

//1
void encontra_casamento_irmaos(int** grafo, int tamanho, list<list<int>>& destino);

//2
void colorir_grafo(Grafo* g);
void colorir_grafo_mat(Grafo* g);
void colorir_grafo_pat(Grafo* g);
void descolorir(Grafo* g);

//3
void define_super_sob(Grafo* g);
void define_max_cores(Grafo* g);
template<typename T>
void ordem_topologica(Grafo* g, Vertice* fonte, T& destino);
void define_min_max_cores(Grafo* g);

//4
void encontra_juncoes(Grafo* g, Juncoes* destino);

//5
void encontra_arvore_dominadores(Grafo* g, vector<Vertice*> &dominadores_imediatos);

//6
void encontra_subgrafos(Grafo* fonte, vector<Grafo*> &subgrafos);

//7
int encontra_profundidade_dominadores(vector<Vertice*> dominadores, Vertice* raiz);
int encontra_profundidade_de(Vertice* v);
int encontra_profundidade_media_de(Vertice* v);
void geracao_grafo_superior(Grafo* g);
void geracao_grafo_inferior(Grafo* g);

//8
void encontra_aneis(Grafo* g, list<Anel*> & destino, int numero_casamentos);

//9
void encontra_aneis_coloridos(Grafo* g, list<Anel*>& destino, int numero_casamentos, bool paralelo = true);

//10
void encontra_aneis_paralelos_procurando(Grafo* g, list<Anel*>& destino, int numero_casamentos, int numero_threads_total, int grao);
void encontra_aneis_paralelos_vetor (Grafo* g, list<Anel*>& destino, int numero_casamentos, int numero_threads_total, int grao);

//teste
void colorir_grafo_esp(Grafo* g, int n);

#endif /* ALGORITMO_H*/
