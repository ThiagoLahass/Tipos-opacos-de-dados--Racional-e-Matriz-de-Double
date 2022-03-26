#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "matriz.h"

static  Numero_pt copia_		(Numero_t	const	*	const	me);

static  Numero_pt soma_			(Numero_t	const	*	const	me,
								 Numero_t	const	*	const	outro,
							     Numero_t			*	const	res);

static  Numero_pt subt_			(Numero_t	const	*	const	me,
								Numero_t	const	*	const	outro,
								Numero_t			*	const	res);

static  Numero_pt mult_			(Numero_t	const	*	const	me,
								Numero_t	const	*	const	outro,
								Numero_t			*	const	res);

static  char * imprime_			(Numero_t	const	*	const	me);

static  void destroi_			(Numero_t			**			me);


/*-----------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de matriz	 *
 *-----------------------------------------------------------------------*/
static  MatrizDouble_pt Copia_ 		(MatrizDouble_t const 	* const  me);

static  MatrizDouble_pt Soma_  		(MatrizDouble_t const 	* const  me,
							   		MatrizDouble_t 	const 	* const  outro,
							   		MatrizDouble_t       	* const  res);

static  MatrizDouble_pt Subt_  		(MatrizDouble_t const 	* const  me,
							   		MatrizDouble_t 	const 	* const  outro,
							   		MatrizDouble_t       	* const  res);

static  MatrizDouble_pt Mult_  		(MatrizDouble_t const 	* const  me,
									MatrizDouble_t 	const 	* const  outro,
									MatrizDouble_t       	* const  res);

static  char *	Imprime_			(MatrizDouble_t	const	* const	 me);

static  void	Destroi_			(MatrizDouble_t			**		 me);

/*----------------FUNCOES ESPECIFICAS PARA O TIPO MATRIZ--------------------*/

static int Retorna_Num_Linhas_ 		(MatrizDouble_t	const	*	const	me);

static int Retorna_Num_Colunas_ 	(MatrizDouble_t	const	*	const	me);

static 	double 	Get_ 				(MatrizDouble_t const   * 	const   me, int linha,
																		int coluna);

static 	void   	Set_ 				(MatrizDouble_t         * 	const   me, int linha, 
																		int coluna,
                                                            			double valor);

static MatrizDouble_pt Resize_ 		(MatrizDouble_t 		* 			me, int num_lin,
																		int num_col);

static MatrizDouble_pt Ones_ 		(MatrizDouble_t 		* 			me, int num_lin,
																		int num_col);

static MatrizDouble_pt Identidade_ 	(MatrizDouble_t 		* 			me, int tam);

static MatrizDouble_pt Mult_escalar_(MatrizDouble_t 		* 	const 	me, double escalar);

static MatrizDouble_pt Dot_  		(MatrizDouble_t const 	* const  me,
									MatrizDouble_t 	const 	* const  outro,
									MatrizDouble_t       	* const  res);

static MatrizDouble_pt  Transpor_ 	(MatrizDouble_t      	* 	     	me);

static MatrizDouble_pt  Transpor_diag_2_ (MatrizDouble_t	*        	me);

static MatrizDouble_pt  Reverse_horizontal_ (MatrizDouble_t * 	const   me);

static MatrizDouble_pt  Reverse_vertical_  (MatrizDouble_t  * 	const   me);

static MatrizDouble_pt  Acrescenta_lin_ (MatrizDouble_t     *      		me);

static MatrizDouble_pt  Acrescenta_col_ (MatrizDouble_t     *      		me);

