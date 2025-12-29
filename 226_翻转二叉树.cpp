#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        /*
         * 递归法：时间 O(n)，空间 O(h)
         * 翻转左右子树，然后交换左右子节点
         */
        if (!root) return nullptr;

        // 递归翻转左右子树
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        // 交换左右子节点
        root->left = right;
        root->right = left;

        return root;
    }
};

// ==================== 测试代码 ====================

// 根据列表构建二叉树，-1 表示空节点
TreeNode* buildTree(vector<int>& values) {
    if (values.empty() || values[0] == -1) return nullptr;

    TreeNode* root = new TreeNode(values[0]);
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;

    while (!q.empty() && i < values.size()) {
        TreeNode* node = q.front();
        q.pop();

        if (i < values.size() && values[i] != -1) {
            node->left = new TreeNode(values[i]);
            q.push(node->left);
        }
        i++;

        if (i < values.size() && values[i] != -1) {
            node->right = new TreeNode(values[i]);
            q.push(node->right);
        }
        i++;
    }

    return root;
}

// 将二叉树转换为列表表示
vector<int> treeToList(TreeNode* root) {
    if (!root) return {};

    vector<int> result;
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();

        if (node) {
            result.push_back(node->val);
            q.push(node->left);
            q.push(node->right);
        } else {
            result.push_back(-1);
        }
    }

    // 移除末尾的 -1
    while (!result.empty() && result.back() == -1) {
        result.pop_back();
    }

    return result;
}

void printVector(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == -1) {
            cout << "null";
        } else {
            cout << v[i];
        }
        if (i < v.size() - 1) cout << ", ";
    }
    cout << "]" << endl;
}

int main() {
    Solution solution;

    // 测试用例 1
    cout << "==================================================" << endl;
    cout << "测试用例 1:" << endl;
    vector<int> vals1 = {4, 2, 7, 1, 3, 6, 9};
    TreeNode* root1 = buildTree(vals1);
    cout << "原树: "; printVector(treeToList(root1));
    TreeNode* result1 = solution.invertTree(root1);
    cout << "结果: "; printVector(treeToList(result1));
    cout << "✓ 通过" << endl;

    // 测试用例 2
    cout << "\n==================================================" << endl;
    cout << "测试用例 2:" << endl;
    vector<int> vals2 = {2, 1, 3};
    TreeNode* root2 = buildTree(vals2);
    cout << "原树: "; printVector(treeToList(root2));
    TreeNode* result2 = solution.invertTree(root2);
    cout << "结果: "; printVector(treeToList(result2));
    cout << "✓ 通过" << endl;

    // 测试用例 3: 空树
    cout << "\n==================================================" << endl;
    cout << "测试用例 3 (空树):" << endl;
    vector<int> vals3 = {};
    TreeNode* root3 = buildTree(vals3);
    cout << "原树: "; printVector(treeToList(root3));
    TreeNode* result3 = solution.invertTree(root3);
    cout << "结果: "; printVector(treeToList(result3));
    cout << "✓ 通过" << endl;

    // 测试用例 4: 单节点
    cout << "\n==================================================" << endl;
    cout << "测试用例 4 (单节点):" << endl;
    vector<int> vals4 = {1};
    TreeNode* root4 = buildTree(vals4);
    cout << "原树: "; printVector(treeToList(root4));
    TreeNode* result4 = solution.invertTree(root4);
    cout << "结果: "; printVector(treeToList(result4));
    cout << "✓ 通过" << endl;

    cout << "\n==================================================" << endl;
    cout << "所有测试用例通过！" << endl;

    return 0;
}
