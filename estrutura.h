#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <list>
#include <set>
#include <vector>
#include <stack>
#include <array>
#include <queue>

#include <math.h>
#include <iomanip>
#include <sstream>
#include <string.h>

using namespace std;

template<typename T>
bool contem(T t, list<T> l);

static list<string> cores;
string primeira_cor();
void reinicia_cores();

class Nodo;

struct Atributos_largura_lista {
	int cor;
	Nodo* nodo;
};
struct Atributos_profundidade_lista {
	int cor;
	int tempo;
	Nodo* nodo;
};
struct Atributos_largura {
	int cor;	//0=branco;	1=cinzento;	2=preto
	int distancia_fonte;
	int predecessor;
};
struct Atributos_profundidade {
	int cor;	//0=branco;	1=cinzento;	2=preto
	int tempo_init;
	int tempo_fim	;
	int predecessor;
};
struct Atributos_componentes {
	int tem_set;
};

struct set_cmp {
	bool operator() (const set<int>& esquerda,const set<int>& direita) const {
		set<int>::iterator it_esq = esquerda.begin();
		set<int>::iterator it_dir = direita.begin();

		for (; it_esq != esquerda.end() && it_dir != direita.end(); it_esq++, it_dir++) {
			if (*it_esq == *it_dir)
				continue;
			else
				return *it_esq < *it_dir;
		}

		return esquerda.size() < direita.size();
	}
};

struct cor_cmp {
	bool operator() (set<int> esquerda, set<int> direita)  {
		set<int>::iterator it_esq = esquerda.begin();
		set<int>::iterator it_dir = direita.begin();

		for (; it_esq != esquerda.end() && it_dir != direita.end(); it_esq++, it_dir++) {
			if (*it_esq == *it_dir)
				continue;
			else
				return false;
		}

		return esquerda.size() == direita.size();
	}
};

class Cor {
	string rgb;
	int r;
	int g;
	int b;

public:
	Cor(int r, int g, int b);
	Cor(string rgb);
	Cor(Cor* cor);

	void soma(Cor* c);
	int to_int();
	string g_rgb() { return rgb; }
};

class Hash {
	vector<set<int>> numeros;
	vector<Cor*> cores;

	public:
		Hash() {}
		~Hash();
		Cor* encontrar_cor(int numero);
		Cor* encontrar_cor(set<int> numero);
		void adicionar_cor(int numero, Cor* cor);
		void adicionar_cor(set<int> numero, Cor* cor);
		void limpar();
		int tam() { return cores.size(); }
};

class Vertice {
	int id;
	int numero;
	char tipo;

	public:
		list<Vertice*> pais;
		list<Vertice*> filhos;
		list<Vertice*> casados;

		int cor_int = 0;	//obtido atraves do map em grafos utilizando set<int> cor
		int cores_ate_folha = 1;	//Maximo de cores até alguma folha
		set<int> cor;	//Representa a cor do vertice
		set<set<int>, set_cmp> cores;	//Cores até as folhas
		vector<int> min_cores;
		vector<int> max_cores;

		//Valores auxiliares utilizados por metodos
		int geracao = -1;
		int valor_int = -1;
		bool valor_bool = false;
		bool valor_bool_2 = false;
		void* ponteiro = 0;

		Vertice(int id, int numero, char tipo);
		void adicionar_cor(int cor_);
		void adicionar_casamento(Vertice* casamento);
		void adicionar_pais(Vertice* pai);
		void adicionar_filho(Vertice* filho);
		void resetar();

		int g_id() { return id; }
		int g_numero() { return numero; }
		char g_tipo() { return tipo; }
};

class Grafo {
	int numero_vertices;
	Vertice* raiz = 0;

	public:
		int** grafo;
		Hash* map = 0;
		vector<Vertice*> atributos;

		Grafo(int numero_vertices_, vector<Vertice*> atributos_, int** grafo_);
		Grafo(int numero_vertices_, vector<Vertice*> atributos_, Vertice* raiz, int** grafo_);
		Vertice* encontrar_atributo(int i);
		void adicionar_vertice(Vertice* v);
		void remover_vertice(Vertice* v);
		void resetar();
		int g_numero_vertices() { return numero_vertices; }
		Vertice* g_raiz() { return raiz; }
};

class Nodo {
	Vertice* nodo;
public:
	list<Nodo*> sucessores;
	list<Nodo*> antecessores;

	Nodo(Vertice* nodo_);
	void adicionar_sucessor(Nodo * sucessor);
	void adicionar_antecessor(Nodo * antecessor);
	void print_filhos();
	void pos_ordem(list<Nodo*> &destino);
	Vertice* g_vertice() { return nodo; }
};

class Juncao {
public:
	Vertice* primeiro;
	Vertice* segundo;
	Vertice* juncao;

	Juncao(Vertice* primeiro_, Vertice* segundo_, Vertice* juncao_);
};

class JuncoesDe {
public:
	Vertice* primeiro;
	Vertice* segundo;

	list<Vertice*> juncoes;

	void adicionar_juncao(Vertice* juncao);
	JuncoesDe(Vertice* primeiro_, Vertice* segundo_);
};

class Juncoes {
public:
	vector<vector<JuncoesDe*>> juncoes;

	Juncoes(int tamanho) { juncoes = vector<vector<JuncoesDe*>>(tamanho, vector<JuncoesDe*>(tamanho, 0)); }
	void adicionarJuncoes(JuncoesDe* j) {	juncoes[j -> primeiro -> g_id()][j -> segundo -> g_id()] = j;
											juncoes[j -> segundo -> g_id()][j -> primeiro -> g_id()] = j; }
};

class Anel_aux {
public:
	Vertice* primeiro;
	Vertice* segundo;

	vector<Vertice*> juncoes;
	vector<vector<list<Vertice*>>> caminhos_primeiro;
	vector<vector<list<Vertice*>>> caminhos_segundo;

	vector<vector<set<int>>> cores;

	void mudar_tamanho(int tamanho);
};

class Anel {
public:
	list<Vertice*> anel;
	list<Vertice*> vertices;
	list<list<Vertice*>> caminhos;
	list<list<Vertice*>> casamentos;
	list<Vertice*> juncoes;

	string linha_normal;
	string linha_ordem;

	void adicionar_elemento(vector<list<Vertice*>> caminho, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas, bool realizado= false);
};

#endif /* ESTRUTURA_H */
