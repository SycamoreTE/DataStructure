#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int
#define MAX_SIZE 50

typedef struct SqStack
{
    ElemType data[MAX_SIZE];
    int top;
} SqStack;

typedef struct SqQueue
{
    ElemType data[MAX_SIZE];
    int front, rear;
} SqQueue;

typedef struct LNode
{
    ElemType data;
    struct LNode *next;

} LNode, *LinkList;

void InitStack(SqStack *S) { S->top = -1; }

bool StackEmpty(SqStack *S)
{
    if (S->top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Push(SqStack *S, ElemType x)
{
    if (S->top == MAX_SIZE - 1)
    {
        return false;
    }
    else
    {
        S->data[++S->top] = x;
        return true;
    }
}

bool Pop(SqStack *S, ElemType *x)
{
    if (S->top == -1)
    {
        return false;
    }
    else
    {
        *x = S->data[S->top--];
        return false;
    }
}

bool GetTop(SqStack *S, ElemType *x)
{
    if (S->top == -1)
    {
        return false;
    }
    else
    {
        *x = S->data[S->top];
        return true;
    }
}

void InitQueue(SqQueue *Q)
{
    Q->front = Q->rear = 0;
}

bool QueueEmpty(SqQueue *Q)
{
    if (Q->front == Q->rear)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool EnQueue(SqQueue *Q, ElemType x)
{
    if ((Q->rear + 1) % MAX_SIZE == Q->front)
    {
        return false;
    }
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAX_SIZE;
    return true;
}

bool DeQueue(SqQueue *Q, ElemType *x)
{
    if (Q->front == Q->rear)
    {
        return false;
    }
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAX_SIZE;
    return true;
}

/** 判断含n个元素的单链表是否中心对称**/
bool IsSymmertry(LinkList L, int n)
{
    SqStack S;
    InitStack(&S);
    int count = 0;
    LNode *p = L->next;
    while (p && count < n / 2)
    {
        Push(&S, p->data);
        count++;
        p = p->next;
    }
    if (n % 2 == 1)
    {
        p = p->next;
    }
    while (!StackEmpty(&S))
    {
        ElemType x;
        Pop(&S, &x);
        if (x == p->data)
        {
            p = p->next;
        }
        else
        {
            return false;
        }
    }
    if (p == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** 判断入栈出栈操作是否合法 I代表入栈，O代表出栈**/
bool IsValid(char list[])
{
    int i = 0, in = 0, out = 0;
    while (list[i] != '\0')
    {
        switch (list[i])
        {
        case 'O':
            out++;
            if (out > in)
            {
                return false;
            }
            break;
        case 'I':
            in++;
            break;
        default:
            break;
        }
        i++;
    }
    if (in >= out)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/** 将队列中的元素逆置 **/
void ReverseQueue(SqQueue *Q){
    SqStack S;
    InitStack(&S);
    ElemType x = 0;
    while(!QueueEmpty(Q)){
        DeQueue(Q, &x);
        Push(&S, x);
    }
    while(!StackEmpty(&S)){
        Pop(&S, &x);
        EnQueue(Q, x);
    }
}

/** 判断表达式中的括号(),{},[]是否配对**/
bool BracketsCheck(char A[]){
    SqStack S;
    InitStack(&S);
    int i = 0;
    int check = 0;
    while(A[i] != '\0'){
        switch (A[i]) {
        case '(':{
            Push(&S, A[i]);
            break; 
        }
        case '{':{
            Push(&S, A[i]);
            break;
        }
        case '[':{
            Push(&S, A[i]);
        }
        case ')':{
            Pop(&S, &check);
            if(check != '('){
                return false;
            }
            break;
        }
        case '}':{
            Pop(&S, &check);
            if(check != '}'){
                return false;
            }
            break;
        }
        case ']':{
            Pop(&S, &check);
            if(check != ']'){
                return false;
            }
            break;
        }
        default:{
            break;
        }
        }
        i++;
    }
    return true;
}

/** 火车调度 火车序列，将火车软座调整到火车硬座后**/
void TrainArrange(char *train){
    SqQueue Q;
    SqStack S;
    InitQueue(&Q);
    InitStack(&S);
    int i = 0, element = 0;
    while(train[i] != '\0'){
        switch (train[i]) {
            case 'H':{
                Push(&S, train[i]);
                break;
            }
            case 'S':{
                EnQueue(&Q, train[i]);
                break;
            }
        }
        i++;
    }
    while(!StackEmpty(&S)){
        Pop(&S, &element);
        EnQueue(&Q, element);
    }
    i = 0;
    while(!QueueEmpty(&Q)){
        DeQueue(&Q, &element);
        train[i] = element;
        i++;
    }
}

/**实现递归函数 
 **         1,    n = 0
 **Pn(x) =  2x,   n = 1
 **         2xPn-1(x) - 2(n-1)Pn-2(x),  n > 1
**/
#define MAX_NUM 1000
typedef struct stack{
    float data[MAX_NUM];
    int top;
}stack;

long long Recursion_func(float x, int n){
    stack s;
    s.top = -1;
    if(n == 0){
        return 1;
    }
    if(n == 1){
        return 2*x;
    }
    s.data[++s.top] = 1;
    s.data[++s.top] = 2*x;
    for(int i = 0; i < n - 1; i++){
        s.top++;
        s.data[s.top] = 2*x*s.data[s.top-1] - 2*(n-1)*s.data[s.top-2];
    }
    return s.data[s.top];
}

void PrintQueue(SqQueue *Q){
    ElemType x = 0;
    while(!QueueEmpty(Q)){
        DeQueue(Q, &x);
        printf("%d\t", x);
    }
    printf("\n");
}

LinkList List_TailInsert()
{
    LinkList L = (LinkList)malloc(sizeof(LinkList));
    LNode *s, *r = L;
    ElemType x;
    printf("please input linklist element: ");
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        printf("please input linklist element: ");
        scanf("%d", &x);
    }
    r->next = NULL;
    return L;
}

void PrintList(LinkList L)
{
    LNode *p = L->next;
    while (p)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
}

int main()
{
    // LinkList list1 = List_TailInsert();
    // PrintList(list1);
    // if (IsSymmertry(list1, 6))
    // {
    //     printf("list is symmertry");
    // }
    // else
    // {
    //     printf("list is not symmertry");
    // }
    // printf("\n");

    char list2[] = "IOIOIIOO";
    if (IsValid(list2))
    {
        printf("is valid");
    }
    else
    {
        printf("is invalid");
    }
    printf("\n");

    char statement[] = "{(a+b)-{c/d}/[a*b]}";
    if(BracketsCheck(statement)){
        printf("Brackets valid");
    }else{
        printf("Brackets invalid");
    }
    printf("\n");

    printf("recursion result: %lld\n", Recursion_func(3.2, 20));

    SqQueue Q;
    InitQueue(&Q);
    EnQueue(&Q, 1);
    EnQueue(&Q, 2);
    EnQueue(&Q, 4);
    ReverseQueue(&Q);
    PrintQueue(&Q);
    return 0;
}