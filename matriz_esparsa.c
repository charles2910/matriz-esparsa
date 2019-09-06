#include "matriz_esparsa.h"
#include <stdio.h>
#include <stdlib.h>

/* 
 * Inicializa um novo elemento (estrutura NO) da matriz com valores "zerados".
 * @return ponteiro para Nó
 */
NO *criar_no() {
	NO *novo = (NO *) malloc (sizeof (NO));
	if(novo != NULL) {
		novo->linha = -1;
		novo->coluna = -1;
		novo->valor = 0.0;
		novo->prox_coluna = NULL;
		novo->prox_linha = NULL;
		return novo;
	} else {
		return NULL;
	}
}

/* 
 * Inicializa o ponteiro (estrutura MATRIZ_ESPARSA) para a matriz com valores "zerados".
 * @return ponteiro para matriz
 */
MATRIZ_ESPARSA *iniciar_matriz() {
	MATRIZ_ESPARSA *novo = (MATRIZ_ESPARSA *) malloc (sizeof (MATRIZ_ESPARSA));
	if(novo != NULL) {
		novo->nr_linhas = -1;
		novo->nr_colunas = -1;
		novo->inicio = NULL;
		return novo;
	} else {
		return NULL;
	}
}

/* 
 * Iniciliza um  nova matriz esparsa de nr_linhas e nr_colunas.
 * @return ponteiro para matriz
 */
MATRIZ_ESPARSA *criar_matriz(int nr_linhas, int nr_colunas) //NOVO CODIGO
{
    NO 	*proximaLinha = NULL, 
		*proximaColuna = NULL;  				//guardarao endereco do ultimo noh criado

    for(int i = nr_linhas; i >= 1; i--) { 		//criar os indicadores de posicao de linha da ultima linha para a primeira
        NO *matriz = criar_no();
        if(matriz != NULL) {
            matriz->linha = i;
            matriz->prox_linha = proximaLinha;  //recebe endereco do ultimo noh criado q eh a proxima "linha"
            proximaLinha = matriz;  			//torna esta o ultimo noh criado
        }
    }

    for(int j = nr_colunas; j >= 1; j--) { 		//repete o processo anterior, mas agora para colunas  
        NO *matriz = criar_no();  
        if(matriz != NULL) {
            matriz->coluna = j;
            matriz->prox_coluna= proximaColuna;
            proximaColuna = matriz;
        }
    }

    NO *cabeca = criar_no();
    if (cabeca != NULL) { 						//criando o noh cabeca
        cabeca->coluna = 0;
        cabeca->linha = 0;
        cabeca->prox_coluna = proximaColuna;
        cabeca->prox_linha = proximaLinha;
    }

    MATRIZ_ESPARSA *matriz = iniciar_matriz();
    if (matriz != NULL) {
        matriz->inicio = cabeca;
        matriz->nr_colunas = nr_colunas;
        matriz->nr_linhas = nr_linhas;
    }

	if (matriz != NULL)
    	return matriz;  						//retorna o endereco do apontador para o no cabeca
	else
		return NULL;
}

/*
 * Apaga a matriz, liberando toda memória alocada.
 */
void apagar_matriz(MATRIZ_ESPARSA *matriz) {
   	NO 	*proximaColuna = NULL, 
	   	*proximaLinha = NULL;							//armazenarao o endereco das proximas coluna e linha respctivamente
	// TODO: implementar um vetor para guardar elementos da matriz, apagar do vetor, apresenta um comportamento mais estável
   	if (matriz != NULL && matriz->inicio != NULL) {
       	proximaColuna = matriz->inicio;  				//recebe o endereco do noh cabeca
		proximaLinha = proximaColuna->prox_linha;  		//recebe o endereco da primeira linha da primeira coluna

       	do { 											//checa se acabou os indicadores de colunas      	
           	do { 										//checa se acabou as linhas
				if (proximaLinha == NULL)
					break;  
               	proximaLinha = proximaLinha->prox_linha;//aponta para o noh que sera apagado na proxima iteracao
               	free (proximaColuna->prox_linha);  		//libera o noh desta iteracao
				proximaColuna->prox_linha = proximaLinha;//indicador passa a apontar o proximo noh
				   
           	} while (proximaColuna->prox_linha != NULL);
			if (proximaColuna == NULL)
					break;
           	proximaColuna = proximaColuna->prox_coluna;  //faz o processo acima pra colunas
			free (matriz->inicio);  
           	matriz->inicio = proximaColuna;
       	} while (matriz->inicio->prox_coluna != NULL);  
   	}
	free(matriz);
}

