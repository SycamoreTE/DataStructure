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

void printStack(SqStack *s){
    ElemType x;
    while (s->top != -1) {
        x = Pop(s);
        printf("%c\t", x);
    }
    printf("\n");
}

bool isValid(char A[]){
    int i = 0, j = 0, k = 0;
    while(A[i] != '\0'){
        switch (A[i]) {
            case 'I': {
                j++;
                break;
            }
            case 'O':{
                k++;
                if(k > j){
                    return false;
                }
                break;
            }
        }
        i++;
    }
    if(j != k){
        return false;
    }else{
        return true;
    }
}

int main(){
    char A[] = {};
    ElemType x;
    int i = 0;
    printf("please input 'I' or 'O': ");
    scanf("%s",&x);
    while(x != 'q'){
        A[i] = x;
        printf("please input 'I' or 'O': ");
        scanf("%s",&x);
    }
    if(isValid(A)){
        printf("Operation sequence is valid");
    }else{
        printf("Operation sequence is invalid");
    }
    return 0;
}
