#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Poly.h"

/*
	����һ������ʽ��
	degree: ����ʽ����ݴ� 
*/
Poly* poly_create(unsigned int degree) {
	Poly* this = (Poly*)malloc(sizeof(Poly));
	this->degree = degree;
	this->terms = (PolyTerm*)calloc(degree+1, sizeof(PolyTerm)); 
}

/*
	����һ������ʽ��
	this:	�����ٵĶ���ʽָ�� 
*/
void poly_free(Poly* this) {
	free(this->terms);
	free(this);
}

/*
	�����ʽ�����һ���
	this:			Ŀ�����ʽ 
	coefficient:	������ϵ��
	exponent:		�������ݴ� 
*/
void poly_term(Poly* this, int coefficient, int exponent) {
	// ����������ݴθ��ڶ���ʽ����ݴΣ���ֱ�ӷ��� 
	if (exponent > this->degree) return;
	
	// ��ϵ��ǡ��λ�ü�¼ϵ��ֵ
	this->terms[exponent].coefficient = coefficient;
	this->terms[exponent].exponent = exponent;
}

Poly* poly_clone(Poly *this) {
	Poly* that = poly_create(this->degree);
	memcpy(that->terms, this->terms, (this->degree + 1) * sizeof(PolyTerm));
		
	return that;
}

/*
	�ڿ���̨�������ʽ��
	this:	Ҫ����Ķ���ʽ
	order:	���˳��1: �Ӹߴ��ݵ��ʹ��ݣ������෴ 
*/
void poly_print(Poly* this, int order) {
	if (this->degree == 0 && this->terms[0].coefficient == 0)
		printf("0");
	else {
		for (int i=0; i<=this->degree; i++) {
			int index = (order == 1) ? this->degree - i : i;
			if (this->terms[index].coefficient != 0) {
				if (this->terms[index].exponent == 0)
					printf("%d ", this->terms[index].coefficient);
				else if (this->terms[index].exponent == 1)
					printf("%dx ", this->terms[index].coefficient);
				else
					printf("%dx^%d ", this->terms[index].coefficient, this->terms[index].exponent);
			}
		}
	}
	printf("\n");
}

/*
	����ʽ��ӡ�
	poly1:	������
	poly2:	����
*/
Poly* poly_add(Poly* poly1, Poly* poly2) {
	int degree = (poly1->degree > poly2->degree) ? poly1->degree : poly2->degree;
	Poly* poly3 = poly_create(degree);
	
	for (int i=0; i<=degree; i++) {
		int coefficient1 = (i <= poly1->degree) ? poly1->terms[i].coefficient : 0;
		int coefficient2 = (i <= poly2->degree) ? poly2->terms[i].coefficient : 0;
		poly_term(poly3, coefficient1 + coefficient2, i);
	}
	
	return poly3;
}

/*
	����ʽ�����
	poly1:	������
	poly2:	����
*/
Poly* poly_sub(Poly* poly1, Poly* poly2) {
	int degree = (poly1->degree > poly2->degree) ? poly1->degree : poly2->degree;
	Poly* poly3 = poly_create(degree);
	
	for (int i=0; i<=degree; i++) {
		int coefficient1 = (i <= poly1->degree) ? poly1->terms[i].coefficient : 0;
		int coefficient2 = (i <= poly2->degree) ? poly2->terms[i].coefficient : 0;
		poly_term(poly3, coefficient1 - coefficient2, i);
	}
	
	return poly3;
}

/*
	����ʽ��ˡ� 
	poly1:	������
	poly2:	����
*/
Poly* poly_mul(Poly* poly1, Poly* poly2) {
	int degree = poly1->degree + poly2->degree;
	Poly* poly3 = poly_create(degree);
	
	for (int i=0; i<=poly1->degree; i++) {
		for (int j=0; j<=poly2->degree; j++) {
			int coefficient = poly1->terms[i].coefficient * poly2->terms[j].coefficient;
			int exponent = i + j;
			poly3->terms[exponent].coefficient += coefficient;
			poly3->terms[exponent].exponent = exponent;
		}
	}

	return poly3;
}

