#include "estrutura.h"

template<typename T>
bool contem(T t, list<T> l) {
	for (T x: l)
		if (x == t)
			return true;

	return false;
}

string primeira_cor() {
	if (cores.size() == 0) {
		printf("Não tem cores suficientes\n");
		return "";
	}

	string retorno = cores.front();
	cores.pop_front();

	return retorno;
}

void reinicia_cores() {
	cores.clear();
	cores.push_back("#0000FF");
	cores.push_back("#FF0000");
	cores.push_back("#00FF00");
	cores.push_back("#FFFF00");
	cores.push_back("#FF00FF");
	cores.push_back("#00FFFF");
	cores.push_back("#808080");
	cores.push_back("#4682B4");
	cores.push_back("#008080");
	cores.push_back("#808000");
	cores.push_back("#8B4513");
	cores.push_back("#DEB887");
	cores.push_back("#8B008B");
	cores.push_back("#CD5C5C");
	cores.push_back("#FF69B4");
	cores.push_back("#B22222");
	cores.push_back("#FF8C00");
	cores.push_back("#D8BFD8");
	cores.push_back("#EEE8AA");

	for (int i = 0; i < 1000; i++) {
		string nova_cor = proxima_cor_aleatoria();
		nova_cor = "#" + nova_cor;

		cores.push_back(nova_cor);
	}
}

string proxima_cor_aleatoria() {
	stringstream stream;
	string retorno = "";
	int numero;

	int um = rand() % 16;
	int dois = rand() % 16;
	int tres = rand() % 16;
	int quatro = rand() % 16;
	int cinco = rand() % 16;
	int seis = rand() % 16;

	numero = um;
	numero = (numero << 4) + dois;
	numero = (numero << 4) + tres;
	numero = (numero << 4) + quatro;
	numero = (numero << 4) + cinco;
	numero = (numero << 4) + seis;

	stream << hex << numero;
	retorno = stream.str();

	return retorno;
}

static int atual = 0;

//Cor
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
	/*
	int c_ = cor -> to_int();
	int r_ = (c_ >> 8) & 256;
	int g_ = (c_ >> 16) & 256;
	int b_ = c_ & 256;
*/
	Cor(cor -> g_rgb());
}

void Cor::soma(Cor* c) {
	int c_ = c -> to_int();
	int r_ = (c_ >> 8) & 256;
	int g_ = (c_ >> 16) & 256;
	int b_ = c_ & 256;

	stringstream stream;
	r = (r + r_)/2;
	g = (g + g_)/2;
	b = (b + b_)/2;
	rgb = "#";
	if (r < 16) rgb += "0";
	stream << std::hex << (r);
	if (g < 16) stream << std::hex << (0);
	stream << std::hex << (g);
	if (b < 16) stream << std::hex << (0);
	stream << std::hex << (b);
	rgb += stream.str();
}

int Cor::to_int() {
	int ret = r;
	ret = (ret << 8) + g;
	ret = (ret << 8) + b;

	if (ret < 0)	//MUDAR
		ret = ret * -1;
	return ret;
}

//Hash
Hash::~Hash() {
	Cor* aux;
	while (!cores.empty()) {
		aux = cores.back();
		cores.pop_back();
		delete aux;
	}
}

void Hash::adicionar_cor(int numero, Cor* cor) {
	set<int> aux = set<int>();
	aux.insert(numero);
	numeros.push_back(aux);
	cores.push_back(cor);
}

void Hash::adicionar_cor(set<int> numero, Cor* cor) {
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
	set<int> aux = set<int>();
	aux.insert(numero);

	return encontrar_cor(aux);
}

Cor* Hash::encontrar_cor(set<int> numero) {
	cor_cmp cmp;
	for (int i = 0; i < numeros.size(); i++)
	{
		if (cmp.operator()(numeros[i], numero))
			return cores[i];
	}
	return 0;
}
int Hash::encontrar_indice_cor(set<int> numero) {
	cor_cmp cmp;
	for (int i = 0; i < numeros.size(); i++)
	{
		if (cmp.operator()(numeros[i], numero))
			return i;
	}
	return -1;
}

//Vertice
Vertice::Vertice (int id_, int numero_, char tipo_) {
	id = id_;
	numero = numero_;
	tipo = tipo_;
}

void Vertice::adicionar_cor(int cor_) {
	cor.insert(cor_);
}
void Vertice::adicionar_casamento(Vertice* casamento) {
	casados.push_back(casamento);
}
void Vertice::adicionar_pais(Vertice* pai) {
	pais.push_back(pai);
}
void Vertice::adicionar_filho(Vertice* filho) {
	filhos.push_back(filho);
}

