#ifndef GRAFO_H
#define GRAFO_H

typedef struct Aresta {
    int destino;            // Índice do vértice destino
    int peso;               // Distância entre as cidades
    struct Aresta* prox;    // Próxima aresta
} Aresta;

typedef struct Vertice {
    char nome[30];          // Nome da cidade
    Aresta* lista;          // Lista de vizinhos
} Vertice;

typedef struct Grafo {
    int numVertices;        // Número de cidades
    int numArestas;         // Número de estradas
    int capacidade;         // Capacidade atual do vetor de vertices
    Vertice* vertices;      // Vetor de vértices
} Grafo;


// Cria um grafo com capacidade para numVertices
Grafo* criarGrafo(int numVertices);

// Procura índice de uma cidade pelo nome
int buscarIndiceCidade(Grafo* g, char* nome);

// Adiciona cidade se ela não existir e retorna o índice
int adicionarCidade(Grafo* g, char* nome);

// Adiciona uma estrada (grafo não direcionado)
void adicionarAresta(Grafo* g, char* origem, char* destino, int peso);

// Imprime a lista de adjacência
void imprimirGrafo(Grafo* g);

// Carrega grafo a partir de um arquivo texto
void carregarArquivo(Grafo* g, const char* nomeArquivo);

// Libera memória do grafo
void liberarGrafo(Grafo* g);

// Retorna (imprime) os vizinhos de uma cidade
void vizinhosCidade(Grafo* g, char* nomeCidade);

// Retorna a quantidade de vizinhos de uma cidade
int quantidadeVizinhos(Grafo* g, char* nomeCidade);

void menorCaminho(Grafo* g, char* origem, char* destino);

int ehConexo(Grafo* g);

void cidadesCriticas(Grafo* g);

void passeioTuristico(Grafo* g);

#endif
