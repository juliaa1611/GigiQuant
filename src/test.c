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

    char buffer[64];
    fgets(buffer, 64, fin);

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
        else
        {
            fprintf(fout, "task 4\n");
        }
    }
    else { //nu e nr => task 2 sau 3
        if (strchr(buffer, ',') == NULL) { //task 2 
            node *piata1 = NULL; char p1[32];
            node *piata2 = NULL; char p2[32];
            node *piata3 = NULL; char p3[32];

            sscanf(buffer, "%31[^\r\n]", p1);
            while(fgets(buffer, 64, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9')
                push(&piata1, atof(buffer));

            sscanf(buffer, "%31[^\r\n]", p2);
            while(fgets(buffer, 64, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9')
                push(&piata2, atof(buffer));

            sscanf(buffer, "%31[^\r\n]", p3);
            while(fgets(buffer, 64, fin) != NULL && buffer[0] >= '0' && buffer[0] <= '9') 
                push(&piata3, atof(buffer));

            int zi = 1;
            while (piata1 != NULL && piata2 != NULL && piata3 != NULL) {
                float x = pop(&piata1);
                float y = pop(&piata2);
                float z = pop(&piata3);

                if (x == y && y != z) 
                    fprintf (fout, "ziua %d - %.2lf - %s\n", zi, fabs(x - z), p3);
                if (x == z && z != y)
                    fprintf (fout, "ziua %d - %.2lf - %s\n", zi, fabs(x - y), p2);
                if (y == z && x != y)
                    fprintf (fout, "ziua %d - %.2lf - %s\n", zi, fabs(y - x), p1);
                zi ++;
            }

            deleteStack(&piata1);
            deleteStack(&piata2);
            deleteStack(&piata3);
        }
        else { //task3
            
        }
    }
    

    fclose(fin);
    fclose(fout);
    return 0;
}