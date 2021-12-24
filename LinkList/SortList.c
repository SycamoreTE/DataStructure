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

void SortList(LinkList* L){
    LNode *q = L->next, *r = q->next, *pre;
    q->next = NULL;
    q = r;
    while(q != NULL){
        r = q->next;
        pre = L;   //每次循环找插入的结点时，pre 总指向 单链表头节点
        while((pre->next != NULL)&&(pre->next->data < q->data)){
            pre = pre->next;
        }
        q->next = pre->next;
        pre->next = q;        
        q = r;
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
    SortList(L);
    printList(L);
    return 0;
}