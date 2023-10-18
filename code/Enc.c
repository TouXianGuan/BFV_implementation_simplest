Poly* ct0(PolyPairs* pk, Poly* m, int d, int t, int q, Poly* e1, Poly* u) {
	//pk0 * u
	Poly *poly1 = poly_mod_mul(pk->poly0, u, d, q);
	
	//pk0 * u + e1
	Poly *poly2 = poly_mod_add(poly1, e1, d, q);
	
	//(q / t) * m
	Poly *poly3 = poly_mod_coefficient_mul(m, q/t, q);
	
	//pk0 * u + e1 + (q / t) * m
	Poly *poly4 = poly_mod_add(poly2, poly3, d, q);
	
	return poly4;	
}
