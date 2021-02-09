#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <list>
#include <iomanip>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;
class Nodo;
class Particao;
class D_arvore;

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

class Vertice {
	public:
		list<Vertice*> adjs;
		list<Vertice*> filhos;
		list<Vertice*> pais;
		int id;
		void* atributo;

	Vertice();
	Vertice(int id_);

	void adicionar_aresta(Vertice* vertice);
	void adicionar_filho(Vertice* vertice);
	void adicionar_pai(Vertice* vertice);
};
class Atributos_vertice {
	class a{

	};
	public:
		int id;
		int numero;
		int geracao;
		char tipo;
		list<int> cor;
		list<Atributos_vertice*> pais;
		list<Atributos_vertice*> filhos;
		list<Atributos_vertice*> casados;

		int cores_ate_folha;
		Atributos_vertice* folha_cores;

		int particao;
		bool valor_bool;

		Atributos_vertice(int id, int numero, char tipo);
		void adicionar_cor(int cor_);
		void adicionar_casamento(Atributos_vertice* casamento);
		void adicionar_pais(Atributos_vertice* pai);
		void adicionar_filho(Atributos_vertice* filho);
};

class Grafo {
	public:
		int numero_vertices;
		int** grafo;
		list<Atributos_vertice*> atributos;

		Grafo(int numero_vertices_, list<Atributos_vertice*> atributos_, int** grafo_);
		void adicionar_aresta(int v1, int v2);
		void adicionar_arco(int fonte, int destino);
		Atributos_vertice* encontrar_atributo(int i);
};

class Nodo {
	public:
		int id;
		list<Nodo*> proximo;
		Nodo* anterior;

		Nodo(int id_);
		Nodo(int id_, Nodo* anterior_);
		void adicionar_filho(Nodo* filho);
	void adicionar_anterior(Nodo* anterior_);
};

class Cor {
	public:
		Cor();
		Cor(int r, int g, int b);
		Cor(string rgb);
		Cor(Cor* cor);

		string rgb;
		int r;
		int g;
		int b;
		void soma(Cor* c);
};

class Hash {
	vector<int> numeros;
	vector<Cor*> cores;

	public:
		Hash();
		~Hash();
		Cor* encontrar_cor(int numero);
		void adicionar_cor(int numero, Cor* cor);
		void limpar();
};

class Juncao {
	public:
		Atributos_vertice* primeiro;
		Atributos_vertice* segundo;
		Atributos_vertice* juncao;

		Juncao(Atributos_vertice* primeiro_, Atributos_vertice* segundo_, Atributos_vertice* juncao_);
};

class JuncoesDe {
	public:
		Atributos_vertice* primeiro;
		Atributos_vertice* segundo;

		list<Atributos_vertice*> juncoes;

		void adicionar_juncao(Atributos_vertice* juncao);
		JuncoesDe(Atributos_vertice* primeiro_, Atributos_vertice* segundo_);
};

class Anel {
	public:
		list<Atributos_vertice*> anel;
		list<Atributos_vertice*> vertices;
		list<list<Atributos_vertice*>> caminhos;
		list<list<Atributos_vertice*>> casamentos;
		list<Atributos_vertice*> juncoes;

		string linha_normal;
		string linha_ordem;

		void adicionar_elemento(list<Atributos_vertice*> caminho, bool caminho_inverso);
		void adicionar_elemento(vector<list<Atributos_vertice*>> caminho, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas, bool realizado= false);
};

class Anel_aux {
	public:
		Atributos_vertice* primeiro;
		Atributos_vertice* segundo;

		vector<Atributos_vertice*> juncoes;
		vector<vector<list<Atributos_vertice*>>> caminhos_primeiro;
		vector<vector<list<Atributos_vertice*>>> caminhos_segundo;
		void mudar_tamanho(int tamanho);
};

class Nodo_dominadores {
public:
	list<Nodo_dominadores*> sucessores_a_arv;
	list<Nodo_dominadores*> antecessores_a_arv;

	list<Nodo_dominadores*> sucessores_d_arv;
	list<Nodo_dominadores*> antecessores_d_arv;

	int id;
	Atributos_vertice* atributo;

	int count = 1;
	int weigth = 0;

	Nodo_dominadores(Atributos_vertice* v);
	//Ops D_Arv
	void adicionar_sucessor_d_arv(Nodo_dominadores* d);
	void adicionar_antecessor_d_arv(Nodo_dominadores* d);
	void remover_sucessor_d_arv(Nodo_dominadores* d);

	void se_tornar_filho_de_d_arv(Nodo_dominadores* d);
	bool contem_d_arv(Nodo_dominadores* d);
	Nodo_dominadores* primeiro_antecessor_d_arv();
	int tamanho_predecessores_d_arv();

	//Ops A_Arv
	void adicionar_sucessor_a_arv(Nodo_dominadores* a);
	void adicionar_antecessor_a_arv(Nodo_dominadores* a);
	void remover_sucessor_a_arv(Nodo_dominadores* a);
	bool contem_a_arv(Nodo_dominadores* a);
	int max_caminho_a_arv();
	void print_filhos_a_arv();
};

class A_arvore {
public:
	list<Nodo_dominadores*> raizes;
	vector<vector<Nodo_dominadores*>> ancestrais;

	A_arvore(list<Nodo_dominadores*> raizes_);
	void link(Nodo_dominadores* u, Nodo_dominadores* v);
	Nodo_dominadores* get_ancestor(Nodo_dominadores* u, int i);
	Nodo_dominadores* find(Nodo_dominadores* u, Nodo_dominadores* v, int i, int d);
	Nodo_dominadores* lowest(Nodo_dominadores* u, Nodo_dominadores* v, D_arvore* arv);
	Nodo_dominadores* raiz(Nodo_dominadores* u);
};

class D_arvore {
public:
	list<Nodo_dominadores*> raizes;

	D_arvore(list<Nodo_dominadores*> raizes_);
	Nodo_dominadores* raiz(Nodo_dominadores* u);
	int depth(Nodo_dominadores* u);
	void merge(Nodo_dominadores* u, Nodo_dominadores* v);
	Nodo_dominadores* lowest(Nodo_dominadores* u, Nodo_dominadores* v, A_arvore* arv);

};

class Region {
public:
	Nodo_dominadores* header;
	list<Nodo_dominadores*> membros;
	list<Region*> sucessores;
	list<Region*> antecessores;

	Region(Nodo_dominadores* header_);

	void juntar(Region* r);
};



#endif /* ESTRUTURA_H */
