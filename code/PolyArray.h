// 定义多项式组数据类型
typedef struct {
	int size;
	Poly **polys;
} PolyArray;

// 创建一个多项式组。 
PolyArray* polyarray_create();

// 销毁一个多项式组。 
void polyarray_free(PolyArray* this);

// 向多项式组中添加一个多项式。 
void polyarray_poly(PolyArray*, Poly*, int);

// 在控制台输出多项式组。
void polyarray_print(PolyArray*, int order);

// 多项式组相加
PolyArray* polyarray_add(PolyArray* pa1, PolyArray* pa2, int d, int t);

// 多项式组相减 
PolyArray* polyarray_sub(PolyArray* pa1, PolyArray* pa2, int d, int t); 

// 多项式组相乘 
PolyArray* polyarray_mul(PolyArray* pa1, PolyArray* pa2, int d, int t); 

// 多项式组系数相乘 
PolyArray *polyarray_coe_mul(PolyArray *pa, int a, int t); 

// 多项式组近似系数除法
PolyArray *polyarray_round_div(PolyArray *pa, double a, int t); 
