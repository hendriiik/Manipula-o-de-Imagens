#ifndef BIBLIOTECA_FUNCOES
#define BIBLIOTECA_FUNCOES

#include "biblioteca_pgms.h"

#define PI 3.141592

//biblioteca_funcoes.h

//void quick_sort (int *a, int n);
//implementacao do quicksort

int compara(const void *a, const void *b);
//funcao auxiliar do qsort

void nega(pgm *antiga, pgm *nova);
//funcao que inverte as imagens

void lbp(pgm *antiga,pgm *nova);
//funcao que aplica o filtro lbp

void limiar(pgm *antiga, pgm *nova,float limite);
//funcao que aplica o filtro limiar

void media(pgm *antiga, pgm *nova);
//funcao aplica o filtro de reducao de ruido pela media

void mediana(pgm *antiga, pgm *nova,int mascara);
//aplica o filtro de reducao de ruido pela mediana

void rotacao(pgm *antiga, pgm *nova, float rad);
//funcao que aplica o filtro de rotacionamento

#endif