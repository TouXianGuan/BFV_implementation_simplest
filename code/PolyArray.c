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
	int i;
	for(i=0; i<this->size; i++) {
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
	int i;
	for(i=0; i<this->size; i++){
		if(this->polys[i]) poly_print(this->polys[i], order);
	}
}
