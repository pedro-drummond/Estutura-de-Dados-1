#include <stdlib.h>
#include <stdio.h>
#include "buscabinaria.h"

int main(){
    int casos, malhas, posDesejada, alvo, aux, posEncontrada = -1;
    TDicionario dicionario;

    scanf("%d %d", &casos, &malhas);

    TDicionario_Inicia(&dicionario, malhas);
    //printf("Dicionario inicializado\n");

    for (int i = 0; i < casos; i++){
        dicionario.cont = 0;
        lerMalhas(malhas, &dicionario, &posDesejada, &alvo);
        //printf("chequei malhas\n");
        aux = CheckPos(&dicionario, posDesejada, alvo); //checa se o jogador acertou o alvo
            if(aux >= 0){ // se acertou
                exibeResultado(alvo, alvo, dicionario.cont); //problema - arrumar
                continue;
            }else{ // se errou
                posEncontrada = TDicionario_find(&dicionario, alvo);
                exibeResultado(alvo, posEncontrada, dicionario.cont);
            }
        //se não acertou procura o alvo
        //posEncontrada = TDicionario_find(&dicionario, alvo, posDesejada, aux);
        //printf("encontrei\n");
        //exibeResultado(posDesejada, posEncontrada);
    }
    LiberaMemoria(&dicionario);
    return 0;
}