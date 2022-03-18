#include "testes.h"

int main(int argc, char *argv[]) {
	executar_escience(argc, argv);
	cout << "Exit não funcionou, retornando" << endl;
	return 1;

	//Primeiro argumento = nome arquivo, segundo = numero de casamentos para testar aneis
	cout << "Oi, sou um programa em c++\n";
	string entrada = "";
	string destino = "";
	int k = 2;
	int num = 8;
	int grao = 40;
	int execucao = 0;	//0 = aneis, 1 = juncoes
	bool p = false;		//p = true para colorir grafo com max num cores e executar paralelo
	int algoritmo = 0;	//0 = A1P, 1 = A1LSC, 2 = A1LCC, 3 = A2P, 4 = A2L, 5 = A3
	int coloracao = 0;	//0 = Coloração do arquivo, 1 = Coloração MAterna, 2 = Coloração Paterna, 3 = Coloração Geral

	for (int i = 1; i < argc; i++) {
		cout << "argv[" << i << "]: " << argv[i] << endl;
	}

	if (argc == 1) {
		entrada = "./arquivos_prog/temp_0";
		execucao = 0;
		nome_rede = "";
		destino = "./aneis/teste.txt";
	} else if (argc == 5) { //	./programa.out nome_arquivo tipo_execução nome_Rede
		entrada = argv[1];
		execucao = atoi(argv[2]);
		nome_rede = string(argv[3]);
		destino = string(argv[4]);
	} else if (argc == 10) {//	./programa.out Nome_Rede.txt tipo_execucao numero_casamentos algoritmo max_threads grao escrever_cores nome_Rede
		entrada = argv[1];
		execucao = atoi(argv[2]);
		k = atoi(argv[3]);
		algoritmo = atoi(argv[4]);
		num = atoi(argv[5]);
		grao = atoi(argv[6]);
		if (atoi(argv[7]))
			p = true;
		nome_rede = string(argv[8]);
		destino = string(argv[9]);
	} else if (argc == 11) {//	./programa.out Nome_Rede.txt tipo_execucao numero_casamentos algoritmo max_threads grao escrever_cores nome_Rede coloração
		entrada = argv[1];
		execucao = atoi(argv[2]);
		k = atoi(argv[3]);
		algoritmo = atoi(argv[4]);
		num = atoi(argv[5]);
		grao = atoi(argv[6]);
		if (atoi(argv[7]))
			p = true;
		nome_rede = string(argv[8]);
		destino = string(argv[9]);
		coloracao = atoi(argv[10]);
	} else {
		cout << "Entrada com número de argumentos não previstos, retornando\n";
		return 1;
	}

	if (execucao == 0)
		cout << "Nome da Rede: " << nome_rede << " Num_Casamentos: " << k << " Algoritmo: " << algoritmo
		<< " Num Max Thread: " << num << " Grao: " << grao << " Tipo_Coloracao:" << coloracao << endl;
	else
		cout << "Nome da Rede: " << nome_rede << " Execução: " << execucao << endl;

	Grafo *g = trabalha_arquivo(entrada.c_str());
	int **grafo;
	if (g)
		grafo = g->grafo;
	else {
		cout << "Entrada errada, retornando\n";
		return 1;
	}

	switch (coloracao) {
		case (1): {
			descolorir(g);
			colorir_grafo_mat(g);
			break;
		}
		case (2): {
			descolorir(g);
			colorir_grafo_pat(g);
			break;
		}
		case (3): {
			descolorir(g);
			colorir_grafo(g);
			break;
		}
		default:
			break;
	}
		
	//Procura por anéis	= 0
	//escreve_juncoes = 1
	//Escreve informações grafo = default
	try{
	switch(execucao) {
		case (0):	//Procura por aneis
		{
			cout << "Procurando por aneis c++\n";
			//0 = A1P, 1 = A1LSC, 2 = A1LCC, 3 = A2P, 4 = A2L, 5 = A3	
			list<Anel*> aneis;
			switch(algoritmo) {
				case (1):
					com_cores = false;
					encontra_alcancaveis_dfs(g);
					encontra_aneis(g, aneis, k);
					com_cores = true;
					break;
				case (2):
					define_min_max_cores(g);
					//define_super_sob(g);
					encontra_aneis(g, aneis, k);
					break;
				case (3):
					define_min_max_cores(g);
					//define_super_sob(g);
					encontra_aneis_paralelos_vetor(g, aneis, k, num, grao);
					break;
				case (4):
					define_min_max_cores(g);
					//define_super_sob(g);
					encontra_aneis_coloridos(g, aneis, k, false);
					break;
				case (5):
					define_min_max_cores(g);
					//define_super_sob(g);
					encontra_aneis_coloridos_algo3_pool(g, aneis, k, num, grao);
					break;
				default:	//A1P
					define_min_max_cores(g);
					//define_super_sob(g);
					encontra_aneis_paralelos_procurando(g, aneis, k, num, grao);
			}

			cout << "Encontrou " << aneis.size() << "aneis\n";
			//Escreve os aneis encontrados
			if (p) {
				escreve_aneis_coloridos_completo(g, aneis, destino.c_str());
			} else {
				escreve_aneis_completo(aneis, destino.c_str());
			}
			break;
		}
		case (1):
		{	
			cout << "Procurando por juncoes c++" << endl;
			encontra_alcancaveis_dfs(g);
			list<Anel_aux*> juncoes;
			Juncoes* juncoesa = new Juncoes(g -> g_numero_vertices() + 1);
			encontra_juncoes(g, juncoesa);
			com_cores = false;

			for (Vertice* va: g -> atributos) {
				for (Vertice* vb: g -> atributos) {
					if (va != vb && va && vb) {
						Anel_aux* novo = new Anel_aux();
						juncoes.push_back(novo);
						JuncoesDe* par_juncao = juncoesa -> juncoes[va -> g_id()][vb -> g_id()];

						if (par_juncao)
							define_anel_aux(par_juncao, novo);
					}
				}
			}
			
			escreve_juncoes(juncoes, g, destino.c_str());
			com_cores = true;
			break;
		}
		default:
		{
			cout << "Default c++" << endl;
		}
	}
	} catch(...) {	return 2; }

	cout << "Programa C++ chegou ao fim :)\n";
	return 0;
}