int set_valor(MATRIZ_ESPARSA *matriz, int linha, int coluna, double valor) {
    int ind_coluna, ind_linha;  					//indicadores de coluna e linha
   	NO *coluna_atual, *linha_atual;
   	NO *novo_no = (NO *) malloc (sizeof (NO));
	
   	if (matriz->inicio == NULL)
	   return -1;

	coluna_atual = matriz->inicio->prox_coluna;  	//coluna_atual recebe o end. da coluna
	ind_coluna = coluna_atual->coluna;  			//ind_coluna recebe em q coluna coluna_atual esta

	while (coluna != ind_coluna) { 					//procura a coluna correta
		if (coluna_atual->prox_coluna == NULL)  	//gera condicao de saida do laco, mantendo o coluna_atual apontando para ultima coluna
			break;
		coluna_atual = coluna_atual->prox_coluna;  	//pega proxima coluna
		ind_coluna = coluna_atual->coluna;  		//pega numero da coluna
	}
	

	linha_atual = coluna_atual;  					//linha_atual aponta para linha de indicadores da coluna desejada
	ind_linha = linha_atual->linha; 				//indica a linha do noh atual
	if (linha_atual->prox_linha == NULL) { 			//caso nao haja elemento na coluna, executa o if
		novo_no->prox_linha = NULL;
		novo_no->linha = linha;
		novo_no->coluna = coluna;
		novo_no->valor = valor;
		linha_atual->prox_linha = novo_no;
	}
	else {
		while (linha > linha_atual->linha && 
					linha >= linha_atual->prox_linha->linha) { //procura o ponto a inserir o novo noh
			linha_atual = linha_atual->prox_linha;
			ind_linha = linha_atual->linha;
			if (linha_atual->prox_linha == NULL)
			break;
		}
		if (linha == linha_atual->linha) {			//se o noh existir, substitui o valor
			linha_atual->valor = valor;
			return 0;
		}
		else //se nao, iseriremos o novo noh ================================= insercao do novo NOH
		{
		
			novo_no->linha = linha;
			novo_no->coluna = coluna;
			novo_no->valor = valor; 				//novo noh foi criado e seu valor e posicao de linha e coluna ja foram colocados
			novo_no->prox_linha = linha_atual->prox_linha;  //passa a apontar pro proximo noh
			linha_atual->prox_linha = novo_no;  	//noh anterior passa a apontar pra este

			//Agora devemos acertar os ponteiros de coluna, teremos q buscar a linha e inseri-lo:
			int ind_coluna_aux, 
				ind_linha_aux;

			NO 	*linha_atual_aux,
				*coluna_atual_aux;
	
			linha_atual_aux = matriz->inicio->prox_linha;  	//coluna_atual recebe o end. da coluna
			/*ind_linha_aux = linha_atual_aux->linha;  		//ind_coluna recebe em q coluna coluna_atual esta*/
			while (linha != ind_linha_aux) { 				//procura a coluna correta
				if (linha_atual_aux->prox_linha == NULL)	//gera condicao de saida do laco, mantendo o coluna_atual apontando para ultima coluna
					break;
				linha_atual_aux = linha_atual_aux->prox_linha; //pega proxima coluna
				ind_linha_aux = linha_atual_aux->linha;		//pega numero da coluna
			}	
			coluna_atual_aux = linha_atual_aux;  			//linha_atual aponta para linha de indicadores da coluna desejada
			ind_coluna_aux = coluna_atual_aux->coluna; 		//indica a linha do proximo noh
			if (coluna_atual_aux->prox_coluna == NULL) {
				novo_no->prox_coluna = NULL;
				coluna_atual_aux = novo_no;
			}
			else {
				while (coluna > coluna_atual_aux->coluna 
							&& coluna >= coluna_atual_aux->prox_coluna->coluna) { //procura o ponto a inserir o novo noh
					if (coluna_atual_aux->prox_linha == NULL)
						break;   
					coluna_atual_aux = coluna_atual_aux->prox_coluna;
					ind_coluna_aux = coluna_atual_aux->prox_coluna->coluna;
					if (coluna_atual_aux->prox_linha == NULL)
						break;
				}
				novo_no->prox_coluna = coluna_atual_aux->prox_coluna;
				coluna_atual->prox_coluna = novo_no;
			}
		}
	}
	return 1;
}


