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

void Delete_s_t(LinkList* L, int s, int t){
    LNode *p = L->next, *pre = L,*r;
    while(p != NULL){
        r = p->next;
        if(p->data > s && p->data < t){
            pre->next = p->next;
            free(p);
            p = r;
        }else{
            pre = p;
            p = p->next;
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
    int s, t;
    L = List_TailInsert();
    printList(L);
    Delete_s_t(L, 5, 20);
    printList(L);
    return 0;
}