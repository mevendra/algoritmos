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
	geracao = 0;
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
			linha_ordem += " W";
		else
			linha_ordem += " H";

		linha_ordem	+= to_string(v -> numero);
	}

	for (Atributos_vertice* i: caminho) {
		linha_normal += to_string(i -> numero);
		linha_normal += " ";

		if (caminho_inverso)
			if (i -> tipo == 'e')
				linha_ordem += " D";
			else
				linha_ordem += " S";
		else
			if (i -> tipo == 'e')
				linha_ordem += " M";
			else
				linha_ordem += " F";

		linha_ordem	+= to_string(i -> numero);

		anel.push_back(i);
	}

	if (!caminho_inverso && caminho.size() > 0)
		caminho.push_front(v);
}

void encontrar_caminho(vector<list<Atributos_vertice*>> caminho, Atributos_vertice* pertence, list<Atributos_vertice*> &destino) {
	for (list<Atributos_vertice*> l: caminho) {
		for (Atributos_vertice* v: l) {
			if (v == pertence) {
				destino = list<Atributos_vertice*>(l);
				return;
			}
		}
	}
}

bool contem__(Atributos_vertice* x, list<Atributos_vertice*> lista) {
	for (Atributos_vertice* v: lista)
		if (v == x)
			return true;

	return false;
}

