#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool Delete_s_t(SqList *L, int s, int t){
    if(L->length == 0 || s>t){
        return false;
    }
    int i,j;
    for(i = 0; L->data[i] < s; i++);
    for(j = 0; L->data[j] <= t; j++);
    while(j < L->length){
        L->data[i] = L->data[j];
        i++;
        j++;
    }
    L->length = i + 1;
    return true;
}

int main(){
    SqList list = {0};
    list.length = 7;
    for(int i = 0; i < list.length; i++){
        list.data[i] = i*5+2;
        printf("%d\t",list.data[i]);
    }
    printf("\n");
    Delete_s_t(&list, 9, 21);
    for(int i = 0; i < list.length; i++){
        printf("%d\t",list.data[i]);
    }
    printf("\nlist length: %d",list.length);
    return 0;
}