#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxSize 50

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

//栈模拟队列：入队，若S1不为空，入栈S1； 若S1已满，不满足条件；

bool EnQueue(SqStack *S1, SqStack *S2, ElemType e){
    if(Push(S1, e)){
        return true;
    }else if(!StackEmpty(S2)){
        return false;
    }else{
        while(!StackEmpty(S1)){
            Pop(S1, &e);
            Push(S2, e);
        }
    }
    return true;
}

bool DeQueue(SqStack *S1, SqStack *S2, ElemType *x){
    ElemType e;
    if(!StackEmpty(S2)){
        Pop(S2, x);
    }else if(StackEmpty(S1)){
        return false;
    }else{
        while(!StackEmpty(S1)){
            Pop(S1, &e);
            Push(S2, e);
        }
        Pop(S2,x);
    }
    return true;
}

bool QueueEmpty(SqStack *S1, SqStack *S2){
    if(StackEmpty(S1)&&StackEmpty(S2)){
        return true;
    }else{
        return false;
    }
}

int main(){
    ElemType x;
    SqStack S1, S2;
    InitStack(&S1);
    InitStack(&S2);
    EnQueue(&S1, &S2, 2);
    EnQueue(&S1, &S2, 3);
    DeQueue(&S1, &S2, &x);
    printf("DeQueue : %d\n", x);
    DeQueue(&S1, &S2, &x);
    printf("DeQueue : %d", x);
    return 0;
}