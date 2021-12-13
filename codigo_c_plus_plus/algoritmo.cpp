#include "algoritmo.h"
mutex m_listas;
mutex m_numero_aneis;
sem_t s_thread;
int numero_aneis = 0;
bool com_cores = true;


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

void colorir_grafo(Grafo* g, list<int> vertices)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_grafo(), matriz invalida");

	//Colore apartir das fontes
	for (int i: vertices)
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

void colorir_grafo_mat(Grafo* g, list<int> vertices)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_grafo_mat(), matriz invalida");

	//Colore apartir das fontes
	for (int i: vertices) {
		if (g -> encontrar_atributo(i) -> g_tipo() == 'e')
			colorir_apartir_de_tipo(g, i, 'e');
	}
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

void colorir_grafo_pat(Grafo* g, list<int> vertices)
{
	int** grafo = g -> grafo;
	if (!grafo) throw runtime_error("Erro em colorir_grafo_pat(), matriz invalida");

	//Colore apartir das fontes
	for (int i: vertices) {
		if (g -> encontrar_atributo(i) -> g_tipo() == 't')
			colorir_apartir_de_tipo(g, i, 't');
	}
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

void nothing(){}

//g é colorido
void define_super_sob(Grafo* g)
{
	//Inicia cores em g
	init_map(g);

	//Cria um grafo que vai ser operado
	Grafo* copia;
	copiar(g, copia);

	//Inicializa os atributos de g
	for (Vertice* v: g -> atributos) {
		v -> min_cores = vector<int>(g -> g_numero_vertices(), INT_MAX);
		v -> max_cores = vector<int>(g -> g_numero_vertices(), 0);
	}

	//Cria raiz inicial para copia( se não houver)
	Vertice* raiz = copia -> g_raiz();
	if (raiz -> g_tipo() == 'r') {
		for (Vertice* v: raiz -> filhos) {
			v -> adicionar_pais(raiz);
		}
		
		if (raiz -> cor.size() == 0) 
			raiz -> adicionar_cor(raiz -> g_id());
	}

	//Inicializa os atributos de copia
	for (Vertice* v: copia -> atributos) {
		v -> min_cores = vector<int>(copia -> g_numero_vertices(), INT_MAX);
		v -> max_cores = vector<int>(copia -> g_numero_vertices(), 0);
	}
	raiz -> min_cores = vector<int>(copia -> g_numero_vertices(), INT_MAX);
	raiz -> max_cores = vector<int>(copia -> g_numero_vertices(), 0);

	//Encontra super e sob para folhas e as retira do grafo
	while (raiz -> filhos.size() > 0) {
		//Encontra os valores
		list<int> id_folhas;
		define_super_sob_folhas(copia, id_folhas);

		//Adiciona os valores para g
		for (int i: id_folhas) {
			for (Vertice* v: copia -> atributos)
				if (v && v != raiz) {
					int id = v -> g_id();
					g -> atributos[id] -> max_cores[i] = v -> max_cores[i];
					g -> atributos[id] -> min_cores[i] = v -> min_cores[i];
				}
		}

		//Retira as folhas de copia
		podar_folhas(copia);
	}

	int super = 1;
	for (Vertice* v: g -> atributos)
		for (int i = 0; i < g -> g_numero_vertices(); i++) {
			super = super > v -> max_cores[i] ? super : v -> max_cores[i];
			if (v -> min_cores[i] == INT_MAX)
				v -> min_cores[i] = 0;
		}
	g -> s_max_super(super);

	delete copia;
}

//g colorido, com raiz e com cores em g -> map (vertices de g podem ser vazios)
void define_super_sob_folhas(Grafo* g, list<int> &id_folhas)
{
	//Adiciona cor para as folhas
	Cor* cor;
	Map* map = g -> map;

	for (Vertice* v: g -> atributos)
		if (v) {
			set<set<int>, set_cmp> novo;
			v -> cores = novo;

			if (v -> filhos.size() == 0) {
				cor = map -> encontrar_cor(v -> cor);
				if (!cor) {
					throw runtime_error("Em define_super_sob_folhas, cor não encontrada");
				}

				//Adiciona cor e id de v
				set<int> cor_v;
				cor_v.insert(cor -> to_int());
				cor_v.insert(v -> g_id() * (-1));	//id * -1 p ser o primeiro elemento
				id_folhas.push_back(v -> g_id());

				v -> cores.insert(cor_v);
			}
		}

	//Ordenação topologica
	list<Vertice*> ordenacao_topologica;
	ordem_topologica(g, g -> g_raiz(), ordenacao_topologica);

	//Algoritmo
	for (Vertice* v: ordenacao_topologica) {
		//Calcula super e sob
		for (set<int> s: v -> cores) {
			//Pega id da folha
			int id = (*s.begin()) * (-1);

			//Atualiza vetores
			if ((s.size() - 1) > v -> max_cores[id])
				v -> max_cores[id] = s.size() - 1;
			if ((s.size() - 1) < v -> min_cores[id])
				v -> min_cores[id] = s.size() - 1;
		}

		//Passa cores para os pais
		for (Vertice* w: v -> pais) {
			for (set<int> conjunto: v -> cores) {
				set<int> novo(conjunto);
				cor = map -> encontrar_cor(w -> cor);
				if (cor)	//Para quando raiz é artificial(não esta com cor em map)
					novo.insert(cor -> to_int());
				w -> cores.insert(novo);
			}
		}
	}
}

//Retira as folhas de g, alguns atributos podem ser vazios
void podar_folhas(Grafo* g)
{
	list<Vertice*> retirar;
	for (Vertice* v: g -> atributos)
		if (v)
			if (v -> filhos.size() == 0) {
				retirar.push_back(v);
			}

	for (Vertice* v: retirar) {
		g -> atributos[v -> g_id()] = 0;

		for (Vertice* x: v -> pais)
			x -> filhos.remove(v);
		for (Vertice* x: v -> filhos)
			x -> pais.remove(v);
		for (Vertice* x: v -> casados)
			x -> casados.remove(v);

		v -> pais.clear();
		v -> filhos.clear();
		v -> casados.clear();
		delete v;
	}
}

//Copia vertices, cores, ligacoes e map de g para destino
void copiar(Grafo* g, Grafo* &destino)
{
	int numero_vertices = g -> g_numero_vertices();
	Vertice* raiz = 0;
	vector<Vertice*> atributos(numero_vertices);
	int** grafo;

	//Cria as estruturas do novo grafo
	grafo = new int*[numero_vertices];
	for (int i = 0; i < numero_vertices; i++)
		grafo[i] = new int[numero_vertices];

	//Cria os vertices
	for (int i = 0; i < numero_vertices; i++) {
		Vertice* v = g -> encontrar_atributo(i);
		if (!v)
			continue;
		atributos[i] = new Vertice(v -> g_id(), v -> g_numero(), v -> g_tipo());

		if (v == g -> g_raiz())
			raiz = atributos[i];
	}

	//Adiciona ligacoes
	for (Vertice* v: atributos) {
		int id = v -> g_id();
		for (Vertice* a: atributos)
		{
			int i = a -> g_id();

			if (g -> grafo[id][i] == 0) {
				grafo[id][i] = 0;
			} else if (g -> grafo[id][i] == 1) {
				grafo[id][i] = 1;
				v -> adicionar_casamento(a);
			} else if (g -> grafo[id][i] == 12) {
				grafo[id][i] = 12;
				v -> adicionar_casamento(a);
				v -> adicionar_filho(a);
			} else if (g -> grafo[id][i] == 13) {
				grafo[id][i] = 13;
				v -> adicionar_casamento(a);
				v -> adicionar_pais(a);
			} else if (g -> grafo[id][i] == 2) {
				grafo[id][i] = 2;
				v -> adicionar_filho(a);
			} else {	//grafo[id][i] == 3
				grafo[id][i] = 3;
				v -> adicionar_pais(a);
			}
		}
	}

	//Adiciona cores
	for (Vertice* v: atributos)
		for (int cor: g -> atributos[v -> g_id()] -> cor)
			v -> adicionar_cor(cor);

	//Cria grafo
	destino = new Grafo(numero_vertices, atributos, raiz, grafo);

	//Copia cores
	if (g -> map)
		destino -> map = g -> map;
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
		raiz = new Vertice(g -> g_numero_vertices(), -1, 'r');
		for (Vertice* v: raizes) {
			raiz -> adicionar_filho(v);
			v -> adicionar_pais(raiz);
		}
	} else if (raizes.size() == 1)
		raiz = raizes.front();
	else
		return;

	Cor* cor;
	Map* map = g -> map;
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
		g -> map = new Map();
		reinicia_cores();
	}
	Map* map = g -> map;

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
					string rgb = primeira_cor();
					if (rgb == "") //Se o numero de cores colocado na lista cores e muito pequeno
					{ throw runtime_error("Erro em init_map(), Falta Cores!"); }

					//Inicia uma nova cor e a adiciona ao map
					aux = new Cor(rgb);
					map -> adicionar_cor(cor_n, aux);
				}

				if (!cor) {	//Se esta passando pela primeira vez copia a cor de aux
					if (a -> cor.size() == 1)	//Passando pela primeira vez pega a cor que ja foi adicionada
						cor = aux;
					else	//Se tem mais cores inicia uma copia da cor adicionada
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
				a -> cor_int = cor -> to_int();
				continue;
			}
			if (a -> cor.size() > 1)	//cor ainda nao foi adicionada
				map -> adicionar_cor(a -> cor, cor);
		}

		a -> cor_int = cor -> to_int();
	}
}

