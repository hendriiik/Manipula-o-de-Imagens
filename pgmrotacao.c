#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioteca_pgms.h"
#include "biblioteca_funcoes.h"
#include "biblioteca_leitura.h"


int main (int argc, char *argv[]){

    int graus,lin_trans,col_trans;
    float rad,rad2;

    dados *d=malloc(sizeof(dados));
    pgm *antiga= malloc(sizeof(pgm));
    pgm *nova = malloc(sizeof(pgm));

    d=le_parametros(d,argc,argv);
    
    le_e_cria_matriz(antiga,d,argv);

    if(d->outros == -1)
        graus=90;

    else
        graus=atoi(argv[d->outros]);
        

    rad=(graus*PI)/180;
 
    rad2= PI/2 - rad;


    if (graus < 90){
        lin_trans=sin(rad)*antiga->col + sin(rad2)*antiga->lin; 
        col_trans=cos(rad)*antiga->col + cos(rad2)*antiga->lin;
    }

    else{
        col_trans=sin(rad)*antiga->col + sin(rad2)*antiga->lin;
        lin_trans=cos(rad)*antiga->col + cos(rad2)*antiga->lin;
    }


    cria_pgm_vazio_branco(nova,antiga->tipo,lin_trans,col_trans,antiga->max);

    rotacao(antiga,nova,rad);

    cria_arquivo(nova,d,argv);

    libera_memoria(antiga);
    libera_memoria(nova);
    
    return 1;
}