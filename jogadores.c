#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

Jogador *buscar_jogador(Equipe *equipe, const char *nome)
{
    Jogador *atual = equipe == NULL ? NULL : equipe->jogadores;

    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            return atual;
        }

        atual = atual->proximo;
    }

    return NULL;
}

void cadastrar_jogador(void)
{
    char nome_equipe[80];
    char nome_jogador[80];

    printf("Digite o nome da equipe: ");
    fgets(nome_equipe, 80, stdin);
    nome_equipe[strcspn(nome_equipe, "\n")] = '\0';

    Equipe *equipe = buscar_equipe(nome_equipe);

    if (equipe == NULL)
    {
        printf("Equipe nao encontrada.\n");
        return;
    }

    printf("Digite o nome do jogador: ");
    fgets(nome_jogador, 80, stdin);
    nome_jogador[strcspn(nome_jogador, "\n")] = '\0';

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
    }
    else
    {
        Jogador *atual = equipe->jogadores;

        while (atual->proximo != NULL)
        {
            atual = atual->proximo;
        }

        atual->proximo = novo;
    }

    printf("Jogador '%s' cadastrado com sucesso na equipe '%s'.\n",
           novo->nome, equipe->nome);
}