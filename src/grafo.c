#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
