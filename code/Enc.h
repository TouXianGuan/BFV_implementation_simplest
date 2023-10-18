//生成密文第0项 
Poly* ct0(PolyPairs* pk, Poly* m, int d, int t, int q, Poly* e1, Poly* u);

//生成密文第2项 
Poly* ct1(PolyPairs* pk, int d, int q, Poly* e2, Poly* u);

//生成密文
PolyPairs ct(PolyPairs* pk, Poly* m, int d, int t, int q); 
