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
    (*T)->lchild->rchild->lchild = (BiTNode *)malloc(sizeof(BiTNode));
    (*T)->lchild->rchild->rchild = (BiTNode*)malloc(sizeof(BiTNode));
    (*T)->lchild->rchild->lchild->data = 8;
    (*T)->lchild->rchild->lchild->lchild = NULL;
    (*T)->lchild->rchild->lchild->rchild = NULL;
    (*T)->lchild->rchild->rchild->data = 9;
    (*T)->lchild->rchild->rchild->lchild = NULL;
    (*T)->lchild->rchild->rchild->rchild = (BiTNode*)malloc(sizeof(BiTNode));
    (*T)->lchild->rchild->rchild->rchild->data = 10;
    (*T)->lchild->rchild->rchild->rchild->lchild = NULL;
    (*T)->lchild->rchild->rchild->rchild->rchild = NULL;
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

void visit(BiTNode *node) {
    printf("%d-->\t", node->data);
}

void InverseLevel(BiTree Tree){
    SqQueue Q;
    SqStack S;
    InitQueue(&Q);
    InitStack(&S);
    BiTNode *p = Tree;
    EnQueue(&Q, p);
    while(!isEmpty(Q)){
        p = DeQueue(&Q);
        Push(&S, p);
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
    }
    while(!StackEmpty(&S)){
        Pop(&S, &p);
        visit(p);
    }
}

//非递归求树的高
int BtHeight(BiTree Tree){
    if(!Tree){
        return -1;
    }
    SqQueue Q;
    InitQueue(&Q);
    Q.front = Q.rear = -1;
    int level = 0, last = 0;
    BiTNode *p = Tree;
    EnQueue(&Q, p);
    while(!isEmpty(Q)){
        p = DeQueue(&Q);
        if(p->lchild){
            EnQueue(&Q, p->lchild);
        }
        if(p->rchild){
            EnQueue(&Q, p->rchild);
        }
        if(Q.front == last){
            level++;
            last = Q.rear;
        }
    }
    return level;
}

//递归求树高
int BtHeightRecursion(BiTree Tree){
    if(!Tree){
        return 0;
    }
    int left = BtHeightRecursion(Tree->lchild);
    int right = BtHeightRecursion(Tree->rchild);
    if(left > right){
        return left + 1;
    }else{
        return right + 1;
    }
}

//判断一棵树是否为完全二叉树
bool IsComplete(BiTree Tree){
    if(!Tree){
        return true;
    }
    SqQueue Q;
    InitQueue(&Q);
    BiTNode *p = Tree;
    EnQueue(&Q, p);
    while(!isEmpty(Q)){
        p = DeQueue(&Q);
        visit(p);
        if(p){
            EnQueue(&Q, p->lchild);
            EnQueue(&Q, p->rchild);
        }else{
            while(!isEmpty(Q)){
                p = DeQueue(&Q);
                if(p){
                    printf("It's not a complete tree");
                    return false;
                }
            }
        }
    }
    printf("It's a complete tree");
    return true;
}

//删除树中以x为根的子树
void DeleteXTree(BiTree Tree){
    if(Tree){
        DeleteXTree(Tree->lchild);
        DeleteXTree(Tree->rchild);
        free(Tree);
    }
}

void Search(BiTree Tree, ElemType x){
    if(Tree->data == x){
        DeleteXTree(Tree);
    }
    BiTNode *p = Tree;
    SqQueue Q; InitQueue(&Q);
    EnQueue(&Q, p);
    while(!isEmpty(Q)){
        p = DeQueue(&Q);
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

//查找值为x的结点，并输出其所有祖先
bool Ancesters(BiTree Tree, SqQueue *Q,ElemType x){
    if(!Tree){
        return false;
    }
    if(Tree->data == x){
        return true;
    }
    if(Ancesters(Tree->lchild,Q, x)||Ancesters(Tree->rchild,Q, x)){
        EnQueue(Q, Tree);
        return true;
    }
    return false;
}

//找到最近的公共祖先
ElemType FindFirstCommonAncestor(BiTree Tree,ElemType x, ElemType y){
    SqQueue Q1, Q2;
    BiTNode *p, *q;
    InitQueue(&Q1);
    InitQueue(&Q2);
    Ancesters(Tree, &Q1, x);
    Ancesters(Tree, &Q2, y);
    while(!isEmpty(Q1)){
        p = DeQueue(&Q1);
        while(!isEmpty(Q2)){
            q = DeQueue(&Q2);
            if(p == q){
                return p->data;
            }
        }
    }
    return -1;
}

void findAncestor(ElemType x){
    BiTree tree;
    SqQueue Q;
    BiTNode *p = (BiTNode*)malloc(sizeof(BiTNode));
    InitQueue(&Q);
    initTree(&tree);
    Ancesters(tree, &Q, x);
    while(!isEmpty(Q)){
        p = DeQueue(&Q);
        visit(p);
    }
}
//求非空二叉树的宽度
int BtWidth(BiTree T){
    typedef struct{
        BiTree data[MaxSize];
        int level[MaxSize];
        int front,rear;
    } Qu;
    BiTNode *p = T;
    Qu Q; 
    Q.front = Q.rear = -1;
    int level = 0;
    Q.rear++;
    Q.data[Q.rear] = p;
    Q.level[Q.rear] = level+1;
    while(Q.front < Q.rear){
        
        Q.front++;
        p = Q.data[Q.front];
        level = Q.level[Q.front];
        
        if(p->lchild){
            Q.rear++;
            Q.data[Q.rear] = p->lchild;
            Q.level[Q.rear] = level+1;
        }
        
        if(p->rchild){
            Q.rear++;
            Q.data[Q.rear] = p->rchild;
            Q.level[Q.rear] = level+1;
        }
    }
    int max = 0, i = 0,n;
    level = 1;
    while(i <= Q.rear){
        n = 0;
        while(i<=Q.rear && Q.level[i] == level){
            n++;
            i++;
        }
        level = Q.level[i];
        if(n > max){
            max = n;
        }
    }
    return max;
}

void InOrder(BiTree Tree){
    if(Tree){
        InOrder(Tree->lchild);
        visit(Tree);
        InOrder(Tree->rchild);
    }
}

int main(){
    BiTree tree;
    initTree(&tree);
    printf("FindCommonAncestor--------------------\n");
    printf("First Common Ancestor : %d",FindFirstCommonAncestor(tree, 8, 10));
    printf("\nInverseLevel:---------------\n");
    InverseLevel(tree);
    printf("\n----------------------------\n");
    printf("BiTree's Height : %d",BtHeight(tree));
    printf("\n----------------------------\n");
    printf("BiTree Recursion Height : %d",BtHeightRecursion(tree));
    printf("\nFindAncestor-----------------\n");
    findAncestor(10);
    // Search(tree, 3);
    // printf("\n-----------------------Delete_3\n");
    InOrder(tree);
    printf("\nBtWidth: %d",BtWidth(tree));
    return 0;
}