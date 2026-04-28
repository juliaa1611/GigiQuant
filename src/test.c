#include "task1.h"

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

            double rand_mediu = (calculareRandamentTotal(head) / (n - 1));
            fprintf(fout, "%.3lf\n", trunchiere(rand_mediu));
            double volat = sqrt((deviatia_standard(head, rand_mediu))/(n - 1));
            fprintf(fout, "%.3lf\n", trunchiere(volat));
            double sharpe_ratio;
            if (volat) 
                sharpe_ratio = (rand_mediu / volat);
            else 
                sharpe_ratio = 0;
            fprintf(fout, "%.3lf\n", trunchiere(sharpe_ratio));

            stergereLista(&head);
        }
        else {
            fprintf(fout, "task 4\n");
        }
    }
    else { //nu e nr => task 2 sau 3
        if (strchr(buffer, ',') == NULL) { //task 2 
            node *piata1 = NULL; char p1[32];
            node *piata2 = NULL; char p2[32];
            node *piata3 = NULL; char p3[32];

            sscanf(buffer, "%31[^\r\n]", p1);
            while(fgets(buffer, 128, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9')
                push(&piata1, atof(buffer));

            sscanf(buffer, "%31[^\r\n]", p2);
            while(fgets(buffer, 128, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9')
                push(&piata2, atof(buffer));

            sscanf(buffer, "%31[^\r\n]", p3);
            while(fgets(buffer, 128, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9') 
                push(&piata3, atof(buffer));

            int zi = 1;
            while (piata1 != NULL && piata2 != NULL && piata3 != NULL) {
                float x = pop(&piata1);
                float y = pop(&piata2);
                float z = pop(&piata3);

                Queue *Qhead = createQueue();
                if (x == y && y != z) {
                    sprintf(buffer, "ziua %d - %.2lf - %s\n", zi, fabs(x - z), p3);
                    Qpush(Qhead, buffer);
                }
                if (x == z && z != y) {
                    sprintf(buffer, "ziua %d - %.2lf - %s\n", zi, fabs(x - y), p2);
                    Qpush(Qhead, buffer);
                }
                if (y == z && x != y) {
                    sprintf(buffer, "ziua %d - %.2lf - %s\n", zi, fabs(y - x), p1);
                    Qpush(Qhead, buffer);
                } 
                while (Qhead->front != NULL) {
                    char *msg = Qpop(Qhead); 
                    if (msg != NULL) {
                        fprintf(fout, "%s", msg);
                        free(msg);
                    }
                }
                free(Qhead);
                zi ++;
            }

            deleteStack(&piata1);
            deleteStack(&piata2);
            deleteStack(&piata3);
        }
        else { //task3
            actiune vector[15];
            int nra, nrp, curent = 0; const char *temp = strtok(buffer, ","); //pana la prima virgula
            while (temp != NULL) {
                strcpy(vector[curent].nume, temp);
                curent ++;
                temp = strtok(NULL, ",\n"); // de unde a ramas la urmatoarea virgula sau newline
            }
            nra = curent; // nr de actiuni (nr de el de pe linie)
            for (int linie = 0; linie < 5; linie ++) { //pentru preturi
                if (fgets(buffer, 128, fin) == NULL) break; 

                curent = 0; temp = strtok(buffer, ",\n");
                while (temp != NULL) {
                    float x = atof(temp);
                    vector[curent].pret[linie] = x;
                    curent ++; 
                    temp = strtok(NULL, ",\n");
                }
                nrp = linie + 1; //nr de preturi (nr de el de pe coloana)
            } //stim fiecare actiune si preturile ei.

            tree *root = newTreeNode("");
            for (int i = 0; i < nra; i ++) 
                insertTree(root, vector, i, nrp);
            levelOrderTraversal(root, fout);

            char mtemp[12][15];
            actiuneSimetrica(root->left, root->right, vector, mtemp);
            deleteTree(&root);
        }
    }

    fclose(fin);
    fclose(fout);
    return 0;
}