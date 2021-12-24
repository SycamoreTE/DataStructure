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

void SortPrint(LinkList *L){
    LNode *p = L->next, *r = p->next, *pre;
    p->next = NULL;
    p = r;
    while(p != NULL){
        r = p->next;
        pre = L;
        while(pre->next != NULL && pre->next->data < p->data){
            pre = pre->next;
        }
        p->next = pre->next;
        pre->next = p;
        p = r;
    }
    p = L->next;
    while(p!=NULL){
        printf("%d\t",p->data);
        r = p->next;
        free(p);
        p = r;
    }
    free(L);
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
    LinkList *L;
    L = List_TailInsert();
    printList(L);
    SortPrint(L);
    return 0;
}