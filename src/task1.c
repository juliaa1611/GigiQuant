#include "task1.h"

node *creeareNod(double value)
{
    node *newNode = (node*)malloc(sizeof(node));   
    if (!newNode) 
        return NULL;

    newNode->valoare = value;
    newNode->next = NULL;
    return (newNode);
}

void adaugare(node **head, double value)
{
    node *newNode = creeareNod(value);

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    node *curent = *head;
    while (curent->next != NULL)
        curent = curent->next;
    
    curent->next = newNode;
    return;
}

void stergereLista(node **head)
{
    node *temp;
    while (*head != NULL)
    {
        temp = (*head)->next;
        free (*head);
        *head = temp;
    }
    *head = NULL;
    return;
}

double randament(double pt, double pt_anterior)
{
    return ((pt-pt_anterior)/pt_anterior);
}

double calculareRandamentTotal(node *head)
{
    if (head == NULL)
        return 0;

    double randament_total = 0;
    head->randament = 0;
    node *curent = head->next;
    const node *anterior = head;

    while (curent != NULL)
    {
        curent->randament = randament(curent->valoare, anterior->valoare);
        randament_total += curent->randament;

        anterior = curent;
        curent = curent->next;
    }
    return randament_total;
}

double deviatia_standard(node *head, double rand_mediu)
{
    if (head == NULL || head->next == NULL)
        return 0;
    
    double suma = 0;
    head = head->next;
    while (head != NULL)
    {
        double diferenta = (head->randament - rand_mediu);
        suma += diferenta * diferenta;
        head = head->next;
    }
    return suma;
}

double trunchiere(double x)
{
    return trunc(x * 1000.0)/1000.0;
}

int verificaretask1(double *temp2, FILE *fin) {
    char buffer[64];
    fscanf(fin, "%63s", buffer);
    if (strchr(buffer, '.') != NULL)
    {
        (*temp2) = atof(buffer);
        return 1;
    }
    (*temp2) = atoi(buffer);
    return 0;
}

void citirefisiertask1(FILE *fin, int n, node **head) {
    for (int i = 0; i < n - 2; i ++) {
        double temp;
        fscanf(fin, "%lf", &temp);
        adaugare(head, temp);
    }
}

int task1sau4(FILE *fin, FILE *fout) {
    int n;
    if (fscanf(fin, "%d", &n) != 1 || n <= 1)
        return -1;
    return n;
}