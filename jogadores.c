#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

Jogador *buscar_jogador(Equipe *equipe, const char *nome) {
    Jogador *atual = equipe == NULL ? NULL : equipe->jogadores;

    while (atual != NULL) {
        if (comparar_textos(atual->nome, nome) == 0) {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

void cadastrar_jogador(void) {
    char nome_equipe[80];
    char nome_jogador[80];

    printf("\n--- Cadastrar Jogador ---\n");
    printf("Nome da equipe: ");
    fgets(nome_equipe, 80, stdin);
    remover_quebra_linha(nome_equipe);

    Equipe *equipe = buscar_equipe(nome_equipe);

    if (equipe == NULL) {
        printf("Equipe nao encontrada.\n");
        return;
    }

    printf("Nome do jogador: ");
    fgets(nome_jogador, 80, stdin);
    remover_quebra_linha(nome_jogador);

    if (nome_jogador[0] == '\0') {
        printf("O nome do jogador nao pode ser vazio.\n");
        return;
    }

    if (buscar_jogador(equipe, nome_jogador) != NULL) {
        printf("Jogador ja cadastrado nessa equipe.\n");
        return;
    }

    Jogador *novo = malloc(sizeof(Jogador));

    if (novo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    copiar_texto(novo->nome, nome_jogador, sizeof(novo->nome));
    novo->gols = 0;
    novo->proximo = NULL;

    if (equipe->jogadores == NULL) {
        equipe->jogadores = novo;
    } else {
        Jogador *atual = equipe->jogadores;

        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }

        atual->proximo = novo;
    }

    printf("Jogador vinculado a equipe \"%s\" com sucesso!\n",
           equipe->nome);
}