#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//直接插入排序，l1...lk为排好序的序列，将后续的lk+1...ln插入排好序的序列；
void InsertSort(ElemType A[], int n){
    int i,j;
    for(i = 2; i <= n; i++){
        if(A[i]<A[i-1]){
            A[0] = A[i];
            for(j = i-1; A[j] > A[0];--j){
                A[j+1] = A[j];
            }
            A[j+1] = A[0];
        }
    }
}

void BinInsertSort(ElemType A[], int n){
    int low,high,mid,i,j;
    for(int i = 2; i<=n; i++){
        if(A[i]<A[i-1]){
            A[0] = A[i];
            low = 1,high = i-1;
            while(low < high){
                mid = (low + high)/2;
                if(A[mid] < A[0]){
                    low = mid + 1;
                }else{
                    high = mid - 1;
                }
            }
            for(j = i-1; j>=high+1;j--){
                A[j+1] = A[j];
            }
            A[high+1] = A[0];
        }
    }
}

void BubbleSort(ElemType A[], int n){
    for(int i = 0; i < n; i++){
        for(int j = n-1; j>i; j--){
            if(A[j-1]>A[j]){
                Swap(&A[j-1], &A[j]);
            }
        }
    }
}

void BubbleSorts(ElemType A[], int n){
    int low=0, high = n-1;
    int flag = true;
    while(low < high && flag){
        flag = false;
        for(int i = low; i < high;i++){
            if(A[i]>A[i+1]){
                Swap(&A[i], &A[i+1]);
                flag = true;
            }
        }
        high--;
        for(int i = high; i>low;i--){
            if(A[i]<A[i-1]){
                Swap(&A[i], &A[i-1]);
                flag = true;
            }
        }
        low++;
    }
}

//所有奇数排在偶数前
void BubbleApply(ElemType A[], int n){
    for(int i = 0; i < n-1; i++){
        for(int j=n-1;j>i;j--){
            if(A[j]%2==1){
                Swap(&A[j-1], &A[j]);
            }
        }
    }
}

void BubbleSort1(ElemType A[], int n){
    int low = 0,high = n-1;
    while(low < high){
        while(low < high && A[low]%2==1){
            low++;
        }
        while(low < high && A[high]%2==0){
            high--;
        }
        if(low < high){
            Swap(&A[low], &A[high]);
        }
        low++;high--;
    }
}

void SelectSort(ElemType A[], int n){
    for(int i = 0; i < n-1; i++){
        int min = i;
        for(int j = i+1; j < n; j++){
            if(A[j]<A[min]){
                Swap(&A[j], &A[min]);
            }
        }
    }
}

void ShellSort(ElemType A[],int n){
    int i,j,d;
    for(d = n/2; d>=1; d=d/2){
        for(i = d+1; i <= n; i++){
            if(A[i] < A[i-d]){
                A[0] = A[i];
                for(j = i-d; A[j]>A[0];j-=d){
                    A[j+d] = A[j];
                }
                A[j+d] = A[0];
            }
        }
    }
}

int Partition(ElemType A[],int low,int high){
    int pivot = A[low];
    while(low < high){
        while(low < high && A[high]>pivot){
            high--;
        }
        A[low] = A[high];
        while(low < high && A[low]<pivot){
            low++;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

//快速排序
void QuickSort(ElemType A[],int low,int high){
    if(low < high){
        int pivotPos = Partition(A,low,high);
        QuickSort(A, low, pivotPos-1);
        QuickSort(A, pivotPos+1, high);
    }
}

void HeapAdjust(ElemType A[],int k,int len){
    A[0] = A[k];
    for(int i = 2*k; i <= len; i*=2){
        if(i<len && A[i] < A[i+1]){
            i++;
        }
        if(A[i] <= A[0]){
            break;
        }else{
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

void BuildMaxHeap(ElemType A[], int len){
    for(int i = len/2; i>0; i--){
        HeapAdjust(A,i,len);
    }
}

void HeapSort(ElemType A[], int n){
    BuildMaxHeap(A,n);
    for(int i = n; i>1;i--){
        Swap(&A[i], &A[1]);
        HeapAdjust(A,1,i-1);
    }
}

bool isMaxHeap(ElemType A[], int len){
    if(len%2==0){
        if(A[len/2]<A[len]){
            return false;
        }
        for(int i = len/2-1; i > 0; i--){
            if(A[i] < A[2*i] || A[i] < A[2*i+1]){
                return false;
            }
        }
    }else{
        for(int i = len/2; i>0; i--){
            if(A[i]<A[2*i] || A[i]<A[2*i+1]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int a[] = {0,3,2,1,4,5,8,6,7};
    // InsertSort(a, 8);
    HeapSort(a, 8);
    for(int i = 1; i <= 8;i++){
        printf("%d\t",a[i]);
    }
    int b[] = {1,3,2,7,8,6,4,5};
    // BubbleSort(b, 8);
    // SelectSort(b, 8);
    // ShellSort(b, 8);
    // QuickSort(b, 0, 7);
    BubbleSorts(b, 8);
    BubbleApply(b, 8);
    printf("\n");
    for(int i = 0; i < 8; i++){
        printf("%d\t",b[i]);
    }
    int c[] = {17,13,12,56,28,46,53,23,68};
    BubbleSort1(c, 9);
    printf("\n");
    for(int i = 0; i < 9; i++){
        printf("%d\t",c[i]);
    }
}