//
// Created by 安炳旭 on 2020-05-12.
//

#include <cstdio>
#include <algorithm>
using namespace std;
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
int TreeDepth(TreeNode* pRoot)
{
    if(pRoot == NULL){//根结点为空深度为0返回
        return 0;
    }
    return 1+max(TreeDepth(pRoot->right),TreeDepth(pRoot->left)); //此时根结点一定不为空，故深度至少为1，然后计算左子树和右字数的深度，选择最大的加起来则为整个树的深度
}