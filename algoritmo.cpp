#include "algoritmo.h"

void busca_em_largura(int** grafo, int tamanho, int* arvore) {
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

void busca_em_profundidade(int**grafo, int tamanho, int* arvore) {
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
		busca_em_profundidade_(grafo, tamanho, atributos_vertices, vertice, arvore, sem_set);
	}

	//desaloca os atributos
	for(int i = 0; i < tamanho; i++)
	{
		free (atributos_vertices[i]);
	}
}

void busca_em_profundidade_(int** grafo, int tamanho, Atributos_profundidade* atributos_vertices[], int vertice, int* arvore, list<int>& sem_set)
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
				busca_em_profundidade_(grafo, tamanho, atributos_vertices, i, arvore, sem_set);
			}
		}
	}
	atributos_vertices[vertice]->cor = 2;
	atributos_vertices[vertice]->tempo_fim = ++tempo;
}

void busca_componentes_conexas(int** grafo, int tamanho, list<list<int>>& destino) {
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

		busca_em_largura_(grafo, tamanho, lista, vertice);

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

void busca_em_largura_(int** grafo, int tamanho, list<int>& destino, int fonte)
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
			if (grafo[i][vertice] == 1)
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
		atributos -> nodo = new Nodo(v -> id);
		v-> atributo = atributos;
		sem_set.push_back(v);
	}

	while (!sem_set.empty())
	{
		//Primeiro vertice que nao esta em nenhuma arvore
		atual = sem_set.front();
		sem_set.pop_front();

		//Vertice sera uma raiz
		aux = ((Atributos_largura_lista* )atual -> atributo) -> nodo;
		raiz.push_back(aux);

		//Marca vertice
		((Atributos_largura_lista* )atual -> atributo) -> cor = 1;
		fila.push(atual);

		//Procura os alcancaveis por ele
		while (!fila.empty())
		{
			atual = fila.front();
			fila.pop();
			aux = ((Atributos_largura_lista* )atual -> atributo) -> nodo;
			for (Vertice* v: atual -> adjs)
			{
				if (((Atributos_largura_lista* )v -> atributo) -> cor == 0) {
					((Atributos_largura_lista* )v -> atributo) -> cor = 1;
					((Atributos_largura_lista* )v -> atributo) -> nodo -> adicionar_anterior(aux);
					fila.push(v);

				}
			}
			sem_set.remove(atual);
		}
	}

	//Liberacao do espaco alocado aos atributos
	for (Vertice* v: grafo)
	{
		free(v -> atributo);
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
		v-> atributo = atributos;
	}

	Nodo* aux;

	for (Vertice* v: grafo)
	{
		if (((Atributos_profundidade_lista*) v -> atributo) -> cor == 0) {
			//Vertice sera uma raiz
			aux = new Nodo(v -> id);
			((Atributos_profundidade_lista* )v -> atributo) -> nodo = aux;
			raiz.push_back(aux);


			((Atributos_profundidade_lista* )v -> atributo) -> tempo = 0;
			busca_em_profundidade_listas_adjacencia_(grafo, v);
		}
	}

	//Liberacao do espaco alocado aos atributos
	for (Vertice* v: grafo)
	{
		free(v -> atributo);
	}
}

void busca_em_profundidade_listas_adjacencia_(list<Vertice*>& grafo, Vertice* v) {
	((Atributos_profundidade_lista* )v -> atributo) -> cor = 1;
	Nodo* aux;
	Nodo* aux1;
	Atributos_profundidade_lista* att_v = ((Atributos_profundidade_lista* )v -> atributo);
	Atributos_profundidade_lista* att_vertice;

	for (Vertice* vertice: v -> adjs)
	{
		att_vertice = (Atributos_profundidade_lista*) vertice -> atributo;
		if (att_vertice -> cor == 0) {
			aux1 = ((Atributos_profundidade_lista*) v -> atributo) -> nodo;
			aux = new Nodo(vertice -> id, aux1);
			aux1 -> adicionar_filho(aux);

			att_vertice -> cor = 1;
			att_vertice -> tempo = att_v ->tempo + 1;
			busca_em_profundidade_listas_adjacencia_(grafo, vertice);
		}
	}
}

