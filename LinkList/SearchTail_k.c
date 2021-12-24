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

int SearchTail_k(LinkList* L, int k){
    LNode *p = L->next, *pk = L->next;
    int count = 0;
    while(p != NULL && count < k){
        count++;
        p = p->next;
    }
    if(p == NULL){
        return -1;
    }else{
        while(p != NULL){
        p = p->next;
        pk = pk->next;
        }
    }
    return pk->data;
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
    int k;
    L = List_TailInsert();
    printList(L);
    printf("please input k: ");
    scanf("%d",&k);
    printf("\n SearchTail_k : %d",SearchTail_k(L, k));
    return 0;
}
