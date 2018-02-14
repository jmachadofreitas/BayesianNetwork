#include<stdio.h>
#include"grafop.h"

struct bayes {
	double** tensor;
	int num_n;
	int* pai;
	int* max;
};

typedef struct bayes bayes;

bayes newBN(int*, amostra, char*);
double prob(bayes, int*);
int indice(int, int, int, int*);

bayes unserialize(char*);

