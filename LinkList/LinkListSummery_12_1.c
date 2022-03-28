#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ElemType int

typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

/** 1 删除不带头结点的单链表所有值为x的元素**/
bool Delete_x(LinkList L, int x)
{
    if (L == NULL)
    {
        return false;
    }
    LNode *p = L, *pre = p, *r;
    while (p)
    {
        r = p->next;
        if (p->data == x)
        {
            pre->next = p->next;
            p = r;
        }
        else
        {
            pre = p;
            p = p->next;
        }
    }
    return true;
}

/** 1 递归算法删除不带头结点的单链表所有值为x的元素**/
void Delete_x_recursion(LinkList L, int x)
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
        Delete_x_recursion(L, x);
    }
    else
    {
        Delete_x_recursion(L->next, x);
    }
}

/** 3 就地逆置链表**/
void ReverseList(LinkList L)
{
    LNode *p = L->next, *r;
    L->next = NULL;
    while (p)
    {
        r = p->next;
        p->next = L->next;
        L->next = p;
        p = r;
    }
}

/** 4 删除链表中最小值结点 **/
void Delete_Min(LinkList L)
{
    LNode *pre = L, *minpre = pre, *p = L->next, *minp = p;
    while (p)
    {
        if (p->data < minp->data)
        {
            minp = p;
            minpre = pre;
        }
        pre = p;
        p = p->next;
    }
    minpre->next = minp->next;
    free(minp);
}

