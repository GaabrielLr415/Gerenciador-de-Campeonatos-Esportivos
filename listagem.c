#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

typedef struct {
    Jogador *jogador;
    const char *nome_equipe;
} Artilheiro;

static int contar_jogadores(void) {
    int total = 0;
    Equipe *equipe = equipes;

    while (equipe != NULL) {
        Jogador *jogador = equipe->jogadores;
        while (jogador != NULL) {
            total++;
            jogador = jogador->proximo;
        }
        equipe = equipe->proxima;
    }

    return total;
}

void exibir_artilheiros(void) {
    int total = contar_jogadores();
    int indice = 0;
    Artilheiro *artilheiros;
    Equipe *equipe;

    if (total == 0) {
        printf("\nNenhum jogador cadastrado.\n");
        return;
    }

    artilheiros = malloc((size_t)total * sizeof(*artilheiros));
    if (artilheiros == NULL) {
        printf("\nErro ao gerar lista de artilheiros.\n");
        return;
    }

    equipe = equipes;
    while (equipe != NULL) {
        Jogador *jogador = equipe->jogadores;
        while (jogador != NULL) {
            artilheiros[indice].jogador = jogador;
            artilheiros[indice].nome_equipe = equipe->nome;
            indice++;
            jogador = jogador->proximo;
        }
        equipe = equipe->proxima;
    }

    for (int i = 0; i < total - 1; i++) {
        int melhor = i;

        for (int j = i + 1; j < total; j++) {
            if (artilheiros[j].jogador->gols >
                artilheiros[melhor].jogador->gols) {
                melhor = j;
            }
        }

        if (melhor != i) {
            Artilheiro temporario = artilheiros[i];
            artilheiros[i] = artilheiros[melhor];
            artilheiros[melhor] = temporario;
        }
    }

    printf("\n--- Lista de Artilheiros ---\n");
    printf("Pos | Jogador | Equipe | Gols\n");
    for (indice = 0; indice < total; indice++) {
        printf("%d | %s | %s | %d\n",
               indice + 1,
               artilheiros[indice].jogador->nome,
               artilheiros[indice].nome_equipe,
               artilheiros[indice].jogador->gols);
    }

    free(artilheiros);
}

void listar_equipes_jogadores(void) {
    Equipe *equipe = equipes;

    if (equipe == NULL) {
        printf("\nNenhuma equipe cadastrada.\n");
        return;
    }

    printf("\n--- Equipes e jogadores ---\n");
    while (equipe != NULL) {
        Jogador *jogador = equipe->jogadores;

        printf("Equipe: %s | Pontos: %d\n", equipe->nome, equipe->pontos);
        if (jogador == NULL) {
            printf("Nenhum jogador cadastrado.\n");
        } else {
            printf("Jogadores:\n");
            while (jogador != NULL) {
                printf("  Jogador: %s | Gols: %d\n", jogador->nome, jogador->gols);
                jogador = jogador->proximo;
            }
        }

        equipe = equipe->proxima;
    }
}
