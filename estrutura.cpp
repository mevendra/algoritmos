#include "estrutura.h"

Vertice::Vertice(){
	adjs = std::list<Vertice*>();
	id = 0;
	atributo = 0;
}

Vertice::Vertice(int id_) {
	adjs = std::list<Vertice*>();
	id = id_;
	atributo = 0;	
}

void Vertice::adicionar_aresta(Vertice* vertice) {
	adjs.push_back(vertice);
}

Grafo::Grafo(int numero_vertices_, list<Atributos_vertice*> atributos_, int** grafo_) {
	numero_vertices = numero_vertices_;
	atributos = atributos_;
	grafo = grafo_;
}

Atributos_vertice* Grafo::encontrar_vertice(int id) {
	for (Atributos_vertice* a: atributos)
	{
		if (a -> id == id)
			return a;
	}
	return NULL;
}

void Grafo::adicionar_aresta(int v1, int v2){
	grafo[v1][v2] = 1;
	grafo[v2][v1] = 1;
}
void Grafo::adicionar_arco(int fonte, int destino) {
	grafo[fonte][destino] = 2;
	grafo[destino][fonte] = 3;
}

Atributos_vertice::Atributos_vertice (int id_, int numero_, char tipo_) {
	id = id_;
	numero = numero_;
	tipo = tipo_;
}

void Atributos_vertice::adicionar_cor(int cor_) {
	cor.push_back(cor_);
}

Nodo::Nodo(int id_) {
	id = id_;
	anterior = NULL;
}

Nodo::Nodo(int id_, Nodo* anterior_) {
	id = id_;
	anterior = anterior_;
}

void Nodo::adicionar_filho (Nodo* filho) {
	proximo.push_back(filho);
}

void Nodo::adicionar_anterior (Nodo* anterior_) {
	if (anterior == NULL)
		anterior = anterior_;
}
