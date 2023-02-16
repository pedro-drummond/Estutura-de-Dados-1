#include <stdlib.h>
#include <stdio.h>
#include "matriz.h"


int main(){
    int row, col, n, aux;
    char op;
    Matriz a, b;
    scanf("%d %c", &n, &op);
    switch (op)
    {
    case 'T':
        scanf("%d %d", &a.m_row, &a.m_col); // ler a linha e a coluna
        CriaMatriz(&a); // cria a moldura da matriz
        LeValores(&a); // le o numero de elementos e insere na matriz
        MatrizTransposta(&a);
        break;
    case 'S':
        // soma n matrizes
        aux = 0;
         // tem um problema aqui, preciso saber o valor de row col antes de criar a matriz b q vai receber o valor da soma
        while (n > 0){
            scanf("%d %d", &a.m_row, &a.m_col);
            b.m_col =  a.m_col;
            b.m_row = a.m_row;
            if (aux == 0){
                CriaMatriz(&b);
                aux++;
            }            
            CriaMatriz(&a);
            LeValores(&a);
            b = SomaMatriz(&a, &b);
            n--;
        }
        ImprimeMatrizEsparsa(&b);
        LiberaMemoria(&a);
        LiberaMemoria(&b);
        break;
    case 'M':
        aux = 0;
        scanf("%d %d", &a.m_row, &a.m_col);
        CriaMatriz(&a);
        LeValores(&a);
        while (n > 1){
            scanf("%d %d", &b.m_row, &b.m_col);
            CriaMatriz(&b);
            LeValores(&b);
            a = MultiplicaMatriz(&a, &b);
            n--;
        }
        LiberaMemoria(&b);
        ImprimeMatrizEsparsa(&a);
        LiberaMemoria(&a);

        break;
    }
    //MatrizTransposta(a, row, col);
    return 0;
}