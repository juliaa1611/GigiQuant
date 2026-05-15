#include "task4.h"

node *add_list_node(int x) {
    node *newList_node = malloc(sizeof(node));
    newList_node->graph_value = x;
    newList_node->next = NULL;
    return newList_node;    
}

void add_edge(Graph *graph, int x, int y) {
    if(graph->array[x] == NULL) {
        graph->array[x] = add_list_node(y);
        return;
    }
    node *curent = graph->array[x];
    while (curent->next != NULL) {
        if (curent->graph_value == y)
            return;
        curent = curent->next;
    }
    if (curent->graph_value == y)
        return;
    curent->next = add_list_node(y);
}

int find_interval(float x, float size, float P_start) {
    if (x >= P_start) {
        while ((P_start + size) <= x)
            P_start += size;
        return P_start;
    }
    else {
        while (P_start > x)
            P_start -= size;
        return P_start; 
    }
}

Graph *create_graph(int n) {
    Graph *new_graph = malloc(sizeof(Graph));
    new_graph->V = n;
    new_graph->array = calloc(n, sizeof(node*));
    return new_graph;
}

void build_graph(Graph *graph, int n, double size, FILE *fin, double P_start, FILE *fout) {
    double p_curent, p_next;
    fscanf(fin, "%lf", &p_curent);
    int int_curent = find_interval(p_curent, size, P_start);
    while (fscanf(fin, "%lf", &p_next) == 1) {
        int int_next = find_interval(p_next, size, P_start);
        add_edge(graph, int_curent, int_next);
        int_curent = int_next;
    }
}

void print_graph(Graph *graph, int n, FILE *fout) {
    for (int i = 0; i < n; i ++) {
        if(graph->array[i] != NULL) {
            fprintf(fout, "%d ", i); //sursa
            
            node *temp = graph->array[i];
            while (temp != NULL) {
                fprintf(fout, "%d ", temp->graph_value);
                temp = temp->next;
            }
            fprintf(fout, "\n");
        }
    }
}

void empty_graph(Graph *graph, int n) {
    for (int i = 0; i < n; i ++) {
        while(graph->array[i] != NULL) {
            node *temp = graph->array[i];
            graph->array[i] = graph->array[i]->next;
            free (temp);
        }
    }
    free(graph->array); free (graph);
}