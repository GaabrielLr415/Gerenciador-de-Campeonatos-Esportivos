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

static int comparar_artilheiros(const void *a, const void *b) {
    const Artilheiro *artilheiro_a = a;
    const Artilheiro *artilheiro_b = b;

    if (artilheiro_a->jogador->gols != artilheiro_b->jogador->gols) {
        return artilheiro_b->jogador->gols - artilheiro_a->jogador->gols;
    }

    return 0;
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

    qsort(artilheiros, (size_t)total, sizeof(*artilheiros), comparar_artilheiros);

    printf("\n--- Artilheiros ---\n");
    for (indice = 0; indice < total; indice++) {
        printf("%d. %s - %s: %d gols\n",
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

        printf("\nEquipe: %s | Pontos: %d\n", equipe->nome, equipe->pontos);
        if (jogador == NULL) {
            printf("Nenhum jogador cadastrado.\n");
        } else {
            printf("Jogadores:\n");
            while (jogador != NULL) {
                printf("- %s (%d gols)\n", jogador->nome, jogador->gols);
                jogador = jogador->proximo;
            }
        }

        equipe = equipe->proxima;
    }
}