double get_valor(MATRIZ_ESPARSA *matriz, int linha, int coluna) {
	NO 	*paux, 
		*coluna_atual, 
		*linha_atual;

	int ind_coluna, 
		ind_linha;

	if( coluna  > matriz->nr_colunas || linha  > matriz->nr_linhas){
		printf("Numero de linha e/ou coluna invalido(s)");
		return -1;
	}

	paux = matriz->inicio->prox_linha;
	coluna_atual = matriz->inicio->prox_coluna;  	//coluna_atual recebe o end. da coluna
	ind_coluna = coluna_atual->coluna;

	while (coluna != ind_coluna) { 					//procura a coluna correta
		if (coluna_atual->prox_coluna == NULL)  	//gera condicao de saida do laco, mantendo o coluna_atual apontando para ultima coluna
			break;
		coluna_atual = coluna_atual->prox_coluna;  	//pega proxima coluna
		ind_coluna = coluna_atual->coluna;  		//pega numero da coluna
	}

	linha_atual = coluna_atual;  					//linha_atual aponta para linha de indicadores da coluna desejada
	ind_linha = linha_atual->linha; 				//indica a linha do noh atual

	while ((linha > ind_linha) && (linha >= linha_atual->prox_linha->linha)) { //procura a linha correta 
		linha_atual = linha_atual->prox_linha;
	 	ind_linha = linha_atual->linha;
	 	if (linha_atual->prox_linha == NULL)
			break;
	}

	if (linha == ind_linha) 						//se o noh existir, pega o valor
		return linha_atual->valor;
	else  											//se nao existir, retorna 0
		return 0.0000;
}


void print_valor(MATRIZ_ESPARSA *matriz, int linha, int coluna) {
	double valor;
	valor = get_valor (matriz, linha, coluna);
	printf ("%.2lf \n", valor);
}



MATRIZ_ESPARSA *somar_matriz(MATRIZ_ESPARSA *s1, MATRIZ_ESPARSA *s2) {
	
	if(s1->nr_linhas != s2->nr_linhas || s1->nr_colunas != s2->nr_colunas ) { 	// para somar deve ter msmo nmero de linhas e colunas
		printf("As matrizes devem ter o mesmo numero de linhas e colunas");
		return 0;
	}
	else {
		MATRIZ_ESPARSA *s3= criar_matriz(s1->nr_linhas, s2->nr_colunas); 		// cria a matriz que surge da soma
		double aux;
		
		for(int i = 1; i <= s3->nr_linhas; i++) { 								// imprime a matriz
			for(int j = 1; j <= s3->nr_colunas; j++) {
				aux = get_valor(s1, i, j) + get_valor(s2, i, j);
				if (aux != 0)
					set_valor(s3, i, j, aux);	 
			}
		}  
		return s3;	
	}
}


/*
 * Transforma uma linha ou coluna da matriz esparsa em um vetor, retornando 
 * este vetor criado.
 */
double *vectorify(MATRIZ_ESPARSA *matriz, int linha, int coluna) {
	if (matriz == NULL)	
		return NULL;
	double *vetor;
	if (linha == 0) {
		vetor = calloc(sizeof(double), matriz->nr_linhas);
		for (int i = 0; i < matriz->nr_linhas; i++)
			vetor[i] = get_valor(matriz, i + 1, coluna);
	} else {
		vetor = calloc(sizeof(double), matriz->nr_colunas);
		for (int j = 0; j < matriz->nr_colunas; j++)
			vetor[j] = get_valor(matriz, linha, j + 1);
	}
	return vetor;
}


/*
 * Efetua a soma de todos os valores de um vetor, retornando-o.
 */
double soma_vetor(double *vetor, int tamanho) {
	if (vetor == NULL)
		return -1;
	double soma = 0;
	for (int i = 0; i < tamanho; i++)
		soma += vetor[i];
	return soma;
}


/* 
 * Faz a soma final entre os elementos multiplicados de linha por coluna, 
 * retornando o valor final do elemento da matiz já multiplicada.
 */
double soma_mult(int linha, int coluna, MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2)
{
	double *col = vectorify(m1, 0, coluna);
	double *lin = vectorify(m2, linha, 0);
	for (int i = 0; i < m1->nr_colunas; i++)
		lin[i] = lin[i] * col[i];
	double soma = soma_vetor(lin, m1->nr_colunas);
	free(lin);
	free(col);
	return soma;
}


