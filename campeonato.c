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

void registrar_jogo(void) {
    char nome_casa[80];
    char nome_visitante[80];
    int gols_casa;
    int gols_visitante;
    Equipe *equipe_casa;
    Equipe *equipe_visitante;
    Jogo *novo_jogo;

    if (equipes == NULL) {
        printf("\nCadastre pelo menos duas equipes antes de registrar um jogo.\n");
        return;
    }

    printf("\nDigite o nome da equipe da casa: ");
    scanf(" %79[^\n]", nome_casa);
    printf("Digite o nome da equipe visitante: ");
    scanf(" %79[^\n]", nome_visitante);

    equipe_casa = buscar_equipe(nome_casa);
    equipe_visitante = buscar_equipe(nome_visitante);

    if (equipe_casa == NULL || equipe_visitante == NULL) {
        printf("\nUma ou ambas as equipes nao foram encontradas.\n");
        return;
    }

    if (equipe_casa == equipe_visitante) {
        printf("\nAs equipes do jogo devem ser diferentes.\n");
        return;
    }

    printf("Digite os gols de %s: ", equipe_casa->nome);
    if (scanf("%d", &gols_casa) != 1 || gols_casa < 0) {
        printf("\nQuantidade de gols invalida.\n");
        return;
    }

    printf("Digite os gols de %s: ", equipe_visitante->nome);
    if (scanf("%d", &gols_visitante) != 1 || gols_visitante < 0) {
        printf("\nQuantidade de gols invalida.\n");
        return;
    }

    novo_jogo = malloc(sizeof(*novo_jogo));
    if (novo_jogo == NULL) {
        printf("\nErro ao alocar memoria para o jogo.\n");
        return;
    }

    strcpy(novo_jogo->time_casa, equipe_casa->nome);
    strcpy(novo_jogo->time_visitante, equipe_visitante->nome);
    novo_jogo->gols_casa = gols_casa;
    novo_jogo->gols_visitante = gols_visitante;
    novo_jogo->proximo = historico_jogos;
    historico_jogos = novo_jogo;

    equipe_casa->gols_pro += gols_casa;
    equipe_casa->gols_contra += gols_visitante;
    equipe_visitante->gols_pro += gols_visitante;
    equipe_visitante->gols_contra += gols_casa;

    if (gols_casa > gols_visitante) {
        equipe_casa->vitorias++;
        equipe_casa->pontos += 3;
        equipe_visitante->derrotas++;
    } else if (gols_casa < gols_visitante) {
        equipe_visitante->vitorias++;
        equipe_visitante->pontos += 3;
        equipe_casa->derrotas++;
    } else {
        equipe_casa->empates++;
        equipe_visitante->empates++;
        equipe_casa->pontos++;
        equipe_visitante->pontos++;
    }

    printf("\nJogo registrado: %s %d x %d %s.\n",
           equipe_casa->nome,
           gols_casa,
           gols_visitante,
           equipe_visitante->nome);
}

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
