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

PolyArray* homo_mul(PolyArray* a, PolyArray* b, int d, int t, int q) {
	int size = (a->size >= b->size) ? a->size : b->size;
	PolyArray* pa3 = polyarray_create();
	
	for(int i=0; i<size; i++){
		if(a->polys[i]){
			for(int j=0; j<size; j++){
				if(b->polys[j]) {
					Poly* tmp = poly_mul(a->polys[i], b->polys[j]);
					tmp = poly_mod_poly(tmp, d);
					if(!pa3->polys[i+j]) polyarray_poly(pa3, tmp, i+j);
					else poly_add(pa3->polys[i+j], tmp);
				}
			}
		}
	}
	
	PolyArray* pa4 = polyarray_round_div(pa3, (double)q/t, q);
	
	return pa4;
} 
