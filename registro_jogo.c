#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

void registrar_jogo(void) {
    char nome_casa[80], nome_visitante[80];
    int gols_casa, gols_visitante;
    Equipe *equipe_casa, *equipe_visitante;
    Jogo *novo_jogo;

    if (equipes == NULL) {
        printf("\nCadastre pelo menos duas equipes antes de registrar um jogo.\n");
        return;
    }

    /* Cabecalho exato do PDF */
    printf("--- Registrar Jogo ---\n");
    printf("Equipe mandante: ");
    scanf(" %79[^\n]", nome_casa);
    printf("Equipe visitante: ");
    scanf(" %79[^\n]", nome_visitante);

    equipe_casa = buscar_equipe(nome_casa);
    equipe_visitante = buscar_equipe(nome_visitante);

    /* Validacao do Teste 7 */
    if (equipe_casa == NULL) {
        printf("Erro: equipe \"%s\" nao encontrada.\n", nome_casa);
        printf("Nenhuma memoria foi alocada.\n");
        printf("Jogo nao registrado.\n");
        return;
    }
    if (equipe_visitante == NULL) {
        printf("Erro: equipe \"%s\" nao encontrada.\n", nome_visitante);
        printf("Nenhuma memoria foi alocada.\n");
        printf("Jogo nao registrado.\n");
        return;
    }

    if (equipe_casa == equipe_visitante) {
        printf("\nAs equipes do jogo devem ser diferentes.\n");
        return;
    }

    printf("Gols %s: ", equipe_casa->nome);
    if (scanf("%d", &gols_casa) != 1 || gols_casa < 0) {
        printf("\nQuantidade de gols invalida.\n");
        return;
    }

    printf("Gols %s: ", equipe_visitante->nome);
    if (scanf("%d", &gols_visitante) != 1 || gols_visitante < 0) {
        printf("\nQuantidade de gols invalida.\n");
        return;
    }

    /* Leitura dos artilheiros conforme Testes 5 e 6 */
    if (gols_casa > 0 || gols_visitante > 0) {
        printf("Registrando artilheiros do jogo...\n");

        /* Artilheiros do mandante */
        int gols_restantes = gols_casa;
        while (gols_restantes > 0) {
            char nome_artilheiro[80];
            int gols_marcados;
            Jogador *jog;

            printf("Jogador: ");
            scanf(" %79[^\n]", nome_artilheiro);
            printf(" | Gols nesta partida: ");
            scanf("%d", &gols_marcados);

            jog = buscar_jogador(equipe_casa, nome_artilheiro);
            if (jog != NULL) {
                jog->gols += gols_marcados;
                gols_restantes -= gols_marcados;
            } else {
                printf("Jogador nao encontrado. Tente novamente.\n");
            }
        }

        /* Artilheiros do visitante */
        gols_restantes = gols_visitante;
        while (gols_restantes > 0) {
            char nome_artilheiro[80];
            int gols_marcados;
            Jogador *jog;

            printf("Jogador: ");
            scanf(" %79[^\n]", nome_artilheiro);
            printf(" | Gols nesta partida: ");
            scanf("%d", &gols_marcados);

            jog = buscar_jogador(equipe_visitante, nome_artilheiro);
            if (jog != NULL) {
                jog->gols += gols_marcados;
                gols_restantes -= gols_marcados;
            } else {
                printf("Jogador nao encontrado. Tente novamente.\n");
            }
        }
    }

    /* Alocacao de memoria e informacao nos logs */
    printf("Alocando novo no para o jogo no historico...\n");
    novo_jogo = malloc(sizeof(Jogo));
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

    printf("Jogo registrado com sucesso!\n");
    printf("Atualizando estatisticas...\n");

    /* Atualizacao de gols */
    equipe_casa->gols_pro += gols_casa;
    equipe_casa->gols_contra += gols_visitante;
    equipe_visitante->gols_pro += gols_visitante;
    equipe_visitante->gols_contra += gols_casa;

    /* Atualizacao de pontuacoes */
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
        equipe_casa->pontos += 1;
        equipe_visitante->pontos += 1;
    }

    /* Saida formatada identica ao PDF */
    printf("%s: %s | V:%d E:%d D:%d | GP:%d GC:%d\n",
           equipe_casa->nome,
           (gols_casa > gols_visitante) ? "Vitoria (+3 pontos)" : (gols_casa < gols_visitante ? "Derrota (+0 pontos)" : "Empate (+1 ponto)"),
           equipe_casa->vitorias, equipe_casa->empates, equipe_casa->derrotas, equipe_casa->gols_pro, equipe_casa->gols_contra);

    printf("%s: %s | V:%d E:%d D:%d | GP:%d GC:%d\n",
           equipe_visitante->nome,
           (gols_visitante > gols_casa) ? "Vitoria (+3 pontos)" : (gols_visitante < gols_casa ? "Derrota (+0 pontos)" : "Empate (+1 ponto)"),
           equipe_visitante->vitorias, equipe_visitante->empates, equipe_visitante->derrotas, equipe_visitante->gols_pro, equipe_visitante->gols_contra);
}