/** 5 使单链表元素递增有序 **/
void SortList(LinkList L)
{
    LNode *p = L->next, *pre, *q = p->next, *r;
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

/** 6 删除所有介于定值s与t之间的元素值 **/
void Delete_s_t(LinkList L, int s, int t)
{
    LNode *p = L->next, *pre = L, *r;
    while (p)
    {
        r = p->next;
        if (p->data > s && p->data < t)
        {
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

/** 7 找出两个链表的公共节点 **/
int SearchCommonElement(LinkList A, LinkList B)
{
    int length1 = 0, length2 = 0, diff;
    LinkList longlist = (LinkList)malloc(sizeof(LinkList));
    LinkList shortlist = (LinkList)malloc(sizeof(LinkList));
    LNode *p = A->next, *q = B->next;
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
    if (length1 >= length2)
    {
        longlist = A->next;
        shortlist = B->next;
        diff = length1 - length2;
    }
    else
    {
        longlist = B->next;
        shortlist = A->next;
        diff = length2 - length1;
    }
    while (diff != 0)
    {
        longlist = longlist->next;
        diff--;
    }
    while (longlist)
    {
        if (longlist->data == shortlist->data)
        {
            return longlist->data;
        }
        longlist = longlist->next;
        shortlist = shortlist->next;
    }
    return -1;
}

/** 8 按递增顺序输出单链表中元素，并释放节点所占空间**/
void SortPrintList(LinkList L)
{
    LNode *p = L->next, *q = p->next, *pre, *r;
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
    p = L->next;
    while (p)
    {
        r = p->next;
        printf("%d\t", p->data);
        free(p);
        p = NULL;
        p = r;
    }
    free(L);
    L = NULL;
}

/** 10 将带头结点的单链表A分解成带头结点的A和B,
 * A表含有序号为奇数的元素，B表含偶数序号的元素 **/
LinkList DisCreate_A(LinkList A)
{
    LinkList B = (LinkList)malloc(sizeof(LinkList));
    LNode *p = A->next, *q;
    A->next = NULL;
    B->next = NULL;
    LNode *ra = A, *rb = B;
    int count = 0;
    while (p)
    {
        q = p->next;
        count++;
        if (count % 2 != 0)
        {
            ra->next = p;
            ra = p;
        }
        else
        {
            rb->next = p;
            rb = p;
        }
        p = q;
    }
    ra->next = NULL;
    rb->next = NULL;
    return B;
}

/** 11 将带头结点的单链表C(a1,b1,a2,b2,...,an,bn)就地拆分成A(a1,a2,...,an)
       和 B(bn,...,b2,b1)**/
LinkList DisCreate_C(LinkList A)
{
    LinkList B = (LinkList)malloc(sizeof(LinkList));
    LNode *p = A->next, *q;
    A->next = NULL;
    B->next = NULL;
    LNode *ra = A;
    int count = 0;
    while (p)
    {
        q = p->next;
        count++;
        if (count % 2 != 0)
        {
            ra->next = p;
            ra = p;
        }
        else
        {
            p->next = B->next;
            B->next = p;
        }
        p = q;
    }
    ra->next = NULL;
    return B;
}

/** 12 在递增有序的线性表中，去除数值相同的元素，使表中元素不重复**/
void Delete_Same(LinkList L){
    LNode *p = L->next, *q;
    if(p == NULL){
        return;
    }
    while(p){
        q = p->next;
        if(p->data == q->data){
            p->next = q->next;
            free(q);
        }else{
            p = p->next;
        }
    }

}

/** 13 将两个升序的单链表合并为一个降序的单链表 **/
void MergeDescendList(LinkList L1, LinkList L2)
{
    LNode *p = L1->next, *q = L2->next, *r;
    L1->next = NULL;
    while (p && q)
    {
        if (p->data <= q->data)
        {
            r = p->next;
            p->next = L1->next;
            L1->next = p;
            p = r;
        }
        else
        {
            r = q->next;
            q->next = L2->next;
            L2->next = q;
            q = r;
        }
    }
    while (p)
    {
        r = p->next;
        p->next = L1->next;
        L1->next = p;
        p = r;
    }
    while (q)
    {
        r = q->next;
        q->next = L1->next;
        L1->next = q;
        q = r;
    }
}

/** 14 从升序的单链表A B中找出共同的元素生成单链表C**/
LinkList FindCommon(LinkList A, LinkList B)
{
    LinkList C = (LinkList)malloc(sizeof(LinkList));
    LNode *rc = C, *p = A->next, *q = B->next, *r;
    while (p && q)
    {
        if (p->data < q->data)
        {
            p = p->next;
        }
        else if (p->data == q->data)
        {
            r = p->next;
            rc->next = p;
            rc = p;
            p = r;
            q = q->next;
        }
        else
        {
            q = q->next;
        }
    }
    rc->next = NULL;
    return C;
}

/** 15 A B 两集合元素递增排序，找到交集，并存放在A链表中**/
void Union(LinkList A, LinkList B)
{
    LNode *p = A->next, *q = B->next, *ra = A, *r;
    A->next = NULL;
    while (p && q)
    {
        if (p->data < q->data)
        {
            p = p->next;
        }
        else if (p->data > q->data)
        {
            q = q->next;
        }
        else
        {
            r = p->next;
            ra->next = p;
            ra = p;
            p = r;
            q = q->next;
        }
    }
    ra->next = NULL;
}

/** 16 判断序列B是否是A的连续子序列 **/
bool IsSonList(LinkList A, LinkList B)
{
    LNode *p = A->next, *q = B->next, *pre = p;
    while (p && p->data != q->data)
    {
        p = p->next;
        pre = p;
    }
    if (p == NULL)
    {
        return false;
    }
    while (p && q)
    {
        if (p->data == q->data)
        {
            p = p->next;
            q = q->next;
        }
        else
        {
            q = B->next;
            pre = pre->next;
            p = pre;
            while (p && p->data != q->data)
            {
                p = p->next;
                pre = p;
            }
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

bool IsSonList2(LinkList A, LinkList B)
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
/*****************************************************/

/**17 判断带头结点的双链表是否对称**/

/**21
 * 带表头结点的单链表，查找链表倒数第k个位置上的结点，查找成功输出data域的值，并返回1，否则返回0
 * **/
int SearchTail_k(LinkList L, int k)
{
    LNode *p = L->next, *q = p;
    while (k--)
    {
        p = p->next;
    }
    if (p == NULL)
    {
        return 0;
    }
    while (p)
    {
        p = p->next;
        q = q->next;
    }
    if (q)
    {
        printf("the bottom kth element: %d", q->data);
        return 1;
    }
    else
    {
        return 0;
    }
}

/** 22 找出由str1 和 str2 所指向两个链表共同后缀的起始位置**/
int FindCommon_first_element(LinkList A, LinkList B)
{
    LNode *p = A->next, *q = B->next;
    LinkList longlist, shortlist;
    int length1 = 0, length2 = 0, dist;
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
    if (length1 >= length2)
    {
        dist = length1 - length2;
        longlist = A;
        shortlist = B;
    }
    else
    {
        dist = length2 - length1;
        longlist = B;
        shortlist = A;
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
        else
        {
            p = p->next;
            q = q->next;
        }
    }
    return -1;
}

/**23 对单链表中data绝对值相等的结点，仅保留第一次出现的结点，删除其他结点**/
void Delete_abs_same(LinkList L, int n)
{
    int *b = (int *)malloc(sizeof(int) * n);
    memset(b, 0, sizeof(int) * n);
    LNode *p = L->next, *pre = L, *q;
    while (p)
    {
        if (b[abs(p->data)] == 0)
        {
            b[abs(p->data)]++;
            pre = p;
            p = p->next;
        }
        else
        {
            q = p->next;
            pre->next = p->next;
            free(p);
            p = q;
        }
    }
}

/** 25 线性表L=(a1,a2,...,an) 重新排练各结点得到L'=(a1,an,a2,an-1,...)**/
void ReSortList(LinkList L)
{
    LNode *p = L->next, *q = p, *r;
    while (q->next)
    {
        p = p->next;
        q = q->next;
        if (q->next != NULL)
        {
            q = q->next;
        }
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
        p = q->next;
        q = r;
    }
}

//头插法创建链表
LinkList List_HeadInsert()
{
    LinkList L = (LinkList)malloc(sizeof(LinkList));
    L->next = NULL;
    LNode *s;
    int x;
    printf("please input linklist element : ");
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
        printf("please input linklist element : ");
        scanf("%d", &x);
    }
    return L;
}

//尾插法创建链表
LinkList List_TailInsert()
{
    LinkList L = (LinkList)malloc(sizeof(LinkList));
    L->next = NULL;
    LNode *s, *r = L;
    int x;
    printf("please input linklist element : ");
    scanf("%d", &x);
    while (x != 9999)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
        printf("please input linklist element : ");
        scanf("%d", &x);
    }
    r->next = NULL;
    return L;
}

void Print_LinkList(LinkList L)
{
    if (L == NULL)
    {
        printf("Linklist is NULL");
        return;
    }
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
    // LinkList l1 = List_HeadInsert();
    // Print_LinkList(l1);
    // LinkList l2 = List_TailInsert();
    // Print_LinkList(l2);
    // Delete_x(l2, 3);
    // Print_LinkList(l2);
    // Delete_x_recursion(l2, 4);
    // Print_LinkList(l2);
    // ReverseList(l2);
    // Print_LinkList(l2);
    // SortList(l2);
    // Print_LinkList(l2);
    // Delete_s_t(l2, 2, 5);
    // Print_LinkList(l2);

    // LinkList list1 = List_TailInsert();
    // Print_LinkList(list1);
    // LinkList list2 = List_TailInsert();
    // Print_LinkList(list2);
    // printf("first common element : %d\n", SearchCommonElement(list1, list2));

    // SortPrintList(list1);

    // LinkList A = List_TailInsert();
    // Print_LinkList(A);
    // LinkList B = DisCreate_C(A);
    // Print_LinkList(A);
    // Print_LinkList(B);

    LinkList sam = List_TailInsert();
    Print_LinkList(sam);
    Delete_Same(sam);
    Print_LinkList(sam);

    // LinkList list1 = List_TailInsert();
    // Print_LinkList(list1);
    // LinkList list2 = List_TailInsert();
    // Print_LinkList(list2);
    // MergeDescendList(list1, list2);
    // LinkList list3 = FindCommon(list1, list2);
    // printf("%d if is SonList\n", (IsSonList(list1, list2)? 1:0));
    // printf("%d if is SonList\n", (IsSonList2(list1, list2)? 1:0));
    // // Print_LinkList(list1);
    // printf("\n%d", SearchTail_k(list1, 3));
    // printf("\nFirst common element :%d\n", FindCommon_first_element(list1,
    // list2)); Delete_abs_same(list1, 10); Print_LinkList(list1);

    // LinkList L = List_TailInsert();
    // Print_LinkList(L);
    // ReSortList(L);
    // Print_LinkList(L);
    return 0;
}