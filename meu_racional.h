#ifndef MEURACIONAL_H
#define MEURACIONAL_H

#include "numero.h" /*a interface da classe básica */

struct MeuRacional_Interface_st;

struct MeuRacional_st {
    struct Numero_st super;
    struct MeuRacional_Interface_st const *  Metodo;
    long int* valores;
};

typedef struct MeuRacional_st* MeuRacional_pt;
typedef struct MeuRacional_st  MeuRacional_t;



struct MeuRacional_Interface_st {
	MeuRacional_pt (*copia)		(MeuRacional_t	const * const	me);

    MeuRacional_pt (*atribui)	(MeuRacional_t	const * const	me,
								 MeuRacional_t* const			outro);

    MeuRacional_pt (*soma)		(MeuRacional_t	const * const	me,
								MeuRacional_t	const * const	outro,
								MeuRacional_t 		  *			res);

    MeuRacional_pt (*subt)		(MeuRacional_t	const * const	me,
								MeuRacional_t	const * const	outro,
								MeuRacional_t		  *	const	res);

    MeuRacional_pt (*mult)		(MeuRacional_t	const * const	me,
								MeuRacional_t	const * const	outro,
								MeuRacional_t         *	const	res);

    MeuRacional_pt (*divd)		(MeuRacional_t	const * const	me,
								MeuRacional_t	const * const	outro,
								MeuRacional_t		  *	const	res);

    MeuRacional_pt (*ac_soma)	(MeuRacional_t* const			me,
							     MeuRacional_t	const * const	outro);

    MeuRacional_pt (*ac_subt)	(MeuRacional_t* const			me,
							     MeuRacional_t	const * const	outro);

    MeuRacional_pt (*ac_mult)	(MeuRacional_t* const			me,
							     MeuRacional_t	const * const	outro);

    MeuRacional_pt (*ac_divd)	(MeuRacional_t* const			me,
							     MeuRacional_t	const *	const	outro);

    int			(*compara)		(MeuRacional_t	const * const	me,
								MeuRacional_t	const * const	outro);

    char *      (*imprime)		(MeuRacional_t	const * const	me);

    void        (*destroi)		(MeuRacional_t**				me_ref);

    /*------------------------------------------------------*/
	void			(*get     )	(MeuRacional_t  const	* 	const	me,
												long int			num,
												long int			den);

	void			(*set     )	(MeuRacional_t  		* const		me,
												long int			num,
												long int			den);

	long int		(*getNum  )	(MeuRacional_t  const 	* const		me);

	void   			(*setNum )	(MeuRacional_t			* const		me,
												long int			num);


	long int		(*getDen )	(MeuRacional_t	const 	* const		me);

	void   			(*setDen )	(MeuRacional_t			*	const	me,
												long int			num);

    double			(*modulo)	(MeuRacional_t  const * const		me);
    /*------------------------------------------------------*/
};

typedef struct MeuRacional_Interface_st *MeuRacional_Interface_pt;


/* protótipo do construtor   */
MeuRacional_pt Racional_constroi	(MeuRacional_pt				me,
													long int 	num,
													long int 	den);


#endif /* MEURACIONAL_H */
