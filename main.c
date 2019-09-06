#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

int main () {
	printf("Oi.\n");
	MATRIZ_ESPARSA *matriz = criar_matriz(3, 3);
	for (int i = 1; i <= 3; i++)
		for (int j = 1; j <= 3; j++)
			set_valor(matriz, i, j, (double) i + j);
	printf("endereço matriz: %ld\n", matriz);
	printf("%d %d\n", matriz->nr_colunas, matriz->nr_linhas);
	//set_valor(matriz, 2, 2, 7.000);
	print_matriz(matriz);
	//resumo_matriz(matriz);
	MATRIZ_ESPARSA *matriz1 = matriz;
	MATRIZ_ESPARSA *matriz2 = multiplicar_matriz(matriz1, matriz);
	print_matriz(matriz2);
	apagar_matriz(matriz);
	return 0;
}
