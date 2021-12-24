#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

int FindMid(SqList A, SqList B){
    if(A.length != B.length){
        return -1;
    }
    int i = 0, j = 0, count = 0;
    while(count < A.length){
        if(A.data[i] <= B.data[j]){
            i++;
            count++;
            if(count == A.length){
                return A.data[i-1];
            }
        }else{
            j++;
            count++;
            if(count == A.length){
                return B.data[j-1];
            }
        }
    }
    return -1;
}

int main(){
    SqList A = {0},B = {0};
    A.length = B.length = 7;
    for(int i = 0; i < A.length; i++){
        A.data[i] = i*2+7;
        printf("%d\t",A.data[i]);
    }
    printf("\n");
    for(int i = 0; i < B.length; i++){
        B.data[i] = i*3+3;
        printf("%d\t",B.data[i]);
    }
    printf("\n%d",FindMid(A, B));
    return 0;
}