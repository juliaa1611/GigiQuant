#include <comun.h>

typedef struct actiune {
    char nume[5];
    float pret[5];
} actiune;

typedef struct tree {
    char nume[128];
    struct tree *left, *right;
} tree;

tree *newTreeNode(const char *numeNou);
void modifyTree(tree *root,const char *added);
void insertTree(tree *root, actiune v[], int i, int nrp);
int height(tree* root);
void printLevel(tree* root, int level, FILE *fout);
void levelOrderTraversal(tree* root, FILE *fout);
void deleteTree(struct tree** node_ref);
void deleteTreeUtil(struct tree* root);
int isLeaf(const tree *root);
void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], char temp[][15], FILE *file);
