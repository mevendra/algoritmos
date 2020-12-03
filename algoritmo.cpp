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

void encontra_conjuntos_casamentos(list<list<int>> casamentos, int k, list<list<list<int>>> &destino)
{
	//Encontra o numero total de casamentos ordenados
	int soma = 1;
	for (int i = casamentos.size(); i > (casamentos.size() - k); i--)
		soma *= i;

	//Atributos auxiliares
	vector<list<list<int>>> destino_;
	destino_.resize(soma);
	list<list<int>> destino_encontrar_casamentos;

	list<int> indices_casamentos[casamentos.size()];
	list<int> fonte_encontrar_casamentos;
	int indice = 0;
	for (list<int> y: casamentos) {
		fonte_encontrar_casamentos.push_back(indice);
		indices_casamentos[indice++] = y;
	}

	//Realiza busca
	list<int> atual_encontrar_casamentos;
	encontrar_casamentos_ordenados(k, atual_encontrar_casamentos, fonte_encontrar_casamentos, destino_encontrar_casamentos);

	//Realiza conversão para destino
	indice = 0;
	for (list<int> i : destino_encontrar_casamentos) {
		for (int y: i)
			destino_[indice].push_back(indices_casamentos[y]);
		indice++;
	}

	for (int i = 0; i < soma; i++)
		destino.push_back(destino_[i]);
}

bool contem(int elem, list<int> fonte)
{
	for (int i: fonte)
		if (i == elem)
			return true;

	return false;
}

void encontrar_casamentos_ordenados(int k, list<int>& atual, list<int>& fonte, list<list<int>>& destino)
{
	if (k == 0) {
		destino.push_back(atual);
		return;
	}

	for (int i: fonte) {
		if (!contem(i , atual)) {
			list<int> nova_lista(atual);
			nova_lista.push_back(i);
			encontrar_casamentos_ordenados(k-1, nova_lista, fonte, destino);
		}
	}
}

void encontrar_combinacoes(list<int> fonte, list<int>& atual, list<list<int>>& destino)
{
	//Se atual e fonte tem mesmo tamanho atual está completa
	if (atual.size() >= fonte.size()) {
		destino.push_back(atual);
		return;
	}

	//Senao p cada casamento que ainda nao está em atual encontra combinacao com ele na proxima posição
	for (int casamento: fonte) {
		if(!contem(casamento, atual)) {
			list<int> nova(atual);
			nova.push_back(casamento);
			encontrar_combinacoes(fonte, nova, destino);
		}
	}
}

void encontra_pares(queue<list<int>> fonte, list<list<int>> atual, int v_atual, int v_primeiro, list<list<list<int>>> &destino)
{
	//Combino atual com proximos disponiveis em fonte, se fonte for vazia com primeiro
	list<int> par;
	list<int> prox_par;

	par.push_back(v_atual);
	if (fonte.size() == 0) {
		par.push_back(v_primeiro);

		atual.push_back(par);
		destino.push_back(atual);
	} else {
		prox_par = fonte.front();	//prox par é um casamento e tem 2 pares
		fonte.pop();

		int p1 = prox_par.front();
		int p2 = prox_par.back();

		if (v_atual != p1 && v_atual != p2) {
			list<int> par_aux(par);
			list<list<int>> atual_aux(atual);

			par.push_back(p1);
			atual.push_back(par);
			encontra_pares(fonte, atual, p2, v_primeiro, destino);

			par_aux.push_back(p2);
			atual_aux.push_back(par_aux);
			encontra_pares(fonte, atual_aux, p1, v_primeiro, destino);
		} else if (v_atual == p1) {
			par.push_back(p1);
			atual.push_back(par);
			encontra_pares(fonte, atual, p2, v_primeiro, destino);
		} else {
			par.push_back(p2);
			atual.push_back(par);
			encontra_pares(fonte, atual, p1, v_primeiro, destino);
		}
	}
}

