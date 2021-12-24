#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

//直接插入排序
void InsertSort(ElemType A[], int n){
    int i,j;
    for(i = 2; i <= n; i++){
        if(A[i] < A[i-1]){
            A[0] = A[i];
            for(j = i-1; j > 0 && A[j]>A[0];--j){
                A[j+1] = A[j];
            }
            A[j+1] = A[0];
        }
    }
}

void BinaInsertSort(ElemType A[], int n){
    int i,j,low,high;
    for(i = 2; i <= n; i++){
        if(A[i] < A[i-1]){
            A[0] = A[i];
            low = 1, high = i-1;
            while(low <= high){
                int mid = (low + high)/2;
                if(A[mid] > A[0]){
                    high = mid - 1;
                }else{
                    low = mid + 1;
                }
            }
            for(j = i-1; j > high; --j){
                A[j+1] = A[j];
            }
            A[high+1] = A[0];
        }
    }
}

void ShellSort(ElemType A[], int n){
    int i,j;
    for(int d = n/2; d >= 1; d = d/2){
        for(i = d+1; i <= n; ++i){
            if(A[i] < A[i-d]){
                A[0] = A[i];
                for(j=i-d; j>0 && A[j]>A[0]; j = j-d){
                    A[j+d] = A[j];
                }
                A[j+d] = A[0];
            }
        }
    }
}

void BubbleSort(ElemType *A, int n){
    int i,j;
    for(i = 0; i < n; i++){
        for(j = n-1; j > i; --j){
            if(A[j]<A[j-1]){
                swap(&A[j], &A[j-1]);
            }
        }
    }
}

void TwoWayBubbleSort(ElemType A[], int n){
    int low = 0, high = n-1;
    while(low < high){
        for(int i = low; i < high; i++){
            if(A[i]>A[i+1]){
                swap(&A[i], &A[i+1]);
            }
        }
        high--;
        for(int j = high; j > low; j--){
            if(A[j-1]>A[j]){
                swap(&A[j],&A[j-1]);
            }
        }
        low++;
    }
}

