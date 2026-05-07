#pragma once
#include "comun.h"

node *creeareNod(double value);
void adaugare(node **head, double value);
void stergereLista(node **head);
double randament(double pt, double pt_anterior);
double calculareRandamentTotal(node *head);
double deviatia_standard(node *head, double rand_mediu);
double trunchiere(double x);
int verificaretask1(double *temp2, FILE *fin);
void citirefisiertask1(FILE *fin, int n, node **head);