void encontra_raizes(Grafo* g, list<Vertice*>& destino)
{
	for (Vertice* v: g -> atributos)
		if (v)
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
				v -> min_cores[i] = 0;
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
	for (Vertice* v: g -> atributos) {
		if (v) {
			v -> valor_bool = false;
		}
	}

	ordem_topologica(fonte, destino);
}

void encontra_juncoes(Grafo* g, list<Juncao*>& destino)
{
	stack<Vertice*> vs;

	for(Vertice* s: g -> atributos)
	{
		ordem_topologica(g, s, vs);

		//g -> resetar();		//TODO Mudar p
		for (Vertice* v: g -> atributos) v -> valor_int = -1;

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
	Vertice* root = new Vertice(g -> atributos.size(), -1, 'r');
	list<Vertice*> raizes_g;
	encontra_raizes(g, raizes_g);
	for (Vertice* v: raizes_g) {
		v -> adicionar_pais(root);
		root -> adicionar_filho(v);
	}

	//Algoritmo que chama recursivamente
	for (Vertice* v: g -> atributos) {
		v -> valor_bool = true;
		v -> valor_bool_2 = true;	//EQM Nao tenho certeza
	}

	procedimento_dominadores(g, g -> atributos, root, dominadores_imediatos);

	//Retorna g ao normal
	for (Vertice* v: raizes_g) {
		v -> pais.remove(root);
	}
	delete root;
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
		} else if (v -> pais.size() == 0){
			throw runtime_error("Erro em cobertura_dominadores(), Vertice fonte no meio da ordenação");
		} else {
			throw runtime_error("Erro em cobertura_dominadores(), Verificar arvore");	//Verificar esta implementacao
			//Verifica se algum pai é s
			for (Vertice* a: v -> pais) {
				if (a -> g_id() == s -> g_id()) {
					fd[v -> g_id()] = v;
				}
			}
			if (fd[v -> g_id()] == v)
				continue;

			//Verifica se os pais estao na mesma particao(copia)
			//Verifica se os pais estao em particoes diferentes(novo)
			Vertice* b;
			bool encontrou = false;
			for (Vertice* a: v -> pais) {
				if (encontrou)
					break;
				if (fd[a -> g_id()] && !b) {	//Primeiro pai com particao
					b = fd[a -> g_id()];
					continue;
				}

				if (fd[a -> g_id()]) {
					if (fd[a -> g_id()] != b) {	//Pelo menos dois dos pais estao em particoes diferentes, cria nova
						fd[v -> g_id()] = v;
						encontrou = true;
						continue;
					}
				}
			}

			//Todos os pais na mesma particao, copia
			if (!encontrou)
				if (b) {
					fd[v -> g_id()] = b;
				} else
					throw runtime_error("Erro em cobertura_dominadores(), Caso faltando");
		}
	}
}

void encontra_subgrafos(Grafo* fonte, vector<Grafo*> &subgrafos)
{
	cout << "Encontrando subgrafos" << endl;
	list<Vertice*> raizes;
	encontra_raizes(fonte, raizes);

	cout << "Encontrou " << raizes.size() << " raizes\n";

	for (Vertice* v: raizes) {
		cout << "Criando subgrafo com " << v -> g_numero() << endl;
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
	for (Vertice* v: g -> atributos)
		v -> valor_int = -1;

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
		if (x -> valor_int <= v -> valor_int)
			x -> valor_int = v -> valor_int + 1;
		passar_geracao_filhos(x);
	}
}

void geracao_grafo_inferior(Grafo* g)
{
	for (Vertice* v: g -> atributos)
		v -> valor_int_2 = -1;

	list<Vertice*> folhas;
	encontra_folhas(g, folhas);

	for (Vertice* v: folhas) {
		v -> valor_int_2 = 0;
		passar_geracao_pais(v);
	}
}

