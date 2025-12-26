/**
 * 236. 二叉树的最近公共祖先
 * https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 */

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <vector>
#include <cassert>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    // 解法一：存储父节点 + 哈希表
    TreeNode* lowestCommonAncestor_hash(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode*, TreeNode*> parent;
        parent[root] = nullptr;

        // 遍历记录父节点
        stack<TreeNode*> stk;
        stk.push(root);
        while (!stk.empty()) {
            TreeNode* node = stk.top();
            stk.pop();
            if (node->left) {
                parent[node->left] = node;
                stk.push(node->left);
            }
            if (node->right) {
                parent[node->right] = node;
                stk.push(node->right);
            }
        }

        // 记录 p 的所有祖先
        unordered_set<TreeNode*> ancestors;
        TreeNode* curr = p;
        while (curr) {
            ancestors.insert(curr);
            curr = parent[curr];
        }

        // 找 q 的第一个在 p 祖先中的节点
        curr = q;
        while (ancestors.find(curr) == ancestors.end()) {
            curr = parent[curr];
        }

        return curr;
    }

    // 解法二：递归（最优解）
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // 递归终止条件
        if (!root || root == p || root == q) {
            return root;
        }

        // 在左右子树中查找
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // 如果左右都找到了，当前节点是 LCA
        if (left && right) {
            return root;
        }

        // 否则返回非空的那个
        return left ? left : right;
    }
};

// 辅助函数：从数组构建二叉树
pair<TreeNode*, unordered_map<int, TreeNode*>> buildTree(vector<int> values) {
    unordered_map<int, TreeNode*> nodes;
    if (values.empty()) return {nullptr, nodes};

    TreeNode* root = new TreeNode(values[0]);
    nodes[values[0]] = root;
    queue<TreeNode*> q;
    q.push(root);
    int i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* node = q.front();
        q.pop();

        // 左子节点 (用 INT_MIN 表示 null)
        if (i < values.size() && values[i] != INT_MIN) {
            node->left = new TreeNode(values[i]);
            nodes[values[i]] = node->left;
            q.push(node->left);
        }
        i++;

        // 右子节点
        if (i < values.size() && values[i] != INT_MIN) {
            node->right = new TreeNode(values[i]);
            nodes[values[i]] = node->right;
            q.push(node->right);
        }
        i++;
    }

    return {root, nodes};
}

// 释放树内存
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Solution solution;

    // 测试用例 1: p=5, q=1, LCA=3
    auto [root1, nodes1] = buildTree({3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4});
    TreeNode* p1 = nodes1[5];
    TreeNode* q1 = nodes1[1];
    TreeNode* result1 = solution.lowestCommonAncestor(root1, p1, q1);
    assert(result1->val == 3);
    cout << "✓ 测试1通过: p=5, q=1, LCA=" << result1->val << endl;

    // 测试用例 2: p=5, q=4, LCA=5
    auto [root2, nodes2] = buildTree({3, 5, 1, 6, 2, 0, 8, INT_MIN, INT_MIN, 7, 4});
    TreeNode* p2 = nodes2[5];
    TreeNode* q2 = nodes2[4];
    TreeNode* result2 = solution.lowestCommonAncestor(root2, p2, q2);
    assert(result2->val == 5);
    cout << "✓ 测试2通过: p=5, q=4, LCA=" << result2->val << endl;

    // 测试用例 3: p=1, q=2, LCA=1
    auto [root3, nodes3] = buildTree({1, 2});
    TreeNode* p3 = nodes3[1];
    TreeNode* q3 = nodes3[2];
    TreeNode* result3 = solution.lowestCommonAncestor(root3, p3, q3);
    assert(result3->val == 1);
    cout << "✓ 测试3通过: p=1, q=2, LCA=" << result3->val << endl;

    // 测试解法一（哈希表）
    TreeNode* result1_hash = solution.lowestCommonAncestor_hash(root1, p1, q1);
    assert(result1_hash->val == 3);
    cout << "✓ 哈希表解法测试通过" << endl;

    // 清理内存
    deleteTree(root1);
    deleteTree(root2);
    deleteTree(root3);

    cout << "\n所有测试通过！" << endl;
    return 0;
}
