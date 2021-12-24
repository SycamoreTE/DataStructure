#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool Delete_x(SqList *L, int x){
    if(L->length == 0){
        return false;
    }
    int k = 0;
    for(int i = 0; i < L->length; i++){
        if(L->data[i] != x){
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
    return true;
}

int main(){
    SqList list = {0};
    list.length = 6;
    for(int i = 0; i < list.length; i++){
        list.data[i] = i * 3 + 3;
        printf("%d\t",list.data[i]);
    }
    printf("\n");
    Delete_x(&list, 15);
    for(int i = 0; i < list.length; i++){
        printf("%d\t",list.data[i]);
    }
}