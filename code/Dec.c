#include <stdio.h>
#include <stdlib.h>

#include "Poly.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"

Poly* decryption(PolyArray* ct, Poly* s, int d, int t, int q) {
	Poly* poly3 = poly_create(1);
	
	int length = 0;
	
	for(int i=0; i<ct->size; i++){
		if(ct->polys[i]) {			
			Poly* tmp = NULL;
			for(int j=0; j<i; j++){
				if(!tmp) tmp = poly_clone(s);
				else tmp = poly_mod_mul(tmp, s, d, q); 
			}
			if(!tmp) poly3 = poly_mod_add(poly3, ct->polys[i], d, q);
			else poly3 = poly_mod_add(poly3, poly_mod_mul(ct->polys[i], tmp, d, q) , d, q);
		}
	}
	
	Poly* poly4 = poly_mod_round_div(poly3, (double)q/t, t);
	
	poly_free(poly3);
	
	return poly4;
}
