#include "task4.h"

node *add_list_node(int x) { //la lista de adiacenta
    node *newList_node = malloc(sizeof(node));
    newList_node->graph_value = x;
    newList_node->next = NULL;
    return newList_node;    
}

void add_edge(Graph *graph, int x, int y) { //adauga muchie intre 2 noduri
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
    while ((P_start + size) <= x) //destul de logic
        P_start += size;
    return P_start;
}

Graph *create_graph(int n) {
    Graph *new_graph = malloc(sizeof(Graph));
    new_graph->V = n;
    new_graph->array = calloc(n, sizeof(node*));
    return new_graph;
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

void build_graph(Graph *graph, int n, double size, FILE *fin, double P_start, FILE *fout, int *intervals) {
    double p_curent, p_next; //citim primul pret, pt ca trebuie sa stim ambele noduri intre care facem legatura
    fscanf(fin, "%lf", &p_curent);
    int int_curent = find_interval(p_curent, size, P_start); //gasim si intervalul

    int index = 0; intervals[index] = int_curent; //salvam intr un vector de intervale 
    while (fscanf(fin, "%lf", &p_next) == 1) {
        index ++;
        int int_next = find_interval(p_next, size, P_start); //gasim intervalul urmatorului pret
        intervals[index] = int_next; //il salvam in vector
        add_edge(graph, int_curent, int_next); //si facem legatura in graf intre anterior si curent
        int_curent = int_next; //anteriorul este acum curent samd
    }
}

long long int CMMDC(long long int x, long long int y) {
    while (y) {
        int temp = y;
        y = x % y;
        x = temp;
    } //alg lui Euclid
    return llabs(x);
}

void reducere(long long int *x, long long int *y) {
    if ((*x) == 0) return; 
    long long int c = CMMDC((*x), (*y));
    (*x) /= c;
    (*y) /= c;
}

fract add(fract x, fract y) {
    fract rez;
    rez.numarator = x.numarator * y.numitor + y.numarator * x.numitor; //aducem la acelasi numitor
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
    curent[P_start].numarator = 1; //in prima zi sansa sa fim la primul interval e de 1
    //initializam toti numitorii de la ambii vectori cu 1 (numitori nenuli)
    for (int i = 0; i < capacity; i ++) {
        curent[i].numitor = 1;
        nday[i].numitor = 1;
    }
    for (int k = 0; k < K; k ++) {
        //la fiecare zi afisam sansa curenta, apoi calculam si parcurgem recursiv:
        if(curent[P_target].numarator == curent[P_target].numitor) 
            fprintf(fout, "%d\n", 1); //(ex 7/7 = 1)
        else if (curent[P_target].numarator != 0)
            fprintf(fout, "%lld/%lld\n", curent[P_target].numarator, curent[P_target].numitor);
        else 
            fprintf(fout, "%d\n", 0); 

        //am afisat ziua curenta, deci continuam calculele zilei urmatoare: 
        //capacity -> nr total de noduri din graf
        for (int i = 0; i < capacity; i ++) {
            if (curent[i].numarator > 0) { //am ajuns la o valoare valida (la care putem ajunge pe baza drumurilor anterioare)
                int total = 0; node *temp = graph->array[i]; //din graf
                while(temp != NULL) { //calculam doar totalul de muchii spre care arata acea valoare
                    total ++; //si il salvam in totalul curent
                    temp = temp->next;
                }
                fract probabilitate;
                probabilitate.numarator = 1;
                probabilitate.numitor = total;
                //astfel sunt 1/total sanse sa ne ducem pe oricare din muchiile spre care arata nodul
                //nu trb sa tinem cont de legaturi cu valori egale pt ca urmeaza sa le parcurgem individual

                //inmultim probabilitatea curenta cu sansa anterioara sa fi fost deja pe muchia curenta: 
                fract final = multiply(curent[i], probabilitate); 
                reducere(&final.numarator, &final.numitor); //reducem pt calcule mici

                temp = graph->array[i]; //incepem sa parcurgem toate muchiile nodului curent
                while (temp != NULL) {
                    nday[temp->graph_value] =  add(nday[temp->graph_value], final); //adunam la sansa deja existenta
                    reducere(&nday[temp->graph_value].numarator, &nday[temp->graph_value].numitor); //reducem
                    temp = temp->next;
                }
            }
        }
        for (int i = 0; i < capacity; i ++) {
            curent[i].numarator = nday[i].numarator; //actualizam curent
            curent[i].numitor = nday[i].numitor;
            nday[i].numarator = 0; nday[i].numitor = 1;//ziua urmatoare se recalculeaza prin adunare pe baza sanselor
            //curente pe care le facem la fiecare pas, deci ca la orice suma resetam la 0
        }
    }
    free(curent); free(nday);
}