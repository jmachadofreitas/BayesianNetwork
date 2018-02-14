#include<stdio.h>
#include"lista.h"

struct grafoo{
	int** m_adj;
	int num_n;
};

typedef struct grafoo grafoo;

grafoo disc(int);
grafoo add_edge(grafoo,int,int);
lista parents(grafoo,int);

/*Funções auxiliares lista*/

lista new();
bool pert(lista, int);
lista insert(lista,int);
lista elim(lista, int);









