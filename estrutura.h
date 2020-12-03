#ifndef ESTRUTURA_H
#define ESTRUTURA_H

#include <list>
#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;
class Nodo;
class Particao;

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
	public:
		int id;
		int numero;
		char tipo;
		list<int> cor;
		list<Atributos_vertice*> pais;
		list<Atributos_vertice*> filhos;
		list<Atributos_vertice*> casados;
		int cores_ate_folha;
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
class Particao {
	public:
		Atributos_vertice* primeiro;
		list<Atributos_vertice*> vertices;
		int id_primeiro;
		bool ja_avaliado;
		Particao(Atributos_vertice* primeiro);

		void adicionar_vertice(Atributos_vertice* vertice);
};

class Anel {
	public:
		list<Atributos_vertice*> anel;

		void adicionar_elemento(list<Atributos_vertice*> caminho);
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

#endif /* ESTRUTURA_H */
