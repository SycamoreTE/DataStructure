#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct LNode{
  ElemType data;
  struct LNode *next;
}LNode, LinkList;

typedef struct DNode{
    ElemType data;
    struct DNode *prior, *next;
}DNode, DLinkList;

LinkList* MergeDLinkList(LinkList* A, LinkList* B){
    LNode *p = A, *q = B;
    while(p->next != NULL){
        p = p->next;
    }
    p->next = B->next;
    return A;
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
    LinkList *l1, *l2;
    l1 = List_TailInsert();
    l2 = List_TailInsert();
    printList(l1);
    printList(l2);
    l1 = MergeDLinkList(l1, l2);
    printList(l1);
    return 0;
}