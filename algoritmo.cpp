#include "algoritmo.h"

void busca_em_largura_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz)
{
	//Atributos
	queue<Vertice*> fila;
	list<Vertice*> sem_set;
	Atributos_largura_lista* atributos;
	Vertice* atual;
	Nodo* aux;

	//Alocacao do espaco para  os atributos
	for (Vertice* v: grafo)
	{
		atributos = (Atributos_largura_lista*) malloc(sizeof(Atributos_largura_lista));
		atributos -> cor = 0;
		atributos -> nodo = new Nodo(v);
		v-> ponteiro = atributos;
		sem_set.push_back(v);
	}

	while (!sem_set.empty())
	{
		//Primeiro vertice que nao esta em nenhuma arvore
		atual = sem_set.front();
		sem_set.pop_front();

		//Vertice sera uma raiz
		aux = ((Atributos_largura_lista* )atual -> ponteiro) -> nodo;
		raiz.push_back(aux);

		//Marca vertice
		((Atributos_largura_lista* )atual -> ponteiro) -> cor = 1;
		fila.push(atual);

		//Procura os alcancaveis por ele
		while (!fila.empty())
		{
			atual = fila.front();
			fila.pop();
			aux = ((Atributos_largura_lista* )atual -> ponteiro) -> nodo;
			for (Vertice* v: atual -> filhos)
			{
				if (((Atributos_largura_lista* )v -> ponteiro) -> cor == 0) {
					((Atributos_largura_lista* )v -> ponteiro) -> cor = 1;
					((Atributos_largura_lista* )v -> ponteiro) -> nodo -> adicionar_antecessor(aux);
					fila.push(v);

				}
			}
			sem_set.remove(atual);
		}
	}

	//Liberacao do espaco alocado aos ponteiros
	for (Vertice* v: grafo)
	{
		free(v -> ponteiro);
	}
}

void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, list<Nodo*>& raiz)
{
	//Atributos
	Atributos_profundidade_lista* atributos;

	//Alocacao do espaco para  os atributos
	for (Vertice* v: grafo)
	{
		atributos = (Atributos_profundidade_lista*) malloc(sizeof(Atributos_profundidade_lista));
		atributos -> cor = 0;
		v-> ponteiro = atributos;
	}

	Nodo* aux;

	for (Vertice* v: grafo)
	{
		if (((Atributos_profundidade_lista*) v -> ponteiro) -> cor == 0) {
			//Vertice sera uma raiz
			aux = new Nodo(v);
			((Atributos_profundidade_lista* )v -> ponteiro) -> nodo = aux;
			raiz.push_back(aux);


			((Atributos_profundidade_lista* )v -> ponteiro) -> tempo = 0;
			busca_em_profundidade_listas_adjacencia(grafo, v);
		}
	}

	//Liberacao do espaco alocado aos atributos
	for (Vertice* v: grafo)
	{
		free(v -> ponteiro);
	}
}

void busca_em_profundidade_listas_adjacencia(list<Vertice*>& grafo, Vertice* v)
{
	((Atributos_profundidade_lista* )v -> ponteiro) -> cor = 1;
	Nodo* aux;
	Nodo* aux1;
	Atributos_profundidade_lista* att_v = ((Atributos_profundidade_lista* )v -> ponteiro);
	Atributos_profundidade_lista* att_vertice;

	for (Vertice* vertice: v -> filhos)
	{
		att_vertice = (Atributos_profundidade_lista*) vertice -> ponteiro;
		if (att_vertice -> cor == 0) {
			aux1 = ((Atributos_profundidade_lista*) v -> ponteiro) -> nodo;
			aux = new Nodo(vertice);
			aux -> adicionar_antecessor(aux1);
			aux1 -> adicionar_sucessor(aux);

			att_vertice -> cor = 1;
			att_vertice -> tempo = att_v -> tempo + 1;
			busca_em_profundidade_listas_adjacencia(grafo, vertice);
		}
	}
}

void busca_em_largura(int** grafo, int tamanho, int* arvore)
{
	int vertice;
	queue<int> fila;
	list<int> sem_set;

	//Inicia os atributos de cada vertice
	Atributos_largura* atributos_vertices[tamanho];
	Atributos_largura* atributo;
	for (int i = 0; i < tamanho; i++)
	{
		sem_set.push_back(i);
		atributo = (struct Atributos_largura*) malloc(sizeof(struct Atributos_largura));
		atributo->cor = 0;
		atributo->distancia_fonte =-1;
		atributo->predecessor = -1;
		atributos_vertices[i] = atributo;
	}

	//Enquanto tem vertices que nao pertencem a nenhuma arvore continua busca
	while(!sem_set.empty())
	{
		vertice = sem_set.front();	//pega um vertice que nao pertence a nenhuma arvore
		sem_set.pop_front();

		atributos_vertices[vertice]->cor = 1;
		atributos_vertices[vertice]->distancia_fonte = 0;
		fila.push(vertice);
		arvore[vertice] = -1;
		while(!fila.empty())
		{
			vertice = fila.front();
			fila.pop();
			for (int i = 0; i < tamanho; i++) {
				if (grafo[vertice][i] == 1)
				{
					if (atributos_vertices[i]->cor == 0)
					{
						atributos_vertices[i]->cor = 1;
						atributos_vertices[i]->distancia_fonte = atributos_vertices[vertice]->distancia_fonte + 1;
						atributos_vertices[i]->predecessor = vertice;

						arvore[i] = vertice;
						fila.push(i);
						sem_set.remove(i);
					}
					atributos_vertices[vertice]->cor = 2;
				}
			}	//fim for(i)
		}	//fim while(!fila.empty())
	}	//fim while(!sem_set.empty())

	//desaloca os atributos
	for(int i = 0; i < tamanho; i++)
	{
		free (atributos_vertices[i]);
	}
}

void busca_em_profundidade(int**grafo, int tamanho, int* arvore)
{
	list<int> sem_set;
	int vertice;

	//define os atributos dos vertices
	Atributos_profundidade* atributos_vertices[tamanho];
	Atributos_profundidade* atributo;
	for (int i = 0; i < tamanho; i++)
	{
		sem_set.push_back(i);
		atributo = (struct Atributos_profundidade*) malloc(sizeof(struct Atributos_profundidade));
		atributo->cor = 0;
		atributo->tempo_init =0;
		atributo->tempo_fim = 0;
		atributo->predecessor = 0;
		atributos_vertices[i] = atributo;
	}

	while(!sem_set.empty())
	{
		vertice = sem_set.front();
		sem_set.pop_front();

		tempo = 0;
		arvore[vertice] = -1;
		busca_em_profundidade(grafo, tamanho, atributos_vertices, vertice, arvore, sem_set);
	}

	//desaloca os atributos
	for(int i = 0; i < tamanho; i++)
	{
		free (atributos_vertices[i]);
	}
}

void busca_em_profundidade(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice, int* arvore, list<int>& sem_set)
{
	atributos_vertices[vertice]->tempo_init = ++tempo;
	atributos_vertices[vertice]->cor = 1;

	for(int i = 0; i < tamanho; i++)
	{
		if(grafo[vertice][i] == 1)
		{
			if(atributos_vertices[i]->cor == 0)
			{
				atributos_vertices[i]->predecessor = vertice;
				arvore[i] = vertice;
				sem_set.remove(i);
				busca_em_profundidade(grafo, tamanho, atributos_vertices, i, arvore, sem_set);
			}
		}
	}
	atributos_vertices[vertice]->cor = 2;
	atributos_vertices[vertice]->tempo_fim = ++tempo;
}

void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino)
{
	list<int> lista;
	list<int> sem_set;
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

		busca_em_largura(grafo, tamanho, lista, vertice);

		//cria componente
		list<int> matriz;

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

void busca_em_largura(int** grafo, int tamanho, list<int>& destino, int fonte)
{
	int vertice;
	queue<int> fila;
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
			if (grafo[i][vertice] == 2 || grafo[i][vertice] == 12)
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
	{
		if(atributos_vertices[i]->cor)
			destino.push_back(i);
		free(atributos_vertices[i]);
	}

}

void encontra_casamento_irmaos(int** grafo, int tamanho, list<list<int>>& destino)
{
	list<int> casamento;
	for (int i = 0; i < tamanho; i++) {
		for (int y = 0; y < i; y++) {
			if (grafo[i][y] == 1) {
				if (verifica_irmaos(grafo, tamanho, i, y)) {
					casamento = list<int>();
					casamento.push_back(i);
					casamento.push_back(y);

					destino.push_back(casamento);
				}
			}
		}
	}
}

bool verifica_irmaos(int** grafo,int tamanho,int a,int b)
{
	list<int> pais_a;
	for (int i = 0; i < tamanho; i++)
	{
		if (grafo[a][i] == 3 || grafo[a][i] == 13) {
			pais_a.push_back(i);
		}
	}

	for (int i: pais_a)
	{
		if (grafo[b][i] == 3 || grafo[b][i] == 13) {
			return true;
		}
	}

	return false;
}

void colorir_grafo(Grafo* g)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_grafo(), matriz invalida");

	//Busca fontes
	list<int> fontes;
	busca_fontes(grafo, g -> g_numero_vertices(), fontes);

	//Colore apartir das fontes
	for (int i: fontes)
		colorir_apartir_de(g, i);
}

