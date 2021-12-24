#include <stdio.h>
#include <stdlib.h>

#define ElemType int

//直接插入排序{将未排序的序列 插入 已排好序的序列}
void InsertSort(ElemType A[], int n){
    int i,j;
    for(i = 2; i <= n; i++){
        if(A[i] < A[i - 1]){
            A[0] = A[i];
            for(j = i - 1; A[j] > A[0]; --j){
                A[j+1] = A[j];
            }
            A[j+1] = A[0];
        }
    }
}

//折半插入排序{先用折半查找找到待插入的位置}
void BinInsertSort(ElemType A[], int n){
    int i,j,low,high,mid;
    for(i = 2; i <= n; i++){
        A[0] = A[i];
        low = 1,high = i - 1;
        while(low <= high){
            mid = (low + high)/2;
            if(A[mid] > A[0]){
                high = mid - 1;
            }else{
                low = mid + 1;
            }
        }
        for(j = i - 1; j >= high+1; j--){
            A[j+1] = A[j];
        }
        A[high+1] = A[0];
    }
}

//希尔排序{增量d}
void ShellSort(ElemType A[], int n){
    int d,i,j;
    for(d = n/2; d >= 1; d = d/2){
        for(i = d+1; i <= n; ++i){
            if(A[i] < A[i - d]){
                A[0] = A[i];
                for(j = i - d; j > 0 && A[j] > A[0]; j -= d){
                    A[j+d] = A[j];
                }
                A[j+d] = A[0];
            }
        }
    }
}

int main(){
    int A[] = {0,101,86,54,33,21,27,43,56,19,7};
    int B[] = {0,101,86,54,33,21,27,43,56,19,7};
    int C[] = {0,101,86,54,33,21,27,43,56,19,7};
    InsertSort(A, 10);
    for(int i = 1; i <= 10; i++){
        printf("%d\t",A[i]);
    }
    BinInsertSort(B, 10);
    printf("\n");
    for(int i = 1; i <= 10; i++){
        printf("%d\t",B[i]);
    }
    ShellSort(C, 10);
    printf("\n");
    for(int i = 1; i <= 10; i++){
        printf("%d\t",C[i]);
    }
    return 0;
}