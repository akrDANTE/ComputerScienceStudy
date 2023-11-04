#include <iostream>
#include <queue>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

int widthOfBinaryTree(TreeNode *root)
{
    int ans = 0;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty())
    {
        int len = q.size();
        int width = 0;
        int null_cnt = 0;
        for (int i = 0; i < len; i++)
        {
            TreeNode *curr = q.front();
            q.pop();
            if (curr)
            {
                width += 1 + null_cnt;
                null_cnt = 0;
                q.push(curr->left);
                q.push(curr->right);
            }
            else
            {
                null_cnt++;
                q.push(curr);
                q.push(curr);
            }
        }
        ans = max(ans, width);
    }
    return ans;
}

int main()
{
    TreeNode node1(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(4);
    TreeNode node5(5);
    TreeNode node6(6);
    TreeNode node7(7);
    TreeNode node8(8);
    TreeNode node9(9);
    node1.left = &node3;
    node2.right = &node2;
    node3.left = &node5;
    node2.right = &node9;
    node5.left = &node6;
    node9.left = &node7;

    cout << widthOfBinaryTree(&node1);
    return 0;
}