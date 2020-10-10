#include <list>
using namespace std;

class Vertice {
	public:
		list<Vertice*> adjs;
		int id;
		void* atributo;

	Vertice();
	Vertice(int id_);

	void adicionar_aresta(Vertice* vertice);
};

struct Atributos_vertice {
	int id;
	int numero;
	char tipo;
	list<char*> cor;
};

struct Atributos_largura_lista {
	int cor;	//0=branco;	1=cinzento;	2=preto
	int distancia_fonte;
	Vertice* predecessor;
};
struct Atributos_profundidade_lista {

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

class Grafo {
	public:
		int numero_vertices;
		Atributos_vertice** atributos;
		int** grafo;

		Grafo(int numero_vertices_, Atributos_vertice** atributos_, int** grafo_);
	void adicionar_aresta(int v1, int v2);
	void adicionar_arco(int fonte, int destino);
};

class No {
	int id;
	No* proximo;
	No* anterior;
};

class Arvore {
	No* raiz;
};

