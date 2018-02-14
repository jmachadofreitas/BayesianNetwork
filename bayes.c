#include<stdio.h>
#include<stdlib.h>
#include"bayes.h"

bayes newBN(int* pai, amostra a, char* nome) {

	/*a classe ser a ultima variável de cada vector da amostra e a raiz é sempre
	 * a primeira, como foi definido no MST */

	bayes BN;

	BN.num_n = a.num_c;
	BN.max = maximos(a);
	BN.pai = pai;
	BN.tensor = (double**) malloc(a.num_c * sizeof(double));
	lista list = new();
	int i, j, k, l, aux1_var[1], aux1_val[1], aux2_var[2] = { a.num_c - 1, 0 },
			aux2_val[2], aux4_var[3], aux4_val[3], dom[3], ind;
	aux1_var[0] = a.num_c - 1;

	/*-----------------------------------------Serialize-----------------------------------------*/

	FILE *pf = fopen(nome, "w");

	fprintf(pf, "%d\n", BN.num_n);
	i = 0;
	while (i < BN.num_n - 1) {
		fprintf(pf, "%d\n", pai[i]);
		i++;
	}
	i = 0;
	while (i < BN.num_n) {
		fprintf(pf, "%d\n", BN.max[i]);
		i++;
	}

	/*--------------------------------------Tensor 1ª Ordem----------------------------------------*/

	BN.tensor[a.num_c - 1] = (double*) malloc(
			(BN.max[a.num_c - 1] + 1) * sizeof(double));

	i = 0;
	while (i <= BN.max[a.num_c - 1]) {
		aux1_val[0] = i;

		BN.tensor[a.num_c - 1][i] = (count(a, aux1_var, aux1_val, 1) + 0.5)
				/ (a.num_l + 0.5 * (BN.max[a.num_c - 1] + 1));

		//printf("P(C=%d)=%f\n", i, BN.tensor[a.num_c - 1][i]);

		fprintf(pf, "%lf\n", BN.tensor[a.num_c - 1][i]);/*SERIALIZE*/

		i++;
	}

	/*--------------------------------------Tensor de 2ª ordem-------------------------------------*/

	BN.tensor[0] = (double*) malloc(
			(BN.max[a.num_c - 1] + 1) * (BN.max[0] + 1) * sizeof(double));

	i = 0;
	while (i <= BN.max[a.num_c - 1]) {
		j = 0;
		aux2_val[0] = i;
		aux1_val[0] = i;
		while (j <= BN.max[0]) {
			aux2_val[1] = j;
			BN.tensor[0][i * (BN.max[0] + 1) + j] = (count(a, aux2_var,
					aux2_val, 2) + 0.5)
					/ (count(a, aux1_var, aux1_val, 1) + 0.5 * (BN.max[0] + 1));

			/*printf("P(RAIZ=%d|C=%d)=%f\n", j, i,
			 BN.tensor[0][i * (BN.max[0] + 1) + j]);*/

			fprintf(pf, "%lf\n", BN.tensor[0][i * (BN.max[0] + 1) + j]);/*SERIALIZE*/

			j++;

		}
		i++;
	}

	/*-------------------------------------Tensores de 3ª ordem------------------------------------*/

	j = 1;
	while (j < a.num_c - 1) {
		BN.tensor[j] = (double*) malloc(
				(BN.max[a.num_c - 1] + 1) * (BN.max[j] + 1)
						* (BN.max[pai[j]] + 1) * sizeof(double));
		j++;
	}
	j = 1;
	while (j < a.num_c - 1) {
		i = 0;
		while (i < BN.max[a.num_c - 1] + 1) {
			aux4_var[0] = a.num_c - 1;
			aux4_val[0] = i;
			aux2_var[0] = a.num_c - 1;
			aux2_val[0] = i;
			k = 0;

			while (k < BN.max[j] + 1) {
				aux4_var[1] = j;
				aux4_val[1] = k;

				l = 0;
				while (l < BN.max[pai[j]] + 1) {
					aux4_var[2] = pai[j];
					aux4_val[2] = l;
					aux2_var[1] = pai[j];
					aux2_val[1] = l;

					dom[0] = BN.max[a.num_c - 1] + 1;
					dom[1] = BN.max[j] + 1;
					dom[2] = BN.max[pai[j]] + 1;

					ind = indice(i, k, l, dom);
					BN.tensor[j][ind] = (count(a, aux4_var, aux4_val, 3) + 0.5)
							/ (count(a, aux2_var, aux2_val, 2)
									+ 0.5 * (BN.max[j] + 1));
					//printf("P(VAR[%d]=%d|PAI[%d]=%d,C=%d)=%f\n", j, k, j, l, i,BN.tensor[j][ind]);

					fprintf(pf, "%lf\n", BN.tensor[j][ind]);/*SERIALIZE*/

					l++;
				}
				k++;

			}
			i++;
		}
		j++;
	}

	fclose(pf);/*SERIALIZE*/

	return BN;
}

