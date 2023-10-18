#include <stdio.h>
#include <stdlib.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "Key.h"

int c1[16] = {252, -113, -234, 110, 377, -281, -158, 26, 430, -41, -142, -83, 86, -32, -431, -285};
int c2[8] = {3, 0, 0, 0, 0, 0, 0, 0, -3};
int c3[16] = {4, -6, 2, -3, -3, -4, 5, 4, 4, 1, 3, -4, -1, 3, -2, -5};
int c4[16] = {2, -2, -4, 1, -2, 2, -3, -4, 4, -1, 2, 5, 0, -4, 2, -7};
int c5[15] = {1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, 0, 1, 1, 1};
int i, len;

int main(int argc, char *argv[]) {
	
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
	
	len = sizeof(c3) / sizeof(int);
	Poly* poly3 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly3, c3[i], i);
	}
	printf("多项式四\t");
	poly_print(poly3, 1);
	
	len = sizeof(c3) / sizeof(int);
	Poly* poly3 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly3, c3[i], i);
	}
	printf("多项式五\t");
	poly_print(poly3, 1);
	
	PolyPairs* Pk = pk(16, 874);
	printf("公钥\t");
	polypairs_print(Pk, 1);	
	
	poly_free(poly1);
	poly_free(poly2);
	poly_free(poly3);
	polypairs_free(Pk);
	
	return 0;
}
