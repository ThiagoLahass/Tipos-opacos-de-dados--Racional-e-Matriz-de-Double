#include <float.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "meu_racional.h"

static  Numero_pt copia_		(Numero_t	const	*	const	me);

static  Numero_pt atribui_		(Numero_t	const	*	const	me,
								Numero_t			*	const	outro) ;

static  Numero_pt soma_			(Numero_t	const	*	const	me,
								 Numero_t	const	*	const	outro,
							     Numero_t			*	const	res);

static  Numero_pt subt_			(Numero_t	const	*	const	me,
								Numero_t	const	*	const	outro,
								Numero_t			*	const	res);

static  Numero_pt mult_			(Numero_t	const	*	const	me,
								Numero_t	const	*	const	outro,
								Numero_t			*	const	res);

static  Numero_pt divd_			(Numero_t	const	*	const	me,
								Numero_t	const	*	const	outro,
								Numero_t			*	const	res);

static  Numero_pt ac_soma_		(Numero_t			*	const	me,
								Numero_t	const	*	const	outro);

static  Numero_pt ac_subt_		(Numero_t			*	const	me,
								Numero_t	const	*	const	outro);

static  Numero_pt ac_mult_		(Numero_t			*	const	me,
								Numero_t	const	*	const	outro);

static  Numero_pt ac_divd_		(Numero_t			*	const	me,
								Numero_t	const	*	const	outro);

static  int	compara_ 			(Numero_t	const	*	const	me,
								Numero_t	const	*	const	outro);

static  char * imprime_			(Numero_t	const	*	const	me);

static  void destroi_			(Numero_t			**			me);

/*-----------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PRIVADA das funções virtuais de MeuRacional*
 *-----------------------------------------------------------------------*/

void reduz_racional (MeuRacional_t* 	const 	me)
{
	int sinal;
	if ((me->valores[0] * me->valores[1] ) < 0) 
	{ 
		sinal = -1 ;
	}
	else
	{
		sinal = + 1;
	}
	
	long int a, b, rem;
	
	if (me->valores[0] > me->valores[1])
	{	a =  labs (me->valores[0]);
		b =  labs (me->valores[1]); 
	}
	else
	{
		a = labs(me->valores[1]);
		b = labs(me->valores[0]);
	}
	while (b > 0)
	{
		rem = b;
		b = a % b;
		a = rem; 	// a é o MDC de valores[0](numerador) e valores[1](denominador)
	}
	me->valores[0] = labs(me->valores[0]) / a * sinal;
	me->valores[1] = labs(me->valores[1]) / a;
}


/*-----------------------------------------------------------------------*
 * IMPLEMENTAÇÃO DA INTERFACE PÚBLICA das funções virtuais de MeuRacional*
 *-----------------------------------------------------------------------*/
static  MeuRacional_pt	Copia_		(MeuRacional_t	const	*	const	me);

static  MeuRacional_pt	Atribui_	(MeuRacional_t	const	*	const	me,
									MeuRacional_t			*	const	outro) ;

static  MeuRacional_pt	Soma_		(MeuRacional_t	const	*	const	me,
									MeuRacional_t	const	*	const	outro,
									MeuRacional_t			*	const	res);

static  MeuRacional_pt	Subt_		(MeuRacional_t	const	*	const	me,
									MeuRacional_t	const	*	const	outro,
									MeuRacional_t			*	const	res);

static  MeuRacional_pt	Mult_		(MeuRacional_t	const	*	const	me,
									MeuRacional_t	const	*	const	outro,
									MeuRacional_t			*	const	res);

static  MeuRacional_pt	Divd_		(MeuRacional_t	const	*	const	me,
									MeuRacional_t	const	*	const	outro,
									MeuRacional_t			*	const	res);

static  MeuRacional_pt	Ac_Soma_	(MeuRacional_t			*	const	me,
									MeuRacional_t	const	*	const	outro);

static  MeuRacional_pt	Ac_Subt_	(MeuRacional_t			*	const	me,
									MeuRacional_t	const	*	const	outro);

static  MeuRacional_pt	Ac_Mult_	(MeuRacional_t			*	const	me,
									MeuRacional_t	const	*	const	outro);

static  MeuRacional_pt	Ac_Divd_	(MeuRacional_t			*	const	me,
									MeuRacional_t	const	*	const	outro);

static  int				Compara_ 	(MeuRacional_t	const	*	const	me,
									MeuRacional_t	const	*	const	outro);

