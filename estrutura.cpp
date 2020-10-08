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
