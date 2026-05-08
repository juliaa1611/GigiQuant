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

void citire_piete(node **piata1, node **piata2, node **piata3, char *p1, char *p2, char *p3, char *buffer, FILE *fin) {
    sscanf(buffer, "%31[^\r\n]", p1);
    while(fgets(buffer, 128, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9')
        push(piata1, atof(buffer));

    sscanf(buffer, "%31[^\r\n]", p2);
    while(fgets(buffer, 128, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9')
        push(piata2, atof(buffer));

    sscanf(buffer, "%31[^\r\n]", p3);
    while(fgets(buffer, 128, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9') 
        push(piata3, atof(buffer));
}

void afisare_piete (node *piata1, node *piata2, node *piata3, const char *p1, const char *p2, const char *p3, char *buffer, FILE *fout) {
    int zi = 1;
    while (piata1 != NULL && piata2 != NULL && piata3 != NULL) {
        float x = pop(&piata1);
        float y = pop(&piata2);
        float z = pop(&piata3);

        Queue *Qhead = createQueue();
        if (x == y && y != z) {
            sprintf(buffer, "ziua %d - %.2lf - %s\n", zi, fabs(x - z), p3);
            Qpush(Qhead, buffer);
        }
        if (x == z && z != y) {
            sprintf(buffer, "ziua %d - %.2lf - %s\n", zi, fabs(x - y), p2);
            Qpush(Qhead, buffer);
        }
        if (y == z && x != y) {
            sprintf(buffer, "ziua %d - %.2lf - %s\n", zi, fabs(y - x), p1);
            Qpush(Qhead, buffer);
        } 
        while (Qhead->front != NULL) {
            char *msg = Qpop(Qhead); 
            if (msg != NULL) {
                fprintf(fout, "%s", msg);
                free(msg);
            }
        }
        free(Qhead);
        zi ++;
    }
} 