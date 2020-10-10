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

Grafo::Grafo(int numero_vertices_, Atributos_vertice** atributos_, int** grafo_) {
	numero_vertices = numero_vertices_;
	atributos = atributos_;
	grafo = grafo_;
}

void Grafo::adicionar_aresta(int v1, int v2){
	grafo[v1][v2] = 1;
	grafo[v2][v1] = 1;
}
void Grafo::adicionar_arco(int fonte, int destino) {
	grafo[fonte][destino] = 2;
	grafo[destino][fonte] = 3;
}
