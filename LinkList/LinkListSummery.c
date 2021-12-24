#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
    int freq;
} LNode, *LinkList;

typedef struct DNode
{
    ElemType data;
    struct DNode *prior, *next;
} DNode, *DLinkList;

static void PrintList(LinkList L);

void Delete_x(LinkList L, int x)
{
    if (L == NULL)
    {
        return;
    }
    if (L->data == x)
    {
        LNode *p = L;
        L = L->next;
        free(p);
        Delete_x(L, x);
    }
    else
    {
        Delete_x(L->next, x);
    }
}

void Delete_x1(LinkList L, int x)
{
    LNode *p = L->next, *pre = L, *r;
    while (p != NULL)
    {
        if (p->data == x)
        {
            r = p->next;
            pre->next = p->next;
            free(p);
            p = r;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}

void LocalReverse(LinkList L)
{
    LNode *q = L->next, *r;
    L->next = NULL; //头结点后置为空
    while (q)
    {
        r = q->next;
        q->next = L->next;
        L->next = q;
        q = r;
    }
}

void Delete_Min(LinkList L)
{
    LNode *p = L->next, *pre = L, *min = p, *minpre = pre;
    while (p)
    {
        if (p->data < min->data)
        {
            min = p;
            minpre = pre;
        }
        pre = p;
        p = p->next;
    }
    minpre->next = min->next;
    free(min);
}

void SortList(LinkList L)
{
    LNode *p = L->next, *q = p->next, *r, *pre;
    p->next = NULL;
    while (q)
    {
        pre = L;
        r = q->next;
        while (pre->next && pre->next->data < q->data)
        {
            pre = pre->next;
        }
        q->next = pre->next;
        pre->next = q;
        q = r;
    }
}

void Delete_s_t(LinkList L, int s, int t)
{
    LNode *p = L->next, *pre = L, *r;
    while (p)
    {
        if (p->data > s && p->data < t)
        {
            r = p->next;
            pre->next = p->next;
            free(p);
            p = r;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}

int FindCommon(LinkList l1, LinkList l2)
{
    int length1 = 0, length2 = 0, dist;
    LinkList longlist, shortlist;
    LNode *p = l1->next, *q = l2->next;
    while (p)
    {
        length1++;
        p = p->next;
    }
    while (q)
    {
        length2++;
        q = q->next;
    }
    if (length1 > length2)
    {
        dist = length1 - length2;
        longlist = l1;
        shortlist = l2;
    }
    else
    {
        dist = length2 - length1;
        longlist = l2;
        shortlist = l1;
    }
    p = longlist->next, q = shortlist->next;
    while (dist--)
    {
        p = p->next;
    }
    while (p && q)
    {
        if (p->data == q->data)
        {
            return p->data;
        }
        p = p->next;
        q = q->next;
    }
    return -1;
}

void PrintSortList(LinkList L)
{
    LNode *p = L->next, *r = p->next, *pre;
    p->next = NULL;
    p = r;
    while (p)
    {
        r = p->next;
        pre = L;
        while (pre->next && pre->next->data < p->data)
        {
            pre = pre->next;
        }
        p->next = pre->next;
        pre->next = p;
        p = r;
    }
    PrintList(L);
}

LinkList DiscreateA_B(LinkList A)
{
    LinkList B = (LinkList)malloc(sizeof(LNode));
    B->next = NULL;
    int count = 0;
    LNode *p = A->next, *ra = A, *rb = B, *q;
    A->next = NULL;
    while (p)
    {
        q = p->next;
        count++;
        if (count % 2 == 1)
        {
            ra->next = p;
            ra = p;
            p = q;
        }
        else
        {
            rb->next = p;
            rb = p;
            p = q;
        }
    }
    ra->next = NULL;
    rb->next = NULL;
    return B;
}

//(a1,a2,...,b1,bn) 排序(a1,bn,a2,bn-1,...)
void NewSort(LinkList L)
{
    LNode *p = L->next, *q = p, *r;
    while (q)
    {
        p = p->next;
        q = q->next->next;
    }
    q = p->next;
    p->next = NULL;
    while (q)
    {
        r = q->next;
        q->next = p->next;
        p->next = q;
        q = r;
    }
    q = p->next;
    p->next = NULL;
    p = L->next;
    while (q)
    {
        r = q->next;
        q->next = p->next;
        p->next = q;
        p = p->next->next;
        q = r;
    }
}
//递增有序，删除相同的值
void Delete_Same(LinkList L)
{
    LNode *pre = L->next, *p = pre->next, *r;
    while (p)
    {
        if (pre->data == p->data)
        {
            r = p->next;
            pre->next = p->next;
            free(p);
            p = r;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
}

//两个升序单链表合并为降序单链表
void MergeDescendList(LinkList l1, LinkList l2)
{
    LNode *p = l1->next, *q = l2->next, *r;
    l1->next = NULL;
    while (p && q)
    {
        if (p->data <= q->data)
        {
            r = p->next;
            p->next = l1->next;
            l1->next = p;
            p = r;
        }
        else
        {
            r = q->next;
            q->next = l1->next;
            l1->next = q;
            q = r;
        }
    }
    if (q)
    {
        p = q;
    }
    while (p)
    {
        r = p->next;
        p->next = l1->next;
        l1->next = p;
        p = r;
    }
}

LinkList SearchCommonList(LinkList l1, LinkList l2)
{
    LinkList l3 = (LinkList)malloc(sizeof(LNode));
    l3->next = NULL;
    LNode *p = l1->next, *q = l2->next, *r3 = l3, *r;
    while (p && q)
    {
        if (p->data == q->data)
        {
            r = p->next;
            r3->next = p;
            r3 = p;
            p = r;
            q = q->next;
        }
        else if (p->data < q->data)
        {
            p = p->next;
        }
        else
        {
            q = q->next;
        }
    }
    return l3;
}

//判断B是否是A的连续子序列
bool IsSonList(LinkList A, LinkList B)
{
    LNode *p = A->next, *q = B->next, *pre = p;
    while (p && q)
    {
        if (p->data == q->data)
        {
            p = p->next;
            q = q->next;
        }
        else
        {
            pre = pre->next;
            p = pre;
            q = B->next;
        }
    }
    if (q == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool JudgeSymmetry(DLinkList L)
{
    DNode *p = L->next, *q = L->prior;
    while (p != q && q->next != p)
    {
        if (p->data == q->data)
        {
            p = p->next;
            q = q->prior;
        }
        else
        {
            return false;
        }
    }
    return true;
}

// Locate_x(), 每次访问x, freq加1, 链表保持按访问频度递减的顺序排列
void Locate_x(LinkList L, int x)
{
    LNode *p = L->next, *pre = L;
    while (p)
    {
        if (p->data == x)
        {
            pre->next = p->next;
            p->freq++;
            break;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
    pre = L;
    while (pre->next && pre->next->freq > p->freq)
    {
        pre = pre->next;
    }
    p->next = pre->next;
    pre->next = p;
}

int SearchTail_k(LinkList L, int k)
{
    LNode *p = L->next, *q = p;
    while (k--)
    {
        q = q->next;
    }
    while (q)
    {
        p = p->next;
        q = q->next;
    }
    return p->data;
}

//保留单链表中第一次出现的结点而删除其余绝对值相等的节点
void Delete_abs_same(LinkList L, int n)
{
    LNode *p = L->next, *pre = L, *r;
    int B[n];
    for (int i = 0; i < n; i++)
    {
        B[i] = 0;
    }
    while (p)
    {
        if (B[abs(p->data)] == 0)
        {
            B[abs(p->data)] = 1;
            pre = p;
            p = p->next;
        }
        else
        {
            r = p->next;
            pre->next = p->next;
            free(p);
            p = r;
        }
    }
}

LinkList List_TailInsert()
{
    LinkList L;
    LNode *s, *r = L;
    int x, freq;
    printf("please input Linklist element : ");
    scanf("%d", &x);
    // scanf("%d",&freq);
    while (x != 9999)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        // s->freq = freq;
        r->next = s;
        r = s;
        printf("please input Linklist element : ");
        scanf("%d", &x);
        // scanf("%d",&freq);
    }
    r->next = NULL;
    return L;
}

DLinkList List_TailInsert1()
{
    DLinkList L = (DLinkList)malloc(sizeof(DNode));
    DNode *s, *r = L;
    int x;
    printf("please input DLinkList element : ");
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (DNode *)malloc(sizeof(DNode));
        s->data = x;
        s->prior = r;
        r->next = s;
        r = s;
        s->next = L;
        L->prior = s;
        printf("please input DLinkList element : ");
        scanf("%d", &x);
    }
    r->next = L;
    L->prior = r;
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
    LinkList l1 = List_TailInsert();
    PrintList(l1);
    // LocalReverse(l1);
    // PrintList(l1);
    // Delete_x1(l1, 3);
    // PrintList(l1);
    // Delete_Min(l1);
    // PrintList(l1);
    // SortList(l1);
    // PrintList(l1);
    // Delete_s_t(l1, 3, 6);
    // PrintList(l1);
    LinkList l2 = List_TailInsert(); 
    PrintList(l2);
    // PrintList(l3);
    // printf("%d\n",FindCommon(l2, l3));
    // PrintSortList(l3);
    // LinkList l2 = DiscreateA_B(l1);
    // PrintList(l1);
    // PrintList(l2);
    // NewSort(l1);
    // Delete_Same(l1);
    // LinkList l2 = List_TailInsert();
    // PrintList(l1);
    // PrintList(l2);
    // MergeDescendList(l1, l2);
    // LinkList l3 = SearchCommonList(l1, l2);
    // PrintList(l3);
    if(IsSonList(l1, l2)){
        printf("is sonlist");
    }else{
        printf("is not sonlist");
    }
    // DLinkList L = List_TailInsert1();
    // if (JudgeSymmetry(L))
    // {
    //     printf("DLinkList is symmetry");
    // }
    // else
    // {
    //     printf("is not symmetry");
    // }
    // LinkList l3 = List_TailInsert();
    // PrintList(l3);
    // Locate_x(l3, 2);
    // PrintList(l3);
    // LinkList l = List_TailInsert();
    // PrintList(l);
    // Delete_abs_same(l, 20);
    // PrintList(l);
    return 0;
}