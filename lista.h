#include<stdio.h>

struct node{
	int val;
	struct node* next;
};

typedef struct node* nodept;

struct lista{
	int comp;
	nodept first;
};

typedef struct lista lista;

enum bool {false,true};

typedef enum bool bool;
