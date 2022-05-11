#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "biblioteca_leitura.h"


void erro(void){
//imprime uma mensagem de erro
    perror("Erro! Argumento(s) invalido(s)!");
}

void procura_i(dados *d, int argc, char *argv[]){
//funcao que encontra qual sera o arquivo input
    int i,achou;

    i=0;
    achou=0;

    while ((i<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[i],"-i") == 0)){
            d->input=i+1;
            achou=1;
        }
        i++;
    }

    if (achou == 0)
        perror("ERRO");


}

void procura_o(dados *d, int argc, char *argv[]){
//funcao que encontra qual sera o arquivo output
    int i,achou;

    i=0;
    achou=0;

    while ((i<argc-1) && (achou != 1)){
        if ((strcmp(argv[i],"-o")==0)){
            d->output=i+1;
            achou=1;
        }
        i++;
    }

    if (achou == 0)
        printf("ERRO!");

}

void procura_angulo(dados *d, int argc, char *argv[]){
//funcao que encontra o angulo inserido (usado na rotacao)
    int i,achou;

    i=0;
    achou=0;

    while ((i<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[i],"-a")==0)){
            d->outros=i+1;
            achou=1;
        }
        i++;

    }
    if (achou == 0)
        d->outros=-1;

}

void procura_limiar(dados *d, int argc, char *argv[]){
//funcao que encontra o limiar inserido (usado no filtro limiar)
    int i,achou;

    i=0;
    achou=0;

    while ((i<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[i],"-l")==0)){
            d->outros=i+1;
            achou=1;
        }
        i++;
    }

    if (achou == 0)
        d->outros=-1;
        

}

void procura_mascara(dados *d, int argc, char *argv[]){
//funcao que encontra a mascara que sera utilizada para calcular o filtro mediana
    int i,achou;

    i=0;
    achou=0;

    while ((i<(argc-1)) && (achou != 1)){
        if ((strcmp(argv[i],"-m")==0)){
            d->outros=i+1;
            achou=1;
        }
        i++;
    }

    if (achou == 0)
        d->outros=-1;

}


    
dados * le_parametros(dados *d,int argc,char *argv[] ){
    //le todos os parametros inseridos, retornando uma struct com a posicao deles em argv

    procura_i(d,argc,argv);
    procura_o(d,argc,argv);

    if ((strcmp(argv[0],"./pgmrotacao")==0))
        procura_angulo(d,argc,argv);


    if ((strcmp(argv[0],"./pgmlimiar")==0))
        procura_limiar(d,argc,argv);


    if ((strcmp(argv[0],"./pgmmediana")==0))
        procura_mascara(d,argc,argv);

    return d;

}

