#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"
#include "Homomorphic.h"

PolyPairs* homo_add(PolyPairs* a, PolyPairs* b, int d, int q) {
	Poly* c0 = poly_mod_add(a->poly0, b->poly0, d, q);
	Poly* c1 = poly_mod_add(a->poly1, b->poly1, d, q);
	
	PolyPairs* c = polypairs_create(c0, c1);
	
	return c;
}
