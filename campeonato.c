#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

Equipe *equipes = NULL;
Jogo *historico_jogos = NULL;

int ler_inteiro(int *valor) {
    int resultado;
    int caractere;

    resultado = scanf("%d", valor);
    caractere = getchar();
    while (caractere != '\n' && caractere != EOF) {
        caractere = getchar();
    }

    return resultado == 1;
}

int comparar_textos(const char *primeiro, const char *segundo) {
    int indice = 0;

    while (primeiro[indice] != '\0' && segundo[indice] != '\0') {
        if (primeiro[indice] != segundo[indice]) {
            return (unsigned char)primeiro[indice] -
                   (unsigned char)segundo[indice];
        }
        indice++;
    }

    return (unsigned char)primeiro[indice] -
           (unsigned char)segundo[indice];
}

void copiar_texto(char *destino, const char *origem, int tamanho) {
    int indice = 0;

    while (indice < tamanho - 1 && origem[indice] != '\0') {
        destino[indice] = origem[indice];
        indice++;
    }
    destino[indice] = '\0';
}

void remover_quebra_linha(char *texto) {
    int indice = 0;

    while (texto[indice] != '\0') {
        if (texto[indice] == '\n') {
            texto[indice] = '\0';
            return;
        }
        indice++;
    }
}

Equipe *buscar_equipe(const char *nome) {
    Equipe *atual = equipes;

    while (atual != NULL) {
        if (comparar_textos(atual->nome, nome) == 0) {
            return atual;
        }

        atual = atual->proxima;
    }

    return NULL;
}


void cadastrar_equipe(void) {
    Equipe *nova_equipe;

    printf("\nAlocando novo no para a equipe...\n");
    nova_equipe = malloc(sizeof(Equipe));

    if (nova_equipe == NULL) {
        printf("\nErro ao alocar memoria.\n");
        return;
    }

    printf("\n--- Cadastrar Equipe ---\n");
    printf("\nNome da equipe: ");
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

    nova_equipe->proxima = NULL;
    if (equipes == NULL) {
        equipes = nova_equipe;
    } else {
        Equipe *ultima = equipes;
        while (ultima->proxima != NULL) {
            ultima = ultima->proxima;
        }
        ultima->proxima = nova_equipe;
    }

    printf("\nEquipe cadastrada com sucesso!\n");
    printf("Estatisticas iniciais: V:0 E:0 D:0 | GP:0 GC:0 | Pontos:0\n");

    int total = 0;
Equipe *atual = equipes;

while (atual != NULL) {
    total++;
    atual = atual->proxima;
}

printf("Total de equipes: %d\n", total);

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
    Jogador **marcadores = NULL;
    int *gols_marcados = NULL;
    int total_marcadores;
    int marcador_atual = 0;

    printf("\n--- Registrar Jogo ---\n");
    if (equipes == NULL) {
        printf("\nCadastre pelo menos duas equipes antes de registrar um jogo.\n");
        return;
    }

    printf("\nEquipe mandante: ");
    scanf(" %79[^\n]", nome_casa);
    printf("Equipe visitante: ");
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

    printf("Gols %s: ", equipe_casa->nome);
    if (!ler_inteiro(&gols_casa) || gols_casa < 0) {
        printf("\nQuantidade de gols invalida.\n");
        return;
    }

    printf("Gols %s: ", equipe_visitante->nome);
    if (!ler_inteiro(&gols_visitante) || gols_visitante < 0) {
        printf("\nQuantidade de gols invalida.\n");
        return;
    }

    total_marcadores = gols_casa + gols_visitante;

    if (total_marcadores > 0) {
        marcadores = malloc((size_t)total_marcadores * sizeof(*marcadores));
        gols_marcados = malloc((size_t)total_marcadores * sizeof(*gols_marcados));
        if (marcadores == NULL || gols_marcados == NULL) {
            free(marcadores);
            free(gols_marcados);
            printf("\nErro ao preparar os marcadores do jogo.\n");
            return;
        }
    }

    if (gols_casa > 0) {
        printf("\nRegistrando artilheiros do jogo...\n");
        int gols_restantes = gols_casa;
        while (gols_restantes > 0) {
            char nome_jogador[80];
            int gols_do_jogador;
            Jogador *jogador;

            printf("Jogador: ");
            scanf(" %79[^\n]", nome_jogador);
            jogador = buscar_jogador(equipe_casa, nome_jogador);
            if (jogador == NULL) {
                printf("Jogador nao encontrado nessa equipe.\n");
                continue;
            }

            printf("Gols nesta partida para %s (maximo %d): ",
                   jogador->nome, gols_restantes);
            if (!ler_inteiro(&gols_do_jogador) ||
                gols_do_jogador <= 0 || gols_do_jogador > gols_restantes) {
                printf("Quantidade de gols invalida.\n");
                continue;
            }

            marcadores[marcador_atual] = jogador;
            gols_marcados[marcador_atual] = gols_do_jogador;
            marcador_atual++;
            gols_restantes -= gols_do_jogador;
        }
    }

    if (gols_visitante > 0) {
        int gols_restantes = gols_visitante;
        while (gols_restantes > 0) {
            char nome_jogador[80];
            int gols_do_jogador;
            Jogador *jogador;

            printf("Jogador: ");
            scanf(" %79[^\n]", nome_jogador);
            jogador = buscar_jogador(equipe_visitante, nome_jogador);
            if (jogador == NULL) {
                printf("Jogador nao encontrado nessa equipe.\n");
                continue;
            }

            printf("Gols nesta partida para %s (maximo %d): ",
                   jogador->nome, gols_restantes);
            if (!ler_inteiro(&gols_do_jogador) ||
                gols_do_jogador <= 0 || gols_do_jogador > gols_restantes) {
                printf("Quantidade de gols invalida.\n");
                continue;
            }

            marcadores[marcador_atual] = jogador;
            gols_marcados[marcador_atual] = gols_do_jogador;
            marcador_atual++;
            gols_restantes -= gols_do_jogador;
        }
    }

    total_marcadores = marcador_atual;

    novo_jogo = malloc(sizeof(*novo_jogo));
    if (novo_jogo == NULL) {
        free(marcadores);
        free(gols_marcados);
        printf("\nErro ao alocar memoria para o jogo.\n");
        return;
    }

    copiar_texto(novo_jogo->time_casa, equipe_casa->nome,
                 sizeof(novo_jogo->time_casa));
    copiar_texto(novo_jogo->time_visitante, equipe_visitante->nome,
                 sizeof(novo_jogo->time_visitante));
    novo_jogo->gols_casa = gols_casa;
    novo_jogo->gols_visitante = gols_visitante;
    novo_jogo->proximo = NULL;
    if (historico_jogos == NULL) {
        historico_jogos = novo_jogo;
    } else {
        Jogo *ultimo_jogo = historico_jogos;
        while (ultimo_jogo->proximo != NULL) {
            ultimo_jogo = ultimo_jogo->proximo;
        }
        ultimo_jogo->proximo = novo_jogo;
    }

    for (marcador_atual = 0; marcador_atual < total_marcadores; marcador_atual++) {
        marcadores[marcador_atual]->gols += gols_marcados[marcador_atual];
    }
    free(marcadores);
    free(gols_marcados);

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

    printf("\nJogo registrado com sucesso!\n");
    printf("%s %d x %d %s.\n",
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
