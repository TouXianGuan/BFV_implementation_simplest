#include <stdio.h>
#include <stdlib.h>

#include "Poly.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"

Poly* ct0_add_ct1_mul_s(PolyArray* ct, Poly* s, int d, int q) {
	//ct1*s
	Poly *poly1 = poly_mod_mul(ct->polys[1], s, d, q);
	
	//ct0+ct1*s
	Poly *poly2 = poly_mod_add(poly1, ct->polys[0], d, q);
	
	poly_free(poly1);
	
	return poly2;
}

Poly* m_dec(PolyArray* ct, Poly* s, int d, int t, int q) {
	//ct0+ct1*s 
	Poly *poly1 = ct0_add_ct1_mul_s(ct, s, d, q);
	
	//(ct0+ct1*s)/(q/t)
	Poly *poly2 = poly_mod_round_div(poly1, (double)q/t, t);
	
	poly_free(poly1);
	
	return poly2;
}