void passar_geracao_pais(Vertice* v)
{
	for (Vertice* x: v-> pais) {
		x -> valor_int_2 = v -> valor_int_2 >= x -> valor_int_2 ? v -> valor_int_2 + 1 : x -> valor_int_2;
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
	cout << "Encontrando os aneis com algoritmo 1 linear" << endl;
	numero_aneis = 0;
	if (numero_casamentos > 3 || numero_casamentos < 1)
		throw runtime_error("Erro em encontra_aneis(), Numero de casamentos não suportado");

	//3.1
	//Encontra todas as junções do grafo
	Juncoes* jun = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, jun);
	//printf("Encontrou junções\n");

	//3.2.1
	//Encontra todos os casamentos do grafo (list<int> = 1 casamento)
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);
	//printf("Encontrou casamentos\n");

	//3.2.2
	//Encontra combinacoes
	list<list<list<int>>> conjuntos;
	encontra_combinacoes(casamentos, conjuntos, numero_casamentos);

	//define_min_max_cores(g);
	define_super_sob(g);

	//Geracap inferior em Vertice -> valor int 2 e superior em valor int
	geracao_grafo_inferior(g);
	geracao_grafo_superior(g);

	//3.3
	//Define os conjuntos a serem trabalhados e operam encontrando os aneis sobre eles
	if (numero_casamentos == 1) {
		encontra_aneis_a1(g, jun, conjuntos, destino);
	} else if (numero_casamentos == 2) {
		encontra_aneis_a2(g, jun, conjuntos, destino);
	} else {
		encontra_aneis_a3(g, jun, conjuntos, destino);
	}

	cout << "Numero de aneis: " << destino.size() << endl;
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

void encontra_aneis_a1(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos, list<Anel*>& destino)
{
	for (list<list<int>> casamentos: conjuntos) {
		for (list<int> c: casamentos) {
			//printf("Operando sobre conjunto: (%d, %d) \n", c.front(), c.back());

			//Encontra as juncoes do par
			int id_front = c.front();
			int id_back = c.back();
			JuncoesDe* par_juncao = juncoes -> juncoes[id_front][id_back];

			if (!par_juncao) {
				//Nao existe juncao para o par
				//printf("Casamento sem Juncao: %d e %d\n", c.front(), c.back());
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
}

void encontra_aneis_a2(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos_c, list<Anel*>& destino)
{
	clock_t inicio = clock();
	//Define conjunto c com 2 casamentos e trabalha nele
	for (list<list<int>> conjunto_c: conjuntos_c) {
		/*printf("Operando sobre conjunto: ");
		for (list<int> i: conjunto_c)
			printf("(%d,%d) ", i.front(), i.back());
		printf("\n");*/

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
			inicio = clock();
			//Para todo grupo de caminhos disjuntos fazer intersecção
			//Se intersecção for vazia, encontrou um anel
			list<Juncao*> juncoesUtilizadas;
			vector<list<Vertice*>> atual;
			encontra_aneis(c_aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas);
			tempo_encontra_anel += clock() - inicio;
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

void encontra_aneis_a3(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos_c, list<Anel*>& destino)
{
	//3.3
	//Define conjunto c com numero_casamentos casamentos e trabalha nele
	for (list<list<int>> conjunto_c: conjuntos_c) {
		/*printf("Operando sobre conjunto: ");
		for (list<int> i: conjunto_c)
			printf("(%d,%d) ", i.front(), i.back());
		printf("\n");*/

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
				JuncoesDe* par_juncao = juncoes -> juncoes[id_front][id_back];

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

void encontra_caminhos1(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<list<Vertice*>> &caminhos) {
	if (fonte == destino) {
		caminhos.push_back(caminho_atual);
		return;
	}

	for (Vertice* filho: fonte -> filhos){
		if (filho -> alcancaveis[destino -> g_id()] != 0) {
			list<Vertice*> caminho_aux(caminho_atual);
			caminho_aux.push_back(filho);
			encontra_caminhos1(filho, destino, caminho_aux, caminhos);
		}
	}
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
		if (com_cores) {
			int zi = 0;
			set<int>  cores;
			for (int i = juncoes -> min_cores[destino -> primeiro -> g_id()]; i <= juncoes -> max_cores[destino -> primeiro -> g_id()]; i++)
				encontra_caminhos_cores_especificas(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice], cores, i);

			for (int i =  juncoes -> min_cores[destino -> segundo -> g_id()]; i <= juncoes -> max_cores[destino -> segundo -> g_id()]; i++)
				encontra_caminhos_cores_especificas(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice], cores, i);	
		} else {
/**/
			//Encontra caminhos 1 utiliza somente informacao de alcancaveis
			encontra_caminhos1(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice]);
			encontra_caminhos1(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice]);

			//Encontra caminhos nao utiliza informacoes de cores
			//encontra_caminhos(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice]);
			//encontra_caminhos(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice]);
		}
/**/

		tempo_procura_caminhos += clock() - inicio;
		indice++;
	}

	//Encontra os caminhos disjuntos da juncao até os membros do par
	destino -> mudar_tamanho(juncao -> juncoes.size());
	indice = 0;
	for (Vertice* juncoes: juncao -> juncoes) {
		clock_t inicio = clock();
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
		tempo_sao_disjuntos += clock() - inicio;
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
		//MUDAR  adicionar condicoes
		if (filho -> max_cores[destino-> g_id()] + cores.size() < cores_restantes)
			continue;
		else if (filho -> min_cores[destino -> g_id()] == 0)
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

		delete novaJuncao;
	}


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
	inicio = clock();
	//verifica se intersecção é vazia
	for (int i = 0; i < caminhos.size(); i++) {
		for (int y = i + 1; y < caminhos.size(); y++) {
			if (!sao_disjuntos(caminhos[i], caminhos[y])) {
				tempo_sao_disjuntos += clock() - inicio;
				return;
			}
		}
	}
	tempo_sao_disjuntos += clock() - inicio;

	Anel* novo = new Anel();
	novo -> adicionar_elemento(caminhos, casamentos, juncoesUtilizadas);

	destino.push_back(novo);
	//destino.pop_back();
	//delete novo;

	//m_numero_aneis.lock();
	numero_aneis++;
	//m_numero_aneis.unlock();

	//Para escrever sempre que encontrar um anel
/*
	FILE* arquivo;
	arquivo = fopen("aneis/aneis_ordem_3.txt", "a");
	fputs(novo -> linha_normal.c_str(), arquivo);
	fclose(arquivo);

	delete novo;*/

	tempo_verifica_anel += clock() - inicio;
}

//Encontra os aneis de g com numero_casamentos casamentos e os escreve em destino
void encontra_aneis_coloridos(Grafo* g, list<Anel*>& destino, int numero_casamentos, bool paralelo)
{
	numero_aneis = 0;
	if (numero_casamentos > 3 || numero_casamentos < 1)
		return;

	//Encontra Junções
	//cout << "Encontrando Juncoes " << endl;
	Juncoes* juncoes = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, juncoes);

	//Encontra super e sob das cores
	//cout<<"Encontrando super e sob\n";
	define_super_sob(g);

	//Encontra todos os casamentos
	//cout<<"Encontrando os casamentos\n";
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);

	//Encontra todas as combinacoes
	//cout<<"Encontrando as combinacoes destes casamentos: " << casamentos.size() << endl;
	list<list<list<int>>> conjuntos;
	encontra_combinacoes(casamentos, conjuntos, numero_casamentos);

	//Encontra todos os pares de vertices utilizados
	set<Par*, par_cmp> pares;
	encontra_pares_vertices(juncoes, conjuntos, pares);
	//cout<<"Pares de vertices encontrados: " << pares.size() << endl;

	//Encontra todos os caminhos entre os pares de vertices
	int numero_threads = 1;	//Maior valor super, numero de threads utilizadas
	for (Vertice* v: g -> atributos)
		for (int i: v -> max_cores)
			numero_threads = i > numero_threads ? i : numero_threads;
	cout<<"Encontrando os caminhos com " << numero_threads << " threads" << endl;

	clock_t inicio_ = clock();
	vector<vector<list<Caminho*>>> caminhos(g -> g_numero_vertices(), vector<list<Caminho*>> (g -> g_numero_vertices()));
	encontra_caminhos_coloridos(pares, numero_threads, caminhos);
	tempo_procura_caminhos += clock() - inicio_;

	//Define o número de threads
	int m = 0;
	for (vector<list<Caminho*>> v: caminhos)
		for (list<Caminho*> l: v)
			for(Caminho* c: l)
				m = m > c -> cores.size() ? m : c -> cores.size();
	numero_threads = numero_threads < m ? numero_threads : m;
	numero_threads = numero_threads * 2 * numero_casamentos;
	numero_threads = numero_threads < g -> map -> tam() ? numero_threads : g -> map -> tam();

	//Encontra os aneis
	if (!paralelo) {
		//encontra os aneis linearmente
		cout<<"Encontrando os aneis com algoritmo 2 linear(" << numero_threads << ")"<< endl;
		encontra_aneis_coloridos(g, juncoes, conjuntos, caminhos, destino);
	} else {
		//encontra os anéis pelas threads
		cout<<"Encontrando os aneis com algoritmo 3 (" << numero_threads << "threads)" << endl;
/*
 	 	cout << "Encontrando linearmente pelo algoritmo paralelo\n";
		for (int i = 1; i <= numero_threads; i++) {
			cout << "Inicializando thread " << i << endl;
			encontra_aneis_coloridos_t(g, juncoes, conjuntos, caminhos, destino, i);
			cout << "Fim  " << destino.size() << endl;
		}*/
/*
 	 	cout << "Utilizando número maximo de threads\n";
		int max_threads = 10;
		thread threads[numero_threads];
		list<Anel*> destinos[numero_threads];
		sem_init(&s_thread, 0, max_threads);
		for (int i = 1; i <= numero_threads; i++) {
			sem_wait(&s_thread);
			cout << "Inicializando " << i << endl;
			threads[i-1] = thread(encontra_aneis_coloridos_t, g, juncoes, ref(conjuntos), ref(caminhos), ref(destinos[i - 1]), i);
		}

		for (int i = 1; i <= numero_threads; i++) {
			threads[i - 1].join();
		}

		for (int i = 0; i < numero_threads; i++) {
			destino.merge(destinos[i]);
		}
*/


		//cout << "Utilizando todas as threads de uma vez\n";
		thread threads[numero_threads];
		list<Anel*> destinos[numero_threads];
		sem_init(&s_thread, 0, 0);	//Nao utilizado
		for (int i = 1; i <= numero_threads; i++) {
			//cout << "Inicializando thread " << i << endl;
			threads[i-1] = thread(encontra_aneis_coloridos_t, g, juncoes, ref(conjuntos), ref(caminhos), ref(destinos[i-1]), i);
		}
		for (int i = 1; i <= numero_threads; i++) {
			threads[i-1].join();
		}
		for (int i = 0; i < numero_threads; i++) {
			destino.merge(destinos[i]);
		}

	}

	//Deleta estruturas criadas
	delete juncoes;
	for (Par* par: pares)
		delete par;
	for (vector<list<Caminho*>> v: caminhos)
		for (list<Caminho*> l: v)
			for (Caminho* c: l)
				delete c;

	if (!paralelo) {
		cout << " tempo_encontra_anel_aux " << (double) tempo_encontra_anel_p / CLOCKS_PER_SEC << endl;
		cout << " tempo_encontra_anel " << (double) tempo_encontra_anel / CLOCKS_PER_SEC<< endl;
		cout << " tempo_verifica_anel " << (double) tempo_verifica_anel / CLOCKS_PER_SEC<< endl;
		cout << " tempo_procura_caminhos " << (double) tempo_procura_caminhos / CLOCKS_PER_SEC << endl;
		cout << " tempo_copia_caminhos " << (double) tempo_copia_caminhos / CLOCKS_PER_SEC << endl;
		cout << " tempo_sao_disjuntos " << (double) tempo_sao_disjuntos /CLOCKS_PER_SEC << endl;
		/**/
	}

	cout << "Numero de aneis encontrados: " << destino.size() << endl;
}