void Vertice::resetar() {
	geracao = -1;
	valor_int = -1;
	valor_bool = false;
	valor_bool_2 = false;
	if (ponteiro) {
		//delete ponteiro;
		ponteiro = 0;
	}
}

//Grafo
Grafo::Grafo(int numero_vertices_, vector<Vertice*> atributos_, int** grafo_) {
	numero_vertices = numero_vertices_;
	atributos = vector<Vertice*> (atributos_);
	grafo = grafo_;
}

Grafo::Grafo(int numero_vertices_, vector<Vertice*> atributos_, Vertice* raiz_, int** grafo_) {
	raiz = raiz_;
	numero_vertices = numero_vertices_;
	atributos = atributos_;
	grafo = grafo_;
}

Grafo::~Grafo() {
	for (Vertice* v: atributos)
		if (v)
			delete v;

	delete grafo;
}

Vertice* Grafo::encontrar_atributo(int i) {
	if (i >= atributos.size() || i < 0)
		return new Vertice(-1, -1, 'e');
	else
		return atributos[i];
}

void Grafo::resetar() {
	for (Vertice* v: atributos)
		if (v)
			v -> resetar();
}

void Grafo::adicionar_vertice(Vertice* v, bool eh_raiz) {
	//Matriz é ajustada no inicio, não pode ser aumentada
	//atributos[numero_vertices] = v;	todo
	if (v -> g_id() == numero_vertices) {
		atributos.push_back(v);
		numero_vertices++;
		if (eh_raiz)
			raiz = v;
	} else
		throw runtime_error("Em Grafo::adicionar_vertice, vértice com id invalido adicionado");
}

void Grafo::remover_vertice(Vertice* v) {
	if (!v)
		return;
	Vertice* aux = encontrar_atributo(v -> g_id());
	if (aux == v) {
		numero_vertices--;
		atributos[v -> g_id()] = 0;

		for (Vertice* x: v -> pais)
			x -> filhos.remove(v);
		for (Vertice* x: v -> filhos)
			x -> pais.remove(v);
		for (Vertice* x: v -> casados)
			x -> casados.remove(v);

		v -> pais.clear();
		v -> filhos.clear();
		v -> casados.clear();
	}
}

//Nodo
Nodo::Nodo(Vertice* nodo_) {
	nodo = nodo_;
}
void Nodo::adicionar_sucessor(Nodo * sucessor) {
	if (!contem(sucessor, sucessores)) {
		sucessores.push_back(sucessor);
		sucessor -> antecessores.push_back(this);
	}
}
void Nodo::adicionar_antecessor(Nodo * antecessor) {
	if (!contem(antecessor, antecessores)) {
		antecessores.push_back(antecessor);
		antecessor -> sucessores.push_back(this);
	}
}

void Nodo::print_filhos() {
	if (sucessores.size() > 0) {
		printf("%d: ", nodo -> g_numero());
		for (Nodo* d: sucessores) {
			printf("%d ", d -> nodo -> g_numero());
		}
		printf("\n");

		for (Nodo* d: sucessores) {
			d -> print_filhos();
		}
	}
}

void Nodo::pos_ordem(list<Nodo*> &destino) {
	for (Nodo* d: sucessores)
		d -> pos_ordem(destino);
	destino.push_back(this);
}

//Juncao
Juncao::Juncao(Vertice* primeiro_, Vertice* segundo_, Vertice* juncao_) {
	primeiro = primeiro_;
	segundo = segundo_;
	juncao = juncao_;
}

//JuncoesDe
JuncoesDe::JuncoesDe(Vertice* primeiro_, Vertice* segundo_) {
	primeiro = primeiro_;
	segundo = segundo_;
}

void JuncoesDe::adicionar_juncao(Vertice* juncao) {
	juncoes.push_back(juncao);
}

//Anel_aux
void Anel_aux::mudar_tamanho(int tamanho) {
	juncoes.resize(tamanho);
	caminhos_primeiro.resize(tamanho);
	caminhos_segundo.resize(tamanho);
	cores.resize(tamanho);
}