static  char *			Imprime_	(MeuRacional_t	const	*	const	me);

static  void			Destroi_	(MeuRacional_t			**			me);

/* ------------------------------------------------------- *
 * funções que são típicas do numero racional, mas não são *
 * funcoes da classe virtual básica número                 *
 * protótipos das funçoes get e set, por exemplo           *
 *---------------------------------------------------------*/
static 	void			Get_		(MeuRacional_t	const	*	const	me,
													long int			num,
													long int			den);

static 	void			Set_		(MeuRacional_t			* 	const 	me,
													long int			num,
													long int			den);

static	long int		GetNum_		(MeuRacional_t  const	*	const	me);

static	void   			SetNum_		(MeuRacional_t			* 	const 	me,
													long int			num);

static	long int		GetDen_		(MeuRacional_t  const	*	const	me);

static	void   			SetDen_		(MeuRacional_t			* 	const 	me,
													long int			den);

static	double			Modulo_		(MeuRacional_t  const	*	const	me);

 /*---------------------------------------------*
 * implementação do construtor                  *
 * ---------------------------------------------*/
MeuRacional_pt Racional_constroi	(MeuRacional_pt						me,
													long int			num,
													long int			den)
{
	if ( den == 0 ) {
		fprintf(stderr, "ERROR em 'Racional_constroi'\n");
		fprintf(stderr, "O denominador deve ser diferente de zero\n");
		exit(EXIT_FAILURE);
	}

    static struct NumeroVtbl const vtbl = {
        &copia_,
        &atribui_,
        &soma_,
        &subt_,
        &mult_,
        &divd_,
        &ac_soma_,
        &ac_subt_,
        &ac_mult_,
        &ac_divd_,
        &compara_,
        &imprime_,
        &destroi_
    };

    //me = (MeuRacional_pt) Num_constroi ((Numero_pt) me);
	me = (MeuRacional_t*) malloc(sizeof(MeuRacional_t));

	if (me == NULL)
	{
		fprintf(stderr, "ERROR em 'Racional_constroi'\n");
		fprintf(stderr, "Erro na alocação de memória do Racional\n");
		exit(EXIT_FAILURE);
	}

    me->super.metodo = &vtbl;

    static struct MeuRacional_Interface_st const interface = {
    	&Copia_,
        &Atribui_,
        &Soma_,
        &Subt_,
        &Mult_,
        &Divd_,
        &Ac_Soma_,
        &Ac_Subt_,
        &Ac_Mult_,
        &Ac_Divd_,
        &Compara_,
        &Imprime_,
        &Destroi_,
        &Get_,
        &Set_,
        &GetNum_,
        &SetNum_,
        &GetDen_,
        &SetDen_,
        &Modulo_
    };

    me->Metodo = &interface;

	me->valores = (long int*) malloc (2 * sizeof(long int));

	if (me->valores == NULL)
	{
		fprintf(stderr, "ERROR em 'Racional_constroi'\n");
		fprintf(stderr, "Erro na alocação de memória dos valores de num e den\n");
		exit(EXIT_FAILURE);
	}

    me->valores[0] = num;
    me->valores[1] = den;

    return (me);
}


 /*---------------------------------------------*
 * implementação do set e get                   *
 * ---------------------------------------------*/
static inline
void Get_ (MeuRacional_t	const	*	const	me,
							long int			num,
							long int			den)

{
	num = (me->valores[0]);
	den = (me->valores[1]);
}


static inline
void Set_ (MeuRacional_t* const me,
						long int	num,
						long int	den)
{

	if ( den == 0 ) {
		fprintf(stderr, "ERROR em 'Set'\n");
		fprintf(stderr, "O denominador deve ser diferente de zero\n");
		exit(EXIT_FAILURE);
	}

	me->valores[0] = num;
	me->valores[1] = den;

	reduz_racional( me );
}

static inline
long int	GetNum_	(MeuRacional_t  const* const	me)
{
	return me->valores[0];
}


static inline
void   		SetNum_	(MeuRacional_t	* const me,
					long int				num)
{
	me->valores[0] = num;

	reduz_racional( me );
}


static inline
long int	GetDen_	(MeuRacional_t  const* const	me)
{
	return me->valores[1];
}

