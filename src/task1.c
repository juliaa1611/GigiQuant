#include "task1.h"

node *creeareNod(double value) {
    node *newNode = (node*)malloc(sizeof(node));   
    if (!newNode) 
        return NULL;

    newNode->valoare = value;
    newNode->next = NULL;
    return (newNode);
}

void adaugare(node **head, double value) {
    node *newNode = creeareNod(value);

    if (*head == NULL) {
        *head = newNode;
        return;
    }
    node *curent = *head;
    while (curent->next != NULL) //parcurgere pana la capatul listei
        curent = curent->next;
    
    curent->next = newNode;
    return;
}

void stergereLista(node **head) {
    node *temp;
    while (*head != NULL) {
        temp = (*head)->next;
        free (*head);
        *head = temp;
    }
    *head = NULL;
    return;
}

double randament(double pt, double pt_anterior) {
    return ((pt-pt_anterior)/pt_anterior); //dupa formula (P(t)-P(t-1))/P(t)
}

double calculareRandamentTotal(node *head) {
    if (head == NULL)
        return 0;

    double randament_total = 0;
    head->randament = 0;//primul randament e 0 (nu exista anterior)
    node *curent = head->next; //pornim de la urmatorul element
    const node *anterior = head; //tinem minte si anteriorul

    while (curent != NULL) {
        curent->randament = randament(curent->valoare, anterior->valoare);
        randament_total += curent->randament;

        anterior = curent;
        curent = curent->next;
    }
    return randament_total;
}

double deviatia_standard(node *head, double rand_mediu) {
    if (head == NULL || head->next == NULL)
        return 0;
    
    double suma = 0; 
    head = head->next; //la fel ca la randament, pornim de la urmatorul element
    while (head != NULL) {
        double diferenta = (head->randament - rand_mediu); //calc diferenta la fiecare pas
        suma += diferenta * diferenta; //si ridicam la patrat conform formulei
        head = head->next;
    }
    return suma;
}

double trunchiere(double x) {
    return trunc(x * 1000.0)/1000.0; //trunchiere la 3 zecimale
}

int verificaretask1(double *temp2, FILE *fin) {
    char buffer[64];
    fscanf(fin, "%63s", buffer);
    if (strchr(buffer, '.') != NULL) { //daca nu gaseste punct este numar intreg => task1
        (*temp2) = atof(buffer); //transformam si returnam numarul intreg
        return 1;
    }
    (*temp2) = atoi(buffer);
    return 0;
}

void citirefisiertask1(FILE *fin, int n, node **head) {
    for (int i = 0; i < n - 2; i ++) { //primele 2 linii au fost deja citite in main deci raman n-2 linii
        double temp;
        fscanf(fin, "%lf", &temp);
        adaugare(head, temp); //se citesc si se adauga in lista
    }
}

void calculare_volat(node *head, FILE *fout, int n) {
    double rand_mediu = (calculareRandamentTotal(head) / (n - 1));
    fprintf(fout, "%.3lf\n", trunchiere(rand_mediu)); //se trunchiaza randamentul total
    double volat = sqrt((deviatia_standard(head, rand_mediu))/(n - 1));
    fprintf(fout, "%.3lf\n", trunchiere(volat)); //se trunchiaza si volatilitatea
    double sharpe_ratio;
    if (volat) //numitor diferit de 0
        sharpe_ratio = (rand_mediu / volat); 
    else  
        sharpe_ratio = 0;
    fprintf(fout, "%.3lf\n", trunchiere(sharpe_ratio)); //afisam si ultima valoare trunchiata
}
