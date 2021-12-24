#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50
#define ElemType char
typedef struct{
    ElemType data[MaxSize];
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
bool Push(SqStack *s, ElemType x){
    if(s->top == MaxSize-1){
        return false;
    }else{
        s->data[++s->top] = x;
        return true;
    }
}

//出栈
ElemType Pop(SqStack *s){
    if(s->top == -1){
        return -1;
    }else{
        return s->data[s->top--];
    }
}

//读栈顶元素
bool GetTop(SqStack *s, ElemType *x){
    if(s->top == -1){
        return false;
    }else{
        *x = s->data[s->top];
        return true;
    }
}

void printStack(SqStack *s){
    ElemType x;
    while (s->top != -1) {
        x = Pop(s);
        printf("%c\t", x);
    }
    printf("\n");
}

int main(){
    SqStack s;
    InitStack(&s);
    ElemType x;
    printf("please input stack element : ");
    scanf("%s",&x);
    while(x != 'z'){
        Push(&s, x);
        printf("please input stack element : ");
        scanf("%s",&x);
    }
    printStack(&s);
    return 0;
}