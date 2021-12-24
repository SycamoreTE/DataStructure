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

void Delete_abs_same(LinkList* L, int length){
    LNode *p = L->next, *pre = L,*r;
    ElemType e;
    int b[length-1];
    for(int i = 0; i < length; i++){
        b[i] = 0;
    }
    while(p != NULL){
        r = p->next;
        e = abs(p->data);
        if(b[e] == 0){
            b[e] = 1;
            pre = p;
            p = p->next;
        }else{
            pre->next = p->next;
            free(p);
            p = r;
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
    int length;
    LinkList *l;
    l = List_TailInsert();
    printList(l);
    printf("please input list's length :");
    scanf("%d",&length);
    Delete_abs_same(l, length);
    printList(l);
    return 0;
}