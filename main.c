#include <stdio.h>
#include <stdlib.h>
#include "matriz_esparsa.h"

int main () {
	printf("Oi.\n");
	MATRIZ_ESPARSA *matriz = criar_matriz(2, 2);
	printf("endereço matriz: %d\n", matriz);
	printf("%d %d\n", matriz->nr_colunas, matriz->nr_linhas);
	return 0;
}
