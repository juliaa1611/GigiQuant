#pragma once
#include "comun.h"

typedef struct actiune {
    char nume[5];
    float pret[5];
} actiune;

typedef struct tree {
    char nume[128];
    struct tree *left, *right;
} tree;

tree *newTreeNode(const char *numeNou);
void modifyTree(tree *root,const char *added);
void insertTree(tree *root, actiune v[], int i, int nrp);
void deleteTree(struct tree** node_ref);
void deleteTreeUtil(struct tree* root);
int isLeaf(const tree *root);
int find_index(actiune vector[], int nra,const char *a);
void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], int nra, char mtemp[][24], int *total_sim, FILE *fout);
