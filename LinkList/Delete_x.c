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

void Delete_x1(LinkList *L, int x){
    
    LNode *p = (LNode*)malloc(sizeof(LNode));
    if(L == NULL){
        return;
    }
    if(L->data == x){
        p = L;
        L = L->next;
        free(p);
        Delete_x1(L, x);
    }else{
        Delete_x1(L->next, x);
    }
}

void Delete_x2(LinkList *L, int x){
    //p为前驱节点，q为后继
    LNode *pre = L, *q = pre->next;
    while(q != NULL){
        if(q->data == x){
            pre->next = q->next;
            free(q);
            q = pre->next;
        }else{
            pre = q;
            q = q->next;
        }
    }
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
    Delete_x2(L, 6);
    printList(L);
    return 0;
}