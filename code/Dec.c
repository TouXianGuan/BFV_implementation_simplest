#include <stdio.h>
#include <stdlib.h>

#include "Poly.h"
#include "PolyArray.h"
#include "Key.h"
#include "Enc.h"
#include "Dec.h"

Poly* decryption(PolyArray* ct, Poly* s, int d, int t, int q) {
	Poly* poly3 = NULL; 
	
	int length = 0;
	
	for(int i=0; i<ct->size; i++){
		if(ct->polys[i]) {			
			Poly* tmp = ct->polys[i];
			for(int j=0; j<i; j++){
					tmp = poly_mod_mul(tmp, s, d, q);
			}
			if(!poly3)	poly3 = poly_clone(tmp);
			else	poly3 = poly_mod_add(poly3, tmp, d, q);
			poly_print(poly3, 1);
		}
	}
	
	Poly* poly4 = poly_mod_round_div(poly3, (double)q/t, t);
	
	poly_free(poly3);
	
	return poly4;
}