void encontra_aneis_coloridos(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino)
{
	//Para todos conjuntos de casamentos
	for (list<list<int>> conjunto_c: conjuntos) {
		//Encontra combinacoes entre os casamentos
		list<list<list<int>>> combinacoes;
		switch(conjunto_c.size()) {
			case(1):
				combinacoes.push_back(conjunto_c);
				break;
			case(2):
				encontra_combinacoes_dupla(conjunto_c, combinacoes);
				break;
			case(3):
				encontra_combinacoes_trio(conjunto_c, combinacoes);
				break;
			default:
				return;
		}

		//Para todas combinacoes
		for (list<list<int>> c: combinacoes) {
			list<JuncoesDe*> juncoes_c;
			list<Anel_aux*> aneis_aux;
			bool adicionar = true;
			//Para todos os pares da combinacao
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();
				JuncoesDe* par_juncao = 0;

				//MUDAR (retirar para encontrar AxCk, x != k
				if (id_front == id_back) {
					adicionar = false;
					break;
				}

				//Adiciona a juncao do par
				par_juncao = juncoes -> juncoes[id_front][id_back];
				if (!par_juncao) {
					adicionar = false;
					break;
				}
				juncoes_c.push_back(par_juncao);
			}

			//Se todos os pares tem juncao, cria aneis aux
			if (adicionar) {
				clock_t inicio_ = clock();
				for (JuncoesDe* j: juncoes_c) {
					Anel_aux* aux = new Anel_aux();
					aneis_aux.push_back(aux);
					define_anel_aux_coloridos(j, aux, caminhos);
				}
				tempo_encontra_anel_p += clock() - inicio_;
			} else
				continue;

			clock_t inicio_encontra_anel = clock();
			list<Juncao*> juncoesUtilizadas;
			vector<list<Vertice*>> atual;
			encontra_aneis(aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas);
			tempo_encontra_anel += clock() - inicio_encontra_anel;

			for (Anel_aux* a: aneis_aux)
				delete a;
		}
	}
}

