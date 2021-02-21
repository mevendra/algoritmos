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
	printf("\nNumero de raizes: %ld\n", arvore.size());
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
		printf("Vertice %d(%d): Tem %d cores diferentes ate folha(%d)!\n", v -> id, v -> numero, v -> cores_ate_folha, v -> folha_cores -> numero);
		if (v -> folha_cores -> filhos.size() > 0)
			printf("Erro, %d nao é folha\n", v -> folha_cores -> numero);
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
	printf("Numero de juncoes encontradas: %ld\n", destino.size());
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



	printf("Numero de aneis encontrados: %ld\n", destino.size());
}

void testar_dominadores(Grafo* g) {
	printf("Testando encontrar dominadores no grafo\n");
	Nodo_dominadores* d = NULL;

	encontra_arvore_denominadores(g, d);

	if (d == NULL) {
		printf("Erro ao encontrar dominadores\n");
		return;
	}
	d -> print_filhos_a_arv();

	printf("Terminou!\n");
}

int main(int argc, char *argv[]) {
	//Primeiro argumento(NOME) = nome arquivo, segundo(NUMERO) = numero de casamentos para testar aneis

	string entrada = "entrada/";
	string resultado = "aneis/aneis_";
	int k = 1;
	if (argc == 1) {
		entrada += "Arara4MaqPar.txt";
		//entrada += "rede_grande.txt";
		resultado += to_string(k);
	} else if (argc == 2) {
		entrada += argv[1];
		resultado += to_string(k);
		resultado += "_";
		resultado += argv[1];
	} else if (argc == 3) {
		entrada += argv[1];
		k = atoi(argv[2]);
		resultado += to_string(k);
		resultado += "_";
		resultado += argv[1];
	} else if (argc > 3)
		return -1;

	Grafo *g = trabalha_arquivo(entrada.c_str());
	if (!g)
		return 0;
	int **grafo = g->grafo;

	list<Anel*> aneis;
	encontra_aneis(g, aneis, k, resultado.c_str());

	return 0;
}