/*---------------------------------------------*
* implementação do construtor                  *
* ---------------------------------------------*/
MatrizDouble_pt Matriz_constroi (MatrizDouble_pt  me, int num_linhas, int num_colunas) {

	if (num_linhas < 0 || num_colunas < 0) {
		fprintf(stderr, "ERROR em 'Matriz_constroi'\n");
		fprintf(stderr, "Indices [%d][%d] devem ser maiores que zero\n", num_linhas, num_colunas);
		exit(EXIT_FAILURE);
	}

    static struct NumeroVtbl const vtbl = {
		&copia_,
		&soma_,
		&subt_,
        &mult_,
        &imprime_,
        &destroi_
    };
	
	me = (MatrizDouble_t*) malloc(sizeof(MatrizDouble_t)); 

	me->super.metodo = &vtbl;

	me->matriz = (double**) calloc(num_linhas, sizeof(double*));

	if (me->matriz == NULL) {
		fprintf(stderr, "ERROR em 'Matriz_constroi'\n");
		fprintf(stderr, "Erro na alocação de memória em Matriz_constroi\n");
		exit(EXIT_FAILURE);
	}

	for( int i = 0; i < num_linhas; i++ ) {
		me->matriz[i] = (double*) calloc(num_colunas, sizeof(double));
		for( int j = 0; j < num_colunas; j++ ) {
			me->matriz[i][j] = 0;
		}
	}
	

    static struct MatrizDouble_Interface_st const interface = {
		&Copia_,
		&Soma_,
		&Subt_,
        &Mult_,
        &Imprime_,
        &Destroi_,
		&Retorna_Num_Linhas_,
		&Retorna_Num_Colunas_,
        &Get_,
        &Set_,
		&Resize_,
		&Ones_,
		&Identidade_,
		&Mult_escalar_,
		&Dot_,
		&Transpor_,
		&Transpor_diag_2_,
		&Reverse_horizontal_,
		&Reverse_vertical_,
		&Acrescenta_lin_,
		&Acrescenta_col_,
    };

	me->Metodo = &interface;

	me->tam = (int*) calloc (2, sizeof(int));

	if (me->tam == NULL) {
		fprintf(stderr, "ERROR em 'Matriz_constroi'\n");
		fprintf(stderr, "Erro na alocação de memória dos valores do tamanho da matriz\n");
		exit(EXIT_FAILURE);
	}

	me->tam[0] = num_linhas;
	me->tam[1] = num_colunas;

    return (me);
}


/*--------------------------------------------------------*
* implementação das funcoes especificas do tipo matriz    *
* --------------------------------------------------------*/
static inline
int Retorna_Num_Linhas_ 	(MatrizDouble_t	const	*	const	me) {

	return me->tam[0];
}

static inline
int Retorna_Num_Colunas_ 	(MatrizDouble_t	const	*	const	me) {

	return me->tam[1];
}

static inline
double Get_ 				( MatrizDouble_t const * const  me, int linha, 
																int coluna) {

	return (me->matriz[linha][coluna]);
}

static inline
void Set_ 					(MatrizDouble_t 	*	const me, 	int linha, 
																int coluna,
																double valor) {
	if ( (linha < 0 || linha >= Retorna_Num_Linhas_(me)) || (coluna < 0 || coluna >= Retorna_Num_Colunas_(me) )){
		fprintf(stderr, "ERROR em 'Set'\n");
		fprintf(stderr, "Indice [%d][%d] esta fora dos limites: [%d][%d]\n", linha, coluna, Retorna_Num_Linhas_(me) - 1, Retorna_Num_Colunas_(me) - 1);
		exit(EXIT_FAILURE);
	}
	
	me->matriz[linha][coluna] = valor;
}

static inline
MatrizDouble_pt Resize_ 	(MatrizDouble_t * 	me, int num_lin,
													int num_col) {
	if (num_lin < 0 || num_col < 0 ) {
		fprintf(stderr, "ERROR em 'Resize'\n");
		fprintf(stderr, "Indices [%d][%d] devem ser maiores que zero\n", num_lin, num_col);
		exit(EXIT_FAILURE);
	}

	int lin_old = Retorna_Num_Linhas_(me);
	int col_old = Retorna_Num_Colunas_(me);
	int lin_set, col_set;

	MatrizDouble_pt new = NULL;
	new = Matriz_constroi(new, num_lin, num_col );

	if( num_lin < lin_old){
		if( num_col < col_old ){
			lin_set = num_lin;
			col_set = num_col;
		}
		else{
			lin_set = num_lin;
			col_set = lin_old;
		}
	}
	else{
		if( num_col < col_old ){
			lin_set = lin_old;
			col_set = num_col;
		}
		else{
			lin_set = lin_old;
			col_set = col_old;
		}
	}

	for( int i = 0; i < lin_set; i++ ) {
		for( int j = 0; j < col_set; j++ ) {
			Set_(new, i, j, Get_(me, i, j));
		}
	}

	for( int i = 0; i < lin_old; i++ ) {
		free (me->matriz[i]);
	}

	*me = *new;
	return me;
}

static inline
MatrizDouble_pt Ones_ 			(MatrizDouble_t * 	me, int num_lin,
														int num_col) {
	if (num_lin < 0 || num_col < 0) {
		fprintf(stderr, "ERROR em 'Ones'\n");
		fprintf(stderr, "Indices [%d][%d] devem ser maiores que zero\n", num_lin, num_col);
		exit(EXIT_FAILURE);
	}

	me = Resize_(me, num_lin, num_col);

	for (int i = 0; i < num_lin; i++) {
		for (int j = 0; j < num_col; j++) {

			Set_(me, i, j, 1);
		}	
	}

	return me;
}