void Anel::adicionar_elemento(vector<list<Atributos_vertice*>> caminho, list<list<int>> casamentos_, list<Juncao*> juncoesUtilizadas, bool realizado) {
	//Adiciona todos os vertices ao anel
	for (list<Atributos_vertice*> lista: caminho)
		for (Atributos_vertice* i: lista)
			vertices.push_back(i);

	for (Juncao* j: juncoesUtilizadas) {
		vertices.push_back(j -> juncao);
		juncoes.push_back(j -> juncao);
	}

	//Adiciona todos os caminhos percorridos pelas juncoes
	for (Juncao* j: juncoesUtilizadas) {
		list<Atributos_vertice*> novo_caminho;
		novo_caminho.push_back(j -> juncao);

		list<Atributos_vertice*> caminho_aux;
		encontrar_caminho(caminho, j -> primeiro, caminho_aux);
		for (Atributos_vertice* v: caminho_aux)
			novo_caminho.push_front(v);

		caminho_aux.clear();
		encontrar_caminho(caminho, j -> segundo, caminho_aux);
		for (Atributos_vertice* v: caminho_aux)
			novo_caminho.push_back(v);

		caminhos.push_back(novo_caminho);
	}

	//Adiciona os casamentos ao Anel
	for(list<int> l: casamentos_) {
		list<Atributos_vertice*> novo_casamento;
		for (int i: l) {
			for (Atributos_vertice* v: vertices) {
				if (v -> id == i) {
					novo_casamento.push_back(v);
					break;
				}
			}
		}
		casamentos.push_back(novo_casamento);
	}


	//Escolhe o primeiro elemento do anel
	Atributos_vertice* proximo;
	if (casamentos.front().front() -> tipo == 't')
		proximo = casamentos.front().front();
	else
		proximo = casamentos.front().back();

	//Define ordem do anel
	list<list<Atributos_vertice*>> caminhos_aux(caminhos);
	list<list<Atributos_vertice*>> casamentos_aux(casamentos);
	list<Atributos_vertice*> remover;
	while(caminhos_aux.size() > 0) {
		//Encontra o caminho da juncao que proximo pertence e o adiciona ao anel
		for (list<Atributos_vertice*> l: caminhos_aux) {
			if (l.front() == proximo) {
				remover = l;
				for (Atributos_vertice* v: l)
					anel.push_back(v);
				proximo = l.back();
				break;
			} else if (l.back() == proximo) {
				remover = l;
				l.reverse();
				for (Atributos_vertice* v: l)
					anel.push_back(v);
				proximo = l.back();
				break;
			}
		}
		caminhos_aux.remove(remover);

		//Encontra o casamento com o ultimo elemento adicionado ao anel
		for (list<Atributos_vertice*> l: casamentos_aux) {
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
	if (casamentos.size() == 2) {
		//Calcula o numero da geracao do primeiro e segundo ego
		int num = 0;
		bool segundo = false;
		int num_2 = 0;
		Atributos_vertice* ultimo = anel.front();
		for (Atributos_vertice* v: anel) {
			if (contem__(v, ultimo -> filhos)) {
				num--;
			} else if (contem__(v, ultimo -> pais)) {
				num++;
			} else if (contem__(v, ultimo -> casados)) {
				ultimo = v;
				if (segundo)
					break;
				segundo = true;
				num_2 = num;
				num = 0;
			}
			ultimo = v;
		}

		//Se segundo ego tem geracao maior, inverte a ordem dos casamentos
		bool res = num_2 < 0 ? num_2 < num : num_2 > num;
		if (num_2 < num  && !realizado) {
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
	for (Atributos_vertice* v: anel) {
		linha_normal += to_string(v -> numero);
		linha_normal += " ";
	}
	linha_normal += "\n";
}

void Anel_aux::mudar_tamanho(int tamanho) {
	juncoes.resize(tamanho);
	caminhos_primeiro.resize(tamanho);
	caminhos_segundo.resize(tamanho);
}

//Nodo dominadores
Nodo_dominadores::Nodo_dominadores(Atributos_vertice* v) {
	id = v -> id;
	atributo = v;
}
void Nodo_dominadores::adicionar_sucessor_d_arv(Nodo_dominadores* d) {
	sucessores_d_arv.remove(d);
	sucessores_d_arv.push_back(d);
}
void Nodo_dominadores::adicionar_antecessor_d_arv(Nodo_dominadores* d) {
	antecessores_d_arv.remove(d);
	antecessores_d_arv.push_back(d);
}
void Nodo_dominadores::remover_sucessor_d_arv(Nodo_dominadores* d) {
	sucessores_d_arv.remove(d);
}
void Nodo_dominadores::se_tornar_filho_de_d_arv(Nodo_dominadores* d) {
	for (Nodo_dominadores* n: antecessores_d_arv)
		n -> remover_sucessor_d_arv(this);
	antecessores_d_arv.clear();
	adicionar_antecessor_d_arv(d);
	d -> adicionar_sucessor_d_arv(this);
}
bool Nodo_dominadores::contem_d_arv(Nodo_dominadores* d) {
	if (d == this)
		return true;

	for (Nodo_dominadores* n: sucessores_d_arv)
		if (n -> contem_d_arv(d))
			return true;

	return false;
}
Nodo_dominadores* Nodo_dominadores::primeiro_antecessor_d_arv() {
	return antecessores_d_arv.front();
}
int Nodo_dominadores::tamanho_predecessores_d_arv() {
	return antecessores_d_arv.size();
}
void Nodo_dominadores::adicionar_sucessor_a_arv(Nodo_dominadores* a) {
	sucessores_a_arv.remove(a);
	sucessores_a_arv.push_back(a);
}
void Nodo_dominadores::adicionar_antecessor_a_arv(Nodo_dominadores* a) {
	antecessores_a_arv.remove(a);
	antecessores_a_arv.push_back(a);
}
void Nodo_dominadores::remover_sucessor_a_arv(Nodo_dominadores* a) {
	sucessores_a_arv.remove(a);
}
bool Nodo_dominadores::contem_a_arv(Nodo_dominadores* a) {
	if (a == this)
		return true;

	for (Nodo_dominadores* n: sucessores_a_arv)
		if (n -> contem_a_arv(a))
			return true;

	return false;
}
int Nodo_dominadores::max_caminho_a_arv() {
	int max = 1;
	int cam = 0;
	for (Nodo_dominadores* d: sucessores_a_arv) {
		cam = d -> max_caminho_a_arv();
		max = cam >= max ? cam + 1 : max;
	}

	return max;
}
void Nodo_dominadores::print_filhos_a_arv() {
	if (sucessores_a_arv.size() > 0) {
		printf("%d: ", atributo -> numero);
		for (Nodo_dominadores* d: sucessores_a_arv) {
			printf("%d ", d -> atributo -> numero);
		}
		printf("\n");

		for (Nodo_dominadores* d: sucessores_a_arv) {
			d -> print_filhos_a_arv();
		}
	}
}
void Nodo_dominadores::pos_ordem_a_arv(list<Nodo_dominadores*> &destino) {
	for (Nodo_dominadores* d: sucessores_a_arv)
		d -> pos_ordem_a_arv(destino);
	destino.push_back(this);
}

//A_arvore
A_arvore::A_arvore(list<Nodo_dominadores*> raizes_) {
	raizes = list<Nodo_dominadores*>(raizes_);

	ancestrais = vector<vector<Nodo_dominadores*>> (raizes.size(), vector<Nodo_dominadores*> (raizes.size(), NULL)); 	//Talvez max = log raizes.size()
}
void A_arvore::link(Nodo_dominadores* u, Nodo_dominadores* v) {
	ancestrais[u -> id][0] = v;

	u -> adicionar_antecessor_a_arv(v);
	v -> adicionar_sucessor_a_arv(u);

	raizes.remove(u);
}
Nodo_dominadores* A_arvore::get_ancestor(Nodo_dominadores* u, int i) {
	if (ancestrais[u -> id][i - 1] == NULL)
		ancestrais[u -> id][i] = get_ancestor(get_ancestor(u, i - 1), i - 1);

	return ancestrais[u -> id][i];
}
Nodo_dominadores* A_arvore::find(Nodo_dominadores* u, Nodo_dominadores* v, int i, int d) {
	if (i == 0)
		return ancestrais[u -> id][0];

	if (get_ancestor(u, i - 1) == get_ancestor(v, i - 1))
		return find(u, v, i - 1, d);

	int calc = log2(d - pow(2, i - 1));
	calc = calc > i - 1 ? i - 1 : calc;

	return find(get_ancestor(u, i - 1), get_ancestor(v, i - 1), calc, d - pow(2, i - 1));
}
Nodo_dominadores* A_arvore::lowest(Nodo_dominadores* u, Nodo_dominadores* v, D_arvore* arv)  {
	if (arv -> depth(v) > arv -> depth(u)) {
		Nodo_dominadores* aux_n = u;
		u = v;
		v = aux_n;
	}

	Nodo_dominadores* x = raiz(u);
	Nodo_dominadores* y = raiz(v);

	if (x != y || x == NULL) {
		printf("Erro em lowest_a\n");
		return NULL;
	}


	Nodo_dominadores* aux = u;
	Nodo_dominadores* anterior = u;
	int d = arv -> depth(u) - arv -> depth(v);
	int j;
	while (d > 0 && aux != NULL) {
		j = log2(d);
		anterior = aux;
		aux = get_ancestor(aux, j);	//Ancestor?
		d = d - pow(2, j);
	}

	if (aux == NULL)
		return anterior;

	return aux;

}
Nodo_dominadores* A_arvore::raiz(Nodo_dominadores* u) {
	for (Nodo_dominadores* d: raizes)
		if (d -> contem_a_arv(u)) {
			return d;
		}

	return NULL;
}

D_arvore::D_arvore(list<Nodo_dominadores*> raizes_) {
		raizes = list<Nodo_dominadores*>(raizes_);
}
Nodo_dominadores* D_arvore::raiz(Nodo_dominadores* u) {
	for (Nodo_dominadores* d: raizes)
		if (d -> contem_d_arv(u)) {
			return d;
		}
	return NULL;
}

int D_arvore::depth(Nodo_dominadores* u) {
	int depth = 0;
	list<Nodo_dominadores*> caminho;
	Nodo_dominadores* ultimo = u;

	caminho.push_back(ultimo);
	while(ultimo -> tamanho_predecessores_d_arv() > 0) {
		ultimo = ultimo -> primeiro_antecessor_d_arv();
		caminho.push_back(ultimo);
	}

	for(Nodo_dominadores* d: caminho)
		depth += d -> weigth;

	int i = 0;
	Nodo_dominadores* p = NULL;
	if (caminho.size() > 0) {
		caminho.reverse();

		p = caminho.front();
	}
	for (Nodo_dominadores* d: caminho) {
		if (i >= 2) {
			d -> weigth = d -> weigth + p -> weigth;
			d -> se_tornar_filho_de_d_arv(ultimo);
		} else {
			i++;
			p = d;
		}
	}

	return depth;
}
void D_arvore::merge(Nodo_dominadores* u, Nodo_dominadores* v) {
	Nodo_dominadores* x = raiz(u);
	Nodo_dominadores* y = raiz(v);

	int depth_u = depth(u);
	int depth_v = depth(v);

	if (x -> count <= y -> count) {
		x -> se_tornar_filho_de_d_arv(y);
		y -> count = y -> count + x -> count;
		x -> weigth = x -> weigth + depth(v) + 1 - y -> weigth;
		raizes.remove(x);
	} else if (x -> count > y -> count) {
		y -> se_tornar_filho_de_d_arv(x);
		x -> count = y -> count + x -> count;
		x -> weigth = x -> weigth + depth(v) + 1;
		y -> weigth = y -> weigth - x -> weigth;
		raizes.remove(y);
	}
}
Nodo_dominadores* D_arvore::lowest(Nodo_dominadores* u, Nodo_dominadores* v, A_arvore* arv) {
	if (depth(v) > depth(u)) {
		Nodo_dominadores* aux_n = u;
		u = v;
		v = aux_n;
	}

	Nodo_dominadores* x = raiz(u);
	Nodo_dominadores* y = raiz(v);
	if (x != y || x == NULL) {
		printf("Erro em lowest_a\n");
		return NULL;
	}


	Nodo_dominadores* aux = u;
	Nodo_dominadores* ultimo;
	int d = depth(u) - depth(v);
	int j;
	while (d > 0 && aux != NULL) {
		j = log2(d);
		ultimo = aux;
		aux = arv -> ancestrais[aux -> id][j];	//arv -> get_ancestor(aux, j);
		d = d - pow(2, j);
	}

	if (aux == NULL)
		return ultimo;

	return aux;
}

Region::Region(Nodo_dominadores* header_) {
	header = header_;
	membros.push_back(header);
}

void Region::juntar(Region* r) {
	sucessores.remove(r);
	for(Nodo_dominadores* m: r -> membros) {
		membros.remove(m);
		membros.push_back(m);
	}
	for(Region* s: r -> sucessores) {
		sucessores.remove(s);
		sucessores.push_back(s);
		s -> antecessores.remove(r);
		s -> antecessores.remove(this);
		s -> antecessores.push_back(this);
	}
}
