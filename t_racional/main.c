#include <stdio.h>
#include "meu_racional.h"

int main ()
{
	MeuRacional_pt R1 = NULL, R2 = NULL, R3 = NULL;

   printf("---------PRIMEIRA OPERACAO-----------\n");
   printf("Criando Racional_1 e Racional_2\n");

	R1 = Racional_constroi (R1, 10, 20);
	R2 = R1->Metodo->copia (R1);

	printf ("R1 = %s\nR2 = %s \n", R1->Metodo->imprime (R1), R2->Metodo->imprime (R2));
   
   printf("\n---------SEGUNDA OPERACAO-----------\n");
   printf("Criando Racional_3 = 0 e Racional_3 recebe os valores de Racional_2\n");

   R3 = Racional_constroi (R3, 0, 1);
   printf ("R3 antes = %s \n", R3->Metodo->imprime (R3));
   R3 = R2->Metodo->atribui (R2, R3);

   printf ("R2 = %s \n", R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------TERCEIRA OPERACAO-----------\n");
   printf("Racional_3 recebe a soma de Racional_1 com Racional_2\n");
   
   R3 = R3->Metodo->soma(R1, R2, R3);
   
   printf ("R1 = %s \nR2 = %s \n", R1->Metodo->imprime (R1),R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------QUARTA OPERACAO-----------\n");
   printf("Racional_3 recebe a subtracao de Racional_3 com Racional_2\n");

   printf ("R3 antes = %s \n", R3->Metodo->imprime (R3));
   R3 = R3->Metodo->subt(R3, R2, R3);

   printf ("R2 = %s \n", R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------QUINTA OPERACAO-----------\n");
   printf("Racional_3 recebe a multiplicacao de Racional_1 com Racional_2\n");

   R3 = R3->Metodo->mult(R1, R2, R3);

   printf ("R1 = %s \nR2 = %s \n", R1->Metodo->imprime (R1), R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------SEXTA OPERACAO-----------\n");
   printf("Racional_3 recebe a divisao de Racional_1 com Racional_2\n");
   
   R3 = R3->Metodo->divd(R1, R2, R3);

   printf ("R1 = %s \nR2 = %s \n", R1->Metodo->imprime (R1), R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------SETIMA OPERACAO-----------\n");
   printf("Racional_3 foi somado com Racional_2\n");

   printf("R3 antes = %s \n", R3->Metodo->imprime (R3));

   R3 = R3->Metodo->ac_soma(R3, R2);

   printf ("R2 = %s \n", R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------OITAVA OPERACAO-----------\n");
   printf("Racional_3 foi subtraido com Racional_2\n");

   printf("R3 antes = %s \n", R3->Metodo->imprime (R3));

   R3 = R3->Metodo->ac_subt(R3, R2);
   
   printf ("R2 = %s \n", R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------NONA OPERACAO-----------\n");
   printf("Racional_3 foi multiplicado por Racional_2\n");

   printf("R3 antes = %s \n", R3->Metodo->imprime (R3));

   R3 = R3->Metodo->ac_mult(R3, R2);

   printf ("R2 = %s \n", R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------DECIMA OPERACAO-----------\n");
   printf("Racional_3 foi dividido por Racional_2\n");

   printf("R3 antes = %s \n", R3->Metodo->imprime (R3));
   
   R3 = R3->Metodo->ac_divd(R3, R2);
   
   printf ("R2 = %s \n", R2->Metodo->imprime (R2));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   printf("\n---------DECIMA PRIMEIRA OPERACAO-----------\n");

   printf("modulo R1 = %f\n", R1->Metodo->modulo(R1));
   printf("modulo R2 = %f\n", R2->Metodo->modulo(R2));
   printf("modulo R3 = %f\n", R3->Metodo->modulo(R3));

   printf("\n---------DECIMA SEGUNDA OPERACAO-----------\n");
   printf("Compara Racional_1 com Racional_2\n");

   printf ("R1 = %s \n", R1->Metodo->imprime (R1));
   printf ("R2 = %s \n", R2->Metodo->imprime (R2));

   int compara = R1->Metodo->compara(R1,R2);

   if( compara == 0 ) {
      printf ("R1 eh igual a R2\n");
   }
   else if ( compara > 0 ) {
      printf ("R1 eh maior que R2\n");
   }
   else {
      printf ("R1 eh menor que R2\n");
   }

   printf("\n---------DECIMA TERCEIRA OPERACAO-----------\n");
   printf("Compara Racional_1 com Racional_3\n");

   printf ("R1 = %s \n", R1->Metodo->imprime (R1));
   printf ("R3 = %s \n", R3->Metodo->imprime (R3));

   compara = R1->Metodo->compara(R1,R3);

   if( compara == 0 ) {
      printf ("R1 eh igual a R3\n");
   }
   else if ( compara > 0 ) {
      printf ("R1 eh maior que R3\n");
   }
   else {
      printf ("R1 eh menor que R3\n");
   }

   printf("\n---------DECIMA QUARTA OPERACAO-----------\n");
   printf("Compara Racional_3 com Racional_2\n");

   printf ("R3 = %s \n", R3->Metodo->imprime (R3));
   printf ("R2 = %s \n", R2->Metodo->imprime (R2));

   compara = R3->Metodo->compara(R3,R2);

   if( compara == 0 ) {
      printf ("R3 eh igual a R2\n");
   }
   else if ( compara > 0 ) {
      printf ("R3 eh maior que R2\n");
   }
   else {
      printf ("R3 eh menor que R2\n");
   }

   printf("\n---------DECIMA QUINTA OPERACAO-----------\n");
   printf("Destroi  Racional_1, Racional_2 e Racional_3\n");

	R1->Metodo->destroi (&R1);
	R2->Metodo->destroi (&R2);
   R3->Metodo->destroi (&R3);

   if ( R1 == NULL ){
      printf("R1 é NULL \n");
   }
   else{
      printf("R1 nao foi destruido"); 
   }
   if ( R2 == NULL ){
      printf("R2 é NULL \n");
   }
   else{
      printf("R2 nao foi destruido \n");
   }
   if ( R3 == NULL ){
      printf("R3 é NULL \n");
   }
   else{
      printf("R3 nao foi destruido \n");
   }


	return (0);
}








