#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool DeleteSame(SqList *L){
    if(L->length == 0){
        return false;
    }
    int i = 0, j = 1;
    for(; j < L->length; j++){
        if(L->data[i]!= L->data[j]){
            L->data[++i] = L->data[j];
        }
    }
    L->length = i + 1;
    return true;
}

int main(){
    SqList list = {0};
    list.length = 8;
    list.data[0] = 2; list.data[1] = 2; list.data[2] = 7; list.data[3] = 7;
    list.data[4] = 7; list.data[5] = 8; list.data[6] = 8; list.data[7] = 10;
    for(int i = 0; i<list.length;i++){
        printf("%d\t",list.data[i]);
    }
    printf("\n");
    DeleteSame(&list);
    for(int i = 0; i<list.length;i++){
        printf("%d\t",list.data[i]);
    }
    printf("\n list length : %d",list.length);
    return 0;
}