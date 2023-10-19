#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define Gau 4

#include "Poly.h"
#include "PolyPairs.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"

Poly* ct0(PolyArray* pk, Poly* m, int d, int t, int q, Poly* e1, Poly* u) {
	//pk0 * u
	Poly *poly1 = poly_mod_mul(pk->polys[0], u, d, q);
	
	//pk0 * u + e1
	Poly *poly2 = poly_mod_add(poly1, e1, d, q);
	
	//(q / t) * m
	Poly *poly3 = poly_mod_coefficient_mul(m, q/t, q);
	
	//pk0 * u + e1 + (q / t) * m
	Poly *poly4 = poly_mod_add(poly2, poly3, d, q);
	
	poly_free(poly1);
	poly_free(poly2);
	poly_free(poly3);
	
	return poly4;	
}

Poly* ct1(PolyArray* pk, int d, int q, Poly* e2, Poly* u) {
	//pk1 * u
	Poly *poly1 = poly_mod_mul(pk->polys[1], u, d, q);
	
	//pk1 * u + e2
	Poly *poly2 = poly_mod_add(poly1, e2, d, q);
	
	poly_free(poly1);
	
	return poly2;	
}

PolyArray* ct(PolyArray* pk, Poly* m, int d, int t, int q) {
	Poly* u = poly_rand(d-1, 3);
	printf("u\t\t");
	poly_print(u, 1);
	
	Poly* e1 = poly_Gaussian(d-1, Gau);
	printf("e1\t\t");
	poly_print(e1, 1);
	
	Poly* e2 = poly_Gaussian(d-1, Gau);
	printf("e2\t\t");
	poly_print(e2, 1);
	
	PolyArray* Ct = polyarray_create();
	polyarray_poly(Ct, ct0(pk, m, d, t, q, e1, u), 0);
	polyarray_poly(Ct, ct1(pk, d, q, e2, u), 1);
	
	poly_free(u);
	poly_free(e1);
	poly_free(e2);
	
	return Ct;
}
