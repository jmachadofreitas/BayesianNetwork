#include<stdio.h>
#include<stdlib.h>
#include"amostra.h"

amostra emptyS() {
	amostra a;
	a.matriz = NULL;
	a.num_l = 0;
	a.num_c = 0;
	return a;
}

amostra add(int* v, amostra a) {

	int i = length(a);

	if (i == 0) {
		a.matriz = (int**) malloc(sizeof(int*));
		a.matriz[i] = v;
		a.num_l++;
	} else {
		a.matriz = realloc(a.matriz, (i + 1) * sizeof(int*));
		a.matriz[i] = v;
		a.num_l++;
	}
	return a;
}

int length(amostra a) {
	int l = a.num_l;
	return l;
}

int* element(amostra a, int i) {
	int* v = a.matriz[i];
	return v;
}

int count(amostra a, int* var, int* val, int comp) {

	int i = 0, r = 0, j;
	while (i < length(a)) {
		j = 0;
		while (j < comp && a.matriz[i][var[j]] == val[j]) {

			if (j == comp - 1) {
				r++;
			}
			j++;

		}
		i++;
	}
	return r;
}

amostra join(amostra a1, amostra a2) {

	int i = 0, l2 = length(a2), l1 = length(a1);
	a1.matriz = (int**) realloc(a1.matriz, (l1 + l2) * sizeof(int*));
	a1.num_l = (l1 + l2);

	while (i < l2) {

		a1.matriz[l1] = a2.matriz[i];
		i++;
		l1++;
	}
	free(a2.matriz);
	return a1;
}

int* maximos(amostra a) {
	int j = 0, i;
	int* max = (int*) malloc(a.num_c * sizeof(int));
	while (j < a.num_c) {
		i = 0;
		max[j] = 0;
		while (i < length(a)) {
			if (max[j] < a.matriz[i][j]) {
				max[j] = a.matriz[i][j];
			}
			i++;
		}
		j++;
	}
	return max;

}

amostra read(char* dados) {
	amostra a = emptyS();
	int i, j, k,l;
	char linha[100], aux[3];

	FILE* pf = fopen(dados, "r");
	fscanf(pf, "%s", linha);

	i = 0;
	while (linha[i] != '\0') {
		if (linha[i] == ',') {
			a.num_c++;
		}
		i++;
	}
	a.num_c = a.num_c + 1;

	rewind(pf);

	while (fscanf(pf, "%s", linha) != EOF) {

		int* vec = (int*) malloc(a.num_c * sizeof(int));
		i = 0;
		j = 0;
		while (linha[i] != '\0') {
			k = 0;

			while (linha[i] != ',' && linha[i] != '\0') {
				aux[k] = linha[i];
				i++;
				k++;
			}
			if (linha[i] != '\0') {
				i++;
			}

			vec[j] = atoi(aux);

			l=0;
			while(l<3){
			aux[l]='\0';
			l++;
			}

			j++;

		}
		a = add(vec, a);


	}
	fclose(pf);
	return a;
}
