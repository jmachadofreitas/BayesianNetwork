#include<stdio.h>


struct amostra{
int** matriz;
int num_l;
int num_c;
};

typedef struct amostra amostra;

amostra emptyS();
amostra add(int*,amostra);
int length(amostra);
int* element(amostra,int);
int count(amostra,int*,int*,int);
amostra join(amostra,amostra);


/*Auxiliar*/

int* maximos(amostra);

/*Ler Dados*/

amostra read(char*);

