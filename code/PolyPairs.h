// �������ʽ����������
typedef struct {
	Poly *poly0;
	Poly *poly1;
} PolyPairs;

// ����һ������ʽ�ԡ� 
PolyPairs* polypairs_create(Poly* poly0, Poly* poly1);

// ����һ������ʽ�ԡ� 
void polypairs_free(PolyPairs* this);

// �ڿ���̨�������ʽ�ԡ�
void polypairs_print(PolyPairs*, int order);
