//biblioteca que faz a leitura dos argumentos passados por linha de comando, e passa eles para uma struct dados

#ifndef BIBLIOTECA_LEITURA
#define BIBLIOTECA_LEITURA

typedef struct dados{
    int input;  //posicao do input em argv
    int output; //posicao do output em argv
    int outros; //posicao de outros dados em argv
}dados;

void erro(void);
//imprime uma mensagem de erro

dados * le_parametros(dados *d,int argc,char *argv[] );
//le todos os parametros inseridos, retornando uma struct com a posicao deles em argv

void procura_i(dados *d, int argc, char *argv[]);
//funcao que encontra qual sera o arquivo input

void procura_o(dados *d, int argc, char *argv[]);
//funcao que encontra qual sera o arquivo output

void procura_angulo(dados *d, int argc, char *argv[]);
//funcao que encontra o angulo inserido (usado na rotacao)

void procura_limiar(dados *d, int argc, char *argv[]);
//funcao que encontra o limiar inserido (usado no filtro limiar)

void procura_mascara(dados *d, int argc, char *argv[]);
//funcao que encontra a mascara que sera utilizada para calcular o filtro mediana
 
#endif