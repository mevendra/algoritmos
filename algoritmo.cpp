#include "algoritmo.h"

void busca_em_largura(int** grafo, int tamanho, int* arvore) {
	int vertice;
	queue<int> fila;
	list<int> sem_set;

	//Inicia os atributos de cada vertice
	Atributos_largura* atributos_vertices[tamanho];
	Atributos_largura* atributo;
	for (int i = 0; i < tamanho; i++)
	{
		sem_set.push_back(i);
		atributo = (struct Atributos_largura*) malloc(sizeof(struct Atributos_largura));
		atributo->cor = 0;
		atributo->distancia_fonte =-1;
		atributo->predecessor = -1;
		atributos_vertices[i] = atributo;
	}

	//Enquanto tem vertices que nao pertencem a nenhuma arvore continua busca
	while(!sem_set.empty())
	{
		vertice = sem_set.front();	//pega um vertice que nao pertence a nenhuma arvore
		sem_set.pop_front();

		atributos_vertices[vertice]->cor = 1;
		atributos_vertices[vertice]->distancia_fonte = 0;
		fila.push(vertice);
		arvore[vertice] = -1;
		while(!fila.empty()) 
		{
			vertice = fila.front();
			fila.pop();
			for (int i = 0; i < tamanho; i++) {
				if (grafo[vertice][i] == 1)
				{
					if (atributos_vertices[i]->cor == 0)
					{
						atributos_vertices[i]->cor = 1;
						atributos_vertices[i]->distancia_fonte = atributos_vertices[vertice]->distancia_fonte + 1;
						atributos_vertices[i]->predecessor = vertice;

						arvore[i] = vertice;
						fila.push(i);
						sem_set.remove(i);
					}
					atributos_vertices[vertice]->cor = 2;
				}
			}	//fim for(i)
		}	//fim while(!fila.empty())
	}	//fim while(!sem_set.empty())

	//desaloca os atributos
	for(int i = 0; i < tamanho; i++)
	{
		free (atributos_vertices[i]);
	}
}

void busca_em_profundidade(int**grafo, int tamanho, int* arvore) {
	list<int> sem_set;
	int vertice;

	//define os atributos dos vertices
	Atributos_profundidade* atributos_vertices[tamanho];
	Atributos_profundidade* atributo;
	for (int i = 0; i < tamanho; i++)
	{
		sem_set.push_back(i);
		atributo = (struct Atributos_profundidade*) malloc(sizeof(struct Atributos_profundidade));
		atributo->cor = 0;
		atributo->tempo_init =0;
		atributo->tempo_fim = 0;
		atributo->predecessor = 0;
		atributos_vertices[i] = atributo;
	}

	while(!sem_set.empty())
	{
		vertice = sem_set.front();
		sem_set.pop_front();

		tempo = 0;
		arvore[vertice] = -1;
		busca_em_profundidade_(grafo, tamanho, atributos_vertices, vertice, arvore, sem_set);
	}

	//desaloca os atributos
	for(int i = 0; i < tamanho; i++)
	{
		free (atributos_vertices[i]);
	}
}

void busca_em_profundidade_(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice, int* arvore, list<int>& sem_set)
{
	atributos_vertices[vertice]->tempo_init = ++tempo;
	atributos_vertices[vertice]->cor = 1;

	for(int i = 0; i < tamanho; i++) 
	{
		if(grafo[vertice][i] == 1)
		{
			if(atributos_vertices[i]->cor == 0)
			{
				atributos_vertices[i]->predecessor = vertice;
				arvore[i] = vertice;
				sem_set.remove(i);
				busca_em_profundidade_(grafo, tamanho, atributos_vertices, i, arvore, sem_set);
			}
		}
	}
	atributos_vertices[vertice]->cor = 2;
	atributos_vertices[vertice]->tempo_fim = ++tempo;
}

void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino) {
	list<int> lista;
	list<int> sem_set;
	int vertice;

	for(int i = 0; i < tamanho; i++)
	{
		sem_set.push_back(i);
	}

	int cont = 0;
	while(!sem_set.empty())
	{
		vertice = sem_set.front();
		sem_set.pop_front();

		busca_em_largura_(grafo, tamanho, lista, vertice);

		//cria componente
		list<int> matriz;

		//insere vertices
		for(int i: lista)
		{
			matriz.push_back(i);
			sem_set.remove(i);
		}
		lista.clear();

		destino.push_back(matriz);
	}
}

void busca_em_largura_(int** grafo, int tamanho, list<int>& destino, int fonte)
{
	int vertice;
	queue<int> fila;
	Atributos_largura* atributos_vertices[tamanho];
	Atributos_largura* atributo;

	for (int i = 0; i < tamanho; i++)
	{
		atributo = (struct Atributos_largura*) malloc(sizeof(struct Atributos_largura));
		atributo->cor = 0;
		atributo->distancia_fonte =-1;
		atributo->predecessor = 0;
		atributos_vertices[i] = atributo;
	}

	atributos_vertices[fonte]->cor = 1;
	atributos_vertices[fonte]->distancia_fonte = 0;

	fila.push(fonte);
	while(!fila.empty()) 
	{
		vertice = fila.front();
		fila.pop();
		for (int i = 0; i < tamanho; i++) {
			if (grafo[i][vertice] == 1)
			{
				if (atributos_vertices[i]->cor == 0)
				{
					atributos_vertices[i]->cor = 1;
					atributos_vertices[i]->distancia_fonte = atributos_vertices[vertice]->distancia_fonte + 1;
					atributos_vertices[i]->predecessor = vertice;
					fila.push(i);
				}
				atributos_vertices[vertice]->cor = 2;
			}
		}
	}

	for(int i = 0; i < tamanho; i++) 
	{
		if(atributos_vertices[i]->cor)
			destino.push_back(i);
		free(atributos_vertices[i]);
	}
	
}

