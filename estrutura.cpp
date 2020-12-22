#include "algoritmo.h"

//Vertice
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

//Grafo
Grafo::Grafo(int numero_vertices_, list<Atributos_vertice*> atributos_, int** grafo_) {
	numero_vertices = numero_vertices_;
	atributos = atributos_;
	grafo = grafo_;
}

void Grafo::adicionar_aresta(int v1, int v2){
	if (grafo[v1][v2] == 2) {
		grafo[v1][v2] = 12;
		grafo[v2][v1] = 13;
	} else if (grafo[v2][v1] == 2) {
		grafo[v1][v2] = 13;
		grafo[v2][v1] = 12;
	} else {
		grafo[v1][v2] = 1;
		grafo[v2][v1] = 1;
	}
}

void Grafo::adicionar_arco(int fonte, int destino) {
	if (grafo[fonte][destino] == 1) {
		grafo[fonte][destino] = 12;
		grafo[destino][fonte] = 13;
	} else {
		grafo[fonte][destino] = 2;
		grafo[destino][fonte] = 3;
	}
}

Atributos_vertice* Grafo::encontrar_atributo(int i) {
	for (Atributos_vertice* v: atributos)
	{
		if (v -> id == i)
			return v;
	}
	return new Atributos_vertice(-1, -1, 'e');
}

//Atributos_vertice
Atributos_vertice::Atributos_vertice (int id_, int numero_, char tipo_) {
	id = id_;
	numero = numero_;
	tipo = tipo_;
	cores_ate_folha = -1;
	particao = -1;
	valor_bool = false;
	folha_cores = NULL;
}

void Atributos_vertice::adicionar_cor(int cor_) {
	cor.push_back(cor_);
}
void Atributos_vertice::adicionar_casamento(Atributos_vertice* casamento) {
	casados.push_back(casamento);
}
void Atributos_vertice::adicionar_pais(Atributos_vertice* pai) {
	pais.push_back(pai);
}
void Atributos_vertice::adicionar_filho(Atributos_vertice* filho) {
	filhos.push_back(filho);
}

//Nodo
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

//Cor
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

//Hash
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

Juncao::Juncao(Atributos_vertice* primeiro_, Atributos_vertice* segundo_, Atributos_vertice* juncao_) {
	primeiro = primeiro_;
	segundo = segundo_;
	juncao = juncao_;
}

JuncoesDe::JuncoesDe(Atributos_vertice* primeiro_, Atributos_vertice* segundo_) {
	primeiro = primeiro_;
	segundo = segundo_;
}


void JuncoesDe::adicionar_juncao(Atributos_vertice* juncao) {
	juncoes.push_back(juncao);
}

void Anel::adicionar_elemento(list<Atributos_vertice*> caminho, bool caminho_inverso = false) {
	Atributos_vertice* v;
	if (!caminho_inverso && caminho.size() > 0) {
		v = caminho.front();
		caminho.pop_front();
		linha_normal += to_string(v -> numero);
		linha_normal += " ";

		if (v -> tipo == 'e')
			linha_ordem += "W";
		else
			linha_ordem += "H";

		linha_ordem += " ";
		linha_ordem	+= to_string(v -> numero);
		linha_ordem += " ";
	}

	for (Atributos_vertice* i: caminho) {
		linha_normal += to_string(i -> numero);
		linha_normal += " ";

		if (caminho_inverso)
			if (i -> tipo == 'e')
				linha_ordem += "D";
			else
				linha_ordem += "S";
		else
			if (i -> tipo == 'e')
				linha_ordem += "M";
			else
				linha_ordem += "F";

		linha_ordem += " ";
		linha_ordem	+= to_string(i -> numero);
		linha_ordem += " ";

		anel.push_back(i);
	}

	if (!caminho_inverso && caminho.size() > 0)
		caminho.push_front(v);
}