static inline
void   		SetDen_	(MeuRacional_t	* 	const 	me,
					long int					den)
{
	if ( den == 0 ) {
		fprintf(stderr, "ERROR em 'Set_Den'\n");
		fprintf(stderr, "O denominador deve ser diferente de zero\n");
		exit(EXIT_FAILURE);
	}

	me->valores[1] = den;

	reduz_racional( me );
}

static
double		Modulo_(MeuRacional_t   const* const me)
{
	return(((double)(GetNum_(me)))/ ((double)(GetDen_(me))));
}

/*------------------------------------------------------*
 * IMPLEMENTAÇÃO DAS FUNÇÕES VIRTUAIS           *
 * -----------------------------------------------------*/
static inline
MeuRacional_pt Copia_ (MeuRacional_t const * const  me)
{
	return ( (MeuRacional_pt) copia_ ((Numero_pt) me));
}

 static
 Numero_pt copia_ (Numero_t const * const  me)
{
	assert (me != NULL);
	Numero_pt outro = NULL;
	outro = (Numero_pt) Racional_constroi
							((MeuRacional_pt) outro,
							  GetNum_((MeuRacional_pt) me),
							  GetDen_((MeuRacional_pt) me));
	return outro;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Atribui_(MeuRacional_t const * const me,
						MeuRacional_t       * const outro)
{
	return ( (MeuRacional_pt) atribui_ ((Numero_pt) me,
										(Numero_pt) outro));
}

static
 Numero_pt atribui_		(Numero_t const * const		me,
						Numero_t		* const		outro)
 {
	 Set_( (MeuRacional_pt) outro,
	       GetNum_(	(MeuRacional_pt) me),
	       GetDen_( (MeuRacional_pt) me) );

	 return (Numero_pt) outro;
 }
/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt	Soma_		(MeuRacional_t const	* const  me,
							MeuRacional_t	const	* const  outro,
							MeuRacional_t			* const  res)
{
	return ((MeuRacional_pt) soma_ ((Numero_pt) me,
					 						(Numero_pt) outro,
					 						(Numero_pt) res));
}

static  Numero_pt soma_		(Numero_t	const * const  me,
							Numero_t	const * const  outro,
							Numero_t		  * const  res)
{
	Set_((MeuRacional_pt) res,
				
				GetNum_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro)
												+
				GetNum_((MeuRacional_pt) outro)	*	GetDen_((MeuRacional_pt) me),

				GetDen_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro) );

	return (Numero_pt) res;
}


/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Subt_		(MeuRacional_t const * const  me,
							MeuRacional_t	const * const  outro,
							MeuRacional_t		  * const  res)
{
	return ( (MeuRacional_pt)	subt_ ((Numero_pt)		me,
										(Numero_pt)		outro,
										(Numero_pt)		res));
}
static  Numero_pt subt_  (	Numero_t const * const  me,
							Numero_t const * const  outro,
							Numero_t       * const  res)
{
		Set_((MeuRacional_pt) res,
				
				GetNum_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro)
												-
				GetNum_((MeuRacional_pt) outro)	*	GetDen_((MeuRacional_pt) me),

				GetDen_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro) );

	return (Numero_pt) res;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Mult_		(MeuRacional_t const * const  me,
							MeuRacional_t	const * const  outro,
							MeuRacional_t		  * const  res)
{
	return ( (MeuRacional_pt) mult_ ((Numero_pt) me,
									  (Numero_pt) outro,
									  (Numero_pt) res));
}

static  Numero_pt mult_		(Numero_t	const * const  me,
							Numero_t	const * const  outro,
							Numero_t		  * const  res)
{
     Set_((MeuRacional_pt) res,
				GetNum_((MeuRacional_pt) me)	*	GetNum_((MeuRacional_pt) outro),
				GetDen_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro) );

	 return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Divd_	(MeuRacional_t const * const  me,
						MeuRacional_t	const * const  outro,
						MeuRacional_t		  * const  res)
{
	return ( (MeuRacional_pt)
	          divd_ ((Numero_pt) me,
                     (Numero_pt) outro,
                     (Numero_pt) res));
}

static  Numero_pt divd_  (	Numero_t const * const  me,
							Numero_t const * const  outro,
							Numero_t       * const  res)
{
	if ( Modulo_((MeuRacional_pt) outro) == 0 ) {
		fprintf(stderr, "ERROR em 'Divd'\n");
		fprintf(stderr, "Erro na divisao, nao eh possivel dividir por zero\n");
		exit(EXIT_FAILURE);
	}

	Set_((MeuRacional_pt) res,
				GetNum_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro),
				GetDen_((MeuRacional_pt) me)	*	GetNum_((MeuRacional_pt) outro) );

	 return ( (Numero_pt) res);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Soma_  (MeuRacional_t*	const			me,
						 MeuRacional_t		const * const	outro)
{
	return ( (MeuRacional_pt)	ac_soma_ (	(Numero_pt) me,
											(Numero_pt) outro));
}

