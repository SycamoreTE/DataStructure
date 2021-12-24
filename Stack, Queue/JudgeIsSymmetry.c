#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MaxSize 50
#define ElemType char
typedef struct{
    ElemType data[MaxSize];
    int top;
}SqStack;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, LinkList;

//进栈
bool Push(SqStack *s, ElemType x){
    if(s->top == MaxSize-1){
        return false;
    }else{
        s->data[++s->top] = x;
        return true;
    }
}

//出栈
ElemType Pop(SqStack *s){
    if(s->top == -1){
        return -1;
    }else{
        return s->data[s->top--];
    }
}

//初始化
void InitStack(SqStack* s){
    s->top = -1;
}

void printStack(SqStack *s){
    ElemType x;
    while (s->top != -1) {
        x = Pop(s);
        printf("%c\t", x);
    }
    printf("\n");
}

bool IsSymmetry(LinkList *L, int n){
    SqStack S;
    LNode *p = L->next;
    for(int i = 0; i < n/2; i++){
        Push(&S,p->data);
        p = p->next;
    }
    if(n%2 == 1){
        p = p->next;
    }
    while(p != NULL && S.top != -1){
        if(Pop(&S) == p->data){
            p = p->next;
        }else{
            return false;
        }
    }
    return true;
}

LinkList* List_TailInsert(){
    ElemType x;
    LinkList *L = (LinkList*)malloc(sizeof(LNode));
    LNode *s, *r = L;
    printf("please input linklist: ");
    scanf("%s",&x);
    while(x != 'z'){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        s->next = NULL;
        printf("\nplease input linklist: ");
        scanf("%s",&x);
    }
    r->next = NULL;
    return L;
}

void printList(LinkList *L){
    LNode *p;
    p = L->next;
    while(p != NULL){
        printf("%c\t",p->data);
        p = p->next;
    }
    printf("\n");
}

int main(){
    LinkList *L;
    L = List_TailInsert();
    printList(L);
    int x;
    printf("please input element's num: ");
    scanf("%d",&x);
    if(IsSymmetry(L, x)){
        printf("list sequence is symmetry");
    }else{
        printf("list sequence is not symmetry");
    }
    return 0;
}