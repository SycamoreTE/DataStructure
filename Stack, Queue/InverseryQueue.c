#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxSize 50

typedef struct {
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

typedef struct LinkNode{
    ElemType data;
    struct LinkNode *next;
}LinkNode, *QueuePoint;

typedef struct{
    QueuePoint front;
    QueuePoint rear;
}LinkQueue;

//--------------------------------------LinkQueue
void InitQueue(SqQueue *Q){
    Q->front = Q->rear = 0;
}

bool isEmpty(SqQueue *Q){
    if(Q->rear == Q->front){
        return true;
    }else{
        return false;
    }
}

bool EnQueue(SqQueue *Q, ElemType x){
    if((Q->rear + 1)%MaxSize == Q->front){
        return false;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue *Q, ElemType *x){
    if(Q->rear == Q->front){
        return false;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1)%MaxSize;
    return true;
}

void printQueue(SqQueue *Q){
    ElemType x;
    while(!isEmpty(Q)){
        DeQueue(Q, &x);
        printf("%d\t",x);
    }
    printf("\n");
}
//----------------------------------------LinkQueue

//----------------------------------------SqStack
typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

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

bool Push(SqStack *s, ElemType x){
    if(s->top == MaxSize-1){
        return false;
    }else{
        s->data[++s->top] = x;
        return true;
    }
}

bool Pop(SqStack *s, ElemType *x){
    if(s->top == -1){
        return false;
    }else{
        *x = s->data[s->top--];
        return true;
    }
}
//----------------------------------------SqStack

void InverseryQueue(SqQueue *Q, SqStack *S){
    int x;
    while(!isEmpty(Q)){
        DeQueue(Q, &x);
        Push(S, x);
    }
    while(!StackEmpty(S)){
        Pop(S, &x);
        EnQueue(Q, x);
    }
}

int main(){
    ElemType x;
    SqQueue Q; SqStack S;
    InitQueue(&Q);
    InitStack(&S);
    EnQueue(&Q, 6);
    EnQueue(&Q, 7);
    EnQueue(&Q, 8);
    InverseryQueue(&Q, &S);
    printQueue(&Q);
    return 0;
}
