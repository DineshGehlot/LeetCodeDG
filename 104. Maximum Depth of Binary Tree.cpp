// Queue based (also solved by stack)
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        uint32_t depth = 0;
        queue<pair<TreeNode*, uint32_t>> q;
        q.push({root,1});

        while(!q.empty()) {
            auto ele = q.front(); q.pop();
            depth = max(ele.second, depth);
            if(ele.first->left) q.push({ele.first->left, ele.second+1});
            if(ele.first->right) q.push({ele.first->right, ele.second+1});
        }
        return depth;
    }
};

//Recursive
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(!root) return 0;
        return 1 + max(maxDepth(root->left), maxDepth(root->right));
    }
};