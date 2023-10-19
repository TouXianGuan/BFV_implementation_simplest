// �������ʽ����������
typedef struct {
	int size;
	Poly **polys;
} PolyArray;

// ����һ������ʽ�顣 
PolyArray* polyarray_create();

// ����һ������ʽ�顣 
void polyarray_free(PolyArray* this);

// ����ʽ�����
PolyArray* polyarray_add(PolyArray* pa1, PolyArray* pa2, int d, int t);

// ����ʽ����� 
PolyArray* polyarray_sub(PolyArray* pa1, PolyArray* pa2, int d, int t); 

// ����ʽ����� 
PolyArray* polyarray_mul(PolyArray* pa1, PolyArray* pa2, int d, int t); 

// �����ʽ�������һ������ʽ�� 
void polyarray_poly(PolyArray*, Poly*, int);

// �ڿ���̨�������ʽ�顣
void polyarray_print(PolyArray*, int order);
