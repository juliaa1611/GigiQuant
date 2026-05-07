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