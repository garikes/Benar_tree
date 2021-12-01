#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <ctype.h>
#include <stdbool.h>

struct country {
    char name[20];
    int inhabitants;
};
typedef struct tree {
    struct country key;
    struct tree* left;
    struct tree* right;
} node;

node* root;

node* newNode() {
    node* pel;
    char name[20];
    int inhabitants = 0;
    printf("Enter name of the country: ");
    scanf("%s", &name);
    if (!strcmp(name, "-"))
        return NULL;
    printf_s("Enter inhabitants of the country: ");
    scanf_s("%d", &inhabitants);
    pel = (node*)malloc(sizeof(node));
    pel->key.inhabitants = inhabitants;
    strcpy(pel->key.name, name);
    pel->left = pel->right = NULL;
    return pel;
}
node* newNodeFile(char* name, int pop) {
    node* pel;
    if (strlen(name) > 19) {
        return NULL;
}
    pel = (node*)malloc(sizeof(node));
    pel->key.inhabitants = pop;
    strcpy(pel->key.name, name);
    pel->left = pel->right = NULL;
    return pel;
}
void addNode(node* pnew) {
    if (root == NULL) {
        root = pnew;
        return;
}
node* par = root;
do {
    if (strcmp(pnew->key.name, par->key.name) == 0) {
    free(pnew);
return;
}
    if (strcmp(pnew->key.name, par->key.name) > 0) {
    if (par->right == NULL) {
        par->right = pnew;
        return;
    }
    else {
        par = par->right;
    }
}
    else {
        if (par->left == NULL) {
            par->left = pnew;
            return;
}
    else {
        par = par->left;
    }
    }
} while (1);
}
bool iterativeSearch(node* root, char* name)
{
// Traverse untill root reaches to dead end
    while (root != NULL) {
// pass right subtree as new tree
    if (strcmp(root->key.name, name) < 0)
    root = root->right;
// pass left subtree as new tree
    else if (strcmp(root->key.name, name) > 0)
    root = root->left;
        else {
            printf("Counry: %s\n"
            "Inhabitants: %d\n", root->key.name, root->key.inhabitants);
            return 1;
}
}
printf("The is no country");
return 0;
}
node* rightRotate(node* y)
{
    node* x = y->left;
    node* T2 = x->right;
    x->right = y;
    y->left = T2;
    return x;
}
void task3_2(node* elem) {
    if (elem == NULL) {
    return;
}
    else if (elem->left != NULL && elem->left->left != NULL) {
    if (elem->left->right == NULL && elem->left->left->right == NULL) {
    elem->left = rightRotate(elem->left);
}
}
    else if (elem->right != NULL && elem->right->left != NULL) {
        if (elem->right->right == NULL && elem->right->left->right == NULL) {
            elem->right = rightRotate(elem->right);
}
}
task3_2(elem->left);
task3_2(elem->right);
}
    node* search(node* elem, char* name)
{
    if ((root == NULL) || (strcmp(elem->key.name, name) == 0)) {
    printf("Counry: %s\n"
    "Inhabitants: %d\n", elem->key.name, elem->key.inhabitants);
    return elem;
}
    if (strlen(elem->key.name) >= strlen(name))
       return search(elem->left, name);
    else if (strlen(elem->key.name) < strlen(name))
        return search(elem->right, name);
    else {
        printf("The is no country");
        return 0;
}
}
void freeTree(node* proot)
{
    if (proot == NULL)
return;
    freeTree(proot->right);
    freeTree(proot->left);
    free(proot);
}

void printTree(node* root) {
    if (root == NULL)
        return;
    if (root->key.inhabitants)
    printf("%s - ", root->key.name);
printTree(root->left);
printTree(root->right);
}
void file_input(char path[]) {
    FILE* fp;
    char buffer[50];
    int pop;
    fp = fopen(path, "r");
    if (fp == NULL) {
        puts("Неможливо відкрити файл");
        return;
}
while (!feof(fp)) {
    fgets(buffer, 50, fp);
    buffer[strcspn(buffer, "\n")] = 0;
    fscanf(fp, "%d\n", &pop);
    node* np = newNodeFile(buffer, pop);
    if (np != NULL) {
        addNode(np);
}
}
fclose(fp);
return;
}
int main() {
    system("chcp 1251");
    char path[] = "input.txt";
    file_input(path);
    printTree(root);
    char name[20];
for (int i = 0; i < 3; i++) {
    printf("\nEnter country to search: ");
    scanf("%s", &name);
    iterativeSearch(root, name);
}

task3_2(root);
printTree(root);
freeTree(root);
root = NULL;

}