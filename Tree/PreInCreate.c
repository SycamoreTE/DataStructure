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

} BiTNode, *BiTree;

BiTree PreInCreate(ElemType Pre[], ElemType In[], int l1, int h1, int l2, int h2){
    BiTNode *root = (BiTNode*)malloc(sizeof(BiTNode));
    root->data = Pre[l1];
    int i;
    for(i = l2; In[i] != root->data; i++);
    int llen = i - l2;
    int rlen = h2 - i;
    if(llen){
        root->lchild = PreInCreate(Pre, In, l1+1, l1+llen , l2, l2+llen-1);
    }else{
        root->lchild = NULL;
    }
    if(rlen){
        root->rchild = PreInCreate(Pre, In, h1-rlen+1, h1, h2-rlen+1, h2);
    }else{
        root->rchild = NULL;
    }
    return root;
}

void visit(BiTNode *node) {
    printf("%d-->\t", node->data);
}

void PreOrder(BiTree Tree){
    if(Tree){
        visit(Tree);
        PreOrder(Tree->lchild);
        PreOrder(Tree->rchild);
    }
}

void InOrder(BiTree Tree){
    if(Tree){
        InOrder(Tree->lchild);
        visit(Tree);
        InOrder(Tree->rchild);
    }
}

//计算双分支结点的个数
int CountNodes(BiTree Tree){
    if(!Tree){
        return 0;
    }else if(Tree->lchild && Tree->rchild){
        return CountNodes(Tree->lchild) + CountNodes(Tree->rchild) + 1;
    }else{
        return CountNodes(Tree->lchild) + CountNodes(Tree->rchild);
    }
}

//交换左右子树
void swap(BiTree T){
    if(T){
        BiTNode *temp = T->lchild;
        T->lchild = T->rchild;
        T->rchild = temp;
        swap(T->lchild);
        swap(T->rchild);
    }
}

//求先序遍历序列第k个结点的值
static int count = 1;
ElemType PreNode(BiTree Tree, int k){
    if(count == k){
        return Tree->data;
    }
    count++;
    ElemType ch = PreNode(Tree->lchild, k);
    if(ch != '#'){
        return ch;
    }
    ch = PreNode(Tree->rchild, k);
    return ch;
} 

int main(){
    int Pre[6] = {1,2,4,5,3,6};
    int In[6] = {4,2,5,1,6,3};
    BiTree tree = PreInCreate(Pre, In, 0, 5, 0, 5);
    printf("---------------------PreOrder\n");
    PreOrder(tree);
    printf("\n---------------------InOrder\n");
    InOrder(tree);
    printf("\n----------------------CountNodes\n");
    printf("Count Nodes : %d",CountNodes(tree));
    swap(tree);
    printf("\n----------swap--tree-----------PreOrder\n");
    PreOrder(tree);
    printf("\n------------------------Find Kth Data");
    printf("\nPreNode : %d",PreNode(tree, 2));
    return 0;
}