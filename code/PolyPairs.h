// 定义多项式对数据类型
typedef struct {
	Poly *poly0;
	Poly *poly1;
} PolyPairs;

// 创建一个多项式对。 
PolyPairs* polypairs_create(Poly* poly0, Poly* poly1);

// 销毁一个多项式对。 
void polypairs_free(PolyPairs* this);

// 在控制台输出多项式对。
void polypairs_print(PolyPairs*, int order);
