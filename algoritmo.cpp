#include "algoritmo.h"

void busca_em_largura_listas_adjascencia(std::list<Vertice*>& grafo, std::list<Vertice*>& destino, Vertice* fonte) {
	Vertice* elemento;

	for (Vertice* vertice_iterator: grafo)	//Inicializa os atributos do vertice
	{
		vertice_iterator->atributo = malloc(sizeof(struct Atributos));
		((struct Atributos*) (vertice_iterator->atributo))->cor = 0;
		((struct Atributos*) (vertice_iterator->atributo))->distancia_fonte = -1;
		((struct Atributos*) (vertice_iterator->atributo))->predecessor = 0;

	}
	
	if (fonte->atributo) return;	//Fonte nao esta no grafo

	((struct Atributos*) (fonte->atributo))->cor = 1;
	((struct Atributos*) (fonte->atributo))->distancia_fonte = 0;
	destino.clear();
	destino.push_back(fonte);

	while(!destino.empty()) 
	{
		elemento = destino.front();
		destino.pop_front();
		for(Vertice* vertice_iterator: elemento->adjs)
		{
			if (((struct Atributos*) (vertice_iterator->atributo))->cor == 0)	//se 'e branco'
			{		
				((struct Atributos*) (vertice_iterator->atributo))->cor = 1;	//atribui cinzento
				((struct Atributos*) (vertice_iterator->atributo))->distancia_fonte = ((struct Atributos*) (elemento->atributo))->distancia_fonte + 1;
				((struct Atributos*) (vertice_iterator->atributo))->predecessor = elemento;
				destino.push_back(vertice_iterator);	
			}
		}
		((struct Atributos*) (elemento->atributo))->cor = 2;	//atribui preto
	}

	//coloca em destino os vertices coloridos
	for(Vertice* vertice_iterator: elemento->adjs)
	{
		if (((struct Atributos*) (vertice_iterator->atributo))->cor)	//se nao e branco'
		{		
			destino.push_back(vertice_iterator);	
		}
	}
}

//utilizei 0 como branco, 1 como cinzento e 2 como preto
void busca_em_largura(int** grafo, int tamanho, std::list<int>& destino, int fonte) 
{
	int vertice;
	std::queue<int> fila;
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
		if(atributos_vertices[i]->cor)
			destino.push_back(i);
	
}

void busca_em_profundidade(int** grafo, int tamanho, std::list<int>& destino, int fonte) 
{
	Atributos_profundidade* atributos_vertices[tamanho];
	Atributos_profundidade* atributo;

	for (int i = 0; i < tamanho; i++)
	{
		atributo = (struct Atributos_profundidade*) malloc(sizeof(struct Atributos_profundidade));
		atributo->cor = 0;
		atributo->tempo_init =0;
		atributo->tempo_fim = 0;
		atributo->predecessor = 0;
		atributos_vertices[i] = atributo;
	}

	tempo = 0;
	busca_em_profundidade_(grafo, tamanho, atributos_vertices, fonte);
	for(int i = 0; i < tamanho; i++) 
		if(atributos_vertices[i]->cor)
			destino.push_back(i);
}

void busca_em_profundidade_(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice)
{
	atributos_vertices[vertice]->tempo_init = ++tempo;
	atributos_vertices[vertice]->cor = 1;

	for(int i = 0; i < tamanho; i++) 
	{
		if(grafo[i][vertice] == 1)
		{
			if(atributos_vertices[i]->cor == 0)
			{
				atributos_vertices[i]->predecessor = vertice;
				busca_em_profundidade_(grafo, tamanho, atributos_vertices, i);
			}
		}
	}
	atributos_vertices[vertice]->cor = 2;
	atributos_vertices[vertice]->tempo_fim = ++tempo;
}

/*int ** a= new int*[tamanho];
for (int i = 0; i < tamanho; i++)
	a[i] = new int[tamanho];*/
void busca_componentes_conexas(int** grafo, int tamanho, std::list<std::list<int>>& destino) {
	std::list<int> lista;
	std::list<int> sem_set;
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

		busca_em_profundidade(grafo, tamanho,lista, vertice);
		//busca_em_largura(grafo, tamanho, lista, vertice);

		//cria componente
		std::list<int> matriz;

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