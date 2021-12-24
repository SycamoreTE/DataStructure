#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
#define MIN_INIT 50
typedef struct {
  ElemType data[MAX_SIZE];
  int length;
} SqList;

bool isMin(int a, int b, int c){
    if(a < b && a < c){
        return true;
    }
    return false;
}

int SearchMinDistance(SqList A, SqList B, SqList C){
    int min = MIN_INIT;
    int temp_min;
    int i = 0, j = 0, k = 0;
    int a,b,c;
    while(i < A.length && j < B.length && k < C.length){
        temp_min = abs(A.data[i] - B.data[j]) + abs(A.data[i] - C.data[k]) +abs(B.data[j] - C.data[k]);
        if(temp_min < min){
            min = temp_min;
            a = A.data[i];
            b = B.data[j];
            c = C.data[k];
        }
        if(isMin(A.data[i], B.data[j], C.data[k])){
            i++;
        }else if(isMin(B.data[j], A.data[i], C.data[k])){
            j++;
        }else{
            k++;
        } 
    }
    printf("(%d,%d,%d): %d", a,b,c,min);
    return min;
}

int main(){
    SqList s1 = {0},s2 = {0}, s3 = {0};
    s1.length = 3;
    s1.data[0] = -1; s1.data[1]= 0; s1.data[2] = 9;

    s2.length = 4;
    s2.data[0] = -25; s2.data[1] = -10; s2.data[2] = 10; s2.data[3] = 11;

    s3.length = 5;
    s3.data[0] = 2; s3.data[1] = 9; s3.data[2] = 17; s3.data[3] = 30; s3.data[4] = 41;
    printf("SearchMin : %d",SearchMinDistance(s1, s2, s3));
    return 0;
}