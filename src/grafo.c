#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "grafo.h"

Grafo* criarGrafo(int numVertices) {
    Grafo* g = (Grafo*) malloc(sizeof(Grafo));
    g->numVertices = 0; 
    g->numArestas = 0;
    g->vertices = (Vertice*) malloc(numVertices * sizeof(Vertice));

    for (int i = 0; i < numVertices; i++) {
        g->vertices[i].nome[0] = '\0';
        g->vertices[i].lista = NULL;
    }

    return g;
}
int buscarIndiceCidade(Grafo* g, char* nome) {
    for (int i = 0; i < g->numVertices; i++) {
        if (strcmp(g->vertices[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1; // Não encontrada
}

int adicionarCidade(Grafo* g, char* nome) {
    int indice = buscarIndiceCidade(g, nome);
    if (indice == -1) {
        strcpy(g->vertices[g->numVertices].nome, nome);
        g->vertices[g->numVertices].lista = NULL;
        indice = g->numVertices;
        g->numVertices++;
    }
    return indice;
}

void adicionarAresta(Grafo* g, char* origem, char* destino, int peso) {
    int idxOrigem = adicionarCidade(g, origem);
    int idxDestino = adicionarCidade(g, destino);

    // Criar aresta origem -> destino
    Aresta* nova1 = (Aresta*) malloc(sizeof(Aresta));
    nova1->destino = idxDestino;
    nova1->peso = peso;
    nova1->prox = g->vertices[idxOrigem].lista;
    g->vertices[idxOrigem].lista = nova1;

    // Criar aresta destino -> origem
    Aresta* nova2 = (Aresta*) malloc(sizeof(Aresta));
    nova2->destino = idxOrigem;
    nova2->peso = peso;
    nova2->prox = g->vertices[idxDestino].lista;
    g->vertices[idxDestino].lista = nova2;

    g->numArestas++;
}

void imprimirGrafo(Grafo* g) {
    printf("\n=== Lista de Adjacencia ===\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%s -> ", g->vertices[i].nome);
        Aresta* atual = g->vertices[i].lista;
        while (atual != NULL) {
            printf("(%s, %d) ", g->vertices[atual->destino].nome, atual->peso);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void carregarArquivo(Grafo* g, const char* nomeArquivo) {
    FILE* arq = fopen(nomeArquivo, "r");
    if (!arq) {
        printf("Erro ao abrir arquivo: %s\n", nomeArquivo);
        exit(1);
    }

    char cidade1[30], cidade2[30];
    int distancia;

    while (fscanf(arq, "%[^,],%[^,],%d\n", cidade1, cidade2, &distancia) == 3) {
        adicionarAresta(g, cidade1, cidade2, distancia);
    }

    fclose(arq);
}

void liberarGrafo(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        Aresta* atual = g->vertices[i].lista;
        while (atual != NULL) {
            Aresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->vertices);
    free(g);
}

// Retorna (imprime) os vizinhos de uma cidade
void vizinhosCidade(Grafo* g, char* nomeCidade) {
    int idx = buscarIndiceCidade(g, nomeCidade);
    if (idx == -1) {
        printf("Cidade '%s' nao encontrada no grafo.\n", nomeCidade);
        return;
    }

    printf("Vizinhos de %s: ", g->vertices[idx].nome);
    Aresta* atual = g->vertices[idx].lista;
    if (!atual) {
        printf("Nenhum vizinho.\n");
        return;
    }

    while (atual != NULL) {
        printf("(%s, %d) ", g->vertices[atual->destino].nome, atual->peso);
        atual = atual->prox;
    }
    printf("\n");
}

// Retorna a quantidade de vizinhos de uma cidade
int quantidadeVizinhos(Grafo* g, char* nomeCidade) {
    int idx = buscarIndiceCidade(g, nomeCidade);
    if (idx == -1) {
        printf("Cidade '%s' nao encontrada no grafo.\n", nomeCidade);
        return -1; // erro
    }

    int cont = 0;
    Aresta* atual = g->vertices[idx].lista;
    while (atual != NULL) {
        cont++;
        atual = atual->prox;
    }
    return cont;
}

// ---------- Menor caminho (Dijkstra) ----------
void menorCaminho(Grafo* g, char* origem, char* destino) {
    int n = g->numVertices;
    int dist[n], visitado[n], anterior[n];
    int i;

    int start = buscarIndiceCidade(g, origem);
    int end   = buscarIndiceCidade(g, destino);

    if (start == -1 || end == -1) {
        printf("Cidade(s) nao encontrada(s).\n");
        return;
    }

    for (i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        visitado[i] = 0;
        anterior[i] = -1;
    }
    dist[start] = 0;

    for (i = 0; i < n-1; i++) {
        int u = -1, min = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (!visitado[j] && dist[j] < min) {
                min = dist[j];
                u = j;
            }
        }
        if (u == -1) break;
        visitado[u] = 1;

        Aresta* a = g->vertices[u].lista;
        while (a) {
            if (!visitado[a->destino] && dist[u] + a->peso < dist[a->destino]) {
                dist[a->destino] = dist[u] + a->peso;
                anterior[a->destino] = u;
            }
            a = a->prox;
        }
    }

    if (dist[end] == INT_MAX) {
        printf("Nao existe caminho entre %s e %s.\n", origem, destino);
        return;
    }

    printf("Menor distancia entre %s e %s = %d\n", origem, destino, dist[end]);

    // reconstruir caminho
    int caminho[n], tam = 0, v = end;
    while (v != -1) {
        caminho[tam++] = v;
        v = anterior[v];
    }
    printf("Caminho: ");
    for (i = tam-1; i >= 0; i--) {
        printf("%s ", g->vertices[caminho[i]].nome);
        if (i > 0) printf("-> ");
    }
    printf("\n");
}

// ---------- Verifica se grafo é conexo ----------
void dfsConexo(Grafo* g, int v, int* visitado) {
    visitado[v] = 1;
    Aresta* a = g->vertices[v].lista;
    while (a) {
        if (!visitado[a->destino]) dfsConexo(g, a->destino, visitado);
        a = a->prox;
    }
}

int ehConexo(Grafo* g) {
    int n = g->numVertices;
    int visitado[n];
    for (int i = 0; i < n; i++) visitado[i] = 0;

    dfsConexo(g, 0, visitado);

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) {
            printf("A rede NAO eh conexa.\n");
            return 0;
        }
    }
    printf("A rede eh conexa.\n");
    return 1;
}

// ---------- Cidades críticas (articulação) ----------
int tempo;

void dfsArt(Grafo* g, int u, int pai, int* visitado, int* disc, int* low, int* articulacao) {
    int filhos = 0;
    visitado[u] = 1;
    disc[u] = low[u] = ++tempo;

    Aresta* a = g->vertices[u].lista;
    while (a) {
        int v = a->destino;
        if (!visitado[v]) {
            filhos++;
            dfsArt(g, v, u, visitado, disc, low, articulacao);
            low[u] = (low[u] < low[v]) ? low[u] : low[v];

            if ((pai != -1 && low[v] >= disc[u]) || (pai == -1 && filhos > 1)) {
                articulacao[u] = 1;
            }
        } else if (v != pai) {
            if (low[u] > disc[v]) low[u] = disc[v];
        }
        a = a->prox;
    }
}

void cidadesCriticas(Grafo* g) {
    int n = g->numVertices;
    int visitado[n], disc[n], low[n], articulacao[n];

    for (int i = 0; i < n; i++) {
        visitado[i] = disc[i] = low[i] = 0;
        articulacao[i] = 0;
    }
    tempo = 0;

    for (int i = 0; i < n; i++) {
        if (!visitado[i]) dfsArt(g, i, -1, visitado, disc, low, articulacao);
    }

    printf("Cidades criticas: ");
    int achou = 0;
    for (int i = 0; i < n; i++) {
        if (articulacao[i]) {
            printf("%s ", g->vertices[i].nome);
            achou = 1;
        }
    }
    if (!achou) printf("Nenhuma");
    printf("\n");
}

// ---------- Passeio turístico circular ----------
int dfsCiclo(Grafo* g, int atual, int inicio, int profundidade, int* visitado, int* caminho) {
    visitado[atual] = 1;
    caminho[profundidade] = atual;

    Aresta* a = g->vertices[atual].lista;
    while (a) {
        if (a->destino == inicio && profundidade >= 3) {
            caminho[profundidade+1] = inicio;
            return profundidade+1;
        }
        if (!visitado[a->destino]) {
            int tam = dfsCiclo(g, a->destino, inicio, profundidade+1, visitado, caminho);
            if (tam > 0) return tam;
        }
        a = a->prox;
    }

    visitado[atual] = 0;
    return 0;
}

void passeioTuristico(Grafo* g) {
    int n = g->numVertices;
    int visitado[n], caminho[n+1];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) visitado[j] = 0;
        int tam = dfsCiclo(g, i, i, 0, visitado, caminho);
        if (tam > 0) {
            printf("Existe passeio turistico: ");
            for (int k = 0; k <= tam; k++) {
                printf("%s ", g->vertices[caminho[k]].nome);
                if (k < tam) printf("-> ");
            }
            printf("\n");
            return;
        }
    }
    printf("Nao existe passeio turistico com 4 ou mais cidades.\n");
}
