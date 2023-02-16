#include "buscabinaria.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//inicia um dicionário
void TDicionario_Inicia(TDicionario *t, int malhas){
    t->cont = 0; //contador de iteraçoes
    t->max = malhas; //numero de malhas
    t->v = (TRegistro*) malloc(t->max * sizeof(TRegistro));
}

void LiberaMemoria(TDicionario *t){
    free(t->v);
}

int TDicionario_find(TDicionario *t, TChave x){
    return TDicionario_Binaria(t, x, 0, t->max-1);
}

int CheckPos(TDicionario *t, int pos, TChave x){
    if(t->v[pos].Chave == x) return pos;
    else return -1;
}


int TDicionario_Binaria(TDicionario *t, TChave x, int esq, int dir){
    
if(esq > dir) return -1;
    int meio = floor((esq + dir)/2);
    t->cont++;
    if(t->v[meio].Chave == x){  
        return meio;
    }
    if(t->v[meio].Chave > x){
        return TDicionario_Binaria(t, x, esq, meio-1);
        
    }
    else{
        return TDicionario_Binaria(t, x, meio+1, dir);  
    }
    
}

void lerMalhas(int m, TDicionario *dicionario, int *pos, int *alvo) {
    //le as malhas e armazena no dicionario
    for(int i = 0; i < m; i++){
        scanf("%d", &dicionario->v[i].Chave);
    }
    scanf("%d %d", pos, alvo);

}

void exibeResultado(int posDesejada, int posEncontrada, int interacoes) {

    //TDicionario_find(&dicionario, int );

    if(posDesejada != posEncontrada){
        int resto = posDesejada % 10;

        if(posEncontrada != -1 && resto == 1){
            printf("Disparo impreciso: %d divisoes para conquistar o porta aviões %d!\n", interacoes, posDesejada);
        }else if(posEncontrada != -1 && resto == 2){
            printf("Disparo impreciso: %d divisoes para conquistar o encouraçado %d!\n", interacoes, posDesejada);
        }else if(posEncontrada != -1 && resto == 3){
            printf("Disparo impreciso: %d divisoes para conquistar o cruzador %d!\n", interacoes, posDesejada);
        }else if(posEncontrada != -1 && resto == 4){
            printf("Disparo impreciso: %d divisoes para conquistar o fragata %d!\n", interacoes, posDesejada);
        }else if(posEncontrada != -1 && resto == 5){
            printf("Disparo impreciso: %d divisoes para conquistar o submarino %d!\n", interacoes, posDesejada);
        }

        if(posEncontrada == -1 && resto == 1 ){
            printf("Disparo incorreto: Malha sem o porta aviões %d!\n", posDesejada);
        }else if(posEncontrada == -1 && resto == 2){
            printf("Disparo incorreto: Malha sem o encouraçado %d!\n", posDesejada);
        }else if(posEncontrada == -1 && resto == 3){
            printf("Disparo incorreto: Malha sem o cruzador %d!\n", posDesejada);
        }else if(posEncontrada == -1 && resto == 4){
            printf("Disparo incorreto: Malha sem a fragata %d!\n", posDesejada);
        }else if(posEncontrada == -1 && resto == 5){
            printf("Disparo incorreto: Malha sem o submarino %d!\n", posDesejada);
        }

    } else if (posDesejada == posEncontrada) {
         int resto = posEncontrada % 10;

        if(resto == 1) {
            printf("Disparo certeiro: O porta aviões %d afundou!\n", posEncontrada);
        }else if (resto == 2) {
            printf("Disparo certeiro: O encouraçado %d afundou!\n", posEncontrada);
        }else if (resto == 3) {
            printf("Disparo certeiro: O cruzador %d afundou!\n", posEncontrada);
        }else if (resto == 4) {
            printf("Disparo certeiro: A fragata %d afundou!\n", posEncontrada);
        }else if (resto == 5) {
            printf("Disparo certeiro: O submarino %d afundou!\n", posEncontrada);
        }
    }
}
