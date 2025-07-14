#include <vector>
#include <stack>


namespace Leetcode 
{
    struct TreeNode
    {
        int val;
        TreeNode *left, *right;
        TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
    };

    void DfsRecursiveTree(TreeNode* root)
    {
        if (root == nullptr)
            return;
        
        // post order traversal 
        DfsRecursiveTree(root->left);
        DfsRecursiveTree(root->right);
    }

    void DfsIterativeTree(TreeNode* root)
    {
        if (!root)
            return;
        
        std::stack<TreeNode*> stack;
        stack.push(root);

        while(!stack.empty())
        {
            TreeNode* curr = stack.top();
            stack.pop();
            // i can process the element
            if (curr->right)
                stack.push(curr->right);
            if (curr->left)
                stack.push(curr->left);
        }
    }

    void DfsRecursiveGraph()
    {
        
    }
}