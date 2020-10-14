#include "teste.h"
void testar_busca_largura(int** grafo, int tamanho)
{
	printf("\nTestando busca em largura: \n");
	int* arvore = new int[tamanho];
	int num_raiz = 0;
	busca_em_largura(grafo, tamanho, arvore);

	printf("Arvore: \n");
	for (int i = 0; i < tamanho; i++)
	{	
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", arvore[i]);
	}
	printf("\nNumero de raizes: %d\n", num_raiz);
}
void testar_busca_profundidade(int** grafo, int tamanho)
{
	printf("\nTestando busca em profundidade: \n");
	int* arvore = new int[tamanho];
	int num_raiz = 0;
	busca_em_profundidade(grafo, tamanho, arvore);

	printf("Arvore: \n");
	for (int i = 0; i < tamanho; i++)
	{	
		if (arvore[i] == -1)
			num_raiz++;
		printf("%d ", arvore[i]);
	}
	printf("\nNumero de raizes: %d\n", num_raiz);
}
void testar_busca_largura_listas(int** grafo, int tamanho) {
	printf("\nTestando busca em largura: \n");
	list<Nodo*> arvore;
	list<Vertice*> g;
	Vertice* a;
	Vertice* b;

	for (int i = 0; i < tamanho; i++) {
		a = new Vertice(i);
		g.push_back(a);
	}

	for (int i = 0; i < tamanho; i++)
	{
		for (int y = 0; y < tamanho; y++)
		{
			if (grafo[i][y] == 1) {

				for (Vertice* v: g) {
					if (v -> id == i)
						a = v;
					else if (v -> id == y)
						b = v;
				}
				a -> adicionar_aresta(b);
			} else if (grafo[i][y] == 2) {
				for (Vertice* v: g) {
					if (v -> id == i)
							a = v;
					else if (v -> id == y)
						b = v;
				}
				a -> adicionar_filho(b);
			} else if (grafo[i][y] == 3) {
				for (Vertice* v: g) {
					if (v -> id == i)
						a = v;
					else if (v -> id == y)
						b = v;
				}
				a -> adicionar_pai(b);
			} else if (grafo[i][y] == 12) {
				for (Vertice* v: g) {
					if (v -> id == i)
						a = v;
					else if (v -> id == y)
						b = v;
				}
				a -> adicionar_filho(b);
				a -> adicionar_aresta(b);
			} else if (grafo[i][y] == 13) {
				for (Vertice* v: g) {
					if (v -> id == i)
						a = v;
					else if (v -> id == y)
						b = v;
				}
				a -> adicionar_pai(b);
				a -> adicionar_aresta(b);
			}
		}
	}
	busca_em_largura_listas_adjacencia(g, arvore);

	printf("Vertices raiz: \n");
	for (Nodo* n: arvore)
	{	
		printf("%d ", n -> id);
	}
	printf("\nNumero de raizes: %d\n", arvore.size());
}
void testar_busca_largura_listas(std::list<Vertice*>& grafo) {}
void testar_componentes_conexas(int** grafo, int tamanho)
{
	printf("\nTestando busca de componentes conexas\n");
	list<list<int>> destino;

	busca_componentes_conexas(grafo, tamanho, destino);
	for(list<int> m: destino)
	{
		printf("Proximo componente:\n");
		for(int i: m)
		{
			printf("%d ", i);
				
		}
		printf("\n");
	}
}
void testar_colorir_grafo(Grafo* grafo)
{
	printf("Testando colorir grafo\n");
	colorir_grafo(grafo);


	for (Atributos_vertice* a: grafo -> atributos)
	{
		printf("Id: %d, Numero: %d, Cores: ", a -> id, a -> numero);
		for (int i: a -> cor)
		{
			printf("%d | ", i);
			//a -> cor.remove(i);
		}
		printf("\n");
	}
}
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

	int busca = rand() % tamanho;
	printf("Matriz:\n");
	for(int i = 0; i < tamanho; i++) {
		for(int y = 0; y < tamanho; y++) {
			printf("%d ", a[i][y]);
		}
		printf("\n");
	}
	return a;
}

Grafo* trabalha_arquivo(char* caminho)
{
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
				break;
			}
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
			}
			grafo[aux_1 - 1][aux_2 - 1] = 2;
			grafo[aux_2 - 1][aux_1 - 1] = 3;

			break;
			}
			default:
				if (linha[1] == 'V') estado = VERTICE;
				break;
		}
	}

	fclose(arquivo);


	retorno = new Grafo(numero_vertices, atributos, grafo);
	return retorno;
}

int main(int argc, char* argv[]) {
	int tamanho;
	srand(time(NULL));

	if (argc == 1) {
		tamanho = 10;
	}else if (argc<1){
		return 0;
	}else{
		tamanho = atoi(argv[1]);
	}

	Grafo* g = trabalha_arquivo("entrada/Arara4MaqPar.txt");
	int** grafo = g -> grafo;
	testar_busca_largura(grafo, g -> numero_vertices);
	testar_busca_profundidade(grafo, g -> numero_vertices);	//Testando somente arestas, com arcos e totalmente conexo
	testar_componentes_conexas(grafo, g -> numero_vertices);
	testar_busca_largura_listas(grafo, g -> numero_vertices);

	testar_colorir_grafo(g);
	return 0;

}
