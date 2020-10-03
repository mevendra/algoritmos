#include "list"
#include <array>
#include <queue>
#include <stdlib.h>

class Vertice {
	public:
		std::list<Vertice*> adjs;
		void* atributo;
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

static int tempo;
void busca_em_profundidade_(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice);

extern void busca_em_largura_listas_adjascencia(std::list<Vertice*>& grafo, std::list<Vertice*>& destino, Vertice* fonte);
extern void busca_em_largura(int** grafo, int tamanho, std::list<int>& destino, int fonte);
extern void busca_em_profundidade(int** grafo, int tamanho, std::list<int>& destino, int fonte);

extern void busca_componentes_conexas(int** grafo, int tamanho, std::list<std::list<int>>& destino);