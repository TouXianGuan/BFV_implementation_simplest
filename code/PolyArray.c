#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define initial_size 20

#include "Poly.h"
#include "PolyArray.h"

/*
	创建一个多项式组。
*/
PolyArray* polyarray_create() {
	PolyArray* this = (PolyArray*)malloc(sizeof(PolyArray));
	this->size = initial_size;
	this->polys = (Poly**)calloc(this->size, sizeof(Poly*));
}

/*
	销毁一个多项式组。
	this:	被销毁的多项式组指针 
*/
void polyarray_free(PolyArray* this) {
	for(int i=0; i<this->size; i++) {
		if(this->polys[i])	poly_free(this->polys[i]);
	}
	free(this->polys);
	free(this);
}

void polyarray_poly(PolyArray* this, Poly* poly, int exponent) {
	if(exponent >= this->size) return;

	this->polys[exponent] = poly;
}

/*
	在控制台输出多项式组。
	this:	要输出的多项式组 
	order:	输出顺序。1: 从高次幂到低次幂，否则相反 
*/
void polyarray_print(PolyArray* this, int order) {
	for(int i=0; i<this->size; i++){
		if(this->polys[i]) {
			printf("%d\t\t", i);
			poly_print(this->polys[i], order);
		}
	}
}

PolyArray* polyarray_add(PolyArray* pa1, PolyArray* pa2, int d, int t) {
	int size = (pa1->size >= pa2->size) ? pa1->size : pa2->size;
	PolyArray* pa3 = polyarray_create();
	
	for(int i=0; i<size; i++){
		if(pa1->polys[i] && pa2->polys[i])
			polyarray_poly(pa3, poly_mod_add(pa1->polys[i], pa2->polys[i], d, t), i);
		else if(pa1->polys[i] && !pa2->polys[i]) {
			Poly* tmp = poly_create(pa1->polys[i]->degree);
			polyarray_poly(pa3, poly_mod_add(pa1->polys[i], tmp, d, t), i);
			poly_free(tmp);
		}
		else if(!pa1->polys[i] && pa2->polys[i]) {
			Poly* tmp = poly_create(pa2->polys[i]->degree);
			polyarray_poly(pa3, poly_mod_add(tmp, pa2->polys[i], d, t), i);
			poly_free(tmp);
		}
	}
	
	return pa3;
}

PolyArray* polyarray_sub(PolyArray* pa1, PolyArray* pa2, int d, int t) {
	int size = (pa1->size >= pa2->size) ? pa1->size : pa2->size;
	PolyArray* pa3 = polyarray_create();
	
	for(int i=0; i<size; i++){
		if(pa1->polys[i] && pa2->polys[i])
			polyarray_poly(pa3, poly_mod_sub(pa1->polys[i], pa2->polys[i], d, t), i);
		else if(pa1->polys[i] && !pa2->polys[i]) {
			Poly* tmp = poly_create(pa1->polys[i]->degree);
			polyarray_poly(pa3, poly_mod_sub(pa1->polys[i], tmp, d, t), i);
			poly_free(tmp);
		}
		else if(!pa1->polys[i] && pa2->polys[i]) {
			Poly* tmp = poly_create(pa2->polys[i]->degree);
			polyarray_poly(pa3, poly_mod_sub(tmp, pa2->polys[i], d, t), i);
			poly_free(tmp);
		}
	}
	
	return pa3;
}

PolyArray* polyarray_mul(PolyArray* pa1, PolyArray* pa2, int d, int t) {
	int size = (pa1->size >= pa2->size) ? pa1->size : pa2->size;
	PolyArray* pa3 = polyarray_create();
	
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			if(pa1->polys[i] && pa2->polys[j])
				polyarray_poly(pa3, poly_mod_sub(pa1->polys[i], pa2->polys[i], d, t), i+j);
		}
	}
	
	return pa3;
}

PolyArray *polyarray_coe_mul(PolyArray *pa, int a, int t) {
	int size = pa->size;
	PolyArray* pa3 = polyarray_create();
	
	for(int i=0; i<size; i++){
		if(pa->polys[i])
			polyarray_poly(pa3, poly_mod_coefficient_mul(pa->polys[i], a, t), i);
	}
	
	return pa3;
}
