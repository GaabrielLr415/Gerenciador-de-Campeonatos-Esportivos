#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

Equipe *equipes = NULL;
Jogo *historico_jogos = NULL;

void liberar_memoria(void) {
    Jogo *jogo_atual = historico_jogos;
    Equipe *equipe_atual = equipes;

    printf("\nLiberando lista de jogos...\n");
    while (jogo_atual != NULL) {
        Jogo *proximo_jogo = jogo_atual->proximo;

        printf("Liberando no do jogo: %s %d x %d %s\n",
               jogo_atual->time_casa,
               jogo_atual->gols_casa,
               jogo_atual->gols_visitante,
               jogo_atual->time_visitante);

        free(jogo_atual);
        jogo_atual = proximo_jogo;
    }
    historico_jogos = NULL;

    printf("\nLiberando lista de equipes e seus jogadores...\n");
    while (equipe_atual != NULL) {
        Equipe *proxima_equipe = equipe_atual->proxima;
        Jogador *jogador_atual = equipe_atual->jogadores;

        printf("Liberando jogadores de: %s\n", equipe_atual->nome);
        while (jogador_atual != NULL) {
            Jogador *proximo_jogador = jogador_atual->proximo;

            printf("Liberando no: %s\n", jogador_atual->nome);
            free(jogador_atual);
            jogador_atual = proximo_jogador;
        }

        printf("Liberando no da equipe: %s\n", equipe_atual->nome);
        free(equipe_atual);
        equipe_atual = proxima_equipe;
    }
    equipes = NULL;

    printf("\nMemoria liberada com sucesso.\n");
}
