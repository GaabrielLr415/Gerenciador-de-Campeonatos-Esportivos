#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_JOGADORES_EQUIPE 30

// Struturas do sistema
typedef struct {
    char nome[MAX_NOME];
    int gols;
} Jogador;

typedef struct {
    char nome[MAX_NOME];
    int pontos;
    Jogador jogadores[MAX_JOGADORES_EQUIPE];
    int qtd_jogadores;
} Equipe;

// Estrutura auxiliar para ordenação de artilheiros
typedef struct {
    char nome_jogador[MAX_NOME];
    char nome_equipe[MAX_NOME];
    int gols;
} Artilheiro;

// Protótipos das funções
void adicionar_jogador(Equipe *equipe, const char *nome, int gols);
void listar_artilheiros(Equipe equipes[], int qtd_equipes);
void listar_equipes_e_jogadores(Equipe equipes[], int qtd_equipes);

int main() {
    // Exemplo de inicialização de equipes
    Equipe equipes[2];

    // Equipe 1: Flamengo
    strcpy(equipes[0].nome, "Flamengo");
    equipes[0].pontos = 10;
    equipes[0].qtd_jogadores = 0;
    adicionar_jogador(&equipes[0], "Gabigol", 5);
    adicionar_jogador(&equipes[0], "Pedro", 8);

    // Equipe 2: Palmeiras
    strcpy(equipes[1].nome, "Palmeiras");
    equipes[1].pontos = 12;
    equipes[1].qtd_jogadores = 0;
    adicionar_jogador(&equipes[1], "Veiga", 6);
    adicionar_jogador(&equipes[1], "Rony", 3);

    int qtd_equipes = 2;

    // Execução das consultas
    listar_artilheiros(equipes, qtd_equipes);
    listar_equipes_e_jogadores(equipes, qtd_equipes);

    return 0;
}

// Função para associar jogador à equipe
void adicionar_jogador(Equipe *equipe, const char *nome, int gols) {
    if (equipe->qtd_jogadores < MAX_JOGADORES_EQUIPE) {
        strcpy(equipe->jogadores[equipe->qtd_jogadores].nome, nome);
        equipe->jogadores[equipe->qtd_jogadores].gols = gols;
        equipe->qtd_jogadores++;
    }
}

// Requisito: Percorrer equipes/jogadores, ordenar por gols e exibir artilheiros
void listar_artilheiros(Equipe equipes[], int qtd_equipes) {
    // 1. Contagem total de jogadores em todas as equipes
    int total_jogadores = 0;
    for (int i = 0; i < qtd_equipes; i++) {
        total_jogadores += equipes[i].qtd_jogadores;
    }

    if (total_jogadores == 0) {
        printf("Nenhum jogador cadastrado.\n");
        return;
    }

    // 2. Criação do array temporário para armazenar a lista consolidada
    Artilheiro *lista_artilheiros = (Artilheiro *)malloc(total_jogadores * sizeof(Artilheiro));
    int idx = 0;

    // Percorre todas as equipes e os jogadores de cada equipe
    for (int i = 0; i < qtd_equipes; i++) {
        for (int j = 0; j < equipes[i].qtd_jogadores; j++) {
            strcpy(lista_artilheiros[idx].nome_jogador, equipes[i].jogadores[j].nome);
            strcpy(lista_artilheiros[idx].nome_equipe, equipes[i].nome);
            lista_artilheiros[idx].gols = equipes[i].jogadores[j].gols;
            idx++;
        }
    }

    // 3. Ordenação (Bubble Sort) por número de gols (Ordem Decrescente)
    for (int i = 0; i < total_jogadores - 1; i++) {
        for (int j = 0; j < total_jogadores - i - 1; j++) {
            if (lista_artilheiros[j].gols < lista_artilheiros[j + 1].gols) {
                Artilheiro temp = lista_artilheiros[j];
                lista_artilheiros[j] = lista_artilheiros[j + 1];
                lista_artilheiros[j + 1] = temp;
            }
        }
    }

    // 4. Exibição da artilharia
    printf("=== LISTA DE ARTILHEIROS ===\n");
    for (int i = 0; i < total_jogadores; i++) {
        printf("%dº - %s (%s): %d gols\n", 
               i + 1, 
               lista_artilheiros[i].nome_jogador, 
               lista_artilheiros[i].nome_equipe, 
               lista_artilheiros[i].gols);
    }
    printf("\n");

    free(lista_artilheiros);
}

// Requisito: Listar todas as equipes, seus pontos e respectivos jogadores
void listar_equipes_e_jogadores(Equipe equipes[], int qtd_equipes) {
    printf("=== CLASSIFICAÇÃO E ELENCOS ===\n");
    for (int i = 0; i < qtd_equipes; i++) {
        printf("\nEquipe: %s | Pontos: %d\n", equipes[i].nome, equipes[i].pontos);
        printf("Jogadores:\n");
        
        if (equipes[i].qtd_jogadores == 0) {
            printf("  - Nenhum jogador cadastrado\n");
        } else {
            for (int j = 0; j < equipes[i].qtd_jogadores; j++) {
                printf("  - %s (%d gols)\n", equipes[i].jogadores[j].nome, equipes[i].jogadores[j].gols);
            }
        }
    }
}