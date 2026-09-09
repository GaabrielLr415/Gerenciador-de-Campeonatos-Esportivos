#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

void cadastrar_jogador(void)
{
    char nome_equipe[80];
    char nome_jogador[80];

    printf("Digite o nome da equipe: ");
    fgets(nome_equipe, 80, stdin);

    printf("Digite o nome do jogador: ");
    fgets(nome_jogador, 80, stdin);

    nome_equipe[strcspn(nome_equipe, "\n")] = '\0';
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0';

    Equipe *equipe = equipes;

    while (equipe != NULL)
    {
        if (strcmp(equipe->nome, nome_equipe) == 0)
        {
            break;
        }

        equipe = equipe->proxima;
    }

    if (equipe == NULL)
    {
        printf("Equipe nao encontrada.\n");
        return;
    }

    Jogador *novo = malloc(sizeof(Jogador));

    if (novo == NULL)
    {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    strcpy(novo->nome, nome_jogador);
    novo->gols = 0;
    novo->proximo = NULL;

    if (equipe->jogadores == NULL)
    {
        equipe->jogadores = novo;
        return;
    }

    Jogador *atual = equipe->jogadores;

    while (atual->proximo != NULL)
    {
        atual = atual->proximo;
    }

    atual->proximo = novo;
}