static inline
MatrizDouble_pt Identidade_ 	(MatrizDouble_t * 	me, int tam) {

	if ( tam < 0 ) {
		fprintf(stderr, "ERROR em 'Identidade'\n");
		fprintf(stderr, "Tamanho %d deve ser maior que zero\n", tam);
		exit(EXIT_FAILURE);
	}

	me = Resize_(me, tam, tam);

	for (int i = 0; i < tam; i++) {
		for (int j = 0; j < tam; j++) {
			if(i == j){

				Set_(me, i, j, 1);
			}
			else{

				Set_(me, i, j, 0);
			}
		}	
	}

	return me;
}

static inline
MatrizDouble_pt Mult_escalar_ 	(MatrizDouble_t * const me, double escalar) {
	int lin = Retorna_Num_Linhas_(me);
	int col = Retorna_Num_Colunas_(me);

	for (int i = 0; i < lin; i++) {
		for (int j = 0; j < col; j++) {

			Set_(me, i, j, Get_(me, i, j) * escalar);
		}
	}

	return me;
}

static inline
MatrizDouble_pt Dot_  	(MatrizDouble_t const 	* const  me,
						MatrizDouble_t 	const 	* const  outro,
						MatrizDouble_t       	* const  res) {
	
	int lin_me 		= Retorna_Num_Linhas_(me),
		col_me 		= Retorna_Num_Colunas_(me),
		lin_outro 	= Retorna_Num_Linhas_(outro),
		col_outro 	= Retorna_Num_Colunas_(outro),
		lin_res		= Retorna_Num_Linhas_(res),
		col_res 	= Retorna_Num_Colunas_(res);

	MatrizDouble_pt aux = Copia_(me);
	double valor = 0;

	if( (col_me == lin_outro) && (col_res == col_outro) && (lin_me == lin_res)){
		for( int i = 0; i < lin_me; i++ ){
			for( int j = 0; j < col_outro; j++ ){
				for( int k = 0; k < lin_outro; k++ ){
					valor += Get_(me, i, k) * Get_(outro, k, j);
				}

				Set_(aux, i, j, valor);
				valor = 0;
			}
		}

		for( int i = 0; i < lin_res; i++ ){
			for( int j = 0; j < col_res; j++ ){
				Set_(res, i, j, Get_(aux, i, j));
			}
		}
	}
	else {
		fprintf(stderr, "ERROR em 'Dot'\n");
		fprintf(stderr, "Não é possivel multiplicar matrizes com tamanhos:\n");
		fprintf(stderr, "Tamanho Matriz_1 = [%d][%d]\n", lin_me, col_me );
		fprintf(stderr, "Tamanho Matriz_2 = [%d][%d]\n", lin_outro, col_outro );
		fprintf(stderr, "Ou o tamanho da Matriz resultado nao confere\n");
		fprintf(stderr, "Tamanho Matriz_3 = [%d][%d]\n", lin_res, col_res );
		exit(EXIT_FAILURE);
	}

	Destroi_(&aux);
	return res;
}

static MatrizDouble_pt  Transpor_ 	(MatrizDouble_t  * me) {

	int lin_me = Retorna_Num_Linhas_(me), col_me = Retorna_Num_Colunas_(me);

	MatrizDouble_pt aux = Copia_(me);
	me = Resize_(me, col_me, lin_me);

	lin_me = Retorna_Num_Linhas_(me);
	col_me = Retorna_Num_Colunas_(me);

	for( int i = 0; i < lin_me; i++ ) {
		for( int j = 0; j < col_me; j++ ) {
			
			Set_(me, i, j, Get_(aux, j, i));
		}
	}

	Destroi_(&aux);
	return me;
}

static MatrizDouble_pt  Transpor_diag_2_  	(MatrizDouble_t * me) {

	me = Transpor_(me);
	me = Reverse_horizontal_(me);
	me = Reverse_vertical_(me);

	return me;
}

static MatrizDouble_pt  Reverse_horizontal_ (MatrizDouble_t  * const  me) {

	int lin_me = Retorna_Num_Linhas_(me), col_me = Retorna_Num_Colunas_(me);
	MatrizDouble_pt aux = Copia_(me);
	
	for( int i = 0; i < lin_me; i++ ) {
		for( int j = 0; j < col_me; j++ ) {
			
			Set_(me, i, j, Get_(aux, lin_me - i - 1, j));
		}
	}
	
	Destroi_(&aux);
	return me;
}

