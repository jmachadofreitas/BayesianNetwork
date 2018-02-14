#include<stdio.h>
#include<stdlib.h>
#include"grafoo.h"

grafoo disc(int n) {
	int i = 0, j;
	grafoo g;
	g.m_adj = (int**) malloc(n * sizeof(int*));
	g.num_n = n;
	while (i < n) {
		g.m_adj[i] = (int*) malloc(n * sizeof(int));
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

grafoo add_edge(grafoo g, int n1, int n2) {
	if(n1==n2){
		return g;
	}
	g.m_adj[n1][n2] = 1;
	return g;
}

lista parents(grafoo g, int n) {
	lista list = new();
	int i = 0;
	while (i < g.num_n) {
		if (g.m_adj[i][n] != 0) {
			list = insert(list, i);
		}
		i++;
	}
	return list;
}

/*Funções auxiliares lista*/

lista new() {
	lista l;
	l.comp = 0;
	l.first = NULL;
	return l;
}

bool pert(lista t, int i) {
	nodept aux = t.first;
	while (aux != NULL && aux->val != i) {
		aux = aux->next;
	}
	if (aux != NULL && aux->val == i) {
		return true;
	}
	return false;
}

lista insert(lista l, int i) {

	nodept new = (nodept) malloc(sizeof(struct node));
	bool b = pert(l, i);

	if (b==false) {
		new->val = i;
		new->next = l.first;
		l.first = new;
		l.comp++;
	}
	return l;
}

lista elim(lista l, int i) {
	nodept aux = l.first;
	if (aux != NULL) {
		if (aux->val == i) {
			l.first = aux->next;
			l.comp--;
			free(aux);
			return l;
		}
		while (aux->next != NULL && aux->next->val != i){
			aux = aux->next;
		}
		if (aux->next != NULL) {
			nodept aux2 = aux->next;
			aux->next = aux->next->next;
			free(aux2);
			l.comp--;
		}
	}
	return l;
}