/*
	����ʽ����� 
	poly1:	������
	poly2:	����

Poly* poly_div(Poly* poly1, Poly* poly2) {
	if (poly1->degree < poly2->degree)
		return poly_create(0);
		
	int degree = poly1->degree - poly2->degree;
	Poly* quotient = poly_create(degree);			// �� 
	Poly* remainder  = poly_clone(poly1);			// ��
	
	while (remainder->degree >= poly2->degree) {
		int coefficient = remainder->terms[remainder->degree].coefficient / poly2->terms[poly2->degree].coefficient;
		int exponent  = remainder->degree - poly2->degree;
		poly_term(quotient, coefficient, exponent);
		
		for (int i = 0; i <= poly2->degree; i++) {
			remainder->terms[remainder->degree - poly2->degree + i].coefficient -= coefficient * poly2->terms[i].coefficient;
			remainder->terms[remainder->degree - poly2->degree + i].exponent  = exponent + poly2->terms[i].exponent;
		}

		remainder->degree--;
	}
	
	return quotient;
}

/*
	����ʽģ���� 
	poly1:	������
	poly2:	����

Poly* poly_mod(Poly* poly1, Poly* poly2) {
	if (poly1->degree < poly2->degree)
		return poly_clone(poly2);
		
	int degree = poly1->degree - poly2->degree;
	Poly* remainder  = poly_clone(poly1);			// ��
	
	while (remainder->degree >= poly2->degree) {
		int coefficient = remainder->terms[remainder->degree].coefficient / poly2->terms[poly2->degree].coefficient;
		int exponent  = remainder->degree - poly2->degree;
		
		for (int i = 0; i <= poly2->degree; i++) {
			remainder->terms[remainder->degree - poly2->degree + i].coefficient -= coefficient * poly2->terms[i].coefficient;
			remainder->terms[remainder->degree - poly2->degree + i].exponent  = exponent + poly2->terms[i].exponent;
		}
		
		remainder->degree--;
	}
	
	return remainder;
}

/*
	����� mod ����������ǳɻ��� 

Poly* poly_mod_cycle(Poly* poly1, Poly* poly2) {
	if (poly1->degree < poly2->degree)
		return poly_clone(poly2);
				
	int degree = poly1->degree - poly2->degree;
	Poly* remainder  = poly_create(degree);			// ��
	
	if (degree > 0)
		poly_term(remainder,  0 - poly1->terms[poly1->degree].coefficient, degree);
	else
		poly_term(remainder,  0 - poly1->terms[poly1->degree].coefficient, degree);
	
	return remainder;
}*/

/*
	����ʽϵ��ȡģ 
	poly������ʽ
	t��ϵ������ 
*/ 
Poly* poly_mod_coefficient(Poly *poly, int t) {
	int degree = poly->degree;
	Poly* poly3 = poly_create(degree);
	
	for (int i=0; i<=degree; i++) {
		int coefficient = poly->terms[i].coefficient % t;
		if (coefficient > (t/2.0)) coefficient -= t;
		else if(coefficient <= (t/2.0) * (-1))	coefficient += t;
		poly_term(poly3, coefficient, i);
	}
	return poly3;
}

/*
	����ʽȡ����ʽģ 
	poly������ʽ
	d������x^d+1�Ķ���ʽ�����е�d 
*/ 
Poly* poly_mod_poly(Poly *poly, int d) {
	int degree = poly->degree;
	Poly* poly3 = poly_create(degree);
	for(int i=0; i<d; i++){
		poly_term(poly3, 0, i);
	}
	
	for(int i=0; i<=degree; i++){
		int tmp = i % d;
		if((i / d) % 2)	poly3->terms[tmp].coefficient += poly->terms[i].coefficient * (-1);
		else poly3->terms[tmp].coefficient += poly->terms[i].coefficient; 
	}
	
	return poly3;
}

/*
	����ʽģ�� 
	poly1������ʽ1
	poly2������ʽ2
	d�� ����x^d+1�Ķ���ʽ�����е�d 
	t�� 
*/
Poly *poly_mod_add(Poly *poly1, Poly *poly2, int d, int t) {
	Poly* poly3 = poly_add(poly1, poly2);
	poly3 = poly_mod_poly(poly3, d);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}

/*
	����ʽģ�� 
	poly1������ʽ1
	poly2������ʽ2
	d�� ����x^d+1�Ķ���ʽ�����е�d 
	t�� 
*/
Poly *poly_mod_sub(Poly *poly1, Poly *poly2, int d, int t) {
	Poly* poly3 = poly_sub(poly1, poly2);
	poly3 = poly_mod_poly(poly3, d);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}

/*
	����ʽģ�� 
	poly1������ʽ1
	poly2������ʽ2
	d�� ����x^d+1�Ķ���ʽ�����е�d 
	t�� 
*/
Poly *poly_mod_mul(Poly *poly1, Poly *poly2, int d, int t) {
	Poly* poly3 = poly_mul(poly1, poly2);
	poly3 = poly_mod_poly(poly3, d);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}

Poly *poly_coefficient_mul(Poly *poly, int a) {
	int degree = poly->degree;
	Poly* poly3 = poly_create(degree);
	
	for (int i=0; i<=poly->degree; i++) {
		poly_term(poly3, poly->terms[i].coefficient * a, i);
	}

	return poly3;
}

Poly *poly_mod_coefficient_mul(Poly *poly, int a, int t) {
	Poly* poly3 = poly_coefficient_mul(poly, a);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}

Poly *poly_rounding_div(Poly *poly, double a) {
	int degree = poly->degree;
	Poly* poly3 = poly_create(degree);
	
	for (int i=0; i<=poly->degree; i++) {
		double tmp = poly->terms[i].coefficient / a;
		int coefficient = tmp > 0 ? (int)(tmp + 0.5) : (int)(tmp - 0.5);
		
		printf("i=%d c=%d\n", i, coefficient);
		poly_term(poly3, coefficient, i);
	}

	return poly3;
}

Poly *poly_mod_rounding_div(Poly *poly, double a, int t) {
	Poly* poly3 = poly_rounding_div(poly, a);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}