//Arranja os casamentos em numero_casamentos grupos e os escreve em conjuntos
void encontra_combinacoes(vector<list<int>> casamentos,	list<list<list<int>>> &conjuntos, int numero_casamentos)
{
	switch(numero_casamentos) {
	case(1):
			for (list<int> l: casamentos) {
				list<list<int>> novo_elemento;
				novo_elemento.push_back(l);

				conjuntos.push_back(novo_elemento);
			}
			break;
	case(2):
			encontra_duplas_casamentos(casamentos, conjuntos);
			break;
	case(3):
			encontra_trios_casamentos(casamentos, conjuntos);
			break;
	default:
			return;
	}

}

//Encontra todos os pares de vértices das junções presentes em conjuntos e os escreve em destino
void encontra_pares_vertices(Juncoes* juncoes, list<list<list<int>>> conjuntos, set<Par*, par_cmp> &destino)
{
	//Para todos conjuntos de casamentos
	for (list<list<int>> conjunto_c: conjuntos) {
		//Encontra combinacoes entre os casamentos
		list<list<list<int>>> combinacoes;
		switch(conjunto_c.size()) {
		case(1):
				combinacoes.push_back(conjunto_c);
				break;
		case(2):
				encontra_combinacoes_dupla(conjunto_c, combinacoes);
				break;
		case(3):
				encontra_combinacoes_trio(conjunto_c, combinacoes);
				break;
		default:
				return;
		}

		//Para todas combinacoes
		for (list<list<int>> c: combinacoes) {
			list<JuncoesDe*> juncoes_c;
			bool adicionar = true;
			//Para todos os pares da combinacao
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();
				JuncoesDe* par_juncao = 0;

				//MUDAR (retirar para encontrar AxCk, x != k
				if (id_front == id_back) {
					adicionar = false;
					break;
				}

				//Adiciona a juncao do par
				par_juncao = juncoes -> juncoes[id_front][id_back];
				if (!par_juncao) {
					adicionar = false;
					break;
				}
				juncoes_c.push_back(par_juncao);
			}

			//Se todos os pares tem juncao, adiciona aos pares
			if (adicionar) {
				for (JuncoesDe* j: juncoes_c) {
					Vertice* primeiro = j -> primeiro;
					Vertice* segundo = j -> segundo;
					pair<set<Par*>::iterator, bool> insert;

					for (Vertice* juncoes: j -> juncoes) {
						Par* novo_primeiro = new Par(juncoes, primeiro);
						insert = destino.insert(novo_primeiro);
						if (!insert.second)
							delete novo_primeiro;

						Par* novo_segundo = new Par(juncoes, segundo);
						insert = destino.insert(novo_segundo);
						if (!insert.second)
							delete novo_segundo;
					}
				}
			}
		}
	}
}

//Encontra caminhos(caminho e suas cores) com aé numero_threads cores e as escreve em destino
void encontra_caminhos_coloridos(set<Par*, par_cmp> &pares, short numero_threads, vector<vector<list<Caminho*>>> &destino)
{
	int grao = numero_threads == 1 ? pares.size() : pares.size() / (numero_threads * 10);
	grao = grao < 1 ? 1 : grao;

	set<Par*, par_cmp>::iterator it = pares.begin();
	thread threads[numero_threads];
	for (int i = 0; i < numero_threads; i++)
		threads[i] = thread(encontra_caminhos_coloridos_task, ref(pares), ref(it), ref(destino), grao);

	for (int i = 0; i < numero_threads; i++)
		threads[i].join();

	/*
	thread threads[numero_threads - 1];
	for (int i = 1; i < numero_threads; i++)
		threads[i - 1] = thread(encontra_caminhos_coloridos_t, ref(pares), i, ref(destino));

	for (int i = 1; i < numero_threads; i++)
		threads[i - 1].join();
	*/
}

//Encontra caminhos com numero_cores para todos os pares e ps escreve em destino
void encontra_caminhos_coloridos_t(set<Par*, par_cmp> pares, int numero_cores, vector<vector<list<Caminho*>>> &destino)
{
	int i = 0;
	vector<vector<list<Caminho*>>> caminhos(destino.size(), vector<list<Caminho*>> (destino[0].size()));
	for (Par* par: pares) {
		Vertice* fonte = par -> fonte;
		Vertice* destino = par -> destino;
		list<Vertice*> caminho_atual;
		set<int> cores;

		encontra_caminhos_cores_especificas(fonte, destino, caminho_atual, caminhos[fonte -> g_id()][destino -> g_id()], cores, numero_cores);
	}

	for (int i = 0; i < caminhos.size(); i++) {
		for (int y = 0; y < caminhos[i].size(); y++) {
			m_listas.lock();
			for (Caminho* c: caminhos[i][y]) {
				destino[i][y].push_back(c);
			}
			m_listas.unlock();
		}
	}
}

void encontra_caminhos_coloridos_task(set<Par*, par_cmp> &pares, set<Par*, par_cmp>::iterator &iterator, vector<vector<list<Caminho*>>> &destino, int grao)
{
	while(iterator != pares.end()) {
		list<Par*> atuais;
		list<list<Caminho*>> c_atuais;
		m_listas.lock();
		for (int i = 0; i < grao, iterator != pares.end(); i++, iterator++) {
			atuais.push_back(*iterator);
		}
		m_listas.unlock();

		for (Par* par: atuais) {
			Vertice* fonte = par -> fonte;
			Vertice* dest = par -> destino;

			list<Vertice*> caminho_atual;
			list<Caminho*> c_destino;
			set<int> cores;
			for (int i = 1; i <= fonte -> max_cores[dest -> g_id()]; i++)
				encontra_caminhos_cores_especificas(fonte, dest, caminho_atual, c_destino, cores, i);
			c_atuais.push_back(c_destino);
		}

		m_numero_aneis.lock();
		for (Par* par: atuais) {
			Vertice* fonte = par -> fonte;
			Vertice* dest = par -> destino;

			list<Caminho*> ca = c_atuais.front();
			c_atuais.pop_front();
			for (Caminho* c: ca)
				destino[fonte -> g_id()][dest -> g_id()].push_back(c);
		}
		m_numero_aneis.unlock();
	}
}

//Encontra caminhos com cores_restantes, escrevendo as cores e os vértices encontrados em caminhos
void encontra_caminhos_cores_especificas(Vertice* fonte, Vertice* destino,list<Vertice*> caminho_atual, list<Caminho*> &caminhos, set<int> cores, int cores_restantes)
{
	bool nova_cor = cores.insert(fonte -> cor_int).second;
	if (nova_cor)
		cores_restantes--;
	if (cores_restantes < 0)
		return;
	if (fonte == destino && cores_restantes == 0) {
		Caminho* novo = new Caminho(caminho_atual, cores);
		caminhos.push_back(novo);
		return;
	}

	for (Vertice* filho: fonte -> filhos){
		//MUDAR  colocar condicao
		if (filho -> max_cores[destino-> g_id()] + cores.size() < cores_restantes)
			continue;
		else if (filho -> min_cores[destino -> g_id()] == 0)
			continue;

		list<Vertice*> caminho_aux(caminho_atual);
		caminho_aux.push_back(filho);
		encontra_caminhos_cores_especificas(filho, destino, caminho_aux, caminhos, cores, cores_restantes);
	}
}