void Anel::adicionar_elemento(vector<list<Atributos_vertice*>> caminho, list<Atributos_vertice*> juncoes, list<list<int>> casamentos){
	//Adiciona todos os elementos ao anel
	for (list<Atributos_vertice*> lista: caminho) {
		for (Atributos_vertice* i: lista) {
			anel.push_back(i);
		}
	}

	//Adiciona juncoes ao anel
	for (Atributos_vertice* i: juncoes) {
		anel.push_back(i);
	}

	//Escolhe um casamento para iniciar
	list<Atributos_vertice*> aux(anel);
	int primeiro = casamentos.front().front();
	int segundo = casamentos.front().back();
	Atributos_vertice* v = NULL;
	for (Atributos_vertice* i: aux) {
		if ( (i -> id == primeiro || i -> id == segundo) && i -> tipo == 't') {
			v = i;
			break;
		}
	}

	//Se encontrou casamento
	if (v != NULL) {
		aux.remove(v);
		if (v -> tipo == 'e')
			linha_ordem = " W";
		else
			linha_ordem = " H";

		linha_normal += " ";
		linha_normal = to_string(v -> numero);

		linha_ordem += to_string(v -> numero);
	} else {	//Se nao encontrou casamento acontece erro
		printf("Nao encontrou casamento \n");
		return;
	}

	//Começa escolha das linhas
	Atributos_vertice* proximo;
	bool em_subida = false;
	while(aux.size() > 0) {
		//Procura primeiro pelos pais
		proximo = NULL;
		bool parar = false;
		for (Atributos_vertice* pai: v -> pais) {
			for (Atributos_vertice* atrib_aux: aux) {
				if (pai -> id == atrib_aux -> id) {
					parar = true;
					proximo = atrib_aux;
					break;
				}
			}
			if (parar)
				break;
		}

		//Encontrou pai
		if (proximo != NULL) {
			em_subida = true;
			aux.remove(proximo);
			v = proximo;
			if (v -> tipo == 'e')
				linha_ordem += " M";
			else
				linha_ordem += " F";

			linha_normal += " ";
			linha_normal += to_string(v -> numero);

			linha_ordem += to_string(v -> numero);
			continue;
		}

		//Nao encontrou pai, procura filhos
		parar = false;
		for (Atributos_vertice* filho: v -> filhos) {
			for (Atributos_vertice* atrib_aux: aux) {
				if (filho -> id == atrib_aux -> id) {
					parar = true;
					proximo = atrib_aux;
					break;
				}
			}
			if (parar)
				break;
		}

		//Encontrou filho
		if (proximo != NULL) {
			if (em_subida) {	//Estava procurando pai e começa a procurar filho(Juncao)
				linha_ordem += "_J";
				em_subida = false;
			}
			aux.remove(proximo);
			v = proximo;
			if (v -> tipo == 'e')
				linha_ordem += " D";
			else
				linha_ordem += " S";

			linha_normal += " ";
			linha_normal += to_string(v -> numero);

			linha_ordem += to_string(v -> numero);

			continue;
		}

		//Nao encontrou filhos procura casamento
		parar = false;
		for (Atributos_vertice* casado: v -> casados) {
			for (Atributos_vertice* atrib_aux: aux) {
				if (casado -> id == atrib_aux -> id) {
					//Procura se é o casamento desejado
					for (list<int> i: casamentos) {
						if (i.front() == casado -> id) {
							if (i.back() == v -> id) {
								parar = true;
								proximo = atrib_aux;
								break;
							}
						} else if (i.back() == casado -> id) {
							if (i.front() == v -> id) {
								parar = true;
								proximo = atrib_aux;
								break;
							}
						}
					}
					if (parar)
						break;
				}
			}
			if (parar)
				break;
		}
		if (proximo != NULL) {
			aux.remove(proximo);
			v = proximo;
			if (v -> tipo == 'e')
				linha_ordem += " W";
			else
				linha_ordem += " H";

			linha_normal += " ";
			linha_normal += to_string(v -> numero);

			linha_ordem += to_string(v -> numero);

			continue;
		}

		linha_normal = "";
		linha_ordem = "";
		return;
	}

	linha_normal += "\n";
	linha_ordem += "\n";
}

void Anel_aux::mudar_tamanho(int tamanho) {
	juncoes.resize(tamanho);
	caminhos_primeiro.resize(tamanho);
	caminhos_segundo.resize(tamanho);
}
