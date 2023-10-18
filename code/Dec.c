#include <stdio.h>
#include <stdlib.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"

Poly* ct0_add_ct1_mul_s (PolyPairs* ct, Poly* s, int d, int q) {
	//ct1*s
	Poly *poly1 = poly_mod_mul(ct->poly1, s, d, q);
	
	//ct0+ct1*s
	Poly *poly2 = poly_mod_add(poly1, ct->poly0, d, q);
	
	return poly2;
}
