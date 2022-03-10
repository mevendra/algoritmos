#ifndef TESTES_H
#define TESTES_H

#include "algoritmo.h"
#include "transformacao.h"

#include <chrono>
#include <iostream>
#include <time.h>

string nome_rede = "auto";

void testar_encontra_aneis_paralelos(Grafo* g, int k);
void testar_encontra_aneis_semi_paralelos(Grafo* g, int k);
void testar_encontra_aneis_linear(Grafo* g, int k);
void testar_encontra_aneis_paralelos(Grafo* g, int k, int numero_threads, int grao);
void testar_encontra_aneis_paralelos_1(Grafo* g, int k, int numero_threads, int grao);
void testar_encontra_aneis_linear_sem_cores(Grafo* g, int k);

//0
void testar_busca_em_largura(Grafo* g);
void testar_busca_em_profundidade(Grafo* g);
void testar_busca_componentes_conexas(Grafo* g);

//1
void testar_encontrar_casamentos_irmaos(Grafo* g);

//2
void testar_coloracao(Grafo* g);

//3
void testar_max_cores(Grafo* g);

//4
void testar_encontra_juncoes(Grafo* g);

//5
void testar_arvore_dominadores(Grafo* g);

//6
void testar_encontrar_subgrafos(Grafo* g);

//7
void testar_profundidades(Grafo* g);
void testar_geracoes(Grafo* g);

//8
void testar_encontrar_aneis(Grafo* g, int k);

//9
void testar_encontrar_aneis_coloridos(Grafo* g, int k);

void m_escreve_grafo_graphviz(Grafo* g, bool colorir, string caminho = "desenhos/" + nome_rede + "_grafo.dot");
void m_escreve_arvore_graphviz(Grafo* g, string caminho = "desenhos/" + nome_rede + "_arvore.dot");
void m_escreve_dominadores(Grafo* g, bool colorir, string caminho = "desenhos/" + nome_rede + "_dominadores.dot");
void m_escreve_componentes_graphviz(Grafo* g, string caminho = "desenhos/" + nome_rede + "_componentes.dot");

void m_escreve_cores(Grafo* g, string caminho = "outros/" + nome_rede + "_cores.txt");
void m_escreve_max_cores(Grafo* g, string caminho = "outros/" + nome_rede + "_max_cores.txt");
void m_escreve_aneis(Grafo* g, int numero_casamentos = 2, string caminho = "aneis/" + nome_rede + "_aneis_caminho.txt");
void m_escreve_aneis_completo(Grafo* g, int numero_casamentos = 2, string caminho = "aneis/" + nome_rede + "_aneis.txt");
void m_escreve_aneis_coloridos_completo(Grafo* g, int numero_casamentos = 2, string caminho = "aneis/" + nome_rede + "_coloridos.txt");
void m_escreve_comum_entre_grafos(Grafo* g, string caminho = "outros/" + nome_rede + "_comum.txt");
void m_escreve_informacao_grafos(Grafo* g, string caminho = "outros/" + nome_rede + "_info.txt");

void desabilitar_cout();
void reabilitar_cout();

//EScience
void executar_funcao_escience(Grafo* g, int numero_casamentos, int num_threads, int grao, int num_execucoes, string nome_rede);
void executar_escience(int argc, char *argv[]);
template<typename T>
void clear(T& estrutura);

#endif /* TESTES_H */
