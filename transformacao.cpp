#include "transformacao.h"

list<string> cores;

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
				switch(tamanho>6) {
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

Grafo* trabalha_arquivo(char* caminho)
{
	bool first = true;
	//Atributos para leitura de arquivo
	FILE* arquivo;
	char linha[MAX_COLUNA_ARQUIVO];
	arquivo = fopen(caminho, "rt");
	if (arquivo == NULL) return NULL;

	//Atributos de criacao de um grafo
	int numero_vertices = 0;
	int** grafo;
	list<Atributos_vertice*> atributos;
	Grafo* retorno = NULL;

	//Define o que sera feito na leitura de arquivo
	Estados estado = INICIO;

	//Atributos a serem utilizados
	bool esta_em_segunda_coluna = false;
	bool esta_em_terceira_coluna = false;
	char primeira_coluna[MAX_COLUNA_ARQUIVO];
	char segunda_coluna[MAX_COLUNA_ARQUIVO];
	int indice_primeira_coluna = 0;
	int indice_segunda_coluna = 0;
	int id_vertice = -1;
	int numero_vertice = -1;
	char tipo_vertice = ' ';
	Atributos_vertice* atributo;

	while (!feof(arquivo))
	{
		fgets(linha, MAX_COLUNA_ARQUIVO, arquivo);
		switch (estado) {
			case VERTICE:		//Formato:ID ID_GERAL TIPO
			{
				if (linha[1] == 'E') {estado = VERTICE_FIM; break;}
				numero_vertices++;

				//Reseta variaveis
				esta_em_segunda_coluna = false;
				esta_em_terceira_coluna = false;
				for (int i = 0; i < indice_segunda_coluna; i++)
					segunda_coluna[i] = ' ';
				indice_segunda_coluna = 0;

				//Interage com a linha
				for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
				{
					if (esta_em_terceira_coluna) {
						if (linha[i] == 'e') {tipo_vertice = 'e'; break;}
						else if (linha[i] == 't') {tipo_vertice = 't'; break;}
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
				atributo = new Atributos_vertice(id_vertice, numero_vertice, tipo_vertice);
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
				printf("Casamento entre pais e filhos: %d e %d\n", aux_1 - 1, aux_2 - 1);
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


	coloca_transicoes(grafo, numero_vertices, atributos);	//Para facilitar algoritmos depois
	retorno = new Grafo(numero_vertices, atributos, grafo);
	return retorno;
}

void coloca_transicoes(int** grafo, int tamanho, list<Atributos_vertice*> atributos) {
	int id;
	for (Atributos_vertice* v: atributos)
	{
		id = v -> id;
		for (Atributos_vertice* a: atributos)
		{
			int i = a -> id;
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
	int numero = g -> numero_vertices;

	bool continuar = true;
	//Percorre atributos do grafo e para cada um escreve no arquivo os atributos relacioados
	for (Atributos_vertice* atributos: g -> atributos)
	{
		continuar = true;
		if (!nao_desenhar.empty()) {
			int id = atributos -> id;
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
		lin += to_string(atributos -> id);	//Identificador do vertice

		//Comeco dos atributos do DOT e definicao do label do vertice
		lin += " [label = ";
		lin += to_string(atributos -> numero);

		//Continuacao dos atributos e definicao da forma do vertice
		lin += ", shape = ";
		if (atributos -> tipo == 'e') {
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

void escreve_componentes_sem_elementos_graphviz(Grafo* g, list<list<int>> componentes, char* caminho) {
	//Atributos para leitura de arquivo
		FILE* arquivo;
		string lin;
		arquivo = fopen(caminho, "w");

		//Verificacao de quais vertices nao desenhar
		list<int> nao_desenhar;
		for (int i = 0; i < g -> numero_vertices; i++)
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

void escreve_componentes_graphviz(Grafo* g, list<list<int>> componentes, char* caminho) {
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

void escreve_arvore_graphviz(Grafo* g, int* arvore, char* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int numero;
	int** grafo = g -> grafo;
	Atributos_vertice* atributos;

	//Escolha dos vertices que nao serao desenhados
	list<int> aux;
	list<int> nao_desenhar;
	for (int i = 0; i < g -> numero_vertices; i++) {
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
	for (int i = 0; i < g -> numero_vertices; i++)
	{
		//Se nao 'e raiz adiciona aresta
		if (arvore[i] != -1) {
			lin = "";
			lin += to_string(arvore[i]);	//Vertice do qual arco sai
			lin += " -> ";
			lin += to_string(i);	//Vertice em que arco chega
			lin += ";\n";
			fputs(lin.c_str(), arquivo);
			//Forma esperada: ID -> ID;\n
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n", arquivo);
	fclose(arquivo);
}

void escreve_grafo_graphviz(Grafo* g, bool colorir, char* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int** grafo = g -> grafo;
	Atributos_vertice* atributos;

	//Inicio do grafo e instanciacao de vertices
	list<int> nao_desenhar;
	fputs("digraph {\n", arquivo);
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	//Colore os vertices
	if (colorir) {
		Hash* map = new Hash();	//Hash que ira guardar as cores relacionadas com cada numero
		reinicia_cores();	//Reinicia as cores em list<Cor*> cores

		//Atributos para coloracao
		Cor* cor;
		Cor* aux;
		string rgb;

		//Percorre Vertices e escreve as cores
		for (Atributos_vertice* a: g -> atributos)
		{
			cor = NULL;
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

					//Inicia uma nova cor e a adiciona ao hash
					aux = new Cor(rgb);
					map -> adicionar_cor(cor_n, aux);
				}

				if (cor == NULL) {	//Se esta passando pela primeira vez copia a cor de aux
					cor = new Cor(aux);
				} else {	//Se ja tem cor definida realiza a soma da cor atual com a de aux
					cor -> soma(aux);
				}

			}

			if (cor == NULL) continue;	//Nao tem cor (a -> cor esta vazio)

			lin = "";
			lin += to_string(a -> id);
			lin += " [color = \"";
			lin += cor -> rgb;
			lin += "\", style = \"filled\"];\n";
			fputs(lin.c_str(), arquivo);
			//Forma esperada: ID [color = "#HEX_VALUE", style = "filled"];\n
			delete cor;
		}

		map->limpar();
		delete map;	//Realiza delete de todas as cores contidas em map
	}

	//Definicao de arcos e arestas
	for (int i = 0; i < g -> numero_vertices; i++)
	{
		for (int y = 0; y < g -> numero_vertices; y++)
		{
			if (grafo[i][y] == 1 && i < y)	{	//Representa aresta como um arco azul do menor para maior
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += "[color = blue]";
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID_MENOR -> ID_MAIOR [color = blue];\n
			} else if(grafo[i][y] == 2) {	//Representa um arco de i para y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> ID;\n
			} else if(grafo[i][y] == 12) {	//Representa um arco de i para y mas i e pai de y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += "[color = red]";
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> ID[color = red];\n
			}
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n",arquivo);
	fclose(arquivo);
}

void escreve_grafo_com_componentes_especiais(Grafo* g, list<list<int>> componentes, char* caminho) {
	//Atributos para leitura de arquivo
	FILE* arquivo;
	string lin;
	arquivo = fopen(caminho, "w");

	//Atributos p ler grafo
	int** grafo = g -> grafo;
	Atributos_vertice* atributos;

	//Inicio do grafo e instanciacao de vertices
	list<int> nao_desenhar;
	fputs("digraph {\n", arquivo);
	instancia_vertices_graphviz(g, arquivo, nao_desenhar);

	//Colore os vertices
	Hash* map = new Hash();	//Hash que ira guardar as cores relacionadas com cada numero
	reinicia_cores();	//Reinicia as cores em list<Cor*> cores

	//Atributos para coloracao
	Cor* cor;
	Cor* aux;
	string rgb;

	//Percorre Vertices e escreve as cores
	for (Atributos_vertice* a: g -> atributos)
	{
		cor = NULL;
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

				//Inicia uma nova cor e a adiciona ao hash
				aux = new Cor(rgb);
				map -> adicionar_cor(cor_n, aux);
			}

			if (cor == NULL) {	//Se esta passando pela primeira vez copia a cor de aux
				cor = new Cor(aux);
			} else {	//Se ja tem cor definida realiza a soma da cor atual com a de aux
				cor -> soma(aux);
			}
		}

		if (cor == NULL) continue;	//Nao tem cor (a -> cor esta vazio)

		lin = "";
		lin += to_string(a -> id);
		lin += " [color = \"";
		lin += cor -> rgb;
		lin += "\", style = \"filled\"];\n";
		fputs(lin.c_str(), arquivo);
		//Forma esperada: ID [color = "#HEX_VALUE", style = "filled"];\n
		delete cor;
	}

	map->limpar();
	delete map;	//Realiza delete de todas as cores contidas em map


	//Definicao de arcos e arestas
	for (int i = 0; i < g -> numero_vertices; i++)
	{
		for (int y = 0; y < g -> numero_vertices; y++)
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
				//Forma esperada: ID_MENOR -> ID_MAIOR [color = blue];\n
			} else if(grafo[i][y] == 2) {	//Representa um arco de i para y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> ID;\n
			} else if(grafo[i][y] == 12) {	//Representa um arco de i para y mas i e pai de y
				lin = "";
				lin += to_string(i);
				lin += "->";
				lin += to_string(y);
				lin += "[color = red]";
				lin += ";\n";
				fputs(lin.c_str(), arquivo);
				//Forma esperada: ID -> ID[color = red];\n
			}
		}
	}

	//Termina grafo e fecha arquivo
	fputs("}\n",arquivo);
	fclose(arquivo);
}

void escreve_cores(Grafo* g, char* caminho) {
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Atributos_vertice *a : g->atributos) {
		linha = "";
		linha+= "Numero: ";
		linha+= to_string(a -> numero);
		linha+= " Tipo: ";
		if (a -> tipo == 'e')
			linha+= "elipse   ";
		else
			linha+= "triangulo";
		for (int i : a->cor) {
			linha+= "| ";
			linha+= to_string(g -> encontrar_atributo(i) -> numero);
		}
		linha += "\n";
		fputs(linha.c_str(), arquivo);
	}

	fclose(arquivo);
}

void escreve_max_cores(Grafo* g, char* caminho) {
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Atributos_vertice *a : g->atributos) {
		linha = "";
		linha+= "Numero: ";
		linha+= to_string(a -> numero);
		linha+= " Tipo: ";
		if (a -> tipo == 'e')
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

Atributos_vertice* encontrar_casado(Anel* anel) {
	for (Atributos_vertice* i: anel -> anel) {
		for (Atributos_vertice* y: anel -> anel) {
			if (i -> id != y -> id) {
				for (Atributos_vertice* z: i -> casados) {
					if (y -> id == z -> id)
						return y;
				}
			}
		}
	}
	return NULL;
}

void escreve_aneis(list<Anel*> aneis, Grafo* g, char* caminho) {
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Anel* i: aneis) {
		linha = i -> linha_normal;
		fputs(linha.c_str(), arquivo);
	}
	fclose(arquivo);
}
void escreve_aneis_ordem(list<Anel*> aneis, Grafo* g, char* caminho){
	FILE* arquivo;
	arquivo = fopen(caminho, "w");
	string linha;

	for (Anel* i: aneis) {
		linha = i -> linha_ordem;
		fputs(linha.c_str(), arquivo);
	}
	fclose(arquivo);
}

void reinicia_cores() {
	cores.clear();
	cores.push_back("#0000FF");
	cores.push_back("#FF0000");
	cores.push_back("#00FF00");
	cores.push_back("#FFFF00");
	cores.push_back("#FF00FF");
	cores.push_back("#00FFFF");
	cores.push_back("#808080");
	cores.push_back("#4682B4");
	cores.push_back("#008080");
	cores.push_back("#808000");
	cores.push_back("#8B4513");
	cores.push_back("#DEB887");
	cores.push_back("#8B008B");
	cores.push_back("#CD5C5C");
	cores.push_back("#FF69B4");
	cores.push_back("#B22222");
	cores.push_back("#FF8C00");
	cores.push_back("#D8BFD8");
	cores.push_back("#EEE8AA");
}
