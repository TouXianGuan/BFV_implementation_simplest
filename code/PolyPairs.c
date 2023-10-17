#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Poly.h"
#include "PolyPairs.h"

/*
	创建一个多项式对。
*/
PolyPairs* polypairs_create(Poly* poly0, Poly* poly1) {
	PolyPairs* this = (PolyPairs*)malloc(sizeof(PolyPairs));
	this->poly0 = poly0;
	this->poly1 = poly1;
}

/*
	销毁一个多项对。
	this:	被销毁的多项式指针 
*/
void polypairs_free(PolyPairs* this) {
	poly_free(this->poly0);
	poly_free(this->poly1);
}

/*
	在控制台输出多项式。
	this:	要输出的多项式
	order:	输出顺序。1: 从高次幂到低次幂，否则相反 
*/
void polypairs_print(PolyPairs* this, int order) {
	poly_print(this->poly0, order);
	poly_print(this->poly1, order);
}
