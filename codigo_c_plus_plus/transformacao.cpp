#include "transformacao.h"


int** cria_matriz(int tamanho)
{
	int ** a= new int*[tamanho];
	for (int i = 0; i < tamanho; i++)
		a[i] = new int[tamanho];

	int h;
	for (int i = 0; i < tamanho; i++) {
		for(int y = 0; y < tamanho; y++) {
			if (i == y) {
				a[i][y] = 0;
			}else{
				h = rand() % 10;
				switch(tamanho > 6) {
					case(true):
						if (h < 1) {
							a[y][i] = 1;
							a[i][y] = 1;
						} else {
							a[y][i] = 0;
							a[i][y] = 0;
						}
					break;
					case(false):
						if (h < 3) {
							a[y][i] = 1;
							a[i][y] = 1;
						} else {
							a[y][i] = 0;
							a[i][y] = 0;
						}
					break;
				}

			}
		}
	}

	return a;
}

//Transforma casamentos em vértices para P-Grafo
void adicionar_casamentos (Vertice* casamento, vector<Vertice*>& destino)
{
	casamento -> valor_bool = true;
	for (Vertice* c: casamento -> casados) {
		if (c -> valor_bool)
			continue;

		Vertice* p = casamento;
		Vertice* s = c;
		Par* par = new Par(p, s);

		int indice = destino.size();
		Vertice* novo = new Vertice(indice, indice, 'c');
		novo -> ponteiro = par;
		destino.push_back(novo);

		p -> adicionar_cor(indice);
		s -> adicionar_cor(indice);
	}

	for (Vertice* c: casamento -> casados)
		if (!c -> valor_bool)
			adicionar_casamentos(c, destino);
}

//Vertice::ponteiro = par;
Grafo* p_grafo(Grafo* g)
{
	//Cria os vértices,Vertice:ponteiro = ponteiro para vértices de g casados
	vector<Vertice*> atributos;
	Vertice* casamento_fic = new Vertice(-1, -1, 'f');
	for (Vertice* v: g -> atributos) {
		if (!v -> valor_bool) {
			if (v -> casados.size() > 0) {
				adicionar_casamentos(v, atributos);
			} else if (v -> filhos.size() > 0) {	//Tem filho mas não esta casado
				v -> adicionar_casamento(casamento_fic);
				casamento_fic -> valor_bool = false;
				adicionar_casamentos(v, atributos);
				v -> casados.pop_front();
			}
		}
	}

	//Atributos do p_grafo
	int numero_vertices = atributos.size();
	int** grafo = new int*[numero_vertices];
	for (int i = 0; i < numero_vertices; i++) {
		grafo[i] = new int[numero_vertices];
		for (int j = 0; j < numero_vertices; j++)
			grafo[i][j] = 0;
	}

	//Adiciona arcos
	for (Vertice* atual: atributos) {
		Vertice* p = ((Par *) atual -> ponteiro) -> fonte;
		Vertice* s = ((Par *) atual -> ponteiro) -> destino;

		if (p == casamento_fic || s == casamento_fic) {
			for (Vertice* filho: p -> filhos) {
				for (int i: filho -> cor) {
					atual -> adicionar_filho(atributos[i]);
					atributos[i] -> adicionar_pais(atual);

					grafo[atual -> g_id()][i] = 2;
					grafo[i][atual -> g_id()] = 3;
				}
			}

			continue;
		}

		for (Vertice* filho: p -> filhos) {
			if (contem(filho, s -> filhos)) {
				for (int i: filho -> cor) {
					atual -> adicionar_filho(atributos[i]);
					atributos[i] -> adicionar_pais(atual);

					grafo[atual -> g_id()][i] = 2;
					grafo[i][atual -> g_id()] = 3;
				}
			}
		}
	}

	Grafo *novo = new Grafo(numero_vertices, atributos, grafo);
	return novo;
}

void adicionar_alcancaveis (Vertice* fonte, vector<Vertice*>& destino)
{
	if (destino[fonte -> g_id()])
		return;

	destino[fonte -> g_id()] = fonte;
	for (Vertice* filho: fonte -> filhos) {
		adicionar_alcancaveis(filho, destino);
	}
}

Grafo* sub_grafo(Grafo* g, Vertice* fonte)
{
	Vertice* fonte_nova;

	//Marca os vertices que fonte consegue alcançar
	vector<Vertice*> alcancaveis(g -> g_numero_vertices(), 0);
	adicionar_alcancaveis(fonte, alcancaveis);

	//Calcula o numero de vertices
	int numero_vertices = 0;
	for (int i = 0; i < g -> g_numero_vertices(); i++)
		if (alcancaveis[i])
			numero_vertices++;

	//Cria as estruturas para novo grafo
	int** grafo = new int*[numero_vertices];
	for (int i = 0; i < numero_vertices; i++)
		grafo[i] = new int[numero_vertices];

	vector<Vertice*> atributos(numero_vertices);
	numero_vertices = 0;
	for (int i = 0; i < g -> g_numero_vertices(); i++) {
		if (alcancaveis[i]) {
			atributos[numero_vertices] = new Vertice(numero_vertices, alcancaveis[i] -> g_numero(), alcancaveis[i] -> g_tipo());
			atributos[numero_vertices] -> valor_int = alcancaveis[i] -> g_id();
			if (alcancaveis[i] == fonte)
				fonte_nova = atributos[numero_vertices];
			numero_vertices++;
		}
	}

	//Coloca informações
	int id, id_atrib;
	for (Vertice* v: atributos)
	{
		id = v -> valor_int;
		id_atrib = v -> g_id();
		for (Vertice* a: atributos)
		{
			int i = a -> valor_int;
			int i_atrib = a -> g_id();
			if (g -> grafo[id][i] == 0) {
				grafo[id_atrib][i_atrib] = 0;
			} else if (g -> grafo[id][i] == 1) {
				grafo[id_atrib][i_atrib] = 1;
				v -> adicionar_casamento(a);
			} else if (g -> grafo[id][i] == 12) {
				grafo[id_atrib][i_atrib] = 12;
				v -> adicionar_casamento(a);
				v -> adicionar_filho(a);
			} else if (g -> grafo[id][i] == 13) {
				grafo[id_atrib][i_atrib] = 13;
				v -> adicionar_casamento(a);
				v -> adicionar_pais(a);
			} else if (g -> grafo[id][i] == 2) {
				grafo[id_atrib][i_atrib] = 2;
				v -> adicionar_filho(a);
			} else {	//grafo[id][i] == 3
				grafo[id_atrib][i_atrib] = 3;
				v -> adicionar_pais(a);
			}
		}
	}

	//Cola as cores e ponteiros
	for (Vertice* v: atributos)
	{
		for (int cor: g -> atributos[v -> valor_int] -> cor)
			v -> adicionar_cor(cor);
		v -> ponteiro = g -> atributos[v -> valor_int] -> ponteiro;
	}

	Grafo *novo = new Grafo(numero_vertices, atributos, fonte_nova, grafo);
	if (g -> map)
		novo -> map = g -> map;

	return novo;
}

