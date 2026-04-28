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
    while (curent->next != NULL)
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
    return ((pt-pt_anterior)/pt_anterior);
}

double calculareRandamentTotal(node *head) {
    if (head == NULL)
        return 0;

    double randament_total = 0;
    head->randament = 0;
    node *curent = head->next;
    const node *anterior = head;

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
    head = head->next;
    while (head != NULL) {
        double diferenta = (head->randament - rand_mediu);
        suma += diferenta * diferenta;
        head = head->next;
    }
    return suma;
}

double trunchiere(double x) {
    return trunc(x * 1000.0)/1000.0;
}

int verificaretask1(double *temp2, FILE *fin) {
    char buffer[64];
    fscanf(fin, "%63s", buffer);
    if (strchr(buffer, '.') != NULL) {
        (*temp2) = atof(buffer);
        return 1;
    }
    (*temp2) = atoi(buffer);
    return 0;
}

void citirefisiertask1(FILE *fin, int n, node **head) {
    for (int i = 0; i < n - 2; i ++) {
        double temp;
        fscanf(fin, "%lf", &temp);
        adaugare(head, temp);
    }
}

void push(node **top, double newData) {
    node *newNode = malloc(sizeof(node));
    newNode->valoare = newData;
    newNode->next = (*top);
    (*top) = newNode;
    return;
}

double pop(node **top) {
    node *temp = (*top);
    double aux = temp->valoare;
    (*top) = (*top)->next;
    free(temp);
    return aux;
}

int isEmpty(const node *top) {
    if (top == NULL)
        return 1;
    else return 0;
}

void deleteStack(node **top) {
    while(!isEmpty(*top)) {
        node *temp = (*top);
        (*top) = (*top)->next;
        free(temp);
    }
    return;
}

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

void actiuneSimetrica(tree *goleft, tree *goright, actiune vector[], char temp[][15]) {
    if (goleft == NULL || goright == NULL)
        return;

    if (isLeaf(goleft)&& isLeaf(goright)) {
        //am gasit 2 actiuni simetrice
    }
    actiuneSimetrica(goleft->left, goright->right, vector, temp);
    actiuneSimetrica(goleft->right, goright->left, vector, temp);
}

void Qpush(Queue *q, const char *v) {
    Qnode *newNode = malloc(sizeof(Qnode));
    strncpy(newNode->value, v, 63);
    newNode->value[63] = '\0';
    newNode->next = NULL;

    if (q->rear == NULL)
        q->rear = newNode;
    else {
        (q->rear)->next = newNode;
        q->rear = newNode;
    }
    if (q->front == NULL)
        q->front=q->rear;
    return;
}

char *Qpop(Queue *q) {
    if (q->front == NULL) 
        return NULL;

    Qnode *aux = q->front;
    char *d = malloc(64 * sizeof(char)); 
    if (d == NULL) 
        return NULL;
    strcpy(d,aux->value);
    q->front = (q->front)->next;
    free(aux);
    return d;
}

Queue* createQueue() {
    Queue* q;
    q = (Queue *)malloc(sizeof(Queue));
    if (q == NULL)
        return NULL;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

