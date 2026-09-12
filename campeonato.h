#ifndef CAMPEONATO_H
#define CAMPEONATO_H

typedef struct Jogador {
    char nome[80];
    int gols;
    struct Jogador *proximo;
} Jogador;

typedef struct Equipe {
    char nome[80];
    int vitorias;
    int empates;
    int derrotas;
    int gols_pro;
    int gols_contra;
    int pontos;
    Jogador *jogadores;
    struct Equipe *proxima;
} Equipe;

typedef struct Jogo {
    char time_casa[80];
    char time_visitante[80];
    int gols_casa;
    int gols_visitante;
    struct Jogo *proximo;
} Jogo;

extern Equipe *equipes;
extern Jogo *historico_jogos;

int comparar_textos(const char *primeiro, const char *segundo);
void copiar_texto(char *destino, const char *origem, int tamanho);
void remover_quebra_linha(char *texto);
int ler_inteiro(int *valor);

void cadastrar_equipe(void);
Equipe *buscar_equipe(const char *nome);
Jogador *buscar_jogador(Equipe *equipe, const char *nome);
void cadastrar_jogador(void);
void registrar_jogo(void);
void exibir_classificacao(void);
void exibir_artilheiros(void);
void listar_equipes_jogadores(void);
void liberar_memoria(void);

#endif