void define_anel_aux_coloridos(JuncoesDe* juncao, Anel_aux* destino, vector<vector<list<Caminho*>>> &caminhos)
{
	destino -> primeiro = juncao -> primeiro;
	destino -> segundo = juncao -> segundo;

	//Encontra os caminhos da juncao até os mebros do par que tenham no maximo numero_cores cores
	list<Caminho*> caminhos_front[juncao -> juncoes.size()];
	list<Caminho*> caminhos_back[juncao -> juncoes.size()];

	clock_t inicio = clock();
	int indice = 0;
	for (Vertice* juncoes: juncao->juncoes) {
		caminhos_front[indice] = list<Caminho*> (caminhos[juncoes -> g_id()][juncao -> primeiro -> g_id()]);
		caminhos_back[indice] = list<Caminho*> (caminhos[juncoes -> g_id()][juncao -> segundo -> g_id()]);
		indice++;
	}
	tempo_copia_caminhos += clock() - inicio;

	inicio = clock();
	//Encontra os caminhos disjuntos da juncao até os membros do par
	destino -> mudar_tamanho(juncao -> juncoes.size());
	indice = 0;
	for (Vertice* juncoes: juncao -> juncoes) {
		int i = 0;
		int tam_max = (caminhos_front[indice].size() + 1) * (caminhos_back[indice].size() + 1);
		destino -> juncoes[indice] = juncoes;
		destino -> caminhos_primeiro[indice].resize(tam_max);
		destino -> caminhos_segundo[indice].resize(tam_max);
		for (Caminho* caminho_a: caminhos_front[indice]) {
			for (Caminho* caminho_b: caminhos_back[indice]) {
				if (sao_disjuntos(caminho_a -> caminho, caminho_b -> caminho)) {
					destino -> caminhos_primeiro[indice][i] = caminho_a -> caminho;
					destino -> caminhos_segundo[indice][i] = caminho_b -> caminho;
					i++;
				}
			}
		}
		indice++;
	}
	tempo_sao_disjuntos += clock() - inicio;
}

void define_anel_aux_coloridos_t(JuncoesDe* juncao, Anel_aux* destino, vector<vector<list<Caminho*>>> &caminhos)
{
	destino -> primeiro = juncao -> primeiro;
	destino -> segundo = juncao -> segundo;
	destino -> maior_numero_cores = 1;
	destino -> menor_numero_cores = INT_MAX;

	//Encontra os caminhos da juncao até os mebros do par que tenham no maximo numero_cores cores
	list<Caminho*> caminhos_front[juncao -> juncoes.size()];
	list<Caminho*> caminhos_back[juncao -> juncoes.size()];

	clock_t inicio = clock();
	int indice = 0;
	for (Vertice* juncoes: juncao->juncoes) {
		caminhos_front[indice] = list<Caminho*> (caminhos[juncoes -> g_id()][juncao -> primeiro -> g_id()]);
		caminhos_back[indice] = list<Caminho*> (caminhos[juncoes -> g_id()][juncao -> segundo -> g_id()]);
		indice++;
	}
	tempo_copia_caminhos += clock() - inicio;

	inicio = clock();
	//Encontra os caminhos disjuntos da juncao até os membros do par
	destino -> mudar_tamanho(juncao -> juncoes.size());
	indice = 0;
	for (Vertice* juncoes: juncao -> juncoes) {
		int i = 0;
		int tam_max = (caminhos_front[indice].size() + 1) * (caminhos_back[indice].size() + 1);
		destino -> juncoes[indice] = juncoes;
		destino -> caminhos_primeiro[indice].resize(tam_max);
		destino -> caminhos_segundo[indice].resize(tam_max);
		destino -> cores[indice].resize(tam_max);
		for (Caminho* caminho_a: caminhos_front[indice]) {
			for (Caminho* caminho_b: caminhos_back[indice]) {
				if (sao_disjuntos(caminho_a -> caminho, caminho_b -> caminho)) {
					set<int> cores = soma(caminho_a -> cores, caminho_b -> cores);
					destino -> caminhos_primeiro[indice][i] = caminho_a -> caminho;
					destino -> caminhos_segundo[indice][i] = caminho_b -> caminho;
					destino -> cores[indice][i] = set<int>(cores);
					destino -> maior_numero_cores = destino -> maior_numero_cores > cores.size() ? destino -> maior_numero_cores : cores.size();
					destino -> menor_numero_cores = destino -> menor_numero_cores < cores.size() ? destino -> menor_numero_cores : cores.size();
					i++;
				}
			}
		}
		indice++;
	}
	tempo_sao_disjuntos += clock() - inicio;
}

set<int> soma(set<int> a, set<int> b)
{
	set<int> retorno = set<int> (a);
	for (int i: b)
		retorno.insert(i);

	return retorno;
}

void encontra_aneis_coloridos(list<Anel_aux*> aux, vector<list<Vertice*>> &atual, list<Anel*> & destino, list<list<int>> &casamentos, list<Juncao*> &juncoesUtilizadas, int numero_cores, set<int> &cores,int maior_caminho, int menor_caminho)
{
	//Chegou ao ultimo grupo da combinação
	if (aux.size() == 0) {
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
			set<int> cores_aux = soma(anel_a -> cores[i][y], cores);
			//Cor de nova junção ja está na lista de cores

			if (cores_aux.size() > numero_cores)
				continue;
			if (aux.size() * maior_caminho + cores_aux.size() < numero_cores) {
				continue;
			}

			atual_aux.push_back(anel_a -> caminhos_primeiro[i][y]);
			atual_aux.push_back(anel_a -> caminhos_segundo[i][y]);

			encontra_aneis_coloridos(aux, atual_aux, destino, casamentos, juncoes_aux, numero_cores, cores_aux, maior_caminho, menor_caminho);
		}

		delete novaJuncao;
	}
}

