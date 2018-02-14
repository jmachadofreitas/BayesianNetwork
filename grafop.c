#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include"grafop.h"

grafop discWD(int n) {
	int i = 0, j;
	grafop g;
	g.m_adj = (double**) malloc(n * sizeof(double*));
	g.num_n = n;
	while (i < n) {
		g.m_adj[i] = (double*) malloc(n * sizeof(double));
		i++;
	}

	i = 0;
	while (i < n) {
		j = i + 1;
		while (j < n) {
			g.m_adj[j][i] = 0;
			g.m_adj[i][j] = 0;
			j++;
		}
		g.m_adj[i][i] = 0;
		i++;
	}
	return g;
}

grafop add_Wedge(grafop g, int n1, int n2, double w) {
	if (n1 == n2) {
		return g;
	}
	g.m_adj[n1][n2] = w;
	g.m_adj[n2][n1] = w;
	return g;
}

int* MST(grafop g) {

	/*Algoritmo PRIM*/

	int* pai = (int *) malloc(sizeof(int) * g.num_n);
	lista S = new();
	int i = 0;
	int* e = (int*) malloc(sizeof(int) * 2);

	while (i < g.num_n) {
		pai[i] = -1;
		i++;
	}
	S = insert(S, 0);
	while (S.comp != g.num_n) {
		e = pesado(g, S); /* retorna uma aresta pesada de {S,V\S} */
		pai[e[1]] = e[0];
		//printf("pai[%d]=%d\n", e[1], e[0]);
		S = insert(S, e[1]);
	}

	free(e);

	return pai;

}

int* pesado(grafop g, lista S) {
	int i, j, n = g.num_n;
	double max = 0;
	int* e = (int*) malloc(sizeof(int) * 2);

	nodept aux = S.first;

	while (aux != NULL) {
		i = aux->val;
		j = 0;
		while (j < n) {
			if (max <= g.m_adj[i][j] && !pert(S,j)) {
				/*!pert(S,j): se o nó j pertence à lista não se quer uma ligação para esse nó
				 *  evitando grafos cíclicos e alterações do pai do nó*/
				max = g.m_adj[i][j];
				e[0] = i;
				e[1] = j;
			}
			j++;

		}
		aux = aux->next;
	}

	return e;
}

/*--------------------------------------Informação Mútua------------------------------------------------*/

grafop pesos(amostra a) {
	grafop GP = discWD(a.num_c - 1);
	double w;
	int* max = maximos(a);
	int i, j;
	i = 0;
	while (i < a.num_c - 1) {
		j = i + 1;
		while (j < a.num_c - 1) {
			w = IM(a, i, j, max);
			GP = add_Wedge(GP, i, j, w);
			j++;
		}
		i++;
	}
	return GP;
}

double IM(amostra a, int n1, int n2, int* max) {
	int i, j, k;
	int var[3] = { n1, n2, a.num_c - 1 }, val[3], varC[1] = { a.num_c - 1 },
			valC[1], varN1C[2] = { n1, a.num_c - 1 }, valN1C[2], varN2C[2] = {
					n2, a.num_c - 1 }, valN2C[2];
	double aux1, aux2, SUM = 0;
	i = 0;
	while (i < max[a.num_c - 1] + 1) {
		val[2] = i;
		valC[0] = i;
		valN1C[1] = i;
		valN2C[1] = i;
		j = 0;
		while (j < max[n1] + 1) {
			val[0] = j;
			valN1C[0] = j;

			k = 0;
			while (k < max[n2] + 1) {
				val[1] = k;
				valN2C[0] = k;

				aux1 = (count(a, varC, valC, 1)
						* count(a, var, val, 3));
				aux2 = (count(a, varN1C, valN1C, 2)
						* (count(a, varN2C, valN2C, 2)));

				if (aux1 != 0 && aux2 != 0) {
					SUM +=((double)count(a, var, val, 3)/a.num_l)
							*(log((double)aux1 / (double)aux2))/(double)log(2);
				} else {
					SUM += 0;
				}
				k++;
			}
			j++;
		}
		i++;
	}

	return SUM;
}