//Anel
void encontrar_caminho(vector<list<Vertice*>> caminho, Vertice* pertence, list<Vertice*> &destino) {
for (list<Vertice*> l: caminho) {
	for (Vertice* v: l) {
		if (v == pertence) {
			destino = list<Vertice*>(l);
			return;
		}
	}
}
}
void Anel::adicionar_elemento(vector<list<Vertice*>> caminho, list<list<int>> casamentos_, list<Juncao*> juncoesUtilizadas, bool realizado) {
	//Adiciona todos os vertices ao anel
	for (list<Vertice*> lista: caminho)
		for (Vertice* i: lista)
			vertices.push_back(i);

	for (Juncao* j: juncoesUtilizadas) {
		vertices.push_back(j -> juncao);
		juncoes.push_back(j -> juncao);
	}

	//Adiciona todos os caminhos percorridos pelas juncoes
	for (Juncao* j: juncoesUtilizadas) {
		list<Vertice*> novo_caminho;
		novo_caminho.push_back(j -> juncao);

		list<Vertice*> caminho_aux;
		encontrar_caminho(caminho, j -> primeiro, caminho_aux);
		for (Vertice* v: caminho_aux)
			novo_caminho.push_front(v);

		caminho_aux.clear();
		encontrar_caminho(caminho, j -> segundo, caminho_aux);
		for (Vertice* v: caminho_aux)
			novo_caminho.push_back(v);

		caminhos.push_back(novo_caminho);
	}

	//Adiciona os casamentos ao Anel
	for(list<int> l: casamentos_) {
		list<Vertice*> novo_casamento;
		for (int i: l) {
			for (Vertice* v: vertices) {
				if (v -> g_id() == i) {
					novo_casamento.push_back(v);
					break;
				}
			}
		}
		casamentos.push_back(novo_casamento);
	}


	//Escolhe o primeiro elemento do anel
	Vertice* proximo;
	if (casamentos.front().front() -> g_tipo() == 't')
		proximo = casamentos.front().front();
	else
		proximo = casamentos.front().back();

	//Define ordem do anel
	list<list<Vertice*>> caminhos_aux(caminhos);
	list<list<Vertice*>> casamentos_aux(casamentos);
	list<Vertice*> remover;
	while(caminhos_aux.size() > 0) {
		//Encontra o caminho da juncao que proximo pertence e o adiciona ao anel
		for (list<Vertice*> l: caminhos_aux) {
			if (l.front() == proximo) {
				remover = l;
				for (Vertice* v: l)
					anel.push_back(v);
				proximo = l.back();
				break;
			} else if (l.back() == proximo) {
				remover = l;
				l.reverse();
				for (Vertice* v: l)
					anel.push_back(v);
				proximo = l.back();
				break;
			}
		}
		caminhos_aux.remove(remover);

		//Encontra o casamento com o ultimo elemento adicionado ao anel
		for (list<Vertice*> l: casamentos_aux) {
			if (l.front() == proximo) {
				proximo = l.back();
				remover = l;
				break;
			} else if (l.back() == proximo) {
				proximo = l.front();
				remover = l;
				break;
			}
		}
		casamentos_aux.remove(remover);
	}
	//Verifica se escolheu o casamento com menor geração
	if (casamentos.size() == 2 && !realizado) {
		bool primeiro = false;
		bool segundo = false;

		int n_primeiro = 0;
		int n_segundo = 0;
		int n_terceiro = 0;
		int n_quarto = 0;

		Vertice* ultimo = anel.front();
		int aux = 0;
		for (Vertice* v: anel) {
			if (contem(v, juncoes)) {
				if (!primeiro) {
					n_primeiro = aux;
					primeiro = true;
					aux = 0;
					continue;
				} else {
					n_terceiro = aux;
					aux = 0;
					continue;
				}
			} else {
				bool aux_ = false;
				for (list<Vertice*> l: casamentos) {
					if (contem(v, l)) {
						if (!segundo) {
							n_segundo = aux;
							aux = 0;
							segundo = true;
							aux = true;
							break;
						} else {
							n_quarto = aux;
							aux = 0;
							break;
						}
					}
				}
				if (aux_)
					continue;
			}
			aux++;
		}



		//Se segundo ego tem geracao maior, inverte a ordem dos casamentos
		if (n_segundo + n_terceiro > n_primeiro + aux) {
		/*if ((( (n_segundo > n_terceiro ? n_segundo : n_terceiro) == (n_primeiro > aux ? n_primeiro : aux)) &&
				((n_segundo < n_terceiro ? n_segundo : n_terceiro) > (n_primeiro < aux ? n_primeiro : aux))) ||
				((n_segundo > n_terceiro ? n_segundo : n_terceiro) > (n_primeiro > aux ? n_primeiro : aux))) {*/
			//Geracao do casamento interno tem menos descendentes
			anel.clear();
			vertices.clear();
			caminhos.clear();
			casamentos.clear();
			juncoes.clear();

			casamentos_.push_back(casamentos_.front());
			casamentos_.pop_front();
			this -> adicionar_elemento(caminho, casamentos_, juncoesUtilizadas, true);
		}
	}

	//Salva o anel nas strings
	linha_normal = "";
	linha_ordem = "";
	for (Vertice* v: anel) {
		linha_normal += to_string(v -> g_numero());
		linha_normal += " ";
	}
	linha_normal += "\n";
}
