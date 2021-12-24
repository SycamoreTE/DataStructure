#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//二叉排序树
 
typedef struct BSTNode
{
	int data;
	struct BSTNode *lchild;  //左孩子
	struct BSTNode *rchild;  //右孩子
}BSTNode, *BSTree;
 
bool Search(BSTree bst, int key, BSTree f, BSTree *p);
 
void InOderTraverse(BSTree bst)   //中序递归遍历二叉树
{
	if (NULL != bst)
	{
		InOderTraverse(bst->lchild);
		printf("%d ", bst->data);
		InOderTraverse(bst->rchild);
	}
}
 
static BSTNode* BuyNode(int data)   //生成一个节点并进行初始化
{
	BSTNode *pTmp = (BSTNode*)malloc(sizeof(BSTNode));
	if (NULL == pTmp)
	{
		exit(0);
	}
	pTmp->data = data;
	pTmp->lchild = NULL;
	pTmp->rchild = NULL;
	return pTmp;
}
 
bool Insert(BSTree *bst, int key)
{
	if (NULL == *bst)  //空树
	{
		*bst = BuyNode(key);   //插入根节点
		return true;
	}
	BSTNode *p;
	//先在二叉排序树中查找要插入的值是否已经存在
	if (!Search(*bst, key, NULL, &p))  //如果查找失败，则插入；此时p指向遍历的最后一个节点
	{
		BSTNode *pNew = BuyNode(key);
		if (key < p->data)  //将s作为p的左孩子
		{
			p->lchild = pNew;
		}
		else if (key > p->data)  //将s作为p的右孩子
		{
			p->rchild = pNew;
		}
		return true;  //插入成功
	}
	else
	{
		printf("\nThe node(%d) already exists.\n", key);
	}
	return false;
}
 
/*
删除分三种情况：
(1)被删除的节点无孩子，说明该节点是叶子节点，直接删
(2)被删除的节点只有左孩子或者右孩子，直接删，并将其左孩子或者右孩子放在被删节点的位置
(3)被删除的节点既有右孩子又有右孩子
*/
 
BSTNode* FindParent(BSTree bst, BSTNode *child)
{
	if (NULL == bst)
	{
		return NULL;
	}
 
	if (bst->lchild == child || bst->rchild == child)
	{
		return bst;
	}
	else if(NULL != bst->lchild)
	{
		FindParent(bst->lchild, child);
	}
	else if (NULL != bst->rchild)
	{
		FindParent(bst->rchild, child);
	}
}
 
void Delete(BSTree *bst, int key)
{
	if (NULL == *bst)
	{
		exit(1);  //空树直接报错
	}
	BSTNode *p;
	BSTNode *f = NULL;
	BSTNode *q, *s;
	if (Search(*bst, key, NULL, &p)) //确实存在值为key的节点,则p指向该节点
	{
 
		if (NULL == p->lchild && NULL != p->rchild)  //无左孩子,有右孩子
		{
			q = p->rchild;
			p->data = q->data;    //因为两个节点之间本质的不同在于数据域的不同，而与放在哪个地址没有关系
			p->rchild = q->rchild;
			p->lchild = q->lchild;
			free(q);
		}
		else if (NULL == p->rchild && NULL != p->lchild)  //无右孩子,有左孩子
		{
			q = p->lchild;
			p->data = q->data;
			p->rchild = q->rchild;
			p->lchild = q->lchild;
			free(q);
		}
		else if (NULL != p->rchild && NULL != p->lchild) //既有左孩子，又有右孩子
		{
			q = p;
			s = p->lchild;   //找左孩子的最右孩子
			while (s->rchild)
			{
				q = s;
				s = s->rchild;
			}
			p->data = s->data;
 
			if (q != p)
			{
				q->rchild = p->lchild;
			}
			else
			{
				q->lchild = s->lchild;
			}
			free(s);
		}
		else
		{
			if (*bst == p)   //只有一个根节点
			{
				free(*bst);
				*bst = NULL;
				return;
			}
 
			BSTNode* parent = FindParent(*bst, p);
			if (parent->lchild == p)
			{
				parent->lchild = NULL;
			}
			else
			{
				parent->rchild = NULL;
			}
			free(p);
		}
	}
}
 
bool Search(BSTree bst, int key, BSTree f, BSTree *p)  //查找成功时，p指向值为key的节点。如果查找失败，则p指向遍历的最后一个节点
{
	if (!bst)
	{
		*p = f;
		return false;
	}
	if (bst->data == key)  //查找成功，直接返回
	{
		*p = bst;
		return true;
	}
	else if (bst->data < key)
	{
		return Search(bst->rchild, key, bst, p);
	}
	return Search(bst->lchild, key, bst, p);
}
 
int main(void)
{
	BSTNode *root = NULL;
	Insert(&root, 45);
	Insert(&root, 24);
	Insert(&root, 53);
	Insert(&root, 12);
	Insert(&root, 90);
	InOderTraverse(root);
	printf("\n%d ", Insert(&root, 45));   //输出0表示插入失败，输出1表示插入成功
	printf("%d\n", Insert(&root, 4));
	InOderTraverse(root);
	printf("\n");
	Delete(&root, 4);      //删除节点45
	Delete(&root, 45);      //删除节点45
	Delete(&root, 24);      //删除节点45
	Delete(&root, 53);      //删除节点45
	Delete(&root, 12);      //删除节点45
	Delete(&root, 90);      //删除节点45
	InOderTraverse(root);
	return 0;
}