#ifndef MATRIZ_ESPARSA_H
#define MATRIZ_ESPARSA_H

typedef struct particula {
    int linha;
    int coluna;
    double valor;
    struct particula *prox_linha;
    struct particula *prox_coluna;
} NO;
 
typedef struct matriz {
    NO *inicio;
    int nr_linhas;
    int nr_colunas;
} MATRIZ_ESPARSA ;



MATRIZ_ESPARSA *criar_matriz (int nr_linhas, int nr_colunas);  //FUNCIONANDO
void apagar_matriz (MATRIZ_ESPARSA *matriz);  //FUNCIONANDO

int set_valor (MATRIZ_ESPARSA *matriz, int linha, int coluna, double valor);  //FUNCIONANDO
double get_valor (MATRIZ_ESPARSA *matriz, int linha, int coluna);  //FUNCIONANDO
void print_valor (MATRIZ_ESPARSA *matriz, int linha, int coluna);  //FUNCIONANDO  

MATRIZ_ESPARSA *somar_matriz (MATRIZ_ESPARSA *s1, MATRIZ_ESPARSA *s2);  //FUNCIONANDO
MATRIZ_ESPARSA *multiplicar_matriz (MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2);
double soma_mult(int linha, int coluna, MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2); 
double *vectorify(MATRIZ_ESPARSA *matriz, int linha, int coluna);
double soma_vetor(double *vetor, int tamanho);
MATRIZ_ESPARSA *transposta_matriz (MATRIZ_ESPARSA *matriz);  //FUNCIONANDO
double determinante_matriz (MATRIZ_ESPARSA *matriz);  //FUNCIONANDO ateh ordem 4

void print_matriz (MATRIZ_ESPARSA *matriz);  //FUNCIONANDO
void resumo_matriz (MATRIZ_ESPARSA *matriz);  //FUNCIONANDO

#endif
