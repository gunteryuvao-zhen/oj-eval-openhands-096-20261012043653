#include <iostream>
#include <vector>
#include <unordered_map>
#include <sstream>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    std::unordered_map<int, int> depth;  // value -> depth
    std::unordered_map<int, int> parent; // value -> parent value

    // Build tree from preorder traversal and record depth and parent information
    TreeNode* buildTree(std::vector<int>& preorder, int& index, int currentDepth, int parentVal) {
        if (index >= preorder.size() || preorder[index] == -1) {
            index++;
            return nullptr;
        }
        
        int val = preorder[index++];
        TreeNode* node = new TreeNode(val);
        
        // Record depth and parent information
        depth[val] = currentDepth;
        parent[val] = parentVal;
        
        // Build left and right subtrees
        node->left = buildTree(preorder, index, currentDepth + 1, val);
        node->right = buildTree(preorder, index, currentDepth + 1, val);
        
        return node;
    }
    
    // Clean up memory
    void deleteTree(TreeNode* root) {
        if (root) {
            deleteTree(root->left);
            deleteTree(root->right);
            delete root;
        }
    }
    
public:
    // Public method to build the tree and record information
    void buildTreeAndRecord(std::vector<int>& preorder) {
        int index = 0;
        TreeNode* root = buildTree(preorder, index, 0, -1);
        deleteTree(root); // Clean up the tree, we only need the depth and parent maps
    }
    
    int isCousins(int x, int y) {
        // Check if nodes are at the same depth and have different parents
        if (depth.find(x) != depth.end() && depth.find(y) != depth.end()) {
            return (depth[x] == depth[y] && parent[x] != parent[y]) ? 1 : 0;
        }
        return 0; // If either node doesn't exist
    }
};

int main() {
    Solution solution;
    std::vector<int> preorder;
    int n;
    
    // Read number of queries
    std::cin >> n;
    
    // Read queries
    std::vector<std::pair<int, int>> queries(n);
    for (int i = 0; i < n; i++) {
        std::cin >> queries[i].first >> queries[i].second;
    }
    
    // Read preorder traversal
    int val;
    while (std::cin >> val) {
        preorder.push_back(val);
    }
    
    // Build tree and record depth and parent information
    solution.buildTreeAndRecord(preorder);
    
    // Process queries
    for (int i = 0; i < n; i++) {
        std::cout << solution.isCousins(queries[i].first, queries[i].second) << std::endl;
    }
    
    return 0;
}