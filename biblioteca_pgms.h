//biblioteca que maneja pgms e matriz

#ifndef BIBLIOTECA_PGMS
#define BIBLIOTECA_PGMS

#include "biblioteca_leitura.h"

//biblioteca_pgms.h

typedef struct pgm{
    int tipo;   //tipo: se eh p2 (2) ou p5 (5)
    int col;      //tamanho x
    int lin;      //tamanho y
    int max;    //maximo da matriz
    unsigned char **mat;
} pgm;


pgm * le_e_cria_matriz(pgm *m, dados *d,char *argv[]);
//funcao que le e armazena o pgm em uma struct, com informacoes como max, linhas,colunas e tipo do pgm

void cria_pgm_vazio(pgm *m,int tipo,int linhas,int colunas,int maximo);
//funcao que aloca e cria um struct pgm com todos os pixeis = 0, ou seja, preto

void cria_pgm_vazio_branco(pgm *m,int tipo,int linhas,int colunas,int maximo);
//funcao que aloca e cria um struct pgm com todos os pixeis = max, ou seja, branco

void cria_arquivo(pgm *m,struct dados *d,char *argv[]);
//funcao que cria um novo arquivo, com o nome dado em argv, e com os dados de m

void copia_matriz(pgm *nova, pgm *antiga);
//funcao que copia a matriz antiga na nova

void libera_memoria(pgm *matriz);
//funcao que libera a matriz alocada dinamicamente


#endif