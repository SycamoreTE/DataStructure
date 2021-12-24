#include <stdio.h>
#include <stdlib.h>

#define ElemType int

void Merge(ElemType A[],int low,int mid,int high){
    ElemType B[high];
    int i,j,k;
    for(i = low; i <= high; i++){
        B[i] = A[i];
    }
    for(i = low,j = mid+1,k = low; i<=low&&j<=high; ){
        if(B[i]<=B[j]){
            A[k++] = B[i++];
        }else{
            A[k++] = B[j++];
        }
    }
    while(i<=mid){
        A[k++] = B[i++];
    }
    while(j<=high){
        A[k++] = B[j++];
    }
}

void MergeSort(ElemType A[],int low,int high){
    if(low < high){
        int mid = (low + high)/2;
        MergeSort(A, low, mid);
        MergeSort(A, mid+1, high);
        Merge(A, low, mid, high);
    }
}

int main(){
    int a[] = {49,38,65,97,76,13,27};
    MergeSort(a, 0, 6);
    for(int i = 0; i < 7; i++){
        printf("%d\t",a[i]);
    }
}