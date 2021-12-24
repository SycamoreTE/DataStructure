#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 50
#define MAX_NUMBER 1024

typedef struct{
    int data[MAX_SIZE];
    int length;
}SqList;

bool DeleteMin(SqList *L, int *value){
    if(L->length == 0){
        return false;
    }
    int min = L->data[0];
    int pos = 0;
    for(int i = 1; i < L->length; ++i){
        if(L->data[i] < min){
            min = L->data[i];
            pos = i;
        }
    }
    L->data[pos] = L->data[L->length - 1];
    *value = min;
    L->length--;
    return true;
}

bool ReverseList(SqList *L){
    if(L->length == 0){
        return false;
    }
    int mid = (L->length)/2;
    for(int i = 0; i < mid; i++){
        int temp = L->data[i];
        L->data[i] = L->data[L->length - i - 1];
        L->data[L->length - i - 1] = temp;
    }
    return true;
}

bool Delete_x(SqList *L, int x){
    if(L->length == 0){
        return false;
    }
    int k = 0;
    for(int i = 0; i < L->length; i++){
        if(L->data[i] != x){
            L->data[k++] = L->data[i];
        }
    }
    L->length = k;
    return true;
}

//从有序表中删除定值s与t之间的值
bool Delete_s_t(SqList *L, int s, int t){
    if(L->length == 0 || s > t){
        return false;
    }
    int i,j;
    for(i = 0; L->data[i] < s; ++i);
    for(j = 0; L->data[j] <= t; ++j);
    while(j < L->length){
        L->data[i] = L->data[j];
        i++;
        j++;
    }
    L->length = i;
    return true;
}

//线性表中删除定值s与t之间的值
bool Delete_S_T(SqList *L, int s, int t){
    if(L->length == 0 || s > t){
        return false;
    }
    int i,k = 0;
    for(i = 0; i < L->length; i++){
        if(L->data[i] < s || L->data[i] > t){
            L->data[k++] = L->data[i];
        }
    }
    L->length = k;
    return true;
}

//有序表中删除所有重复值元素
bool Delete_Same(SqList *L){
    if(L->length == 0){
        return false;
    }
    int i = 0, j = 1;
    while(j < L->length){
        if(L->data[i] != L->data[j]){
            L->data[++i] = L->data[j];
        }
        j++;
    }
    L->length = i+1;
    return true;
}

//两个有序线性表合并成一个线性表
void MergeList(SqList l1, SqList l2, SqList *L){
    if(l1.length == 0 || l2.length == 0){
        return;
    }
    int i=0,j=0,k=0;
    while(i < l1.length && j < l2.length){
        if(l1.data[i] <= l2.data[j]){
            L->data[k++] = l1.data[i++];
        }else{
            L->data[k++] = l2.data[j++];
        }
    }
    while(i < l1.length){
        L->data[k++] = l1.data[i++];
    }
    while(j < l2.length){
        L->data[k++] = l2.data[j++];
    }
    L->length = k;
}

//将数组中两个顺序表的位置互换
bool Reverse(SqList *L, int begin, int end){
    if(L->length == 0 || begin > end){
        return false;
    }
    int mid = (begin + end)/2;
    for(int i = 0; i < (mid - begin); i++){
        int temp = L->data[begin + i];
        L->data[begin + i] = L->data[end - i];
        L->data[end - i] = temp;
    }
    return true;
}

//在递增有序的线性表中查找数值为x的元素，找到与后继元素交换位置，未找到插入表中
void Find_x(SqList *L, int x){
    int low = 0, high = L->length - 1, mid ;
    while(low < high){
        mid = (low + high)/2;
        if(L->data[mid] < x){
            low = mid + 1;
        }else if(L->data[mid] > x){
            high = mid - 1;
        }else{
            int temp = L->data[mid];
            L->data[mid] = L->data[mid + 1];
            L->data[mid + 1] = temp;
            return;
        }
    }
    if(low >= high){
        L->length++;
        for(int i = L->length - 1; i > high; i--){
            L->data[i] = L->data[i-1];
        }
        L->data[high] = x;
    }
}    

//查找两个等长升序序列A和B的中位数
int Find_Mid(SqList *A, SqList *B){
    int mid = 0;
    int i = 0, j = 0, count = 0;
    while(i < A->length && j < B->length){
        if(A->data[i] <= B->data[j]){
            mid = A->data[i++];
            count++;
        }else{
            mid = B->data[j++];
            count++;
        }
        if(count == A->length){
            return mid;
        }
    }
    return -1;
}

//查找一个整数序列的主元素，n个元素，每个元素的取值范围是0~n-1
int Find_Major(SqList *L){
    int major = 0;
    int *count = (int*)malloc(sizeof(int) * L->length);
    memset(count, 0, sizeof(int)*L->length);
    for(int i = 0; i < L->length; i++){
        count[L->data[i]]++;
    }
    for(int i = 0; i < L->length; i++){
        if(count[i] > L->length/2){
            major = i;
            break;
        }
    }
    return major;
}

//查找数组中未出现的最小正整数
int find_uint_min(SqList *L){
    int min = 0;
    int *tag = (int*)malloc(sizeof(int)*MAX_NUMBER);
    memset(tag, 0, sizeof(int)*MAX_NUMBER);
    for(int i = 0; i < L->length; i++){
        tag[L->data[i] - 1] = 1;
    }
    for(int i = 0; i < MAX_NUMBER; i++){
        if(tag[i] == 0){
            min = i+1;
            break;
        }
    }
    return min;
}

