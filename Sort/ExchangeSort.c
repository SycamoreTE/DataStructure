#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

void BubbleSort(ElemType A[],int n){
    for(int i = 0; i < n; i++){
        // int flag = false;
        for(int j = n-1; j > i; --j){
            if(A[j-1]>A[j]){
                int temp = A[j-1];
                A[j-1] = A[j];
                A[j] = temp;
                // flag = true;               
            }
        }
        // if(flag == false){
        //     return;
        // }
    }
}

//双向冒泡排序，正反两个方向交替，每一趟分别找出最大关键字和最小关键字
void BubbleSorts(ElemType A[], int n){
    int low = 0, high = n - 1;
    int flag = true;
    while(low < high && flag){
        flag = false;
        for(int i = low; i < high; i++){
            if(A[i] > A[i+1]){
                int temp = A[i];
                A[i] = A[i+1];
                A[i+1] = temp;
                flag = true;
            }
        }
        high--;
        for(int i = high; i > low; i--){
            if(A[i] < A[i-1]){
                int temp = A[i];
                A[i] = A[i-1];
                A[i-1] = temp;
                flag = true;
            }
        }
        low++;
    }
}

//把所有奇数移动到偶数前
void BubbleApply(ElemType A[],int n){
    for(int i = 0; i < n; i++){
        int flag = false;
        for(int j = n-1; j > i; j--){
            if(A[j]%2 == 1){
                int temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
                flag = true;
            }
        }
        if(flag == false){
            return;
        }
    }
}

//所有奇数移动到偶数前，快速排序的思想，从前往后找偶数，从后往前找奇数，两者交换
void Move(ElemType A[],int len){
    int i = 0,j = len - 1;
    while(i<j){
        while(i<j && A[i]%2 == 1){
            i++;
        }
        while(i<j && A[j]%2 == 0){
            j--;
        }
        if(i<j){
            int temp = A[i];
            A[i] = A[j];
            A[j] = temp;
        }
        i++;j--;
    }
}

int Kth_elem(ElemType A[], int n, int k){
    for(int i=0; i<k;i++){
        for(int j=n-1; j>i; j--){
            if(A[j] < A[j-1]){
                int temp = A[j];
                A[j] = A[j-1];
                A[j-1] = temp;
            }
        }
    }
    return A[k-1];
}

int Partition(ElemType A[], int low, int high){
    int pivot = A[low];
    while(low < high){
        while(low < high && A[high] >= pivot){
            --high;
        }
        A[low] = A[high];
        while(low < high && A[low] <= pivot){
            ++low;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

int Partition2(ElemType A[], int low, int high){
    int rand_Index = low + rand()%(high - low + 1);
    int temp = A[low];
    A[low] = A[rand_Index];
    A[rand_Index] = temp;
    ElemType pivot = A[low];
    while(low < high){
        while(low < high && A[high] >= pivot){
            --high;
        }
        A[low] = A[high];
        while(low < high && A[low] <= pivot){
            ++low;
        }
        A[high] = A[low];
    }
    A[low] = pivot;
    return low;
}

//集合A划分为S1，S2,使元素个数相差最小，但两集合元素之和的差值最大；
int SetPartition(ElemType A[], int n){
    int low = 0,low0 = 0,high = n-1,high0 = n-1,flag = true,k=n/2;
    int s1=0,s2=0;
    while(flag){
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
        if(low == k){
            flag = false;
        }else if(low < k){
            low0 = low++;
            high = high0;
        }else{
            high0 = high--;
            low = low0;
        }
    } 
    for(int i = 0; i < k; i++){
        s1+=A[i];
    }
    for(int i = k; i < n; i++){
        s2+=A[i];
    }
    return s2-s1;
}

void QuickSort(ElemType A[],int low,int high){
    if(low < high){
        int pivotPos = Partition2(A,low,high);
        QuickSort(A, low, pivotPos-1);
        QuickSort(A, pivotPos+1, high);
    }
}

//调整色块，使条块按红、白、蓝的顺序排好
typedef enum{
    RED,
    WHITE,
    BLUE,
}color;

void Flag_Arrange(color a[], int n){
    int i = 0,j = 0,k = n-1;
    while(j<k){
        switch (a[j]) {
            case RED :{
                color temp = a[j];
                a[j] = a[i];
                a[i] = temp;
                i++;j++;
                break;
            }
            case WHITE:{
                j++;
                break;
            }
            case BLUE:{
                color temp1 = a[j];
                a[j] = a[k];
                a[k] = temp1;
                k--;
            }
        }
    }
}

int main(){
    int a[] = {5,6,7,3,4,1,2};
    // BubbleSort(a, 7);
    // BubbleSorts(a, 7);
    // BubbleApply(a, 7);
    // Move(a, 7);
    printf("%d\n",SetPartition(a, 7));
    printf("%d",Kth_elem(a, 7, 2));
    printf("\n");
    for(int i = 0; i < 7; i++){
        printf("%d\t",a[i]);
    }
    int b[] = {49,38,65,97,76,13,27,49};
    QuickSort(b, 0, 7);
    printf("\n");
    for(int i = 0; i < 8; i++){
        printf("%d\t",b[i]);
    }
    color c[] = {BLUE,RED,WHITE,RED,BLUE,WHITE};
    Flag_Arrange(c, 6);
    printf("\n");
    for(int i = 0; i<6;i++){
        printf("%d\t",c[i]);
    }
}