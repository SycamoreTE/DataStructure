#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MaxSize 50
#define ElemType double
typedef struct{
    ElemType data;
    int top;
    int number;
}SqStack[MaxSize];

double func(int n, double x){
    SqStack S;
    int top = -1,i;
    float f1 = 1, f2 = 2*x;
    for(int i = n; i >= 2; i--){
        top++;
        S[top].number = i;
    }
    while(top >= 0){
        S[top].data = 2*x*f2 - 2*(S[top].number - 1)*f1;
        f1 = f2;
        f2 = S[top].data;
        top--;
    }
    if(n == 0){
        return f1;
    }
    return f2;
}

int main(){
    int n;float x;
    printf("input n :");
    scanf("%d",&n);
    printf("input x :");
    scanf("%f",&x);
    printf("%f",func(n, x));
}