void testar_encontra_aneis_paralelos(Grafo* g, int k)
{
	list<Anel*> destino;
	chrono::steady_clock::time_point init = chrono::steady_clock::now();
	encontra_aneis_coloridos(g, destino, k, true);
	chrono::steady_clock::time_point beg = chrono::steady_clock::now();
	cout << "Algoritmo 3 Paralelo, Tempo: " << chrono::duration_cast<chrono::milliseconds>(beg - init).count() * 0.001 << "s" << endl << endl;
}

void testar_encontra_aneis_semi_paralelos(Grafo* g, int k)
{
	list<Anel*> destino;
	chrono::steady_clock::time_point init = chrono::steady_clock::now();
	encontra_aneis_coloridos(g, destino, k, false);
	chrono::steady_clock::time_point beg = chrono::steady_clock::now();
	cout << "Algoritmo 2 Linear, Tempo: " << chrono::duration_cast<chrono::milliseconds>(beg - init).count() * 0.001 << "s" << endl << endl;
}

void testar_encontra_aneis_linear(Grafo* g, int k)
{
	list<Anel*> destino;
	chrono::steady_clock::time_point init = chrono::steady_clock::now();
	encontra_aneis(g, destino, k);
	chrono::steady_clock::time_point beg = chrono::steady_clock::now();
	cout << "Algoritmo 1 Linear Com cores, Tempo: " << chrono::duration_cast<chrono::milliseconds>(beg - init).count() * 0.001 << "s" << endl << endl;
}

