#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

int SearchMin(SqList L){
    int i;
    int B[L.length - 1];
    for(int i = 0; i < L.length; i++){
        B[i] = 0;
    }
    for(int i = 0; i < L.length; i++){
        B[L.data[i] - 1] = 1;
    }
    for(i = 0; i < L.length; i++){
        if(B[i]==0){
            break;
        }
    }
    return i+1;
}

int main(){
    SqList min1 = {0};
    min1.length = 4;
    min1.data[0] = -5; min1.data[1] = 3; min1.data[2] = 2; min1.data[3] = 3;
    for(int i = 0; i < min1.length; i++){
        printf("%d\t",min1.data[i]);
    }
    printf("\nSearchMin min1: %d\n",SearchMin(min1));
    SqList min2 = {0};
    min2.length = 3;
    for(int i = 0; i<min2.length; i++){
        min2.data[i] = i+8;
        printf("%d\t",min2.data[i]);
    }
    printf("\nSearchMin min2: %d\n",SearchMin(min2));
    return 0;
}