void encontra_aneis_coloridos_t(Grafo* g, Juncoes* juncoes, list<list<list<int>>> conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino, int numero_cores)
{
	//Para todos conjuntos de casamentos
	for (list<list<int>> conjunto_c: conjuntos) {
		//Encontra combinacoes entre os casamentos
		list<list<list<int>>> combinacoes;
		switch(conjunto_c.size()) {
		case(1):
				combinacoes.push_back(conjunto_c);
				break;
		case(2):
				encontra_combinacoes_dupla(conjunto_c, combinacoes);
				break;
		case(3):
				encontra_combinacoes_trio(conjunto_c, combinacoes);
				break;
		default:
				return;
		}

		//Para todas combinacoes
		for (list<list<int>> c: combinacoes) {
			list<JuncoesDe*> juncoes_c;
			list<Anel_aux*> aneis_aux;
			bool adicionar = true;
			int maior_caminho = 1;
			int menor_caminho = INT_MAX;
			//Para todos os pares da combinacao
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();
				JuncoesDe* par_juncao = 0;

				//MUDAR (retirar para encontrar AxCk, x != k
				if (id_front == id_back) {
					adicionar = false;
					break;
				}

				//Adiciona a juncao do par
				par_juncao = juncoes -> juncoes[id_front][id_back];
				if (!par_juncao) {
					adicionar = false;
					break;
				}
				juncoes_c.push_back(par_juncao);
			}

			//Se todos os pares tem juncao, cria aneis aux
			if (adicionar) {
				for (JuncoesDe* j: juncoes_c) {
					Anel_aux* aux = new Anel_aux();
					aneis_aux.push_back(aux);
					define_anel_aux_coloridos_t(j, aux, caminhos);
					maior_caminho = maior_caminho > aux -> maior_numero_cores ? maior_caminho : aux -> maior_numero_cores;
					menor_caminho = menor_caminho < aux -> menor_numero_cores ? menor_caminho : aux -> menor_numero_cores;
				}
			} else
				continue;

			if (menor_caminho <= numero_cores) {
				list<Juncao*> juncoesUtilizadas;
				vector<list<Vertice*>> atual;
				set<int> cores;
				encontra_aneis_coloridos(aneis_aux, atual, destino, conjunto_c, juncoesUtilizadas, numero_cores, cores, maior_caminho, menor_caminho);
			}

			for (Anel_aux* a: aneis_aux)
				delete a;
		}
	}

	sem_post(&s_thread);
	//cout << "Terminou de encontrar aneis com " << numero_cores << " cores\n";
}

void colorir_grafo_esp(Grafo* g, int n)
{
	descolorir(g);

	int i = 0;
	for (Vertice* v: g -> atributos) {
		v -> adicionar_cor(i);
		i = i + 1 >= n ? 0 : i + 1;
	}
}

void encontra_aneis_paralelos_vetor (Grafo* g, list<Anel*>& destino, int numero_casamentos, int numero_threads_total, int grao)
{
	cout << "Encontrando os aneis com algoritmo 2 paralelo" << endl;
	numero_aneis = 0;
	if (numero_casamentos > 3 || numero_casamentos < 1)
		return;

	//Encontra Junções
	//cout << "Encontrando Juncoes " << endl;
	Juncoes* juncoes = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, juncoes);

	//Encontra super e sob das cores
	//cout<<"Encontrando super e sob\n";
	define_super_sob(g);

	//Encontra todos os casamentos
	//cout<<"Encontrando os casamentos\n";
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);

	//Encontra todas as combinacoes
	//cout<<"Encontrando as combinacoes destes casamentos: " << casamentos.size() << endl;
	list<list<list<int>>> conjuntos;
	encontra_combinacoes(casamentos, conjuntos, numero_casamentos);

	//Encontra todos os pares de vertices utilizados
	set<Par*, par_cmp> pares;
	encontra_pares_vertices(juncoes, conjuntos, pares);
	//cout<<"Pares de vertices encontrados: " << pares.size() << endl;

	//Encontra todos os caminhos entre os pares de vertices
	cout<<"Encontrando os caminhos com " << numero_threads_total << " threads" << endl;
	clock_t inicio_ = clock();
	vector<vector<list<Caminho*>>> caminhos(g -> g_numero_vertices(), vector<list<Caminho*>> (g -> g_numero_vertices()));
	encontra_caminhos_coloridos(pares, numero_threads_total, caminhos);
	tempo_procura_caminhos += clock() - inicio_;

	//cout << "Encontrando os aneis" << endl;
	thread threads[numero_threads_total];
	list<Anel*> destinos[numero_threads_total];
	for (int i = 0; i < numero_threads_total; i++) {
		//cout << "Inicioando thread " << i << endl;
		threads[i] = thread(thread_encontra_aneis_vetor, g, juncoes, ref(conjuntos), ref(caminhos), ref(destinos[i]), grao);
	}

	for (int i = 0; i < numero_threads_total; i++) {
		//cout << "Esperando por thread " << i << endl;
		threads[i].join();
	}

	for (int i = 0; i < numero_threads_total; i++) {
		destino.merge(destinos[i]);
	}

	//Deleta estruturas criadas
	delete juncoes;
	for (Par* par: pares)
		delete par;
	for (vector<list<Caminho*>> v: caminhos)
		for (list<Caminho*> l: v)
			for (Caminho* c: l)
				delete c;

	cout << "Numero de aneis encontrados: " << destino.size() << endl;
}

void thread_encontra_aneis_vetor(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino, int grao)
{
	while(conjuntos.size() > 0) {
		list<list<list<int>>> atual;
		m_listas.lock();
		for (int i = 0; i < grao && conjuntos.size() > 0; i++) {
			atual.push_back(conjuntos.front());
			conjuntos.pop_front();
		}
		m_listas.unlock();

		encontra_aneis_coloridos(g, juncoes, atual, caminhos, destino);
	}
}

void encontra_aneis_paralelos_procurando(Grafo* g, list<Anel*>& destino, int numero_casamentos, int numero_threads_total, int grao)
{
	cout << "Encontrando os aneis com algoritmo 1 paralelo" << endl;
	numero_aneis = 0;
	if (numero_casamentos > 3 || numero_casamentos < 1)
		return;

	//Encontra Junções
	//cout << "Encontrando Juncoes " << endl;
	Juncoes* juncoes = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, juncoes);

	//Encontra super e sob das cores
	//cout<<"Encontrando super e sob\n";
	define_super_sob(g);

	//Encontra todos os casamentos
	//cout<<"Encontrando os casamentos\n";
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);

	//Encontra todas as combinacoes
	//cout<<"Encontrando as combinacoes destes casamentos: " << casamentos.size() << endl;
	list<list<list<int>>> conjuntos;
	encontra_combinacoes(casamentos, conjuntos, numero_casamentos);

	//cout << "Encontrando os aneis" << endl;
	thread threads[numero_threads_total];
	list<Anel*> destinos[numero_threads_total];
	for (int i = 0; i < numero_threads_total; i++) {
		//cout << "Inicioando thread " << i << endl;
		threads[i] = thread(thread_encontra_aneis_procurando, g, juncoes, ref(conjuntos), ref(destinos[i]), grao);
	}

	for (int i = 0; i < numero_threads_total; i++) {
		//cout << "Esperando por thread " << i << endl;
		threads[i].join();
	}

	for (int i = 0; i < numero_threads_total; i++) {
		destino.merge(destinos[i]);
	}

	//Deleta estruturas criadas
	delete juncoes;

	cout << "Numero de aneis encontrados: " << destino.size() << endl;
}