void encontra_combinacoes(list<list<int>> fonte, list<list<list<int>>>& destino)
{
	//Definição dos atributos
	//Terá fonte.size() elementos
	list<int> casamentos[fonte.size()];	//Armazena os casamentos que cada inteiro representa
	list<list<list<int>>> destino_aux;	//Armazena as ordens das combinacoes de casamentos
	list<int> fonte_indices;
	list<list<int>> destino_indices;

	//Adiciona os casamentos ao seus indices
	int indice = 0;
	for (list<int> i: fonte) {
		fonte_indices.push_back(indice);
		casamentos[indice++] = i;
	}

	//Encontra todas as combinações entre os casamentos
	for (indice = 0; indice < fonte.size(); indice++) {
		list<int> atual;
		encontrar_combinacoes(fonte_indices, atual, destino_indices);
	}

	//Substitui os indices pelas listas com os casamentos
	for (list<int> i: destino_indices) {
		list<list<int>> elemento;
		for (int y: i) {
			elemento.push_back(casamentos[y]);
		}
		//Verifica se em uma mesma combinação nao existem casamentos separados(x1,y1) (x2,y2) (x1,y3) (x4,y4)
		//todo

		destino_aux.push_back(elemento);
	}

	//Define os pares de casamentos
	for (list<list<int>> i: destino_aux) {
		list<int> aux;
		int primeiro;
		int segundo;
		queue<list<int>> fonte_encontra_pares;
		for (list<int> y : i)
			fonte_encontra_pares.push(y);

		aux = fonte_encontra_pares.front();
		fonte_encontra_pares.pop();

		primeiro = aux.front();
		segundo = aux.back();

		list<list<int>> atual;
		encontra_pares(fonte_encontra_pares, atual, primeiro, segundo, destino);
		encontra_pares(fonte_encontra_pares, atual, segundo, primeiro, destino);
	}
}

