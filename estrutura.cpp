#include "algoritmo.h"

Vertice::Vertice(){
	adjs = std::list<Vertice*>();
	filhos = std::list<Vertice*>();
	pais = std::list<Vertice*>();
	id = 0;
	atributo = 0;
}

Vertice::Vertice(int id_) {
	adjs = std::list<Vertice*>();
	filhos = std::list<Vertice*>();
	pais = std::list<Vertice*>();
	id = id_;
	atributo = 0;	
}

void Vertice::adicionar_aresta(Vertice* vertice) {
	adjs.push_back(vertice);
}

void Vertice::adicionar_filho(Vertice* vertice) {
	filhos.push_back(vertice);
}

void Vertice::adicionar_pai(Vertice* vertice) {
	pais.push_back(vertice);
}

Grafo::Grafo(int numero_vertices_, list<Atributos_vertice*> atributos_, int** grafo_) {
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
Atributos_vertice* Grafo::encontrar_atributo(int i) {
	for (Atributos_vertice* v: atributos)
	{
		if (v -> id == i)
			return v;
	}
	return new Atributos_vertice(-1, -1, 'e');
}
Atributos_vertice::Atributos_vertice (int id_, int numero_, char tipo_) {
	id = id_;
	numero = numero_;
	tipo = tipo_;
	cores_ate_folha = -1;
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

Cor::Cor() {
	stringstream stream;
	r = 1;
	g = 1;
	b = 1;
	rgb = "#";
	if (r < 16) rgb += "0";
	stream << std::hex << (r);
	if (g < 16) stream << std::hex << (0);
	stream << std::hex << (g);
	if (b < 16) stream << std::hex << (0);
	stream << std::hex << (b);
	rgb += stream.str();
}
Cor::Cor(int r_, int g_, int b_) {
	stringstream stream;
	r = r_;
	g = g_;
	b = b_;
	rgb = "#";
	if (r < 16) rgb += "0";
	stream << std::hex << (r);
	if (g < 16) stream << std::hex << (0);
	stream << std::hex << (g);
	if (b < 16) stream << std::hex << (0);
	stream << std::hex << (b);
	rgb += stream.str();
}
Cor::Cor(string rgb_) {
	rgb = rgb_;
	r = 0;
	g = 0;
	b = 0;
	if (rgb.size() == 7) {	//Formato "#HHHHHH"
		istringstream(rgb_.substr(1,2)) >> hex >> r;
		istringstream(rgb_.substr(3,2)) >> hex >> g;
		istringstream(rgb_.substr(5,2)) >> hex >> b;
	} else {	//Formato "HHHHHH"
		istringstream(rgb_.substr(0,2)) >> hex >> r;
		istringstream(rgb_.substr(2,2)) >> hex >> g;
		istringstream(rgb_.substr(4,2)) >> hex >> b;

	}
}
Cor::Cor(Cor* cor) {
	stringstream stream;
	r = cor -> r;
	g = cor -> g;
	b = cor -> b;
	rgb = "#";
	if (r < 16) rgb += "0";
	stream << std::hex << (r);
	if (g < 16) stream << std::hex << (0);
	stream << std::hex << (g);
	if (b < 16) stream << std::hex << (0);
	stream << std::hex << (b);
	rgb += stream.str();
}
void Cor::soma(Cor* c) {
	stringstream stream;
	r = (r + c->r)/2;
	g = (g + c->g)/2;
	b = (b + c->b)/2;
	rgb = "#";
	if (r < 16) rgb += "0";
	stream << std::hex << (r);
	if (g < 16) stream << std::hex << (0);
	stream << std::hex << (g);
	if (b < 16) stream << std::hex << (0);
	stream << std::hex << (b);
	rgb += stream.str();
}

Hash::Hash() {
	numeros = vector<int>();
	cores = vector<Cor*>();
}
Hash::~Hash() {
	Cor* aux;
	while (!cores.empty()) {
		aux = cores.back();
		cores.pop_back();
		delete aux;
	}
}
void Hash::adicionar_cor(int numero, Cor* cor) {
	numeros.push_back(numero);
	cores.push_back(cor);
}
void Hash::limpar() {
	numeros.clear();
	Cor* aux;
	while (!cores.empty()) {
		aux = cores.back();
		cores.pop_back();
		delete aux;
	}
}

Cor* Hash::encontrar_cor(int numero) {
	for (int i = 0; i < numeros.size(); i++)
	{
		if (numeros[i] == numero)
			return cores[i];
	}
	return NULL;
}


