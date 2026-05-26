#pragma once
#include "comun.h"

typedef struct Graph {
    int V; 
    struct node **array;
} Graph;

typedef struct fract {
    long long int numitor;
    long long int numarator;
} fract;

node *add_list_node(int x);
void add_edge(Graph *graph, int x, int y);
int find_interval(float x, float size, float P_start);
Graph *create_graph(int n);
void build_graph(Graph *graph, int n, double size, FILE *fin, double P_start, FILE *fout, int *intervals);
void empty_graph(Graph *graph, int n);
void markov(Graph *graph, int capacity, int K, int P_start, int P_target, FILE *fout);
fract multiply(fract x, fract y);
fract add(fract x, fract y);
void reducere(long long int *x, long long int *y);
long long int CMMDC(long long int x, long long int y);