void busca_fontes(int** grafo, int tamanho, list<int>& destino)
{
	bool eh_fonte;
	for (int i = 0; i < tamanho; i++)
	{
		eh_fonte = true;
		for (int y = 0; y < tamanho; y++)
		{
			if (grafo[i][y] == 3 || grafo[i][y] == 13)
				{eh_fonte = false; break;}	//Vertice i tem um arco chegando nele
		}
		if (eh_fonte) {destino.push_back(i);}	//adiciona i como fonte na lista
	}
}

void colorir_apartir_de(Grafo* g, int vertice)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_apartir_de(), matriz invalida");

	//Atributos
	queue<int> fila;
	int tamanho = g -> g_numero_vertices();
	int vertice_atual;
	Atributos_largura* atributos_vertices[tamanho];
	Atributos_largura* atributo;

	//Alocacao do espaco para Atributos_largura
	for (int i = 0; i < tamanho; i++)
	{
		atributo = (struct Atributos_largura*) malloc(sizeof(struct Atributos_largura));
		atributo->cor = 0;
		atributos_vertices[i] = atributo;
	}

	//Vertice inicial
	atributos_vertices[vertice] -> cor = 1;
	fila.push(vertice);

	while(!fila.empty())
	{
		//Remove primeiro da fila
		vertice_atual = fila.front();
		fila.pop();
		for (int i = 0; i < tamanho; i++)
		{
			if (grafo[vertice_atual][i] == 2 || grafo[vertice_atual][i] == 12) {		//Arco da forma vertice_atual -> i
				if (atributos_vertices[i] -> cor == 0)	//Se i nao esta marcado
				{
					atributos_vertices[i] -> cor = 1;
					fila.push(i);
				}
			}
		}
	}

	//Coloracao dos vertices alcancados e liberacao do espaco alocado
	for (int i = 0; i < tamanho; i++)
	{
		if (atributos_vertices[i] -> cor == 1)
		{
			g -> encontrar_atributo(i) -> adicionar_cor(vertice);
		}
		free(atributos_vertices[i]);
	}
}

void colorir_grafo_mat(Grafo* g)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_grafo_mat(), matriz invalida");

	//Busca fontes
	list<int> fontes;
	busca_fontes_tipo(g, 'e', fontes);


	//Colore apartir das fontes
	for (int i: fontes)
		colorir_apartir_de_tipo(g, i, 'e');
}

void colorir_grafo_pat(Grafo* g)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_grafo_pat(), matriz invalida");

	//Busca fontes
	list<int> fontes;
	busca_fontes_tipo(g, 't', fontes);


	//Colore apartir das fontes
	for (int i: fontes)
		colorir_apartir_de_tipo(g, i, 't');
}

void busca_fontes_tipo(Grafo* g, char tipo, list<int>& destino)
{
	bool eh_fonte;
	int tamanho = g -> g_numero_vertices();
	int** grafo = g-> grafo;
	if (!grafo)	throw runtime_error("Erro em busca_fontes_tipo(), matriz invalida");

	for (int i = 0; i < tamanho; i++)
	{
		eh_fonte = true;
		for (int y = 0; y < tamanho; y++)
		{
			if (grafo[i][y] == 3 || grafo[i][y] == 13)
				{eh_fonte = false; break;}	//Vertice i tem um arco chegando nele
		}
		if (eh_fonte && g -> encontrar_atributo(i) -> g_tipo() == tipo)
			{destino.push_back(i);}	//adiciona i como fonte na lista
	}
}

void colorir_apartir_de_tipo (Grafo* g, int vertice, char tipo)
{
	int** grafo = g -> grafo;
	if (!grafo)	throw runtime_error("Erro em colorir_apartir_de_tipo(), matriz invalida");

	//Atributos
	queue<int> fila;
	int tamanho = g -> g_numero_vertices();
	int vertice_atual;
	Atributos_largura* atributos_vertices[tamanho];
	Atributos_largura* atributo;

	//Alocacao do espaco para Atributos_largura
	for (int i = 0; i < tamanho; i++)
	{
		atributo = (struct Atributos_largura*) malloc(sizeof(struct Atributos_largura));
		atributo->cor = 0;
		atributos_vertices[i] = atributo;
	}

	//Vertice inicial
	atributos_vertices[vertice] -> cor = 1;
	fila.push(vertice);

	while(!fila.empty())
	{
		//Remove primeiro da fila
		vertice_atual = fila.front();
		fila.pop();
		for (int i = 0; i < tamanho; i++)
		{
			if (grafo[vertice_atual][i] == 2 || grafo[vertice_atual][i] == 12) {		//Arco da forma vertice_atual -> i
				if (atributos_vertices[i] -> cor == 0)	//Se i nao esta marcado
				{
					atributos_vertices[i] -> cor = 1;
					if (g -> encontrar_atributo(i) -> g_tipo() == tipo)
						fila.push(i);
				}
			}
		}
	}

	//Coloracao dos vertices alcancados e liberacao do espaco alocado
	for (int i = 0; i < tamanho; i++)
	{
		if (atributos_vertices[i] -> cor == 1)
		{
			g -> encontrar_atributo(i) -> adicionar_cor(vertice);
		}
		free(atributos_vertices[i]);
	}
}

void descolorir(Grafo* g)
{
	for (Vertice* v: g -> atributos)
	{
		v -> cor.clear();
		v -> cores.clear();
		v -> cor_int = 0;
		v -> cores_ate_folha = 1;
	}
}

void define_max_cores(Grafo* g)
{
	init_map(g);	//Coloca cores em g -> map

	//Encontra raiz de g(se não existe cria artificial)
	Vertice* raiz;
	list<Vertice*> raizes;
	encontra_raizes(g, raizes);
	bool raiz_artificial = false;
	if (raizes.size() > 1) {
		raiz_artificial = true;
		raiz = new Vertice(g -> g_numero_vertices(), -1, 'u');
		for (Vertice* v: raizes) {
			raiz -> adicionar_filho(v);
			v -> adicionar_pais(raiz);
		}
		g -> adicionar_vertice(raiz);
	} else if (raizes.size() == 1)
		raiz = raizes.front();
	else
		return;

	Cor* cor;
	Hash* map = g -> map;
	//Adiciona cores para os folhas
	for (Vertice* v: g -> atributos) {
		if (v -> filhos.size() == 0) {
			cor = map -> encontrar_cor(v -> cor);
			if (!cor)
				throw runtime_error("Erro em define_max_cores(), cor não encontrada");

			set<int> cor_v;
			cor_v.insert(cor->to_int());
			set<set<int>, set_cmp> novo;
			novo.insert(cor_v);
			v -> cores = novo;
		} else {
			set<set<int>, set_cmp> novo;
			v -> cores = novo;
		}
	}

	//Ordenação topologica
	list<Vertice*> ordenacao_topologica;
	ordem_topologica(g, raiz, ordenacao_topologica);

	//Algoritmo
	for (Vertice* v: ordenacao_topologica) {
		//Calcula super
		v -> cores_ate_folha = 0;
		for (set<int> s: v -> cores)
			if (s.size() > v -> cores_ate_folha)
				v -> cores_ate_folha = s.size();

		//Passa cores para os pais
		for (Vertice* w: v -> pais) {
			if (w == raiz)
				continue;
			for (set<int> conjunto: v -> cores) {
				set<int> novo(conjunto);
				cor = map -> encontrar_cor(w -> cor);
				novo.insert(cor -> to_int());
				w -> cores.insert(novo);
			}
		}
	}

	//Se raiz artificial foi criada, a exclui
	if (raiz_artificial) {
		g -> remover_vertice(raiz);
		for (Vertice* v: raizes) {
			raiz -> filhos.remove(v);
			v -> pais.remove(raiz);
		}

		delete raiz;
	}
}

