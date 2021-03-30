#include "testes.h"

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
		nome_rede = string(argv[1]);
		entrada += argv[1];
	} else if (argc == 3) {
		nome_rede = string(argv[1]);
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



	//testar_encontrar_aneis(g, 2);
	//testar_encontrar_aneis_coloridos(g, 2);


	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << "[s]" << std::endl;

	/*
		testar_busca_em_largura(g);
		//testar_busca_em_profundidade(g);
		testar_busca_componentes_conexas(g);
		testar_encontrar_casamentos_irmaos(g);
		testar_coloracao(g);
		testar_max_cores(g);
		testar_encontra_juncoes(g);
		testar_arvore_dominadores(g);
		testar_encontrar_subgrafos(g);
		testar_profundidades(g);
		testar_geracoes(g);
		testar_encontrar_aneis(g, k);
		testar_encontrar_aneis_coloridos(g, k);*/


		colorir_grafo(g);
		m_escreve_grafo_graphviz(g, true);
		m_escreve_arvore_graphviz(g);
		//m_escreve_dominadores(g, true);
		m_escreve_componentes_graphviz(g);

		m_escreve_cores(g);
		m_escreve_max_cores(g);
		m_escreve_aneis(g, k);
		m_escreve_aneis_completo(g, k);
		m_escreve_aneis_coloridos_completo(g, k);
		m_escreve_comum_entre_grafos(g);
		m_escreve_informacao_grafos(g);
	 /**/
}

void testar_busca_em_largura(Grafo* g)
{
	printf("\nTestando busca em largura: Matriz\n");
	int *arvore = new int[g -> g_numero_vertices()];
	int num_raiz = 0;
	busca_em_largura(g -> grafo, g -> g_numero_vertices(), arvore);

	printf("Arvore: \n");
	for (int i = 0; i < g -> g_numero_vertices(); i++) {
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", g -> encontrar_atributo(arvore[i]) -> g_numero());
	}
	printf("\nNumero de raizes: %d\n", num_raiz);

	printf("\nTestando busca em largura: Listas\n");
	list<Nodo*> arvore_;
	list<Vertice*> vertices;

	for (Vertice* v: g -> atributos) {
		vertices.push_back(v);
	}

	busca_em_largura_listas_adjacencia(vertices, arvore_);

	printf("Vertices raiz: \n");
	for (Nodo *n : arvore_) {
		printf("%d ", n -> g_vertice() -> g_numero());
	}

	printf("\nNumero de raizes: %ld\n", arvore_.size());
}

void testar_busca_em_profundidade(Grafo* g)
{
	printf("\nTestando busca em profundidade: Matriz\n");
	int *arvore = new int[g -> g_numero_vertices()];
	int num_raiz = 0;
	busca_em_profundidade(g -> grafo, g -> g_numero_vertices(), arvore);

	printf("Arvore: \n");
	for (int i = 0; i < g -> g_numero_vertices(); i++) {
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", g -> encontrar_atributo(arvore[i]) -> g_numero());
	}

	printf("\nNumero de raizes: %d\n", num_raiz);

	printf("\nTestando busca em profundidade: Listas\n");
	list<Nodo*> arvore_;
	list<Vertice*> vertices;

	for (Vertice* v: g -> atributos) {
		vertices.push_back(v);
	}
	busca_em_profundidade_listas_adjacencia(vertices, arvore_);

	printf("Vertices raiz: \n");
	for (Nodo *n : arvore_) {
		printf("%d ", n -> g_vertice() -> g_numero());
	}

	printf("\nNumero de raizes: %ld\n", arvore_.size());
}

void testar_busca_componentes_conexas(Grafo* g)
{
	printf("\nTestando busca de componentes conexas\n");
	list<list<int>> destino;

	busca_componentes_conexas(g -> grafo, g -> g_numero_vertices(), destino);
	for (list<int> m : destino) {
		printf("Proximo componente:\n");
		for (int i : m) {
			printf("%d ", g -> encontrar_atributo(i) -> g_numero());

		}
		printf("\n");
	}
}

void testar_encontrar_casamentos_irmaos(Grafo* g)
{
	printf("\nTestando casamentos entre irmaos\n");
	list<list<int>> destino;
	encontra_casamento_irmaos(g -> grafo, g -> g_numero_vertices(), destino);

	for (list<int> c: destino) {
		if (c.size() == 2) {
			printf("Casamento entre irmaos %d e %d\n", g -> encontrar_atributo(c.front()) -> g_numero(), g -> encontrar_atributo(c.back()) -> g_numero());
		}
	}
}

