#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define Gau 4

#include "Poly.h"
#include "PolyPairs.h"
#include "PolyArray.h"
#include "Key.h"

Poly* poly_rand(int degree, int range) {
	Poly* poly1 = poly_create(degree);
	int i;
	for(i=0; i<=degree; i++){
		int coeffient = rand() % range - range / 2;
		poly_term(poly1, coeffient, i);
	}
	
	return poly1;
}

Poly* poly_Gaussian(int degree, int range) {
	Poly* poly1 = poly_create(degree);
	int i;
	for(i=0; i<=degree; i++){
		double u = (double)rand() / RAND_MAX; // 生成0~1之间的均匀分布随机数
		double std_dev = (double)range / 2;
		int coeffient = (int)round(std_dev * sqrt(-2 * log(u))); // 使用反函数法生成满足离散正态分布的随机数
		poly_term(poly1, coeffient, i);
	}
	
	return poly1;
}

Poly* pri_key(int degree) {	
	return poly_rand(degree, 3);
}

Poly* gen_a(int degree, int range) {
	return poly_rand(degree, range);
}

Poly* pk0(Poly* a, Poly* s, Poly* e, int d, int q)
{
	//-a
	Poly *poly1 = poly_mod_coefficient_mul(a, -1, q);
	
	//-a*s
	Poly *poly2 = poly_mod_mul(poly1, s, d, q);
	
	//-a*s+e
	Poly *poly3 = poly_mod_add(poly2, e, d, q);
	
	return poly3;
}

Poly* pk1(Poly* a, int d, int q) {
	Poly *poly1 = poly_mod_poly(a, d);
	Poly *poly2 = poly_mod_coefficient(poly1, q);
	
	return poly2;
}

PolyArray* pub_key(Poly* s, int d, int q) {
	Poly* a = gen_a(d-1, q);
	printf("a\t\t");
	poly_print(a, 1);
	
	Poly* e = poly_Gaussian(d-1, Gau);
	printf("e\t\t");
	poly_print(e, 1);
	
	PolyArray* pk = polyarray_create();
	polyarray_poly(pk, pk0(a, s, e, d, q), 0);
	polyarray_poly(pk, pk1(a, d, q), 1);
	
	return pk;
}
