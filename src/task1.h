#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

typedef struct node {
    double valoare;
    double randament;
    struct node *next;
} node;

typedef struct actiune {
    char nume[5];
    float pret[5];
} actiune;

typedef struct tree {
    char nume[128];
    struct tree *left, *right;
} tree;

typedef struct Qnode {
    char value[64];
    struct Qnode *next;
} Qnode;

typedef struct Queue {
    Qnode *front, *rear;
} Queue;

node *creeareNod(double value);
void adaugare(node **head, double value);
void stergereLista(node **head);
double randament(double pt, double pt_anterior);
double calculareRandamentTotal(node *head);
double deviatia_standard(node *head, double rand_mediu);
double trunchiere(double x);
int verificaretask1(double *temp2, FILE *fin);
void citirefisiertask1(FILE *fin, int n, node **head);
void push(node **top, double newData);
double pop(node **top);
int isEmpty(const node *top);
void deleteStack(node **top);
tree *newTreeNode(const char *numeNou);
void modifyTree(tree *root,const char *added);
void insertTree(tree *root, actiune v[], int i, int nrp);
int height(tree* root);
void printLevel(tree* root, int level, FILE *fout);
void levelOrderTraversal(tree* root, FILE *fout);
void deleteTree(struct tree** node_ref);
void deleteTreeUtil(struct tree* root);
int isLeaf(const tree *root);
void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], char temp[][15]);
Queue* createQueue();
char *Qpop(Queue *q);
void Qpush(Queue *q,const char *v);
