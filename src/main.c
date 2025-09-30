#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "grafo.h"

int main() {
    Grafo* g = criarGrafo(10); 
    carregarArquivo(g, "inputs/exemplo.txt");

    int opcao;
    char nomeCidade[30], cidadeOrigem[30], cidadeDestino[30];
    int qnt;

    do {
        printf("\n==== MENU ====\n");
        printf("1 - Mostrar grafo (lista de adjacencia)\n");
        printf("2 - Mostrar numero de cidades\n");
        printf("3 - Mostrar numero de estradas\n");
        printf("4 - Mostrar vizinhos de uma cidade\n");
        printf("5 - Mostrar quantidade de vizinhos de uma cidade\n");
        printf("6 - Calcular menor caminho entre duas cidades\n");
        printf("7 - Verificar se a rede é conexa\n");
        printf("8 - Identificar cidades criticas\n");
        printf("9 - Verificar se existe passeio turistico circular (>=4 cidades)\n");
        printf("10 - Exemplo de passeio turistico circular (se existir)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

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
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                vizinhosCidade(g, nomeCidade);
                break;
            case 5:
                printf("Digite o nome da cidade: ");
                fgets(nomeCidade, sizeof(nomeCidade), stdin);
                nomeCidade[strcspn(nomeCidade, "\n")] = '\0';
                qnt = quantidadeVizinhos(g, nomeCidade);
                if (qnt >= 0) {
                    printf("A cidade %s possui %d vizinhos.\n", nomeCidade, qnt);
                }
                break;
            case 6:
                printf("Digite a cidade de origem: ");
                fgets(cidadeOrigem, sizeof(cidadeOrigem), stdin);
                cidadeOrigem[strcspn(cidadeOrigem, "\n")] = '\0';
                printf("Digite a cidade de destino: ");
                fgets(cidadeDestino, sizeof(cidadeDestino), stdin);
                cidadeDestino[strcspn(cidadeDestino, "\n")] = '\0';
                menorCaminho(g, cidadeOrigem, cidadeDestino);
                break;
            case 7:
                if (redeConexa(g))
                    printf("A rede eh conexa.\n");
                else
                    printf("A rede NAO eh conexa.\n");
                break;
            case 8:
                cidadesCriticas(g);
                break;
            case 9:
                if (existePasseioTuristico(g))
                    printf("Existe um passeio turistico circular com pelo menos 4 cidades.\n");
                else
                    printf("Nao existe passeio turistico circular com 4 cidades.\n");
                break;
            case 10:
                exemploPasseioTuristico(g);
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
