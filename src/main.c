#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"

//exemplo de menu kkkkkk

int main() {
    Grafo* g = criarGrafo(10); // Capacidade inicial para 10 cidades
    carregarArquivo(g, "inputs/exemplo.txt");

    int opcao;
    do {
        printf("\n==== MENU ====\n");
        printf("1 - Mostrar grafo (lista de adjacencia)\n");
        printf("2 - Mostrar numero de cidades\n");
        printf("3 - Mostrar numero de estradas\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                imprimirGrafo(g);
                break;
            case 2:
                printf("Numero de cidades: %d\n", g->numVertices);
                break;
            case 3:
                printf("Numero de estradas: %d\n", g->numArestas);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while(opcao != 0);

    liberarGrafo(g);
    return 0;
}
