#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ElemType int
#define MaxSize 50

//定义树的链式存储结构
typedef struct BiTNode {
    struct BiTNode *lchild;
    struct BiTNode *rchild;
    ElemType data;
} BiTNode, *BiTree, *LinkList;

typedef struct ThreadNode{
    struct ThreadNode *lchild, *rchild;
    ElemType data;
    int ltag,rtag;
}ThreadNode, *ThreadTree;

void PreToPost(int Pre[],int Post[],int l1, int h1,int l2, int h2){
    int half;
    if(h1 >= l1){
        Post[h2] = Pre[l1];
        half = (h1 - l1)/2;
        PreToPost(Pre, Post, l1+1, l1+half, l2, l2+half-1);
        PreToPost(Pre, Post, l1+half+1, h1, l2+half, h2-1);
    }
}

//将二叉树的叶节点按从左到右的顺序连成单链表；
//表头指针为head，按二叉链表方式存储，用右指针链接叶子节点
LinkList head, pre = NULL;
LinkList InOrder(BiTree Tree){
    if(Tree){
        InOrder(Tree->lchild);
        if(Tree->lchild == NULL && Tree->rchild == NULL){
            if(pre == NULL){
                head = Tree;
                pre = Tree;
            }else{
                pre->rchild = Tree;
                pre = Tree;
            }
        }
        InOrder(Tree->rchild);
        pre->rchild = NULL;
    }
    return head;
}

//判断两棵二叉树是否相似
int similar(BiTree T1, BiTree T2){
    int left,right;
    if(T1 == NULL && T2 == NULL){
        return 1;
    }else if(T1 == NULL || T2 == NULL){
        return 0;
    }else{
        left = similar(T1->lchild, T2->lchild);
        right = similar(T1->rchild, T2->rchild);
        return left && right;                                                                                                                               
    }
}

ThreadNode *pre1 = NULL;

void visit1(ThreadTree q){
    if(q){
        if(q->lchild == NULL){
            q->lchild = pre1;
            q->ltag = 1;
        }
        if(pre1 != NULL && pre1->rchild == NULL){
            pre1->rchild = q;
            pre1->rtag = 1;
        }
        pre1 = q;
    }
}

void InThread(ThreadTree T){
    if(T){
        InThread(T->lchild);
        if(T->lchild == NULL){
            T->ltag = 1;
            T->lchild = pre1;
        }
        if(pre1 != NULL && pre1->rchild == NULL){
            pre1->rtag = 1;
            pre1->rchild = T;
        }
        pre1 = T;
        InThread(T->rchild);
    }
}

void CreateInThread(ThreadTree T){
    if(T){
        InThread(T);
        if(pre1->rchild == NULL){
            pre1->rtag = 1;
        }
    }
}

//中序线索二叉树的指定结点 在后序的前驱节点
ThreadNode InPostPre(ThreadTree T, ThreadNode *p){
    ThreadNode *q = (ThreadNode*)malloc(sizeof(ThreadNode));
    if(p->rtag == 0){
        q = p->rchild;
    }else if(p->ltag == 0){
        q = p->lchild;
    }else if(p->lchild == NULL){
        q = NULL;
    }else{
        while(p->ltag == 1 && p->lchild != NULL){
            p = p->lchild;
        }
        if(p->ltag == 0){
            q = p->lchild;
        }else{
            q = NULL;
        }
    }
    return *q;
}

