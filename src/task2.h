#pragma once
#include "comun.h"

typedef struct Qnode {
    char value[64];
    struct Qnode *next;
} Qnode;

typedef struct Queue {
    Qnode *front, *rear;
} Queue;

void push(node **top, double newData);
double pop(node **top);
int isEmpty(const node *top);
void deleteStack(node **top);
Queue* createQueue();
char *Qpop(Queue *q);
void Qpush(Queue *q,const char *v);
void citire_piete(node **piata1, node **piata2, node **piata3, char *p1, char *p2, char *p3, char *buffer, FILE *fin);
void afisare_piete (node *piata1, node *piata2, node *piata3, const char *p1, const char *p2, const char *p3, char *buffer, FILE *fout);