void init_map(Grafo* g)
{
	if (!g -> map) {
		g -> map = new Hash();
		reinicia_cores();
	}
	Hash* map = g -> map;

	//Atributos para coloracao
	Cor* cor;
	Cor* aux;
	string rgb;
	string lin;

	//Percorre Vertices e escreve as cores
	for (Vertice* a: g -> atributos)
	{
		cor = map -> encontrar_cor(a -> cor);

		if (!cor) {	//Primeira ocorrencia do set
			//Para cada cor que coloriu o vertice
			for (int cor_n: a -> cor)
			{
				aux = map -> encontrar_cor(cor_n);	//Encontra cor
				//Se cor nao tiver sido encontrada ainda
				if (!aux) {
					string cor = primeira_cor();
					if (cor == "") //Se o numero de cores colocado na lista cores e muito pequeno
					{ throw runtime_error("Erro em init_map(), Falta Cores!"); }
						//Pega a primeira cor
					rgb = cor;

					//Inicia uma nova cor e a adiciona ao hash
					aux = new Cor(rgb);
					map -> adicionar_cor(cor_n, aux);
				}

				if (!cor) {	//Se esta passando pela primeira vez copia a cor de aux
					cor = new Cor(aux);
				} else {	//Se ja tem cor definida realiza a soma da cor atual com a de aux
					cor -> soma(aux);
				}
			}
			if (!cor) {	//Vertice n tem cor, adiciona cor especial
				a -> cor.insert(-1);
				cor = map -> encontrar_cor(a -> cor);
				if (!cor) {
					cor = new Cor("#BD9A9A");
					map -> adicionar_cor(a -> cor, cor);
				}
				continue;
			}
			map -> adicionar_cor(a -> cor, cor);
		}

		a -> cor_int = cor -> to_int();
	}
}

void encontra_raizes(Grafo* g, list<Vertice*>& destino)
{
	for (Vertice* v: g -> atributos)
		if (v -> pais.size() == 0)
			destino.push_back(v);
}

void ordem_topologica(Vertice* fonte, stack<Vertice*>& destino)
{
	fonte -> valor_bool = true;

	//Busca em profundidade todos os filhos
	for (Vertice* filho: fonte -> filhos) {
		if (!filho -> valor_bool)
			ordem_topologica(filho, destino);
	}

	//Quando termina busca de todos os filhos, insere vertice na pilha
	destino.push(fonte);
}

template<typename T>
void ordem_topologica(Vertice* fonte, T& destino)
{
	fonte -> valor_bool = true;

	//Busca em profundidade todos os filhos
	for (Vertice* filho: fonte -> filhos) {
		if (!filho -> valor_bool)
			ordem_topologica(filho, destino);
	}

	//Quando termina busca de todos os filhos, insere vertice na pilha
	destino.push_back(fonte);
}

void define_min_max_cores(Grafo* g)
{
	init_map(g);

	for (Vertice* v: g -> atributos) {
		v -> min_cores = vector<int>(g -> g_numero_vertices(), INT_MAX);
		v -> max_cores = vector<int>(g -> g_numero_vertices(), 0);
	}

	for (Vertice* v: g -> atributos) {
		set<int> colors;
		procedimento_min_max(v, v, colors);
		for (int i = 0; i < g -> g_numero_vertices(); i++) {
			if (v -> min_cores[i] == INT_MAX)
				v -> min_cores[i] = -1;
		}
	}

}

void procedimento_min_max(Vertice* f, Vertice* a, set<int> colors)
{
	colors.insert(a -> cor_int);

	if (f -> min_cores[a -> g_id()] > colors.size())
		f -> min_cores[a -> g_id()] = colors.size();

	if (f -> max_cores[a -> g_id()] < colors.size())
		f -> max_cores[a -> g_id()] = colors.size();


	for (Vertice* v: a -> filhos)
		procedimento_min_max(f, v, colors);
}

template<typename T>
void ordem_topologica(Grafo* g, Vertice* fonte, T& destino)
{
	g -> resetar();

	ordem_topologica(fonte, destino);
}

void encontra_juncoes(Grafo* g, list<Juncao*>& destino)
{
	stack<Vertice*> vs;

	for(Vertice* s: g -> atributos)
	{
		ordem_topologica(g, s, vs);
		g -> resetar();

		s -> valor_int = s -> g_id();
		vs.pop();

		Vertice* v;
		while(!vs.empty())
		{
			v = vs.top();
			vs.pop();

			if (v -> pais.size() == 2) {
				if ((v -> pais.front() -> valor_int == -1) && (v -> pais.back() -> valor_int == -1)) {
					throw runtime_error("Erro em encontra_juncoes(), Ambos pais de vertice nao mapeados");
				} else if (v -> pais.front() -> g_id() == s -> g_id() || v -> pais.back() -> g_id() == s -> g_id()) {
					v -> valor_int = v -> g_id();
				} else if (v -> pais.front() -> valor_int == -1) {
					v -> valor_int = v -> pais.back() -> valor_int;
				} else if (v -> pais.back() -> valor_int == -1) {
					v -> valor_int = v -> pais.front() -> valor_int;
				} else if (v -> pais.front() -> valor_int != v -> pais.back() -> valor_int) {
					v -> valor_int = v -> g_id();
				} else {
					v -> valor_int = v -> pais.front() -> valor_int;
				}

			} else if (v -> pais.size() == 1) {
				if (v -> pais.front() -> g_id() == s -> g_id())
					v -> valor_int = v -> g_id();
				else
					v -> valor_int = v -> pais.front() -> valor_int;
			} else {
				throw runtime_error("Erro em encontra_juncoes(), Vertice fonte no meio da ordenação");
			}
		}

		//Juncoes
		Vertice* a1;
		Vertice* a2;
		for (int i = 0; i < g -> g_numero_vertices(); i++)
		{
			a1 = g -> atributos[i];
			if (a1 -> valor_int != -1)
				for (int j = i + 1; j < g -> g_numero_vertices(); j++)
				{
					a2 = g -> atributos[j];
					if (a2 -> valor_int != -1)
						if (a1 -> valor_int != a2 -> valor_int)
							destino.push_back(new Juncao(a1, a2, s));
				}
		}
	}
}

void encontra_juncoes(Grafo* g, list<JuncoesDe*>& destino)
{
	list<Juncao*> juncoes;
	encontra_juncoes(g, juncoes);

	//JuncoesDe* jun[g -> g_numero_vertices()][g->numero_vertices];
	vector<vector<JuncoesDe*>> jun(g -> g_numero_vertices(), vector<JuncoesDe*> (g -> g_numero_vertices()));
	JuncoesDe* aux;

	Vertice* e1;
	Vertice* e2;
	for (int i = 0; i < g -> g_numero_vertices(); i++) {
		for (int j = i + 1; j < g -> g_numero_vertices(); j++) {
			e1 = g -> atributos[i];
			e2 = g -> atributos[j];
			aux = new JuncoesDe(e1, e2);

			jun[i][j] = aux;
			jun[j][i] = aux;
			destino.push_back(aux);
		}
	}

	for (Juncao* j: juncoes)
		jun[j -> primeiro -> g_id()][j -> segundo -> g_id()] -> adicionar_juncao(j -> juncao);
}

void encontra_juncoes(Grafo* g, Juncoes* destino)
{
	list<JuncoesDe*> l;
	encontra_juncoes(g, l);

	for (JuncoesDe* j: l)
		destino -> adicionarJuncoes(j);

}

void encontra_arvore_dominadores(Grafo* g, vector<Vertice*> &dominadores_imediatos)
{
	//Criação de atributo "Raiz" que se liga aos raizes de g
	Vertice* root = new Vertice(g -> atributos.size(), g -> g_numero_vertices(), 'z');
	list<Vertice*> raizes_g;
	encontra_raizes(g, raizes_g);
	for (Vertice* v: raizes_g) {
		v -> adicionar_pais(root);
		root -> adicionar_filho(v);
	}
	g -> adicionar_vertice(root);

	//Algoritmo que chama recursivamente
	for (Vertice* v: g -> atributos)
		v -> valor_bool = true;

	procedimento_dominadores(g, g -> atributos, root, dominadores_imediatos);

	//Retorna g ao normal
	g -> remover_vertice(root);
	for (Vertice* v: raizes_g) {
		v -> pais.remove(root);
	}
}

void procedimento_dominadores(Grafo *g, vector<Vertice*> u, Vertice* s, vector<Vertice*> &dominadores_imediatos)
{
	//Array fd de retorno de cobertura_dominadores
	vector<Vertice*> fd(g -> g_numero_vertices(), 0);
	cobertura_dominadores(g, u, s, fd);

	for (Vertice* w: fd) {
		//Para cada dominador em fd
		if (w && w -> valor_bool_2) {
			//procura todos os vertuces u | fd(u) = w
			vector<Vertice*> u_aux(g -> g_numero_vertices(), 0);
			int i = 0;
			for (Vertice* v: fd) {
				if (v == w) {
					u_aux[i] = g -> atributos[i];
				}
				i++;
			}

			w -> valor_bool_2 = false;
			procedimento_dominadores(g, u_aux, w, dominadores_imediatos);
			dominadores_imediatos[w -> g_id()] = s;
		}
	}
}

