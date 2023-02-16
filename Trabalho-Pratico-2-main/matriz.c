#include "matriz.h"

#include <stdlib.h>
#include <stdio.h>


void CriaMatriz(Matriz *m){
    //Cria uma cabeça e faz a cauda apontar para ela
    m->cabeca = (Celula *)malloc(sizeof(Celula));
    m->cauda = m->cabeca;
    m->cabeca->prox = m->cabeca;
    m->cabeca->baixo = m->cabeca;
    
    // valores de linhas e colunas
    //printf("\nDigite o numero de linhas e colunas da matriz: ");
    
    // cria as celulas da coluna
    for (int i = 0; i < m->m_col; i++) {
        m->cauda->prox = (Celula *)calloc(1, sizeof(Celula));
        m->cauda = m->cauda->prox;
        m->cauda->prox = m->cabeca;
        m->cauda->baixo = m->cauda;
        m->cauda->col_pos = -1;
    }
    
    // cria as celulas da linha
    m->cauda = m->cabeca;
    for (int i = 0; i < m->m_row; i++) {
        m->cauda->baixo = (Celula *)calloc(1, sizeof(Celula));
        m->cauda = m->cauda->baixo;
        m->cauda->baixo = m->cabeca;
        m->cauda->prox = m->cauda;
        m->cauda->row_pos = -1;
    }
}

void LeValores(Matriz *m){ 
    // ler um valor de linha coluna e valor e adicionar na matriz na posição correta
    int linha, coluna, valor, nElements;
    //printf("\nDigite o numero de elementos da matriz: ");
    scanf("%d", &nElements);
    do {// ler os valores e criar as celulas
        //printf("\nDigite a linha coluna e valor: ");
        scanf("%d %d %d", &linha, &coluna, &valor);
        InsereCelula(m, linha, coluna, valor);
        nElements--;
    } while (nElements > 0);
}
void InsereCelula(Matriz* m, int row, int col, int valor){
        // cria uma celula
        Celula *nova = (Celula *)malloc(sizeof(Celula));
        nova->item.numero = valor;
        nova->row_pos = row;
        nova->col_pos = col;
        
        // INSERIR CELULA
        // percorre a linha
        Celula *aux = m->cabeca;
        Celula *aux2;
        for (int i = 0; i < row; i++) {
            aux = aux->baixo;
        }
        // achar a posiçao da coluna
        aux2 = aux;
        while (aux != aux2->prox) {
            aux2 = aux2->prox;
        }
        aux2->prox = nova;
        nova->prox = aux;
        // percorre a coluna
        aux = m->cabeca;
        for (int i= 0; i < col; i++) {
            aux = aux->prox;
        }
        // achar a posiçao da linha
        aux2 = aux;
        while (aux != aux2->baixo) {
            aux2 = aux2->baixo;
        }
        aux2->baixo = nova;
        nova->baixo = aux;
        // FIM INSERIR CELULA
}

void LiberaMemoria(Matriz *m){
    int i, j;
    Celula *aux = m->cabeca->baixo;
    Celula *aux2 = aux->prox;
    //percorrer a matriz esparsa e liberar a memoria
    for(i = 1; i <= m->m_row; i++){
        for(j = 1; j <= m->m_col; j++){
            if(aux->prox->row_pos == i && aux->prox->col_pos == j){
                aux2 = aux->prox;
                aux->prox = aux->prox->prox;
                free(aux2);
            }
        }
        aux = aux->baixo;
    }
    aux = m->cabeca->prox;
    for(i = 1; i <= m->m_col; i++){
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    aux = m->cabeca->baixo;
    for(i = 1; i <= m->m_row; i++){
        aux2 = aux;
        aux = aux->baixo;
        free(aux2);
    }
    free(m->cabeca);
}

void ImprimeMatrizEsparsa(Matriz *m){
    int i, j;
    Celula *aux = m->cabeca->baixo;
    Celula *aux2 = aux->prox;
    for(i = 1; i <= m->m_row; i++){
        for(j = 1; j <= m->m_col; j++){
            if(aux2->row_pos == i && aux2->col_pos == j){
                printf("%d ", aux2->item.numero);
                aux2 = aux2->prox;
            }else{
                printf("0 ");
            }
        }
        printf("\n");
        aux = aux->baixo;
        aux2 = aux->prox;
    }
}

void MatrizTransposta(Matriz *m){
    int i, j;
    Matriz t;
    t.m_col = m->m_row;
    t.m_row = m->m_col;
    CriaMatriz(&t);
    // passar valores da matriz m para matriz tranposta
    Celula *aux = m->cabeca->prox;
    Celula *aux2 = aux->baixo;
    for(i = 1; i <= m->m_col; i++){
        for(j = 1; j <= m->m_row; j++){
            if(aux2->row_pos == j && aux2->col_pos == i){
                InsereCelula(&t, i, j, aux2->item.numero);
                aux2 = aux2->baixo;
            }
        }
        aux = aux->prox;
        aux2 = aux->baixo;
    }
    ImprimeMatrizEsparsa(&t);
    LiberaMemoria(&t);
}

Matriz SomaMatriz(Matriz *a, Matriz *b){
    int i, j, soma;
    Celula *cA, *cB;
    Matriz c;
    c.m_col = a->m_col;
    c.m_row = a->m_row;
    CriaMatriz(&c);
    cA = a->cabeca->baixo;
    cB = b->cabeca->baixo;
    for (i = 1; i <= a->m_row; i++){
        for(j = 1; j <= a->m_col; j++){
            if(cA->prox->col_pos == j && cB->prox->col_pos == j){
                soma = cA->prox->item.numero + cB->prox->item.numero;
                if (soma)
                    InsereCelula(&c, i, j, soma);
                cA = cA->prox;
                cB = cB->prox;
            }
            else if(cA->prox->col_pos == j){
                InsereCelula(&c, i, j, cA->prox->item.numero);
                cA = cA->prox;
            }
            else if(cB->prox->col_pos == j){
                InsereCelula(&c, i, j, cB->prox->item.numero);
                cB = cB->prox;
            }
        }
        cA = cA->prox->baixo;
        cB = cB->prox->baixo;
    }
    return c;
}

Matriz MultiplicaMatriz(Matriz *a, Matriz *b){
    int i, j, k, soma;
    //cria c e atribui os valores de linha e coluna
    Matriz c;
    c.m_row = a->m_row;
    c.m_col = b->m_col;
    CriaMatriz(&c);
    //multiplicação
    for(i = 1; i <= a->m_row; i++){
        for(j = 1; j <= b->m_col; j++){
            soma = 0;
            for(k = 1; k <= a->m_col; k++){
                soma += PegaElemento(a, i, k) * PegaElemento(b, k, j);
            }
            if(soma != 0)
                InsereCelula(&c, i, j, soma);
        }
    }
    return c;
}


int PegaElemento(Matriz *m, int row, int col){
    Celula *aux = m->cabeca->prox;
    for (int i = 0; i < col -1; i++)
        aux = aux->prox;
    Celula *aux2 = aux;
    do{
        aux = aux->baixo;
        if (aux->row_pos == row)
            return aux->item.numero;
    }while (aux != aux2);

    return 0;
}