//求树的WPL
void WPL(BiTree T, int* wpl, int deep){
    if(T){
        *wpl += deep*(T->data);
        WPL(T->lchild, wpl, deep+1);
        WPL(T->rchild, wpl, deep+1);
    }
}
void InitThreadTree(ThreadTree *T){
    *T = (ThreadNode*)malloc(sizeof(ThreadNode));
    (*T)->data = 1;
    (*T)->ltag = 0;
    (*T)->rtag = 0;
    (*T)->lchild = (ThreadNode*) malloc(sizeof(ThreadNode));
    (*T)->rchild = (ThreadNode*) malloc(sizeof(ThreadNode));
    (*T)->lchild->data = 2;
    (*T)->lchild->ltag = 0;
    (*T)->lchild->rtag = 0;
    (*T)->lchild->lchild = (ThreadNode*) malloc(sizeof(ThreadNode));
    (*T)->lchild->rchild = (ThreadNode*) malloc(sizeof(ThreadNode));
    (*T)->lchild->rchild->data = 5;
    (*T)->lchild->rchild->ltag = 0;
    (*T)->lchild->rchild->rtag = 0;
    (*T)->lchild->rchild->lchild = NULL;
    (*T)->lchild->rchild->rchild = NULL;
    (*T)->rchild->data = 3;
    (*T)->rchild->ltag = 0;
    (*T)->rchild->rtag = 0;
    (*T)->rchild->lchild = (ThreadNode*) malloc(sizeof(ThreadNode));
    (*T)->rchild->lchild->data = 6;
    (*T)->rchild->lchild->ltag = 0;
    (*T)->rchild->lchild->rtag = 0;
    (*T)->rchild->lchild->lchild = NULL;
    (*T)->rchild->lchild->rchild = NULL;
    (*T)->rchild->rchild = (ThreadNode*) malloc(sizeof(ThreadNode));
    (*T)->rchild->rchild->data = 7;
    (*T)->rchild->rchild->ltag = 0;
    (*T)->rchild->rchild->rtag = 0;
    (*T)->rchild->rchild->lchild = NULL;
    (*T)->rchild->rchild->rchild = NULL;
    (*T)->lchild->lchild->data = 4;
    (*T)->lchild->lchild->ltag = 0;
    (*T)->lchild->lchild->rtag = 0;
    (*T)->lchild->lchild->lchild = NULL;
    (*T)->lchild->lchild->rchild = NULL;
}

void initTree(BiTree *T) {
    *T = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->data = 1;
    (*T)->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->data = 2;
    (*T)->lchild->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->lchild->rchild->data = 5;
    (*T)->lchild->rchild->lchild = NULL;
    (*T)->lchild->rchild->rchild = NULL;
    (*T)->rchild->data = 3;
    (*T)->rchild->lchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild->lchild->data = 6;
    (*T)->rchild->lchild->lchild = NULL;
    (*T)->rchild->lchild->rchild = NULL;
    (*T)->rchild->rchild = (BiTNode *) malloc(sizeof(BiTNode));
    (*T)->rchild->rchild->data = 7;
    (*T)->rchild->rchild->lchild = NULL;
    (*T)->rchild->rchild->rchild = NULL;
    (*T)->lchild->lchild->data = 4;
    (*T)->lchild->lchild->lchild = NULL;
    (*T)->lchild->lchild->rchild = NULL;
}

void visit2(ThreadNode *node){
    printf("%d::%d::%d-->\t",node->data,node->ltag,node->rtag);
}

void visit(BiTNode *node) {
    printf("%d-->\t", node->data);
}

void InOrder2(ThreadTree T){
    if(T){
        InOrder2(T->lchild);
        visit2(T);
        InOrder2(T->rchild);
    }
}

ThreadNode* FirstNode(ThreadNode *p){
    while(p->ltag==0){
        p = p->lchild;
    }
    return p;
}

ThreadNode* NextNode(ThreadNode *p){
    if(p->rtag == 0){
        return FirstNode(p->rchild);
    }else{
        return p->rchild;
    }
}

//中序遍历线索二叉树
void ThreadInOrder(ThreadTree T){
    for(ThreadNode *p = FirstNode(T);p != NULL; p = NextNode(p)){
        visit2(p);
    }
}

void PreOrder(LinkList head){
    while(head){
        visit(head);
        head = head->rchild;
    }
}

void PreCreateTree(ThreadTree T){
    ElemType x;
    scanf("%d",&x);
    if(x != 9999){
        T->data = x;
        T->ltag = 0;
        T->rtag = 0;
        PreCreateTree(T->lchild);
        PreCreateTree(T->rchild);
    }else{
        T = NULL;
    }
}

int main(){
    int Pre[7] = {1,2,4,5,3,6,7};
    int Post[7] = {0};
    PreToPost(Pre, Post, 0, 6, 0, 6);
    for(int i = 0; i < 7; i++){
        printf("%d\t",Post[i]);
    }
    BiTree tree;
    initTree(&tree);
    LinkList h;
    h = InOrder(tree);
    printf("\n------------------Link leaf node\n");
    PreOrder(h);
    int wpl = 0;
    WPL(tree, &wpl, 0);
    printf("\nWPL of this tree : %d",wpl);
    ThreadTree tree1;
    InitThreadTree(&tree1);
    printf("\nInit Thread Tree-----------------\n");
    InOrder2(tree1);
    CreateInThread(tree1);
    printf("\nCreate Thread--------------------\n");
    ThreadInOrder(tree1);
    return 0;
}