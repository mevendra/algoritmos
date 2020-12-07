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
	//
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
void testar_max_cores_ate_folha(Grafo* g) {
	printf("Testando encontrar o maior numero de cores diferentes ate uma folha\n");
	//colorir_grafo(g);

	colorir_grafo_mat(g);
	define_max_cores(g);
	for (Atributos_vertice* v: g -> atributos)
	{
		printf("Vertice %d(%d): Tem %d cores diferentes ate folha!\n", v -> id, v -> numero, v -> cores_ate_folha);
	}
	descolorir(g);
}
void testar_juncoes(Grafo* g) {
	printf("Testando encontrar juncoes\n");
	list<Juncao*> destino;
	encontra_juncoes(g, destino);
	int num = 1088;
	printf("Mostrando Juncoes sobre o numero %d\n", num);
	for (Juncao* j: destino)
	{
		if (j -> juncao -> numero == num)
			printf("Juncao %d sobre %d e %d encontrada\n", j -> juncao -> numero, j -> primeiro -> numero, j -> segundo -> numero);
	}
	printf("Numero de juncoes encontradas: %d\n", destino.size());
}
void testar_aneis(Grafo* g, int k) {
	printf("Testando encontrar aneis com %d casamentos\n", k);
	list<Anel*> destino;
	encontra_aneis(g, destino, k);
	printf("Um exemplo de anel: \n");
	Anel* ex;
	if (destino.size() > 0) {
		ex = destino.front();
		for (Atributos_vertice* i: ex -> anel)
			printf("%d  ", i -> numero);
		printf("\n");
		ex = destino.back();
		for (Atributos_vertice* i: ex -> anel)
			printf("%d  ", i -> numero);
		printf("\n");
	}



	printf("Numero de aneis encontrados: %d\n", destino.size());
}
int main(int argc, char *argv[]) {
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
	testar_max_cores_ate_folha(g);
	testar_juncoes(g);
	testar_aneis(g, 2);

	bool escreve_grafos = false;
	if (escreve_grafos) {
	//Escrita dos grafos
	//Grafo normal (sem cores)
	escreve_grafo_graphviz(g, false, "entrada/grafo_normal.dot");
	printf("Escreveu grafo normal!\n");

	//Arvore
	int* arv = new int[g -> numero_vertices];
	busca_em_largura(grafo, g -> numero_vertices, arv);
	escreve_arvore_graphviz(g, arv, "entrada/arvore.dot");
	printf("Escreveu arvore!\n");

	//Componentes conexas
	list<list<int>> lista;
	busca_componentes_conexas(grafo, g -> numero_vertices, lista);
	escreve_componentes_graphviz(g, lista, "entrada/componentes.dot");
	printf("Escreveu componentes!\n");

	//Grafo Colorido
	colorir_grafo(g);
	escreve_grafo_graphviz(g, true, "entrada/grafo_colorido.dot");
	descolorir(g);
	printf("Escreveu grafo colorido\n");

	//Grafo materno colorido
	colorir_grafo_mat(g);
	escreve_grafo_graphviz(g, true, "entrada/grafo_colorido_mat.dot");
	descolorir(g);
	printf("Escreveu grafo materno colorido!\n");

	//Grafo paterno colorido
	colorir_grafo_pat(g);
	escreve_grafo_graphviz(g, true, "entrada/grafo_colorido_pat.dot");
	descolorir(g);
	printf("Escreveu e coloriu pat!\n");


	list<list<int>> destino;
	//Componentes de casamento entre irmaos
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	escreve_componentes_sem_elementos_graphviz(g, destino, "entrada/casamento_irmaos.dot");
	printf("Escreveu Componentes de casamento entre irmaos!\n");

	//Componentes de casamento entre irmaos + grafo colorido
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	colorir_grafo(g);
	escreve_grafo_com_componentes_especiais(g, destino, "entrada/grafo_colorido_com_casamento_irmaos.dot");
	descolorir(g);
	printf("Escreveu Componentes de casamento entre irmaos junto com grafo colorido!\n");

	//Componentes de casamento entre irmaos + grafo materno colorido
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	colorir_grafo_mat(g);
	escreve_grafo_com_componentes_especiais(g, destino, "entrada/grafo_colorido_materno_com_casamento_irmaos.dot");
	descolorir(g);
	printf("Escreveu Componentes de casamento entre irmaos junto com grafo materno colorido!\n");

	//Componentes de casamento entre irmaos + grafo paterno colorido
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	colorir_grafo_pat(g);
	escreve_grafo_com_componentes_especiais(g, destino, "entrada/grafo_colorido_paterno_com_casamento_irmaos.dot");
	descolorir(g);
	printf("Escreveu Componentes de casamento entre irmaos junto com grafo paterno colorido!\n");

	//Saida textual das cores
	colorir_grafo(g);
	escreve_cores(g, "entrada/cores.txt");
	escreve_max_cores(g, "entrada/max_cores.txt");
	descolorir(g);

	//Saida textual das cores maternas
	colorir_grafo_mat(g);
	escreve_cores(g, "entrada/cores_mat.txt");
	escreve_max_cores(g, "entrada/max_cores_mat.txt");
	descolorir(g);

	//Saida textual das cores paternas
	colorir_grafo_pat(g);
	escreve_cores(g, "entrada/cores_pat.txt");
	escreve_max_cores(g, "entrada/max_cores_pat.txt");
	descolorir(g);
	}
	return 0;
}

