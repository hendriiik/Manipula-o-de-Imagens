#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "biblioteca_pgms.h"

pgm * le_e_cria_matriz(pgm *m,dados *d,char *argv[]){
//funcao que le e armazena o pgm em uma struct, com informacoes como max, linhas,colunas e tipo do pgm
    
    FILE *arq;
    int i, j ;
    char tipo[3],comentario[500];
    int linhas,colunas,max;


    arq = fopen(argv[d->input], "rb");

    if (!arq)
        perror("Erro! O arquivo nao existe!");
        //caso o arquivo nao exista, devolve erro
    

    else if (fgets (tipo, 3, arq) == NULL) 
        perror("Error opening file");
    

    else{

        if (strcmp(tipo,"P2") == 0)
            m->tipo=2;
            //tipo do arquivo eh p2


        else if (strcmp(tipo,"P5") == 0)
            m->tipo=5;
            //tipo do arquivo eh p5
    
        
        else
            perror("Arquivo invalido. O programa sera abortado\n");
            //tipo de arquivo invalido

    
        if(fgetc(arq)!= '\n')
            fseek(arq,-1,SEEK_CUR);

        if (fgetc(arq) == '#'){
            fgets(comentario,500,arq);
            //se tiver um comentario, le seus primeiros 500 caracteres ou ateh chegar num \n, pulando ele 
        }
        else 
            fseek(arq, -1, SEEK_CUR);
            //se nao for um comentario, volta o ponteiro do arquivo de volta para tras

        
        fscanf(arq, "%i %i\n", &colunas, &linhas);
        m->col=colunas; 
        m->lin=linhas;
        fscanf(arq, "%i\n", &max);
        m->max=max;

        

        m->mat = malloc (m->lin * sizeof (unsigned char*)) ;
        // aloca cada uma das linhas (vetores de COL inteiros)
        for (i=0; i < m->lin; i++)
            m->mat[i] = malloc (m->col * sizeof (unsigned char)) ;
            

        if(m->tipo==2){

            // percorre a matriz lendo o tipo p2
            for (i=0; i < m->lin; i++)
                for (j=0; j < m->col; j++)
                    fscanf(arq, "%hhu", &m->mat[i][j]); 
            
        }

        else{
            
            // percorre a matriz lendo o tipo p5
            for (i=0; i < m->lin; i++)
                for (j=0; j < m->col; j++)
                    fread(&m->mat[i][j],sizeof(unsigned char),1,arq ); 

        }
    }
    fclose(arq);
    return m;
}

void cria_pgm_vazio(pgm *m,int tipo,int linhas,int colunas,int maximo){
//aloca e cria um struct pgm com todos os pixeis = 0, ou seja, preto

    int i,j;

    m->col=colunas;
    m->lin=linhas;
    m->max=maximo;
    m->tipo=tipo;

    m->mat = malloc (m->lin * sizeof (unsigned char*)) ;
    
    // aloca cada uma das linhas (vetores de COL inteiros)
    for (i=0; i < m->lin; i++)
        m->mat[i] = malloc (m->col * sizeof (unsigned char)) ;

    for(i=0;i<linhas;i++)
        for(j=0;j<colunas;j++)
            m->mat[i][j]=0;

}

void cria_pgm_vazio_branco(pgm *m,int tipo,int linhas,int colunas,int maximo){
//aloca e cria um struct pgm com todos os pixeis = max, ou seja, branco

    int i,j;

    m->col=colunas;
    m->lin=linhas;
    m->max=maximo;
    m->tipo=tipo;

    m->mat = malloc (m->lin * sizeof (unsigned char*)) ;
    
    // aloca cada uma das linhas (vetores de col inteiros)
    for (i=0; i < m->lin; i++)
        m->mat[i] = malloc (m->col * sizeof (unsigned char)) ;

    for(i=0;i<linhas;i++)
        for(j=0;j<colunas;j++)
            m->mat[i][j]=maximo;
            //insere branco no pixel

}

void cria_arquivo(pgm *m,dados *d,char *argv[]){
//cria um novo arquivo, com o nome dado em argv, e com os dados de m
    int i,j;
    
    FILE *novo_arq;
    novo_arq = fopen(argv[d->output], "w");

    fprintf(novo_arq,"P");
    if (m->tipo == 2)
        fprintf(novo_arq,"2\n");

    else
        fprintf(novo_arq,"5\n");

    fprintf(novo_arq, "%i %i\n", m->col,m->lin);
    fprintf(novo_arq, "%i\n", m->max);


    if (m->tipo == 2){
        for (i=0; i<m->lin; i++){
            for (j=0; j<m->col; j++){
            //imprime a matriz no arquivo p2
                fprintf(novo_arq, "%i",m->mat[i][j]);
                fprintf(novo_arq, " ");
            }
            fprintf(novo_arq,"\n");
        }
    }

    else{
         for (i=0; i<m->lin; i++)
            for (j=0; j<m->col; j++)
                //imprime a matriz no arquivo p5
                fwrite(&m->mat[i][j],1,sizeof(m->mat[i][j]),novo_arq);
    }

    fclose(novo_arq);

}

void copia_matriz(pgm *nova, pgm *antiga){
//copia a matriz antiga na nova
    int i,j;

    nova->col=antiga->col;
    nova->lin=antiga->lin;
    nova->max=antiga->max;
    nova->tipo=antiga->tipo;

    for(i=0;i<antiga->lin;i++)
        for(j=0;j<antiga->col;j++)
            nova->mat[i][j]=antiga->mat[i][j];

}

void libera_memoria(pgm *matriz){
//libera a matriz alocada dinamicamente
    int i;

    for (i=0; i < matriz->lin; i++)
        free (matriz->mat[i]) ;
            free (matriz->mat) ;

    free(matriz);

}