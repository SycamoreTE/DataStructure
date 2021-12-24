#include "StackQueueOperation_12_21.h"
#include <stdio.h>
#include <stdlib.h>

void visit(BiTNode *b){
    if(b != NULL){
        printf("%d ->\t", b->data);
    }
}

void PreOrder(BiTree T){
    if(T != NULL){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

/**先序遍历非递归**/
void PreOrder2(BiTree T){
    SqStack S;
    InitStack(&S);
    if(T){
        BiTNode *p = T;
        while(p || !StackEmpty(S)){
            if(p){
                visit(p);
                Push(&S, p);
                p = p->lchild;
            }else{
                Pop(&S, &p);
                p = p->rchild;
            }
        }
    }
}

void InOrder(BiTree T){
    if(T){
        InOrder(T->lchild);
        visit(T);
        InOrder(T->rchild);
    }
}

/**中序遍历非递归**/
void InOrder2(BiTree T){
    SqStack S;
    InitStack(&S);
    if(T){
        BiTNode *p = T;
        while(p || !StackEmpty(S)){
            if(p){
                Push(&S, p);
                p = p->lchild;
            }else{
                Pop(&S, &p);
                visit(p);
                p = p->rchild;
            }
        }
    }
}

void PostOrder(BiTree T){
    if(T){
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        visit(T);
    }
}

/**后序遍历非递归**/
void PostOrder2(BiTree T){
    SqStack S;
    InitStack(&S);
    if(T){
        BiTNode *p = T, *r = NULL;
        while(p || !StackEmpty(S)){
            if(p){
                Push(&S, p);
                p = p->lchild;
            }else{
                GetTop(&S, &p);
                if(p->rchild && p->rchild != r){
                    p = p->rchild;
                }else{
                    Pop(&S, &p);
                    visit(p);
                    r = p;
                    p = NULL;
                }
            }
        }
    }
}

/**层次遍历**/
void LevelTraverse(BiTree T){
    SqQueue Q;
    InitQueue(&Q);
    BiTNode *p = T;
    EnQueue(&Q, p);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        visit(p);
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
    }
}

ThreadNode *pre = NULL;

void visitThreadNode(ThreadNode *T){
    if(T){
        if(T->lchild == NULL){
            T->lchild = pre;
            T->ltag = 1;
        }
        if(pre && pre->rchild == NULL){
            pre->rchild = T;
            pre->rtag = 1;
        }
        pre = T;
    }
}

void InThread(ThreadTree T){
    if(T){
        InThread(T->lchild);
        visitThreadNode(T);
        InThread(T->rchild);
    }
}

void CreateInThread(ThreadTree T){
    if(T){
        InThread(T);
    }
    if(pre->rchild == NULL){
        pre->rtag = 1;
    }
}

ThreadNode *FisrtNode(ThreadNode *p){
    while(p->ltag == 0){
        p = p->lchild;
    }
    return p;
}

ThreadNode *NextNode(ThreadNode *p){
    if(p->rtag == 0){
        return FisrtNode(p->rchild);
    }else{
        return p->rchild;
    }
}

void visit2(ThreadNode *p){
    printf("[%d,%d,%d]->",p->ltag,p->data,p->rtag);
}

void InThreadOrder(ThreadNode *T){
    for(ThreadNode *p = FisrtNode(T); p!= NULL; p = NextNode(p)){
        visit2(p);
    }
}

/**4 给出二叉树自下而上，自右而左的层次遍历算法**/
void LevelReverse(BiTree T){
    SqQueue Q;
    InitQueue(&Q);
    SqStack S;
    InitStack(&S);
    BiTNode *p = T;
    EnQueue(&Q, p);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        Push(&S, p);
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
    }
    while(!StackEmpty(S)){
        Pop(&S, &p);
        visit(p);
    }
}

/**5 非递归法求树的高度**/
int BtHeight(BiTree T){
    if(T == NULL){
        return 0;
    }
    SqQueue Q;
    InitQueue(&Q);
    BiTNode *p = T;
    EnQueue(&Q, p);
    int last = 0, level = 0;
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
        if(last == Q.front){
            last = Q.rear;
            level++;
        }
    }
    return level;
}

