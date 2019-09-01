#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

int main () {
	printf("Oi.\n");
	MATRIZ_ESPARSA *matriz = criar_matriz(2, 2);
	for (int i = 1; i <= 2; i++)
		for (int j = 1; j <= 2; j++)
			set_valor(matriz, i, j, (double) i + j);
	printf("endereço matriz: %ld\n", matriz);
	printf("%d %d\n", matriz->nr_colunas, matriz->nr_linhas);
	print_matriz(matriz);
	return 0;
}