static MatrizDouble_pt  Reverse_vertical_  (MatrizDouble_t  * const me) {

	int lin_me = Retorna_Num_Linhas_(me), col_me = Retorna_Num_Colunas_(me);
	MatrizDouble_pt aux = Copia_(me);
	
	for( int i = 0; i < lin_me; i++ ) {
		for( int j = 0; j < col_me; j++ ) {
			
			Set_(me, i, j, Get_(aux, i, col_me - j - 1));
		}
	}
	
	Destroi_(&aux);
	return me;
}

static MatrizDouble_pt  Acrescenta_lin_  (MatrizDouble_t * me) {

	int lin_me = Retorna_Num_Linhas_(me), col_me = Retorna_Num_Colunas_(me);

	me = Resize_(me, lin_me + 1, col_me);

	return me;
}

static MatrizDouble_pt  Acrescenta_col_   (MatrizDouble_t * me) {

	int lin_me = Retorna_Num_Linhas_(me), col_me = Retorna_Num_Colunas_(me);

	me = Resize_(me, lin_me, col_me + 1);

	return me;
}


/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           		*
 * -----------------------------------------------------*/
static inline
MatrizDouble_pt Copia_ (MatrizDouble_t const * const  me) {

	return ( (MatrizDouble_pt) copia_ ((Numero_pt) me));
}

static Numero_pt copia_ (Numero_t const * const  me) {	

	int lin = Retorna_Num_Linhas_((MatrizDouble_pt)me), col = Retorna_Num_Colunas_((MatrizDouble_pt)me);
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Matriz_constroi ((MatrizDouble_pt) outro, lin, col);

	for( int i = 0; i < lin; i++) {
		for( int j = 0; j < col; j++) {
			((MatrizDouble_pt) outro)->matriz[i][j] = ((MatrizDouble_pt) me)->matriz[i][j];
		}
	}
	return outro;
}


static inline
MatrizDouble_pt Soma_  (MatrizDouble_t const * const  me,
						MatrizDouble_t const * const  outro,
						MatrizDouble_t       * const  res) {

	return ((MatrizDouble_pt) soma_ ((Numero_pt) me, (Numero_pt) outro,(Numero_pt) res));
}

static  Numero_pt soma_ (Numero_t const * const  me,
						Numero_t  const * const  outro,
						Numero_t        * const  res) {

	int lin_me 		= Retorna_Num_Linhas_((MatrizDouble_pt)me),
		col_me 		= Retorna_Num_Colunas_((MatrizDouble_pt)me),
		lin_outro 	= Retorna_Num_Linhas_((MatrizDouble_pt)outro),
		col_outro 	= Retorna_Num_Colunas_((MatrizDouble_pt)outro);

	if( ( lin_me == lin_outro ) && ( col_me = col_outro )){
		for( int i = 0; i < lin_me; i++ ){
			for( int j = 0; j < col_me; j++ ){
				((MatrizDouble_pt) res)->matriz[i][j] = ((MatrizDouble_pt) me)->matriz[i][j] +
														((MatrizDouble_pt) outro)->matriz[i][j];
			}
		}
	}
	else {
		fprintf(stderr, "ERROR em 'Soma'\n");
		fprintf(stderr, "Não é possivel somar matrizes com tamanhos diferentes\n");
		fprintf(stderr, "Tamanho Matriz_1 = [%d][%d]\n", lin_me, col_me);
		fprintf(stderr, "Tamanho Matriz_2 = [%d][%d]\n", lin_outro, col_outro);
		exit(EXIT_FAILURE);
	}

	return (Numero_pt) res;
}


