#pragma once
#include "comun.h"

typedef struct Graph {
    int V; 
    struct node **array;
} Graph;

node *add_list_node(int x);
void add_edge(Graph *graph, int x, int y);
int find_interval(float x, float size, float P_start);
Graph *create_graph(int n);
void build_graph(Graph *graph, int n, double size, FILE *fin, double P_start, FILE *fout);
void print_graph(Graph *graph, int n, FILE *fout);
void empty_graph(Graph *graph, int n);