void testar_encontra_aneis_linear_sem_cores(Grafo* g, int k)
{
	list<Anel*> destino;
	chrono::steady_clock::time_point init = chrono::steady_clock::now();
	com_cores = false;
	encontra_aneis(g, destino, k);
	com_cores = true;
	chrono::steady_clock::time_point beg = chrono::steady_clock::now();
	cout << "Algoritmo 1 Linear Sem Cores, Tempo: " << chrono::duration_cast<chrono::milliseconds>(beg - init).count() * 0.001 << "s" << endl << endl;
}

void testar_encontra_aneis_paralelos(Grafo* g, int k, int numero_threads, int grao)
{
	list<Anel*> destino;
	chrono::steady_clock::time_point init = chrono::steady_clock::now();
	encontra_aneis_paralelos_vetor(g, destino, k, numero_threads, grao);
	chrono::steady_clock::time_point beg = chrono::steady_clock::now();
	cout << "Algoritmo 2 Paralelo, Tempo: " << chrono::duration_cast<chrono::milliseconds>(beg - init).count() * 0.001 << "s" << endl << endl;
}

void testar_encontra_aneis_paralelos_1(Grafo* g, int k, int numero_threads, int grao)
{
	list<Anel*> destino;
	chrono::steady_clock::time_point init = chrono::steady_clock::now();
	encontra_aneis_paralelos_procurando(g, destino, k, numero_threads, grao);
	chrono::steady_clock::time_point beg = chrono::steady_clock::now();
	cout << "Algoritmo 1 Paralelo, Tempo: " << chrono::duration_cast<chrono::milliseconds>(beg - init).count() * 0.001 << "s" << endl << endl;
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
	vector<Vertice*> dominadores(g -> g_numero_vertices() + 1, 0);
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
	colorir_grafo(g);
	list<Anel*> aneis;
	encontra_aneis_coloridos(g, aneis, numero_casamentos);

	escreve_aneis_coloridos_completo(g, aneis, caminho.c_str());
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

void desabilitar_cout() {
	cout.setstate(ios_base::failbit);
}

void reabilitar_cout() {
	cout.clear();
}

void executar_funcao_escience(Grafo* g, int numero_casamentos, int num_threads, int grao, int num_execucoes, string nome_rede) {
	list<Anel*> destino;
	
	//Algo 3 sequencial
	double total = 0;
	double max = 0;
	double min = INT_MAX;
	for (int i = 0; i < num_execucoes; i++) {
		cout << "Execucao " << i + 1 << " procura anéis coloridos com algo 3 sequencial" << endl;
		desabilitar_cout();

		auto init = chrono::steady_clock::now();
		encontra_aneis_coloridos_algo3_sequencial(g, destino, numero_casamentos);
		auto end = chrono::steady_clock::now();

		reabilitar_cout();
		chrono::duration<double> diff = end - init;
		double tempo = diff.count();
		total += tempo;
		cout << "Tempo da execucao: " << tempo << endl;
		cout << "Número de anéis encontrados: " << get_num_aneis() << endl;
		clear_num_aneis();
		if (tempo > max) 
			max = tempo;
		if (tempo < min)
			min = tempo;
	}
	cout << "Tempo total execução anéis coloridos com algo 3 sequencial em " << num_execucoes << " execuções: " << total << 
		", Max: " << max << ", Min: " << min << ", Média: " << total / num_execucoes << endl << endl;

	//Algo 3 paralelo
	total = 0;
	max = 0;
	min = INT_MAX;
	for (int i = 0; i < num_execucoes; i++) {
		cout << "Execucao " << i + 1 << " procura anéis coloridos com algo 3 paralelo" << endl;
		desabilitar_cout();

		auto init = chrono::steady_clock::now();
		encontra_aneis_coloridos_algo3_pool(g, destino, numero_casamentos, num_threads, grao);
		auto end = chrono::steady_clock::now();

		reabilitar_cout();
		chrono::duration<double> diff = end - init;
		double tempo = diff.count();
		total += tempo;
		cout << "Tempo da execucao: " << tempo << endl;
		cout << "Número de anéis encontrados: " << get_num_aneis() << endl;
		clear_num_aneis();

		if (tempo > max) 
			max = tempo;
		if (tempo < min)
			min = tempo;
	}
	cout << "Tempo total execução anéis coloridos com algo 3 paralelo em " << num_execucoes << " execuções: " << total << 
		", Max: " << max << ", Min: " << min << ", Média: " << total / num_execucoes << endl;

	int numero_cores = g -> map ? g -> map -> tam() : 0 ;
	cout << "Numero de cores no grafo:" << numero_cores << endl;


	if (numero_casamentos == 1) {
		desabilitar_cout();
		encontra_aneis_coloridos_algo3_pool_FIX_EXCLUIR(g, destino, numero_casamentos, num_threads, grao);
		reabilitar_cout();

		list<Anel*> aneis;
		encontra_aneis_NOME_A_DEFINIR(destino, aneis, 2);
		cout << "Numero aneis: " << destino.size() << endl;
		cout << "Numero aneis com 2 cores divididas pelas juncoes: " << aneis.size() << endl;

		string caminho = "escience/1_" + nome_rede;
		escreve_numeros_aneis(g, destino, caminho.c_str());
	} else if (numero_casamentos == 2) {
		desabilitar_cout();
		encontra_aneis_coloridos_algo3_pool_FIX_EXCLUIR(g, destino, numero_casamentos, num_threads, grao);
		reabilitar_cout();

		list<Anel*> aneis;
		encontra_aneis_NOME_A_DEFINIR(destino, aneis, 4);
		cout << "Numero aneis: " << destino.size() << endl;
		cout << "Numero aneis com 4 cores divididas pelas juncoes: " << aneis.size() << endl;		
		
		string caminho = "escience/2_" + nome_rede;
		escreve_numeros_aneis(g, destino, caminho.c_str());
	}

	cout << "*************************FIM EXECUCAO: " << nome_rede << ", " << numero_casamentos << " *************************" << endl;
}

void executar_escience(int argc, char *argv[]) {
	cout << "Execução E-Science" << endl;
	string nome_rede;
	int numero_casamentos;
	int num_threads;
	int grao;
	int num_execucoes;
	int tipo_coloracao;
	Grafo * g;
	if (argc == 7) { //	./programa.out nome_arquivo numero_casamentos num_threads grao num_execucoes tipo_coloracao
		nome_rede = string(argv[1]);
		numero_casamentos = atoi(argv[2]);
		num_threads = atoi(argv[3]);
		grao = atoi(argv[4]);
		num_execucoes = atoi(argv[5]);
		tipo_coloracao = atoi(argv[6]);
	} else {
		for (int i = 1; i < argc; i++) {
			cout << "argv[" << i << "]: " << argv[i] << endl;
		}
		cout << "Informações não foram fornecidas, saindo..." << endl;
		exit(1);
	}

	g = trabalha_arquivo(nome_rede.c_str());
	int **grafo;
	if (g)
		grafo = g->grafo;
	else {
		cout << "Entrada errada, retornando\n";
		exit(1);
	}

	if (tipo_coloracao == 0)
		colorir_grafo(g);
	else if (tipo_coloracao == 1)
		colorir_grafo_pat(g);
	else
		colorir_grafo_mat(g);

	define_min_max_cores(g);
	//define_super_sob(g);

	executar_funcao_escience(g, numero_casamentos, num_threads, grao, num_execucoes, nome_rede);
	exit(0);
}

//T utiliza size, front e pop_Front
template<typename T>
void clear(T& estrutura) {
	while(estrutura.size() > 0) {
		auto elemento = estrutura.front();
		estrutura.pop_front();

		delete elemento;
	}
}