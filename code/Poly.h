// �������ʽ��������
typedef struct {
	int coefficient;					// ϵ�� 
	int exponent;						// �ݴ� 
} PolyTerm;

typedef struct {
	unsigned int	degree;				// ����ʽ������ݴ� 
	PolyTerm*		terms;				// ����ʽ������鳤��Ϊ degree + 1 
} Poly;

// ����һ������ʽ�� 
Poly* poly_create(unsigned int);

// ����һ������ʽ�� 
void  poly_free(Poly*);

// �����ʽ�����һ��� 
void poly_term(Poly*, int, int);

// ���ƶ���ʽ�� 
Poly* poly_clone(Poly*); 

// �ڿ���̨�������ʽ��
void poly_print(Poly*, int order);

// ����ʽ��ӡ� 
Poly* poly_add(Poly*, Poly*);

// ����ʽ����� 
Poly* poly_sub(Poly*, Poly*);

// ����ʽ��ˡ� 
Poly* poly_mul(Poly*, Poly*); 

/*// ����ʽ����� 
Poly* poly_div(Poly*, Poly*); 

// ����ʽģ���� 
Poly* poly_mod(Poly*, Poly*); 
 
// ����ʽģ���ɻ��� 
Poly* poly_mod_cycle(Poly*, Poly*); */

// ����ʽϵ��ȡģ 
Poly* poly_mod_coefficient(Poly *poly, int t);

//����ʽȡ����ʽģ 
Poly* poly_mod_poly(Poly *poly, int d);

//����ʽģ�� 
Poly *poly_mod_add(Poly *poly1, Poly *poly2, int d, int t);

//����ʽģ�� 
Poly *poly_mod_sub(Poly *poly1, Poly *poly2, int d, int t);

//����ʽģ�� 
Poly *poly_mod_mul(Poly *poly1, Poly *poly2, int d, int t);

//����ʽϵ���˷� 
Poly *poly_coefficient_mul(Poly *poly, int a);

//����ʽģϵ���˷� 
Poly *poly_mod_coefficient_mul(Poly *poly, int a, int t);

//����ʽ����ϵ������ 
Poly *poly_rounding_div(Poly *poly, double a);

//����ʽģ����ϵ������ 
Poly *poly_mod_round_div(Poly *poly, double a, int t);
