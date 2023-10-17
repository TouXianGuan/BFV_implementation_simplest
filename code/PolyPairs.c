#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Poly.h"
#include "PolyPairs.h"

/*
	����һ������ʽ�ԡ�
*/
PolyPairs* polypairs_create(Poly* poly0, Poly* poly1) {
	PolyPairs* this = (PolyPairs*)malloc(sizeof(PolyPairs));
	this->poly0 = poly0;
	this->poly1 = poly1;
}

/*
	����һ������ԡ�
	this:	�����ٵĶ���ʽָ�� 
*/
void polypairs_free(PolyPairs* this) {
	poly_free(this->poly0);
	poly_free(this->poly1);
}

/*
	�ڿ���̨�������ʽ��
	this:	Ҫ����Ķ���ʽ
	order:	���˳��1: �Ӹߴ��ݵ��ʹ��ݣ������෴ 
*/
void polypairs_print(PolyPairs* this, int order) {
	poly_print(this->poly0, order);
	poly_print(this->poly1, order);
}
