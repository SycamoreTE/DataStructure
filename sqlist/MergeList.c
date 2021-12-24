#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool MergeList(SqList A, SqList B, SqList *L){
    if(A.length == 0 && B.length == 0){
        return false;
    }
    int i = 0, j = 0, k = 0;
    while( i<A.length && j<B.length){
        if(A.data[i] <= B.data[j]){
            L->data[k++] = A.data[i++];
        }else{
            L->data[k++] = B.data[j++];
        }
    }
    while (i<A.length) {
        L->data[k++] = A.data[i++];
    }
    while(j<B.length){
        L->data[k++] = B.data[j++];
    }
    L->length = k;
    return true;
}

int main(){
    SqList l1 = {0}, l2 = {0}, l3 = {0};
    l1.length = 4;
    l2.length = 6;
    for(int i = 0; i<l1.length;i++){
        l1.data[i] = i*2 +7;
        printf("%d\t",l1.data[i]);
    }
    printf("\n");
    for(int i = 0; i<l2.length;i++){
        l2.data[i] = i*3+2;
        printf("%d\t",l2.data[i]);
    }
    printf("\n");
    MergeList(l1, l2, &l3);
    for(int i = 0; i < l3.length; i++){
        printf("%d\t",l3.data[i]);
    }
    printf("\n mergelist length: %d",l3.length);
    return 0;
}