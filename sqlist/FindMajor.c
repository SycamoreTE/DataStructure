#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} Sqlist1;

int FindMajor(Sqlist1 L, int n){
    if(L.length == 0){
        return -1;
    }
    int major = 0;
    int B[n];
    for(int i = 0; i < n; i++){
        B[i] = 0;
    }
    for(int i = 0; i < n; i++){
        B[L.data[i]]++;
    }
    for(int i = 0; i < n; i++){
        if(B[i] > n/2){
            major = i;
            return major;
        }
    }
    return -1;
}

int main(){
    Sqlist1 list1 = {0};
    list1.length = 8;
    list1.data[0] = 0; list1.data[1] = 3; list1.data[2] = 5; list1.data[3] = 5;
    list1.data[4] = 5; list1.data[5] = 7; list1.data[6] = 5; list1.data[7] = 5;
    for(int i = 0; i < list1.length; i++){
        printf("%d\t",list1.data[i]);
    }
    printf("\nFindMajor : %d",FindMajor(list1,list1.length));
    return 0;
}