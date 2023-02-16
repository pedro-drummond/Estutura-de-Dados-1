#ifndef jogo_da_velha_h
#define jogo_da_velha_h

typedef struct tabuleiro TADTabuleiro;

TADTabuleiro *inicializaTabuleiro(int);

void liberaTabuleiro(TADTabuleiro **, int);

void liberaTadTabuleiro(TADTabuleiro *);

void entrada(char*, TADTabuleiro **);

int validar(TADTabuleiro *, char *);

int vitoria(TADTabuleiro *);

void analisar(char *, int, TADTabuleiro *);

void mestre(TADTabuleiro*, int );

#endif // jogo_da_velha_h
