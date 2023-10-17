#include <stdio.h>
#include <stdlib.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "Key.h"

int c1[16] = {84, -60, -282, 186, 322, -138, 70, 52, 107, -212, -369, 447, -229, -393, -256, 42};
int c2[16] = {-1, 1, 1, 0, -1, 0, 1, 0, 1, -1, 0, -1, -1, -1, 0, 1};
int c3[16] = {1, 4, 0, 4, -4, 3, -1, 0, 4, 1, -6, -6, 7, 1, 1, -3};
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
	
	Poly* coeDiv = poly_mod_coefficient_Div(poly1, 37, 24);
	printf("多项式系数除法 \t");
	poly_print(coeDiv, 1);	
	
	poly_free(poly1);
	poly_free(poly2);
	poly_free(poly3);
	poly_free(coeDiv);
	
	return 0;
}