void descolorir(Grafo* g)
{
	for (Atributos_vertice* v: g -> atributos)
	{
		v -> cor.clear();
	}
}

void colorir_grafo(Grafo* g)
{
	int** grafo = g -> grafo;
	if (grafo == NULL) return;

	//Busca fontes
	list<int> fontes;
	busca_fontes(grafo, g -> numero_vertices, fontes);


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

void colorir_apartir_de(Grafo* g,int vertice)
{
	int** grafo = g -> grafo;
	if (grafo == NULL) return;

	//Atributos
	queue<int> fila;
	int tamanho = g -> numero_vertices;
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
	if (grafo == NULL) return;

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
	if (grafo == NULL) return;

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
		int tamanho = g -> numero_vertices;
		int** grafo = g-> grafo;
		for (int i = 0; i < tamanho; i++)
	{
		eh_fonte = true;
		for (int y = 0; y < tamanho; y++)
		{
			if (grafo[i][y] == 3 || grafo[i][y] == 13)
				{eh_fonte = false; break;}	//Vertice i tem um arco chegando nele
		}
		if (eh_fonte && g -> encontrar_atributo(i) -> tipo == tipo)
			{destino.push_back(i);}	//adiciona i como fonte na lista
	}
}

void colorir_apartir_de_tipo (Grafo* g, int vertice, char tipo)
{
	int** grafo = g -> grafo;
	if (grafo == NULL) return;

	//Atributos
	queue<int> fila;
	int tamanho = g -> numero_vertices;
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
					if (g -> encontrar_atributo(i) -> tipo == tipo)
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

void define_max_cores(Grafo* g)
{
	queue<Atributos_vertice*> fila;
	list<Lista_lista*> lista_cores[g -> numero_vertices];

	//Para saber qual folha tem o maior numero de cores
	vector<Atributos_vertice*> folhas[g -> numero_vertices];

	for (Atributos_vertice* v: g -> atributos)
	{
		v -> valor_bool = false;

		if (v -> filhos.size() == 0) {	//if eh_folha
			int id = v -> id;
			Lista_int* v_cor = new Lista_int();
			for (int i: v -> cor) {
				v_cor -> adicionar(i);
			}
			Lista_lista* nova_lista = new Lista_lista();
			nova_lista -> adicionar(v_cor);

			//Para saber qual folha tem o maior numero de cores
			folhas[id].push_back(v);

			lista_cores[id].push_back(nova_lista);
			fila.push(v);
		}
	}

	Atributos_vertice* v;
	while(!fila.empty())
	{
		v = fila.front();
		fila.pop();

		if (v -> valor_bool)
			continue;

		int v_id = v -> id;

		bool prox_while= false;
		for (Atributos_vertice* filho: v -> filhos) {
			if (filho -> valor_bool == false) {
				prox_while = true;
				fila.push(v);
				break;
			}
		}
		if (prox_while) continue;

		for (Atributos_vertice* pai: v -> pais)
		{
			int i = pai -> id;
			Lista_int* pai_cor = new Lista_int();
			for (int y: pai -> cor) {
				pai_cor -> adicionar(y);
			}
			Lista_lista* nova_lista_pai;
			int id_vector = 0;
			for (Lista_lista* lista: lista_cores[v_id])
			{
				bool adicionar = true;
				nova_lista_pai = lista -> copiar();
				nova_lista_pai -> adicionar(pai_cor -> copiar_lista());
				for (Lista_lista* l: lista_cores[i])
				{
					if (l -> eh_igual(nova_lista_pai)) {
						adicionar = false;
						break;
					}
				}
				if (adicionar) {
					lista_cores[i].push_back(nova_lista_pai);

					//Para saber qual folha tem o maior numero de cores
					folhas[i].push_back(folhas[v_id][id_vector]);
				} else
					delete nova_lista_pai;
				id_vector++;
			}
			delete pai_cor;
			fila.push(pai);
		}

		v -> valor_bool = true;
	}

	int tamanho;
	int id_folha;
	int y;
	for (int i = 0; i < g -> numero_vertices; i++)
	{
		tamanho = 0;
		y = 0;
		id_folha = 0;
		for (Lista_lista* lista: lista_cores[i])
		{
			if (lista -> tamanho > tamanho) {
				tamanho = lista -> tamanho;
				id_folha = y;
			}
			delete lista;
			y++;
		}
		Atributos_vertice* v = g -> encontrar_atributo(i);
		v -> cores_ate_folha = tamanho;


		//Para saber qual folha tem o maior numero de cores
		y = 0;
		v -> folha_cores = v;
		for (Atributos_vertice* a: folhas[i]) {
			if (y == id_folha)
				v -> folha_cores = a;
			y++;
		}
	}
}

void ordem_topologica(Atributos_vertice* fonte, stack<Atributos_vertice*>& destino)
{
	fonte -> valor_bool = true;

	//Busca em profundidade todos os filhos
	for (Atributos_vertice* filho: fonte -> filhos) {
		if (!filho -> valor_bool)
			ordem_topologica(filho, destino);
	}

	//Quando termina busca de todos os filhos, insere vertice na pilha
	destino.push(fonte);
}

void encontra_juncoes(Grafo* g, list<Juncao*>& destino)
{
	stack<Atributos_vertice*> vs;

	for(Atributos_vertice* s: g -> atributos)
	{
		for(Atributos_vertice* a: g -> atributos)
			a -> valor_bool = false;

		ordem_topologica(s, vs);
		for(Atributos_vertice* a: g -> atributos)
		{
			a -> particao = -1;
			a -> valor_bool = false;
		}

		s -> particao = s -> id;
		//assert(vs.front() -> id == s -> id);
		vs.pop();

		Atributos_vertice* v;
		while(!vs.empty())
		{
			v = vs.top();
			vs.pop();

			if (v -> pais.size() == 2) {
				if ((v -> pais.front() -> particao == -1) && (v -> pais.back() -> particao == -1)) {
					printf("Erro, pais do vertice nao mapeados");
					destino.clear();
					return;
				} else if (v -> pais.front() -> id == s -> id || v -> pais.back() -> id == s -> id) {
					v -> particao = v -> id;
				} else if (v -> pais.front() -> particao == -1) {
					v -> particao = v -> pais.back() -> particao;
				} else if (v -> pais.back() -> particao == -1) {
					v -> particao = v -> pais.front() -> particao;
				} else if (v -> pais.front() -> particao != v -> pais.back() -> particao) {
					v -> particao = v -> id;
				} else {
					v -> particao = v -> pais.front() -> particao;
				}

			} else if (v -> pais.size() == 1) {
				if (v -> pais.front() -> id == s -> id)
					v -> particao = v -> id;
				else
					v -> particao = v -> pais.front() -> particao;
			} else {
				printf("Erro, vertice fonte no meio da ordenacao");
				destino.clear();
				return;
			}
		}

		//Juncoes
		for (Atributos_vertice* a1: g -> atributos)
		{
			if (a1 -> particao != -1) {
				for (Atributos_vertice* a2: g -> atributos)
				{
					if(!a2 -> valor_bool) {
						if (a1 -> particao != a2 -> particao && a2 -> particao != -1) {
							destino.push_back(new Juncao(a1, a2, s));
						}
					}
				}
			}
			a1 -> valor_bool = true;
		}
	}
}

void encontra_juncoes(Grafo* g, list<JuncoesDe*>& destino)
{
	list<Juncao*> juncoes;
	encontra_juncoes(g, juncoes);

	JuncoesDe* jun[g -> numero_vertices][g->numero_vertices];
	JuncoesDe* aux;
	for (int i = 0; i < g -> numero_vertices; i++) {
		for (int j = i + 1; j < g -> numero_vertices; j++) {
			Atributos_vertice* e1 = g -> encontrar_atributo(i);
			Atributos_vertice* e2 = g -> encontrar_atributo(j);
			aux = new JuncoesDe(e1, e2);

			jun[i][j] = aux;
			jun[j][i] = aux;
			destino.push_back(aux);
		}
	}

	for (Juncao* j: juncoes) {
		jun[j -> primeiro -> id][j -> segundo -> id] -> adicionar_juncao(j -> juncao);
	}
}

void encontra_casamentos(Grafo* g, list<list<int>>& casamentos)
{
	for (int i = 0; i < g -> numero_vertices; i++) {
		for (int j = i + 1; j < g -> numero_vertices; j++) {
			if (g -> grafo[i][j] == 1 || g -> grafo[i][j] == 12 || g -> grafo[i][j] == 13) {
				list<int> casamento;
				casamento.push_back(i);
				casamento.push_back(j);

				casamentos.push_back(casamento);
			}
		}
	}
}

void encontra_casamentos(Grafo* g, vector<list<int>>& casamentos)
{
	for (int i = 0; i < g -> numero_vertices; i++) {
		for (int j = i + 1; j < g -> numero_vertices; j++) {
			if (g -> grafo[i][j] == 1 || g -> grafo[i][j] == 12 || g -> grafo[i][j] == 13) {
				list<int> casamento;
				casamento.push_back(i);
				casamento.push_back(j);

				casamentos.push_back(casamento);
			}
		}
	}
}

bool contem(int elem, list<int> fonte)
{
	for (int i: fonte)
		if (i == elem)
			return true;

	return false;
}

void encontra_caminhos(Atributos_vertice* fonte, Atributos_vertice* destino,list<Atributos_vertice*> caminho_atual, list<list<Atributos_vertice*>> &caminhos)
{
	if (fonte == destino) {
		caminhos.push_back(caminho_atual);
		return;
	}

	for (Atributos_vertice* filho: fonte -> filhos) {
		list<Atributos_vertice*> caminho_aux(caminho_atual);
		caminho_aux.push_back(filho);
		encontra_caminhos(filho, destino, caminho_aux, caminhos);
	}
}

bool sao_disjuntos(list<Atributos_vertice*> caminho_a, list<Atributos_vertice*> caminho_b)
{
	for (Atributos_vertice* i: caminho_a)
		for (Atributos_vertice* y: caminho_b)
			if (i == y)
				return false;
	return true;
}

void verifica_anel(vector<list<Atributos_vertice*>> caminhos, list<Anel*> &destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas)
{
	/*
	//teste
	bool teste = true;
	for (Atributos_vertice* i: juncoes) {
		if (i -> numero == 1004) {
			printf("\n");
			teste = false;
			printf("Verificando anel de juncao 1004\n");
			printf("Atributos nos caminhos: \n");
			for(list<Atributos_vertice*> a: caminhos) {
				for (Atributos_vertice*i : a) {
					printf("%d, ", i -> numero);
				}
			}
			printf("\n");
		}
	}*/
	//Verifica se Alguma juncao é repetida ou esta em algum caminho
	list<Atributos_vertice*> aux;
	for (Juncao* j: juncoesUtilizadas) {
		for (Atributos_vertice* v: aux) {
			if (v == j -> juncao)
				return;
		}
		aux.push_back(j -> juncao);
	}
	for (list<Atributos_vertice*> l: caminhos)
		for (Atributos_vertice* v: l)
			for (Atributos_vertice* v1: aux)
				if (v == v1) {
					return;
				}



	//verifica se intersecção é vazia
	for (int i = 0; i < caminhos.size(); i++) {
		for (int y = i + 1; y < caminhos.size(); y++) {
			if (!sao_disjuntos(caminhos[i], caminhos[y]))
				return;
		}
	}

	Anel* novo = new Anel();
	novo -> adicionar_elemento(caminhos, casamentos, juncoesUtilizadas);

	destino.push_back(novo);

	//teste
	/*
	if (!teste) {
		printf("Anel com 1004 de juncao encontrado!\n");
		printf("%s", novo -> linha_ordem.c_str());
		printf("\n");
	}*/


	//Para escrever sempre que encontrar um anel
	/*
	FILE* arquivo;
	arquivo = fopen("entrada/aneis_ordem_3.txt", "a");
	fputs(novo -> linha_ordem.c_str(), arquivo);
	fclose(arquivo);
	*/
}

void encontra_aneis(list<Anel_aux*> aux, vector<list<Atributos_vertice*>> atual, list<Anel*> & destino, list<list<int>> casamentos, list<Juncao*> juncoesUtilizadas)
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
		return;	//Mudar p incluir a2c1
		list<Juncao*> juncoes_aux(juncoesUtilizadas);
		juncoes_aux.push_back(new Juncao(anel_a -> primeiro, anel_a -> segundo, anel_a -> primeiro));

		vector<list<Atributos_vertice*>> atual_aux(atual);
		// Verificar (Colocar 0 ou 2) em atual_aux

		encontra_aneis(aux, atual_aux, destino, casamentos, juncoes_aux);
		return;
	}

	for (int i = 0; i < anel_a -> juncoes.size(); i++) {
		list<Juncao*> juncoes_aux(juncoesUtilizadas);
		juncoes_aux.push_back(new Juncao(anel_a -> primeiro, anel_a -> segundo, anel_a -> juncoes[i]));

		//Aqui estava o erro, estava caminhos_primeiro.size()
		for (int y = 0; y < anel_a -> caminhos_primeiro[i].size(); y++) {
			if (anel_a -> caminhos_primeiro[i][y].size() == 0 && anel_a -> caminhos_segundo[i][y].size() == 0)
				break;

			vector<list<Atributos_vertice*>> atual_aux(atual);

			atual_aux.push_back(anel_a -> caminhos_primeiro[i][y]);
			atual_aux.push_back(anel_a -> caminhos_segundo[i][y]);

			encontra_aneis(aux, atual_aux, destino, casamentos, juncoes_aux);
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
	list<list<Atributos_vertice*>> caminhos_front[juncao -> juncoes.size()];
	list<list<Atributos_vertice*>> caminhos_back[juncao -> juncoes.size()];
	int indice = 0;
	for (Atributos_vertice* juncoes: juncao->juncoes) {
		list<Atributos_vertice*> caminho_atual;
		encontra_caminhos(juncoes, destino -> primeiro, caminho_atual, caminhos_front[indice]);
		encontra_caminhos(juncoes, destino -> segundo, caminho_atual, caminhos_back[indice]);
		indice++;
	}

	//Encontra os caminhos disjuntos da juncao até os membros do par
	destino -> mudar_tamanho(juncao -> juncoes.size());
	indice = 0;
	for (Atributos_vertice* juncoes: juncao -> juncoes) {
		int i = 0;
		int tam_max = (caminhos_front[indice].size() + 1) * (caminhos_back[indice].size() + 1);
		destino -> juncoes[indice] = juncoes;
		destino -> caminhos_primeiro[indice].resize(tam_max);
		destino -> caminhos_segundo[indice].resize(tam_max);
		for (list<Atributos_vertice*> caminho_a: caminhos_front[indice]) {
			for (list<Atributos_vertice*> caminho_b: caminhos_back[indice]) {
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

void casamentos_sem_juncao(vector<list<int>> casamentos, list<JuncoesDe*> juncoes, Grafo* g) {
	for (list<int> c: casamentos) {
		//Encontra as juncoes do par
		int id_front = c.front();
		int id_back = c.back();
		JuncoesDe* par_juncao = NULL;
		for (JuncoesDe* j: juncoes) {
			if (id_front == j -> primeiro -> id || id_front == j -> segundo -> id)  {
				if (id_back == j -> primeiro -> id || id_back == j -> segundo -> id) {
					par_juncao = j;
					break;
				}
			}
		}

		if (par_juncao == NULL) {
			string casamento = "";
			casamento += to_string(g -> encontrar_atributo(c.front()) -> numero);
			casamento += " e ";
			casamento += to_string(g -> encontrar_atributo(c.back()) -> numero);
			casamento += "\n";
			FILE* arquivo;
			arquivo = fopen("entrada/casamentos_sem_juncao.txt", "a");
			fputs(casamento.c_str(), arquivo);
			fclose(arquivo);
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
		JuncoesDe* par_juncao = NULL;
		for (JuncoesDe* j: juncoes) {
			if (id_front == j -> primeiro -> id || id_front == j -> segundo -> id)  {
				if (id_back == j -> primeiro -> id || id_back == j -> segundo -> id) {
					par_juncao = j;
					break;
				}
			}
		}

		if (par_juncao == NULL) {
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
		vector<list<Atributos_vertice*>> atual;
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

void encontra_aneis_a2(Grafo* g, list<JuncoesDe*> juncoes, vector<list<int>> casamentos, list<Anel*>& destino)
{
	//Constroi todos os conjuntos de casamentos, cada 1 com 2 casamentos
	list<list<list<int>>> conjuntos_c;
	encontra_duplas_casamentos(casamentos, conjuntos_c);

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
					par_anel_aux -> primeiro = g -> encontrar_atributo(id_front);
					par_anel_aux -> segundo = par_anel_aux -> primeiro;
					continue;
				}

				//Encontra as juncoes do par
				JuncoesDe* par_juncao = NULL;
				for (JuncoesDe* j: juncoes) {
					if (id_front == j -> primeiro -> id || id_front == j -> segundo -> id)  {
						if (id_back == j -> primeiro -> id || id_back == j -> segundo -> id) {
							par_juncao = j;
							break;
						}
					}
				}

				if (par_juncao == NULL) {
					//Nao existe juncao para o par
					proximo = true;
					break;
				}

				//Define caminhos disjuntos das juncoes ate o par
				define_anel_aux(par_juncao, par_anel_aux);
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

			//Para todo grupo de caminhos disjuntos fazer intersecção
			//Se intersecção for vazia, encontrou um anel
			list<Juncao*> juncoesUtilizadas;
			vector<list<Atributos_vertice*>> atual;
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
		//(x1,y1) (x2, y2) -> (x1,x2) (y1,y2) e (x1, y2) (y1, x2)
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

				//Se par é o mesmo elemento continua busca em outros pares REVISAR AxCk, x != k
				if (id_front == id_back) {
					par_anel_aux -> primeiro = g -> encontrar_atributo(id_front);
					par_anel_aux -> segundo = par_anel_aux -> primeiro;
					continue;
				}

				//Encontra as juncoes do par
				JuncoesDe* par_juncao = NULL;
				for (JuncoesDe* j: juncoes) {
					if (id_front == j -> primeiro -> id || id_front == j -> segundo -> id)  {
						if (id_back == j -> primeiro -> id || id_back == j -> segundo -> id) {
							par_juncao = j;
							break;
						}
					}
				}

				if (par_juncao == NULL) {
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
			vector<list<Atributos_vertice*>> atual;
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

void encontra_aneis(Grafo* g, list<Anel*>& destino, int numero_casamentos)
{
	if (numero_casamentos > 3 || numero_casamentos < 1)
		return;

	//3.1
	//Encontra todas as junções do grafo
	list<JuncoesDe*> juncoes;
	encontra_juncoes(g, juncoes);
	printf("Encontrou junções\n");

	//3.2
	//Encontra todos os casamentos do grafo (list<int> = 1 casamento)
	vector<list<int>> casamentos;
	encontra_casamentos(g, casamentos);
	printf("Encontrou casamentos\n");

	//3.3
	//Define os conjuntos a serem trabalhados e operam encontrando os aneis sobre eles
	if (numero_casamentos == 1)
		encontra_aneis_a1(juncoes, casamentos, destino);
	else if (numero_casamentos == 2)
		encontra_aneis_a2(g, juncoes, casamentos, destino);
	else
		encontra_aneis_a3(g, juncoes, casamentos, destino);
}

//Procura por um Nodo_dominadores em uma lista, dado seu atributo
Nodo_dominadores* encontra_nodo(Atributos_vertice* i, list<Nodo_dominadores*> l) {
	for (Nodo_dominadores* d: l)
		if (d -> atributo == i)
			return d;

	return NULL;
}

//Procura por regiao sabendo seu Nodo
Region* encontra_regiao(Nodo_dominadores* i, list<Region*> l) {
	for (Region* r: l)
		for (Nodo_dominadores* d: r -> membros)
			if (d == i)
				return r;


	return NULL;
}

//Coloca em destino os Atributos de g que nao tenham vertices de entrada
void encontra_raizes(Grafo* g, list<Atributos_vertice*>& destino) {
	for (Atributos_vertice* v: g -> atributos)
		if (v -> pais.size() == 0)
			destino.push_back(v);
}

//Encontra o Nodo_dominador que representa em seus sucessores_a_arv a arvore de dominadores
void encontra_arvore_denominadores(Grafo* g, Nodo_dominadores* raiz) {
	//Criação de atributo "Raiz" que se liga aos raizes de g
	Atributos_vertice* root = new Atributos_vertice(g -> atributos.size(), 99999, 'z');
	list<Atributos_vertice*> raizes_g;
	encontra_raizes(g, raizes_g);
	for (Atributos_vertice* v: raizes_g) {
		v -> adicionar_pais(root);
		root -> adicionar_filho(v);
	}
	g -> atributos.push_back(root);

	//Instaciação e valoração dos Nodo_dominadores e das regioes
	list<Nodo_dominadores*> raizes;
	list<Region*> regioes;
	for (Atributos_vertice* v: g -> atributos) {
		Nodo_dominadores* novo = new Nodo_dominadores(v);
		raizes.push_back(novo);

		Region* nova = new Region(novo);
		regioes.push_back(nova);
	}
	for (Region* r: regioes) {
		for (Atributos_vertice* v: r -> header -> atributo -> filhos) {
			Nodo_dominadores* prox = encontra_nodo(v, raizes);
			Region* prox_r = encontra_regiao(prox, regioes);

			r -> sucessores.push_back(prox_r);
		}
		for (Atributos_vertice* v: r -> header -> atributo -> pais) {
			Nodo_dominadores* prox = encontra_nodo(v, raizes);
			Region* prox_r = encontra_regiao(prox, regioes);

			r -> antecessores.push_back(prox_r);
		}
	}

	//Estruturas que serão utilizadas no calculo
	A_arvore* a_arv = new A_arvore(raizes);
	D_arvore* d_arv = new D_arvore(raizes);
	while (regioes.size() > 1) {
		bool terminar = true;
		Region* retirar;
		Region* consome;

		//encontra regiao com somente um antecessor
		for (Region* r: regioes) {
			if (r -> antecessores.size() == 1) {
				terminar = false;
				retirar = r;
				break;
			}
		}

		if (terminar) {
			//Ocorreu erro, deletar regioes, Nodos e retirar root do grafo
			raiz =  NULL;
			return;
		}

		//Regiao que irá consumir retirar
		consome = retirar -> antecessores.front();
		consome -> juntar(retirar);

		//Encontra o Nodo que irá linkar com o header de consome
		Nodo_dominadores* proximo = NULL;
		if (retirar -> header -> atributo -> pais.size() == 2) {	//Se tem dois pais em g, proximo = ancestral em comum mais baixo
			Nodo_dominadores* a = encontra_nodo(retirar -> header -> atributo -> pais.front(), raizes);
			Nodo_dominadores* b = encontra_nodo(retirar -> header -> atributo -> pais.back(), raizes);

			//proximo = d_arv -> lowest(a, b, a_arv);
			proximo = a_arv -> lowest(a, b, d_arv);
		} else if (retirar -> header -> atributo -> pais.size() == 1) {		//Se tem somente um pai, proximo = pai
			proximo = encontra_nodo(retirar -> header -> atributo -> pais.front(), raizes);
		}

		if (proximo != NULL) {
			a_arv -> link(retirar -> header, proximo);
			d_arv -> merge(retirar -> header, proximo);
		} else {
			//Ocorreu erro, deletar regioes, Nodos e retirar root do grafo
			raiz =  NULL;
			return;
		}

		//Deleta regiao que foi consumida
		regioes.remove(retirar);
		delete retirar;
	}

	//Retorna g ao normal
	g -> atributos.remove(root);
	for (Atributos_vertice* v: raizes_g) {
		v -> pais.remove(root);
	}

	//Vertice raiz
	raiz = a_arv -> raizes.front();
}


