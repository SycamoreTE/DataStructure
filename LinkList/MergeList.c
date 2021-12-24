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

//头插法，元素递减
LinkList* MergeList(LinkList *l1, LinkList *l2){
    LNode *p = l1->next, *q = l2->next, *r;
    l1->next = NULL;
    while(p != NULL && q != NULL){
        if(p->data <= q->data){
            r = p->next;
            p->next = l1->next;
            l1->next = p;
            p = r;
        }else{
            r = q->next;
            q->next = l1->next;
            l1->next = q;
            q = r;
        }
    }
    while(p!= NULL){
        r = p->next;
        p->next = l1->next;
        l1->next = p;
        p = r;
    }
    while(q != NULL){
        r = q->next;
        q->next = l1->next;
        l1->next = q;
        p = r;
    }
    return l1;
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
    printf("input first linklist: \n");
    A = List_TailInsert();
    printf("input second linklist: \n");
    B = List_TailInsert();
    printList(A);
    printList(B);
    A = MergeList(A, B);
    printList(A);
    return 0;
}