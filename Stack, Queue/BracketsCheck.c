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

void printStack(SqStack *s){
    ElemType x;
    while (s->top != -1) {
        x = Pop(s);
        printf("%c\t", x);
    }
    printf("\n");
}


bool BracketsCheck(char A[]){
    SqStack S;
    InitStack(&S);
    int i = 0;
    ElemType e;
    while(A[i] != '\0'){
        switch (A[i]) {
            case '(':{
                Push(&S,'(');
                break;
            }
            case '{':{
                Push(&S,'{');
                break;
            }
            case '[':{
                Push(&S,'[');
                break;
            }
            case ')':{
                e = Pop(&S);
                if(e != '('){
                    return false;
                }
                break;
            }
            case '}':{
                e = Pop(&S);
                if(e != '{'){
                    return false;
                }
                break;
            }
            case ']':{
                e = Pop(&S);
                if(e != '['){
                    return false;
                }
                break;
            }
            default: break;
        }
        i++;
    }
    if(!StackEmpty(&S)){
        return false;
    }else{
        return true;
    }
}

int main(){
    int i = 0;
    char A[MaxSize];
    ElemType e;
    printf("please input statement: ");
    scanf("%s",&e);
    while(e != 'q'){
        A[i] = e;
        i++;
        printf("please input statement: ");
        scanf("%s",&e);
    }
    if(BracketsCheck(A)){
        printf("brackets statement is valid");
    }else{
        printf("brackets statement is invalid");
    }
    return 0;
}