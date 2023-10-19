#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Poly.h"
#include "PolyPairs.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"
#include "Homomorphic.h"

PolyArray* homo_add(PolyArray* a, PolyArray* b, int d, int q) {
	PolyArray* c = polyarray_add(a, b, d, q);
	
	return c;
}