void testar_coloracao(Grafo* g)
{
	printf("Testando colorir grafo\n");

	colorir_grafo(g);
	for (Vertice* v: g -> atributos) {
		printf("Vertice %d com cores", v -> g_numero());
		for (int i : v -> cor)
			printf(" %d", g -> encontrar_atributo(i) -> g_numero());
		printf("\n");
	}
	descolorir(g);

	colorir_grafo_mat(g);
	for (Vertice* v: g -> atributos) {
		printf("Vertice %d com cores", v -> g_numero());
		for (int i : v -> cor)
			printf(" %d", g -> encontrar_atributo(i) -> g_numero());
		printf("\n");
	}
	descolorir(g);

	colorir_grafo_pat(g);
	for (Vertice* v: g -> atributos) {
		printf("Vertice %d com cores", v -> g_numero());
		for (int i : v -> cor)
			printf(" %d", g -> encontrar_atributo(i) -> g_numero());
		printf("\n");
	}
	descolorir(g);

}

void testar_max_cores(Grafo* g)
{
	printf("Testando encontrar o maior numero de cores diferentes ate uma folha\n");
	colorir_grafo_pat(g);
	vector<int> max(g -> g_numero_vertices(), 0);

	printf("aqui\n");
	define_max_cores(g);
	int y = 0;
	for (Vertice* v: g -> atributos)
	{
		printf("Vertice %d(%d): Tem %d cores diferentes ate folha!\n", v -> g_id(), v -> g_numero(), v -> cores_ate_folha);
		max[y++] = v -> cores_ate_folha;
	}

	init_map(g);
	define_min_max_cores(g);

	for (Vertice* v: g -> atributos){
		if (v -> g_numero() == 1001)
			for (int i = 0; i < v -> min_cores.size(); i++)
				printf("Vertice %d tem (min: %d, max: (%d, %d)) cores diferentes até %d\n", v -> g_numero(), v -> min_cores[i], v -> max_cores[i],max[i] , g -> encontrar_atributo(i) -> g_numero());
	}

	descolorir(g);
}

void testar_encontra_juncoes(Grafo* g)
{
	printf("Testando encontrar juncoes\n");
	list<Juncao*> destino;
	encontra_juncoes(g, destino);

	printf("Numero de juncoes encontradas: %ld\n", destino.size());
}

void testar_arvore_dominadores(Grafo* g)
{
	printf("Testando encontrar dominadores no grafo\n");

	vector<Vertice*> dominadores;
	encontra_arvore_dominadores(g, dominadores);
	int i = 0;
	int w;
	for (Vertice* v: dominadores) {
		printf("%d, %d", g-> atributos[i] -> g_numero(), v -> g_numero());
		w = v -> g_id();
		while(w < g -> g_numero_vertices()) {
			Vertice* aux = dominadores[w];
			w = aux -> g_id();
			printf(" %d", aux -> g_numero());
		}
		printf("\n");

	}
	printf("Terminou!\n");
}

void testar_encontrar_subgrafos(Grafo* g)
{
	printf("Testando encontrar subgrafos\n");
	vector<Grafo*> subgrafos(g -> g_numero_vertices(), 0);

	encontra_subgrafos(g, subgrafos);

	for (Grafo* g1: subgrafos) {
		if (g1) {
			printf("Novo grafo com raiz %d e %d vertices criado!\n", g1 -> g_raiz() -> g_numero(), g1 -> g_numero_vertices());
			for (Vertice* v: g1 -> atributos)
				delete v;
			delete g1;
		}
	}
	printf("Terminou!\n");
}

void testar_profundidades(Grafo* g)
{

}
void testar_geracoes(Grafo* g)
{

}

void testar_encontrar_aneis(Grafo* g, int k)
{
	printf("Testando encontrar aneis com %d casamentos\n", k);
	list<Anel*> destino;
	encontra_aneis(g, destino, k);
	printf("Um exemplo de anel: \n");
	Anel* ex;
	if (destino.size() > 0) {
		ex = destino.front();
		for (Vertice* i: ex -> anel)
			printf("%d  ", i -> g_numero());
		printf("\n");
		ex = destino.back();
		for (Vertice* i: ex -> anel)
			printf("%d  ", i -> g_numero());
		printf("\n");
	}

	printf("Numero de aneis encontrados: %ld\n", destino.size());
}

