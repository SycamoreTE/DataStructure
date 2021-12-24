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

LinkList* Union(LinkList* A, LinkList* B){
    LNode *p = A->next, *q = B->next;
    A->next = NULL;
    LNode *ra = A, *r;
    while(p != NULL && q !=NULL){
        if(p->data == q->data){
            r = p->next;
            ra->next = p;
            ra = p;
            p = r;
            q = q->next;
        }else if(p->data < q->data){
            p = p->next;
        }else{
            q = q->next;
        }
    }
    //释放未遍历完的结点
    if(p != NULL){
        q = p;
    }
    while(q != NULL){
        r = q->next;
        free(q);
        q = r;
    } 
    ra->next = NULL;
    return A;
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
    LinkList *A, *B;
    printf("input first linklist: \n");
    A = List_TailInsert();
    printf("input second linklist: \n");
    B = List_TailInsert();
    printList(A);
    printList(B);
    A = Union(A, B);
    printList(A);
    return 0;
}