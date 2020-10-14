#include <list>
using namespace std;
class Nodo;

struct Atributos_largura_lista {
	int cor;
	Nodo* nodo;
};
struct Atributos_profundidade_lista {};
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

		Atributos_vertice(int id, int numero, char tipo);
		void adicionar_cor(int cor_);
};

class Grafo {
	public:
		int numero_vertices;
		int** grafo;
		list<Atributos_vertice*> atributos;

		Grafo(int numero_vertices_, list<Atributos_vertice*> atributos_, int** grafo_);
		Atributos_vertice* encontrar_vertice(int id);
	void adicionar_aresta(int v1, int v2);
	void adicionar_arco(int fonte, int destino);
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


