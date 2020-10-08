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

class Arvore {
	public:
		int id;
};
	
struct Atributos {
	int cor;	//0=branco;	1=cinzento;	2=preto
	int distancia_fonte;
	Vertice* predecessor;
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