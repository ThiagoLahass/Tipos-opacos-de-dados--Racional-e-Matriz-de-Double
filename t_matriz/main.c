#include <stdio.h>
#include "matriz.h"

int main ()
{
	MatrizDouble_pt M1 = NULL, M2 = NULL, M3 = NULL, M4 = NULL;

   printf("---------PRIMEIRA OPERACAO-----------\n");
   printf("Criando Matriz_1 como 3x2\n");

	M1 = Matriz_constroi( M1, 3, 2);
   M1->Metodo->set(M1, 0, 0, 10);
   M1->Metodo->set(M1, 0, 1, 10.25);
   M1->Metodo->set(M1, 1, 0, 10.50);
   M1->Metodo->set(M1, 1, 1, 10.75);
   M1->Metodo->set(M1, 2, 0, 1);
   M1->Metodo->set(M1, 2, 1, 2);

   M1->Metodo->imprime (M1);

   printf("---------SEGUNDA OPERACAO-----------\n");
   printf("Copia Matriz_2 da Matriz_1\n");

   M2 = M1->Metodo->copia( M1 );

   printf("M1:\n");
   M1->Metodo->imprime (M1);
   printf("M2:\n");
   M2->Metodo->imprime (M2);

   printf("---------TERCEIRA OPERACAO-----------\n");
   printf("Seta Matriz_1[0][1] = 1000 e Matriz_2[1][0] = 5\n");

   M2->Metodo->set(M2, 1, 0, 5);
   M1->Metodo->set(M1, 0, 1, 1000);

   printf("M1:\n");
   M1->Metodo->imprime (M1);
   printf("M2:\n");
   M2->Metodo->imprime (M2);

   printf("---------QUARTA OPERACAO-----------\n");
   printf("Cria a Matriz_3 3x2 a faz Matriz_3 = Matriz_1 + Matriz_2\n");

   M3 = Matriz_constroi(M3, 3, 2);

   printf("M1:\n");
   M1->Metodo->imprime (M1);
   printf("M2:\n");
   M2->Metodo->imprime (M2);
   printf("M3 antes:\n");
   M3->Metodo->imprime (M3);

   M3 = M3->Metodo->soma(M1, M2, M3);

   printf("M3 depois:\n");
   M3->Metodo->imprime (M3);

   printf("---------QUINTA OPERACAO-----------\n");
   printf("Matriz_2 = Matriz_1 - Matriz_3\n");

   printf("M1:\n");
   M1->Metodo->imprime (M1);
   printf("M3:\n");
   M3->Metodo->imprime (M3);

   M2 = M2->Metodo->subt(M1, M3, M2);

   printf("M2 depois:\n");
   M2->Metodo->imprime (M2);

   printf("---------SEXTA OPERACAO-----------\n");
   printf("Cria a Matriz_4 2x2 a faz Matriz_3 = Matriz_1 * Matriz_4\n");
   M4 = Matriz_constroi(M4, 2, 2);
   M4->Metodo->set(M4, 0, 0, 1);
   M4->Metodo->set(M4, 0, 1, 2);
   M4->Metodo->set(M4, 1, 0, 3);
   M4->Metodo->set(M4, 1, 1, 4);

   M3 = M3->Metodo->mult(M1, M4, M3);

   printf("M1:\n");
   M1->Metodo->imprime (M1);
   printf("M4:\n");
   M4->Metodo->imprime (M4);
   printf("M3:\n");
   M3->Metodo->imprime (M3);

   printf("---------SETIMA OPERACAO-----------\n");
   printf("Resize de Matriz_4 de 2x2 para 5x5\n");

   printf("M4 antes:\n");
   M4->Metodo->imprime (M4);

   M4 = M4->Metodo->resize(M4, 5, 5);

   printf("M4:\n");
   M4->Metodo->imprime (M4);
   
   printf("Resize de Matriz_4 de 5x5 para 2x3\n");

   M4 = M4->Metodo->resize(M4, 2, 3);
   
   printf("M4:\n");
   M4->Metodo->imprime (M4);

   printf("---------OITAVA OPERACAO-----------\n");
   printf("Transforma a Matriz_1 numa matriz ones 3x3\n");

   printf("M1 antes:\n");
   M1->Metodo->imprime (M1);

   M1 = M1->Metodo->ones(M1, 3, 3);

   printf("M1:\n");
   M1->Metodo->imprime (M1);

   printf("---------NONA OPERACAO-----------\n");
   printf("Transforma a Matriz_1 numa matriz identidade 4x4\n");

   printf("M1 antes:\n");
   M1->Metodo->imprime (M1);

   M1 = M1->Metodo->identidade(M1, 4);

   printf("M1:\n");
   M1->Metodo->imprime (M1);

   printf("---------DECIMA OPERACAO-----------\n");
   printf("Multiplica a Matriz_2 pelo escalar 5\n");

   printf("M2 antes:\n");
   M2->Metodo->imprime (M2);

   M2 = M2->Metodo->mult_escalar(M2, 5);

   printf("M2:\n");
   M2->Metodo->imprime (M2);

   printf("-----DECIMA PRIMEIRA OPERACAO------\n");
   printf("Matriz_3 recebe o resultado da operacao DOT entre Matriz_3 e Matriz_4 (Matriz_3 * Matriz_4)\n");

   M4 = M4->Metodo->resize(M4, 2, 2);
   M4->Metodo->set(M4, 0, 0, 1);
   M4->Metodo->set(M4, 0, 1, 2);
   M4->Metodo->set(M4, 1, 0, 3);
   M4->Metodo->set(M4, 1, 1, 4);
   

   M3 = M3->Metodo->ones(M3, 3, 2);
   M3->Metodo->set(M3, 0, 0, 1);
   M3->Metodo->set(M3, 0, 1, 2);
   M3->Metodo->set(M3, 1, 0, 3);
   M3->Metodo->set(M3, 1, 1, 4);


   printf("M3 antes:\n");
   M3->Metodo->imprime (M3);
   printf("M4:\n");
   M4->Metodo->imprime (M4);

   M3 = M3->Metodo->dot(M3, M4, M3);

   printf("M3:\n");
   M3->Metodo->imprime (M3);

   printf("-----DECIMA SEGUNDA OPERACAO------\n");
   printf("Transpoe a Matriz_2\n");

   printf("M2 antes:\n");
   M2->Metodo->imprime (M2);

   M2 = M2->Metodo->transpor(M2);

   printf("M2:\n");
   M2->Metodo->imprime (M2);

   printf("-----DECIMA TERCEIRA OPERACAO------\n");
   printf("Transpoe_diag_2 a Matriz_2\n");

   printf("M2 antes:\n");
   M2->Metodo->imprime (M2);

   M2 = M2->Metodo->transpor_diag_2(M2);

   printf("M2:\n");
   M2->Metodo->imprime (M2);

   printf("-----DECIMA QUARTA OPERACAO-----\n");
   printf("Aplica a funcao reverse horizontal na Matriz_3\n");

   printf("M3 antes:\n");
   M3->Metodo->imprime (M3);

   M3 = M3->Metodo->reverse_horizontal(M3);

   printf("M3 depois:\n");
   M3->Metodo->imprime (M3);

   printf("-----DECIMA QUINTA OPERACAO------\n");
   printf("Aplica a funcao reverse vertical na Matriz_3\n");

   printf("M3 antes:\n");
   M3->Metodo->imprime (M3);

   M3 = M3->Metodo->Reverse_vertical(M3);

   printf("M3 depois:\n");
   M3->Metodo->imprime (M3);

   printf("-----DECIMA SEXTA OPERACAO------\n");
   printf("Adiciona uma linha na Matriz_2\n");

   printf("M2 antes:\n");
   M2->Metodo->imprime (M2);

   M2 = M2->Metodo->acrescenta_lin(M2);

   printf("M2:\n");
   M2->Metodo->imprime (M2);

   printf("-----DECIMA SETIMA OPERACAO------\n");
   printf("Adiciona uma coluna na Matriz_3\n");

   printf("M3 antes:\n");
   M3->Metodo->imprime (M3);

   M3 = M3->Metodo->acrescenta_col(M3);

   printf("M3 depois:\n");
   M3->Metodo->imprime (M3);

   printf("---------ULTIMA OPERACAO-----------\n");
   printf("Destroi as matrizes e verifica se seus ponteiros estao como NULL\n");

   M1->Metodo->destroi(&M1);
   M2->Metodo->destroi(&M2);
   M3->Metodo->destroi(&M3);
   M4->Metodo->destroi(&M4);

   if ( M1 == NULL ){
      printf("M1 == NULL \n");
   }
   else{
      printf("M1 nao foi destruido"); 
   }
   if ( M2 == NULL ){
      printf("M2 == NULL \n");
   }
   else{
      printf("M2 nao foi destruido \n");
   }
   if ( M3 == NULL ){
      printf("M3 == NULL \n");
   }
   else{
      printf("M3 nao foi destruido \n");
   }
   if ( M4 == NULL ){
      printf("M4 == NULL \n");
   }
   else{
      printf("M4 nao foi destruido \n");
   }

	return (0);
}