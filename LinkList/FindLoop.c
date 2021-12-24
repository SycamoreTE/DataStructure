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

LNode* FindLoop(LinkList *L){
    LNode *p = L, *q = p;
    while(p != NULL && q->next != NULL){
        p = p->next;
        q = q->next->next;
        if(p == q){
            break;
        }
    }
    if(p == NULL || q->next == NULL){
        return NULL;
    }
    while(L != p){
        L = L->next;
        p = p->next;
    }
    return p;
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
    r->next = L;
    return L;
}

void printList(LinkList *L){
    LNode *p;
    p = L->next;
    while(p != NULL && p != L){
        printf("%d\t",p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    LinkList *L;
    L = List_TailInsert();
    printList(L);
    LNode *p = FindLoop(L);
    if(p){
        printf("List is a loop, %d",p->data);
    }else{
        printf("list is not a loop");
    }
    return 0;
}