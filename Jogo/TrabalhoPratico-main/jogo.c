#include <stdio.h>
#include <stdlib.h>
#include "jogo.h"

struct tabuleiro
{
    char **TabuleiroJogo;
    int quantX;
    int quantO;
    int quantV;
};

TADTabuleiro *inicializaTabuleiro(int tam)
{
    TADTabuleiro *tab = (TADTabuleiro *)malloc(sizeof(TADTabuleiro));
    tab->TabuleiroJogo = malloc(tam * sizeof(int *));

    for (int i = 0; i < tam; ++i)
    {
        tab->TabuleiroJogo[i] = malloc(tam * sizeof(int));
    }

    return tab;
}
void liberaTabuleiro(TADTabuleiro **Tabuleiro, int tam)
{
    for (int i = 0; i < tam; i++)
        free(((*Tabuleiro)->TabuleiroJogo)[i]);
    free((*Tabuleiro)->TabuleiroJogo);
}

void liberaTadTabuleiro(TADTabuleiro *tab)
{
    free(tab);
}

void entrada(char jogo[9], TADTabuleiro **tab)
{
    // Lendo o Vetor com Jogadas
    scanf("%s", jogo);
    // Transpondo Vetor Para Matriz
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            (*tab)->TabuleiroJogo[i][j] = jogo[i * 3 + j];
        }
    }
}

int validar(TADTabuleiro *Tabuleiro, char *jogo)
{
    Tabuleiro->quantO = 0;
    Tabuleiro->quantX = 0;
    Tabuleiro->quantV = 0;
    int diferenca;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++){
            if(Tabuleiro->TabuleiroJogo[i][j] == 'X')
                Tabuleiro->quantX++;
            else if(Tabuleiro->TabuleiroJogo[i][j] == 'O')
                Tabuleiro->quantO++; 
            else if(Tabuleiro->TabuleiroJogo[i][j] == 'V')
                Tabuleiro->quantV++;
        }
    } 
    //diferença de quantidade de X e O
    diferenca = abs( Tabuleiro->quantX - Tabuleiro->quantO );
    //se a diferença for maior que 1, não é possível ganhar
    if( diferenca > 1 || Tabuleiro->quantV + Tabuleiro->quantX + Tabuleiro->quantO != 9)
        return 1;
    else
        return 0;
    //VALIDANDO VITORIAS
    int vitorias[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int vx = 0, vy = 0;
    //verificar vitoria
    for (int i = 0; i < 8; i++){
        if(jogo[vitorias[i][0]] != 'V' && jogo[vitorias[i][0]] == jogo[vitorias[i][1]] && jogo[vitorias[i][0]] == jogo[vitorias[i][2]]){
            if(jogo[vitorias[i][0]] == 'X')
                vx++;
            else
                vy++;
        }
    }
    if (vx > 0 && vy == 0)
        return 1;
    else
        return 0;
    return 0; 
}

int vitoria(TADTabuleiro *tab)
{
    // 0 : invalido
    // 1 : vitoria X
    // 2 : vitoria O
    // 3 : velha
    // 4 : n acabou
    int cx = 0;
    int co = 0;
    for (int i = 0; i < 3; i++)
    {
        if (tab->TabuleiroJogo[i][0] == tab->TabuleiroJogo[i][1] && tab->TabuleiroJogo[i][1] == tab->TabuleiroJogo[i][2] && tab->TabuleiroJogo[i][0] != 'V')
        {
            if (tab->TabuleiroJogo[i][0] == 'X')
                cx++;
            else
                co++;
        }
    }
    // Game over - col
    for (int j = 0; j < 3; j++)
    {
        if (tab->TabuleiroJogo[0][j] == tab->TabuleiroJogo[1][j] && tab->TabuleiroJogo[1][j] == tab->TabuleiroJogo[2][j] && tab->TabuleiroJogo[0][j] != 'V')
        {
            if (tab->TabuleiroJogo[0][j] == 'X')
                cx++;
            else
                co++;
        }
    }
    // game over - diagonal
    if (tab->TabuleiroJogo[0][0] == tab->TabuleiroJogo[1][1] && tab->TabuleiroJogo[1][1] == tab->TabuleiroJogo[2][2] && tab->TabuleiroJogo[0][0] != 'V')
    {
        if (tab->TabuleiroJogo[0][0] == 'X')
            cx++;
        else
            co++;
    }

    // game over - diagonal secundária
    if (tab->TabuleiroJogo[0][2] == tab->TabuleiroJogo[1][1] && tab->TabuleiroJogo[1][1] == tab->TabuleiroJogo[2][0] && tab->TabuleiroJogo[2][0] != 'V')
    {
        if (tab->TabuleiroJogo[0][2] == 'X')
            cx++;
        else
            co++;
    }

    if (cx > 0 && co > 0)
        return 0;
    else if (cx > 0 && co == 0)
        return 1;
    else if (co > 0 && cx == 0)
        return 2;

    // game over - empate
    int e = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (tab->TabuleiroJogo[i][j] == 'V')
                e++;
        }
    }
    if (e == 0)
        return 3;
    // game over - o jogo não acabou
    return 4;
}

