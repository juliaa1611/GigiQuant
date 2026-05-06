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