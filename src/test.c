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

    int n = task1sau4(fin, fout); //prima data din fisier
    if (n > 0) { //daca e nr => task1 sau task4

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
    }
    

    fclose(fin);
    fclose(fout);
    return 0;
}