
struct kdtree{
	int ponto[K];	
	struct kdtree *dir, *esq;
};
typedef struct kdtree kdTree;

struct pilha{
	
	kdTree *raiz;
	char codigo[8];
	struct pilha *prox;
	
};
typedef struct pilha Pilha;
void init(Pilha **p)
{
	*p = NULL;
}
void push(Pilha **p, kdTree *raiz)
{
	Pilha *NC;
	NC = (Pilha*)malloc(sizeof(Pilha));
	NC->prox = NULL;
	NC->raiz = raiz;
	if(*p == NULL)
		*p = NC;
	else
	{
		NC->prox = *p;
		*p = NC;
	} 
	
}
void pop(Pilha **P, kdTree **x)
{
	
	Pilha *aux;
	aux = *P;
	*x = (*P)->raiz ;
	*P = (*P)->prox;
	free(aux);
	
}
char isEmpty(Pilha *p){
	
	return p == NULL;
}
