#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "Key.h"
#include "Enc.h"

int c1[16] = {252, -113, -234, 110, 377, -281, -158, 26, 430, -41, -142, -83, 86, -32, -431, -285};
int c2[9] = {3, 0, 0, 0, 0, 0, 0, 0, -3};
int c3[16] = {4, -6, 2, -3, -3, -4, 5, 4, 4, 1, 3, -4, -1, 3, -2, -5};
int c4[16] = {2, -2, -4, 1, -2, 2, -3, -4, 4, -1, 2, 5, 0, -4, 2, -7};
int c5[15] = {1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, 0, 1, 1, 1};
int c6[16] = {84, -60, -282, 186, 322, -138, 70, 52, 107, -212, -369, 447, -229, -393, -256, 42};
int i, len;

int main(int argc, char *argv[]) {
	srand(time(NULL) * 10000); 
	
	len = sizeof(c1) / sizeof(int);
	Poly* poly1 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly1, c1[i], i);
	}
	printf("多项式一\t");
	poly_print(poly1, 1);
	
	len = sizeof(c2) / sizeof(int);
	Poly* poly2 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly2, c2[i], i);
	}
	printf("多项式二\t");
	poly_print(poly2, 1);
	
	len = sizeof(c3) / sizeof(int);
	Poly* poly3 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly3, c3[i], i);
	}
	printf("多项式三\t");
	poly_print(poly3, 1);
	
	len = sizeof(c4) / sizeof(int);
	Poly* poly4 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly4, c4[i], i);
	}
	printf("多项式四\t");
	poly_print(poly4, 1);
	
	len = sizeof(c5) / sizeof(int);
	Poly* poly5 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly5, c5[i], i);
	}
	printf("多项式五\t");
	poly_print(poly5, 1);
	
	len = sizeof(c6) / sizeof(int);
	Poly* poly6 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly6, c6[i], i);
	}
	printf("多项式六\t");
	poly_print(poly6, 1);
	
	Poly* Sk = sk(15);
	printf("sk\t\t");
	poly_print(Sk, 1); 
	
	PolyPairs *Pk = pk(Sk, 16, 874);
	printf("pk\n");
	polypairs_print(Pk, 1); 
	printf("\n");
	
	PolyPairs *Ct = ct(Pk, poly2, 16, 7, 874);
	printf("Ct\n");
	polypairs_print(Ct, 1); 
	printf("\n");
	
	poly_free(poly1);
	poly_free(poly2);
	poly_free(poly3);
	poly_free(poly4);
	poly_free(poly5);
	poly_free(Sk);
	polypairs_free(Pk);
	polypairs_free(Ct);
	
	return 0;
}