static inline
MatrizDouble_pt Subt_  (   MatrizDouble_t const * const  me,
						   MatrizDouble_t const * const  outro,
						   MatrizDouble_t       * const  res) {

	return ((MatrizDouble_pt) subt_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}

static  Numero_pt subt_  (	Numero_t const * const  me,
							Numero_t const * const  outro,
							Numero_t       * const  res) {

	int lin_me 		= Retorna_Num_Linhas_((MatrizDouble_pt)me),
		col_me 		= Retorna_Num_Colunas_((MatrizDouble_pt)me),
		lin_outro 	= Retorna_Num_Linhas_((MatrizDouble_pt)outro),
		col_outro 	= Retorna_Num_Colunas_((MatrizDouble_pt)outro);

	if( ( lin_me == lin_outro ) && ( col_me = col_outro )){
		for( int i = 0; i < lin_me; i++ ){
			for( int j = 0; j < col_me; j++ ){
				((MatrizDouble_pt) res)->matriz[i][j] = ((MatrizDouble_pt) me)->matriz[i][j] -
														((MatrizDouble_pt) outro)->matriz[i][j];
			}
		}
	}
	else {
		fprintf(stderr, "ERROR em 'Subt'\n");
		fprintf(stderr, "Não é possivel subtrair matrizes com tamanhos diferentes\n");
		fprintf(stderr, "Tamanho Matriz_1 = [%d][%d]\n", lin_me, col_me);
		fprintf(stderr, "Tamanho Matriz_2 = [%d][%d]\n", lin_outro, col_outro);
		exit(EXIT_FAILURE);
	}

	return (Numero_pt) res;
}


static inline
MatrizDouble_pt Mult_  ( MatrizDouble_t const * const  me,
						MatrizDouble_t 	const * const  outro,
					   MatrizDouble_t         * const  res) {
	return ((MatrizDouble_pt) mult_ ((Numero_pt) me, (Numero_pt) outro, (Numero_pt) res));
}

static  Numero_pt mult_  (Numero_t 	const * const  me,
						Numero_t 	const * const  outro,
						Numero_t       	  * const  res) {

	int lin_me 		= Retorna_Num_Linhas_((MatrizDouble_pt)me),
		col_me 		= Retorna_Num_Colunas_((MatrizDouble_pt)me),
		lin_outro 	= Retorna_Num_Linhas_((MatrizDouble_pt)outro),
		col_outro 	= Retorna_Num_Colunas_((MatrizDouble_pt)outro),
		lin_res		= Retorna_Num_Linhas_((MatrizDouble_pt)res),
		col_res 	= Retorna_Num_Colunas_((MatrizDouble_pt)res);
	
	MatrizDouble_pt aux = Copia_((MatrizDouble_pt)me);
	double valor = 0;

	if( (col_me == lin_outro) && (col_res == col_outro) && (lin_me == lin_res)){
		for( int i = 0; i < lin_me; i++ ){
			for( int j = 0; j < col_outro; j++ ){
				for( int k = 0; k < col_me; k++ ){
					valor += Get_((MatrizDouble_pt)me, i, k) * Get_((MatrizDouble_pt)outro, k, j);
				}
				Set_((MatrizDouble_pt) aux, i, j, valor);
				valor = 0;
			}
		}

		for( int i = 0; i < lin_res; i++ ){
			for( int j = 0; j < col_res; j++ ){
				Set_((MatrizDouble_pt)res, i, j, Get_((MatrizDouble_pt)aux, i, j));
			}
		}

	}
	else {
		fprintf(stderr, "ERROR em 'Mult'\n");
		fprintf(stderr, "Não é possivel multiplicar matrizes com tamanhos:\n");
		fprintf(stderr, "Tamanho Matriz_1 = [%d][%d]\n", lin_me, col_me);
		fprintf(stderr, "Tamanho Matriz_2 = [%d][%d]\n", lin_outro, col_outro);
		fprintf(stderr, "Ou o tamanho da Matriz resultado nao confere\n");
		fprintf(stderr, "Tamanho Matriz_3 = [%d][%d]\n", lin_res, col_res);
		exit(EXIT_FAILURE);
	}

	Destroi_(&aux);
	return (Numero_pt) res;
}


static inline
char * Imprime_  ( MatrizDouble_t const * const  me) {

	return ( imprime_ ((Numero_pt) me));
}

static  char * imprime_  (Numero_t const * const  me) {

	int num_linhas 	= ((MatrizDouble_pt) me)->tam[0];
	int num_colunas = ((MatrizDouble_pt) me)->tam[1];
	int i, j;
    static char buffer[50] = "";
	
	/*
	for( i = 0; i < num_linhas; i++ ) {
		for( j = 0; j < num_colunas; j++ ) {
			sprintf(buffer[i],  "%.2f ",Get_(((MatrizDouble_pt)me), i, j));
		}
		sprintf(buffer, "\n");
	}
	*/

	for( i = 0; i < num_linhas; i++ ) {
		for( j = 0; j < num_colunas; j++ ) {
			printf("%10.2f ",Get_(((MatrizDouble_pt)me), i, j));
		}
		printf("\n");
	}
	printf("\n");

	return buffer;
}

/*---------------------------------------------*
* implementação do destrutor                   *
* ---------------------------------------------*/
static inline
void Destroi_  (MatrizDouble_t **   me_ref) {

	destroi_ ((Numero_t **)  me_ref);
}

static void destroi_ (Numero_t **  me_ref) {
	Numero_t * me = *me_ref;

	for( int i = 0; i < ((MatrizDouble_pt) me)->tam[0]; i++ ) {
		free (((MatrizDouble_pt) me)->matriz[i]);
	}
	free (((MatrizDouble_pt) me)->matriz);
	free ((Numero_pt) me);
	*me_ref = NULL;
}