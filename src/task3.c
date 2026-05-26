#include "task3.h"

void newTreeNode(tree **node, const char *numeNou) {
    *node = malloc(sizeof(tree));
    if (*node != NULL) {
        strcpy((*node)->nume, numeNou);
        (*node)->left = NULL;
        (*node)->right = NULL;
    }
}

void modifyTree(tree *root, const char *added) {
    if (root == NULL) 
        return;
    if (strlen(root->nume) > 0) {
        strcat(root->nume, " "); 
    }
    strcat(root->nume, added);
    return;
}

void insertTree(tree *root, actiune v[], int i, int nrp) {
    tree *curent = root;
    for (int j = 1; j < nrp; j ++) { //nrp - nr de preturi
        if (v[i].pret[j] >= v[i].pret[j - 1]) { // daca e mai mare mergem in dreapta
            if(curent->right == NULL) //daca nu exista deja nod existent in dreapta
                newTreeNode(&(curent->right), v[i].nume); //creem un nod nou
            else 
                modifyTree(curent->right, v[i].nume); //altfel il modificam pe cel existent
            curent = curent->right;
        }
        else { //analog stanga
            if(curent->left == NULL) 
                newTreeNode(&(curent->left), v[i].nume);
            else 
                modifyTree(curent->left, v[i].nume);
            curent = curent->left;
        }
    }
}

void deleteTree(tree* root) {
    if (root == NULL) return;
    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int isLeaf(const tree *root) {
    if(root->left == NULL && root->right == NULL)
        return 1;
    return 0;
}

int find_index(actiune vector[], int nra, const char *a) {
    //functie care gaseste index-ul unei actiuni in ordinea data initial
    for (int i = 0; i < nra; i ++) 
        if(strcmp(vector[i].nume, a) == 0)
            return i;
    return -1;
}

void read_names(actiune vector[], const char *temp, int *curent) {
    //in structura de nume a vectorului de actiuni salveaza fiecare actiune
    while (temp != NULL) {
        strcpy(vector[(*curent)].nume, temp);
        (*curent) ++;
        temp = strtok(NULL, ",\n"); //continua de unde a ramas pana la urmatoarea virgula sau newline
    }
}

void read_value(actiune vector[], int *nrp, const char *temp, char *buffer, FILE *fin) {
    for (int linie = 0; linie < 5; linie ++) {
        if (fgets(buffer, 128, fin) == NULL) break; 

        int curent = 0; temp = strtok(buffer, ",\n"); //incepem cu primul pret
        while (temp != NULL) {
            float x = atof(temp); //transf char-ul in float
            vector[curent].pret[linie] = x;
            curent ++; 
            temp = strtok(NULL, ",\n");//pana la urmatorul pret sau newline
        }
        (*nrp) = linie + 1; //nr de preturi (nr de el de pe coloana)
    } //astfel am salvat fiecare actiune si preturile ei.
}

void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], int nra, char mtemp[][24], int *total_sim, FILE *fout) {
    if (goleft == NULL || goright == NULL)
        return;

    if (isLeaf(goleft) && isLeaf(goright)) { //suntem in 2 frunze simetrice din arbore
        char temp_left[64]; strcpy(temp_left, goleft->nume);
        char temp_right[64]; strcpy(temp_right, goright->nume);

        char *ast[10]; char *adr[10]; //vector pt actiunile din stanga respectiv dreapta
        int nrs = 0; int ndr = 0; //nrs-nr de act din nodul din stanga; nrd-pt dreapta

        char *buffer = strtok(temp_left, " \n");
        while (buffer != NULL) {
            ast[nrs] = buffer;
            nrs ++;
            buffer = strtok(NULL, " \n");
        } //am adaugat toate act din stanga

        buffer = strtok(temp_right, " \n");
        while (buffer != NULL) {
            adr[ndr] = buffer;
            ndr ++;
            buffer = strtok(NULL, " \n");
        } //am adaugat toate act din dreapta

        for (int i = 0; i < nrs; i ++) { //pt fiecare el din stanga
            int index_left = find_index(vector, nra, ast[i]); //gasim indexul
            for (int j = 0; j < ndr; j ++) { //pt fiecare el din dreapta
                int index_right = find_index(vector, nra, adr[j]); //gasim si indexul lui
                //salvam in ordinea index-ului mai mic
                if (index_left < index_right) 
                    sprintf(mtemp[(*total_sim)], "%s-%s", ast[i], adr[j]); //total_sim -> nr total de actiuni simetrice
                else 
                    sprintf(mtemp[(*total_sim)], "%s-%s", adr[j], ast[i]);
                (*total_sim)++;
            }
        }
    }
    //parcurgem recursiv cu 2 pointeri, fie amandoi spre exterior, fie amandoi spre interior pt a asigura simetria
    actiuneSimetrica(goleft->left, goright->right, vector, nra, mtemp, total_sim, fout);
    actiuneSimetrica(goleft->right, goright->left, vector, nra, mtemp, total_sim, fout);
}

void afisareSimetrica(
    const char mtemp[][24], actiune vector[], int nra, int total_sim, FILE *fout) {
    //folosim oridnea initiala a vectorului pentru afisarea actiunilor simetrice
    for (int i = 0; i < nra; i ++) 
        for (int j = 0; j < total_sim; j ++) 
            if (strncmp(mtemp[j], vector[i].nume, 4) == 0)
                fprintf(fout, "%s\n", mtemp[j]);
}