int Partition(int A[], int low, int high){
    int rand_Index = low + rand()%(high - low + 1);
    int temp = A[low];
    A[low] = A[rand_Index];
    A[rand_Index] = temp;
    int pivot = A[low];
    while(low < high){
        while(low < high && A[high] > pivot){
            high--;
        }
        A[low] = A[high];
        while(low < high && A[low] < pivot){
            low++;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

void QuickSort(int A[], int low, int high){
    if(low < high){   //递归退出的条件
        int pivotpos = Partition(A, low, high);
        QuickSort(A, low, pivotpos-1);
        QuickSort(A, pivotpos+1, high);
    }
}

//排序，将所有奇数排在偶数前
void BubbleApply(int A[], int n){
    int i,j;
    for(i = 0; i < n; i++){
        for(j = n-1; j>i; --j){
            if(A[j]%2==1){
                swap(&A[j-1], &A[j]);
            }
        }
    }
}

//排序，将所有偶数排在奇数前
void QuickSortApply(int A[], int n){
    int low = 0, high = n-1;
    while(low < high){
        while(low < high && A[high]%2==1){
            high--;
        }
        while (low < high && A[low]%2==0) {
            low++;
        }
        swap(&A[low], &A[high]);
    }
}

//找出第k小的元素值
int Find_kth_min(int A[], int n, int k){
    int i,j;
    for(i = 0; i < k; i++){
        for(j = n-1; j > i; --j){
            if(A[j-1] > A[j]){
                swap(&A[j-1], &A[j]);
            }
        }
    }
    return A[k-1];
}

//将序列A分为两个集合，使个数n1-n2最小但S1-S2最大
//无需进行全序列的排序
int SetPartition(int A[], int n){
    int pivot, low = 0, low0 = 0, high = n-1, high0 = n-1,flag = true, i;
    int s1 = 0, s2 = 0;
    while(flag){
        pivot = A[low];
        while (low < high) {
            while(low < high && A[high] > pivot){
                high--;
            }
            A[low] = A[high];
            while(low < high && A[low] < pivot){
                low++;
            }
            A[high] = A[low];
        }
        A[low] = pivot;
        if(low == (n/2)-1){
            flag = false;
        }else{
            if(low < (n/2)-1){
                low0 = ++low;
                high = high0;
            }else{
                high0 = --high;
                low = low0;
            }
        }
    }
    for(i = 0; i < n/2; i++){
        s1 += A[i];
    }
    for(;i < n; i++){
        s2 += A[i];
    }
    return s2 - s1;
}

typedef enum{
    RED = 1,
    WHITE,
    BLUE,
}color;

//将条块按照红、白、蓝三种颜色排序
void Flag_Arrange(color a[], int n){
    int i = 0, j = 0, k = n - 1;
    while(j <= k){
        switch (a[j]) {
           case RED:{
               swap(&a[i], &a[j]);
               i++;
               j++;
               break;
           }
           case WHITE:{
               j++;
               break;
           }
           case BLUE:{
               swap(&a[j], &a[k]);
               k--;
               break;
           }
        }
    }
}

void SelectSort(int A[], int n){
    int i,j;
    for(i = 0; i < n-1; i++){
        int min = i;
        for(j = i+1; j < n; j++){
            if(A[j] < A[min]){
                swap(&A[j], &A[min]);
            }
        }
    }
}

void HeadAdjust(int A[], int k, int n){
    A[0] = A[k];
    for(int i = 2*k; i<=n; i*=2){
        if(i<n && A[i]<A[i+1]){
            i++;
        }
        if(A[0]>A[i]){
            break;
        }else{
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];
}

void BuildMaxHeap(int A[], int n){
    for(int i = n/2; i > 0; i--){
        HeadAdjust(A,i,n);
    }
}

void HeapSort(int A[], int n){
    BuildMaxHeap(A,n);
    for(int i = n; i > 1; --i){
        swap(&A[1], &A[i]);
        HeadAdjust(A, 1, i-1);
    }
}

bool IsMaxHeap(int A[], int n){
    if(n%2 == 0){
        if(A[n/2] < A[n]){
            return false;
        }
        for(int i = n/2 - 1; i > 0; i--){
            if(A[i] < A[2*i] || A[i] < A[2*i+1]){
                return false;
            }
        }
    }else{
        for(int i = n/2; i>0; i--){
            if(A[i]<A[2*i] || A[i]<A[2*i+1]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    ElemType a[8] = {0,7,6,5,4,3,2,1};
    // InsertSort(a, 7);
    // ShellSort(a, 7);
    HeapSort(a, 7);
    for(int i = 1; i <= 7; i++){
        printf("%d\t",a[i]);
    }
    printf("\n");
    ElemType b[9] = {24,12,23,11,31,21,56,45,67};
    // BinaInsertSort(b, 8);
    SelectSort(b, 9);
    for(int i = 0; i <= 8; i++){
        printf("%d\t",b[i]);
    }
    int c[9] = {24,12,23,11,31,21,56,45,67};
    // BubbleSort(c, 9);
    // TwoWayBubbleSort(c, 9);
    // QuickSort(c, 0, 8);
    // BubbleApply(c, 9);
    // QuickSortApply(c, 9);
    // printf("\n%d", Find_kth_min(c, 9, 7));
    printf("\ns2 - s1 : %d",SetPartition(c, 9)); 
    printf("\n");
    for(int i = 0; i < 9; i++){
        printf("%d\t",c[i]);
    }
    color flag[] = {BLUE,BLUE,WHITE,WHITE,RED,WHITE};
    Flag_Arrange(flag, 6);
    printf("\n");
    for(int i = 0; i < 6; i++){
        printf("%d\t",flag[i]);
    }
    return 0;
}