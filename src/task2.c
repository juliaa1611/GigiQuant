#include "task2.h"

void push(node **top, double newData) {
    node *newNode = malloc(sizeof(node));
    newNode->valoare = newData;
    newNode->next = (*top);
    (*top) = newNode;
    return;
}

double pop(node **top) {
    node *temp = (*top);
    double aux = temp->valoare;
    (*top) = (*top)->next;
    free(temp);
    return aux;
}

int isEmpty(const node *top) {
    if (top == NULL)
        return 1;
    else return 0;
}

void deleteStack(node **top) {
    while(!isEmpty(*top)) {
        node *temp = (*top);
        (*top) = (*top)->next;
        free(temp);
    }
    return;
}

void Qpush(Queue *q, const char *v) {
    Qnode *newNode = malloc(sizeof(Qnode));
    strncpy(newNode->value, v, 63);
    newNode->value[63] = '\0';
    newNode->next = NULL;

    if (q->rear == NULL)
        q->rear = newNode;
    else {
        (q->rear)->next = newNode;
        q->rear = newNode;
    }
    if (q->front == NULL)
        q->front=q->rear;
    return;
}

char *Qpop(Queue *q) {
    if (q->front == NULL) 
        return NULL;

    Qnode *aux = q->front;
    char *d = malloc(64 * sizeof(char)); 
    if (d == NULL) 
        return NULL;
    strcpy(d,aux->value);
    q->front = (q->front)->next;
    free(aux);
    return d;
}

Queue* createQueue() {
    Queue* q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;
    q->front = NULL;
    q->rear = NULL;
    return q;
}