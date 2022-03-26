#ifndef NUMERO_H
#define NUMERO_H

#include <stdint.h>

struct NumeroVtbl;
struct Numero_st;

struct Numero_st {
    struct NumeroVtbl const *metodo; 
} ;

typedef struct Numero_st  Numero_t;
typedef struct Numero_st* Numero_pt;

/* Tabela Virtual de métodos de "Numero" */
struct NumeroVtbl {
	Numero_pt 	(*copia)	(Numero_t const * const me);

	Numero_pt 	(*soma)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

	Numero_pt 	(*subt)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							 Numero_t       * const res);

    Numero_pt 	(*mult)		(Numero_t const * const  me,
							 Numero_t const * const  outro,
							Numero_t        * const res);

    char *      (*imprime)  (Numero_t const * const  me);

    void        (*destroi)  (Numero_t       **       me_ref);
};

typedef struct NumeroVtbl * NumeroVtbl_pt;



/*-------------------------------------------------------
 * 	INTERFACE PÚBLICA DE Numero_t
 * ------------------------------------------------------*/
Numero_pt	Num_constroi	(Numero_pt 						me);

static inline 
Numero_pt 	Num_copia		(Numero_t 	const 	* 	const 	me) {

 	return (  me->metodo->copia(me));
}

static inline 
Numero_pt 	Num_soma 		(Numero_t 	const 	* 	const  	me,
							Numero_t 	const 	* 	const  	outro,
						    Numero_t       		* 	const 	res) {

 	return (me->metodo->soma(me, outro, res));
}

static inline
Numero_pt 	Num_subt 		(Numero_t 	const 	* 	const  	me,
							Numero_t 	const 	* 	const  	outro,
							Numero_t       		* 	const 	res) {

 	return (me->metodo->subt(me, outro, res));
}

static inline
Numero_pt 	Num_mult 		(Numero_t 	const 	* 	const  	me,
							Numero_t 	const 	* 	const  	outro,
							Numero_t       		* 	const 	res) {
	return (me->metodo->mult(me, outro, res));
}

static inline
char* 		Num_imprime 	(Numero_t 	const 	* 	const  	me) {

 	return (me->metodo->imprime)(me);
}

static inline
void  		Num_destroi 	(Numero_t  			**   		me_ref) {
  /* (me->metodo->destroi)(me)*/;
}

#endif