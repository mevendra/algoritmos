#include "teste.h"
void testa_busca_largura(int** grafo, int tamanho) 
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
void testa_busca_profundidade(int** grafo, int tamanho)
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
void testa_busca_largura_listas(int** grafo, int tamanho) {}
void testa_busca_largura_listas(std::list<Vertice*>& grafo) {}
void testa_componentes_conexas(int** grafo, int tamanho) 
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
	Atributos_vertice** atributos;
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
	Atributos_vertice* atributo;
	queue<Atributos_vertice*> fila;

	while (!feof(arquivo))
	{
		fgets(linha, MAX_COLUNA_ARQUIVO, arquivo);
		switch (estado) {
			case VERTICE:		//Formate: ID ID_GERAL TIPO
			{
				numero_vertices++;
				if (linha[1] == 'E') {estado = VERTICE_FIM; break;}

				//Reseta variaveis
				atributo = (struct Atributos_vertice*) malloc(sizeof(Atributos_vertice));
				esta_em_segunda_coluna = false;
				esta_em_terceira_coluna = false;
				for (int i = 0; i < indice_segunda_coluna; i++)
					segunda_coluna[i] = ' ';
				indice_segunda_coluna = 0;

				//Interage com a linha
				for (int i = 0; i < MAX_COLUNA_ARQUIVO; i++)
				{
					if (esta_em_terceira_coluna) {
						if (linha[i] == 'e') {atributo -> tipo = 'e'; break;}
						else if (linha[i] == 't') {atributo -> tipo = 't'; break;}
						printf("Erro ao ler arquivo, Vertices numero: %d\nLinha: %s", numero_vertices,linha);
					} else if (esta_em_segunda_coluna) {
						if (linha[i] == ' ') {esta_em_terceira_coluna = true; continue;}
						segunda_coluna[indice_segunda_coluna++] = linha[i];
					} else {
						if (linha[i] == ' ') {esta_em_segunda_coluna = true; continue;}
					}
				}

				//converte texto para numeros
				atributo -> id = numero_vertices - 1;
				atributo -> numero = atoi(segunda_coluna);
				fila.push(atributo);
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

				//Cria o array para os atributos
				atributos = new Atributos_vertice*[numero_vertices];
				for (int i = 0; i < numero_vertices; i++)
				{
					atributos[i] = fila.front();
					fila.pop();
				}

				//Define o proximo estado a ser iterado
				estado = ARESTA;
				break;
			}
			case ARESTA:
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
				grafo[aux_1][aux_2] = 1;
				grafo[aux_2][aux_1] = 1;

				break;
			}
			case ARCO:
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
			grafo[aux_1][aux_2] = 2;
			grafo[aux_2][aux_1] = 3;

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

	printf("Antes arquivo\n");
	Grafo* graf = trabalha_arquivo("entrada/Arara4MaqPar.txt");
	int** grafo = graf -> grafo;
	testa_busca_largura(grafo, graf -> numero_vertices);
	testa_busca_profundidade(grafo, graf -> numero_vertices);
	testa_componentes_conexas(grafo, graf -> numero_vertices);

	return 0;

}
