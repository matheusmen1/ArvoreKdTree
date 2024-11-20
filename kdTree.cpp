#define K 2
#define TF 100
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio2.h>
#include <ctype.h>
#include <math.h>
#include <windows.h>
#include "TADPilhakdTree.h"
#include<time.h>
struct listaPontos{
	int ponto[K];
	struct listaPontos *prox;
};
typedef listaPontos ListaPontos;
kdTree *criaNo(int ponto[K])
{
	kdTree *Caixa;
	Caixa = (kdTree*)malloc(sizeof(kdTree));
	Caixa->dir = NULL;
	Caixa->esq = NULL;
	Caixa->ponto[0] = ponto[0];
	Caixa->ponto[1] = ponto[1];
	
	return Caixa;
}
ListaPontos *criaNoLista(int ponto[K])
{
	ListaPontos *NC;
	NC = (ListaPontos*)malloc(sizeof(ListaPontos));
	NC->prox = NULL;
	NC->ponto[0] = ponto[0];
	NC->ponto[1] = ponto[1];
	
	return NC;
}
void ordenarEixo(int pontos[TF][K] , int d, int ini,int fim) //bubblesort
{

	for (int i = ini; i <= fim-1; i++)
	{
		
		for (int j = i+1; j <= fim; j++)
		{
			
			if (pontos[i][d] > pontos[j][d])
			{
				int aux[K];
			
				aux[0] = pontos[i][0];
				aux[1] = pontos[i][1];
	
				pontos[i][0] = pontos[j][0];
				pontos[i][1] = pontos[j][1];
				
				pontos[j][0] = aux[0];
				pontos[j][1] = aux[1];
				
			}	
			
		}
	
	}
	
}
void insereBalanceadaR(kdTree **raiz, int pontos[TF][K],int ini, int fim ,int n)
{
	int d, meio;
	if (ini <= fim)
	{
	
		d=n%K;
		ordenarEixo(pontos,d, ini, fim);
		meio = (ini+fim)/2;
		
		*raiz = criaNo(pontos[meio]);
		
		insereBalanceadaR(&(*raiz)->esq, pontos, ini,meio-1,n+1);
		insereBalanceadaR(&(*raiz)->dir, pontos, meio+1,fim,n+1);
	}
}

void insereR(kdTree **raiz, int ponto[K], int n)
{
	int d;
	if (*raiz==NULL)
		*raiz=criaNo(ponto);
	else
	{
		d=n%K;
		if (ponto[d] < (*raiz)->ponto[d])
			insereR(&(*raiz)->esq, ponto, n+1);
		else
			insereR(&(*raiz)->dir, ponto, n+1);
	}
}
void buscarPontos(kdTree *raiz ,int coordenada[K], int raio, ListaPontos **L)
{

	int distancia;
	ListaPontos *aux ,*NC, *ant;
	Pilha *P;
	init(&P);
	push(&P, raiz);
	while(!isEmpty(P))
	{
		if (raiz != NULL)
		{
			pop(&P, &raiz);
			while(raiz != NULL)
			{
				distancia = sqrt(pow(coordenada[0]- raiz->ponto[0],2) + pow(coordenada[1] - raiz->ponto[1],2));
				if (distancia <= raio) // esta dentro do raio
				{
					NC = criaNoLista(raiz->ponto);
					
					if (*L == NULL)
						*L = NC;
					else
					{
						aux = *L;
						while(aux != NULL && aux->ponto[0] != raiz->ponto[0] && aux->ponto[1] != raiz->ponto[1])
						{
							ant = aux;
							aux = aux->prox;
						}
						if (aux == NULL)
						{
							ant->prox = NC;
	;					}
					}
					
					// insere na lista	
				}
				push(&P, raiz);
				raiz = raiz->dir;
				
			}
		}
		pop(&P, &raiz);
		raiz = raiz->esq;
		if (raiz != NULL)
			push(&P, raiz);
		
	}


}
void executar(kdTree **raiz)
{
	srand(time(NULL));
	int x,y, pontos[TF][K],i, TL;
	TL = rand()%20;
	i = 0;
	while(i < TL)
	{
		x = rand()%100;
		y = rand()%100;
		pontos[i][0] = x;
		pontos[i][1] = y;
		i++;
	}
	insereBalanceadaR(raiz, pontos, 0, i-1, 0);
//	int x, y, TL = 0, pontos[TF][K];
//	printf ("digite o valor de x e y\n");
//	scanf ("%d %d", &x, &y);
//	while(x > 0 && y > 0 && TL < TF)
//	{
//		pontos[TL][0] = x;
//		pontos[TL][1] = y;
//	
//		TL++;
//		printf ("digite o valor de x e y\n");
//		scanf ("%d %d", &x, &y);
//		
//		
//	}
//	insereBalanceadaR(raiz, pontos, 0, TL-1, 0);
	
}
void exibeh(kdTree *raiz)
{
	static int n = -1;
	if (raiz != NULL)
	{
		n++;
		exibeh(raiz->dir);
		for (int i =0; i < 5*n; i++)
			printf (" ");
		printf ("(%d, %d)\n",raiz->ponto[0], raiz->ponto[1]);
		exibeh(raiz->esq);
		n--; 
		
		
	}
	
}

void ExibeVertical(kdTree *raiz, int c, int l) {
    
	if (raiz != NULL)
    {
    	ExibeVertical(raiz->esq, c - 1, l + 1);
   		gotoxy(c * 6, l);  
    	printf("(%d, %d)", raiz->ponto[0], raiz->ponto[1]);
  		ExibeVertical(raiz->dir, c + 1, l + 1);
    }   

}
void exibirPontos(ListaPontos *L, int coordenada[K], int raio)
{
	if (L != NULL)
	{
		//printf ("-----------------------------------------------------------\n");
		printf ("\n\n");
		printf ("\t\tCoordenadas: (%d, %d)\tRaio: %d\n", coordenada[0],coordenada[1], raio);
		printf ("-----------------------------------------------------------\n\n");
		while(L != NULL)
		{
			printf ("Pontos: (%d, %d)\n", L->ponto[0], L->ponto[1]);
			L=L->prox;
		}
		printf ("\n-----------------------------------------------------------\n");
	}
	else
		printf ("\nLista Vazia");
}
int main(void)
{
	
	int coordenada[K], raio;
	kdTree *raiz;
	ListaPontos *Lista;
	Lista = NULL;
	raiz = NULL;
	
	executar(&raiz);
	
	//exibeh(raiz);
	ExibeVertical(raiz, 5,10);
	
	// constantes
	coordenada[0] = rand()%100; 
	coordenada[1] = rand()%100;
	raio = rand()%100;
	
	// buscar pontos
	buscarPontos(raiz, coordenada, raio, &Lista);
	exibirPontos(Lista, coordenada, raio);

	
}
