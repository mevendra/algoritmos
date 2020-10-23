#include "lista.h"
//Elemento_int
Elemento_int::Elemento_int(int elemento_) {
	elemento = elemento_;
	proximo = NULL;
}
Elemento_int::~Elemento_int() {	//Verificar funcionamento
	delete proximo;
}

//Lista_int
Lista_int::Lista_int() {
	primeiro = NULL;
	tamanho = 0;
}
Lista_int::~Lista_int() {	//Verificar funcionamento
	delete primeiro;
}
bool Lista_int::vazia() {
	if (tamanho <= 0) return true;
	else return false;
}
bool Lista_int::contem(int numero) {
	Elemento_int* atual = primeiro;
	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento == numero) return true;
		atual = atual -> proximo;
	}
	return false;
}
bool Lista_int::eh_igual(Lista_int* lista) {
	if (lista == NULL) return false;
	if(tamanho != lista -> tamanho) return false;

	Elemento_int* atual = primeiro;
	Elemento_int* atual_lista = lista -> primeiro;
 	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento == atual_lista -> elemento) {
			atual = atual -> proximo;
			atual_lista = atual_lista -> proximo;
		} else {
			return false;
		}
	}
	return true;
}
void Lista_int::adicionar(int numero) {
	Elemento_int* atual = primeiro;
	Elemento_int* aux = NULL;
	Elemento_int* novo = new Elemento_int(numero);
	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento < numero) {
			aux = atual;
			atual = atual -> proximo;
		} else if (atual -> elemento == numero) {	//Lista ja tem elemento
			return;
		} else {
			break;
		}
	}
	if (atual == NULL && aux == NULL) {	//primeiro elemento da lista
		primeiro = novo;
	} else if ( atual == NULL) {	//chegou ao fim da lista
		aux -> proximo = novo;
	} else if (aux == NULL) {	//Inserir no comeco
		aux = primeiro;
		primeiro = novo;
		novo -> proximo = aux;
	} else {
		aux -> proximo = novo;
		novo -> proximo = atual;
	}
	tamanho++;
}
void Lista_int::remover(int numero) {	//Verificar funcionamento (delete atual)
	Elemento_int* atual = primeiro;
	Elemento_int* anterior = NULL;

	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento == numero) {
			if (!anterior == NULL) {
				anterior -> proximo = atual -> proximo;
			} else {
				primeiro = atual -> proximo;
			}
			atual -> proximo = NULL;
			delete atual;
			tamanho--;
		} else {
			anterior = atual;
			atual = atual -> proximo;
		}
	}
}

//Elemento_lista
Elemento_lista::Elemento_lista(Lista_int* lista) {
	elemento = lista;
	proximo = NULL;
}
Elemento_lista::~Elemento_lista() {	//Verificar funcionamento
	delete elemento;
	delete proximo;
}
Lista_int* Elemento_lista::copiar_lista() {
	Lista_int* nova = new Lista_int();
	if (elemento == NULL) return nova;

	Elemento_int* atual = elemento -> primeiro;
	for (int i = 0; i < elemento -> tamanho; i++) {
		nova -> adicionar(atual -> elemento);
		atual = atual -> proximo;
	}

	return nova;
}

//Lista_lista
Lista_lista::Lista_lista() {
	tamanho = 0;
	primeiro = NULL;
}
Lista_lista::~Lista_lista() {	//Verificar funcionamento
	delete primeiro;
}
bool Lista_lista::vazia() {
	if (tamanho <= 0) return true;
	return false;
}
bool Lista_lista::contem(Lista_int* numero) {
	Elemento_lista* atual = primeiro;
	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento -> eh_igual(numero)) return true;
		atual = atual -> proximo;
	}
	return false;
}
bool Lista_lista::eh_igual(Lista_lista* lista) {
	if (lista == NULL) return false;
	if (lista -> tamanho != tamanho) return false;

	Elemento_lista* atual = primeiro;
	for (int i = 0; i < tamanho; i++)
	{
		if (lista -> contem(atual -> elemento)) {
			atual = atual -> proximo;
		} else {
			return false;
		}
	}
	return true;
}
void Lista_lista::adicionar(Lista_int* numero) {
	Elemento_lista* atual = primeiro;
	Elemento_lista* novo = new Elemento_lista(numero);

	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento -> eh_igual(numero)) {	//Lista ja tem elemento
			return;
		}
		atual = atual -> proximo;
	}
	atual = primeiro;
	primeiro = novo;
	novo -> proximo = atual;
	tamanho++;
}
void Lista_lista::remover(Lista_int* numero) {	//Verificar funcionamento
	Elemento_lista* atual = primeiro;
	Elemento_lista* anterior = NULL;

	for (int i = 0; i < tamanho; i++)
	{
		if (atual -> elemento -> eh_igual(numero)) {
			if (!anterior == NULL) {
				anterior -> proximo = atual -> proximo;
			} else {
				primeiro = atual -> proximo;
			}
			tamanho--;
			delete atual;
			return;
		} else {
			anterior = atual;
			atual = atual -> proximo;
		}
	}
}
Lista_lista* Lista_lista::copiar() {
	Lista_lista* nova = new Lista_lista();

	Elemento_lista* atual = primeiro;
	Lista_int* novo;
	for (int i = 0; i < tamanho; i++)
	{
		novo = atual -> copiar_lista();
		nova -> adicionar(novo);

		atual = atual -> proximo;
	}

	return nova;
}
