#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType char
#define MaxSize 50

typedef struct SqStack{
    ElemType data[MaxSize];
    int top;
}SqStack;

typedef struct SqQueue{
    ElemType data[MaxSize];
    int front,rear;
}SqQueue;

typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

void PrintQueue(SqQueue *Q);

void InitStack(SqStack *S){
    S->top = -1;
}

bool StackEmpty(SqStack S){
    if(S.top == -1){
        return true;
    }else{
        return false;
    }
}

bool Push(SqStack *S, ElemType x){
    if(S->top == MaxSize - 1){
        return false;
    }else{
        S->data[++S->top] = x;
        return true;
    }
}

bool Pop(SqStack *S, ElemType *x){
    if(S->top == -1){
        return false;
    }else{
        *x = S->data[S->top--];
        return true;
    }
}

bool GetTop(SqStack *S, ElemType *x){
    if(S->top == -1){
        return false;
    }else{
        *x = S->data[S->top];
        return true;
    }
}

void InitQueue(SqQueue *Q){
    Q->front = Q->rear = -1;
}

bool QueueEmpty(SqQueue Q){
    if(Q.front == Q.rear){
        return true;
    }else{
        return false;
    }
}

bool EnQueue(SqQueue *Q, ElemType x){
    if((Q->rear+1)%MaxSize == Q->front){
        return false;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1)%MaxSize;
    return true;
}

bool DeQueue(SqQueue *Q, ElemType *x){
    if(Q->front == Q->rear){
        return false;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1)%MaxSize;
    return true;
}

bool IsStackValid(char A[]){
    int i = 0, j = 0, k = 0;
    while(A[i] != '\0'){
        switch (A[i]) {
        case 'I':{
            j++;
            break;
        }
        case 'O':{
            k++;
            if(k > j){
                return false;
            }
            break;
        }
        }
        i++;
    }
    if(k != j){
        return false;
    }else{
        return true;
    }
}

//判断单链表的字符是否中心对称
bool IsSymmetry(LinkList L, int length){
    LNode *p = L->next, *q = p;
    SqStack S;
    InitStack(&S);
    for(int i = 0; i < length/2; i++){
        Push(&S, p->data);
        p = p->next;
    }
    if(length%2==1){
        p = p->next;
    }
    while(p && !StackEmpty(S)){
        ElemType value;
        Pop(&S,&value);
        if(value == p->data){
            p = p->next;
        }else{
            return false;
        }
    }
    return true;
}

void ReverseQueue(SqQueue *Q){
    SqStack S;
    InitStack(&S);
    while(!QueueEmpty(*Q)){
        ElemType value;
        DeQueue(Q, &value);
        Push(&S, value);
    }
    while(!StackEmpty(S)){
        ElemType pop;
        Pop(&S, &pop);
        EnQueue(Q, pop);
    }
}

//两个栈模拟队列,S1用于入队,S2用于出队;
//入队时判断能否成功入队S1，若不能，将S1中的所有元素放入S2中，再把入队元素放入S1；
//出队时从S2出栈，若S2为空，将S1中的所有元素放入S2中再出队列；
bool EnQueue1(SqStack *S1, SqStack *S2, ElemType x){
    ElemType e;
    if(Push(S1, x)){
        return true;
    }else if(!StackEmpty(*S2)){
        return false;
    }else{
        while(!StackEmpty(*S1)){
            Pop(S1, &e);
            Push(S2, e);
        }
    }
    Push(S1, x);
    return true;
}

bool DeQueue1(SqStack *S1, SqStack *S2, ElemType *x){
    ElemType e;
    if(!StackEmpty(*S2)){
        Pop(S2, x);
        return true;
    }else if(StackEmpty(*S1)){
        printf("Queue is null");
        return false;
    }else{
        while(!StackEmpty(*S1)){
            Pop(S1,&e);
            Push(S2, e);
        }
    }
    Pop(S2, x);
    return true;
}

bool BracketsCheck(char A[]){
    SqStack S;
    InitStack(&S);
    int i = 0;
    ElemType e;
    while(A[i] != '\0'){
        switch (A[i]) {
        case '{':{
            Push(&S, A[i]);
            break;
        }
        case '[':{
            Push(&S, A[i]);
            break;
        }
        case '(':{
            Push(&S, A[i]);
            break;
        }
        case '}':{
            Pop(&S, &e);
            if(e != '{'){
                return false;
            }
            break;
        }
        case ']':{
            Pop(&S, &e);
            if(e != '['){
                return false;
            }
            break;
        }
        case ')':{
            Pop(&S, &e);
            if(e != '('){
                return false;
            }
            break;
        }
        default: break;
        }
        i++;
    }
    return true;
}

void TrainArrange(char A[]){
    SqQueue Q;
    SqStack S;
    InitQueue(&Q);
    InitStack(&S);
    int i = 0;
    ElemType e;
    while(A[i] != '\0'){
        switch (A[i]) {
        case 'H':{
            Push(&S, A[i]);
            break;
        }
        case 'S':{
            EnQueue(&Q, A[i]);
            break;
        }
        }
        i++;
    }
    while(!StackEmpty(S)){
        Pop(&S,&e);
        EnQueue(&Q, e);
    }
    PrintQueue(&Q);
}

int StackCompute(int x, int n){
    SqStack S;
    InitStack(&S);
    S.data[1] = 1;
    S.data[2] = 2*x;
    int i = 3;
    while(i <= n){
        S.data[i] = 2*x*S.data[i-1] - 2*(n-1)*S.data[i-2];
        i++;
    }
    return S.data[n];
}

LinkList ListTail_Insert(){
    LinkList L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s, *r = L;
    ElemType data;
    printf("please input linklist element : ");
    scanf("%s",&data);
    while(data != 'Q'){
        s = (LNode*)malloc(sizeof(LNode));
        s->data = data;
        r->next = s;
        r = s;
        printf("please input linklist element : ");
        scanf("%s",&data);
    }
    r->next = NULL;
    return L;
}

void PrintList(LinkList L){
    LNode *p = L->next;
    while(p){
        printf("%c\t",p->data);
        p = p->next;
    }
    printf("\n");
}

void PrintQueue(SqQueue *Q){
    ElemType x;
    printf("\n");
    while (!QueueEmpty(*Q)) {
        DeQueue(Q, &x);
        printf("%c\t",x);
    }
    printf("\n");
}

int main(){
    char A[] = "IOIOIIOO";
    if(IsStackValid(A)){
        printf("Stack sequence is valid");
    }else{
        printf("Stack sequence is invalid");
    }

    // LinkList l1 = ListTail_Insert();
    // PrintList(l1);
    // if(IsSymmetry(l1, 3)){
    //     printf("Linklist is symmetry");
    // }else{
    //     printf("Linklist is not symmetry");
    // }
    SqQueue Q;
    SqStack S;
    InitQueue(&Q);
    InitStack(&S);
    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 3);
    ReverseQueue(&Q);
    PrintQueue(&Q);
    char a[] = "(a+b)/{(c-d)*[c+d]}";
    if(BracketsCheck(a)){
        printf("Brackets are valid");
    }else{
        printf("Brackets are invalid");
    }
    char b[] = "HSHSSSHHHHSS";
    TrainArrange(b);
    printf("%d",StackCompute(4, 5));
    return 0;
}