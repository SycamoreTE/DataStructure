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

ElemType SearchFirstCommon(LinkList *l1, LinkList *l2){
    int len1, len2,dist;
    LNode *p = l1->next, *q = l2->next;
    LinkList *longlist = (LinkList*)malloc(sizeof(LNode));
    LinkList *shortlist = (LinkList*)malloc(sizeof(LNode));
    while(p != NULL){
        len1++;
        p = p->next;
    }
    while(q != NULL){
        len2++;
        q = q->next;
    }
    if(len1 > len2){
        dist = len1 - len2;
        longlist = l1->next; shortlist = l2->next;
    }else{
        dist = len2 - len1;
        longlist = l2->next; shortlist = l1->next;
    }
    while(dist != 0){
        longlist = longlist->next;
        dist--;
    }
    while(longlist != NULL && shortlist != NULL){
        if(longlist->data == shortlist->data){
            return longlist->data;
        }
        longlist = longlist->next;
        shortlist = shortlist->next;
    }
    return 0;
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
    ElemType e;
    l1 = List_TailInsert();
    l2 = List_TailInsert();
    printList(l1);
    printList(l2);
    e = SearchFirstCommon(l1, l2);
    printf("SearchFirstCommon : %d",e);
    return 0;
}