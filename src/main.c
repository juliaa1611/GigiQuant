#include "task1.h"
#include "task2.h"
#include "task3.h"

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
        double temp1, temp2; 
        fscanf(fin, "%lf", &temp1); //a doua data e la fel pt t1 si t2
        
        if(verificaretask1(&temp2, fin) == 1){ //daca gaseste '.' => t1
            node *head = NULL;
            adaugare(&head, temp1);
            adaugare(&head, temp2);
            citirefisiertask1(fin, n, &head);
            calculare_volat(head, fout, n);
            stergereLista(&head);
        }
        else {
            fprintf(fout, "task 4\n");
        }
    }
    else { //nu e nr => task 2 sau 3
        if (strchr(buffer, ',') == NULL) { //task 2 
            node *piata1 = NULL; char p1[32]; node *piata2 = NULL; char p2[32]; node *piata3 = NULL; char p3[32];
            citire_piete(&piata1, &piata2, &piata3, p1, p2, p3, buffer, fin);
            afisare_piete(piata1, piata2, piata3, p1, p2, p3, buffer, fout);

            deleteStack(&piata1); deleteStack(&piata2); deleteStack(&piata3);
        }
        else { //task3
            actiune vector[10]; int nra = 0, nrp;
            const char *temp = strtok(buffer, ",");
            read_names(vector, temp, &nra); //citirea actiunilor de pe prima linie
            read_value(vector, &nrp, temp, buffer, fin); // nr de actiuni (nr de el de pe linie)

            tree *root = newTreeNode(""); //in root sunt toate actiunile, dar nu ne intereseaza
            for (int i = 0; i < nra; i ++) 
                insertTree(root, vector, i, nrp);

            char mtemp[12][24]; int total_sim = 0;
            actiuneSimetrica(root->left, root->right, vector, nra, mtemp, &total_sim, fout);
            afisareSimetrica(mtemp, vector, nra, total_sim, fout);

            deleteTree(&root);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}