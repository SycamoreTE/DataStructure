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

//(a1,a2,...,b1,b2,...,bn-1,bn) 转换 (a1,bn,a2,bn-1,...)
void SortList(LinkList *L){
    LNode *p = L->next, *q = p,*r,*p1;
    while(q != NULL){
        p = p->next;
        q = q->next->next;
    }
    //使p指向中间结点, 原地逆置后半段；
    q = p->next;
    p->next = NULL;
    while(q != NULL){
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }
    //后半段元素依次插入前半段
    q = L->next;
    p1 = p->next;
    p->next = NULL;  //把前半段与后半段分隔开
    while(p1 != NULL){
        r = p1->next;
        p1->next = q->next;
        q->next = p1;
        q = q->next->next;
        p1 = r;
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
    LinkList *l;
    l = List_TailInsert();
    printList(l);
    SortList(l);
    printList(l);
    return 0;
}