MATRIZ_ESPARSA *multiplicar_matriz (MATRIZ_ESPARSA *m1, MATRIZ_ESPARSA *m2){
	if(m1->nr_colunas != m2->nr_linhas){
		printf("ERRO: números de colunas e linhas das matrizes não coicidem.\n");
		return NULL;
	}

	MATRIZ_ESPARSA *m3 = criar_matriz(m1->nr_linhas, m2->nr_colunas); // cria a matriz q sera gereda pel multiplicaçao	
	
	for(int j = 0; j < m2->nr_colunas; j++) {  
		for(int i = 0; i < m1->nr_linhas; i++) {
			
			double v = soma_mult (i + 1, j + 1, m1, m2);
			set_valor(m3, i + 1, j + 1, v);
		}
	}
	return m3;
}




MATRIZ_ESPARSA *transposta_matriz(MATRIZ_ESPARSA *matriz) {
	MATRIZ_ESPARSA *t = criar_matriz(matriz->nr_colunas, matriz->nr_linhas);
	double aux;

	for(int i = 1; i <= matriz->nr_linhas; i++) {
		for(int j = 1; j <= matriz->nr_colunas; j++) {
			aux = get_valor(matriz, i, j);
			if (aux != 0)
				set_valor(t, j, i, aux);	 
		}
	}  
	return t;
}




double determinante_matriz(MATRIZ_ESPARSA *matriz) {
	if (matriz->nr_colunas == matriz->nr_linhas)  //checa se a matriz eh quadrada
	{
		int m_imp[matriz->nr_linhas][matriz->nr_colunas];  //criaremos a matriz em memoria para facilitar o calculo (espera-se q ela caiba na memoria)
		for(int i = 0; i < matriz->nr_linhas; i++){  // crio uma matriz com o numero de linhas e colunas inicialmente dadas
			for(int j = 0; j < matriz->nr_colunas; j++){
				m_imp[i][j]=0 ; // zero toda a matriz e posteriormente substiruiremos os valores da matris os quais sao diferentes de zero
			}
		}
		   
		for(int i = 0; i < matriz->nr_linhas; i++){  // crio uma matriz com o numero de linhas e colunas inicialmente dadas
			for(int j = 0; j < matriz->nr_colunas; j++){
				m_imp[i][j] = get_valor (matriz, i + 1, j + 1) ; // substitui os valores da matriz que sao diferentes de zero
			}
		}

		if (matriz->nr_colunas == 2)  //calcula o determinante de ordem 2
		{
			double det = 0.0;

			det = m_imp[0][0]*m_imp[1][1] - m_imp[0][1]*m_imp[1][0];
			printf ("O valor do determinante eh: %.4lf\n", det);
			return det;
		}

		if (matriz->nr_colunas == 3)  //calcula o determinante de matriz de ordem 3
		{
			double det = 0.0;

			det = (m_imp[0][0]*m_imp[1][1]*m_imp[2][2] + m_imp[0][1]*m_imp[1][2]*m_imp[2][0] + m_imp[0][2]*m_imp[1][0]*m_imp[2][1]) 
			- (m_imp[0][2]*m_imp[1][1]*m_imp[2][0] + m_imp[0][0]*m_imp[1][2]*m_imp[2][1] + m_imp[0][1]*m_imp[1][0]*m_imp[2][2]);
			printf ("O valor do determinante eh: %.4lf\n", det);
			return det;
		}
		if (matriz->nr_colunas == 4)  //calcula o determinante da matriz de ordem 4
		{
			double det = 0.0, det00 = 0.0, det01 = 0.0, det02 = 0.0, det03 = 0.0;

			det00 = m_imp[0][0] * ((m_imp[1][1]*m_imp[2][2]*m_imp[3][3] + m_imp[1][2]*m_imp[2][3]*m_imp[3][1] + m_imp[1][3]*m_imp[2][1]*m_imp[3][2]) 
			- (m_imp[1][3]*m_imp[2][2]*m_imp[3][1] + m_imp[1][1]*m_imp[2][3]*m_imp[3][2] + m_imp[1][2]*m_imp[2][1]*m_imp[3][3]));
			
			det01 = m_imp[0][1] * ((m_imp[1][0]*m_imp[2][2]*m_imp[3][3] + m_imp[1][2]*m_imp[2][3]*m_imp[3][0] + m_imp[1][3]*m_imp[2][0]*m_imp[3][2]) 
			- (m_imp[1][3]*m_imp[2][2]*m_imp[3][0] + m_imp[1][0]*m_imp[2][3]*m_imp[3][2] + m_imp[1][2]*m_imp[2][0]*m_imp[3][3]));

			det02 = m_imp[0][2] * ((m_imp[1][0]*m_imp[2][1]*m_imp[3][3] + m_imp[1][1]*m_imp[2][3]*m_imp[3][0] + m_imp[1][3]*m_imp[2][0]*m_imp[3][1]) 
			- (m_imp[1][3]*m_imp[2][1]*m_imp[3][0] + m_imp[1][0]*m_imp[2][3]*m_imp[3][1] + m_imp[1][1]*m_imp[2][0]*m_imp[3][3]));

			det03 = m_imp[0][3] * ((m_imp[1][0]*m_imp[2][1]*m_imp[3][2] + m_imp[1][1]*m_imp[2][2]*m_imp[3][0] + m_imp[1][2]*m_imp[2][0]*m_imp[3][1]) 
			- (m_imp[1][2]*m_imp[2][1]*m_imp[3][0] + m_imp[1][0]*m_imp[2][2]*m_imp[3][1] + m_imp[1][1]*m_imp[2][0]*m_imp[3][2]));

			det = det00 - det01 + det02 - det03;
			printf ("%.4lf \n", det);
			return det;
		} 
	}
	return -1; //deu ruim!
}

