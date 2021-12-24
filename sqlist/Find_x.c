#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool Find_x(SqList *L, int x){
    if(L->length == 0){
        return false;
    }
    int pos = MAX_SIZE, temp = 0,mid = 0;
    int low = 0, high = L->length - 1;
    while(low < high){
        mid = (low + high)/2;
        if(L->data[mid]==x){
            pos = mid;
            break;
        }else if(L->data[mid] < x){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    if(pos < 0 || pos > L->length - 1){
        return false;
    }
    temp = L->data[pos];
    L->data[pos] = L->data[pos + 1];
    L->data[pos + 1] = temp;
    return true;
}

int main(){
    SqList list = {0};
    list.length = 15;
    for(int i = 0; i < list.length; i++){
        list.data[i] = i*2 + 1;
        printf("%d\t",list.data[i]);
    }
    printf("\n");
    Find_x(&list, 10);
    for(int i = 0; i < list.length; i++){
        printf("%d\t",list.data[i]);
    }
    return 0;
}