void cobertura_dominadores(Grafo* g, vector<Vertice*> u, Vertice* s, vector<Vertice*>& fd)
{
	stack<Vertice*> vs;

	for(Vertice* a: g -> atributos)
		a -> valor_bool = true;
	for(Vertice* a: u)
		if (a)
			a -> valor_bool = false;

	ordem_topologica(s, vs);

	fd[s -> g_id()] = s;
	vs.pop();

	Vertice* v;
	while(!vs.empty())
	{
		v = vs.top();
		vs.pop();

		if (v -> pais.size() == 2) {
			if ((!fd[v -> pais.front() -> g_id()]) && (!fd[v -> pais.back() -> g_id()])) {
				throw runtime_error("Erro em cobertura_dominadores(), Ambos pais de vertice nao mapeados");
			} else if (v -> pais.front() -> g_id() == s -> g_id() || v -> pais.back() -> g_id() == s -> g_id()) {
				fd[v -> g_id()] = v;
			} else if (!fd[v -> pais.front() -> g_id()]) {
				fd[v -> g_id()] = fd[v -> pais.back() -> g_id()];
			} else if (!fd[v -> pais.back() -> g_id()]) {
				fd[v -> g_id()] = fd[v -> pais.front() -> g_id()];
			} else if (fd[v -> pais.back() -> g_id()] != fd[v -> pais.front() -> g_id()]) {
				fd[v -> g_id()] = v;
			} else {
				fd[v -> g_id()] = fd[v -> pais.front() -> g_id()];
			}

		} else if (v -> pais.size() == 1) {
			if (v -> pais.front() -> g_id() == s -> g_id())
				fd[v -> g_id()] = v;
			else
				fd[v -> g_id()] = fd[v -> pais.front() -> g_id()];
		} else {
			throw runtime_error("Erro em cobertura_dominadores(), Vertice fonte no meio da ordenação");
		}
	}
}

void encontra_subgrafos(Grafo* fonte, vector<Grafo*> &subgrafos)
{
	list<Vertice*> raizes;
	encontra_raizes(fonte, raizes);

	for (Vertice* v: raizes) {
		Grafo* novo = sub_grafo(fonte, v);
		subgrafos.push_back(novo);
		printf("Subgrafo com %d como raiz, com %d vertices criado\n", v -> g_numero(), novo -> g_numero_vertices());
	}
}

int encontra_profundidade_dominadores(vector<Vertice*> dominadores, Vertice* raiz)
{
	//Muito nao otimizado
	vector<int> profundidade(dominadores.size(), 1);
	list<int> verificar;
	verificar.push_back(raiz -> g_id());

	while(!verificar.empty()) {
		int atual = verificar.front();
		verificar.remove(atual);

		int i = -1;
		for (Vertice* v: dominadores) {
			i++;
			if (v) {
				if (v -> g_id() == atual) {
					profundidade[i] = profundidade[atual] + 1;
					verificar.push_back(i);
				}
			}
		}
	}

	int retorno = 0;
	for (int i: profundidade)
		retorno = retorno > i ? retorno : i;

	return retorno;
}

int encontra_profundidade_de(Vertice* v)
{
	int profundidade = 0;
	for (Vertice* f: v -> filhos) {
		int aux = encontra_profundidade_de(f);
		profundidade = profundidade > aux ? profundidade : aux;
	}

	return profundidade + 1;
}

int encontra_profundidade_media_de(Vertice* v)
{
	if (v -> filhos.size() == 0)
		return 1;
	int sum = 0;
	for (Vertice* f: v -> filhos) {
		sum += encontra_profundidade_media_de(f);
	}

	return (sum / v -> filhos.size()) + 1;
}

void geracao_grafo_superior(Grafo* g)
{
	g -> resetar();

	list<Vertice*> raizes;
	encontra_raizes(g, raizes);

	for (Vertice* v: raizes) {
		v -> valor_int = 0;
		passar_geracao_filhos(v);
	}
}

void passar_geracao_filhos(Vertice* v)
{
	for (Vertice* x: v-> filhos) {
		x -> valor_int = v -> valor_int + 1;
		passar_geracao_filhos(x);
	}
}

void geracao_grafo_inferior(Grafo* g)
{
	for (Vertice* v: g -> atributos)
		v -> valor_int = -1;

	list<Vertice*> folhas;
	encontra_folhas(g, folhas);

	for (Vertice* v: folhas) {
		v -> valor_int = 0;
		passar_geracao_pais(v);
	}
}

void passar_geracao_pais(Vertice* v)
{
	for (Vertice* x: v-> pais) {
		x -> valor_int = v -> valor_int + 1;
		passar_geracao_pais(x);
	}
}

void encontra_folhas(Grafo* g, list<Vertice*> &destino)
{
	for (Vertice* v: g -> atributos)
		if (v -> filhos.size() == 0)
			destino.push_back(v);
}

void encontra_aneis(Grafo* g, list<Anel*> & destino, int numero_casamentos)
{
	if (numero_casamentos > 3 || numero_casamentos < 1)
		throw runtime_error("Erro em encontra_aneis(), Numero de casamentos não suportado");

	//3.1
	//Encontra todas as junções do grafo
	list<JuncoesDe*> juncoes;
	encontra_juncoes(g, juncoes);
	printf("Encontrou junções\n");
	Juncoes* jun = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, jun);

	//3.2
	//Encontra todos os casamentos do grafo (list<int> = 1 casamento)
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);
	printf("Encontrou casamentos\n");


	define_min_max_cores(g);

	//3.3
	//Define os conjuntos a serem trabalhados e operam encontrando os aneis sobre eles
	if (numero_casamentos == 1)
		encontra_aneis_a1(juncoes, casamentos, destino);
	else if (numero_casamentos == 2)
		encontra_aneis_a2(g, jun, casamentos, destino);
	else
		encontra_aneis_a3(g, juncoes, casamentos, destino);

	cout << " tempo_encontra_anel_p " << (double) tempo_encontra_anel_p << endl;
	cout << " tempo_verifica_anel " << (double) tempo_verifica_anel  << endl;
	cout << " tempo_encontra_anel " << (double) tempo_encontra_anel << endl;
	cout << " tempo_procura_caminhos " << (double) tempo_procura_caminhos  << endl;
	cout << " tempo_sao_disjuntos " << (double) tempo_sao_disjuntos << endl << endl;


	cout << " tempo_encontra_anel_p " << (double) tempo_encontra_anel_p / CLOCKS_PER_SEC << endl;
	cout << " tempo_verifica_anel " << (double) tempo_verifica_anel / CLOCKS_PER_SEC  << endl;
	cout << " tempo_encontra_anel " << (double) tempo_encontra_anel / CLOCKS_PER_SEC<< endl;
	cout << " tempo_procura_caminhos " << (double) tempo_procura_caminhos / CLOCKS_PER_SEC << endl;
	cout << " tempo_sao_disjuntos " << (double) tempo_sao_disjuntos /CLOCKS_PER_SEC << endl;
}

void encontra_casamentos(Grafo* g, vector<list<int>>& casamentos)
{
	for (int i = 0; i < g -> g_numero_vertices(); i++) {
		for (int j = i + 1; j < g -> g_numero_vertices(); j++) {
			if (g -> grafo[i][j] == 1 || g -> grafo[i][j] == 12 || g -> grafo[i][j] == 13) {
				list<int> casamento;
				casamento.push_back(i);
				casamento.push_back(j);

				casamentos.push_back(casamento);
			}
		}
	}
}

void encontra_aneis_a1(list<JuncoesDe*> juncoes, vector<list<int>> casamentos, list<Anel*>& destino)
{
	for (list<int> c: casamentos) {
		printf("Operando sobre conjunto: (%d, %d) \n", c.front(), c.back());
		//Encontra as juncoes do par
		int id_front = c.front();
		int id_back = c.back();
		JuncoesDe* par_juncao = 0;
		for (JuncoesDe* j: juncoes) {
			if (id_front == j -> primeiro -> g_id() || id_front == j -> segundo -> g_id())  {
				if (id_back == j -> primeiro -> g_id() || id_back == j -> segundo -> g_id()) {
					par_juncao = j;
					break;
				}
			}
		}

		if (!par_juncao) {
			//Nao existe juncao para o par
			printf("Casamento sem Juncao: %d e %d\n", c.front(), c.back());
			continue;
		}

		//Define anel_aux, que contem juncoes e caminhos ate par
		list<Anel_aux*> c_aneis_aux;
		Anel_aux* par_anel_aux = new Anel_aux();
		define_anel_aux(par_juncao, par_anel_aux);
		c_aneis_aux.push_back(par_anel_aux);

		//Para todo grupo de caminhos disjuntos fazer intersecção
		//Se intersecção for vazia, encontrou um anel
		list<list<int>> conjunto_c;
		list<Juncao*> juncoesUtilizadas;
		vector<list<Vertice*>> atual;
		conjunto_c.push_back(c);
		encontra_aneis(c_aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas);

		//Para cada anel aux criado excluilo
		while(c_aneis_aux.size() > 0) {
			Anel_aux* a = c_aneis_aux.front();
			c_aneis_aux.pop_front();
			delete a;
		}
		for (Juncao* j: juncoesUtilizadas)
			delete j;
	}
}

