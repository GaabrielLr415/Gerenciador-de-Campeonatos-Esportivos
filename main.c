#include <stdio.h>
#include "campeonato.h"

int main() {
    int opcao;

    do {
        printf("\n===== GERENCIADOR DE CAMPEONATOS =====\n");
        printf("1 - Cadastrar equipe\n");
        printf("2 - Cadastrar jogador\n");
        printf("3 - Registrar jogo\n");
        printf("4 - Exibir classificacao\n");
        printf("5 - Exibir artilheiros\n");
        printf("6 - Listar equipes e jogadores\n");
        printf("7 - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_equipe();
                break;

            case 2:
                printf("Cadastro de jogadores.\n");
                break;

            case 3:
                printf("Registro de jogo.\n");
                break;

            case 4:
                exibir_classificacao();
                break;

            case 5:
                printf("Artilheiros.\n");
                break;

            case 6:
                printf("Lista de equipes e jogadores.\n");
                break;

            case 7:
                liberar_memoria();
                printf("Encerrando o programa.\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 7);

    return 0;
}
