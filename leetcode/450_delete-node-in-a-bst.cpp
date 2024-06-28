
//  https://leetcode.com/problems/delete-node-in-a-bst/
/*
450. Delete Node in a BST
Solved
Medium

Topics
Companies
Given a root node reference of a BST and a key, delete the node with the given key in the BST. Return the root node reference (possibly updated) of the BST.

Basically, the deletion can be divided into two stages:

Search for a node to remove.
If the node is found, delete the node.


The number of nodes in the tree is in the range [0, 104].
-105 <= Node.val <= 105
Each node has a unique value.
root is a valid binary search tree.
-105 <= key <= 105
 

Follow up: Could you solve it with time complexity O(height of tree)?
*/

// a good reference with images, O(n) 
// https://leetcode.com/problems/delete-node-in-a-bst/solutions/1590789/c-shortest-recursive-solution-detailed-explanation-with-images


// 27ms, 32.06MB

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
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root) {
            if (key < root-> val) {
                root->left = deleteNode(root->left, key);
            }
            else if (key > root-> val) {
                root->right = deleteNode(root->right, key);
            } else { // found! root is to be deleted 
                if (!root->left && !root->right) {
                    return NULL; // 1 no child
                } else if (!root->left || !root->right) {
                    return (root->left) ? root->left : root->right; // 1 child, return it
                }
                // 2 children both valid, find next successor in in-order-traversal (aka greatest in left subtree or smallest in right subtree)
                TreeNode* tmp = root->left;
                while (tmp->right != NULL) {
                    tmp = tmp->right;
                }
                root->val = tmp->val;
                root->left = deleteNode(root->left, tmp->val);

                // alternatively find smallest in right subtree:
                /*
                whie (tmp->left != NULL) {
                    tmp = tmp->left;
                }
                root->val = tmp->val;
                root->right = deleteNode(root->right, tmp->val);

                */

            }
        }

        return root;
        
    }
};
