#include<stdio.h>
#include<stdlib.h>
#include"bayes.h"

int main(int argc, char* argv[]) {
	/*argv[0] é o prob.out
	 * argv[1] redebayes.bn
	 * argv[2,...,BN.num_n-1] valores do tuplo*/

	int i = 0, N;
	double aux = 0;
	char* nome;
	char* BayesNet = argv[1];
	bayes BN = unserialize(BayesNet);

	FILE *pf = fopen("out.res", "w");

	if (argc == 1 + BN.num_n) {

		int* vec = (int*) malloc(BN.num_n * sizeof(int));

		i = 0;
		while (i < BN.num_n - 1) {
			N = atoi(argv[i + 2]);
			vec[i] = N;

			i++;
		}

		i = 0;
		double* probas = (double*) malloc(
				sizeof(double) *( BN.max[BN.num_n - 1]+1));
		while (i < BN.max[BN.num_n-1] + 1) {
			vec[BN.num_n - 1] = i;
			probas[i] = prob(BN, vec);
			i++;
		}

		i = 0;
		while (i < BN.max[BN.num_n - 1] + 1) {
			aux += probas[i];
			i++;
		}

		i = 0;
		while (i < BN.max[BN.num_n - 1] + 1) {
			fprintf(pf, "P(C=%d)=%lf ", i, probas[i] / aux);
			i++;
		}

		fprintf(pf, "Fiabilidade= %E ", aux);

	} else {
		fprintf(pf, "O número de argumentos está errado");
	}

	fclose(pf);

	return 0;

}