void testar_encontrar_aneis_coloridos(Grafo* g, int k)
{
	printf("Testando encontrar aneis com %d casamentos\n", k);
	colorir_grafo_mat(g);
	list<Anel*> destino;
	encontra_aneis_coloridos(g, destino, k);
	printf("Um exemplo de anel: \n");
	Anel* ex;
	if (destino.size() > 0) {
		ex = destino.front();
		for (Vertice* i: ex -> anel)
			printf("%d  ", i -> g_numero());
		printf("\n");
		ex = destino.back();
		for (Vertice* i: ex -> anel)
			printf("%d  ", i -> g_numero());
		printf("\n");
	}

	printf("Numero de aneis encontrados: %ld\n", destino.size());
}

void m_escreve_grafo_graphviz(Grafo* g, bool colorir, string caminho)
{
	printf("Escrevendo grafo!\n");
	escreve_grafo_graphviz(g, colorir, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_arvore_graphviz(Grafo* g, string caminho)
{
	printf("Escreve arvore de busca!\n");
	int* arvore = new int[g -> g_numero_vertices()];
	busca_em_largura(g -> grafo, g -> g_numero_vertices(), arvore);
	escreve_arvore_graphviz(g, arvore, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_dominadores(Grafo* g, bool colorir, string caminho)
{
	printf("Escreve dominadores!\n");
	vector<Vertice*> dominadores;
	encontra_arvore_dominadores(g, dominadores);
	escreve_arvore_graphviz(g, dominadores, colorir, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_componentes_graphviz(Grafo* g, string caminho)
{
	printf("Escreve componentes!\n");
	list<list<int>> lista;
	busca_componentes_conexas(g -> grafo, g -> g_numero_vertices(), lista);
	escreve_componentes_graphviz(g, lista, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_cores(Grafo* g, string caminho)
{
	printf("Escreve cores!\n");
	escreve_cores(g, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_max_cores(Grafo* g, string caminho)
{
	printf("Escreve max cores!\n");
	escreve_max_cores(g, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_aneis(Grafo* g, int numero_casamentos, string caminho)
{
	printf("Escreve aneis caminho!\n");
	list<Anel*> aneis;
	encontra_aneis(g, aneis, numero_casamentos);

	escreve_aneis(aneis, g, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_aneis_completo(Grafo* g, int numero_casamentos, string caminho)
{
	printf("Escreve aneis!\n");
	list<Anel*> aneis;
	encontra_aneis(g, aneis, numero_casamentos);

	escreve_aneis_completo(aneis, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_aneis_coloridos_completo(Grafo* g, int numero_casamentos, string caminho)
{
	printf("Escreve aneis coloridos!\n");
	list<Anel*> aneis;
	encontra_aneis_coloridos(g, aneis, numero_casamentos);

	escreve_aneis_completo(aneis, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_comum_entre_grafos(Grafo* g, string caminho)
{
	printf("Escreve comum subgrafo!\n");
	vector<Grafo*> subgrafos(g -> g_numero_vertices(), 0);
	encontra_subgrafos(g, subgrafos);
	int y = 0;
	for (int i = 0; i < subgrafos.size(); i++)
		if (subgrafos[i])
			y++;
	vector<Grafo*> sub(y);
	y = 0;
	for (int i = 0, y = 0; i < subgrafos.size(); i++)
		if (subgrafos[i])
			sub[y++] = subgrafos[i];

	escreve_comum_entre_grafos(sub, caminho.c_str());
	printf("Terminou!\n");
}

void m_escreve_informacao_grafos(Grafo* g, string caminho)
{
	printf("Escreve informacoes subgrafo!\n");
	vector<Grafo*> subgrafos(g -> g_numero_vertices(), 0);
	encontra_subgrafos(g, subgrafos);
	int y = 0;
	for (int i = 0; i < subgrafos.size(); i++)
		if (subgrafos[i])
			y++;
	vector<Grafo*> sub(y);
	y = 0;
	for (int i = 0, y = 0; i < subgrafos.size(); i++)
		if (subgrafos[i])
			sub[y++] = subgrafos[i];

	escreve_informacao_grafos(g, sub, caminho.c_str());
	printf("Terminou!\n");
}
