#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild, *rchild;
    int count; //保存以此结点为根的结点个数
} BiTNode, *BiTree;

ElemType pred = 0;
//判定二叉树是否是二叉排序树；中序遍历，前驱结点的值总小于后继结点的值
int JudgeBST(BiTree T){
    if(T == NULL){
        return 1;
    }
    int b1,b2;
    b1 = JudgeBST(T->lchild);
    if(b1 == 0 || pred >= T->data){
        return 0;
    }
    b2 = JudgeBST(T->rchild);
    return b2;
}

//求指定结点在二叉排序树中的层次
int level(BiTree T, BiTNode *p){
    int level = 0;
    BiTNode *q = T;
    if(T){
        level++;
        while(q->data != p->data){
            if(q->data < p->data){
                q = q->rchild;
            }else{
                q = q->lchild;
            }
            level++;
        }
    }
    return level;
}

//二叉排序树插入新结点
int BST_Insert(BiTree T, ElemType k){
    if(T == NULL){
        T = (BiTree)malloc(sizeof(BiTree));
        T->data = k;
        return 1;
    }else if(T->data == k){
        return 0;
    }else if(T->data < k){
        return BST_Insert(T->rchild, k);
    }else{
        return BST_Insert(T->lchild, k);
    }
}

BiTree Create_BST(ElemType data[], int length){
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T = NULL;
    for(int i = 0; i < length; i++){
        BST_Insert(T, data[i]);
    }
    return T;
}

//判断二叉树是平衡二叉树
int JudgeAVL(BiTree T,int *deep){
    if(T == NULL){
        *deep = 0;
        return 1;
    }else if(T->lchild == NULL && T->rchild == NULL){
        *deep = 1;
        return 1;
    }else{
        int left,right;
        if(JudgeAVL(T->lchild, &left)&&JudgeAVL(T->rchild, &right)){
            if(abs(left - right)<= 1){
                *deep = left > right? left+1:right+1;
                return 1;
            }
        }
    }
    return 0;
}

BiTNode* Find_kth_Small(BiTree T, int k){
    if(k<1 || k > (T->count)){
        return NULL;
    }
    if(T->lchild == NULL){
        if(k==1){
            return T;
        }else{
            return Find_kth_Small(T->rchild, k-1);
        }
    }else{
        if(T->lchild->count == k - 1){
            return T;
        }
        if(T->lchild->count > k - 1){
            return Find_kth_Small(T->lchild, k);
        }
        if(T->lchild->count < k - 1){
            return Find_kth_Small(T->rchild, k - (T->lchild->count) - 1);
        }
    }
    return NULL;
}

void visit(BiTNode *node){
    printf("%d-->\t",node->data);
}

void InOrder(BiTree tree){
    if(tree){
        InOrder(tree->lchild);
        visit(tree);
        InOrder(tree->rchild);
    }
}

void initTree(BiTree *T) {
    *T = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->data = 7;
    (*T)->count = 6;
    (*T)->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->data = 5;
    (*T)->lchild->count = 3;
    (*T)->lchild->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->rchild->data = 6;
    (*T)->lchild->rchild->count = 1;
    (*T)->lchild->rchild->lchild = NULL;
    (*T)->lchild->rchild->rchild = NULL;
    (*T)->rchild->data = 9;
    (*T)->rchild->count = 2;
    (*T)->rchild->lchild = NULL;
    (*T)->rchild->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild->rchild->data = 10;
    (*T)->rchild->rchild->count = 1;
    (*T)->rchild->rchild->lchild = NULL;
    (*T)->rchild->rchild->rchild = NULL;
    (*T)->lchild->lchild->data = 3;
    (*T)->lchild->lchild->count = 1;
    (*T)->lchild->lchild->lchild = NULL;
    (*T)->lchild->lchild->rchild = NULL;
}

int main(){
    BiTree tree;
    initTree(&tree);
    InOrder(tree);
    if(JudgeBST(tree)){
        printf("\nIt is a Binary Search Tree");
    }else{
        printf("\nIt's not a Binary Search Tree");
    }
    BiTNode p;
    p.data = 3;
    printf("\n p is in level %d",level(tree, &p));
    BiTree tree1;
    initTree(&tree1);
    int deep = 0;
    if(JudgeAVL(tree1, &deep)){
        printf("\nIt's a balance binary tree");
    }else{
        printf("\nIt's not a balance binaty tree");
    }
    BiTNode *q = Find_kth_Small(tree1, 3);
    printf("\nThe third Small is %d", (*q).data);
    if(BST_Insert(tree1, 8)){
        printf("\nInsert success");
    }else{
        printf("\nInsert failed");
    }
    return 0;
}
