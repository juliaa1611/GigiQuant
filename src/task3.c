#include "task3.h"

tree *newTreeNode(const char *numeNou) {
    tree *node = malloc(sizeof(struct tree));
    if (node == NULL) return NULL;
    strcpy(node->nume, numeNou);
    node->left = NULL;
    node->right = NULL;
    return node;
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
    for (int j = 1; j < nrp; j ++) {
        if (v[i].pret[j] >= v[i].pret[j - 1]) { // -> dreapta
            if(curent->right == NULL) 
                curent->right = newTreeNode(v[i].nume);
            else 
                modifyTree(curent->right, v[i].nume);
            curent = curent->right;
        }
        else {
            if(curent->left == NULL) 
                curent->left = newTreeNode(v[i].nume);
            else 
                modifyTree(curent->left, v[i].nume);
            curent = curent->left;
        }
    }
}

void deleteTree(struct tree** root) {
    tree *temp = *root;
    if (*root == NULL) return;
    deleteTree(&temp->left);
    deleteTree(&temp->right);
    free(temp);
    *root = NULL;
}

int isLeaf(const tree *root) {
    if(root->left == NULL && root->right == NULL)
        return 1;
    return 0;
}

int find_index(actiune vector[], int nra, const char *a) {
    for (int i = 0; i < nra; i ++) {
        if(strcmp(vector[i].nume, a) == 0)
            return i;
    }
    return -1;
}

void read_names(actiune vector[], const char *temp, int *curent) {
    while (temp != NULL) {
        strcpy(vector[(*curent)].nume, temp);
        (*curent) ++;
        temp = strtok(NULL, ",\n"); // de unde a ramas la urmatoarea virgula sau newline
    }
}

void read_value(actiune vector[], int *nrp, const char *temp, char *buffer, FILE *fin) {
    for (int linie = 0; linie < 5; linie ++) { //pentru preturi
        if (fgets(buffer, 128, fin) == NULL) break; 

        int curent = 0; temp = strtok(buffer, ",\n");
        while (temp != NULL) {
            float x = atof(temp);
            vector[curent].pret[linie] = x;
            curent ++; 
            temp = strtok(NULL, ",\n");
        }
        (*nrp) = linie + 1; //nr de preturi (nr de el de pe coloana)
    } //stim fiecare actiune si preturile ei.
}

void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], int nra, char mtemp[][24], int *total_sim, FILE *fout) {
    if (goleft == NULL || goright == NULL)
        return;

    if (isLeaf(goleft) && isLeaf(goright)) { //suntem in 2 noduri simetrice din arbore
        //fprintf(fout, ":%s sunt simetrice cu: %s\n", goleft->nume, goright->nume);
        char temp_left[64]; strcpy(temp_left, goleft->nume);
        char temp_right[64]; strcpy(temp_right, goright->nume);

        char *ast[10]; char *adr[10]; //vector pt fiecare din actiuni
        int nrs = 0; int ndr = 0; //nr pt fiecare

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

        for (int i = 0; i < nrs; i ++) {
            int index_left = find_index(vector, nra, ast[i]);
            for (int j = 0; j < ndr; j ++) {
                int index_right = find_index(vector, nra, adr[j]);

                if (index_left < index_right) 
                    sprintf(mtemp[(*total_sim)], "%s-%s", ast[i], adr[j]);
                else 
                    sprintf(mtemp[(*total_sim)], "%s-%s", adr[j], ast[i]);
                (*total_sim)++;
            }
        }
    }
    actiuneSimetrica(goleft->left, goright->right, vector, nra, mtemp, total_sim, fout);
    actiuneSimetrica(goleft->right, goright->left, vector, nra, mtemp, total_sim, fout);
}

void afisareSimetrica(
    const char mtemp[][24], actiune vector[], int nra, int total_sim, FILE *fout) {
    for (int i = 0; i < nra; i ++) {
        for (int j = 0; j < total_sim; j ++) {
            if (strncmp(mtemp[j], vector[i].nume, 4) == 0)//primele 4 litere egale
                fprintf(fout, "%s\n", mtemp[j]);
        }            
    }
}