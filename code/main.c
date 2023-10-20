#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Poly.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"
#include "Homomorphic.h"

int main(int argc, char *argv[]) {
	int c1[] = {3, 0, 2, 0, 0, 0, 0, 0, -3, 0, 0, 0, 0, 0, 0, 0};
	int c2[] = {0, 3, 2, 1, 0};
	int i, len;
	
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
	
	int d = 16, t = 7, q = 128 * t;
	
	Poly *sk = pri_key(16);
	printf("私钥\t");
	poly_print(sk, 1);
	
	PolyArray* pk = pub_key(sk, d, q);
	printf("公钥\n");
	polyarray_print(pk, 1);	
	
	PolyArray* m1 = ct(pk, poly1, d, t, q);
	printf("密文1\n");
	polyarray_print(m1, 1);	
	
	PolyArray* m2 = ct(pk, poly2, d, t, q);
	printf("密文2\n");
	polyarray_print(m2, 1);	
	
	PolyArray* m3 = homo_add(m1, m2, d, q);
	printf("同态加\n");
	polyarray_print(m3, 1);
	
	PolyArray* m4 = homo_mul(m1, m2, d, t, q);
	printf("同态乘\n");
	polyarray_print(m4, 1);	
	
	Poly* M3 = decryption(m3, sk, d, t, q);
	printf("同态加解密\t\t");
	poly_print(M3, 1);	
	
	Poly* M4 = decryption(m4, sk, d, t, q);
	printf("同态乘解密\t\t");
	poly_print(M4, 1);	
	
	
	return 0;
}
