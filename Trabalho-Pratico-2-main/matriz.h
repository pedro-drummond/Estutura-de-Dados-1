#ifndef matriz_h
#define matriz_h

typedef struct{
    int numero;
} Item;

typedef struct celula{
    struct celula *prox;
    struct celula *baixo;
    int row_pos;
    int col_pos;
    Item item;
}Celula;

typedef struct {
    Celula *cabeca;
    Celula *cauda;
    int m_row, m_col;
} Matriz;

void CriaMatriz(Matriz*);

void ImprimeMatrizEsparsa(Matriz*);

void LiberaMemoria(Matriz*);

void MatrizTransposta(Matriz*);

void InsereCelula(Matriz*, int, int, int);

void LeValores(Matriz *);

Matriz SomaMatriz(Matriz*, Matriz *);

Matriz MultiplicaMatriz(Matriz*, Matriz *);

int PegaElemento(Matriz *, int, int);


#endif // lista_h