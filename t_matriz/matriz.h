#ifndef MATRIZDOUBLE_H
#define MATRIZDOUBLE_H

#include "numero.h"

struct MatrizDouble_Interface_st;

struct MatrizDouble_st {
    struct Numero_st super; 
    struct MatrizDouble_Interface_st const *  Metodo;
    int *tam;
    double ** matriz;
};

typedef struct MatrizDouble_st* MatrizDouble_pt;
typedef struct MatrizDouble_st  MatrizDouble_t;


struct MatrizDouble_Interface_st {

    MatrizDouble_pt (*copia)	    (MatrizDouble_t const   * const     me);

    MatrizDouble_pt (*soma)	        (MatrizDouble_t const   * const     me, 
							        MatrizDouble_t  const   * const     outro, 
							        MatrizDouble_t          * const     res);
    
    MatrizDouble_pt (*subt)	        (MatrizDouble_t const   * const     me, 
							        MatrizDouble_t  const   * const     outro, 
							        MatrizDouble_t          * const     res);
							 
    MatrizDouble_pt (*mult)	        (MatrizDouble_t const   * const     me, 
							        MatrizDouble_t  const   * const     outro, 
							        MatrizDouble_t          * const     res);
							 					 
    char *      	(*imprime)      (MatrizDouble_t const   * const     me);
    
    void        	(*destroi)      (MatrizDouble_t         **          me_ref);

    int (*retorna_num_linhas)       (MatrizDouble_t	const	* const	    me);

    int (*retorna_num_colunas)      (MatrizDouble_t	const	* const	    me);


    double       	(*get)  	    (MatrizDouble_t const   * const     me, int linha, 
                                                                        int coluna);

	void   		 	(*set) 		    (MatrizDouble_t         * const     me, int linha, 
                                                                        int coluna,
                                                                        double valor);
                                                                    
    MatrizDouble_pt (*resize)       (MatrizDouble_t         *           me, int num_lin, 
                                                                        int num_col);

    MatrizDouble_pt (*ones)         (MatrizDouble_t         *           me, int num_lin,
                                                                        int num_col);

    MatrizDouble_pt (*identidade)   (MatrizDouble_t         *           me, int tam);

    MatrizDouble_pt (*mult_escalar) (MatrizDouble_t         * const     me, double escalar);

    MatrizDouble_pt (*dot)	        (MatrizDouble_t const   * const     me, 
							        MatrizDouble_t  const   * const     outro, 
							        MatrizDouble_t          * const     res);

    MatrizDouble_pt (*transpor) 	(MatrizDouble_t         * 	        me);

    MatrizDouble_pt (*transpor_diag_2)(MatrizDouble_t       *           me);

    MatrizDouble_pt  (*reverse_horizontal)(MatrizDouble_t   * const     me);

    MatrizDouble_pt  (*Reverse_vertical)(MatrizDouble_t     * const     me);

    MatrizDouble_pt  (*acrescenta_lin)(MatrizDouble_t       *           me);

    MatrizDouble_pt  (*acrescenta_col)(MatrizDouble_t       *           me);

};

typedef struct MatrizDouble_Interface_st *MatrizDouble_Interface_pt;

MatrizDouble_pt Matriz_constroi (MatrizDouble_pt  me, int num_linhas, int num_colunas);

#endif
