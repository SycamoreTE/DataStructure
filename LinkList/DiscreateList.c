#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50
#define MIN_INIT 50

typedef struct LNode{
  ElemType data;
  struct LNode *next;
}LNode, LinkList;

LinkList* DiscreateList(LinkList *A){
    int count = 0;
    LinkList* B = (LinkList*)malloc(sizeof(LNode));
    LNode *p = A->next, *ra = A, *rb = B;
    B->next = NULL;
    while(p != NULL){
        count++;
        if(count %2 == 0){
            rb->next = p;
            rb = p;
        }else{
            ra->next = p;
            ra = p;
        }
        p = p->next;
    }
    //使尾指针指向NULL
    ra->next = NULL;
    rb->next = NULL;
    return B;
}

//B链表使用头插法
LinkList* DiscreateList2(LinkList* A){
    int count = 0;
    LinkList* B = (LinkList*)malloc(sizeof(LNode));
    LNode *p = A->next, *ra = A, *r;
    B->next = NULL;   //新建的链表初始化为空，不初始化会进入死循环；
    while(p!=NULL){
        count++;
        if(count %2 == 0){
            r = p->next;
            p->next = B->next;
            B->next = p;
            p = r;
        }else{
            ra->next = p;
            ra = p;
            p = p->next;
        }
    }
    //尾指针指向NULL
    ra->next = NULL;
    return B;
}

LinkList* List_TailInsert(){
    int x;
    LinkList *L = (LinkList*)malloc(sizeof(LNode));
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

void printList(LinkList *L){
    LNode *p;
    p = L->next;
    while(p != NULL){
        printf("%d\t",p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    LinkList *A, *B;
    A = List_TailInsert();
    printList(A);
    B = DiscreateList2(A);
    printList(A);
    printList(B);
    return 0;
}