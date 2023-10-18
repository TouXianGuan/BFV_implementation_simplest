#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define Gau 4

#include "Poly.h"
#include "PolyPairs.h"
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

Poly* sk(int degree) {	
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

PolyPairs* pk(int d, int q) {
	Poly* a = gen_a(d, q);
	poly_print(a, 1);
	Poly* s = sk(d);
	poly_print(s, 1);
	Poly* e = poly_Gaussian(d, Gau);
	poly_print(e, 1);
	
	PolyPairs* Pk = polypairs_create(pk0(a, s, e, d, q), pk1(a, d, q));
	
	return Pk;
}
