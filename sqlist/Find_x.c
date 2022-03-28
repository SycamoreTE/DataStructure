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
    int low = 0, high = L->length - 1, mid;
    while(low < high){
        mid = (low + high)/2;
        if(L->data[mid] == x){
            int temp = L->data[mid];
            L->data[mid] = L->data[mid+1];
            L->data[mid+1] = temp;
            return true;
        }else if(L->data[mid] < x){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    if(low >= high){
        int i;
        for(i = L->length - 1; i > high; i--){
            L->data[i+1] = L->data[i];
        }
        L->data[i+1] = x;
        L->length++;
    }
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