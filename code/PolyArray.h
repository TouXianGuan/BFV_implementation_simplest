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
