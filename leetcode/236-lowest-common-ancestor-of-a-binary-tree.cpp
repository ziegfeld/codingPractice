

// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/


#include <tuple>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
//work in progress
    std::tuple<short, int> try1(TreeNode* root, const int& p, const int& q) {
        int val = root->val;
        short ret = val == q;
        // LSB 0x1 means q found; LSB<<1 (bit1,, 0x2) means p found. 0x5 means
        // all found so just return the answer (*val).
        ret |= (val == p) << 1;
        // TODO optimize: p or q already found then don't need to even pass into
        // next layer. use std::optional!
        if (root->left) {
            short retl;
            [ retl, val ] = try1(root->left, p, q);
            ret |= retl;
        }

        if (ret == 0x3 || ret == 0x5) {
            return {5, val};
        }
        if (root->right) {
            short retr;
            [ retr, val ] = try1(root->left, p, q);
            ret |= retr;
        }
        if (ret == 0x3 || ret == 0x5) {
            return {5, val};
        } else {
            return {ret, val};
        }
    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 674250813 -
        auto [flag, answer] = try1(root, p->val, q->val);
        return (5 == flag) ? answer : -1; // -1 == throw error!
    }

    /* native recursion, passed

        TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
    {
        // just need a traveral where parent is visited last.
        if (root == nullptr || root == p || root == q) {
            return root;
        }
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        if (left && right)
            return root;
        // if p or q in this left sub-tree, then return; other wise it(or both)
    must be in right sub-tree return left ? left : right;
    }
    */
};
