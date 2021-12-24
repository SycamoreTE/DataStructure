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

int SequenceSonList(LinkList* A, LinkList* B){
    LNode *p = A->next, *q = B->next;
    while(p != NULL && q != NULL){
        if(p->data == q->data){
            p = p->next;
            q = q->next;
        }else{
            p = p->next;
            q = B->next;
        }
    }
    if(!q){
        return 1;
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
    LinkList *A = NULL, *B = NULL;
    printf("\ninput first linklist: \n");
    A = List_TailInsert();
    printf("\ninput second linklist: \n");
    B = List_TailInsert();
    printList(A);
    printList(B);
    if(SequenceSonList(A, B)){
        printf("B is sonlist");
    }else{
        printf("B is not sonlist");
    }
    return 0;
}