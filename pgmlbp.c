#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca_pgms.h"
#include "biblioteca_funcoes.h"
#include "biblioteca_leitura.h"


int main (int argc, char *argv[]){

    dados *d=malloc(sizeof(dados));
    
    pgm *antiga= malloc(sizeof(pgm));
    pgm *nova = malloc(sizeof(pgm));

    d=le_parametros(d,argc,argv);
    
    le_e_cria_matriz(antiga,d,argv);

    cria_pgm_vazio(nova,antiga->tipo,antiga->lin,antiga->col,255);

    lbp(antiga,nova);

    cria_arquivo(nova,d,argv);
    libera_memoria(antiga);
    libera_memoria(nova);
    return 1;

}