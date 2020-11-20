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
				if (adicionar)
					lista_cores[i].push_back(nova_lista_pai);
				else
					delete nova_lista_pai;
			}
			delete pai_cor;
			fila.push(pai);
		}

		v -> valor_bool = true;
	}

	int tamanho;
	for (int i = 0; i < g -> numero_vertices; i++)
	{
		tamanho = 0;
		for (Lista_lista* lista: lista_cores[i])
		{
			if (lista -> tamanho > tamanho) tamanho = lista -> tamanho;
			delete lista;
		}
		g -> encontrar_atributo(i) -> cores_ate_folha = tamanho;
	}
}

void ordem_topologica(Grafo* g, Atributos_vertice* fonte, queue<Atributos_vertice*>& destino)
{
	//Utilizado busca em largura
	//Atributos
	queue<Atributos_vertice*> aux;
	bool visitado[g -> numero_vertices];
	for (int i = 0; i < g -> numero_vertices; i++)
		visitado[i] = false;

	aux.push(fonte);

	Atributos_vertice* atual;
	while(!aux.empty())
	{
		atual = aux.front();
		aux.pop();
		destino.push(atual);

		for(Atributos_vertice* filho: atual -> filhos)
		{
			if (!visitado[filho -> id]) {
				visitado[filho->id] = true;
				aux.push(filho);
			}
		}
	}
}

void encontra_juncoes(Grafo* g, list<Juncao*>& destino) {
	queue<Atributos_vertice*> vs;

	for(Atributos_vertice* s: g -> atributos)
	{
		for(Atributos_vertice* a: g -> atributos)
		{
			a -> particao = -1;
			a -> valor_bool = false;
		}
		ordem_topologica(g, s, vs);
		s -> particao = s -> id;
		//assert(vs.front() -> id == s -> id);
		vs.pop();

		Atributos_vertice* v;
		while(!vs.empty())
		{
			v = vs.front();
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








