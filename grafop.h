#include<stdio.h>
#include"amostra.h"
#include"grafoo.h"

struct grafop {
	double** m_adj;
	int num_n;

};

typedef struct grafop grafop;

grafop discWD(int);
grafop add_Wedge(grafop, int, int, double);
int* MST(grafop);
int* pesado(grafop, lista);
/*-----------2ªParte-------------*/
grafop pesos(amostra);
double IM(amostra, int, int, int*);

