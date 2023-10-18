#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Poly.h"

/*
	创建一个多项式。
	degree: 多项式最高幂次 
*/
Poly* poly_create(unsigned int degree) {
	Poly* this = (Poly*)malloc(sizeof(Poly));
	this->degree = degree;
	this->terms = (PolyTerm*)calloc(degree+1, sizeof(PolyTerm)); 
}

/*
	销毁一个多项式。
	this:	被销毁的多项式指针 
*/
void poly_free(Poly* this) {
	free(this->terms);
	free(this);
}

/*
	向多项式中添加一个项。
	this:			目标多项式 
	coefficient:	添加项的系数
	exponent:		添加项的幂次 
*/
void poly_term(Poly* this, int coefficient, int exponent) {
	// 如果添加项的幂次高于多项式最高幂次，则直接返回 
	if (exponent > this->degree) return;
	
	// 在系数恰当位置记录系数值
	this->terms[exponent].coefficient = coefficient;
	this->terms[exponent].exponent = exponent;
}

Poly* poly_clone(Poly *this) {
	Poly* that = poly_create(this->degree);
	memcpy(that->terms, this->terms, (this->degree + 1) * sizeof(PolyTerm));
		
	return that;
}

/*
	在控制台输出多项式。
	this:	要输出的多项式
	order:	输出顺序。1: 从高次幂到低次幂，否则相反 
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
	多项式相加。
	poly1:	被加数
	poly2:	加数
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
	多项式相减。
	poly1:	被减数
	poly2:	减数
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
	多项式相乘。 
	poly1:	被乘数
	poly2:	乘数
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
	多项式相除。 
	poly1:	被除数
	poly2:	除数

Poly* poly_div(Poly* poly1, Poly* poly2) {
	if (poly1->degree < poly2->degree)
		return poly_create(0);
		
	int degree = poly1->degree - poly2->degree;
	Poly* quotient = poly_create(degree);			// 商 
	Poly* remainder  = poly_clone(poly1);			// 余
	
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
	多项式模除。 
	poly1:	被除数
	poly2:	除数

Poly* poly_mod(Poly* poly1, Poly* poly2) {
	if (poly1->degree < poly2->degree)
		return poly_clone(poly2);
		
	int degree = poly1->degree - poly2->degree;
	Poly* remainder  = poly_clone(poly1);			// 余
	
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
	上面的 mod 方法好像就是成环的 

Poly* poly_mod_cycle(Poly* poly1, Poly* poly2) {
	if (poly1->degree < poly2->degree)
		return poly_clone(poly2);
				
	int degree = poly1->degree - poly2->degree;
	Poly* remainder  = poly_create(degree);			// 余
	
	if (degree > 0)
		poly_term(remainder,  0 - poly1->terms[poly1->degree].coefficient, degree);
	else
		poly_term(remainder,  0 - poly1->terms[poly1->degree].coefficient, degree);
	
	return remainder;
}*/

/*
	多项式系数取模 
	poly：多项式
	t：系数基底 
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
	多项式取多项式模 
	poly：多项式
	d：形如x^d+1的多项式基底中的d 
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
	多项式模加 
	poly1：多项式1
	poly2：多项式2
	d： 形如x^d+1的多项式基底中的d 
	t： 
*/
Poly *poly_mod_add(Poly *poly1, Poly *poly2, int d, int t) {
	Poly* poly3 = poly_add(poly1, poly2);
	poly3 = poly_mod_poly(poly3, d);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}

/*
	多项式模减 
	poly1：多项式1
	poly2：多项式2
	d： 形如x^d+1的多项式基底中的d 
	t： 
*/
Poly *poly_mod_sub(Poly *poly1, Poly *poly2, int d, int t) {
	Poly* poly3 = poly_sub(poly1, poly2);
	poly3 = poly_mod_poly(poly3, d);
	poly3 = poly_mod_coefficient(poly3, t);
	return poly3;
}

/*
	多项式模乘 
	poly1：多项式1
	poly2：多项式2
	d： 形如x^d+1的多项式基底中的d 
	t： 
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