Grafo* trabalha_arquivo(char const* caminho)
{
	bool first = true;
	//Atributos para leitura de arquivo
	FILE* arquivo;
	char linha[MAX_COLUNA_ARQUIVO];
	arquivo = fopen(caminho, "rt");
	__asm__("label2:");
	if (arquivo == NULL) return NULL;

	//Atributos de criacao de um grafo
	int numero_vertices = 0;
	int** grafo;
	vector<Vertice*> atributos;
	Grafo* retorno = NULL;

	//Define o que sera feito na leitura de arquivo
	Estados estado = INICIO;

	//Atributos a serem utilizados
	bool esta_em_segunda_coluna = false;
	bool esta_em_terceira_coluna = false;
	bool esta_em_quarta_coluna = false;
	char primeira_coluna[MAX_COLUNA_ARQUIVO];
	char segunda_coluna[MAX_COLUNA_ARQUIVO];
	char terceira_coluna[MAX_COLUNA_ARQUIVO];
	int indice_primeira_coluna = 0;
	int indice_segunda_coluna = 0;
	int indice_terceira_coluna = 0;
	int id_vertice = -1;
	int numero_vertice = -1;
	char tipo_vertice = ' ';
	Vertice* atributo;

	while (!feof(arquivo))
	{
		//Aqui
		if (fgets(linha, MAX_COLUNA_ARQUIVO, arquivo) == NULL)
			continue;

		switch (estado) {
			case VERTICE:		//Formato:ID ID_GERAL TIPO
			{
				if (linha[1] == 'E') {estado = VERTICE_FIM; break;}
				numero_vertices++;

				//Reseta variaveis
				esta_em_segunda_coluna = false;
				esta_em_terceira_coluna = false;
				esta_em_quarta_coluna = false;
				for (int i = 0; i < indice_segunda_coluna; i++)
					segunda_coluna[i] = ' ';
				indice_segunda_coluna = 0;
				for (int i = 0; i < indice_terceira_coluna; i++)
					terceira_coluna[i] = ' ';
				indice_terceira_coluna = 0;

				//Interage com a linha
				for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
				{
					if (esta_em_quarta_coluna) {
						if (linha[i] == '\n') {break;}
						else if (linha[i] == ' ') {continue;}
						terceira_coluna[indice_terceira_coluna++] = linha[i];

					} else if (esta_em_terceira_coluna) {
						if (linha[i] == 'e') {
							tipo_vertice = 'e'; 
							i += 6;	//Para proxima indice representar " " ou "\n"
							esta_em_quarta_coluna = true;
							continue;
						} else if (linha[i] == 't') {
							tipo_vertice = 't';
							i += 7;	//Para proxima indice representar " " ou "\n"
							esta_em_quarta_coluna = true;
							continue;
						}
						printf("Erro ao ler arquivo, Vertices numero: %d\nLinha: %s", numero_vertices,linha);
						break;
					} else if (esta_em_segunda_coluna) {
						if (linha[i] == ' ') {esta_em_terceira_coluna = true; continue;}
						segunda_coluna[indice_segunda_coluna++] = linha[i];
					} else {
						if (linha[i] == ' ') {esta_em_segunda_coluna = true; continue;}
					}
				}

				//converte texto para numeros
				id_vertice = numero_vertices - 1;
				numero_vertice = atoi(segunda_coluna);
				atributo = new Vertice(id_vertice, numero_vertice, tipo_vertice);
				if (indice_terceira_coluna > 0) {
					int cor = atoi(terceira_coluna);
					atributo->adicionar_cor(cor);
				}
				atributos.push_back(atributo);
				break;
			}
			case VERTICE_FIM:
			{
				//Cria matriz de retorno
				grafo = new int*[numero_vertices];
				for (int i = 0; i < numero_vertices; i++)
					grafo[i] = new int[numero_vertices];
				for (int i = 0; i < numero_vertices; i++)
					for (int y = 0; y < numero_vertices; y++)
						grafo[i][y] = 0;

				//Define o proximo estado a ser iterado
				estado = ARESTA;
			} // @suppress("No break at end of case")	//Para entrar no proximo caso do break
			case ARESTA:	//Formato:ID ID
			{
				//Chegou na linha dos arcos
				if (linha[1] == 'A') {estado = ARCO; break;}

				//Reseta variaveis
				esta_em_segunda_coluna = false;
				for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
					primeira_coluna[i] = ' ';
				indice_primeira_coluna = 0;
				for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
					segunda_coluna[i] = ' ';
				indice_segunda_coluna = 0;

				//Interage com a linha
				for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
				{
					if (esta_em_segunda_coluna) {
						if (linha[i] == '\n') {break;}
						segunda_coluna[indice_segunda_coluna++] = linha[i];
					} else {
						if (linha[i] == ' ') {esta_em_segunda_coluna = true; continue;}
						primeira_coluna[indice_primeira_coluna++] = linha[i];
					}
				}

				//Define a linha e coluna da matriz que recebem a aresta
				int aux_1, aux_2;
				aux_1 = atoi(primeira_coluna);
				aux_2 = atoi(segunda_coluna);
				grafo[aux_1 - 1][aux_2 - 1] = 1;
				grafo[aux_2 - 1][aux_1 - 1] = 1;

				break;
			}
			case ARCO:	//Formato:ID_fonte ID_destino
			{
			//Reseta variaveis
			esta_em_segunda_coluna = false;
			for (int i = 0; i < indice_primeira_coluna; i++)
				primeira_coluna[i] = ' ';
			indice_primeira_coluna = 0;
			for (int i = 0; i < indice_segunda_coluna; i++)
				segunda_coluna[i] = ' ';
			indice_segunda_coluna = 0;

			//Interage com a linha
			for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
			{
				if (esta_em_segunda_coluna) {
					if (linha[i] == '\n') {break;}
					segunda_coluna[indice_segunda_coluna++] = linha[i];
				} else {
					if (linha[i] == ' ') {esta_em_segunda_coluna = true; continue;}
					primeira_coluna[indice_primeira_coluna++] = linha[i];
				}
			}

			//Define a linha e coluna da matriz que recebem o arco
			int aux_1, aux_2;
			aux_1 = atoi(primeira_coluna);
			aux_2 = atoi(segunda_coluna);
			if (grafo[aux_1 - 1][aux_2 - 1] == 1) {
				//printf("Casamento entre pais e filhos: %d e %d\n", aux_1 - 1, aux_2 - 1);
				grafo[aux_1 - 1][aux_2 - 1] = 12;
				grafo[aux_2 - 1][aux_1 - 1] = 13;
			} else {
				grafo[aux_1 - 1][aux_2 - 1] = 2;
				grafo[aux_2 - 1][aux_1 - 1] = 3;
			}
			break;
			}
			default:
				if (linha[1] == 'V') estado = VERTICE;
				break;
		}
	}

	fclose(arquivo);

	coloca_transicoes(grafo, atributos);	//Para facilitar algoritmos depois
	retorno = new Grafo(numero_vertices, atributos, grafo);
	return retorno;
}

void coloca_transicoes(int** grafo, vector<Vertice*> atributos) {
	int id;
	for (Vertice* v: atributos)
	{
		id = v -> g_id();
		for (Vertice* a: atributos)
		{
			int i = a -> g_id();
			if (grafo[id][i] == 0) {
				continue;
			} else if (grafo[id][i] == 1) {
				v -> adicionar_casamento(a);
			} else if (grafo[id][i] == 12) {
				v -> adicionar_casamento(a);
				v -> adicionar_filho(a);
			} else if (grafo[id][i] == 13) {
				v -> adicionar_casamento(a);
				v -> adicionar_pais(a);
			} else if (grafo[id][i] == 2) {
				v -> adicionar_filho(a);
			} else {	//grafo[id][i] == 3
				v -> adicionar_pais(a);
			}
		}
	}
}

