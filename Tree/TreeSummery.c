#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "StackQueueOperation.h"

#define ElemType int

void visit(BiTNode *T){
    printf("%d-->",T->data);
}

void PreOrder(BiTree T){
    if(T){
        visit(T);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void PreOrder2(BiTree T){
    SqStack S;
    InitStack(&S);
    if(T){
        BiTNode *p = T;
        while(p || !StackEmpty(S)){
            if(p){
                visit(p);
                Push(&S,p);
                p = p->lchild;
            }else{
                Pop(&S,&p);
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

void InOrder2(BiTree T){
    SqStack S;
    InitStack(&S); BiTNode *p = T;
    while(p || !StackEmpty(S)){
        if(p){
            Push(&S,p);
            p = p->lchild;
        }else{
            Pop(&S,&p);
            visit(p);
            p = p->rchild;
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

void PostOrder2(BiTree T){
    SqStack S;
    InitStack(&S);
    BiTNode *p = T, *r = NULL;
    while(p || !StackEmpty(S)){
        if(p){
            Push(&S,p);
            p = p->lchild;
        }else{
            GetTop(&S, &p);
            if(p->rchild && p->rchild != r){
                p = p->rchild;
            }else{
                Pop(&S,&p);
                visit(p);
                r = p;
                p = NULL;
            }
        }
    }
}

void LevelReverse(BiTree T){
    BiTNode *p = T;
    SqQueue Q;
    InitQueue(&Q);
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

void InverseLevel(BiTree T){
    BiTNode *p = T;
    SqQueue Q; 
    SqStack S;
    InitQueue(&Q);
    InitStack(&S);
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
        Pop(&S,&p);
        visit(p);
    }
}

int TreeHeight(BiTree T){
    if(T == NULL){
        return 0;
    }
    SqQueue Q;
    InitQueue(&Q);
    int last = 0, level = 0;
    BiTNode *p = T;
    EnQueue(&Q, p);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
        if(Q.front == last){
            last = Q.rear;
            level++;
        }
    }
    return level;
}

int HeightRecursion(BiTree T){
    if(T == NULL){
        return 0;
    }
    int left,right;
    left = HeightRecursion(T->lchild);
    right = HeightRecursion(T->rchild);
    if(left >= right){
        return left+1;
    }else{
        return right+1;
    }
}

BiTree PreInCreate(ElemType pre[],ElemType in[],int l1, int h1, int l2, int h2){
    BiTNode *root = (BiTNode*)malloc(sizeof(BiTNode));
    root->data = pre[l1];
    int llen, rlen, i;
    for(i = l2; in[i] != root->data; i++);
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

bool IsCompleteTree(BiTree T){
    SqQueue Q;
    InitQueue(&Q);
    if(!T){
        return true;
    }
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
                if(p){
                    return false;
                }
            }
        }
    }
    return true;
}

int CountNodes(BiTree T){
    int count = 0;
    if(T == NULL){
        return 0;
    }
    BiTNode *p = T;
    SqQueue Q;
    InitQueue(&Q);
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

void SwapTree(BiTree T){
    if(T){
        BiTNode *p = T->lchild;
        T->lchild = T->rchild;
        T->rchild = p;
        SwapTree(T->lchild);
        SwapTree(T->rchild);
    }
}

//求先序遍历的第k个结点的值
ElemType PreNode_k(BiTree b, int k){
    SqStack S;
    InitStack(&S);
    BiTNode *p = b;
    int count = 0;
    while(p || !StackEmpty(S)){
        if(p){
            visit(p);
            count++;
            if(count == k){
                return p->data;
            }
            Push(&S,p);
            p = p->lchild;
        }else{
            Pop(&S,&p);
            p = p->rchild;
        }
    }
    return -1;
}

//删除以x为根的子树
void DeleteXTree(BiTNode *t){
    if(t){
        DeleteXTree(t->lchild);
        DeleteXTree(t->rchild);
    }
    free(t);
}

void SearchXTree(BiTree T, ElemType x){
    BiTNode *p = T;
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, p);
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        if(p->lchild){
            if(p->lchild->data == x){
                DeleteXTree(p->lchild);
                p->lchild = NULL;
            }else{
                EnQueue(&Q, p->lchild);
            }
        }
        if(p->rchild){
            if(p->rchild->data == x){
                DeleteXTree(p->rchild);
                p->rchild = NULL;
            }else{
                EnQueue(&Q, p->rchild);
            }
        }
    }
}

bool Ancestors(BiTree T, SqQueue *Q, ElemType x){
    if(!T){
        return false;
    }
    if(T->data == x){
        return true;
    }
    if(Ancestors(T->lchild, Q, x) || Ancestors(T->rchild, Q, x)){
        EnQueue(Q, T);
        return true;
    }
    return false;
}

void findAncestors(BiTree T, ElemType x){
    SqQueue Q;
    InitQueue(&Q);
    Ancestors(T, &Q, x);
    BiTNode *p;
    while(!QueueEmpty(Q)){
        DeQueue(&Q, &p);
        visit(p);
    }
}

BiTNode* FirstCommonAncestor(BiTree T, ElemType x, ElemType y){
    SqQueue Q1,Q2;
    InitQueue(&Q1);
    InitQueue(&Q2);
    Ancestors(T, &Q1, x);
    Ancestors(T, &Q2, y);
    BiTNode *p, *q;
    while(!QueueEmpty(Q1)){
        DeQueue(&Q1, &p);
        while(!QueueEmpty(Q2)){
            DeQueue(&Q2, &q);
            if(p == q){
                return p;
            }
        }
    }
    return NULL;
}

static int count[100];
static int MAX = -1;

void BiWidth(BiTree T, int k){
    if(T == NULL){
        return;
    }
    count[k]++;
    if(MAX < count[k]){
        MAX = count[k];
    }
    BiWidth(T->lchild, k+1);
    BiWidth(T->rchild, k+1);
}

//已知满二叉树的先序序列pre, 求后序序列post
void PreToPost(int pre[], int post[],int l1, int h1, int l2, int h2){
    if(h1 >= l1){
        int half = (h1-l1)/2;
        post[h2] = pre[l1];
        PreToPost(pre, post, l1+1, l1+half, l2, l2+half-1);
        PreToPost(pre, post, l1+half+1, h1, l2+half, h2-1);
    }
}

bool Similar(BiTree T1, BiTree T2){
    if(T1 == NULL && T2 == NULL){
        return true;
    }else if(T1 == NULL || T2 == NULL){
        return false;
    }else{
        int left = Similar(T1->lchild, T2->lchild);
        int right = Similar(T1->rchild, T2->rchild);
        return left&&right;
    }
}

void ComputeWPL(BiTree T, int *wpl, int depth){
    if(T){
        *wpl += T->data * depth;
        ComputeWPL(T->lchild, wpl, depth+1);
        ComputeWPL(T->rchild, wpl, depth+1);
    }
}

void BiTreeToExpression(BiTree T, int depth){
    if(T == NULL){
        return;
    }else if(T->lchild == NULL && T->rchild == NULL){
        printf("%d",T->data);
    }else{
        if(depth > 1){
            printf("(");
        }
        BiTreeToExpression(T->lchild, depth+1);
        printf("%d ",T->data);
        BiTreeToExpression(T->rchild, depth+1);
        if(depth > 1){
            printf(")");
        }
    }
}

int BST_Insert(BiTree T, ElemType k){
    if(T == NULL){
        T = (BiTNode*)malloc(sizeof(BiTNode));
        T->data = k;
        T->lchild = NULL;
        T->rchild = NULL;
        return 1;
    }else if(T->data == k){
        return -1;
    }else if(T->data > k){
        return BST_Insert(T->lchild, k);
    }else{
        return BST_Insert(T->rchild, k);       
    }
}

//创建排序树
BiTree CreateBST(ElemType data[], int length){
    BiTree T = NULL;
    int i;
    for(i = 0; i < length; i++){
        BST_Insert(T, data[i]);
    }
    return T;
}

static int pred = 0;
bool JudgeBST(BiTree T){
    if(T == NULL){
        return true;
    }
    int b1, b2;
    b1 = JudgeBST(T->lchild);
    if(!b1 || pred >= T->data){
        return false;
    }
    pred = T->data;
    b2 = JudgeBST(T->rchild);
    return b2;
}

bool JudgeBalance(BiTree T, int *deep){
    if(T == NULL){
        *deep = 0;
        return true;
    }else if(T->lchild == NULL && T->rchild == NULL){
        *deep = 1;
        return true;
    }else{
        int left,right;
        if(JudgeBalance(T->lchild,&left)&& JudgeBalance(T->rchild,&right)){
            if(abs(left - right)<=1){
                *deep = left > right? left+1: right+1;
                return true;
            }
        }
    }
    return false;
}

typedef struct Stack{
    ElemType data[MaxSize];
    int top;
}Stack;

int BalanceTreeNodes(int height){
    int minNodes = 0;
    Stack S;
    S.top = -1;
    S.data[0] = 1;
    S.data[1] = 2;
    for(int i = 2; i < height; i++){
        S.data[i] = S.data[i-1] + S.data[i-2] + 1;
        printf("%d\t",S.data[i]);
    }
    return S.data[height-1];
}

//从大到小输出二叉排序树中所有值不小于k的值
void printBST(BiTree T, ElemType k){
    if(T == NULL){
        return;
    }
    if(T->rchild){
        printBST(T->rchild,k);
    }
    if(T->data >= k){
        printf("%d\t",T->data);
    }
    if(T->lchild){
        printBST(T->lchild,k);
    }
}

static ThreadNode *pre = NULL;

void visitThread(ThreadNode *T){
    if(T){
        if(T->lchild == NULL){
            T->lchild = pre;
            T->ltag = 1;
        }
        if(pre != NULL && pre->rchild == NULL){
            pre->rchild = T;
            pre->rtag = 1;
        }
        pre = T;
    }
}

void InThread(ThreadTree T){
    if(T){
        InThread(T->lchild);
        visitThread(T);
        InThread(T->rchild);
    }
}

void CreateInThread(ThreadTree T){
    if(T != NULL){
        InThread(T);
        if(pre->rchild == NULL){
            pre->rtag = 1;
        }
    }
}

void visit2(ThreadNode *p){
    printf("%d,%d,%d-->\t",p->ltag,p->data,p->rtag);
}

ThreadNode* FirstNode(ThreadNode *p){
    while(p->ltag == 0){
        p = p->lchild;
    }
    return p;
}

ThreadNode* NextNode(ThreadNode *p){
    if(p->rtag == 1){
        return p->rchild;
    }else{
        return FirstNode(p->rchild);
    }
} 

void ThreadInOrder(ThreadTree T){
    for(ThreadNode *p = FirstNode(T); p != NULL; p = NextNode(p)){
        visit2(p);
    }
}

//在中序线索二叉树中查找指定结点在后序的前驱结点
ThreadNode* InPostPre(ThreadTree T, ThreadNode *p){
    ThreadNode *q;
    if(p->rtag == 0){
        q = p->rchild;
    }else if(p->ltag == 0){
        q = p->lchild;
    }else if(p->lchild == NULL){
        q = NULL;
    }else{
        while(p->ltag == 1 && p->lchild != NULL){
            p = p->lchild;
        }
        if(p->ltag == 0){
            q = p->lchild;
        }else{
            q = NULL;
        }
    }
    return q;
}

BiTree CreateTree(){
    BiTree T = (BiTree)malloc(sizeof(BiTNode));
    T->data = 1;
    T->lchild = (BiTNode*)malloc(sizeof(BiTNode));
    T->rchild = (BiTNode*)malloc(sizeof(BiTNode));
    T->lchild->data = 2;
    T->rchild->data = 3;
    T->lchild->lchild = (BiTNode*)malloc(sizeof(BiTNode));
    T->lchild->rchild = (BiTNode*)malloc(sizeof(BiTNode));
    T->lchild->lchild->data = 4;
    T->lchild->rchild->data = 5;
    T->lchild->lchild->lchild = NULL;
    T->lchild->lchild->rchild = NULL;
    T->lchild->rchild->lchild = NULL;
    T->lchild->rchild->rchild = NULL;
    T->rchild->lchild = (BiTNode*)malloc(sizeof(BiTNode));
    T->rchild->rchild = (BiTNode*)malloc(sizeof(BiTNode));
    T->rchild->lchild->data = 6;
    T->rchild->rchild->data = 7;
    T->rchild->lchild->lchild = NULL;
    T->rchild->lchild->rchild = NULL;
    T->rchild->rchild->lchild = NULL;
    T->rchild->rchild->rchild = NULL;
    return T;
}

ThreadTree CreateThreadTree(){
    ThreadTree T = (ThreadTree)malloc(sizeof(ThreadNode));
    T->data = 1;
    T->ltag = 0;
    T->rtag = 0;
    T->lchild = (ThreadNode*)malloc(sizeof(ThreadNode));
    T->rchild = (ThreadNode*)malloc(sizeof(ThreadNode));
    T->lchild->data = 2;
    T->lchild->ltag = 0;
    T->lchild->rtag = 0;
    T->rchild->data = 3;
    T->rchild->ltag = 0;
    T->rchild->rtag = 0;
    T->lchild->lchild = (ThreadNode*)malloc(sizeof(ThreadNode));
    T->lchild->rchild = (ThreadNode*)malloc(sizeof(ThreadNode));
    T->lchild->lchild->data = 4;
    T->lchild->lchild->ltag = 0;
    T->lchild->lchild->rtag = 0;
    T->lchild->rchild->data = 5;
    T->lchild->rchild->ltag = 0;
    T->lchild->rchild->rtag = 0;
    T->lchild->lchild->lchild = NULL;
    T->lchild->lchild->rchild = NULL;
    T->lchild->rchild->lchild = NULL;
    T->lchild->rchild->rchild = NULL;
    T->rchild->lchild = (ThreadNode*)malloc(sizeof(ThreadNode));
    T->rchild->rchild = (ThreadNode*)malloc(sizeof(ThreadNode));
    T->rchild->lchild->data = 6;
    T->rchild->lchild->ltag = 0;
    T->rchild->lchild->rtag = 0;
    T->rchild->rchild->data = 7;
    T->rchild->rchild->ltag = 0;
    T->rchild->rchild->rtag = 0;
    T->rchild->lchild->lchild = NULL;
    T->rchild->lchild->rchild = NULL;
    T->rchild->rchild->lchild = NULL;
    T->rchild->rchild->rchild = NULL;
    return T;
}

int main(){
    BiTree T = CreateTree();
    printf("---------------PreOrder\n");
    PreOrder(T);
    printf("\n---------------PreOrder2\n");
    PreOrder2(T);
    printf("\n---------------InOrder\n");
    InOrder(T);
    printf("\n---------------InOrder2\n");
    InOrder2(T);
    printf("\n---------------PostOrder\n");
    PostOrder(T);
    printf("\n---------------PostOrder2\n"); 
    PostOrder2(T);
    printf("\n-----------------LevelReverse\n");
    LevelReverse(T);
    printf("\n-----------------InverseLevel\n");
    InverseLevel(T);
    printf("BiTree Height : %d, %d",TreeHeight(T),HeightRecursion(T));

    printf("\n");
    ThreadTree t = CreateThreadTree();
    CreateInThread(t);
    ThreadInOrder(t);
    int pre[6] = {1,2,4,5,3,6};
    int in[6] = {4,2,5,1,6,3};
    BiTree b = PreInCreate(pre, in, 0, 5, 0, 5);
    printf("\n-----------------pre-in-create\n");
    PreOrder(b);
    if(IsCompleteTree(b)){
        printf("\nb is a complete tree\n");
    }else{
        printf("\nb is not a complete tree\n");
    }
    printf("count parent nodes: %d\n",CountNodes(b));
    PreOrder(b);
    SwapTree(b);
    printf("\n-------------------swap-tree\n");
    PreOrder(b);
    printf("\nPreNode_k: %d\n",PreNode_k(b, 3));
    SearchXTree(b, 3);
    PreOrder(b);
    printf("\n");
    int a1[8] = {1,2,4,5,6,8,7,3};
    int a2[8] = {4,2,6,8,5,7,1,3};
    BiTree T1 = PreInCreate(a1, a2, 0, 7, 0, 7);
    findAncestors(T1, 8);
    printf("\n7 8 First Common Ancestor: %d\n",FirstCommonAncestor(T1, 7, 8)->data);
    BiWidth(T, 0);
    printf("T width: %d\n",MAX);
    int b1[7] = {1,2,4,5,3,6,7};
    int b2[7] = {0};
    PreToPost(b1, b2, 0, 6, 0, 6);
    for(int i = 0; i < 7; i++){
        printf("%d\t",b2[i]);
    }
    int wpl = 0;
    ComputeWPL(T, &wpl, 1);
    printf("\nWPL : %d\n",wpl);
    int bst[8] = {4,2,6,8,5,7,1,3};
    BiTree BST = CreateBST(bst, 8);
    InOrder(BST);
    if(JudgeBST(BST)){
        printf("\nIt's a binary search tree\n");
    }else{
        printf("\nIt's not a binary search tree\n");
    }
    BalanceTreeNodes(8);
    return 0;
}
