/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // Create a hashmap to store the indices of elements in the inorder traversal
        unordered_map<int, int> map;
        for (int i = 0; i < inorder.size(); i++) {
            map[inorder[i]] = i;
        }
        
        // Initialize the index variable to track the current position in the preorder traversal
        int index = 0;
        
        // Call the recursive construct function to build the binary tree
        return construct(preorder, map, index, 0, inorder.size() - 1);
    }

private:
    TreeNode* construct(vector<int>& preorder, unordered_map<int, int>& map, int& index, int i, int j) {
        // Base case: If the start index exceeds the end index, return NULL (indicating a null subtree)
        if (i > j) {
            return NULL;
        }
        
        // Create a new TreeNode with the value from the preorder traversal at the current index
        TreeNode* root = new TreeNode(preorder[index++]);
        
        // Find the index of the root value in the inorder traversal
        int mid = map[root->val];
        
        // Recursively build the left subtree with elements to the left of the root in the inorder traversal
        root->left = construct(preorder, map, index, i, mid - 1);
        
        // Recursively build the right subtree with elements to the right of the root in the inorder traversal
        root->right = construct(preorder, map, index, mid + 1, j);
        
        // Return the constructed root node
        return root;
    }
};
