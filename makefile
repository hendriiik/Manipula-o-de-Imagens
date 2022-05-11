
#makefile para tratamento de imagens pgm
#autor: Hendrik Kees Koppe

OPCOES= -Wall
BIBLIOTECAS= -lm

all:pgmlbp pgmlimiar pgmmedia pgmmediana pgmnega pgmrotacao

clean: 
	-rm -f *.o *~

purge: clean
	-rm -f pgmnega pgmmedia pgmmediana pgmlimiar pgmlbp pgmrotacao 


pgmnega: pgmnega.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o
	gcc $(OPCOES) pgmnega.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o -o pgmnega $(BIBLIOTECAS)

pgmmedia: pgmmedia.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o
	gcc $(OPCOES) pgmmedia.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o -o pgmmedia $(BIBLIOTECAS)

pgmmediana: pgmmediana.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o
	gcc $(OPCOES) pgmmediana.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o -o pgmmediana $(BIBLIOTECAS)

pgmlimiar: pgmlimiar.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o
	gcc $(OPCOES) pgmlimiar.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o -o pgmlimiar $(BIBLIOTECAS)


pgmlbp: pgmlbp.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o
	gcc $(OPCOES) pgmlbp.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o -o pgmlbp $(BIBLIOTECAS)


pgmrotacao: pgmrotacao.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o
	gcc $(OPCOES) pgmrotacao.o biblioteca_leitura.o biblioteca_funcoes.o biblioteca_pgms.o -o pgmrotacao $(BIBLIOTECAS)

biblioteca_leitura.o: biblioteca_leitura.c biblioteca_leitura.h
	gcc $(OPCOES) -c biblioteca_leitura.c

biblioteca_pgms.o: biblioteca_pgms.c biblioteca_pgms.h
	gcc $(OPCOES) -c biblioteca_pgms.c

biblioteca_funcoes.o: biblioteca_funcoes.c biblioteca_funcoes.h
	gcc $(OPCOES) -c biblioteca_funcoes.c $(BIBLIOTECAS)

pgmnega.o: pgmnega.c
	gcc $(OPCOES) -c pgmnega.c 

pgmmedia.o: pgmmedia.c
	gcc $(OPCOES) -c pgmmedia.c

pgmmediana.o: pgmmediana.c
	gcc $(OPCOES) -c pgmmediana.c

pgmlimiar.o: pgmlimiar.c
	gcc $(OPCOES) -c pgmlimiar.c

pgmlbp.o: pgmlbp.c
	gcc $(OPCOES) -c pgmlbp.c

pgmrotacao.o: pgmrotacao.c
	gcc $(OPCOES) -c pgmrotacao.c $(BIBLIOTECAS)
