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
	printf("Primeiro Algoritmo:\n");
	Nodo_dominadores* d = NULL;

	encontra_arvore_dominadores(g, d);

	if (d == NULL) {
		printf("Erro ao encontrar dominadores\n");
		return;
	}
	d -> print_filhos_a_arv();

	printf("Segundo Algoritmo:\n");
	vector<Atributos_vertice*> dominadores;
	encontra_arvore_dominadores(g, dominadores);
	int i = 0;
	int w;
	for (Atributos_vertice* v: dominadores) {
		printf("%d, %d", g-> atributos[i] -> numero, v -> numero);
		w = v -> id;
		while(w < g -> numero_vertices) {
			Atributos_vertice* aux = dominadores[w];
			w = aux -> id;
			printf(" %d", aux -> numero);
		}
		printf("\n");

	}
	printf("Terminou!\n");
	return;
}

int main(int argc, char *argv[]) {
	//Primeiro argumento = nome arquivo, segundo = numero de casamentos para testar aneis
	string entrada = "entrada/";
	int k = 1;
	if (argc == 1) {
		//entrada += "rede_pequena.txt";
		entrada += "Arara4MaqPar.txt";
		//entrada += "rede_grande.txt";
		//entrada += "EN4MaqPar.txt";
	} else if (argc == 2) {
		entrada += argv[1];
	} else if (argc == 3) {
		entrada += argv[1];
		k = atoi(argv[2]);
	} else if (argc > 3)
		return -1;

	Grafo *g = trabalha_arquivo(entrada.c_str());
	int **grafo;
	if (g)
		grafo = g->grafo;
	else
		return 1;

	std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
	printf("Inicio\n");

	/*
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
	testar_aneis(g, k);
	testar_dominadores(g);*/

	vector<Grafo*> subgrafos;
	encontra_subgrafos(g, subgrafos);

	escreve_informacao_grafos(g, subgrafos, "outros/informacoes.txt");

	/*
	for (Grafo* g1: subgrafos) {
		vector<Atributos_vertice*> dominadores(g1 -> numero_vertices + 1, 0);
		cam = "desenhos/dominadores_mat_";
		cam += to_string(g1 -> raiz -> numero);
		cam += ".dot";
		encontra_arvore_dominadores(g1, dominadores);
		escreve_arvore_graphviz(g1, dominadores,true, cam.c_str());
	}*/

	/*
	for (Grafo* g1: subgrafos) {
		printf("aqui\n");
		for (Atributos_vertice* v: g1 -> atributos)
			v -> particao = -1;
		cam = "desenhos/subgrafo_mat_";
		cam += to_string(g1 -> raiz -> numero);
		cam += ".dot";
		escreve_grafo_graphviz(g1, true, cam.c_str());
	}*/

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;


	bool escreve_grafos = false;
	if (escreve_grafos) {
	//Dominadores
	vector<Atributos_vertice*> dominadores(g -> numero_vertices, 0);
	colorir_grafo(g);
	encontra_arvore_dominadores(g, dominadores);
	escreve_arvore_graphviz(g, dominadores,true, "desenhos/arvore_dominadores_2_na.dot");

	Nodo_dominadores* raiz;
	colorir_grafo_mat(g);
	encontra_arvore_dominadores(g, raiz);
	escreve_arvore_graphviz(g, raiz,true, "desenhos/arvore_dominadores_2_aa.dot");

	//Arvore
	int* arv = new int[g -> numero_vertices];
	busca_em_largura(grafo, g -> numero_vertices, arv);
	escreve_arvore_graphviz(g, arv, "desenhos/arvore.dot");
	printf("Escreveu arvore!\n");

	//Componentes conexas
	list<list<int>> lista;
	busca_componentes_conexas(grafo, g -> numero_vertices, lista);
	escreve_componentes_graphviz(g, lista, "desenhos/componentes.dot");
	printf("Escreveu componentes!\n");

	//Grafo Colorido
	colorir_grafo(g);
	escreve_grafo_graphviz(g, true, "desenhos/grafo_colorido.dot");
	descolorir(g);
	printf("Escreveu grafo colorido\n");

	//Grafo materno colorido
	colorir_grafo_mat(g);
	escreve_grafo_graphviz(g, true, "desenhos/grafo_colorido_mat.dot");
	descolorir(g);
	printf("Escreveu grafo materno colorido!\n");

	//Grafo paterno colorido
	colorir_grafo_pat(g);
	escreve_grafo_graphviz(g, true, "desenhos/grafo_colorido_pat.dot");
	descolorir(g);
	printf("Escreveu e coloriu pat!\n");


	list<list<int>> destino;
	//Componentes de casamento entre irmaos
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	escreve_componentes_sem_elementos_graphviz(g, destino, "desenhos/casamento_irmaos.dot");
	printf("Escreveu Componentes de casamento entre irmaos!\n");

	//Componentes de casamento entre irmaos + grafo colorido
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	colorir_grafo(g);
	escreve_grafo_com_componentes_especiais(g, destino, "desenhos/grafo_colorido_com_casamento_irmaos.dot");
	descolorir(g);
	printf("Escreveu Componentes de casamento entre irmaos junto com grafo colorido!\n");

	//Componentes de casamento entre irmaos + grafo materno colorido
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	colorir_grafo_mat(g);
	escreve_grafo_com_componentes_especiais(g, destino, "desenhos/grafo_colorido_materno_com_casamento_irmaos.dot");
	descolorir(g);
	printf("Escreveu Componentes de casamento entre irmaos junto com grafo materno colorido!\n");

	//Componentes de casamento entre irmaos + grafo paterno colorido
	destino.clear();
	encontra_casamento_irmaos(grafo, g -> numero_vertices, destino);
	colorir_grafo_pat(g);
	escreve_grafo_com_componentes_especiais(g, destino, "desenhos/grafo_colorido_paterno_com_casamento_irmaos.dot");
	descolorir(g);
	printf("Escreveu Componentes de casamento entre irmaos junto com grafo paterno colorido!\n");

	//Saida textual das cores
	colorir_grafo(g);
	escreve_cores(g, "outros/cores.txt");
	escreve_max_cores(g, "outros/max_cores.txt");
	descolorir(g);

	//Saida textual das cores maternas
	colorir_grafo_mat(g);
	escreve_cores(g, "outros/cores_mat.txt");
	escreve_max_cores(g, "outros/max_cores_mat.txt");
	descolorir(g);

	//Saida textual das cores paternas
	colorir_grafo_pat(g);
	escreve_cores(g, "outros/cores_pat.txt");
	escreve_max_cores(g, "outros/max_cores_pat.txt");
	descolorir(g);
	}
	return 0;
}

