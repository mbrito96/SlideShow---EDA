typedef struct _nodo {
	void * elemento;
	struct  _nodo * proximo;
}nodeType;

typedef struct {
	nodeType * firstElement;
	unsigned int elementSize;
	unsigned int elementCount;
}headerType;

typedef headerType * listType;

typedef enum { FALSE, TRUE } bool_t;