void analisar(char jogo[9], int contador, TADTabuleiro *Tab)
{
    int vit = vitoria(Tab);
    // 0 : invalido
    // 1 : vitoria X
    // 2 : vitoria O
    // 3 : velha
    // 4 : n acabou
    switch (vit)
    {
    case 1:
        printf("Tabuleiro %d com vitoria [X]\n", contador);
        break;
    case 2:
        printf("Tabuleiro %d com vitoria [O]\n", contador);
        break;
    case 3:
        printf("Tabuleiro %d deu velha\n", contador);
        break;
    case 0:
        printf("Tabuleiro %d invalido\n", contador);
        break;
    case 4:
        // para jogador indefinido x = o
        mestre(Tab, contador);
        break;
    }
}
void mestre(TADTabuleiro *Tab,int contador){
    printf("Tabuleiro %d em andamento ", contador);
    //declaração das variaveis
    int cont = 0,espaco = 0, lesp = 0, rowsp = 0, colsp = 0, row = 0;
    int winrow[3], wincol[3];
    char jogador;

    if(Tab->quantX == Tab->quantO)
        printf("[proximo jogador indefinido]\n"); 
    else if(Tab->quantV  > 0){
        
        if(Tab->quantO > Tab->quantX)
            jogador='X';
        else if(Tab->quantX > Tab->quantO)
                jogador='O';
        for(int i=0;i<3;i++){
            int cont=0,espaco=0,colsp=0;
            for(int j=0;j<3;j++){
                if(Tab->TabuleiroJogo[i][j] == jogador)
                    cont++;
                else if(Tab->TabuleiroJogo[i][j] == 'V'){
                        espaco=1;
                        colsp=j;
                }        
            }
            if(cont == 2 && espaco == 1){
                winrow[row]=i;
                wincol[row]=colsp;
                row++;
            }
        }
        for(int i=0;i<3;i++){
            int cont=0,espaco=0,rowsp=0;
            for(int j=0;j<3;j++){
                if(Tab->TabuleiroJogo[j][i] == jogador)
                    cont++;
                else if(Tab->TabuleiroJogo[j][i]=='V'){
                        espaco=1;
                        rowsp=j;
                }        
            }
            if(cont == 2 && espaco == 1){
                winrow[row]=rowsp;
                wincol[row]=i;
                row++;
            }
        }
        for(int i=0;i<3;i++){
            if(Tab->TabuleiroJogo[i][i] == jogador)
                cont++;
            else if(Tab->TabuleiroJogo[i][i]=='V'){
                    espaco=1;
                    lesp=i;
            }
        }
        if(cont == 2 && espaco == 1){
                winrow[row]=lesp;
                wincol[row]=lesp;
                row++;
            }
        // zerando contador
        cont = 0,espaco = 0;
        for(int i = 0;i < 3; i++){
            if(Tab->TabuleiroJogo[i][2-i] == jogador)
                cont++;
            else if(Tab->TabuleiroJogo[i][2-i]=='V'){
                    espaco=1;
                    rowsp=i;
                    colsp=2-i;
            }
        }
        if(cont == 2 && espaco == 1){
                winrow[row]=rowsp;
                wincol[row]=colsp;
                row++;
            }
        //prints
        if(row == 1)
            printf("[%c: (%d,%d)]\n",jogador,winrow[0]+1,wincol[0]+1);   
        else if(row == 2)
                printf("[%c: (%d,%d)(%d,%d)]\n",jogador,winrow[0]+1,wincol[0]+1,winrow[1]+1,wincol[1]+1);  
        else if(row == 3)
                printf("[%c: (%d,%d)(%d,%d)(%d,%d)]\n",jogador,winrow[0]+1,wincol[0]+1,winrow[1]+1,wincol[1]+1,winrow[2]+1,wincol[2]+1);  
        else
            printf("[%c: sem jogada mestre]\n",jogador);
    }
}