bool IsMin(int a, int b, int c){
    if(a <= b && a <= c){
        return true; 
    }else{
        return false;
    }
}

//三元组(a,b,c)的元素按升序分别存放在三个数组中，求所有可能的三元组中的最小距离
//最小距离计算公式 S = |a - b| + |a - c| + |b - c|
int Min_Distance(SqList A, SqList B, SqList C){
    int a = 0, b = 0, c = 0;
    int i = 0, j = 0, k = 0;
    int min = MAX_NUMBER, distance = 0;
    while(i < A.length && j < B.length && k < C.length){
        distance = abs(A.data[i] - B.data[j]) + abs(A.data[i] - C.data[k]) + abs(B.data[j] - C.data[k]);
        if(distance < min){
            min = distance;
            a = A.data[i];
            b = B.data[j];
            c = C.data[k];
        }
        if(IsMin(A.data[i], B.data[j], C.data[k])){
            i++;
        }else if(IsMin(B.data[j], A.data[i], C.data[k])){
            j++;
        }else{
            k++;
        }
    }
    printf("(%d,%d,%d): %d", a, b, c, min);
    return min;
}                                              

void PrintSqList(SqList *L){
    printf("\n");
    for(int i = 0; i < L->length; ++i){
        printf("%d\t", L->data[i]);
    }
    printf("\n");
}

int main(){
    SqList L1 = {0};
    int min = 0;
    L1.length = 5;
    L1.data[0] = -1; L1.data[1] = 1; L1.data[2] = 2; L1.data[3] = 2; L1.data[4] = 3;
    DeleteMin(&L1, &min);
    PrintSqList(&L1);
    printf("min : %d\n", min);
    Delete_x(&L1, 3);
    PrintSqList(&L1);

    SqList l2 = {0};
    l2.length = 6;
    l2.data[0] = 1; l2.data[1] = 2; l2.data[2] = 3; l2.data[3] = 4; l2.data[4] = 5; l2.data[5] = 6;
    ReverseList(&l2);
    PrintSqList(&l2);
    Delete_S_T(&l2, 1, 4);
    PrintSqList(&l2);

    SqList l3 = {0};
    l3.length = 6;
    for(int i = 0; i < l3.length; ++i){
        l3.data[i] = i+1;
    }
    Delete_s_t(&l3, 1, 4);
    PrintSqList(&l3);
    printf("l3.length %d\n", l3.length);

    SqList list = {0};
    list.length = 8;
    list.data[0] = 2; list.data[1] = 2; list.data[2] = 7; list.data[3] = 7;
    list.data[4] = 7; list.data[5] = 8; list.data[6] = 8; list.data[7] = 10;
    PrintSqList(&list);
    Delete_Same(&list);
    PrintSqList(&list);         
    printf("list length %d\n", list.length);

    MergeList(l3, list, &list);
    PrintSqList(&list);

    SqList A = {0};
    A.length = 15;
    for(int i = 0; i < A.length; i++){
        A.data[i] = i*2 + 1;
    }
    PrintSqList(&A);
    Find_x(&A, 8);
    PrintSqList(&A);

    Reverse(&A, 0, 14);
    Reverse(&A, 0, 4);
    Reverse(&A, 4, 14);
    PrintSqList(&A);

    SqList a = {0}, b = {0};
    a.length = b.length = 5;
    for(int i = 0; i < a.length; i++){
        a.data[i] = 11+2*(i);
    }
    for(int i = 0; i < b.length - 1; i++){
        b.data[i] = 2*(i+1);
    }
    b.data[b.length-1] = 20;
    PrintSqList(&a);
    PrintSqList(&b);
    printf("mid of A and B: %d\n", Find_Mid(&a, &b));

    SqList major = {0};
    major.length = 8;
    major.data[0] = 0; major.data[1] = 5; major.data[2] = 5; major.data[3] = 3;
    major.data[4] = 5; major.data[5] = 7; major.data[6] = 5; major.data[7] = 5;
    PrintSqList(&major);
    printf("major element is : %d\n", Find_Major(&major));

    SqList min1 = {0};
    min1.length = 4;
    min1.data[0] = -5; min1.data[1] = 3; min1.data[2] = 2; min1.data[3] = 3;
    PrintSqList(&min1);
    printf("SearchMin min1: %d\n",find_uint_min(&min1));
    SqList min2 = {0};
    min2.length = 3;
    for(int i = 0; i<min2.length; i++){
        min2.data[i] = i+8;
    }
    PrintSqList(&min2);
    printf("SearchMin min2: %d",find_uint_min(&min2));

    SqList s1 = {0},s2 = {0}, s3 = {0};
    s1.length = 3;
    s1.data[0] = -1; s1.data[1]= 0; s1.data[2] = 9;

    s2.length = 4;
    s2.data[0] = -25; s2.data[1] = -10; s2.data[2] = 10; s2.data[3] = 11;

    s3.length = 5;
    s3.data[0] = 2; s3.data[1] = 9; s3.data[2] = 17; s3.data[3] = 30; s3.data[4] = 41;
    printf("SearchMin : %d",Min_Distance(s1, s2, s3));
}