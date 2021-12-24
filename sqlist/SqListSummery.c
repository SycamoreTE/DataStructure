#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxSize 50
typedef struct {
    ElemType data[MaxSize];
    int length;
}SqList;

bool DeleteMin(SqList *L, int *value){
    if(L->length == 0){
        return false;
    }
    int pos = 0;
    int min = L->data[0];
    for(int i = 0; i < L->length; i++){
        if(L->data[i] < min){
            min = L->data[i];
            pos = i;
        }
    }
    L->data[pos] = L->data[L->length - 1];
    L->length--;
    return true;
}

void Reverse(SqList *L){
    int low = 0, high = L->length - 1;
    int mid = (low + high)/2;
    for(int i = 0; i < mid; i++){
        int temp = L->data[i];
        L->data[i] = L->data[L->length-i-1];
        L->data[L->length-i-1] = temp;
    }
}

bool Delete_x(SqList *L, int x){
    if(L->length == 0){
        return false;
    }
    int k = 0;
    for(int i = 0; i < L->length; i++){
        if(L->data[i] != x){
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
    return true;
}

//从有序顺序表中删除在给定值s与t之间的所有元素
bool Delete_s_t(SqList *L, int s, int t){
    if(L->length == 0 || s > t){
        return false;
    }
    int i,j;
    for(i = 0; L->data[i] < s; i++);
    for(j = 0; L->data[j] <= t; j++);
    while(j < L->length){
        L->data[i] = L->data[j];
        i++;
        j++;
    }
    L->length = i+1;
    return true;
}

//从顺序表中删除给定值s与t之间的所有元素
bool Delete_S_T(SqList *L, int s, int t){
    if(L->length == 0 || s > t){
        return false;
    }
    int k = 0;
    for(int i = 0; i < L->length; i++){
        if(L->data[i] < s || L->data[i] > t){
            L->data[k] = L->data[i];
            k++;
        }
    }
    L->length = k;
    return true;
}

void Delete_Same(SqList *L){
    int i = 0, j = 1;
    for(;j < L->length; j++){
        if(L->data[i] != L->data[j]){
            L->data[++i] = L->data[j];
        }
    }
    L->length = i+1;
}

void MergeList(SqList L1, SqList L2, SqList *L){
    int i = 0, j = 0, k = 0;
    while(i < L1.length && j < L2.length){
        if(L1.data[i] <= L2.data[j]){
            L->data[k++] = L1.data[i++];
        }else{
            L->data[k++] = L2.data[j++];
        }
    }
    while(i < L1.length){
        L->data[k++] = L1.data[i++];
    }
    while(j < L2.length){
        L->data[k++] = L2.data[j++];
    }
    L->length = k;
}

void ReverseList(SqList *L, int begin, int end){
    int mid = (begin + end)/2;
    for(int i = 0; i < mid - begin; i++){
        int temp = L->data[begin + i];
        L->data[begin + i] = L->data[end - i];
        L->data[end - i] = temp;
    }
}

void Find_x(SqList *L, int x){
    int low = 0, high = L->length - 1, mid;
    while(low < high){
        mid = (low + high)/2;
        if(L->data[mid] == x){
            int temp = L->data[mid];
            L->data[mid] = L->data[mid+1];
            L->data[mid+1] = temp;
            break;
        }else if(L->data[mid] < x){
            low = mid + 1;
        }else{
            high = mid - 1;
        }
    }
    if(low >= high){
        for(int i = L->length-1; i > high; i--){
            L->data[i+1]=L->data[i];
        }
        L->data[high] = x;
        L->length++;
    }
}

int Find_Mid(SqList L1, SqList L2){
    if(L1.length != L2.length){
        return -1;
    }
    int count = 0;
    int i = 0, j = 0;
    while(i < L1.length && j < L2.length){
        if(L1.data[i] <= L2.data[j]){
            i++;
            count++;
            if(count == L1.length){
                return L1.data[i-1];
            }
        }else{
            j++;
            count++;
            if(count == L1.length){
                return L2.data[j-1];
            }
        }
    }
    return -1;
}

int FindMajor(SqList L){
    int B[L.length];
    for(int i = 0; i < L.length; i++){
        B[i] = 0;
    }
    for(int i = 0; i < L.length; i++){
        B[L.data[i]]++;
    }
    for(int i = 0; i < L.length; i++){
        if(B[i] > L.length/2){
            return i;
        }
    }
    return 0;
}

//查找序列中未出现的最小正整数
int SearchMin(SqList L, int n){
    int B[n];
    for(int i = 0; i < n; i++){
        B[i] = 0;
    }
    for(int i = 0; i < n; i++){
        B[L.data[i]-1] = 1;
    }
    for(int i = 0; i < n; i++){
        if(B[i] == 0){
            return i+1;
        }
    }
    return 0;
}

#define MIN_INIT 50

bool IsMin(int a, int b, int c){
    if(a <= b && a <= c){
        return true;
    }else{
        return false;
    }
}

int Find_MinDistance(SqList l1, SqList l2, SqList l3){
    int i = 0, j = 0, k = 0;
    int a,b,c;
    int distance = MIN_INIT;
    while(i < l1.length && j < l2.length && k < l3.length){
        int length = abs(l1.data[i]-l2.data[j])+abs(l1.data[i]-l3.data[k])+abs(l2.data[j]-l3.data[k]);
        if(length < distance){
            distance = length;
            a = l1.data[i];
            b = l2.data[j];
            c = l3.data[k];
        }
        if(IsMin(l1.data[i], l2.data[j], l3.data[k])){
            i++;
        }else if(IsMin(l2.data[j], l1.data[i], l3.data[k])){
            j++;
        }else{
            k++;
        }
    }
    printf("(%d,%d,%d), min : %d",a,b,c,distance);
    return distance;
}

int main(){
    SqList list = {0};
    list.length = 8;
    list.data[0] = 2; list.data[1] = 2; list.data[2] = 7; list.data[3] = 7;
    list.data[4] = 7; list.data[5] = 8; list.data[6] = 8; list.data[7] = 10;
    for(int i = 0; i<list.length;i++){
        printf("%d\t",list.data[i]);
    }
    printf("\n");
    Find_x(&list,4);
    for(int i = 0; i<list.length;i++){
        printf("%d\t",list.data[i]);
    }
    printf("\n list length : %d\n",list.length);
    Delete_Same(&list);
    for(int i = 0; i<list.length;i++){
        printf("%d\t",list.data[i]);
    }
    printf("\n list length : %d\n",list.length);
    SqList l1 = {0}, l2 = {0}, l3 = {0};
    l1.length = 4;
    l2.length = 6;
    for(int i = 0; i<l1.length;i++){
        l1.data[i] = i*2 +7;
        printf("%d\t",l1.data[i]);
    }
    printf("\n");
    for(int i = 0; i<l2.length;i++){
        l2.data[i] = i*3+2;
        printf("%d\t",l2.data[i]);
    }
    printf("\n");
    MergeList(l1, l2, &l3);
    for(int i = 0; i < l3.length; i++){
        printf("%d\t",l3.data[i]);
    }
    printf("\n mergelist length: %d\n",l3.length);
    SqList list1 = {0};
    list1.length = 8;
    list1.data[0] = 0; list1.data[1] = 3; list1.data[2] = 5; list1.data[3] = 5;
    list1.data[4] = 5; list1.data[5] = 7; list1.data[6] = 5; list1.data[7] = 5;
    for(int i = 0; i < list1.length; i++){
        printf("%d\t",list1.data[i]);
    }
    printf("\nFindMajor : %d\n",FindMajor(list1));
    SqList s1 = {0},s2 = {0}, s3 = {0};
    s1.length = 3;
    s1.data[0] = -1; s1.data[1]= 0; s1.data[2] = 9;

    s2.length = 4;
    s2.data[0] = -25; s2.data[1] = -10; s2.data[2] = 10; s2.data[3] = 11;

    s3.length = 5;
    s3.data[0] = 2; s3.data[1] = 9; s3.data[2] = 17; s3.data[3] = 30; s3.data[4] = 41;
    printf("SearchMin : %d",Find_MinDistance(s1, s2, s3));
    return 0;
}