// 均匀生成随机多项式 
Poly* poly_rand(int degree, int range);

//根据离散高斯分布生成多项式 
Poly* poly_Gaussian(int degree, int range);

// 生成多项式a 
Poly* gen_a(int degree, int range);

// 生成私钥 
Poly* pri_key(int degree);

// 生成公钥pk的第0项 
Poly* pk0(Poly* a, Poly* s, Poly* e, int d, int q);

// 生成公钥pk的第1项
Poly* pk1(Poly* a, int d, int q);

// 生成公钥
PolyArray* pub_key(Poly* s, int d, int q);
