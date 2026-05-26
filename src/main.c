#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"

int main(int argc, const char* argv[])
{
    if (argc < 3) {
        printf("Compilat fara toate fisierele!\n"); 
        return 0;
    }

    FILE *fin, *fout;
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
    if (!fin) {
        printf("Eroare la fisierul de intrare!\n");
        fclose(fout);
        return 0;
    }
    if (!fout) {
        printf("Eroare la fisierul de iesire!\n");
        fclose (fin);
        return 0;
    }

    char buffer[128];
    fgets(buffer, 128, fin);

    if (isdigit(buffer[0])) { //daca e nr => task1 sau task4
        int n = atoi(buffer);
        double size, temp; 
        fscanf(fin, "%lf", &size); //a doua data e la fel pt t1 si t2
        
        if(verificaretask1(&temp, fin) == 1){ //task1
            node *head = NULL;
            adaugare(&head, size);
            adaugare(&head, temp);
            citirefisiertask1(fin, n, &head);
            calculare_volat(head, fout, n);
            stergereLista(&head);
        }
        else { //task4--------------------------------
            int K = (int)temp; double P_target, P_start;  
            fscanf(fin, "%lf", &P_start); fscanf(fin, "%lf", &P_target);
            P_start = find_interval(P_start, size, P_start);
            P_target = find_interval(P_target, size, P_start);
            Graph *graph; int capacity = 500;
            int intervals[n];
            graph = create_graph(capacity);
            build_graph(graph, n, size, fin, P_start, fout, intervals);
            markov(graph, capacity, K, P_start, P_target, fout);
            empty_graph(graph, capacity);
        } //-------------------------------------------
    }
    else { //nu e nr => task 2 sau 3
        if (strchr(buffer, ',') == NULL) { //task 2 
            node *piata1 = NULL; char p1[32]; node *piata2 = NULL; char p2[32]; node *piata3 = NULL; char p3[32];
            citire_piete(&piata1, &piata2, &piata3, p1, p2, p3, buffer, fin);
            afisare_piete(&piata1, &piata2, &piata3, p1, p2, p3, buffer, fout);

            deleteStack(&piata1); deleteStack(&piata2); deleteStack(&piata3);
        }
        else { //task3
            actiune vector[10]; int nra = 0, nrp;
            const char *temp = strtok(buffer, ",");
            read_names(vector, temp, &nra); //citirea actiunilor de pe prima linie
            read_value(vector, &nrp, temp, buffer, fin); // nr de actiuni (nr de el de pe linie)

            tree *root = NULL; newTreeNode(&root, ""); //in root sunt toate actiunile, dar nu ne intereseaza
            for (int i = 0; i < nra; i ++) 
                insertTree(root, vector, i, nrp);

            char mtemp[12][24]; int total_sim = 0;
            actiuneSimetrica(root->left, root->right, vector, nra, mtemp, &total_sim, fout);
            afisareSimetrica(mtemp, vector, nra, total_sim, fout);
            deleteTree(root);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}