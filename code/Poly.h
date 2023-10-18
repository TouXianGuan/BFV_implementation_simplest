// 定义多项式数据类型
typedef struct {
	int coefficient;					// 系数 
	int exponent;						// 幂次 
} PolyTerm;

typedef struct {
	unsigned int	degree;				// 多项式的最高幂次 
	PolyTerm*		terms;				// 多项式的项，数组长度为 degree + 1 
} Poly;

// 创建一个多项式。 
Poly* poly_create(unsigned int);

// 销毁一个多项式。 
void  poly_free(Poly*);

// 向多项式中添加一个项。 
void poly_term(Poly*, int, int);

// 复制多项式。 
Poly* poly_clone(Poly*); 

// 在控制台输出多项式。
void poly_print(Poly*, int order);

// 多项式相加。 
Poly* poly_add(Poly*, Poly*);

// 多项式相减。 
Poly* poly_sub(Poly*, Poly*);

// 多项式相乘。 
Poly* poly_mul(Poly*, Poly*); 

/*// 多项式相除。 
Poly* poly_div(Poly*, Poly*); 

// 多项式模除。 
Poly* poly_mod(Poly*, Poly*); 
 
// 多项式模除成环。 
Poly* poly_mod_cycle(Poly*, Poly*); */

// 多项式系数取模 
Poly* poly_mod_coefficient(Poly *poly, int t);

//多项式取多项式模 
Poly* poly_mod_poly(Poly *poly, int d);

//多项式模加 
Poly *poly_mod_add(Poly *poly1, Poly *poly2, int d, int t);

//多项式模减 
Poly *poly_mod_sub(Poly *poly1, Poly *poly2, int d, int t);

//多项式模乘 
Poly *poly_mod_mul(Poly *poly1, Poly *poly2, int d, int t);

//多项式系数乘法 
Poly *poly_coefficient_mul(Poly *poly, int a);

//多项式模系数乘法 
Poly *poly_mod_coefficient_mul(Poly *poly, int a, int t);

//多项式近似系数除法 
Poly *poly_rounding_div(Poly *poly, double a);

//多项式模近似系数除法 
Poly *poly_mod_round_div(Poly *poly, double a, int t);
