#include <stdio.h>
#include <stdlib.h>
#include "campeonato.h"

static int saldo_gols(const Equipe *equipe) {
    return equipe->gols_pro - equipe->gols_contra;
}

static int equipe_deve_vir_depois(const Equipe *equipe_a,
                                  const Equipe *equipe_b) {
    int saldo_a = saldo_gols(equipe_a);
    int saldo_b = saldo_gols(equipe_b);

    if (equipe_a->pontos != equipe_b->pontos) {
        return equipe_a->pontos < equipe_b->pontos;
    }

    if (saldo_a != saldo_b) {
        return saldo_a < saldo_b;
    }

    if (equipe_a->gols_pro != equipe_b->gols_pro) {
        return equipe_a->gols_pro < equipe_b->gols_pro;
    }

    return 0;
}

static int contar_equipes(void) {
    int total = 0;
    Equipe *atual = equipes;

    while (atual != NULL) {
        total++;
        atual = atual->proxima;
    }

    return total;
}

void exibir_classificacao(void) {
    int total = contar_equipes();
    Equipe **ranking;
    Equipe *atual;
    int i;

    if (total == 0) {
        printf("\nNenhuma equipe cadastrada.\n");
        return;
    }

    ranking = malloc(total * sizeof(Equipe *));
    if (ranking == NULL) {
        printf("\nErro ao gerar classificacao.\n");
        return;
    }

    atual = equipes;
    for (i = 0; i < total; i++) {
        ranking[i] = atual;
        atual = atual->proxima;
    }

    for (i = 0; i < total - 1; i++) {
        int melhor = i;

        for (int j = i + 1; j < total; j++) {
            if (equipe_deve_vir_depois(ranking[melhor], ranking[j])) {
                melhor = j;
            }
        }

        if (melhor != i) {
            Equipe *temporaria = ranking[i];
            ranking[i] = ranking[melhor];
            ranking[melhor] = temporaria;
        }
    }

    printf("\n--- Tabela de Classificacao ---\n");
    printf("%-4s | %-20s | %3s | %1s | %1s | %1s | %2s | %2s | %3s\n",
           "Pos", "Equipe", "Pts", "V", "E", "D", "GP", "GC", "SG");

    for (i = 0; i < total; i++) {
        printf("%-4d | %-20s | %3d | %1d | %1d | %1d | %2d | %2d | %+3d\n",
               i + 1,
               ranking[i]->nome,
               ranking[i]->pontos,
               ranking[i]->vitorias,
               ranking[i]->empates,
               ranking[i]->derrotas,
               ranking[i]->gols_pro,
               ranking[i]->gols_contra,
               saldo_gols(ranking[i]));
    }

    free(ranking);
}
