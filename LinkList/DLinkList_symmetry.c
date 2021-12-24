#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct DNode{
    ElemType data;
    struct DNode *prior, *next;
}DNode, DLinkList;

bool Symmetry(DLinkList *L){
    DNode *p = L->prior, *q = L->next;
    while(p != q && p->next != q){
        if(p->data == q->data){
            p = p->prior;
            q = q->next;
        }else{
            return false;
        }
    }
    return true;
}

DLinkList* ListTailInsert(){
    DLinkList* L = (DLinkList*)malloc(sizeof(DNode));
    L->next = NULL;
    DNode *r = L, *s;
    int x;
    printf("\nplease input linklist: ");
    scanf("%d",&x);
    while(x != 9999){
        s = (DNode*)malloc(sizeof(DNode));
        s->data = x;
        s->prior = r;
        r->next = s;
        r = s;
        s->next = L;
        L->prior = s;
        printf("\nplease input linklist: ");
        scanf("%d",&x);
    }
    r->next = L;
    L->prior = r;
    return L;
}

void printList1(DLinkList *L){
    DNode *p = L;
    while(p != NULL && p->prior != L){
        p = p->prior;
        printf("%d\t",p->data);
    }
    printf("\n");
}

void printlist2(DLinkList *L){
    DNode *p = L;
    while(p != NULL && p->next != L){
        p = p->next;
        printf("%d\t",p->data);
    }
    printf("\n");
}

int main(){
    DLinkList *A;
    A = ListTailInsert();
    printList1(A);
    printlist2(A);
    if(Symmetry(A)){
        printf("Dlinklist is symmetry");
    }else{
        printf("Dlinklist is not symmetry");
    }
    return 0;
}