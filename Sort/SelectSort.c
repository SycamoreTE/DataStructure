#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode,*LinkList;

void Swap(int *a, int *b);

void SelectSort1(LinkList L){
    LNode *p = L->next, *min = p;
    while(p){
        min = p;
        LNode *q = p->next;
        while(q){
            if(q->data < min->data){
                Swap(&q->data, &min->data);
            }
            q = q->next;
        }
        p = p->next;
    }
}

void SelectSort(ElemType A[], int n){
    for(int i = 0; i < n-1; i++){
        int min = i;
        for(int j = i+1; j<n; j++){
            if(A[j]<A[min]){
                Swap(&A[j], &A[min]);
            }
        }
    }
}

void HeadAdjust(ElemType A[],int k,int len){
    A[0] = A[k];
    for(int i = 2*k; i<=len; i*=2){
        if(i<len && A[i]<A[i+1]){  //取较大元素的下标
            i++;
        }
        if(A[0]>=A[i]){     //与较大元素下标交换
            break;
        }else{             
            A[k] = A[i];
            k = i;
        }
    }
    A[k] = A[0];  //被筛选的元素放入最终位置
}

void BuildMaxHeap(ElemType A[], int len){
    for(int i = len/2; i>0; i--){    //从表中len/2的非终端节点开始调整排序
        HeadAdjust(A,i,len);   
    }
}

void Swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void HeapSort(ElemType A[], int len){
    BuildMaxHeap(A,len);
    for(int i = len; i>1; i--){  //逐一输出堆顶元素
        Swap(&A[i],&A[1]);       //堆顶元素与堆底元素交换
        HeadAdjust(A,1,i-1);     //重新调整剩余的i-1个元素
    }
}

LinkList List_TailInsert(){
    int x;
    LinkList L = (LinkList)malloc(sizeof(LNode));
    LNode *s, *r = L;
    printf("\nplease input linklist: ");
    scanf("%d",&x);
    while(x != 9999){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        s->next = NULL;
        printf("\nplease input linklist: ");
        scanf("%d",&x);
    }
    r->next = NULL;
    return L;
}

void printList(LinkList L){
    LNode *p;
    p = L->next;
    while(p != NULL){
        printf("%d\t",p->data);
        p = p->next;
    }
    printf("\n");
}

//判断序列是小根堆
bool IsMinHeap(ElemType A[],int len){
    if(len%2==0){
        if(A[len/2] > A[len]){
            return false;
        }
        for(int i = len/2 - 1;i>=1;i--){
            if(A[i]>A[2*i] || A[i]>A[2*i+1]){
                return false;
            }
        }
    }else{
        for(int i = len/2;i>=1;i--){
            if(A[i]>A[2*i] || A[i]>A[2*i+1]){
                return false;
            }
        }
    }
    return true;
}

bool IsMaxHeap(ElemType A[],int len){
    if(len%2==0){
        if(A[len/2] < A[len]){
            return false;
        }
        for(int i = len/2 -1;i>=1;i--){
            if(A[i] < A[2*i] || A[i] < A[2*i+1]){
                return false;
            }
        }
    }else{
        for(int i = len/2; i>=1; i--){
            if(A[i]<A[2*i] || A[i]<A[2*i+1]){
                return false;
            }
        }
    }
    return true;
}

int main(){
    int a[] = {7,6,3,4,1,2,5,8};
    SelectSort(a, 8);
    for(int i = 0; i<8;i++){
        printf("%d\t",a[i]);
    }
    printf("\n");
    int b[] = {0,53,17,78,9,45,65,87,32};
    HeapSort(b, 8);
    for(int i = 1; i <= 8; i++){
        printf("%d\t",b[i]);
    }
    // LinkList L = List_TailInsert();
    // SelectSort1(L);
    // printList(L);
    int c[] = {0,5,8,12,19,28,20,15,22};
    if(IsMinHeap(c, 8)){
        printf("It is a min heap");
    }else{
        printf("It is not a min heap");
    }
    int max[] = {0,87,45,78,32,17,65,53,9};
    if(IsMaxHeap(max, 8)){
        printf("\nIt is a max heap");
    }else{
        printf("\nIt is not a max heap");
    }
    return 0;
}