void encontra_aneis_a2(Grafo* g, Juncoes* juncoes, vector<list<int>> casamentos, list<Anel*>& destino)
{
	clock_t inicio = clock();
	//Constroi todos os conjuntos de casamentos, cada 1 com 2 casamentos
	list<list<list<int>>> conjuntos_c;
	encontra_duplas_casamentos(casamentos, conjuntos_c);

	printf("Numero de casamentos: %ld\n", casamentos.size());

	//Define conjunto c com 2 casamentos e trabalha nele
	for (list<list<int>> conjunto_c: conjuntos_c) {
		printf("Operando sobre conjunto: ");
		for (list<int> i: conjunto_c)
			printf("(%d,%d) ", i.front(), i.back());
		printf("\n");

		//Transforma casamentos em combinacoes
		//(x1,y1) (x2, y2) -> (x1,x2) (y1,y2) e (x1, y2) (y1, x2)
		list<list<list<int>>> combinacoes;
		encontra_combinacoes_dupla(conjunto_c, combinacoes);

		//Para cada possibilidade de agrupamento(combinacao)
		bool proximo = false;
		for (list<list<int>> c: combinacoes) {
			//Estrutura que armazena caminhos e juncoes para cada par em c
			list<Anel_aux*> c_aneis_aux;

			//Para cada par da combinação
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();

				//Anel auxiliar do par
				Anel_aux* par_anel_aux = new Anel_aux();
				c_aneis_aux.push_back(par_anel_aux);


				//Se par é o mesmo elemento continua busca em outros pares
				if (id_front == id_back) {
					proximo = true;	//mudar para encontrar AxCk, x != k (comentar linha)
					par_anel_aux -> primeiro = g -> encontrar_atributo(id_front);
					par_anel_aux -> segundo = par_anel_aux -> primeiro;
					continue;
				}

				//Encontra as juncoes do par
				JuncoesDe* par_juncao = juncoes -> juncoes[id_front][id_back];

				if (!par_juncao) {
					//Nao existe juncao para o par
					proximo = true;
					break;
				}
				tempo_encontra_anel_p += clock() - inicio;

				//Define caminhos disjuntos das juncoes ate o par
				define_anel_aux(par_juncao, par_anel_aux);

				inicio = clock();
			}

			//Algum par nao tem juncao
			if (proximo) {
				while(c_aneis_aux.size() > 0) {
					Anel_aux* a = c_aneis_aux.front();
					c_aneis_aux.pop_front();
					delete a;
				}
				continue;
			}

			tempo_encontra_anel_p += clock() - inicio;
			//Para todo grupo de caminhos disjuntos fazer intersecção
			//Se intersecção for vazia, encontrou um anel
			list<Juncao*> juncoesUtilizadas;
			vector<list<Vertice*>> atual;
			encontra_aneis(c_aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas);
			inicio = clock();

			//Para cada anel aux criado excluilo
			while(c_aneis_aux.size() > 0) {
				Anel_aux* a = c_aneis_aux.front();
				c_aneis_aux.pop_front();
				delete a;
			}
			for (Juncao* j: juncoesUtilizadas)
				delete j;
		}
	}

	tempo_encontra_anel_p += clock() - inicio;
}

void encontra_aneis_a3(Grafo* g, list<JuncoesDe*> juncoes, vector<list<int>> casamentos, list<Anel*>& destino)
{
	//Constroi todos os conjuntos de casamentos, cada 1 com numero_casamentos tamanho
	list<list<list<int>>> conjuntos_c;
	encontra_trios_casamentos(casamentos, conjuntos_c);

	//3.3
	//Define conjunto c com numero_casamentos casamentos e trabalha nele
	for (list<list<int>> conjunto_c: conjuntos_c) {
		printf("Operando sobre conjunto: ");
		for (list<int> i: conjunto_c)
			printf("(%d,%d) ", i.front(), i.back());
		printf("\n");

		//Transforma casamentos em combinacoes
		//(x1,y1) (x2, y2) (x3, y3) -> (x1,x2) (y2,y3) (x3, y1) && ...
		list<list<list<int>>> combinacoes;
		encontra_combinacoes_trio(conjunto_c, combinacoes);

		//Para cada possibilidade de agrupamento(combinacao)
		bool proximo = false;
		for (list<list<int>> c: combinacoes) {
			//Estrutura que armazena caminhos e juncoes para cada par em c
			list<Anel_aux*> c_aneis_aux;

			//Para cada par da combinação
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();

				//Anel auxiliar do par
				Anel_aux* par_anel_aux = new Anel_aux();
				c_aneis_aux.push_back(par_anel_aux);

				//Se par é o mesmo elemento continua busca em outros pares (AxCk, x != k)
				if (id_front == id_back) {
					proximo = true;	//mudar para encontrar AxCk, x != k (comentar linha)
					par_anel_aux -> primeiro = g -> encontrar_atributo(id_front);
					par_anel_aux -> segundo = par_anel_aux -> primeiro;
					continue;
				}

				//Encontra as juncoes do par
				JuncoesDe* par_juncao = 0;
				for (JuncoesDe* j: juncoes) {
					if (id_front == j -> primeiro -> g_id() || id_front == j -> segundo -> g_id())  {
						if (id_back == j -> primeiro -> g_id() || id_back == j -> segundo -> g_id()) {
							par_juncao = j;
							break;
						}
					}
				}

				if (!par_juncao) {
					//Nao existe juncao para o par
					proximo = true;
					break;
				}

				//Define caminhos disjuntos das juncoes ate o par
				define_anel_aux(par_juncao, par_anel_aux);
			}

			if (proximo) {
				while(c_aneis_aux.size() > 0) {
					Anel_aux* a = c_aneis_aux.front();
					c_aneis_aux.pop_front();
					delete a;
				}
				continue;
			}

			//Para todo grupo de caminhos disjuntos fazer intersecção
			//Se intersecção for vazia, encontrou um anel
			list<Juncao*> juncoesUtilizadas;
			vector<list<Vertice*>> atual;
			encontra_aneis(c_aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas);

			//Para cada anel aux criado excluilo
			while(c_aneis_aux.size() > 0) {
				Anel_aux* a = c_aneis_aux.front();
				c_aneis_aux.pop_front();
				delete a;
			}
			for (Juncao* j: juncoesUtilizadas)
				delete j;
		}
	}
}

void encontra_duplas_casamentos(vector<list<int>> casamentos, list<list<list<int>>>& destino)
{
	for (int i = 0; i < casamentos.size(); i++) {
		for (int y = i + 1; y < casamentos.size(); y++) {
			list<list<int>> nova_dupla;
			nova_dupla.push_back(casamentos[i]);
			nova_dupla.push_back(casamentos[y]);

			destino.push_back(nova_dupla);
		}
	}
}

void encontra_combinacoes_dupla(list<list<int>> dupla_casamentos, list<list<list<int>>>& destino)
{
	int x1, y1, x2, y2;

	x1 = dupla_casamentos.front().front();
	y1 = dupla_casamentos.front().back();
	x2 = dupla_casamentos.back().front();
	y2 = dupla_casamentos.back().back();

	list<int> nova_simples_1_1;
	list<int> nova_simples_1_2;
	list<list<int>> nova_complexa_1;
	nova_simples_1_1.push_back(x1);
	nova_simples_1_1.push_back(x2);
	nova_simples_1_2.push_back(y1);
	nova_simples_1_2.push_back(y2);
	nova_complexa_1.push_back(nova_simples_1_1);
	nova_complexa_1.push_back(nova_simples_1_2);
	destino.push_back(nova_complexa_1);

	list<int> nova_simples_2_1;
	list<int> nova_simples_2_2;
	list<list<int>> nova_complexa_2;
	nova_simples_2_1.push_back(x1);
	nova_simples_2_1.push_back(y2);
	nova_simples_2_2.push_back(y1);
	nova_simples_2_2.push_back(x2);
	nova_complexa_2.push_back(nova_simples_2_1);
	nova_complexa_2.push_back(nova_simples_2_2);
	destino.push_back(nova_complexa_2);
}