void busca_em_largura_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz)
{
	//Atributos
	queue<Vertice*> fila;
	list<Vertice*> sem_set;
	Atributos_largura_lista* atributos;
	Vertice* atual;
	Nodo* aux;

	//Alocacao do espaco para  os atributos
	for (Vertice* v: grafo)
	{
		atributos = (Atributos_largura_lista*) malloc(sizeof(Atributos_largura_lista));
		atributos -> cor = 0;
		atributos -> nodo = new Nodo(v -> id);
		v-> atributo = atributos;
		sem_set.push_back(v);
	}

	while (!sem_set.empty())
	{
		//Primeiro vertice que nao esta em nenhuma arvore
		atual = sem_set.front();
		sem_set.pop_front();

		//Vertice sera uma raiz
		aux = ((Atributos_largura_lista* )atual -> atributo) -> nodo;
		raiz.push_back(aux);

		//Marca vertice
		((Atributos_largura_lista* )atual -> atributo) -> cor = 1;
		fila.push(atual);

		//Procura os alcancaveis por ele
		while (!fila.empty())
		{
			atual = fila.front();
			fila.pop();
			aux = ((Atributos_largura_lista* )atual -> atributo) -> nodo;
			for (Vertice* v: atual -> adjs)
			{
				if (((Atributos_largura_lista* )v -> atributo) -> cor == 0) {
					((Atributos_largura_lista* )v -> atributo) -> cor = 1;
					((Atributos_largura_lista* )v -> atributo) -> nodo -> adicionar_anterior(aux);
					fila.push(v);

				}
			}
			sem_set.remove(atual);
		}
	}

	//Liberacao do espaco alocado aos atributos
	for (Vertice* v: grafo)
	{
		free(v -> atributo);
	}
}
void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz)
{
	//Atributos
	queue<Vertice*> fila;
	Atributos_largura* atributos;

	//Alocacao do espaco para  os atributos
	for (Vertice* v: grafo)
	{
		atributos = (Atributos_largura*) malloc(sizeof(Atributos_largura));
		atributos -> cor = 0;
		v-> atributo = atributos;
	}

	//Liberacao do espaco alocado aos atributos
	for (Vertice* v: grafo)
	{
		free(v -> atributo);
	}
}

void colorir_grafo(Grafo* g)
{
	int** grafo = g -> grafo;
	if (grafo == NULL) return;

	//Busca fontes
	list<int> fontes;
	busca_fontes(grafo, g -> numero_vertices, fontes);


	//Colore apartir das fontes
	for (int i: fontes)
		colorir_apartir_de(g, i);
}

void busca_fontes(int** grafo, int tamanho, list<int>& destino)
{
	bool eh_fonte;
	for (int i = 0; i < tamanho; i++)
	{
		eh_fonte = true;
		for (int y = 0; y < tamanho; y++)
		{
			if (grafo[i][y] == 3 || grafo[i][y] == 13)
				{eh_fonte = false; break;}	//Vertice i tem um arco chegando nele
		}
		if (eh_fonte) {destino.push_back(i);}	//adiciona i como fonte na lista
	}
}

void colorir_apartir_de(Grafo* g,int vertice)
{
	int** grafo = g -> grafo;
	if (grafo == NULL) return;

	//Atributos
	queue<int> fila;
	int tamanho = g -> numero_vertices;
	int vertice_atual;
	Atributos_largura* atributos_vertices[tamanho];
	Atributos_largura* atributo;

	//Alocacao do espaco para Atributos_largura
	for (int i = 0; i < tamanho; i++)
	{
		atributo = (struct Atributos_largura*) malloc(sizeof(struct Atributos_largura));
		atributo->cor = 0;
		atributos_vertices[i] = atributo;
	}

	//Vertice inicial
	atributos_vertices[vertice] -> cor = 1;
	fila.push(vertice);

	while(!fila.empty())
	{
		//Remove primeiro da fila
		vertice_atual = fila.front();
		fila.pop();
		for (int i = 0; i < tamanho; i++)
		{
			if (grafo[vertice_atual][i] == 2 || grafo[vertice_atual][i] == 12) {		//Arco da forma vertice_atual -> i
				if (atributos_vertices[i] -> cor == 0)	//Se i nao esta marcado
				{
					atributos_vertices[i] -> cor = 1;
					fila.push(i);
				}
			}
		}
	}

	//Coloracao dos vertices alcancados e liberacao do espaco alocado
	for (int i = 0; i < tamanho; i++)
	{
		if (atributos_vertices[i] -> cor == 1)
		{
			g -> encontrar_vertice(i) -> adicionar_cor(vertice);
		}
		free(atributos_vertices[i]);
	}
}