void thread_encontra_aneis_procurando(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, list<Anel*> &destino, int grao)
{
	while(conjuntos.size() > 0) {
		list<list<list<int>>> atual;
		m_listas.lock();
		for (int i = 0; i < grao && conjuntos.size() > 0; i++) {
			atual.push_back(conjuntos.front());
			conjuntos.pop_front();
		}
		m_listas.unlock();

		if (atual.front().size() == 1)
			encontra_aneis_a1(g, juncoes, atual, destino);
		else if (atual.front().size() == 2)
			encontra_aneis_a2(g, juncoes, atual, destino);
		else
			encontra_aneis_a3(g, juncoes, atual, destino);
	}
}

void encontra_aneis_coloridos_algo3_pool(Grafo* g, list<Anel*>& destino, int numero_casamentos, int num_threads, int grao)
{
	cout << "Encontrando os aneis com algoritmo 3 paralelo alterado" << endl;
	numero_aneis = 0;
	if (numero_casamentos > 3 || numero_casamentos < 1)
		return;

	//Encontra Junções
	cout << "Encontrando Juncoes " << endl;
	Juncoes* juncoes = new Juncoes(g -> g_numero_vertices());
	encontra_juncoes(g, juncoes);

	//Encontra super e sob das cores
	cout<<"Encontrando super e sob\n";
	define_super_sob(g);

	//Encontra todos os casamentos
	cout<<"Encontrando os casamentos\n";
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);

	//Encontra todas as combinacoes
	cout<<"Encontrando as combinacoes destes casamentos: " << casamentos.size() << endl;
	list<list<list<int>>> conjuntos;
	encontra_combinacoes(casamentos, conjuntos, numero_casamentos);

	//Encontra todos os pares de vertices utilizados
	set<Par*, par_cmp> pares;
	encontra_pares_vertices(juncoes, conjuntos, pares);
	cout<<"Pares de vertices encontrados: " << pares.size() << endl;

	//Encontra todos os caminhos entre os pares de vertices
	cout<<"Encontrando os caminhos com " << num_threads << " threads" << endl;
	vector<vector<list<Caminho*>>> caminhos(g -> g_numero_vertices(), vector<list<Caminho*>> (g -> g_numero_vertices()));
	encontra_caminhos_coloridos(pares, num_threads, caminhos);

	//Calcula o maior numero de cores possiveis em um anel
	int max_cores = 0;
	for (vector<list<Caminho*>> v: caminhos)
		for (list<Caminho*> l: v)
			for(Caminho* c: l)
				max_cores = max_cores > c -> cores.size() ? max_cores : c -> cores.size();
	max_cores = max_cores * 2 * numero_casamentos;
	max_cores = max_cores < g -> map -> tam() ? max_cores : g -> map -> tam();


	cout << "Encontrando os aneis" << endl;
	thread threads[num_threads];
	list<Anel*> destinos[num_threads];
	for (int i = 0; i < num_threads; i++) {
		cout << "Inicioando thread " << i << endl;
		threads[i] = thread(thread_encontra_aneis_coloridos_algo3_pool, g, juncoes, ref(conjuntos), ref(caminhos), ref(destinos[i]), grao, max_cores);
	}

	for (int i = 0; i < num_threads; i++) {
		cout << "Esperando por thread " << i << endl;
		threads[i].join();
	}

	for (int i = 0; i < num_threads; i++) {
		destino.merge(destinos[i]);
	}

	//Deleta estruturas criadas
	delete juncoes;
	for (Par* par: pares)
		delete par;
	for (vector<list<Caminho*>> v: caminhos)
		for (list<Caminho*> l: v)
			for (Caminho* c: l)
				delete c;

	cout << "Numero de aneis encontrados: " << destino.size() << endl;
}

void thread_encontra_aneis_coloridos_algo3_pool(Grafo* g, Juncoes* juncoes, list<list<list<int>>> &conjuntos, vector<vector<list<Caminho*>>> &caminhos, list<Anel*> &destino, int grao, int max_cores)
{
	while(conjuntos.size() > 0) {
		list<list<list<int>>> atual;
		m_listas.lock();
		for (int i = 0; i < grao && conjuntos.size() > 0; i++) {
			atual.push_back(conjuntos.front());
			conjuntos.pop_front();
		}
		m_listas.unlock();

		for (int i = 1; i < max_cores; i++)
			encontra_aneis_coloridos_t(g, juncoes, atual, caminhos, destino, i);
	}
}

//Encontra os aneis de "fonte" que tenham "num_cores" cores e que as cores estejam dividas pelas juncoes
void encontra_aneis_NOME_A_DEFINIR(list<Anel*> fonte, list<Anel*> &destino, int num_cores)
{
	cout << "NOME A DEFINIR :)\n";
	for (Anel* anel: fonte) {
		if (anel -> cores.size() != num_cores)
			continue;
		bool adicionar = true;
		for (list<Vertice*> lista: anel -> caminhos) {
			int cor_atual = lista.front() -> cor_int;
			for (Vertice* v: lista) {
				if (cor_atual != v -> cor_int) {
					adicionar = false;
					break;
				}
			}
			if (!adicionar)
				break;
		}
		if (adicionar)
			destino.push_back(anel);
	}
}

//Melhorar
int** multiplica_matrizes(int** m1, int** m2, int n) {
	int ** retorno = new int*[n];
	for (int i = 0; i < n; i++)
		retorno[i] = new int[n];

	for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            retorno[i][j] = 0;

            for (int k = 0; k < n; k++) {
                if (m1[i][k] * m2[k][j]) {
					retorno[i][j] = 1;
					break;
				}
				//retorno[i][j] += m1[i][k] * m2[k][j];
            }
        }
    }

	return retorno;
}

//Melhorar
int** encontra_alcancaveis(int** grafo, int n) {
	int** proxima = multiplica_matrizes(grafo, grafo, n);

	int i = n / 2;
	while(i > 0) {
		int** aux = proxima;
		proxima = multiplica_matrizes(proxima, proxima, n);

		delete aux;
		i = i / 2;
	}

	return proxima;
}

void dfs(Vertice* v) {
	v -> valor_bool = true;
	for (Vertice* u: v -> filhos) {
		if (!u -> valor_bool) {
			dfs(u);
		}
	}
}

void encontra_alcancaveis_dfs(Grafo* g) {
	for (Vertice* v: g -> atributos) {
		v -> valor_bool = false;
		v -> alcancaveis = vector<int>(g -> g_numero_vertices(), 0);
	}

	for (Vertice* v: g -> atributos) {
		dfs(v);
		for (Vertice* u: g -> atributos) {
			if (u -> valor_bool) {
				u -> valor_bool = false;
				v -> alcancaveis[u -> g_id()] = 1;
			}
		}
	}
}

