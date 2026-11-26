class Solution {
public:
    unordered_map<int, int> mp;
    int idx = 0;

    TreeNode* solve(vector<int>& preorder, int start, int end) {
        if (start > end) {
            return NULL;
        }

        int rootVal = preorder[idx++];
        TreeNode* root = new TreeNode(rootVal);

        int pos = mp[rootVal];

        root->left = solve(preorder, start, pos - 1);
        root->right = solve(preorder, pos + 1, end);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        for (int i = 0; i < inorder.size(); i++) {
            mp[inorder[i]] = i;
        }

        return solve(preorder, 0, inorder.size() - 1);
    }
};
