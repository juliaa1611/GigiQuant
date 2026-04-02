#include "task1.h"

int main(int argc, const char* argv[])
{
    if (argc < 3)
    {
        printf("Compilat fara toate fisierele!\n"); 
        return 0;
    }

    FILE *fin, *fout;
    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");
    if (!fin)
    {
        printf("Eroare la fisierul de intrare!\n");
        fclose(fout);
        return 0;
    }
    if (!fout)
    {
        printf("Eroare la fisierul de iesire!\n");
        fclose (fin);
        return 0;
    }

    int n;

    //inceput task 1
    if (fscanf(fin, "%d", &n) != 1 || n <= 1)
    {
        fclose(fin);
        fclose(fout);
        return 0;
    }

    node *head = NULL;
    for (int i = 0; i < n; i ++)
    {
        double temp;
        fscanf(fin, "%lf", &temp);
        adaugare(&head, temp);
    }

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
    //sfarsit task1

    stergereLista(&head);
    fclose(fin);
    fclose(fout);
    return 0;
}