// �������ʽ����������
typedef struct {
	int size;
	Poly **polys;
} PolyArray;

// ����һ������ʽ�顣 
PolyArray* polyarray_create();

// ����һ������ʽ�顣 
void polyarray_free(PolyArray* this);

// �����ʽ�������һ������ʽ�� 
void polyarray_poly(PolyArray*, Poly*, int);

// �ڿ���̨�������ʽ�顣
void polyarray_print(PolyArray*, int order);
