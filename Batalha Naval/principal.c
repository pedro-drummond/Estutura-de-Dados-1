#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"
#define TAM 3

int main(){
    int qtdTabuleiro, contador = 0, check;
    char jogo[9];
    TADTabuleiro *tab;
    //numero de tabuleiros a ser analisado
    scanf("%d", &qtdTabuleiro);
    //main loop
    while (contador < qtdTabuleiro){
        tab = inicializaTabuleiro(TAM);
        contador++;;
        entrada(jogo, &tab);
        check = validar(tab, jogo);
        if(check == 1){
            printf("Tabuleiro %d invalido\n", contador);
        }
        else{
           analisar(jogo, contador, tab);
        }
        liberaTabuleiro(&tab, TAM);
        liberaTadTabuleiro(tab);
    }
    return 0;
}