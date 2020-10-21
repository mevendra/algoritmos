#include "teste.h"
void testar_busca_largura(Grafo* grafo) {
	printf("\nTestando busca em largura: \n");
	int *arvore = new int[grafo -> numero_vertices];
	int num_raiz = 0;
	busca_em_largura(grafo -> grafo, grafo -> numero_vertices, arvore);

	printf("Arvore: \n");
	for (int i = 0; i < grafo -> numero_vertices; i++) {
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", grafo -> encontrar_atributo(arvore[i]) -> numero);
	}
	printf("\nNumero de raizes: %d\n", num_raiz);
}
void testar_busca_profundidade(Grafo* grafo) {
	printf("\nTestando busca em profundidade: \n");
	int *arvore = new int[grafo -> numero_vertices];
	int num_raiz = 0;
	busca_em_profundidade(grafo -> grafo, grafo -> numero_vertices, arvore);

	printf("Arvore: \n");
	for (int i = 0; i < grafo -> numero_vertices; i++) {
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", grafo -> encontrar_atributo(arvore[i])->numero);
	}
	printf("\nNumero de raizes: %d\n", num_raiz);
}
void testar_busca_largura_listas(Grafo* graf) {
	printf("\nTestando busca em largura: \n");
	list<Nodo*> arvore;
	list<Vertice*> g;
	Vertice *a;
	Vertice *b;
	int tamanho = graf -> numero_vertices;
	int** grafo = graf -> grafo;

	for (int i = 0; i < tamanho; i++) {
		a = new Vertice(i);
		g.push_back(a);
	}

	for (int i = 0; i < tamanho; i++) {
		for (int y = 0; y < tamanho; y++) {
			if (grafo[i][y] == 1) {

				for (Vertice *v : g) {
					if (v->id == i)
						a = v;
					else if (v->id == y)
						b = v;
				}
				a->adicionar_aresta(b);
			} else if (grafo[i][y] == 2) {
				for (Vertice *v : g) {
					if (v->id == i)
						a = v;
					else if (v->id == y)
						b = v;
				}
				a->adicionar_filho(b);
			} else if (grafo[i][y] == 3) {
				for (Vertice *v : g) {
					if (v->id == i)
						a = v;
					else if (v->id == y)
						b = v;
				}
				a->adicionar_pai(b);
			} else if (grafo[i][y] == 12) {
				for (Vertice *v : g) {
					if (v->id == i)
						a = v;
					else if (v->id == y)
						b = v;
				}
				a->adicionar_filho(b);
				a->adicionar_aresta(b);
			} else if (grafo[i][y] == 13) {
				for (Vertice *v : g) {
					if (v->id == i)
						a = v;
					else if (v->id == y)
						b = v;
				}
				a->adicionar_pai(b);
				a->adicionar_aresta(b);
			}
		}
	}
	busca_em_largura_listas_adjacencia(g, arvore);

	printf("Vertices raiz: \n");
	for (Nodo *n : arvore) {
		printf("%d ", graf -> encontrar_atributo(n->id) -> numero);
	}
	printf("\nNumero de raizes: %d\n", arvore.size());
}
void testar_busca_profundidade_listas(Grafo* graf) {
}
void testar_componentes_conexas(Grafo* grafo) {
	printf("\nTestando busca de componentes conexas\n");
	list<list<int>> destino;

	busca_componentes_conexas(grafo -> grafo, grafo -> numero_vertices, destino);
	for (list<int> m : destino) {
		printf("Proximo componente:\n");
		for (int i : m) {
			printf("%d ", grafo -> encontrar_atributo(i) -> numero);

		}
		printf("\n");
	}
}
void testar_colorir_grafo(Grafo *grafo) {
	printf("Testando colorir grafo\n");
	colorir_grafo(grafo);

	for (Atributos_vertice *a : grafo->atributos) {
		printf("Id: %d, Numero: %d, Tipo: %c ||Cores: ", a->id, a->numero, a->tipo);
		for (int i : a->cor) {
			printf("%d | ", grafo -> encontrar_atributo(i) -> numero);
		}
		printf("\n");
	}

	descolorir(grafo);
}

void testar_colorir_grafo_mat(Grafo* grafo) {
	printf("Testando colorir grafo\n");
	colorir_grafo_mat(grafo);


	for (Atributos_vertice *a : grafo->atributos) {
		printf("Id: %d, Numero: %d, Tipo: %c ||Cores: ", a->id, a->numero, a->tipo);
		for (int i : a->cor) {
			printf("%d | ", grafo -> encontrar_atributo(i) -> numero);
		}
		printf("\n");
	}

	descolorir(grafo);
}
void testar_colorir_grafo_pat(Grafo* grafo) {
	printf("Testando colorir grafo\n");
	colorir_grafo_pat(grafo);

	for (Atributos_vertice *a : grafo->atributos) {
		printf("Id: %d, Numero: %d, Tipo: %c ||Cores: ", a->id, a->numero, a->tipo);
		for (int i : a->cor) {
			printf("%d | ", grafo -> encontrar_atributo(i) -> numero);
		}
		printf("\n");
	}

	descolorir(grafo);
}
void testar_casamento_entre_irmaos(Grafo* g) {
	list<list<int>> destino;
	encontra_casamento_irmaos(g ->grafo, g -> numero_vertices, destino);
	for (list<int> a: destino) {
		printf("Casamento entre irmaos: ");
		for (int i: a) {
			printf("%d ", g -> encontrar_atributo(i) -> numero);
		}
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	srand(time(NULL));

	Grafo *g = trabalha_arquivo("entrada/Arara4MaqPar.txt");
	int **grafo = g->grafo;

	testar_busca_largura(g);
	testar_busca_profundidade(g);//Testando somente arestas, com arcos e totalmente conexo
	testar_componentes_conexas(g);
	testar_busca_largura_listas(g);
	testar_colorir_grafo_mat(g);
	testar_colorir_grafo_mat(g);
	testar_colorir_grafo(g);
	testar_casamento_entre_irmaos(g);

	escreve_grafo_graphviz(g, false, "entrada/grafo_normal.dot");

	int* arv = new int[g -> numero_vertices];
	busca_em_largura(grafo, g -> numero_vertices, arv);
	escreve_arvore_graphviz(g, arv, "entrada/arvore.dot");

	list<list<int>> lista;
	busca_componentes_conexas(grafo, g -> numero_vertices, lista);
	escreve_componentes_graphviz(g, lista, "entrada/componentes.dot");

	//escrevendo e colorindo
	colorir_grafo(g);
	escreve_grafo_graphviz(g, true, "entrada/grafo_colorido.dot");
	descolorir(g);

	colorir_grafo_mat(g);
	escreve_grafo_graphviz(g, true, "entrada/grafo_colorido_mat.dot");
	descolorir(g);

	colorir_grafo_pat(g);
	escreve_grafo_graphviz(g, true, "entrada/grafo_colorido_pat.dot");
	descolorir(g);

	//casamento entre irmaos
	list<list<int>> destino;
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	escreve_componentes_graphviz(g, destino, "entrada/casamento_irmaos.dot");

	return 0;

}