static  Numero_pt ac_soma_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				
				GetNum_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro)
												+
				GetNum_((MeuRacional_pt) outro)	*	GetDen_((MeuRacional_pt) me),

				GetDen_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro) );

	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Subt_  (MeuRacional_t* const  me,
						 MeuRacional_t const * const  outro)
{
	return ((MeuRacional_pt) ac_subt_	((Numero_pt)me,
										(Numero_pt)outro));

}


static  Numero_pt ac_subt_ (Numero_t       * const  me,
							Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				
				GetNum_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro)
												-
				GetNum_((MeuRacional_pt) outro)	*	GetDen_((MeuRacional_pt) me),

				GetDen_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro) );
	return (Numero_pt) me;
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Mult_		(MeuRacional_t*	const			me,
							MeuRacional_t		const * const	outro)
{
	return ((MeuRacional_pt) ac_mult_	((Numero_pt)me,
										(Numero_pt)outro));
}


static  Numero_pt ac_mult_  (Numero_t       * const  me,
                             Numero_t const * const  outro)
{
	Set_((MeuRacional_pt) me,
				GetNum_((MeuRacional_pt) me)	*	GetNum_((MeuRacional_pt) outro),
				GetDen_((MeuRacional_pt) me)	*	GetDen_((MeuRacional_pt) outro) );
	 return ( (Numero_pt) me);
}

/*-----------------------------------------------------------------*/
static inline
MeuRacional_pt Ac_Divd_  (MeuRacional_t*	const			me,
						 MeuRacional_t		const * const	outro)
{
	return ( (MeuRacional_pt)	ac_divd_ ((Numero_pt) me,
									     (Numero_pt) outro));
}


static  Numero_pt ac_divd_  (Numero_t       * const  me,
							Numero_t const * const  outro)
{

	if ( Modulo_((MeuRacional_pt) outro) == 0 ) {
		fprintf(stderr, "ERROR em 'Ac_Divd'\n");
		fprintf(stderr, "Erro na divisao, nao eh possivel dividir por zero\n");
		exit(EXIT_FAILURE);
	}

	Set_((MeuRacional_pt)me,
		GetNum_((MeuRacional_pt)me) * GetDen_((MeuRacional_pt)outro),
		GetDen_((MeuRacional_pt)me) * GetNum_((MeuRacional_pt)outro));

	 return ( (Numero_pt) me);}

/*-----------------------------------------------------------------*/
static inline
int Compara_	(MeuRacional_t const * const  me,
				MeuRacional_t	const * const  outro)
{
	return ( compara_ ((Numero_pt) me,
                       (Numero_pt) outro));
}

static  int	compara_ 	(Numero_t const * const  me,
                         Numero_t const * const  outro)
{
    double diferenca;
    diferenca	= Modulo_((MeuRacional_pt)me) - Modulo_((MeuRacional_pt)outro);

    if ( fabs (diferenca) < DBL_TRUE_MIN )
    {
		return (0);
	}
	if( diferenca > 0 )
	{ 
		return (1);
	}
	else
	{  
		return (-1);
	}
}

/*-----------------------------------------------------------------*/
static inline
char * Imprime_  (MeuRacional_t const * const  me)
{
	return ( imprime_ ((Numero_pt) me));
}

static  char * imprime_  (Numero_t const * const  me)
{
    static char buffer[50];

	sprintf(buffer, "%ld/%ld",GetNum_((MeuRacional_pt) me), (GetDen_((MeuRacional_pt) me)) );

	return buffer;
}


 /*---------------------------------------------*
 * implementação do destrutor                   *
 * ---------------------------------------------*/
static inline
void Destroi_  (MeuRacional_t **   me_ref)
{
	destroi_ ((Numero_t **)  me_ref);
}
static void destroi_ (Numero_t **  me_ref)
{
	Numero_t * me = *me_ref;
	free (((MeuRacional_pt) me)->valores);
	free ((Numero_pt) me);
	*me_ref = NULL;
}
