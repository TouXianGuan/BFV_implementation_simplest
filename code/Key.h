// ���������������ʽ 
Poly* poly_rand(int degree, int range);

// ���ɶ���ʽa 
Poly* gen_a(int degree, int range);

// ����˽Կ 
Poly* sk(int degree);

// ���ɹ�Կpk�ĵ�0�� 
Poly* pk0(Poly* a, Poly* s, Poly* e, int d, int q);

// ���ɹ�Կpk�ĵ�1��
Poly* pk1(Poly* a, int d, int q);

// ���ɹ�Կ
PolyPairs* pk(int d, int q);