void print_matriz(MATRIZ_ESPARSA *matriz) {
	double m_imp[matriz->nr_linhas][matriz->nr_colunas];
	
	for(int i = 0; i < matriz->nr_linhas; i++) {  // crio uma matriz com o numero de linhas e colunas inicialmente dadas
		for(int j = 0; j < matriz->nr_colunas; j++) {
			m_imp[i][j]=0 ; // zero toda a matriz e posteriormente substiruiremos os valores da matris os quais sao diferentes de zero
		}
	}
	   
	for(int i = 0; i < matriz->nr_linhas; i++) {  // crio uma matriz com o numero de linhas e colunas inicialmente dadas
		for(int j = 0; j < matriz->nr_colunas; j++) {
			m_imp[i][j] = get_valor (matriz, i + 1, j + 1) ; // substitui os valores da matriz que sao diferentes de zero
		}
	}
	
   	for(int i = 0; i < matriz->nr_linhas; i++) {  // imprime a matriz
		for(int j = 0; j < matriz->nr_colunas; j++) {
			printf("%.2lf ",m_imp[i][j]) ;
		}
		printf("\n");
	}  
}


void resumo_matriz(MATRIZ_ESPARSA *matriz) {
	double m_imp[matriz->nr_linhas][matriz->nr_colunas];

	for(int i = 0; i < matriz->nr_linhas; i++) {  				// crio uma matriz com o numero de linhas e colunas inicialmente dadas
		for(int j = 0; j < matriz->nr_colunas; j++) {
			m_imp[i][j]=0 ; 									// zero toda a matriz e posteriormente substiruiremos os valores da matris os quais sao diferentes de zero
		}
	}
	
	for(int i = 0; i < matriz->nr_linhas; i++) {  				// crio uma matriz com o numero de linhas e colunas inicialmente dadas
		for(int j = 0; j < matriz->nr_colunas; j++) {
			m_imp[i][j] = get_valor (matriz, i + 1, j + 1) ; 	// substitui os valores da matriz que sao diferentes de zero
		}
	}
	
	for(int i = 0; i < matriz->nr_linhas; i++) {  				// imprime a matriz
		for(int j = 0; j < matriz->nr_colunas; j++) {
			if (m_imp[i][j]!= 0.0){
				printf("linha:%d coluna:%d valor:%lf \n", i+1, j+1, m_imp[i][j]);
			}
		}
		printf("\n");
	}  

}


MATRIZ_ESPARSA *ler_matriz(const char nome[]) {
	FILE *p = NULL;
	int tam[4];
	
	p = fopen ("nome", "rb");

	if (!p)
		printf ("Erro na abertura do arquivo.");
	
	/*do
	{*/
		fread (tam, sizeof (int), 4, p);
		for (int i = 0; i < 4; i++)
			printf ("%d ", tam[i]);
	//}
}

