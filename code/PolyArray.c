#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define initial_size 20

#include "Poly.h"
#include "PolyArray.h"

/*
	����һ������ʽ�顣
*/
PolyArray* polyarray_create() {
	PolyArray* this = (PolyArray*)malloc(sizeof(PolyArray));
	this->size = initial_size;
	this->polys = (Poly**)calloc(this->size, sizeof(Poly*));
}

/*
	����һ������ʽ�顣
	this:	�����ٵĶ���ʽ��ָ�� 
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
	�ڿ���̨�������ʽ�顣
	this:	Ҫ����Ķ���ʽ�� 
	order:	���˳��1: �Ӹߴ��ݵ��ʹ��ݣ������෴ 
*/
void polyarray_print(PolyArray* this, int order) {
	int i;
	for(i=0; i<this->size; i++){
		if(this->polys[i]) poly_print(this->polys[i], order);
	}
}
