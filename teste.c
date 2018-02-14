#include<stdio.h>
#include<stdlib.h>
#include"bayes.h"


int main() {

	/*if (argc == 2)
	 printf("The argument supplied is %s\n", argv[1]);
	 else if (argc > 2)
	 printf("Too many arguments supplied.\n");
	 else
	 printf("One argument expected.\n");
	 }*/

	/*
	 argc contains the number of command-line arguments passed to the main
	 program and
	 argv[] is an array of pointers-to-char, each element of which points
	 to a passed command-line argument.
	 */

	printf("TESTE DA AMOSTRA\n");
	int v[4], i, j, k, l;
	int u[4] = { 4, 2, 3, 0 };
	int* pai;
	double probabilidade1, probabilidade2;
	v[0] = 0;
	v[1] = 1;
	v[2] = 2;
	v[3] = 1;
	/*
	 amostra a = emptyS();
	 a.num_c = 4;

	 a = add(v, a);
	 a = add(u, a);
	 a = add(u, a);
	 a.num_l = 3;

	 printf("comprimento da amostra: %d \n", length(a));

	 l = length(a);

	 for (i = 0; i < l; i++) {
	 for (j = 0; j < 4; j++) {
	 printf("Amostra %d na posicao %d = %d\n", i, j, a.matriz[i][j]);
	 }
	 }
	 printf("comprimento da amostra: %d \n", length(a));
	 int* t = element(a, 0);
	 printf("%d %d %d %d \n", t[0], t[1], t[2], t[3]);

	 int var[2] = { 0, 3 }, val[2] = { 0, 1 };
	 int y = count(a, var, val, 2);
	 printf("COUNT: %d\n", y);

	 amostra b = emptyS();
	 b.num_c = 4;
	 b = add(v, b);
	 b = add(u, b);
	 b = add(v, b);
	 b = add(u, b);

	 amostra c = emptyS();
	 c.num_c = 4;
	 puts("AMOSTRA A");
	 for (i = 0; i < length(a); i++) {
	 printf("|");
	 for (j = 0; j < 4; j++) {

	 if (j != 3) {
	 printf("%d ", a.matriz[i][j]);
	 } else {
	 printf("%d|\n", a.matriz[i][j]);
	 }
	 }
	 }

	 puts("AMOSTRA B");
	 for (i = 0; i < length(b); i++) {
	 printf("|");
	 for (j = 0; j < 4; j++) {

	 if (j != 3) {
	 printf("%d ", b.matriz[i][j]);
	 } else {
	 printf("%d|\n", b.matriz[i][j]);
	 }
	 }
	 }
	 printf("comprimento de B:%d, colunas de B:%d \n", length(b), b.num_c);
	 a = join(a, b);

	 puts("AMOSTRA A U B");
	 for (i = 0; i < length(a); i++) {
	 printf("|");
	 for (j = 0; j < 4; j++) {

	 if (j != 3) {
	 printf("%d ", a.matriz[i][j]);
	 } else {
	 printf("%d|\n", a.matriz[i][j]);
	 }
	 }
	 }
	 printf(
	 "numero de linhas da amostra C=AUB:%d,\n numero de colunas da amostra C=AUB :%d \n",
	 length(a), a.num_c);

	 int* max = maximos(a);
	 printf("MÁXIMOS: %d %d %d %d \n", max[0], max[1], max[2], max[3]);

	 int n = 3;

	 printf("TESTE DOS GRAFOS ORIENTADOS\n");
	 puts("GRAFO DISC");
	 grafoo g = disc(n);
	 for (i = 0; i < n; i++) {
	 printf("|");
	 for (j = 0; j < n; j++) {
	 if (j != n - 1) {
	 printf("%d ", g.m_adj[i][j]);
	 } else {
	 printf("%d|\n", g.m_adj[i][j]);
	 }
	 }
	 }
	 printf("adicionar aresta de 0 para 1\n");

	 g = add_edge(g, 0, 1);

	 for (i = 0; i < n; i++) {
	 printf("|");
	 for (j = 0; j < n; j++) {
	 if (j != n - 1) {
	 printf("%d ", g.m_adj[i][j]);
	 } else {
	 printf("%d|\n", g.m_adj[i][j]);
	 }
	 }
	 }
	 puts("Grafo:");

	 g = add_edge(g, 2, 1);
	 g = add_edge(g, 1, 0);

	 for (i = 0; i < n; i++) {
	 printf("|");
	 for (j = 0; j < n; j++) {
	 if (j != n - 1) {
	 printf("%d ", g.m_adj[i][j]);
	 } else {
	 printf("%d|\n", g.m_adj[i][j]);
	 }
	 }
	 }

	 lista q;
	 q = parents(g, 1);
	 printf("Pais do nó 1 %d e %d\n", q.first->val, q.first->next->val);

	 puts("GRAFOS PESADOS");
	 grafop gp = discWD(3);

	 for (i = 0; i < 3; i++) {
	 printf("|");
	 for (j = 0; j < 3; j++) {
	 if (j != 3 - 1) {
	 printf("%f ", gp.m_adj[i][j]);
	 } else {
	 printf("%f|\n", gp.m_adj[i][j]);
	 }
	 }
	 }

	 printf("adicionar aresta de 0 para 1 com peso 0.00123 e outras\n");
	 gp = add_Wedge(gp, 0, 1, 0.666);
	 gp = add_Wedge(gp, 0, 2, 0.666);
	 gp = add_Wedge(gp, 1, 2, 0.24325);

	 for (i = 0; i < 3; i++) {
	 printf("|");
	 for (j = 0; j < 3; j++) {
	 if (j != 3 - 1) {
	 printf("%f ", gp.m_adj[i][j]);
	 } else {
	 printf("%f|\n", gp.m_adj[i][j]);
	 }
	 }
	 }

	 pai = MST(gp);
	 printf("Pais : %d %d %d\n", pai[0], pai[1], pai[2]);

	 puts("REDE DE BAYES");

	 max = maximos(a);
	 printf("MAXIMOS: %d %d %d %d \n", max[0], max[1], max[2], max[3]);


	 bayes BN = newBN(pai, a);

	 puts("TENSOR1");

	 for (i = 0; i < (max[a.num_c - 1] + 1); i++) {
	 printf("P(C=%d)=%f\n", i, BN.tensor[a.num_c - 1][i]);
	 }
	 puts("TENSOR2");
	 for (i = 0; i < (max[a.num_c - 1] + 1) * (max[0] + 1); i++) {
	 printf("P(Raiz|C)=%f\n", BN.tensor[0][i]);
	 }
	 puts("TENSORES3");
	 for (j = 1; j < a.num_c - 1; j++) {
	 for (i = 0;
	 i < (BN.max[BN.num_n - 1] + 1) * (max[j] + 1) * (BN.max[BN.pai[j]] + 1);
	 i++) {
	 printf("elemento:%d P(Raiz|pai,C)=%f\n",i, BN.tensor[j][i]);
	 }
	 }
	 puts("PROBABILIDADE DE UM VECTOR");
	 int v1[4] = { 0, 1, 2, 1 }, v2[4] = { 0, 1, 2, 0 };

	 probabilidade1 = prob(BN, v1);
	 probabilidade2 = prob(BN, v2);
	 printf("PROB(C=0):%f\n",
	 probabilidade1 / (probabilidade1 + probabilidade2));
	 printf("PROB(C=1):%f\n",
	 probabilidade2 / (probabilidade1 + probabilidade2));*/

	puts("INFORMAÇÂO MUTUA, GRAFO PESADO:");

	amostra A = emptyS();

	int v11[20] = { 0, 0, 0, 0, 0, 3, 2, 1, 1, 5, 4, 0, 3, 0, 3, 3, 1, 1, 4, 1 };
	int v22[20] = { 1, 0, 0, 0, 3, 2, 4, 1, 2, 3, 4, 1, 3, 0, 0, 3, 2, 1, 2, 0 };
	int v3[20] = { 1, 1, 0, 0, 4, 5, 3, 2, 1, 2, 3, 0, 3, 0, 1, 2, 3, 3, 4, 0 };
	int v4[20] = { 1, 1, 1, 0, 6, 5, 4, 3, 4, 5, 1, 1, 3, 0, 3, 3, 2, 1, 4, 1 };
	int v5[20] = { 1, 1, 1, 1, 6, 5, 4, 3, 4, 5, 2, 1, 3, 0, 2, 1, 2, 1, 3, 1 };
	int v6[20] = { 0, 1, 0, 1, 4, 5, 3, 2, 1, 2, 1, 0, 3, 0, 3, 3, 6, 2, 4, 1 };
	int v7[20] = { 0, 0, 1, 1, 3, 2, 1, 4, 5, 4, 2, 0, 3, 0, 2, 2, 1, 1, 4, 0 };
	int v8[20] = { 0, 1, 1, 1, 4, 5, 3, 2, 1, 2, 2, 0, 3, 0, 3, 1, 4, 3, 5, 0 };
	int v9[20] = { 1, 1, 1, 1, 3, 2, 1, 4, 5, 4, 3, 0, 3, 0, 1, 1, 2, 1, 4, 1 };
	A.num_c = 20;

	/*int v11[12] = { 0, 0, 0, 0 ,0 ,3 };
	 int v22[12] = { 1, 0, 0, 0 ,3 ,2 };
	 int v3[12] = { 1, 1, 0, 0 ,4 ,5};
	 int v4[12] = { 1, 1, 1, 0 ,6 ,5 };
	 int v5[12] = { 1, 1, 1, 1 ,6 ,5 };
	 int v6[12] = { 0, 1, 0, 1 ,4 ,5};
	 int v7[12] = { 0, 0, 1, 1 ,3 ,2 };
	 int v8[12] = { 0, 1, 1, 1 ,4 ,5};
	 int v9[12] = { 1, 1, 1, 1 ,3 ,2 };
	 A.num_c = 6;*/

	A = add(v11, A);
	A = add(v22, A);
	A = add(v3, A);
	A = add(v4, A);
	A = add(v3, A);
	A = add(v11, A);
	A = add(v22, A);
	A = add(v5, A);
	A = add(v6, A);
	A = add(v4, A);
	A = add(v5, A);
	A = add(v9, A);
	A = add(v9, A);
	A = add(v7, A);
	A = add(v8, A);
	A = add(v9, A);
	A = add(v4, A);
	A = add(v5, A);
	A = add(v9, A);
	A = add(v11, A);
	A = add(v22, A);
	A = add(v3, A);
	A = add(v4, A);
	A = add(v3, A);
	A = add(v11, A);
	A = add(v22, A);
	A = add(v5, A);
	A = add(v6, A);
	A = add(v4, A);
	A = add(v5, A);
	A = add(v9, A);
	A = add(v9, A);
	A = add(v7, A);
	A = add(v8, A);
	A = add(v9, A);
	A = add(v4, A);
	A = add(v5, A);
	A = add(v9, A);
	printf("numero de linhas da amostra A:%d,\n numero de colunas da amostra A :%d \n",
			length(A), A.num_c);
	grafop GP = pesos(A);

	for (i = 0; i < A.num_c - 1; i++) {
		printf("|");
		for (j = 0; j < A.num_c - 1; j++) {
			if (j != A.num_c - 2) {
				printf("%lf ", GP.m_adj[i][j]);
			} else {
				printf("%lf|\n", GP.m_adj[i][j]);
			}
		}
	}

	pai = MST(GP);

	/*for (i = 0; i < A.num_c - 1; i++) {
		printf("Pai[%d]=%d  ", i, pai[i]);
	}*/
	printf("EMRDAGDG\n");
	puts("HEllo");

	bayes BN1 = newBN(pai, A,"bayesnet.bn");

	probabilidade1 = prob(BN1, v5);
	probabilidade2 = prob(BN1, v4);
	printf("PROB(C=0):%f\n",
			probabilidade1 / (probabilidade1 + probabilidade2));
	printf("PROB(C=1):%f\n",
			probabilidade2 / (probabilidade1 + probabilidade2));


	bayes BN2;
	char* dados = "Cancro.da";
	amostra Amostra = emptyS();
	Amostra = read(dados);
	puts("!AMOSTRA!");

	printf("comprimento da Amostra:%d, colunas da Amostra:%d \n",
			length(Amostra), Amostra.num_c);

	for (i = 0; i < length(Amostra); i++) {
		printf("|");
		for (j = 0; j < Amostra.num_c; j++) {

			if (j != Amostra.num_c - 1) {
				printf("%d ", Amostra.matriz[i][j]);
			} else {
				printf("%d|\n", Amostra.matriz[i][j]);
			}
		}
	}

	grafop GrafoPesado=pesos(Amostra);
	int* Pais=MST(GrafoPesado);

	for(i=0;i<Amostra.num_c-1;i++){
		for(j=0;j<Amostra.num_c-1;j++){
			printf("GrafoPesado[%d][%d]=%lf\n",i,j,GrafoPesado.m_adj[i][j]);
		}
	}

	char* bayesnet="Bayes100.bn";
	bayes BayesNet=newBN(Pais,Amostra,bayesnet);

	BN2 = unserialize(bayesnet);
/*
	 for (i = 0; i < BN2.num_n - 1; i++) {
	 printf("pai[%d]=%d\n", i, BN2.pai[i]);
	 }

	 for (i = 0; i < BN2.num_n; i++) {
	 printf("max[%d]=%d\n", i, BN2.max[i]);
	 }

	 i = 0;
	 while (i <= BN2.max[BN2.num_n - 1]) {
	 printf("BN2.tensor[%d][%d]=%f\n",
	 BN2.num_n - 1,i,BN2.tensor[BN2.num_n - 1][i]);
	 i++;
	 }

	 i = 0;
	 while (i <= BN2.max[BN2.num_n - 1]) {

	 j = 0;
	 while (j <= BN2.max[0]) {
	 printf("BN2.tensor[%d][%d]=%f\n",
	 0,i * (BN2.max[0] + 1) + j,BN2.tensor[0][i * (BN2.max[0] + 1) + j]);
	 j++;
	 }
	 i++;
	 }
*/
	 /*TENSOR3*/
/*
	 int dom[3];
	 int ind;
	 j = 1;
	 while (j < BN2.num_n - 1) {
	 i = 0;
	 while (i < BN2.max[BN2.num_n - 1] + 1) {

	 k = 0;

	 while (k < BN2.max[j] + 1) {

	 l = 0;
	 while (l < BN2.max[BN2.pai[j]] + 1) {

	 dom[0] = BN2.max[BN2.num_n - 1] + 1;
	 dom[1] = BN2.max[j] + 1;
	 dom[2] = BN2.max[BN2.pai[j]] + 1;

	 ind = indice(i, k, l, dom);
	 printf("BN2.tensor[%d][%d]=%f\n",j,ind, BN2.tensor[j][ind]);

	 l++;
	 }
	 k++;

	 }
	 i++;
	 }
	 j++;
	 }
*/

	return 0;
}