void instancia_vertices_graphviz(Grafo* g, FILE* arquivo, list<int>& nao_desenhar) {
	//Atributos a serem utilizados
	string lin;
	int numero = g -> g_numero_vertices();

	bool continuar = true;
	//Percorre atributos do grafo e para cada um escreve no arquivo os atributos relacioados
	for (Vertice* atributos: g -> atributos)
	{
		if(!atributos)
			continue;
		continuar = true;
		if (!nao_desenhar.empty()) {
			int id = atributos -> g_id();
			for (int i: nao_desenhar)
			{
				if (i == id) {
					continuar = false;
					break;
				}
			}
		}
		if (!continuar) continue;
		lin = "";

		//Definicao do vertice
		lin += to_string(atributos -> g_id());	//Identificador do vertice

		//Comeco dos atributos do DOT e definicao do label do vertice
		lin += " [label = ";
		lin += to_string(atributos -> g_numero());

		//Continuacao dos atributos e definicao da forma do vertice
		lin += ", shape = ";
		if (atributos -> g_tipo() == 'e') {
			lin += "ellipse";
		} else {
			lin += "triangle";
		}

		//Fim dos atributos e insercao do vertice no arquivo
		lin += "];\n";
		fputs(lin.c_str(), arquivo);
		//Forma esperada: ID [label = NUMERO, forma = FORMA];\n
	}
}

void escreve_componentes_sem_elementos_graphviz(Grafo* g, list<list<int>> componentes, char const* caminho) {
	//Atributos para leitura de arquivo
		FILE* arquivo;
		string lin;
		arquivo = fopen(caminho, "w");

		//Verificacao de quais vertices nao desenhar
		list<int> nao_desenhar;
		for (int i = 0; i < g -> g_numero_vertices(); i++)
		{
			nao_desenhar.push_back(i);
		}
		for (list<int> lista: componentes)
		{
			for (int i: lista) {
				nao_desenhar.remove(i);
			}
		}

		//Inicio do grafo e Instanciacao de vertices
		fputs("graph {\n", arquivo);
		instancia_vertices_graphviz(g, arquivo, nao_desenhar);

		//Instancia componentes
		int aux;
		for (list<int> lista: componentes)
		{
			if (lista.size() <= 1) continue;
			lin = "";
			aux = lista.front();
			lista.pop_front();
			lin += to_string(aux);

			//Para cada elemento do componente adicionar uma aresta
			for (int i: lista)
			{
				lin += " -- ";
				lin += to_string(i);
			}

			//Fim do componente e insercao no arquivo
			lin += ";\n";
			fputs(lin.c_str(), arquivo);
			//Forma esperada: ID (-- ID)^NUMERO_DE_ELEMENTOS_COMPONENTE;\n
		}

		//Fechamento do grafo e do arquivo
		fputs("}", arquivo);
		fclose(arquivo);
}

void escreve_componentes_graphviz(Grafo* g, list<list<int>> componentes, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Verificacao de quais vertices nao desenhar
	list<int> nao_desenhar;
	for (list<int> lista: componentes)
	{
		if (lista.size() == 1) {
			int id = lista.front();
			nao_desenhar.push_back(id);
		}
	}

	//Inicio do grafo e Instanciacao de vertices
	fputs("graph {\n", arquivo);
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	//Instancia componentes
	int aux;
	for (list<int> lista: componentes)
	{
		if (lista.size() <= 1) continue;
		lin = "";
		aux = lista.front();
		lista.pop_front();
		lin += to_string(aux);

		//Para cada elemento do componente adicionar uma aresta
		for (int i: lista)
		{
			lin += " -- ";
			lin += to_string(i);
		}

		//Fim do componente e insercao no arquivo
		lin += ";\n";
		fputs(lin.c_str(), arquivo);
		//Forma esperada: ID (-- ID)^NUMERO_DE_ELEMENTOS_COMPONENTE;\n
	}

	//Fechamento do grafo e do arquivo
	fputs("}", arquivo);
	fclose(arquivo);
}