void encontra_trios_casamentos(vector<list<int>> casamentos, list<list<list<int>>>& destino)
{
	for (int i = 0; i < casamentos.size(); i++) {
		for (int y = i + 1; y < casamentos.size(); y++) {
			for (int z = y + 1; z < casamentos.size(); z++) {
				list<list<int>> novo_trio;
				novo_trio.push_back(casamentos[i]);
				novo_trio.push_back(casamentos[y]);
				novo_trio.push_back(casamentos[z]);


				destino.push_back(novo_trio);
			}
		}
	}
}

void encontra_combinacoes_trio(list<list<int>> trio_casamentos, list<list<list<int>>>& destino)
{
	//(x1,y1) (x2,y2) (x3,y3) ->
	//(x1,x2) (y2, x3) (y3, y1)
	//(x1,x2) (y2, y3) (x3, y1)
	//(x1,y2) (x2, y3) (x3, y1)
	//(x1,y2) (x2, x3) (y3,y1)
	//(y1,x2) (y2, x3) (y3, x1)
	//(y1,x2) (y2, y3) (x3, x1)
	//(y1,y2) (x2, y3) (x3, x1)
	//(y1,y2) (x2, x3) (y3, x1)
	int x1, y1, x2, y2, x3, y3;

	x1 = trio_casamentos.front().front();
	y1 = trio_casamentos.front().back();
	trio_casamentos.pop_front();
	x2 = trio_casamentos.front().front();
	y2 = trio_casamentos.front().back();
	x3 = trio_casamentos.back().front();
	y3 = trio_casamentos.back().back();

	list<list<int>> linha_1;
	list<int> nova_1;
	list<int> nova_2;
	list<int> nova_3;
	nova_1.push_back(x1);
	nova_1.push_back(x2);
	nova_2.push_back(y2);
	nova_2.push_back(x3);
	nova_3.push_back(y3);
	nova_3.push_back(y1);
	linha_1.push_back(nova_1);
	linha_1.push_back(nova_2);
	linha_1.push_back(nova_3);
	destino.push_back(linha_1);

	list<list<int>> linha_2;
	list<int> nova_1_2;
	list<int> nova_2_2;
	list<int> nova_3_2;
	nova_1_2.push_back(x1);
	nova_1_2.push_back(x2);
	nova_2_2.push_back(y2);
	nova_2_2.push_back(y3);
	nova_3_2.push_back(x3);
	nova_3_2.push_back(y1);
	linha_2.push_back(nova_1_2);
	linha_2.push_back(nova_2_2);
	linha_2.push_back(nova_3_2);
	destino.push_back(linha_2);

	list<list<int>> linha_3;
	list<int> nova_1_3;
	list<int> nova_2_3;
	list<int> nova_3_3;
	nova_1_3.push_back(x1);
	nova_1_3.push_back(y2);
	nova_2_3.push_back(x2);
	nova_2_3.push_back(y3);
	nova_3_3.push_back(x3);
	nova_3_3.push_back(y1);
	linha_3.push_back(nova_1_3);
	linha_3.push_back(nova_2_3);
	linha_3.push_back(nova_3_3);
	destino.push_back(linha_3);

	list<list<int>> linha_4;
	list<int> nova_1_4;
	list<int> nova_2_4;
	list<int> nova_3_4;
	nova_1_4.push_back(x1);
	nova_1_4.push_back(y2);
	nova_2_4.push_back(x2);
	nova_2_4.push_back(x3);
	nova_3_4.push_back(y3);
	nova_3_4.push_back(y1);
	linha_4.push_back(nova_1_4);
	linha_4.push_back(nova_2_4);
	linha_4.push_back(nova_3_4);
	destino.push_back(linha_4);

	list<list<int>> linha_5;
	list<int> nova_1_5;
	list<int> nova_2_5;
	list<int> nova_3_5;
	nova_1_5.push_back(y1);
	nova_1_5.push_back(x2);
	nova_2_5.push_back(y2);
	nova_2_5.push_back(x3);
	nova_3_5.push_back(y3);
	nova_3_5.push_back(x1);
	linha_5.push_back(nova_1_5);
	linha_5.push_back(nova_2_5);
	linha_5.push_back(nova_3_5);
	destino.push_back(linha_5);

	list<list<int>> linha_6;
	list<int> nova_1_6;
	list<int> nova_2_6;
	list<int> nova_3_6;
	nova_1_6.push_back(y1);
	nova_1_6.push_back(x2);
	nova_2_6.push_back(y2);
	nova_2_6.push_back(y3);
	nova_3_6.push_back(x3);
	nova_3_6.push_back(x1);
	linha_6.push_back(nova_1_6);
	linha_6.push_back(nova_2_6);
	linha_6.push_back(nova_3_6);
	destino.push_back(linha_6);

	list<list<int>> linha_7;
	list<int> nova_1_7;
	list<int> nova_2_7;
	list<int> nova_3_7;
	nova_1_7.push_back(y1);
	nova_1_7.push_back(y2);
	nova_2_7.push_back(x2);
	nova_2_7.push_back(y3);
	nova_3_7.push_back(x3);
	nova_3_7.push_back(x1);
	linha_7.push_back(nova_1_7);
	linha_7.push_back(nova_2_7);
	linha_7.push_back(nova_3_7);
	destino.push_back(linha_7);

	list<list<int>> linha_8;
	list<int> nova_1_8;
	list<int> nova_2_8;
	list<int> nova_3_8;
	nova_1_8.push_back(y1);
	nova_1_8.push_back(y2);
	nova_2_8.push_back(x2);
	nova_2_8.push_back(x3);
	nova_3_8.push_back(y3);
	nova_3_8.push_back(x1);
	linha_8.push_back(nova_1_8);
	linha_8.push_back(nova_2_8);
	linha_8.push_back(nova_3_8);
	destino.push_back(linha_8);
}

void define_anel_aux(JuncoesDe* juncao, Anel_aux* destino)
{
	destino -> primeiro = juncao -> primeiro;
	destino -> segundo = juncao -> segundo;


	//Encontra os caminhos da juncao até os mebros do par
	list<list<Vertice*>> caminhos_front[juncao -> juncoes.size()];
	list<list<Vertice*>> caminhos_back[juncao -> juncoes.size()];
	int indice = 0;
	for (Vertice* juncoes: juncao->juncoes) {
		list<Vertice*> caminho_atual;

		clock_t inicio = clock();

		thread threads[juncoes -> max_cores[destino -> primeiro -> g_id()] + juncoes -> max_cores[destino -> segundo -> g_id()]];
		int zi = 0;
		set<int>  cores;
		for (int i = 1; i <= juncoes -> max_cores[destino -> primeiro -> g_id()]; i++)
			//encontra_caminhos_cores_especificas(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice], cores, i);
			threads[zi++] = thread(encontra_caminhos_cores_especificas, ref(juncoes), ref(destino -> primeiro), ref(caminho_atual), ref(caminhos_front[indice]), ref(cores), i);
		for (int i = 1; i <= juncoes -> max_cores[destino -> segundo -> g_id()]; i++)
			//encontra_caminhos_cores_especificas(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice], cores, i);
			threads[zi++] = thread(encontra_caminhos_cores_especificas, ref(juncoes), ref(destino -> segundo), ref(caminho_atual), ref(caminhos_back[indice]), ref(cores), i);

		for (int i = 0; i < zi; i++)
			threads[i].join();
/*
		encontra_caminhos(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice]);
		encontra_caminhos(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice]);
*/

		tempo_procura_caminhos += clock() - inicio;
		indice++;
	}

	//Encontra os caminhos disjuntos da juncao até os membros do par
	destino -> mudar_tamanho(juncao -> juncoes.size());
	indice = 0;
	for (Vertice* juncoes: juncao -> juncoes) {
		int i = 0;
		int tam_max = (caminhos_front[indice].size() + 1) * (caminhos_back[indice].size() + 1);
		destino -> juncoes[indice] = juncoes;
		destino -> caminhos_primeiro[indice].resize(tam_max);
		destino -> caminhos_segundo[indice].resize(tam_max);
		for (list<Vertice*> caminho_a: caminhos_front[indice]) {
			for (list<Vertice*> caminho_b: caminhos_back[indice]) {
				if (sao_disjuntos(caminho_a, caminho_b)) {
					destino -> caminhos_primeiro[indice][i] = caminho_a;
					destino -> caminhos_segundo[indice][i] = caminho_b;
					i++;
				}
			}
		}
		indice++;
	}
}

void encontra_caminhos(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<list<Vertice*>> &caminhos)
{
	if (fonte == destino) {
		caminhos.push_back(caminho_atual);
		return;
	}

	for (Vertice* filho: fonte -> filhos){
		list<Vertice*> caminho_aux(caminho_atual);
		caminho_aux.push_back(filho);
		encontra_caminhos(filho, destino, caminho_aux, caminhos);
	}
}

