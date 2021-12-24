#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50
#define ElemType int

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

//--------------------------------------LinkQueue
void InitQueue1(LinkQueue *Q){
    Q->front = Q->rear = (LinkNode*)malloc(sizeof(LinkNode));  //创建头结点
    Q->front->next = NULL;
}

bool IsEmpty1(LinkQueue *Q){
    if(Q->front == Q->rear){
        return true;
    }else{
        return false;
    }
}

void EnQueue1(LinkQueue *Q, ElemType x){
    LinkNode *s = (LinkNode *)malloc(sizeof(LinkNode));
    s->data = x; s->next = NULL;
    Q->rear->next = s;
    Q->rear = s;
}

bool DeQueue1(LinkQueue *Q, ElemType *x){
    if(Q->front == Q->rear){
        return false;
    }
    LinkNode *p = Q->front->next;
    *x = p->data;
    Q->front->next = p->next;
    if(Q->rear == p){
        Q->rear = Q->front;
    }
    free(p);
    return true;
}
//----------------------------------------LinkQueue

int main(){
    ElemType x;
    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, 6);
    EnQueue(&Q, 7);
    DeQueue(&Q, &x);
    printf("DeQueue : %d",x);

    LinkQueue Q1;
    InitQueue1(&Q1);
    EnQueue1(&Q1, 8);
    EnQueue1(&Q1, 9);
    DeQueue1(&Q1, &x);
    printf("DeQueue : %d",x);
    return 0;
}