void encontra_caminhos(Atributos_vertice* fonte, Atributos_vertice* destino,list<Atributos_vertice*> caminho_atual, list<list<Atributos_vertice*>> &caminhos)
{
	if (fonte -> id == destino -> id) {
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
			if (i -> id == y -> id)
				return false;
	return true;
}

void verifica_anel(vector<list<Atributos_vertice*>> caminhos, list<Anel*> &destino, list<Atributos_vertice*> juncoes) {
	//verifica se intersecção é vazia
	for (int i = 0; i < caminhos.size(); i++) {
		for (int y = i + 1; y < caminhos.size(); y++) {
			if (!sao_disjuntos(caminhos[i], caminhos[y]))
				return;
		}
	}

	Anel* novo = new Anel();
	//É um anel, adiciona elementos ao anel
	for (int i = 0; i < caminhos.size(); i++)
		novo -> adicionar_elemento(caminhos[i]);


	for (Atributos_vertice* i: juncoes)
		novo -> anel.push_back(i);

	destino.push_back(novo);
}

void encontra_aneis(list<Anel_aux*> aux, vector<list<Atributos_vertice*>> atual, list<Anel*> & destino, list<Atributos_vertice*> juncoes) {
	if (aux.size() == 0) {
		verifica_anel(atual, destino, juncoes);
		return;
	}

	Anel_aux* anel_a = aux.front();
	aux.pop_front();

	for (int i = 0; i < anel_a -> juncoes.size(); i++) {
		list<Atributos_vertice*> juncoes_aux(juncoes);
		juncoes_aux.push_back(anel_a -> juncoes[i]);

		for (int y = 0; y < anel_a -> caminhos_primeiro.size(); y++) {
			if (anel_a -> caminhos_primeiro[i][y].size() == 0 || anel_a -> caminhos_segundo[i][y].size() == 0)
				break;
			vector<list<Atributos_vertice*>> atual_aux(atual);
			atual_aux.push_back(anel_a -> caminhos_primeiro[i][y]);
			atual_aux.push_back(anel_a -> caminhos_segundo[i][y]);

			encontra_aneis(aux, atual_aux, destino, juncoes_aux);
		}
	}
}

void encontra_aneis(Grafo* g, list<Anel*>& destino, int numero_casamentos) {
	//3.1
	//Encontra todas as junções do grafo
	list<JuncoesDe*> juncoes;
	encontra_juncoes(g, juncoes);
	printf("Encontrou junções\n");

	//3.2
	//Encontra todos os casamentos do grafo (list<int> = 1 casamento)
	list<list<int>> casamentos;
	encontra_casamentos(g, casamentos);
	printf("Encontrou casamentos\n");

	//Constroi todos os conjuntos de casamentos, cada 1 com numero_casamentos tamanho
	list<list<list<int>>> conjuntos_c;
	encontra_conjuntos_casamentos(casamentos, numero_casamentos, conjuntos_c);
	printf("Encontrou conjuntos dos casamentos\n");

	//3.3
	//Define conjunto c com numero_casamentos casamentos e trabalha nele
	for (list<list<int>> conjunto_c: conjuntos_c) {
		printf("Operando sobre conjunto: ");
		for (list<int> i: conjunto_c)
			printf("(%d,%d) ", i.front(), i.back());
		printf("\n");
		//Encontra todas as possibilidades de agrupamentos de casamentos dos elementos do conjunto c
		//Total de possibilidades = 2 ^ numero_casamentos
		list<list<list<int>>> combinacoes;
		encontra_combinacoes(conjunto_c, combinacoes);

		//Para cada possibilidade de agrupamento(combinacao)
		for (list<list<int>> c: combinacoes) {

			//Estrutura que armazena caminhos e juncoes para cada par em c
			list<Anel_aux*> c_aneis_aux;

			//Para cada par da combinação
			for (list<int> par: c) {
				int id_front = par.front();
				int id_back = par.back();

				//Se par é o mesmo elemento continua busca em outros pares REVISAR
				if (id_front == id_back)
					continue;

				//Anel auxiliar do par
				Anel_aux* par_anel_aux = new Anel_aux();
				c_aneis_aux.push_back(par_anel_aux);

				//Encontra as juncoes do par (e as define em par_anel_aux)
				JuncoesDe* par_juncao;
				for (JuncoesDe* j: juncoes) {
					if (id_front == j -> primeiro -> id || id_front == j -> segundo -> id)  {
						if (id_back == j -> primeiro -> id || id_back == j -> segundo -> id) {
							par_juncao = j;
							break;
						}
					}
				}
				par_anel_aux -> primeiro = par_juncao -> primeiro;
				par_anel_aux -> segundo = par_juncao -> segundo;

				//Encontra os caminhos da juncao até os mebros do par
				list<list<Atributos_vertice*>> caminhos_front[par_juncao->juncoes.size()];
				list<list<Atributos_vertice*>> caminhos_back[par_juncao->juncoes.size()];
				int indice = 0;
				for (Atributos_vertice* juncao: par_juncao->juncoes) {
					list<Atributos_vertice*> caminho_atual;
					encontra_caminhos(juncao, par_anel_aux -> primeiro, caminho_atual, caminhos_front[indice]);
					encontra_caminhos(juncao, par_anel_aux -> segundo, caminho_atual, caminhos_back[indice]);
					indice++;
				}


				//Encontra os caminhos disjuntos da juncao até os membros do par
				par_anel_aux -> mudar_tamanho(par_juncao->juncoes.size());
				indice = 0;
				for (Atributos_vertice* juncao: par_juncao->juncoes) {
					int i = 0;
					int tam_max = (caminhos_front[indice].size() + 1) * (caminhos_back[indice].size() + 1);
					par_anel_aux -> juncoes[indice] = juncao;
					par_anel_aux -> caminhos_primeiro[indice].resize(tam_max);
					par_anel_aux -> caminhos_segundo[indice].resize(tam_max);
					for (list<Atributos_vertice*> caminho_a: caminhos_front[indice]) {
						for (list<Atributos_vertice*> caminho_b: caminhos_back[indice]) {
							if (sao_disjuntos(caminho_a, caminho_b)) {
								par_anel_aux -> caminhos_primeiro[indice][i] = caminho_a;
								par_anel_aux -> caminhos_segundo[indice][i] = caminho_b;
								i++;
							}
						}
					}
					indice++;
				}
			}

			//Para todo grupo de caminhos disjuntos fazer intersecção
			//Se intersecção for vazia, encontrou um anel
			list<Atributos_vertice*> juncao;
			vector<list<Atributos_vertice*>> atual;
			encontra_aneis(c_aneis_aux, atual, destino, juncao);

			//Para cada anel aux criado excluilo ???
		}
	}
}