void encontra_caminhos_cores_especificas(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<list<Vertice*>> &caminhos, set<int> cores, int cores_restantes)
{
	bool nova_cor = cores.insert(fonte -> cor_int).second;
	if (nova_cor)
		cores_restantes--;
	if (cores_restantes < 0)
		return;
	if (fonte == destino && cores_restantes == 0) {
		caminhos.push_back(caminho_atual);
		return;
	}

	for (Vertice* filho: fonte -> filhos){
		//MUDAR  colocar condicao
		if (filho -> max_cores[destino-> g_id()] + cores.size() < cores_restantes)
			continue;
		else if (filho -> min_cores[destino -> g_id()] == -1)
			continue;

		list<Vertice*> caminho_aux(caminho_atual);
		caminho_aux.push_back(filho);
		encontra_caminhos_cores_especificas(filho, destino, caminho_aux, caminhos, cores, cores_restantes);
	}
}

bool sao_disjuntos(list<Vertice*> caminho_a, list<Vertice*> caminho_b)
{
	for (Vertice* i: caminho_a)
		for (Vertice* y: caminho_b)
			if (i == y)
				return false;
	return true;
}

void encontra_aneis(list<Anel_aux*> aux, vector<list<Vertice*>> atual, list<Anel*> & destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas)
{
	//Chegou ao ultimo grupo da combinação
	if (aux.size() == 0) {
		verifica_anel(atual, destino, casamentos, juncoesUtilizadas);

		return;
	}

	//Remove proximo da lista
	Anel_aux* anel_a = aux.front();
	aux.pop_front();

	//Se proximo da lista tem elementos iguais
	if (anel_a -> primeiro == anel_a -> segundo) {
		return;	//Mudar p incluir AxCk, x != k
		list<Juncao*> juncoes_aux(juncoesUtilizadas);
		juncoes_aux.push_back(new Juncao(anel_a -> primeiro, anel_a -> segundo, anel_a -> primeiro));

		vector<list<Vertice*>> atual_aux(atual);
		// Verificar (Colocar 0 ou 2) em atual_aux

		encontra_aneis(aux, atual_aux, destino, casamentos, juncoes_aux);
		return;
	}


	Juncao* novaJuncao = 0;
	for (int i = 0; i < anel_a -> juncoes.size(); i++) {
		list<Juncao*> juncoes_aux(juncoesUtilizadas);
		novaJuncao = new Juncao(anel_a -> primeiro, anel_a -> segundo, anel_a -> juncoes[i]);
		juncoes_aux.push_back(novaJuncao);

		for (int y = 0; y < anel_a -> caminhos_primeiro[i].size(); y++) {
			if (anel_a -> caminhos_primeiro[i][y].size() == 0 && anel_a -> caminhos_segundo[i][y].size() == 0)
				break;

			vector<list<Vertice*>> atual_aux(atual);

			atual_aux.push_back(anel_a -> caminhos_primeiro[i][y]);
			atual_aux.push_back(anel_a -> caminhos_segundo[i][y]);

			encontra_aneis(aux, atual_aux, destino, casamentos, juncoes_aux);
		}
	}

	if (!novaJuncao)
		delete novaJuncao;
}

void verifica_anel(vector<list<Vertice*>> caminhos, list<Anel*> &destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas)
{
	clock_t inicio = clock();
	//Verifica se Alguma juncao é repetida ou esta em algum caminho
	list<Vertice*> aux;
	for (Juncao* j: juncoesUtilizadas) {
		for (Vertice* v: aux)
			if (v == j -> juncao)
				return;

		aux.push_back(j -> juncao);
	}
	for (list<Vertice*> l: caminhos)
		for (Vertice* v: l)
			for (Vertice* v1: aux)
				if (v == v1)
					return;




	tempo_verifica_anel += clock() - inicio;

	clock_t inicio_ = clock();
	//verifica se intersecção é vazia
	for (int i = 0; i < caminhos.size(); i++) {
		for (int y = i + 1; y < caminhos.size(); y++) {
			if (!sao_disjuntos(caminhos[i], caminhos[y])) {
				tempo_sao_disjuntos += clock() - inicio_;
				return;
			}
		}
	}
	tempo_sao_disjuntos += clock() - inicio_;
	inicio = clock();

	Anel* novo = new Anel();
	novo -> adicionar_elemento(caminhos, casamentos, juncoesUtilizadas);

	destino.push_back(novo);

	//Para escrever sempre que encontrar um anel
/*
	FILE* arquivo;
	arquivo = fopen("aneis/aneis_ordem_3.txt", "a");
	fputs(novo -> linha_normal.c_str(), arquivo);
	fclose(arquivo);

	delete novo;*/


	tempo_verifica_anel += clock() - inicio;
}

void encontra_aneis_coloridos(Grafo* g, list<Anel*>& destino, int numero_casamentos)
{
	if (numero_casamentos > 3 || numero_casamentos < 1)
		return;

	//3.1
	//Encontra todas as junções do grafo
	list<JuncoesDe*> juncoes;
	encontra_juncoes(g, juncoes);
	printf("Encontrou junções\n");
	Juncoes* jun = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, jun);

	//3.2
	//Encontra todos os casamentos do grafo (list<int> = 1 casamento)
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);
	printf("Encontrou casamentos\n");

	//Colorir o grafo e encontrar max_cores
	define_max_cores(g);
	define_min_max_cores(g);

	//3.3
	//Define os conjuntos a serem trabalhados e operam encontrando os aneis sobre eles
	if (numero_casamentos == 1)
		encontra_aneis_a1(juncoes, casamentos, destino);
	else if (numero_casamentos == 2) {
		//int tam = g -> atributos[0] -> cores_ate_folha;
		//int tam = g -> map -> tam();
		int tam = 0;
		for (Vertice* v: g -> atributos) {
			if (v -> cores_ate_folha > tam)
				tam = v -> cores_ate_folha;
		}
		tam *= 4;
		thread threads[tam];
		//encontra_aneis_coloridos_a2(g, juncoes, casamentos, destino, 3);

		for (int i = 1; i < tam; i++) {
			//threads[i] = thread(encontra_aneis_coloridos_a2, ref(g), ref(jun), casamentos, ref(destino), i);
			encontra_aneis_coloridos_a2(g, jun, casamentos, destino, i);
		}

		for (int i = 1; i < tam; i++) {
			//threads[i].join();
		}
	}
	else
		encontra_aneis_a3(g, juncoes, casamentos, destino);
	int i = 0;
	for (vector<JuncoesDe*> j: jun -> juncoes) {
		for (JuncoesDe* d: j) {
			if (d)
				i++;
		}
	}

	printf("Numero de juncoes: %d\n", i);

	cout << " tempo_encontra_anel_p " << (double) tempo_encontra_anel_p << endl;
	cout << " tempo_verifica_anel " << (double) tempo_verifica_anel  << endl;
	cout << " tempo_encontra_anel " << (double) tempo_encontra_anel << endl;
	cout << " tempo_procura_caminhos " << (double) tempo_procura_caminhos  << endl;
	cout << " tempo_sao_disjuntos " << (double) tempo_sao_disjuntos << endl << endl;


	cout << " tempo_encontra_anel_p " << (double) tempo_encontra_anel_p / CLOCKS_PER_SEC << endl;
	cout << " tempo_verifica_anel " << (double) tempo_verifica_anel / CLOCKS_PER_SEC  << endl;
	cout << " tempo_encontra_anel " << (double) tempo_encontra_anel / CLOCKS_PER_SEC<< endl;
	cout << " tempo_procura_caminhos " << (double) tempo_procura_caminhos / CLOCKS_PER_SEC << endl;
	cout << " tempo_sao_disjuntos " << (double) tempo_sao_disjuntos /CLOCKS_PER_SEC << endl;
}

