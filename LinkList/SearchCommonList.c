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

LinkList* SearchCommonList(LinkList *A, LinkList *B){
    LinkList *C = (LinkList*)malloc(sizeof(LNode));
    C->next = NULL;
    LNode *pa = A->next, *pb = B->next, *pc = C,*r;
    while(pa != NULL && pb != NULL){
        if(pa->data < pb->data){
            pa = pa->next;
        }else if(pa->data > pb->data){
            pb = pb->next;
        }else{
            r = pa->next;
            pc->next = pa;
            pc = pa;
            pa = r;
            pb = pb->next;
        }
    }
    pc->next = NULL;
    return C;
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
    LinkList *A, *B, *C;
    printf("input first linklist: \n");
    A = List_TailInsert();
    printf("input second linklist: \n");
    B = List_TailInsert();
    printList(A);
    printList(B);
    C = SearchCommonList(A, B);
    printList(C);
    return 0;
}