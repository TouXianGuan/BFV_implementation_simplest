// ���������������ʽ 
Poly* poly_rand(int degree, int range);

//������ɢ��˹�ֲ����ɶ���ʽ 
Poly* poly_Gaussian(int degree, int range);

// ���ɶ���ʽa 
Poly* gen_a(int degree, int range);

// ����˽Կ 
Poly* pri_key(int degree);

// ���ɹ�Կpk�ĵ�0�� 
Poly* pk0(Poly* a, Poly* s, Poly* e, int d, int q);

// ���ɹ�Կpk�ĵ�1��
Poly* pk1(Poly* a, int d, int q);

// ���ɹ�Կ
PolyArray* pub_key(Poly* s, int d, int q);