void encontra_aneis_coloridos_a2(Grafo* g, Juncoes* juncoes, vector<list<int>> casamentos, list<Anel*>& destino, int numero_cores)
{
	clock_t inicio = clock();
	printf("Procurando aneis com %d cores\n", numero_cores);
	//Constroi todos os conjuntos de casamentos, cada 1 com 2 casamentos
	list<list<list<int>>> conjuntos_c;
	encontra_duplas_casamentos(casamentos, conjuntos_c);

	//Define conjunto c com 2 casamentos e trabalha nele
	int vezes = 0;
	for (list<list<int>> conjunto_c: conjuntos_c) {
		if (++vezes % 2500 == 0)
			printf("Procurando %d\n", vezes);
		//Transforma casamentos em combinacoes
		//(x1,y1) (x2, y2) -> (x1,x2) (y1,y2) e (x1, y2) (y1, x2)
		list<list<list<int>>> combinacoes;
		encontra_combinacoes_dupla(conjunto_c, combinacoes);

		//Para cada possibilidade de agrupamento(combinacao)
		bool proximo = false;
		for (list<list<int>> c: combinacoes) {
			//Estrutura que armazena caminhos e juncoes para cada par em c
			list<Anel_aux*> c_aneis_aux;
			list<JuncoesDe*> jun;

			//Para cada par da combinação
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();


				//Se par é o mesmo elemento continua busca em outros pares
				if (id_front == id_back) {
					proximo = true;	//mudar para encontrar AxCk, x != k (comentar linha), adicionar ela no proximo loop for com atribuicoes
					continue;
				}

				//Encontra as juncoes do par
				JuncoesDe* par_juncao = juncoes ->juncoes[id_front][id_back];

				if (!par_juncao) {
					//Nao existe juncao para o par
					proximo = true;
					break;
				}

				jun.push_back(par_juncao);
			}

			if (!proximo) {
				int soma = 0;
				for (JuncoesDe* par_juncao: jun) {
					Vertice* primeiro = par_juncao -> primeiro;
					Vertice* segundo = par_juncao -> segundo;
					int aux_1 = 0;
					int aux;
					for (Vertice* j: par_juncao -> juncoes) {
						aux = j -> max_cores[primeiro -> g_id()] + j -> max_cores[segundo -> g_id()];
						aux_1 = aux > aux_1 ? aux : aux_1;
					}
					soma += aux_1;
				}
				if (soma < numero_cores) {
					proximo = true;
				} else
					for (JuncoesDe* par_juncao: jun) {
						//Anel auxiliar do par
						Anel_aux* par_anel_aux = new Anel_aux();
						c_aneis_aux.push_back(par_anel_aux);

						tempo_encontra_anel_p += clock() - inicio;
						//Define caminhos disjuntos das juncoes ate o par
						define_anel_aux_cores(par_juncao, par_anel_aux, numero_cores);
						inicio = clock();
					}
			}

			//Algum par nao tem juncao
			if (proximo) {
				while(c_aneis_aux.size() > 0) {
					Anel_aux* a = c_aneis_aux.front();
					c_aneis_aux.pop_front();
					delete a;
				}
				continue;
			}

			tempo_encontra_anel_p += clock() - inicio;
			//Para todo grupo de caminhos disjuntos fazer intersecção
			//Se intersecção for vazia, encontrou um anel
			list<Juncao*> juncoesUtilizadas;
			vector<list<Vertice*>> atual;
			set<int> cores;
			clock_t inicio_ = clock();
			encontra_aneis_coloridos(c_aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas, cores, numero_cores);
			tempo_encontra_anel += clock() - inicio_;
			inicio = clock();

			//Para cada anel aux criado excluilo
			while(c_aneis_aux.size() > 0) {
				Anel_aux* a = c_aneis_aux.front();
				c_aneis_aux.pop_front();
				delete a;
			}
			for (Juncao* j: juncoesUtilizadas)
				delete j;
		}
	}
	printf("Terminou de encontrar aneis com %d cores\n", numero_cores);
	tempo_encontra_anel_p += clock() - inicio;
}

void define_anel_aux_cores(JuncoesDe* juncao, Anel_aux* destino, int c)
{
	destino -> primeiro = juncao -> primeiro;
	destino -> segundo = juncao -> segundo;


	//Encontra os caminhos da juncao até os mebros do par que tenham no maximo c cores
	list<list<Vertice*>> caminhos_front[juncao -> juncoes.size()];
	list<list<Vertice*>> caminhos_back[juncao -> juncoes.size()];

	vector<set<int>> l_cores_front;
	vector<set<int>> l_cores_back;
	int indice = 0;
	for (Vertice* juncoes: juncao->juncoes) {
		if (juncoes -> min_cores[destino -> primeiro -> g_id()] > c || juncoes -> min_cores[destino -> segundo -> g_id()] > c) {
				indice++;
				continue;
		}

		list<Vertice*> caminho_atual;
		set<int> cores;
		clock_t inicio = clock();
		encontra_caminhos_cores(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice], c, l_cores_front, cores);
		encontra_caminhos_cores(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice], c, l_cores_back, cores);
		tempo_procura_caminhos += clock() - inicio;
		indice++;
	}

	//Encontra os caminhos disjuntos da juncao até os membros do par, com o maximo de cores
	destino -> mudar_tamanho(juncao -> juncoes.size());
	indice = 0;
	for (Vertice* juncoes: juncao -> juncoes) {
		int i = 0;
		int tam_max = (caminhos_front[indice].size() + 1) * (caminhos_back[indice].size() + 1);
		destino -> juncoes[indice] = juncoes;
		destino -> caminhos_primeiro[indice].resize(tam_max);
		destino -> caminhos_segundo[indice].resize(tam_max);
		destino -> cores[indice].resize(tam_max);
		int x = 0;
		for (list<Vertice*> caminho_a: caminhos_front[indice]) {
			set<int> cores_front = l_cores_front[x];
			int y = 0;
			for (list<Vertice*> caminho_b: caminhos_back[indice]) {
				set<int> cores_back = l_cores_back[y];
				set<int> soma_ = soma(l_cores_back[y], l_cores_front[x]);
				if (soma_.size() <= c) {
					clock_t inicio_ = clock();
					if (sao_disjuntos(caminho_a, caminho_b)) {
						destino -> caminhos_primeiro[indice][i] = caminho_a;
						destino -> caminhos_segundo[indice][i] = caminho_b;
						destino -> cores[indice][i] = soma_;
						i++;
					}
					tempo_sao_disjuntos += clock() - inicio_;
				}
				y++;
			}
			x++;
		}
		indice++;
	}
}

void encontra_caminhos_cores(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<list<Vertice*>> &caminhos, int cores_restantes, vector<set<int>> &l_cores, set<int> cores)
{
	bool nova_cor = cores.insert(fonte -> cor_int).second;
	if (nova_cor)
		cores_restantes--;
	if (cores_restantes < 0)
		return;
	if (fonte == destino) {
		l_cores.push_back(cores);
		caminhos.push_back(caminho_atual);
		return;
	}

	for (Vertice* filho: fonte -> filhos){
		//MUDAR  colocar condicao
		list<Vertice*> caminho_aux(caminho_atual);
		caminho_aux.push_back(filho);
		encontra_caminhos_cores(filho, destino, caminho_aux, caminhos, cores_restantes, l_cores, cores);
	}
}

set<int> soma(set<int> a, set<int> b)
{
	set<int> ret(a);

	for (int i: b)
		ret.insert(i);

	return ret;
}

void encontra_aneis_coloridos(list<Anel_aux*> aux, vector<list<Vertice*>> atual, list<Anel*> & destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas, set<int> cores, int numero_cores)
{
	//Chegou ao ultimo grupo da combinação
	if (aux.size() == 0) {
		//verifica_anel_colorido(atual, destino, casamentos, juncoesUtilizadas, numero_cores);
		if (cores.size() == numero_cores)
			verifica_anel(atual, destino, casamentos, juncoesUtilizadas);
		return;
	}

	//Remove proximo da lista
	Anel_aux* anel_a = aux.front();
	aux.pop_front();

	//Se proximo da lista tem elementos iguais
	if (anel_a -> primeiro == anel_a -> segundo) {
		return;	//Mudar p incluir AxCk, x != k
	}


	Juncao* novaJuncao = 0;
	for (int i = 0; i < anel_a -> juncoes.size(); i++) {
		list<Juncao*> juncoes_aux(juncoesUtilizadas);
		novaJuncao = new Juncao(anel_a -> primeiro, anel_a -> segundo, anel_a -> juncoes[i]);
		juncoes_aux.push_back(novaJuncao);

		for (int y = 0; y < anel_a -> caminhos_primeiro[i].size(); y++) {
			if (anel_a -> caminhos_primeiro[i][y].size() == 0 && anel_a -> caminhos_segundo[i][y].size() == 0)
				break;

			vector<list<Vertice*>> atual_aux(atual);
			set<int> cores_aux = soma(cores, anel_a -> cores[i][y]);

			if (cores_aux.size() > numero_cores)
				continue;

			atual_aux.push_back(anel_a -> caminhos_primeiro[i][y]);
			atual_aux.push_back(anel_a -> caminhos_segundo[i][y]);

			encontra_aneis_coloridos(aux, atual_aux, destino, casamentos, juncoes_aux, cores_aux, numero_cores);
		}
	}

	if (!novaJuncao)
		delete novaJuncao;

}

void verifica_anel_colorido(vector<list<Vertice*>> caminhos, list<Anel*> &destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas, int numero_cores)
{
	verifica_anel(caminhos, destino, casamentos, juncoesUtilizadas);
}
