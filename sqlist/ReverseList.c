#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool ReverseList(SqList *L){
    if(L->length == 0){
        return false;
    }
    int temp = 0;
    for(int i = 0; i < L->length/2; i++){
        temp = L->data[i];
        L->data[i] = L->data[L->length - i -1];
        L->data[L->length - i - 1] = temp;
    }
    return true;
}

int main(){
    SqList list = {0};
    list.length = 7;
    for(int i = 0; i < list.length; i++){
        list.data[i] = i;
        printf("%d\t",list.data[i]);
    }
    printf("\n");
    ReverseList(&list);
    for(int i = 0; i < list.length; i++){
        printf("%d\t",list.data[i]);
    }
    return 0;
}