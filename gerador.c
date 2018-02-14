#include<stdio.h>
#include<stdlib.h>
#include"bayes.h"

int main(int argc, char* argv[]) {

	/* argv[0] é o gerador
	 * argv[1] dados.da
	 */

	char* dados = argv[1];
	char* nome = argv[2];
	amostra Amostra = emptyS();
	grafop GrafoPesado;
	int* pais;
	bayes BayesNet;

	Amostra = read(dados);

	GrafoPesado = pesos(Amostra);

	pais = MST(GrafoPesado);

	BayesNet = newBN(pais, Amostra, nome);

	return 0;
}
