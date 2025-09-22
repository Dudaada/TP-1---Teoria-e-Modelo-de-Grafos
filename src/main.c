#include <stdio.h>
#include <stdlib.h>
#include <string.h> // para strcspn
#include "grafo.h"

int main() {
    Grafo* g = criarGrafo(10); // Capacidade inicial para 10 cidades
    carregarArquivo(g, "inputs/exemplo.txt");

    int opcao;
    char nomeCidade[30]; // declarada uma vez
    int qnt;

    do {
        printf("\n==== MENU ====\n");
        printf("1 - Mostrar grafo (lista de adjacencia)\n");
        printf("2 - Mostrar numero de cidades\n");
        printf("3 - Mostrar numero de estradas\n");
        printf("4 - Mostrar vizinhos de uma cidade\n");
        printf("5 - Mostrar quantidade de vizinhos de uma cidade\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // consome o \n que sobra do scanf

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
            case 4:
                printf("Digite o nome da cidade: ");
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0'; // remover \n
                vizinhosCidade(g, nomeCidade);
                break;
            case 5:
                printf("Digite o nome da cidade: ");
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0'; // remove \n
                qnt = quantidadeVizinhos(g, nomeCidade);
                if (qnt >= 0) {
                    printf("A cidade %s possui %d vizinhos.\n", nomeCidade, qnt);
                }
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
