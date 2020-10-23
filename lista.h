#ifndef LISTA_H
#define LISTA_H
#include <stdlib.h>
using namespace std;

class Elemento_int {
public:
	int elemento;
	Elemento_int *proximo;

	Elemento_int(int elemento);
	~Elemento_int();
};
class Lista_int {
public:
	Elemento_int *primeiro;
	int tamanho;

	Lista_int();
	~Lista_int();
	bool vazia();
	bool contem(int numero);
	bool eh_igual(Lista_int *lista);
	void adicionar(int numero);
	void remover(int numero);
};

class Elemento_lista {
	public:
		Lista_int* elemento;

		Elemento_lista* proximo;
		Elemento_lista(Lista_int* elemento);
		~Elemento_lista();
		Lista_int* copiar_lista();
};
class Lista_lista {
	public:
		Elemento_lista *primeiro;
		int tamanho;

		Lista_lista();
		~Lista_lista();
		bool vazia();
		bool contem(Lista_int* numero);
		bool eh_igual(Lista_lista* lista);
		void adicionar(Lista_int* numero);
		void remover(Lista_int* numero);
		Lista_lista* copiar();
};

#endif

