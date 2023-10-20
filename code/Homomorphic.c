#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Poly.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"
#include "Homomorphic.h"

PolyArray* homo_add(PolyArray* a, PolyArray* b, int d, int q) {
	PolyArray* c = polyarray_add(a, b, d, q);
	
	return c;
}

PolyArray* homo_mul(PolyArray* a, PolyArray*b, int d, int t, int q) {
	PolyArray* pa3 = polyarray_mul(a, b, d, q);
	
	PolyArray* pa4 = polyarray_coe_mul(pa3, q/t, q);
	
	polyarray_free(pa3);
	
	return pa4;
} 
