#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "numero.h"

static  Numero_pt Num_copia_ (Numero_t const * const   me);

static  Numero_pt Num_soma_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_subt_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  Numero_pt Num_mult_  (Numero_t const * const    me,
							  Numero_t const * const    outro,
							  Numero_t       * const    res);

static  char * Num_imprime_  (Numero_t const * const    me);

static  void   Num_destroi_  (Numero_t  	**     		me_ref);

Numero_pt Num_constroi (Numero_pt  me) {

	me = (Numero_t *) malloc (sizeof(Numero_t));
	if (me == NULL) {
		/*erro!!! não conseguiu alocar */
	    printf ("Erro na alocação de memória em Num_Constroi");
	    exit (1);
	}

    static struct NumeroVtbl const vtbl = {
		&Num_copia_,
		&Num_soma_,
		&Num_subt_,
        &Num_mult_,
        &Num_imprime_,
        &Num_destroi_
    };

    me->metodo = &vtbl;

    return (me);
}

static inline
Numero_pt 	Num_copia_ 	(Numero_t 	const 	* 	const   me) {

	assert (0);
	printf ("%p",(void *)me);
	return (Numero_pt) NULL;
}

static inline
Numero_pt 	Num_soma_  	(Numero_t 	const 	* 	const    me,
						Numero_t 	const 	* 	const    outro,
						Numero_t       		* 	const    res) {

	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline
Numero_pt 	Num_subt_  	(Numero_t 	const 	* 	const    me,
						Numero_t 	const 	* 	const    outro,
						Numero_t       		* 	const    res) {

	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);
	return (Numero_pt) NULL;
}

static inline
Numero_pt 	Num_mult_  	(Numero_t 	const 	* 	const    me,
						Numero_t 	const 	* 	const    outro,
						Numero_t       		* 	const    res) {

	assert (0);
	printf ("%p %p %p",(void *)me, (void *)outro, (void *)res);

	return (Numero_pt) NULL;
}

static inline
char* 		Num_imprime_  (Numero_t const 	* 	const    me) {
	assert (0);
	printf ("%p",(void *)me);
	return (char *) NULL;
}

/* --------------------------------------------------*
 * implementação do destrutor                        *
 * --------------------------------------------------*/
static inline
void 		Num_destroi_ 	(Numero_t 		** 			me_ref) {
	/* *free (me); */
}