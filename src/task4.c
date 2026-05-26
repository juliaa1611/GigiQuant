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
    while (curent->next != NULL) 
        curent = curent->next;
    curent->next = add_list_node(y);
}

int find_interval(float x, float size, float P_start) {
    P_start = 0;
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

void build_graph(Graph *graph, int n, double size, FILE *fin, double P_start, FILE *fout, int *intervals) {
    double p_curent, p_next;
    fscanf(fin, "%lf", &p_curent);
    int int_curent = find_interval(p_curent, size, P_start);

    int index = 0; intervals[index] = int_curent;
    while (fscanf(fin, "%lf", &p_next) == 1) {
        index ++;
        int int_next = find_interval(p_next, size, P_start);
        intervals[index] = int_next;
        add_edge(graph, int_curent, int_next);
        int_curent = int_next;
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

long long int CMMDC(long long int x, long long int y) {
    while (y) {
        int temp = y;
        y = x % y;
        x = temp;
    }
    return llabs(x);
}

void reducere(long long int *x, long long int *y) {
    if ((*x) == 0) {
        (*y) = 1;
        return;
    } 
    long long int c = CMMDC((*x), (*y));
    (*x) /= c;
    (*y) /= c;
}

fract add(fract x, fract y) {
    fract rez;
    rez.numarator = x.numarator * y.numitor + y.numarator * x.numitor;
    rez.numitor = x.numitor * y.numitor;
    return rez;
}

fract multiply(fract x, fract y) {
    fract rez;
    rez.numarator = x.numarator * y.numarator;
    rez.numitor = x.numitor * y.numitor;
    return rez;
}

void markov(Graph *graph, int capacity, int K, int P_start, int P_target, FILE *fout) {
    fract *curent = calloc(capacity, sizeof(fract));
    fract *nday = calloc(capacity, sizeof(fract));
    curent[P_start].numarator = 1;
    for (int i = 0; i < capacity; i ++) {
        curent[i].numitor = 1;
        nday[i].numitor = 1;
    }
    for (int k = 0; k < K; k ++) {
        if(curent[P_target].numarator == curent[P_target].numitor)
            fprintf(fout, "%d\n", 1);
        else if (curent[P_target].numarator != 0)
            fprintf(fout, "%lld/%lld\n", curent[P_target].numarator, curent[P_target].numitor);
        else 
            fprintf(fout, "%d\n", 0);
        for (int i = 0; i < capacity; i ++) {
            if (curent[i].numarator > 0) {
                int total = 0; node *temp = graph->array[i];
                while(temp != NULL) {
                    total ++;
                    temp = temp->next;
                }
                fract probabilitate;
                probabilitate.numarator = 1;
                probabilitate.numitor = total;
                fract final = multiply(curent[i], probabilitate);
                reducere(&final.numarator, &final.numitor);

                temp = graph->array[i];
                while (temp != NULL) {
                    nday[temp->graph_value] =  add(nday[temp->graph_value], final);
                    reducere(&nday[temp->graph_value].numarator, &nday[temp->graph_value].numitor);
                    temp = temp->next;
                }
            }
        }
        reducere(&nday[P_target].numarator, &nday[P_target].numitor);
        for (int i = 0; i < capacity; i ++) {
            curent[i].numarator = nday[i].numarator;
            curent[i].numitor = nday[i].numitor;
            nday[i].numarator = 0; nday[i].numitor = 1;
        }
    }
    free(curent); free(nday);
}