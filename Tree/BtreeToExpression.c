#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType char

typedef struct BtNode{
    ElemType data;
    struct BtNode *left, *right;
} BtNode, *BiTree;

void BtreeToExp(BiTree tree, int deep){
    if(tree == NULL){
        return;
    }else if(tree->left == NULL && tree->right == NULL){
        printf("%c",tree->data);
    }else{
        if(deep > 1){
            printf("(");
        }
        BtreeToExp(tree->left, deep+1);
        printf("%c",tree->data);
        BtreeToExp(tree->right, deep+1);
        if(deep > 1){
            printf(")");
        }
    }
}

void BiTreeToExpression(BiTree T, int depth){
    if(T){
        if(depth > 1){
            printf("(");
        }
        BiTreeToExpression(T->left, depth+1);
        printf("%c", T->data);
        BiTreeToExpression(T->right, depth+1);
        if(depth > 1){
            printf(")");
        }
    }
}

void InitTree(BiTree *T){
    (*T) = (BtNode*)malloc(sizeof(BtNode));
    (*T)->data = '+';
    (*T)->left = (BtNode*)malloc(sizeof(BtNode));
    (*T)->right = (BtNode*)malloc(sizeof(BtNode));
    (*T)->left->data = '*';
    (*T)->right->data = '-';
    (*T)->right->left = NULL;
    (*T)->left->left = (BtNode*)malloc(sizeof(BtNode));
    (*T)->left->right = (BtNode*)malloc(sizeof(BtNode));
    (*T)->left->left->data = 'a';
    (*T)->left->right->data = 'b';
    (*T)->left->left->left = NULL;
    (*T)->left->left->right = NULL;
    (*T)->left->right->left = NULL;
    (*T)->left->right->right = NULL;
    (*T)->right->right = (BtNode*)malloc(sizeof(BtNode));
    (*T)->right->right->data = '-';
    (*T)->right->right->left = (BtNode*)malloc(sizeof(BtNode));
    (*T)->right->right->right = (BtNode*)malloc(sizeof(BtNode));
    (*T)->right->right->left->data = 'c';
    (*T)->right->right->left->left = NULL;
    (*T)->right->right->left->right = NULL;
    (*T)->right->right->right->data = 'd';
    (*T)->right->right->right->left = NULL;
    (*T)->right->right->right->right = NULL;
}

int main(){
    BiTree tree;
    InitTree(&tree);
    BtreeToExp(tree, 1);
    BiTreeToExpression(tree, 1);
}