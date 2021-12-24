#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool Reverse(SqList *L, int begin, int end){
    if(L->length == 0 || begin > end){
        return false;
    }
    int temp = 0;
    int mid = (begin + end)/2;
    for(int i = 0; i < (mid - begin); i++){
        temp = L->data[begin + i];
        L->data[begin + i] = L->data[end - i];
        L->data[end - i] = temp;
    }
    return true;
}

int main(){
    SqList A = {0};
    A.length = 15;
    for(int i = 0; i < A.length; i++){
        A.data[i] = i*2 + 1;
        printf("%d\t",A.data[i]);
    }
    printf("\n");
    Reverse(&A, 0, 14);
    Reverse(&A, 0, 4);
    Reverse(&A, 5, 14);
    for(int i = 0; i < A.length; i++){
        printf("%d\t",A.data[i]);
    }
    return 0;
}