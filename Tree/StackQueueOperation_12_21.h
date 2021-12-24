#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxSize 50

typedef struct BiTNode{
    ElemType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
}BiTNode,*BiTree;

typedef struct ThreadNode{
    ElemType data;
    struct ThreadNode *lchild;
    struct ThreadNode *rchild;
    int ltag, rtag;
}ThreadNode, *ThreadTree;

typedef struct SqStack{
    BiTNode* data[MaxSize];
    int top;
}SqStack;

typedef struct SqQueue{
    BiTNode* data[MaxSize];
    int front,rear;
}SqQueue;

void InitStack(SqStack *S){
    S->top = -1;
}

bool StackEmpty(SqStack S){
    if(S.top == -1){
        return true;
    }else{
        return false;
    }
}

bool Push(SqStack *S, BiTNode *x){
    if(S->top == MaxSize - 1){
        return false;
    }else{
        S->data[++S->top] = x;
        return true;
    }
}

bool Pop(SqStack *S, BiTNode **x){
    if(S->top == -1){
        return false;
    }else{
        *x = S->data[S->top--];
        return true;
    }
}

bool GetTop(SqStack *S, BiTNode **x){
    if(S->top == -1){
        return false;
    }else{
        *x = S->data[S->top];
        return true;
    }
}

void InitQueue(SqQueue *Q){
    Q->front = Q->rear = -1;
}

bool QueueEmpty(SqQueue Q){
    if(Q.front == Q.rear){
        return true;
    }else{
        return false;
    }
}

bool EnQueue(SqQueue *Q, BiTNode *x){
    if((Q->rear+1)%MaxSize == Q->front){
        return false;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue *Q, BiTNode **x){
    if(Q->front == Q->rear){
        return false;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1)%MaxSize;
    return true;
}