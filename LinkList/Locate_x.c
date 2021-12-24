#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int

typedef struct DNode{
    int freq;
    ElemType data;
    struct DNode *prior, *next;
}DNode, DLinkList;

DLinkList* Locate(DLinkList* L, int x){
    DNode *p = L->next, *q;
    while(p && p->data != x){
        p = p->next;
    }
    if(p == NULL){
        return NULL;
    }else{
        p->freq++;
        //取出p结点
        p->prior->next = p->next;
        p->next->prior = p->prior;
        q = L->next;
        //找到p结点插入的位置
        while(q != NULL && q->freq > p->freq){
            q = q->next;
        }
        //p 在 q 前插入 p->q
        q->prior->next = p;
        p->next = q;
        p->prior = q->prior;
        q->prior = p;
    }
    return L;
}

DLinkList* ListTailInsert(){
    DLinkList* L = (DLinkList*)malloc(sizeof(DNode));
    L->next = NULL;
    DNode *r = L, *s;
    int x, freq;
    printf("\nplease input linklist: ");
    scanf("%d",&x);
    printf("\nplease input DNode frequence: ");
    scanf("%d",&freq);
    while(x != 9999){
        s = (DNode*)malloc(sizeof(DNode));
        s->data = x;
        s->freq = freq;
        s->prior = r;
        r->next = s;
        r = s;
        s->next = L;
        L->prior = s;
        printf("\nplease input linklist: ");
        scanf("%d",&x);
        printf("\nplease input DNode frequence: ");
        scanf("%d",&freq);
    }
    r->next = L;
    L->prior = r;
    return L;
}

void printlist2(DLinkList *L){
    DNode *p = L;
    while(p != NULL && p->next != L){
        p = p->next;
        printf("%d, freq: %d\t",p->data,p->freq);
    }
    printf("\n");
}

int main(){
    DLinkList* L;
    L = ListTailInsert();
    printlist2(L);
    L = Locate(L, 6);
    printlist2(L);
    return 0;
}