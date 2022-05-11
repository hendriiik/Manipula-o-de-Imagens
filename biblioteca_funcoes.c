//biblioteca com filtros para imagens pgm

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "biblioteca_funcoes.h"
#include "biblioteca_pgms.h"


int compara(const void *a, const void *b){
//funcao auxiliar do qsort
    if(*(unsigned char*)a > *(unsigned char*)b)
        return 1;

    else if (*(unsigned char*)a < *(unsigned char*)b)
        return -1;

    else
        return 0;    
}


void nega(pgm *antiga, pgm *nova){
//funcao que inverte as imagens
    int i,j;
    
    for (i=0; i<antiga->lin; i++)
        for (j=0; j<antiga->col; j++)
            nova->mat[i][j]=antiga->max - antiga->mat[i][j];
}

void lbp(pgm *antiga,pgm *nova){
//funcao que aplica o filtro lbp
    int i,j, k, l;
    unsigned char multiplicacao, soma, limiar;
    unsigned char matriz_lbp[3][3];

    for (i=0;i<antiga->lin; i++){ //percorre a matriz aplicando o filtro
        for (j=0;j<antiga->col;j++){

            if((i==0 || i==antiga->lin -1) || (j==0 || j==antiga->col-1))    //se for borda, simplismente imprime
                nova->mat[i][j]=antiga->mat[i][j];
            

            else{
                multiplicacao=1;    //inicia a multiplicacao com expoente 0 (2^0)
                soma=0;             //a soma inicia em 0

                limiar=antiga->mat[i][j];    //o limiar da matriz de vizinhos eh o valor central

                for (k=-1;k<=1;k++){
                    for(l=-1;l<=1;l++){
                        if (k != 0 || l != 0){  //se nao for o central, compara com ele, gerando 0 ou 1
                            
                            if (antiga->mat[i+k][j+l] >= limiar)
                                matriz_lbp[k+1][l+1] = 1;

                            else
                                matriz_lbp[k+1][l+1] = 0;

                            matriz_lbp[k+1][l+1]= multiplicacao*matriz_lbp[k+1][l+1];   //multiplica pelo expoente de 2 atual 
                            
                            soma=soma+matriz_lbp[k+1][l+1]; //atualiza a soma e o expoente de 2
                            multiplicacao=multiplicacao*2;
                            
                        }


                    }
                }

                nova->mat[i][j]=soma;

             }
        }
    }
}

void limiar(pgm *antiga, pgm *nova, float limite){
//aplica o filtro limiar

    int i,j;
    unsigned char lim;
     
    lim=limite*antiga->max; //descobre qual sera o pixel limite

    for (i=0; i<antiga->lin; i++){
        for (j=0; j<antiga->col; j++){
            if (antiga->mat[i][j] >= lim)
                nova->mat[i][j]= antiga->max;   //se for maior que o pixel limite, recebe preto

            else
                nova->mat[i][j]=0;     //senao recebe branco
        
        }
    }
}

void media(pgm *antiga, pgm *nova){
//aplica o filtro de reducao de ruido pela media

    int i,j, k,l,qtdade_vizinhos, novo_i,novo_j;
    unsigned novo_valor;

    for (i=0;i<antiga->lin;i++){
        for (j=0;j<antiga->col; j++){
            novo_valor=0;   //inicia media
            qtdade_vizinhos=0; //inicia vizinhos

            for (k=-1;k<=1;k++){
                for(l=-1;l<=1;l++){
                    novo_i=i+k; //calcula o x do vizinho atual
                    novo_j=j+l; //calcula o y do vizinho atual

                    if ((novo_i >=0 && novo_i < antiga->lin) && (novo_j >=0 && novo_j < antiga->col)){    //se for um vizinho valido, adiciona na media
                        novo_valor= novo_valor + antiga->mat[novo_i][novo_j];  //media = media + valor adjascente
                        qtdade_vizinhos++;  //vizinho valido
                    }
                }
            }

            novo_valor=novo_valor/qtdade_vizinhos;  //calcula a media
            nova->mat[i][j]=novo_valor;
        }
    }

}

void mediana(pgm *antiga, pgm *nova,int mascara){
//aplica o filtro de reducao de ruido pela mediana

    int i,j,k,l,qtdade_vizinhos,novo_i,novo_j,tam_masc;
    unsigned char novo_valor;
    unsigned char vizinhos[1000];

    if(mascara%2 == 0)
        mascara=mascara+1;
    //se a mascara nao for um impar, transforma em um

    tam_masc=(mascara-1)/2;
    
    for (i=0;i<antiga->lin;i++){
        for (j=0;j<antiga->col; j++){
            qtdade_vizinhos=0; //inicia vizinhos

            for (k=-tam_masc;k<=tam_masc;k++){
                for(l=-tam_masc;l<=tam_masc;l++){
                    novo_i=i+k; //calcula o x do vizinho atual
                    novo_j=j+l; //calcula o y do vizinho atual

                    if ((novo_i >=0 && novo_i < antiga->lin) && (novo_j >=0 && novo_j < antiga->col)){
                        //se for um vizinho valido, adiciona na media
                        vizinhos[qtdade_vizinhos] = antiga->mat[novo_i][novo_j];  //media = media + valor adjascente
                        qtdade_vizinhos++;  //vizinho valido
                    }
                    
                }
            }

            qsort(vizinhos,qtdade_vizinhos,sizeof(unsigned char),compara);   //ordena o vetor de vizinhos

            novo_valor=vizinhos[qtdade_vizinhos/2]; //o pixel atual recebe o elemento da mediana do vetor

            nova->mat[i][j]=novo_valor;

        }
    }
}

void rotacao(pgm *antiga, pgm *nova, float rad){
    //aplica o filtro de rotacionamento
    int novo_lin,novo_col,lin_min,col_min,i,j,lin_teste,col_teste;

    lin_min=nova->lin;
    col_min=nova->col;

    for(i=0;i< antiga->lin ;i++){
        for(j=0;j<antiga->col;j++){
        //checa os cantos e pega os menores deles, que serao usados para arrumar a posicao da matriz

            lin_teste=cos(rad)*i + sin(rad)*j;
            col_teste=cos(rad)*j - sin(rad)*i;

            if (lin_min > lin_teste)
                lin_min=lin_teste;

            if(col_min > col_teste)
                col_min=col_teste;
        }
    }


    for (i=0; i< antiga->lin; i++){
        for (j=0;j< antiga->col; j++){
        //imprime os pixeis da antiga matriz na nova

            novo_lin=i*cos(rad)+j*sin(rad);
            novo_col=j*cos(rad)-i*sin(rad);
            nova->mat[novo_lin-lin_min][novo_col-col_min]=antiga->mat[i][j];
            
        }
    }
}