double prob(bayes BN, int* vec) {
	double P, P1, P2, P3 = 1;
	int i = 1, dom[3], ind;
	P1 = BN.tensor[BN.num_n - 1][vec[BN.num_n - 1]];
	P2 = BN.tensor[0][vec[BN.num_n - 1] * (BN.max[0] + 1) + vec[0]];
	while (i < BN.num_n - 1) {
		dom[0] = BN.max[BN.num_n - 1] + 1;
		dom[1] = BN.max[i] + 1;
		dom[2] = BN.max[BN.pai[i]] + 1;
		ind = indice(vec[BN.num_n - 1], vec[i], vec[BN.pai[i]], dom);
		P3 *= BN.tensor[i][ind];
		i++;
	}
	//printf("P1=%f P2=%f P3=%f\n", P1, P2, P3);
	P = P1 * P2 * P3;
	return P;
}

/*--------------------Auxiliar-------------------------*/

int indice(int i, int k, int l, int* dom) {
	int pos[3] = { i, k, l };
	int aux = 0, ind = 0, prod = 1, j;
	while (aux < 3) {
		prod = 1;
		j = aux + 1;
		while (j < 3) {
			prod *= dom[j];
			j++;
		}
		ind += pos[aux] * prod;
		aux++;
	}
	return ind;
}

/*--------------------------------------------Unserialize-----------------------------------------*/

bayes unserialize(char* bayesnet) {

	FILE* pf = fopen(bayesnet, "r");

	int dom[3], ind, i, j, k, l;
	double d;
	bayes BN;

	fscanf(pf, "%d", &BN.num_n);

	BN.pai = (int*) malloc(sizeof(int) * BN.num_n);
	BN.max = (int*) malloc(sizeof(int) * BN.num_n);

	/*----------------------PAIS-----------------------------*/

	i = 0;
	while (i < BN.num_n - 1) {
		fscanf(pf, "%d", &BN.pai[i]);
		i++;
	}

	/*--------------------MAXIMOS----------------------------*/

	i = 0;
	while (i < BN.num_n) {
		fscanf(pf, "%d", &BN.max[i]);
		i++;
	}


	BN.tensor = (double**) malloc(BN.num_n * sizeof(double));

	/*--------------------TENSOR1---------------------------*/

	BN.tensor[BN.num_n - 1] = (double*) malloc(
			(BN.max[BN.num_n - 1] + 1) * sizeof(double));

	i = 0;
	while (i <= BN.max[BN.num_n - 1]) {
		fscanf(pf, "%lf", &BN.tensor[BN.num_n - 1][i]);

		i++;
	}

	/*--------------------TENSOR2---------------------------*/

	BN.tensor[0] = (double*) malloc(
			(BN.max[BN.num_n - 1] + 1) * (BN.max[0] + 1) * sizeof(double));

	i = 0;
	while (i <= BN.max[BN.num_n - 1]) {
		j = 0;
		while (j <= BN.max[0]) {

			fscanf(pf, "%lf", &BN.tensor[0][i * (BN.max[0] + 1) + j]);
			//o double tem 2 vezes mais precisão logo transformar um double em float dá erro
			// então faz-se longfloat, %lf, para se conseguir guardar um double num float.

			j++;

		}
		i++;
	}

	/*-----------------------TENSOR3----------------------------*/

	j = 1;

	while (j < BN.num_n - 1) {
		BN.tensor[j] = (double*) malloc(
				(BN.max[BN.num_n - 1] + 1) * (BN.max[j] + 1)
						* (BN.max[BN.pai[j]] + 1) * sizeof(double));
		j++;
	}

	j = 1;
	while (j < BN.num_n - 1) {
		i = 0;
		while (i < BN.max[BN.num_n - 1] + 1) {

			k = 0;

			while (k < BN.max[j] + 1) {

				l = 0;
				while (l < BN.max[BN.pai[j]] + 1) {

					dom[0] = BN.max[BN.num_n - 1] + 1;
					dom[1] = BN.max[j] + 1;
					dom[2] = BN.max[BN.pai[j]] + 1;

					ind = indice(i, k, l, dom);
					fscanf(pf, "%lf", &BN.tensor[j][ind]);

					l++;
				}
				k++;

			}
			i++;
		}
		j++;
	}

	fclose(pf);
	return BN;
}
