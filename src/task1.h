#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct node
{
    double valoare;
    double randament;
    struct node *next;
} node;

node *creeareNod(double value);
void adaugare(node **head, double value);
void stergereLista(node **head);
double randament(double pt, double pt_anterior);
double calculareRandamentTotal(node *head);
double deviatia_standard(node *head, double rand_mediu);
double trunchiere(double x);