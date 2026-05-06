#include <task3.h>

tree *newTreeNode(const char *numeNou) {
    tree *node = malloc(sizeof(struct tree));
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

int height(tree* root) {
    int hs, hd;
    if (root == NULL) return -1;
    
    hs = height(root->left);
    hd = height(root->right);
    
    return 1 + ((hs > hd) ? hs : hd);
}

void printLevel(tree* root, int level, FILE *fout) {
    if (root == NULL) return;
    
    if (level == 0) {
        fprintf(fout, "%s - ", root->nume);
    } else if (level > 0) {
        printLevel(root->left, level - 1, fout);
        printLevel(root->right, level - 1, fout);
    }
}

void levelOrderTraversal(tree* root, FILE *fout) {
    int h = height(root);
    int i;
    
    for (i = 0; i <= h; i++) {
        printLevel(root, i, fout);
        fprintf(fout, "\n");
    }
}

void deleteTreeUtil(struct tree* root) {
       if (root == NULL) return;
       deleteTreeUtil(root->left);
       deleteTreeUtil(root->right);
       free(root);
}

void deleteTree(struct tree** node_ref) {
  deleteTreeUtil(*node_ref);
  *node_ref = NULL;
}

int isLeaf(const tree *root) {
    if(root->left == NULL && root->right == NULL)
        return 1;
    return 0;
}

void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], char temp[][15], FILE *fout) {
    if (goleft == NULL || goright == NULL)
        return;

    if (isLeaf(goleft) && isLeaf(goright)) { //suntem in 2 noduri simetrice din arbore
        fprintf(fout, ":%s sunt simetrice cu: %s\n", goleft->nume, goright->nume);

    }
    actiuneSimetrica(goleft->left, goright->right, vector, temp, fout);
    actiuneSimetrica(goleft->right, goright->left, vector, temp, fout);
}