#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxSize 50

//定义树的链式存储结构
typedef struct BiTNode {
    struct BiTNode *lchild;
    struct BiTNode *rchild;
    ElemType data;

} BiTNode, *BiTree;

typedef struct {
    BiTNode* data[MaxSize];
    int front,rear;
}SqQueue;

typedef struct{
    BiTNode* data[MaxSize];
    int top;
}SqStack;

//初始化
void InitStack(SqStack* s){
    s->top = -1;
}

bool StackEmpty(SqStack* s){
    if(s->top == -1){
        return true;
    }else{
        return false;
    }
}

//进栈
bool Push(SqStack *s, BiTNode *x){
    if(s->top == MaxSize-1){
        return false;
    }else{
        s->data[++s->top] = x;
        return true;
    }
}

//出栈
bool Pop(SqStack *s, BiTNode **x){
    if(s->top == -1){
        return false;
    }else{
        *x = s->data[s->top--];
        return true;
    }
}

//读栈顶元素
bool GetTop(SqStack *s, BiTNode **x){
    if(s->top == -1){
        return false;
    }else{
        *x = s->data[s->top];
        return true;
    }
}

void InitQueue(SqQueue *Q){
    Q->front = Q->rear = 0;
}

bool isEmpty(SqQueue Q){
    if(Q.rear == Q.front){
        return true;
    }else{
        return false;
    }
}

bool EnQueue(SqQueue *Q, BiTNode* x){
    if((Q->rear + 1)%MaxSize == Q->front){
        return false;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1)%MaxSize;
    return true;
}

BiTNode* DeQueue(SqQueue *Q){
    if(Q->rear == Q->front){
        return false;
    }
    BiTNode *x = Q->data[Q->front];
    Q->front = (Q->front + 1)%MaxSize;
    return x;
}

//用于初始化一棵树的算法
void initTree(BiTree *T) {
    *T = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->data = 1;
    (*T)->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->data = 2;
    (*T)->lchild->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->rchild->data = 5;
    (*T)->lchild->rchild->lchild = NULL;
    (*T)->lchild->rchild->rchild = NULL;
    (*T)->rchild->data = 3;
    (*T)->rchild->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild->lchild->data = 6;
    (*T)->rchild->lchild->lchild = NULL;
    (*T)->rchild->lchild->rchild = NULL;
    (*T)->rchild->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild->rchild->data = 7;
    (*T)->rchild->rchild->lchild = NULL;
    (*T)->rchild->rchild->rchild = NULL;
    (*T)->lchild->lchild->data = 4;
    (*T)->lchild->lchild->lchild = NULL;
    (*T)->lchild->lchild->rchild = NULL;
}

//访问函数 用于输出结点的数据
void visit(BiTNode *node) {
    printf("%d-->\t", node->data);
}

//先序遍历递归版本
void preOrderTraverse(BiTree Tree) {
    if (Tree) {
        visit(Tree);
        preOrderTraverse(Tree->lchild);
        preOrderTraverse(Tree->rchild);
    }
}

//先序遍历非递归版本
void preOrderTraverseNonrecursion(BiTree Tree) {
    if(Tree == NULL){
        return;
    }
    SqStack S;
    InitStack(&S);
    BiTNode *p = Tree;
    while(p || !StackEmpty(&S)){
        if(p){
            visit(p);
            Push(&S,p);
            p = p->lchild;
        }else{
            Pop(&S, &p);
            p = p->rchild;
        }
    }
}

//中序遍历递归版本
void inOrderTraverse(BiTree Tree) {
    if (Tree) {
        inOrderTraverse(Tree->lchild);
        visit(Tree);
        inOrderTraverse(Tree->rchild);
    }
}

//中序遍历非递归版本
void inOrderTraverseNonrecursion(BiTree Tree) {
    if(Tree == NULL){
        return;
    }
    SqStack S;
    InitStack(&S);
    BiTNode *p = Tree;
    while(p || !StackEmpty(&S)){
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

//后序遍历递归算法
void postOrderTraverse(BiTree Tree) {
    if (Tree) {
        postOrderTraverse(Tree->lchild);
        postOrderTraverse(Tree->rchild);
        visit(Tree);
    }
}

//后序遍历的递归算法
void postOrderTraverseNonrecursion(BiTree Tree) {
    if(Tree == NULL){
        return;
    }
    SqStack S;
    InitStack(&S);
    BiTNode *p = Tree, *r = NULL;
    while(p || !StackEmpty(&S)){
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
                r = p;  //标志被访问的右子树
                p = NULL;  //结点访问完后，重置指针
            }
        }
    }
}

//层序遍历算法
void LevelOrderTraverse(BiTree Tree) {
    SqQueue Q;
    InitQueue(&Q);
    BiTNode *p = Tree, *q;
    EnQueue(&Q, p);
    while(!isEmpty(Q)){
        q = DeQueue(&Q);
        visit(q);
        if(q->lchild){
            EnQueue(&Q, q->lchild);
        }
        if(q->rchild){
            EnQueue(&Q, q->rchild);
        }
    }
}

int main() {
    BiTree tree;
    initTree(&tree);

    preOrderTraverse(tree);
    printf("\n-----PreOrder/NonRecursion------\n");
    preOrderTraverseNonrecursion(tree);

    printf("\n");
    printf("\n-------------------------------------------\n");
    printf("\n");

    inOrderTraverse(tree);
    printf("\n-----InOrder/NonRecursion------\n");
    inOrderTraverseNonrecursion(tree);


    printf("\n");
    printf("\n-------------------------------------------\n");
    printf("\n");

    postOrderTraverse(tree);
    printf("\n-----PostOrder/NonRecursion------\n");
    postOrderTraverseNonrecursion(tree);

    printf("\n");
    printf("\n-------------------------------------------\n");
    printf("\n");

    printf("LevelOrder\n");
    LevelOrderTraverse(tree);

    return 0;
}