int BtHeight2(BiTree T){
    if(T == NULL){
        return 0;
    }
    int left = 0, right = 0;
    left = BtHeight2(T->lchild);
    right = BtHeight2(T->rchild);
    if(left > right){
        return left + 1;
    }else{
        return right + 1;
    }
}

/**6 由先序遍历序列和中序遍历序列，建立二叉树的二叉链表**/
BiTree PreInCreate(int pre[], int in[], int l1, int h1, int l2, int h2){
    BiTNode *root = (BiTNode*)malloc(sizeof(BiTNode));
    root->data = pre[l1];
    int llen = 0, rlen = 0, i = 0;
    for(i = l2; root->data != in[i]; i++);
    llen = i - l2;
    rlen = h2 - i;
    if(llen){
        root->lchild = PreInCreate(pre, in, l1+1, l1+llen, l2, l2+llen-1);
    }else{
        root->lchild = NULL;
    }
    if(rlen){
        root->rchild = PreInCreate(pre, in, h1-rlen+1, h1, h2-rlen+1, h2);
    }else{
        root->rchild = NULL;
    }
    return root;
}

/**7 判定二叉树是否是完全二叉树**/
bool IsCompleteTree(BiTree T){
    if(T == NULL){
        return true;
    }
    SqQueue Q;
    InitQueue(&Q);
    BiTNode *p = T;
    EnQueue(&Q, p);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        if(p){
            EnQueue(&Q, p->lchild);
            EnQueue(&Q, p->rchild);
        }else{
            while(!QueueEmpty(Q)){
                DeQueue(&Q, &p);
                if(p){             //空结点后若还有非空结点，不是完全二叉树
                    return false;
                }
            }
        }
    }
    return true;
}

/**8 计算给定二叉树的所有双分支结点个数**/
int CountDNodes(BiTree T){
    int count = 0;
    SqQueue Q;
    InitQueue(&Q);
    BiTNode *p = T;
    EnQueue(&Q, p);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        if(p->lchild && p->rchild){
            count++;
        }
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
    }
    return count;
}

void CreateTree(BiTree *T){
    ElemType data;
    printf("please input root node : ");
    scanf("%d", &data);

    if(data == -1){
        *T = NULL;
    }else{
        *T = (BiTNode*)malloc(sizeof(BiTree)); 
        (*T)->data = data;
        printf("please input %d's lchild node : ", data);
        CreateTree(&(*T)->lchild);
        printf("please input %d's rchild node : ", data);
        CreateTree(&(*T)->rchild);
    }
}

void CreateThreadTree(ThreadTree *T){
    ElemType data;
    printf("please input root node : ");
    scanf("%d", &data);

    if(data == -1){
        *T = NULL;
    }else{
        *T = (ThreadNode*)malloc(sizeof(ThreadNode));
        (*T)->data = data;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        printf("please input %d's lchild node : ", data);
        CreateThreadTree(&(*T)->lchild);
        printf("please input %d's rchild node : ", data);
        CreateThreadTree(&(*T)->rchild);
    }
}

int main(){
    // BiTree T;
    // CreateTree(&T);
    // printf("PreOrder non recursion \n");
    // PreOrder2(T);
    // printf("\nInOrder non recursion \n");
    // InOrder2(T);                                
    // printf("\nPostOrder non recursion \n");
    // PostOrder2(T);
    // printf("\nLevelOrder \n");
    // LevelTraverse(T);
    // printf("\nLevelReverseOrder \n");
    // LevelReverse(T);
    // printf("\n BiTree Height : %d %d\n", BtHeight(T), BtHeight2(T));

    int pre[] = {1,2,4,5,6,3,7,8};
    int in[] = {4,2,6,5,1,7,3,8};
    BiTree b = PreInCreate(pre, in, 0, 7, 0, 7);
    printf("InOrder----\n");
    InOrder(b);

    BiTree tree;
    CreateTree(&tree);
    if(IsCompleteTree(tree)){
        printf("\n is a complete tree");
    }else{
        printf("\n is not a complete tree");
    }

    printf("\n double nodes : %d", CountDNodes(tree));
    // ThreadTree T1;
    // CreateThreadTree(&T1);
    // CreateInThread(T1);
    // printf("inorder-----\n");
    // InThreadOrder(T1);
    return 0;
}