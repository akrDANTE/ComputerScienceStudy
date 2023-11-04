#include <iostream>
#include <stack>
#include <unordered_set>

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

int kthSmallest(TreeNode *root, int k)
{
    stack<TreeNode *> s;
    unordered_set<TreeNode *> visited;
    s.push(root);
    int index = 0;
    while (!s.empty())
    {
        TreeNode *curr = s.top();
        if (curr->right && visited.find(curr->right) == visited.end())
        {
            s.pop();
            s.push(curr->right);
            s.push(curr);
        }
        if (curr->left && visited.find(curr->left) == visited.end())
        {
            s.push(curr->left);
        }
        else
        {
            visited.insert(curr);
            index++;
            if (index == k)
            {
                return curr->val;
            }
            s.pop();
        }
    }
    return -1;
}

int main()
{
    TreeNode tree(4);
    TreeNode node(1);
    TreeNode node2(2);
    TreeNode node3(3);
    TreeNode node4(5);

    node.right = &node2;

    kthSmallest(&node, 2);

    return 0;
}