void escreve_arvore_graphviz(Grafo* g, int* arvore, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int numero;
	int** grafo = g -> grafo;
	Vertice* atributos;

	//Escolha dos vertices que nao serao desenhados
	list<int> aux;
	list<int> nao_desenhar;
	for (int i = 0; i < g -> g_numero_vertices(); i++) {
		if (arvore[i] != -1) {
			aux.push_back(arvore[i]);
		} else {
			nao_desenhar.push_back(i);
		}
	}
	for (int i: aux) {
		nao_desenhar.remove(i);
	}

	//Inicio do grafo e Instanciacao de vertices
	fputs("digraph {\n", arquivo);
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	//Instanciacao da arvore
	for (int i = 0; i < g -> g_numero_vertices(); i++)
	{
		//Se nao 'e raiz adiciona aresta
		if (arvore[i] != -1) {
			lin = "";
			lin += to_string(arvore[i]);	//Vertice do qual arco sai
			lin += " -> ";
			lin += to_string(i);	//Vertice em que arco chega
			lin += ";\n";
			fputs(lin.c_str(), arquivo);
			//Forma esperada: ID -> g_id();\n
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n", arquivo);
	fclose(arquivo);
}

void escreve_grafo_graphviz(Grafo* g, bool colorir, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int** grafo = g -> grafo;
	Vertice* atributos;

	//Inicio do grafo e instanciacao de vertices
	list<int> nao_desenhar;
	fputs("digraph {\n", arquivo);
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	//Colore os vertices
	if (colorir) {
		escreve_cores_graphviz(g, arquivo);
	}

	//Definicao de arcos e arestas
	for (int i = 0; i < g -> g_numero_vertices(); i++)
	{
		for (int y = 0; y < g -> g_numero_vertices(); y++)
		{
			if (grafo[i][y] == 1 && i < y)	{	//Representa aresta como um arco azul do menor para maior
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += "[color = blue]";
				lin += ";\nsubgraph{rank = same;";
				lin += to_string(i);
				lin+=";";
				lin += to_string(y);
				lin += "}\n";

				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID_MENOR -> g_id()_MAIOR [color = blue];\n
			} else if(grafo[i][y] == 2) {	//Representa um arco de i para y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> g_id();\n
			} else if(grafo[i][y] == 12) {	//Representa um arco de i para y mas i e pai de y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += "[color = red]";
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> g_id()[color = red];\n
			}
		}
	}

	if (g -> atributos[0] -> valor_int != -1) {
		for (Vertice* v: g -> atributos) {
			v -> valor_bool = false;
			printf("Valor valor_int: %d\n", v -> valor_int);
		}

		int i = 0;
		int atual = 0;
		while (i < g -> g_numero_vertices()) {
			if (g -> atributos.front() -> valor_int == -1)
				break;
			lin = "subgraph{ rank = same ";
			for (Vertice* v: g -> atributos) {
				if (v -> valor_int == atual) {
					i++;
					lin += ";";
					lin += to_string(v -> g_id());
				}
			}
			lin += "}\n";

			atual++;
			fputs(lin.c_str(), arquivo);
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n",arquivo);
	fclose(arquivo);
}

void escreve_p_grafo_graphviz(Grafo* g, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int** grafo = g -> grafo;
	Vertice* atributos;

	//Inicio do grafo e instanciacao de vertices
	fputs("digraph {\n", arquivo);
	//Percorre atributos do grafo e para cada um escreve no arquivo os atributos relacioados
	for (Vertice* atributos: g -> atributos)
	{
		Vertice* p = ((Par*) atributos -> ponteiro) -> fonte;
		Vertice* s = ((Par*) atributos -> ponteiro) -> destino;
		lin = "";

		//Definicao do vertice
		lin += to_string(atributos -> g_id());	//Identificador do vertice

		//Comeco dos atributos do DOT e definicao do label do vertice
		lin += " [label = \"";
		lin += to_string(p -> g_numero());
		lin += " & ";
		lin += to_string(s -> g_numero());
		lin += "\"";

		//Continuacao dos atributos e definicao da forma do vertice
		lin += ", shape = diamond];\n";
		fputs(lin.c_str(), arquivo);

		//Forma esperada: ID [label = NUMERO, forma = FORMA];\n
	}

	//Definicao de arcos e arestas
	for (int i = 0; i < g -> g_numero_vertices(); i++)
	{
		for (int y = 0; y < g -> g_numero_vertices(); y++)
		{
			if(grafo[i][y] == 2) {	//Representa um arco de i para y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> g_id();\n
			}
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n",arquivo);
	fclose(arquivo);
}

void escreve_arvore_p_grafo_graphviz(Grafo* g, vector<Vertice*> dominadores, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string lin;

	//Inicio do grafo e Instanciacao de vertices
	fputs("digraph {\n", arquivo);
	//Percorre atributos do grafo e para cada um escreve no arquivo os atributos relacioados
	for (Vertice* atributos: g -> atributos)
	{
		if (!atributos)
			continue;
		Vertice* p = ((Par*) atributos -> ponteiro) -> fonte;
		Vertice* s = ((Par*) atributos -> ponteiro) -> destino;
		lin = "";

		//Definicao do vertice
		lin += to_string(atributos -> g_id());	//Identificador do vertice

		//Comeco dos atributos do DOT e definicao do label do vertice
		lin += " [label = \"";
		lin += to_string(p -> g_numero());
		lin += " & ";
		lin += to_string(s -> g_numero());
		lin += "\"";

		//Continuacao dos atributos e definicao da forma do vertice
		lin += ", shape = diamond];\n";
		fputs(lin.c_str(), arquivo);

		//Forma esperada: ID [label = NUMERO, forma = FORMA];\n
	}

	/*
	lin = "";
	lin += to_string(raiz -> nodo -> g_id());	//Identificador do vertice
	lin += " [label = ";
	lin += to_string(raiz -> nodo -> g_numero());
	lin += ", shape = square];\n";
	fputs(lin.c_str(), arquivo);*/
	//Forma esperada: ID [label = NUMERO, forma = FORMA];\n

	int i = 0;
	for (Vertice* v: dominadores) {
		if (!v) {
			continue;
		}
		lin = "";
		lin += to_string(v -> g_id());
		lin += " -> ";
		lin += to_string(i);
		lin += ";\n";
		fputs(lin.c_str(), arquivo);
		i++;
		//Forma esperada: ID -> g_id();\n
	}

	//Termina grafo e fecha arquivo
	fputs("}\n", arquivo);
	fclose(arquivo);
}

void escreve_grafo_com_componentes_especiais(Grafo* g, list<list<int>> componentes, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int** grafo = g -> grafo;
	Vertice* atributos;

	//Inicio do grafo e instanciacao de vertices
	list<int> nao_desenhar;
	fputs("digraph {\n", arquivo);
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	//Colore os vertices
	escreve_cores_graphviz(g, arquivo);


	//Definicao de arcos e arestas
	for (int i = 0; i < g -> g_numero_vertices(); i++)
	{
		for (int y = 0; y < g -> g_numero_vertices(); y++)
		{
			if (grafo[i][y] == 1 && i < y)	{	//Representa aresta como um arco azul do menor para maior
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				bool mesmo_componente = false;
				bool zi = false;
				bool zy = false;
				for (list<int> l: componentes)
				{
					zi = false;
					zy = false;
					for (int x: l)
					{
						if (x == i) zi = true;
						else if(x == y) zy = true;
					}
					if (zi && zy) {
						mesmo_componente = true;
						break;
					}
				}

				if (mesmo_componente) {
					lin += "[color = green]";
				} else {
					lin += "[color = blue]";
				}
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID_MENOR -> g_id()_MAIOR [color = blue];\n
			} else if(grafo[i][y] == 2) {	//Representa um arco de i para y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> g_id();\n
			} else if(grafo[i][y] == 12) {	//Representa um arco de i para y mas i e pai de y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += "[color = red]";
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> g_id()[color = red];\n
			}
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n",arquivo);
	fclose(arquivo);
}

void escreve_cores_graphviz(Grafo* g, FILE* arquivo) {
	//Colore os vertices
	Map* map;
	if (g -> map) {
		map = g -> map;
		cout << "Mapa definido" << endl;
	} else {
		printf("Criando novo mapa para Grafo\n");
		map = new Map();	//Map que ira guardar as cores relacionadas com cada numero
		g -> map = map;
		reinicia_cores();	//Reinicia as cores em list<Cor*> cores

		cout << "Tam cores: " << cores.size() << endl;
	}

	//Atributos para coloracao
	Cor* cor;
	Cor* aux;
	string rgb;
	string lin;

	//Percorre Vertices e escreve as cores
	for (Vertice* a: g -> atributos)
	{
		printf("Cores(int): ");
		for (int i: a -> cor) {
			printf("%d ", i);
		}
		cor = map -> encontrar_cor(a -> cor);
		if (cor)
			printf("Encontrou cor");

		printf("\n");
		if (!cor) {	//Primeira ocorrencia do set
			//Para cada cor que coloriu o vertice
			for (int cor_n: a -> cor)
			{
				aux = map -> encontrar_cor(cor_n);	//Encontra cor
				//Se cor nao tiver sido encontrada ainda
				if (aux == NULL) {
					if (cores.empty()) //Se o numero de cores colocado na lista cores e muito pequeno
					{ printf("Erro: falta cores\n"); return;}
						//Pega a primeira cor
					rgb = cores.front();
					cores.pop_front();

					//Inicia uma nova cor e a adiciona ao map
					aux = new Cor(rgb);
					map -> adicionar_cor(cor_n, aux);
				}

				if (cor == NULL) {	//Se esta passando pela primeira vez copia a cor de aux
					cor = new Cor(aux);
				} else {	//Se ja tem cor definida realiza a soma da cor atual com a de aux
					cor -> soma(aux);
				}
			}
			if (!cor)	//Vertice n tem cor
				continue;
			map -> adicionar_cor(a -> cor, cor);
		}
		printf("Cor: %s \n", cor -> g_rgb().c_str());

		lin = "";
		lin += to_string(a -> g_id());
		lin += " [color = \"";
		lin += cor -> g_rgb();
		lin += "\", style = \"filled\"];\n";
		fputs(lin.c_str(), arquivo);
		//Forma esperada: ID [color = "#HEX_VALUE", style = "filled"];\n
	}
}

void escreve_cores(Grafo* g, char const* caminho) {
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Vertice *a : g->atributos) {
		linha = "";
		linha+= "Numero: ";
		linha+= to_string(a -> g_numero());
		linha+= " Tipo: ";
		if (a -> g_tipo() == 'e')
			linha+= "elipse   ";
		else
			linha+= "triangulo";
		for (int i : a->cor) {
			linha+= "| ";
			linha+= to_string(g -> encontrar_atributo(i) -> g_numero());
		}
		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

void escreve_max_cores(Grafo* g, char const* caminho) {
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Vertice *a : g->atributos) {
		linha = "";
		linha+= "Numero: ";
		linha+= to_string(a -> g_numero());
		linha+= " Tipo: ";
		if (a -> g_tipo() == 'e')
			linha+= "elipse   ";
		else
			linha+= "triangulo";
		linha+= " Maximo de Cores: ";
		linha+= to_string(a -> cores_ate_folha);
		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

Vertice* encontrar_casado(Anel* anel) {
	for (Vertice* i: anel -> anel) {
		for (Vertice* y: anel -> anel) {
			if (i -> g_id() != y -> g_id()) {
				for (Vertice* z: i -> casados) {
					if (y -> g_id() == z -> g_id())
						return y;
				}
			}
		}
	}
	return NULL;
}

void escreve_juncoes(list<Anel_aux*> aneis, Grafo* g, char const* caminho)
{
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	linha = "Ego, Alter, Percurso, Parente\n";
	fputs(linha.c_str(), arquivo);

	for (Anel_aux* anel: aneis) {
		linha = to_string(anel -> primeiro -> g_numero());	//Ego
		linha += ", ";
		linha += to_string(anel -> segundo -> g_numero());	//Alter
		linha += ", ";

		for (int i = 0; i < anel -> juncoes.size(); i++) {
			for (int j = 0; j < anel -> caminhos_primeiro[i].size(); j++) {
				if (anel -> caminhos_primeiro[i][j].size() == 0 || anel -> caminhos_segundo[i][j].size() == 0)
					continue;
				string percurso = "";
				string parente = "";
				for (Vertice* v: anel -> caminhos_primeiro[i][j]) {
					percurso = to_string(v -> g_numero()) + " " + percurso;
					if (v -> g_tipo() == 'e')
						parente = "M" + parente;
					else
						parente = "F" + parente;
				}

				percurso += " (" + to_string(anel -> juncoes[i] -> g_numero()) + ")";
				if (anel -> juncoes[i] -> g_tipo() == 'e')
					parente = "M" + parente;
				else
					parente = "F" + parente;

				for (Vertice* v: anel -> caminhos_segundo[i][j]) {
					percurso += " " + to_string(v -> g_numero());
					if (v -> g_tipo() == 'e')
						parente = "D" + parente;
					else
						parente = "S" + parente;
				}

				fputs((linha + percurso + ", " + parente + "\n").c_str(), arquivo);	
			}
		}
	}

	fclose(arquivo);	
}

void escreve_aneis(list<Anel*> aneis, Grafo* g, char const* caminho) {
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Anel* i: aneis) {
		linha = i -> linha_normal;
		fputs(linha.c_str(), arquivo);
	}
	fclose(arquivo);
}

void escreve_aneis_ordem(list<Anel*> aneis, Grafo* g, char const* caminho){
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Anel* i: aneis) {
		linha = i -> linha_ordem;
		fputs(linha.c_str(), arquivo);
	}
	fclose(arquivo);
}

void escreve_aneis_completo(list<Anel*> aneis, char const* caminho) {
	if (aneis.empty())
		return;
	int tam = aneis.front() -> casamentos.size();

	string linha = "Anel, ";
	for (int i = 0; i < tam; i++) {
		linha += "Ego";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "SxEgo";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "Alter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "SxAlter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	linha += "Percurso, BarryPercurso, Parente, ";
	for (int i = 0; i < tam; i++) {
		linha += "Casal";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	for (int i = 0; i < tam; i++) {
		linha += "Geração";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";

		linha += "Lateral";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	for (int i = 0; i < tam; i++) {
		linha += "Cnx";
		if (tam > 1)
			linha += to_string(i);
		if (i < tam - 1)
			linha += ", ";
	}
	linha += "\n";


	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	fputs(linha.c_str(), arquivo);
	int count = 0;
	for (Anel* a: aneis) {
		if (a -> anel.size() == 0)
			continue;
		count ++;
		linha = to_string(count);	//Anel
		linha += ", ";

		for (list<Vertice*> casamentos: a -> casamentos) {
			if (casamentos.front() -> g_tipo() == 't') {
				linha += to_string(casamentos.front() -> g_numero());	//EgoX
				linha += ", ";
				linha += "m";		//SxEgoX
				linha += ", ";
				linha += to_string(casamentos.back() -> g_numero());	//AlterX
				linha += ", ";
				linha += "f";		//SxAlterX
				linha += ", ";
			} else {
				linha += to_string(casamentos.back() -> g_numero());	//EgoX
				linha += ", ";
				linha += "m";		//SxEgoX
				linha += ", ";
				linha += to_string(casamentos.front() -> g_numero());	//AlterX
				linha += ", ";
				linha += "f";		//SxAlterX
				linha += ", ";
			}
		}

		//Percurso
		for (Vertice* v: a -> anel) {
			linha += to_string(v -> g_numero());
			linha += " ";
		}
		linha += ", ";

		//BaryryPercurso
		for (Vertice* v: a -> anel) {
			if (contem (v, a -> juncoes)) {
				linha += "(";
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += ") ";
			} else {
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += " ";

			}
		}
		linha += ", ";

		//Parente
		Vertice* ultimo = a -> anel.front();
		for (Vertice* v: a -> anel) {
			if (contem(v, ultimo -> filhos)) {
				if (v -> g_tipo() == 'e') {
					linha += "D";
				} else {
					linha += "S";
				}
			} else if (contem(v, ultimo -> pais)) {
				if (v -> g_tipo() == 'e') {
					linha += "M";
				} else {
					linha += "F";
				}
			} else if (contem(v, ultimo -> casados)) {
				if (v -> g_tipo() == 'e') {
					linha += "W";
				} else {
					linha += "H";
				}
			}
			ultimo = v;
		}

		//CasalX
		for (list<Vertice*> casamentos: a -> casamentos) {
			linha += ", ";
			linha += to_string(casamentos.front() -> g_numero());
			linha += " ";
			linha += to_string(casamentos.back() -> g_numero());
		}

		//Calculos de geracao,lateral e cnx
		list<int> cnx;
		list<int> geracao;
		vector<int> lateral;
		int lat_e = 0;
		int lat_d = 0;
		int num = 0;
		int num_cnx = -1;
		ultimo = a -> anel.front();
		for (Vertice* v: a -> anel) {
			num_cnx++;
			if (contem(v, ultimo -> filhos)) {
				num--;
				lat_d++;
			} else if (contem(v, ultimo -> pais)) {
				num++;
				lat_e++;
			} else if (contem(v, ultimo -> casados)) {
				if (lat_d > lat_e)
					lateral.push_back(lat_e);
				else
					lateral.push_back(lat_d);
				cnx.push_back(num_cnx);
				geracao.push_back(num);
				num = 0;
				lat_e = 0;
				lat_d = 0;
				num_cnx = 0;
			}
			ultimo = v;
		}
		geracao.push_back(num);
		cnx.push_back(num_cnx);
		if (lat_d > lat_e)
			lateral.push_back(lat_e);
		else
			lateral.push_back(lat_d);

		int i_=0;

		//Geracao e Lateral
		for (int i: geracao) {
			linha += ", ";
			linha += "G";
			linha += to_string(i);
			linha += ", ";
			linha += to_string(lateral[i_]);

			i_++;
		}

		//Cnx
		for (int i: cnx) {
			linha += ", ";
			linha += to_string(i);

		}

		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

void escreve_aneis_alternativo(list<Anel*> aneis, char const* caminho) {
	if (aneis.empty())
		return;
	int tam = aneis.front() -> casamentos.size();

	string linha = "Anel, ";
	for (int i = 0; i < tam; i++) {
		linha += "Ego";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "SxEgo";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "Alter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "SxAlter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}

	linha += "Barry_Percurso, ";

	for (int i = 0; i < tam; i++) {
		linha += "Percurso_";
		linha += to_string(i);
		linha += ", ";
	}
	for (int i = 0; i < tam; i++) {
		linha += "Parente_";
		linha += to_string(i);
		linha += ", ";
	}
	linha += "\n";


	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	fputs(linha.c_str(), arquivo);
	int count = 0;
	for (Anel* a: aneis) {
		if (a -> anel.size() == 0)
			continue;
		count ++;
		linha = to_string(count);	//Anel
		linha += ", ";

		for (list<Vertice*> casamentos: a -> casamentos) {
			if (casamentos.front() -> g_tipo() == 't') {
				linha += to_string(casamentos.front() -> g_numero());	//EgoX
				linha += ", ";
				linha += "m";		//SxEgoX
				linha += ", ";
				linha += to_string(casamentos.back() -> g_numero());	//AlterX
				linha += ", ";
				linha += "f";		//SxAlterX
				linha += ", ";
			} else {
				linha += to_string(casamentos.back() -> g_numero());	//EgoX
				linha += ", ";
				linha += "m";		//SxEgoX
				linha += ", ";
				linha += to_string(casamentos.front() -> g_numero());	//AlterX
				linha += ", ";
				linha += "f";		//SxAlterX
				linha += ", ";
			}
		}

		//BaryryPercurso
		for (Vertice* v: a -> anel) {
			if (contem (v, a -> juncoes)) {
				linha += "(";
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += ") ";
			} else {
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += " ";

			}
		}
		linha += ", ";

		//Percurso
		Vertice* ultimo = a -> anel.front();
		for (Vertice* v: a -> anel) {
			if (contem(v, ultimo -> casados)) {
				linha += ", ";
				linha += to_string(v -> g_numero());
				linha += " ";
			} else {
				linha += to_string(v -> g_numero());
				linha += " ";
			}
			ultimo = v;
		}
		linha += ", ";

		//Parente
		ultimo = a -> anel.front();
		for (Vertice* v: a -> anel) {
			if (contem(v, ultimo -> filhos)) {
				if (v -> g_tipo() == 'e') {
					linha += "D";
				} else {
					linha += "S";
				}
			} else if (contem(v, ultimo -> pais)) {
				if (v -> g_tipo() == 'e') {
					linha += "M";
				} else {
					linha += "F";
				}
			} else if (contem(v, ultimo -> casados)) {
				linha += ", ";
				if (v -> g_tipo() == 'e') {
					linha += "W";
				} else {
					linha += "H";
				}
			}
			ultimo = v;
		}

		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

list<Vertice*> encontra_caminho(Vertice* v, list<list<Vertice*>> l) {
	for (list<Vertice*> li: l)
		for (Vertice* vi: li)
			if (vi == v)
				return li;

	return list<Vertice*>();
}

bool contem (Vertice* v, Vertice* u, list<list<Vertice*>> lista) {
	for (list<Vertice*> l: lista) {
		if (l.front() == v) {
			if (l.back() == u)
				return true;
		} else if (l.front() == u)
			if (l.back() == v)
				return true;
	}

	return false;
}

void escreve_aneis_coloridos(Grafo* g, list<Anel*> aneis, char const* caminho)
{
	if (aneis.empty() || !g -> map)
		return;

	Map* map = g -> map;
	int tam = aneis.front() -> casamentos.size();

	string linha = "Anel, ";
	for (int i = 0; i < tam; i++) {
		linha += "Ego";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "Alter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	linha += "BarryPercurso, PercursoColorido, ";
	linha += ", Numero de Cores, Cores";
	linha += "\n";


	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	fputs(linha.c_str(), arquivo);
	int count = 0;
	for (Anel* a: aneis) {
		count ++;
		linha = to_string(count);	//Anel
		linha += ", ";

		//Ego e Alter
		Vertice* u = a -> anel.back();
		int id = 0;
		for (Vertice* v: a -> anel) {
			if (contem(v, u, a -> casamentos)) {
				linha += to_string(v -> g_numero());	//EgoX
				linha += ", ";
				linha += to_string(u -> g_numero());	//AlterX
				linha+= ", ";
				id++;
			}
			u = v;
		}

		//BaryryPercurso
		Vertice* prev = a -> anel.front();
		for (Vertice* v: a -> anel) {
			for (list<Vertice*> l: a -> casamentos)
				if ((l.front() == prev && l.back() == v) || (l.front() == v && l.back() == prev)) {
					linha += ". ";
					break;
				}

			if (contem (v, a -> juncoes)) {
				linha += "(";
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += ") ";
			} else {
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += " ";
			}
		}
		linha += ", ";

		//PercursoColorido
		for (Vertice* v: a -> anel) {
			bool jun = contem (v, a -> juncoes);
			if (jun)
				linha += "(";
			linha += to_string(v -> g_numero());
			linha+= "[ ";
			for (int i : v -> cor) {	//Cor
				Vertice * atual_cor = g -> encontrar_atributo(i);
				linha += to_string(atual_cor -> g_numero());
				linha += " ";
				if (atual_cor -> g_id() == -1)
					delete atual_cor;
			}
			//linha += to_string(map -> encontrar_indice_cor(v -> cor));
			if (jun)
				linha += "]) ";
			else
				linha += "] ";
		}

		//Numero de Cores
		set<int> cores;
		for (Vertice* v: a -> anel) {
			int i = map -> encontrar_indice_cor(v -> cor);
			if (i == -1)
				throw runtime_error("Cor invalida!");
			cores.insert(i);
		}
		linha += ", ";
		linha += to_string(cores.size());
		linha += ", ";

		//Cores
		for (int i: cores) {
			linha += "(";
			for (int j: map -> encontrar_numeros(i)) {
				Vertice * atual_cor = g -> encontrar_atributo(j);
				linha += to_string(atual_cor -> g_numero());
				if (atual_cor -> g_id() == -1)
					delete atual_cor;
			}
			linha += ") ";
		}

		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

void escreve_aneis_coloridos_completo(Grafo* g, list<Anel*> aneis, char const* caminho)
{
	if (aneis.empty() || !g -> map)
		return;

	Map* map = g -> map;
	int tam = aneis.front() -> casamentos.size();

	string linha = "Anel, ";
	for (int i = 0; i < tam; i++) {
		linha += "Ego";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "SxEgo";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "CorEgo";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "Alter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "SxAlter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
		linha += "CorAlter";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	linha += "Percurso, BarryPercurso,PercursoColorido, Parente, ";
	for (int i = 0; i < tam; i++) {
		linha += "Casal";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	for (int i = 0; i < tam; i++) {
		linha += "Geração";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";

		linha += "Lateral";
		if (tam > 1)
			linha += to_string(i);
		linha += ", ";
	}
	for (int i = 0; i < tam; i++) {
		linha += "Cnx";
		if (tam > 1)
			linha += to_string(i);
		if (i < tam - 1)
			linha += ", ";
	}
	linha += ", Numero de Cores, Cores";

	if (tam > 1) {
		for (int i = 0; i < tam; i++) {
			linha += ", Parente";
			linha += to_string(i);
		}

	}
	linha += "\n";


	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	fputs(linha.c_str(), arquivo);
	int count = 0;
	for (Anel* a: aneis) {
		count ++;
		linha = to_string(count);	//Anel
		linha += ", ";

		//Ego e Alter
		Vertice* u = a -> anel.back();
		int id = 0;
		for (Vertice* v: a -> anel) {
			if (contem(v, u, a -> casamentos)) {
				linha += to_string(v -> g_numero());	//EgoX
				linha+= ", ";
				linha += v -> g_tipo() == 't' ? "m" : "f";		//SxEgoX
				linha += ", ";
				for (int i : v -> cor) {	//EgoCor
					linha += to_string(i);
					linha += " ";
				}
				//linha += to_string(map -> encontrar_indice_cor(v -> cor));	//EgoCor
				linha += ", ";
				linha += to_string(u -> g_numero());	//AlterX
				linha+= ", ";
				linha += u -> g_tipo() == 't' ? "m" : "f";			//SxAlterX
				linha += ", ";
				for (int i : u -> cor) {	//AlterCor
					linha += to_string(i);
					linha += " ";
				}
				//linha += to_string(map -> encontrar_indice_cor(u -> cor));	//AlterCor
				linha += ", ";
				id++;
			}
			u = v;
		}

		//Percurso
		for (Vertice* v: a -> anel) {
			linha += to_string(v -> g_numero());
			linha += " ";
		}
		linha += ", ";

		//BaryryPercurso
		for (Vertice* v: a -> anel) {
			if (contem (v, a -> juncoes)) {
				linha += "(";
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += ") ";
			} else {
				if (v -> g_tipo() == 't')
					linha += "m";
				else
					linha += "f";
				linha += to_string(v -> g_numero());
				linha += " ";
			}
		}
		linha += ", ";

		//PercursoColorido
		for (Vertice* v: a -> anel) {
			bool jun = contem (v, a -> juncoes);
			if (jun)
				linha += "(";
			linha += to_string(v -> g_numero());
			linha+= "- ";
			for (int i : v -> cor) {	//Cor
				linha += to_string(i);
				linha += " ";
			}
			//linha += to_string(map -> encontrar_indice_cor(v -> cor));
			if (jun)
				linha += ") ";
			else
				linha += " ";
		}
		linha += ", ";

		//Parente
		Vertice* ultimo = a -> anel.front();
		for (Vertice* v: a -> anel) {
			if (contem(v, ultimo, a -> casamentos)) {
				if (v -> g_tipo() == 'e') {
					linha += "W";
				} else {
					linha += "H";
				}
			} else if (contem(v, ultimo -> filhos)) {
				if (v -> g_tipo() == 'e') {
					linha += "D";
				} else {
					linha += "S";
				}
			} else if (contem(v, ultimo -> pais)) {
				if (v -> g_tipo() == 'e') {
					linha += "M";
				} else {
					linha += "F";
				}
			}
			ultimo = v;
		}

		//CasalX
		for (list<Vertice*> casamentos: a -> casamentos) {
			linha += ", ";
			linha += to_string(casamentos.front() -> g_numero());
			linha+= "-";
			linha += to_string(map -> encontrar_indice_cor(casamentos.front() -> cor));
			linha += " ";
			linha += to_string(casamentos.back() -> g_numero());
			linha+= "-";
			linha += to_string(map -> encontrar_indice_cor(casamentos.back() -> cor));
		}
		//Calculos de geracao, lateral e cnx
		list<Vertice*> atuais(a -> anel);
		list<int> cnx;
		list<int> geracao;
		vector<int> lateral;
		int lat_e = 0;
		int lat_d = 0;
		int num = 0;
		int num_cnx = 0;

		vector<Vertice*> vetor;
		for (Vertice* v: a -> anel)
			vetor.push_back(v);

		bool primeiro = true;
		int i = 0;
		for (Vertice* att: a -> juncoes) {
			list<Vertice*> caminho = encontra_caminho(att, a -> caminhos);
			if (caminho.size() == 0)
				throw runtime_error("Caminho nao encontrado");

			bool primeiro = true;
			for (Vertice* v: caminho) {
				if (primeiro) {
					if (contem(v, a -> juncoes)) {
						primeiro = false;
						continue;
					}
					num++;
					num_cnx++;
					lat_e++;
				} else {
					num--;
					num_cnx++;
					lat_d++;
				}
			}
			if (lat_d > lat_e)
				lateral.push_back(lat_e);
			else
				lateral.push_back(lat_d);
			cnx.push_back(num_cnx);
			geracao.push_back(num);
			num = 0;
			lat_e = 0;
			lat_d = 0;
			num_cnx = 0;
		}

		int i_ = 0;
		//Geracao e Lateral
		for (int i: geracao) {
			linha += ", ";
			linha += "G";
			linha += to_string(i);
			linha += ", ";
			linha += to_string(lateral[i_]);

			i_++;
		}

		//Cnx
		for (int i: cnx) {
			linha += ", ";
			linha += to_string(i);

		}

		//Numero de Cores
		set<int> cores;
		for (Vertice* v: a -> anel) {
			int i = map -> encontrar_indice_cor(v -> cor);
			if (i == -1)
				throw runtime_error("Cor invalida!");
			cores.insert(i);
		}
		linha += ", ";
		linha += to_string(cores.size());
		linha += ", ";

		//Cores
		for (int i: cores) {
			linha += "( ";
			for (int j: map -> encontrar_numeros(i)) {
				linha += to_string(j);
				linha += " ";
			}
			linha += ") ";
		}

		if (tam > 1) {
			linha += ", ";
			//Parentes
			Vertice* ultimo = a -> anel.front();
			for (Vertice* v: a -> anel) {
				if (contem(v, ultimo, a -> casamentos)) {
					linha += ", ";
				} else if (contem(v, ultimo -> filhos)) {
					if (v -> g_tipo() == 'e') {
						linha += "D";
					} else {
						linha += "S";
					}
				} else if (contem(v, ultimo -> pais)) {
					if (v -> g_tipo() == 'e') {
						linha += "M";
					} else {
						linha += "F";
					}
				}
				ultimo = v;
			}
		}

		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

void escreve_arvore_graphviz(Grafo* g, vector<Vertice*> dominadores, bool colorir, char const* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string lin;

	//Inicio do grafo e Instanciacao de vertices
	fputs("digraph {\n", arquivo);
	list<int> nao_desenhar;
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	/*
	lin = "";
	lin += to_string(raiz -> nodo -> g_id());	//Identificador do vertice
	lin += " [label = ";
	lin += to_string(raiz -> nodo -> g_numero());
	lin += ", shape = square];\n";
	fputs(lin.c_str(), arquivo);*/
	//Forma esperada: ID [label = NUMERO, forma = FORMA];\n

	int i = 0;
	for (Vertice* v: dominadores) {
		if (!v) {
			printf("here\n");
			continue;
		}
		lin = "";
		lin += to_string(v -> g_id());
		lin += " -> ";
		lin += to_string(i);
		lin += ";\n";
		fputs(lin.c_str(), arquivo);
		i++;
		printf("lin: %s\n", lin.c_str());
		//Forma esperada: ID -> g_id();\n
	}

	if (colorir)
		escreve_cores_graphviz(g, arquivo);

	//Termina grafo e fecha arquivo
	fputs("}\n", arquivo);
	fclose(arquivo);
}

void escreve_comum_entre_grafos(vector<Grafo*> grafos, char const* caminho)
{
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string lin = "Subgrafo de A, Subgrafo de B, Comuns, Tem em A, Tem em B\n";
	string tem_a = "";
	fputs(lin.c_str(), arquivo);

	for (int i = 0; i < grafos.size() - 1; i++) {
		for (int y = i + 1; y < grafos.size(); y++) {
			for (Vertice* v: grafos[y] -> atributos)
				v -> valor_bool = true;

			if (grafos[i] -> g_raiz() -> g_tipo() == 'r' || grafos[y] -> g_raiz() -> g_tipo() == 'r')
				continue;

			//Sub A
			lin = to_string(grafos[i] -> g_raiz() -> g_numero());
			lin += ", ";

			//Sub B
			lin += to_string(grafos[y] -> g_raiz() -> g_numero());
			lin += ", ";

			//Comuns
			lin += "{ ";
			tem_a = "{ ";
			for (Vertice* i_: grafos[i] -> atributos) {
				bool encontrou = false;
				for (Vertice* y_: grafos[y] -> atributos) {
					if (i_ -> g_numero() == y_ -> g_numero()) {
						lin += to_string(i_ -> g_numero());
						lin += ", ";
						encontrou = true;
						y_ -> valor_bool = false;
						break;
					}
				}
				if (!encontrou) {
					tem_a += to_string(i_ -> g_numero());
					tem_a += ", ";
				}
			}
			lin += "}, ";
			tem_a += "}, ";

			//Tem em A
			lin += tem_a;

			//Tem em B
			lin += "{ ";
			for (Vertice* v: grafos[y] -> atributos)
				if (v -> valor_bool) {
					lin += to_string(v -> g_numero());
					lin += ", ";
				}
			lin += "}\n";
			fputs(lin.c_str(), arquivo);
		}
	}


	fclose(arquivo);
}

void escreve_informacao_grafos(Grafo* g, vector<Grafo*> grafos, char const* caminho)
{
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string lin = "Numero, Profundidade Geral, Profundidade Media(Sum(filhos.pm)/filhos), Profundidade Arvore Dominadores\n";
	fputs(lin.c_str(), arquivo);

	for (Vertice* v: g -> atributos) {
		lin = to_string(v -> g_numero());
		lin += ", ";

		lin += to_string(encontra_profundidade_de(v));
		lin += ", ";


		lin += to_string(encontra_profundidade_media_de(v));
		lin += ", ";

		bool encontrou = false;
		for (Grafo* g1: grafos) {
			if (g1 -> g_raiz() -> g_tipo() != 'r')
				if (g1 -> g_raiz() -> g_numero() == v -> g_numero()) {
					encontrou = true;
					vector<Vertice*> dominadores(g1 -> g_numero_vertices() + 1, 0);
					encontra_arvore_dominadores(g1, dominadores);

					lin += to_string(encontra_profundidade_dominadores(dominadores, g1 -> g_raiz()));
					lin += "\n";
					break;
				}
		}
		if (!encontrou)
			lin += "-1\n";

		fputs(lin.c_str(), arquivo);
	}
	fclose(arquivo);
}

void escreve_lista_cores(Grafo* g, char const* caminho)
{
	if (!g -> map)
		return;

	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string lin = "Numero, Cor\n";
	fputs(lin.c_str(), arquivo);

	for (Vertice* v: g -> atributos) {
		lin = to_string(v -> g_numero());
		lin += ", ";
		lin += to_string(g -> map -> encontrar_indice_cor(v -> cor));
		lin += "\n";
		fputs(lin.c_str(), arquivo);
	}
	fclose(arquivo);
}

void escreve_lista_vertices_formam_cores(Grafo* g, char const* caminho)
{
	if (!g -> map)
		return;

	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string lin = "Numero, primeiro_vertice_cor, segundo_vertice_cor, ...\n";
	fputs(lin.c_str(), arquivo);

	for (Vertice* v: g -> atributos) {
		lin = to_string(v -> g_numero());
		Vertice* cor = 0;
		for (int i: v -> cor) {
			cor = g -> encontrar_atributo(i);
			if (!cor) {
				throw runtime_error("Erro vertice nao encontrado");
			}

			lin += ", ";
			lin += to_string(cor -> g_numero());
		}
		lin += "\n";
		fputs(lin.c_str(), arquivo);
	}
	fclose(arquivo);
}

struct cmp {

	bool operator() (set<set<int>, set_cmp> esquerda, set<set<int>, set_cmp> direita)  {
		set<set<int>>::iterator it_esq = esquerda.begin();
		set<set<int>>::iterator it_dir = direita.begin();

		for (; it_esq != esquerda.end() && it_dir != direita.end(); it_esq++, it_dir++) {
			if (*it_esq == *it_dir)
				continue;
			else
				return false;
		}

		return esquerda.size() == direita.size();
	}
};

class Helper {
public:
	cmp comparador;
	vector<set<set<int>, set_cmp>> cores;
	vector<int> aparicoes;

	Helper(){}

	void adicionar(set<set<int>, set_cmp> novo) {
		for (int i = 0; i < cores.size(); i++) {
			set<set<int>, set_cmp> s = cores[i];
			if (comparador.operator()(novo, s)) {
				aparicoes[i]++;
				return;
			}
		}

		cores.push_back(novo);
		aparicoes.push_back(1);
	}
};

void escreve_numeros_aneis(Grafo * g, list<Anel*> aneis, char const* caminho)
{
	FILE* arquivo;
	arquivo = fopen(caminho, "w");

	int num_casamentos = aneis.front() ? aneis.front() -> casamentos.size() : -1;
	string lin = "Aneis A" + to_string(num_casamentos) + "C" + to_string(num_casamentos) + "\n";
	lin += "Número total de Aneis: ";
	lin += to_string(aneis.size());
	lin += "\n";

	//Número de aneis com X cores
	int num = 0;
	for (Anel* a: aneis)
		num = num < a->cores.size() ? a->cores.size() : num;
	vector<int> numero_aneis(num + 1, 0);
	for (Anel* a: aneis)
		numero_aneis[a->cores.size()]++;
	for (int i = 0; i < numero_aneis.size(); i++)
		lin += "Número de aneis com " + to_string(i) + " cores: " + to_string(numero_aneis[i]) + "\n";

	fputs(lin.c_str(), arquivo);

	//Cores no grafo
	lin = "\nCores no Grafo:\n";
	for (int i = 0; i < g -> map -> tam(); i++) {
		pair<Cor*, set<int>> par = (*(g -> map))[i];
		Cor * c = par.first;
		set<int> set = par.second;

		lin += c -> g_rgb();
		lin += " : ";
		for (int i : set) {
			Vertice * atual = g -> encontrar_atributo(i);
			lin += to_string(atual -> g_numero());
			lin += " ";
			if (atual -> g_numero() < 0)
				delete atual;
		}
		lin += "\n";
	}
	fputs(lin.c_str(), arquivo);

	//Aparencia das Cores
	lin = "\nNúmero de aparição das cores\n";
	vector<int> aparicoes(g -> g_numero_vertices() + 1, 0);
	for (Anel* a: aneis)
		for (set<int> set: a -> cores)
			for (int i: set)
				if (i >= 0)
					aparicoes[i]++;
				else
					aparicoes[g -> g_numero_vertices()]++;

	for (int i = 0; i < aparicoes.size(); i++)
		if (aparicoes[i] > 0) {
			Vertice * atual = g -> encontrar_atributo(i);
			lin += to_string(atual -> g_numero());
			lin += " : ";
			if (atual -> g_numero() < 0) {
				lin += to_string(aparicoes[g -> g_numero_vertices()]);
				delete atual;
			} else
				lin += to_string(aparicoes[i]);
			lin += "\n";
		}

	fputs(lin.c_str(), arquivo);


	//Aparencias em conjuntos
	num = 0;
	for (Anel* a: aneis)
		num = num < a->cores.size() ? a->cores.size() : num;
	num++;	//

	list<Anel*> aneis_ordenados[num];
	for (Anel* a: aneis)
		aneis_ordenados[a -> cores.size()].push_back(a);

	lin = "";
	for (int i = 0; i < num; i++) {
		lin += "\nNúmero de anéis com " + to_string(i) + " cores:" + to_string(aneis_ordenados[i].size()) + "\n";
		Helper * h = new Helper();
		for (Anel* a: aneis_ordenados[i]) {
			h -> adicionar(a -> cores);
		}

		for (int j = 0; j < h -> aparicoes.size(); j++) {
			lin += "Grupo: ";
			set<set<int>, set_cmp> s2 = h -> cores[j];
			int separador = 0;
			for (set<int> s1: s2) {
				for (int z: s1) {
					Vertice * atual = g -> encontrar_atributo(z);
					lin += to_string(atual -> g_numero()) + " ";
					if (atual -> g_numero() < 0) {
						delete atual;
					}
				}
				if (++separador < s2.size())
					lin += " | ";

			}

			lin += " , Anéis: " + to_string(h -> aparicoes[j]) + "\n";
		}


		delete h;
	}
	fputs(lin.c_str(), arquivo);



	fclose(arquivo);
}