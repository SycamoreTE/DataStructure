#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50
#define ElemType char
typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

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

void TrainArrange(char* train){
    char *p = train, *q = train, e;
    SqStack S;
    InitStack(&S);
    while(*p){
        if(*p == 'H'){
            Push(&S, 'H');
        }else{
            *(q++) = *p;
        }
        p++;
    }
    while(!StackEmpty(&S)){
        e = Pop(&S);
        *(q++) = e;
    }
    printf("--------");
    // while(*p != '\0'){
    //     printf("%c\t",*p);
    //     p++;
    // }
}

int main(){
    char A[MaxSize];
    char e;
    int i = 0;
    printf("please input train sequence : ");
    scanf("%s",&e);
    while(e != 'q'){
        A[i] = e;
        i++;
        printf("please input train sequence : ");
        scanf("%s",&e);
    }
    TrainArrange(A);
    while(A[i] != '\0'){
        printf("%c\t",A[i]);
        i++;
    }
    return 0;
}