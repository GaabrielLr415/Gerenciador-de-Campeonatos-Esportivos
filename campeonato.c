#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

Equipe *equipes = NULL;
Jogo *historico_jogos = NULL;

// Cadastro e busca de equipes
// Desenvolvido por: Fillipe

Equipe *buscar_equipe(const char *nome) {
    Equipe *atual = equipes;

    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual;
        }

        atual = atual->proxima;
    }

    return NULL;
}


void cadastrar_equipe(void) {
    Equipe *nova_equipe;

    nova_equipe = malloc(sizeof(Equipe));

    if (nova_equipe == NULL) {
        printf("\nErro ao alocar memoria.\n");
        return;
    }

    printf("\nDigite o nome da equipe: ");
    scanf(" %79[^\n]", nova_equipe->nome);

    if (buscar_equipe(nova_equipe->nome) != NULL) {
        printf("\nEquipe ja cadastrada.\n");
        free(nova_equipe);
        return;
    }

    nova_equipe->vitorias = 0;
    nova_equipe->empates = 0;
    nova_equipe->derrotas = 0;
    nova_equipe->gols_pro = 0;
    nova_equipe->gols_contra = 0;
    nova_equipe->pontos = 0;

    nova_equipe->jogadores = NULL;

    nova_equipe->proxima = equipes;
    equipes = nova_equipe;

    printf("\nEquipe '%s' cadastrada com sucesso.\n",
           nova_equipe->nome);
}

// Fim - Cadastro e busca de equipes

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
