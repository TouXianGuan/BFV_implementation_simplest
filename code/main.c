#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"
#include "Homomorphic.h"

int c1[16] = {252, -113, -234, 110, 377, -281, -158, 26, 430, -41, -142, -83, 86, -32, -431, -285};
int c2[] = {3, 0, 2, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0};
int c3[16] = {4, -6, 2, -3,-3, -4, 5, 4, 4, 1, 3, -4, -1, 3, -2, -5};
int c4[16] = {2, -2, -4, 1, -2, 2, -3, -4, 4, -1, 2, 5, 0, -4, 2, -7};
int c5[15] = {1, 0, 0, -1, 0, -1, 0, 0, -1, 0, 0, 0, 1, 1, 1};
int c6[16] = {84, -60, -282, 186, 322, -138, 70, 52, 107, -212, -369, 447, -229, -393, -256, 42};
int c7[16] = {393, 7, -12, -2, -3, -13, 10, 9, -380, 19, -23, -32, 22, 17, -2, 13};
int c8[] = {0, 3, 2, 1, 0};
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
	
	len = sizeof(c7) / sizeof(int);
	Poly* poly7 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly7, c7[i], i);
	}
	printf("多项式七\t");
	poly_print(poly7, 1);
	
	len = sizeof(c8) / sizeof(int);
	Poly* poly8 = poly_create(len - 1);
	for (i=0; i<len; i++) {
		poly_term(poly8, c8[i], i);
	}
	printf("多项式八\t");
	poly_print(poly8, 1);	
	Poly *sk = pri_key(16);
	printf("私钥\t");
	poly_print(sk, 1);
	
	PolyArray* pk = pub_key(sk, 16, 896);
	printf("公钥\n");
	polyarray_print(pk, 1);	
	
	PolyArray* m1 = ct(pk, poly2, 16, 7, 896);
	printf("密文1\n");
	polyarray_print(m1, 1);	
	
	PolyArray* m2 = ct(pk, poly8, 16, 7, 896);
	printf("密文2\n");
	polyarray_print(m2, 1);	
	
	PolyArray* m3 = homo_add(m1, m2, 16, 896);
	printf("同态加\n");
	polyarray_print(m3, 1);	
	
	Poly* M3 = m_dec(m3, sk, 16, 7, 896);
	printf("同态加解密\n");
	poly_print(M3, 1);	
		
	PolyArray* mmul = polyarray_coe_mul(m1, 3, 896);
	printf("多项式组系数乘法\n");
	polyarray_print(mmul, 1);
	
	return 0;
}
