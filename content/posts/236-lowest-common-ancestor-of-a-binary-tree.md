---
title: "236. 二叉树的最近公共祖先"
difficulty: "中等"
description: "给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。"
---

# 236. 二叉树的最近公共祖先

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为："对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。"

## 示例

<Mermaid>
graph TD
    A((3)) --> B((5))
    A --> C((1))
    B --> D((6))
    B --> E((2))
    C --> F((0))
    C --> G((8))
    E --> H((7))
    E --> I((4))
    style B fill:#90EE90
    style C fill:#90EE90
    style A fill:#FFD700
</Mermaid>

**示例 1：**
```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3。
```

**示例 2：**
```
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
```

**示例 3：**
```
输入：root = [1,2], p = 1, q = 2
输出：1
```

## 提示

- 树中节点数目在范围 `[2, 10^5]` 内。
- `-10^9 <= Node.val <= 10^9`
- 所有 `Node.val` 互不相同。
- `p != q`
- `p` 和 `q` 均存在于给定的二叉树中。

---

## 解法一：存储父节点 + 哈希表

### 思路

1. 遍历整棵树，用哈希表记录每个节点的父节点
2. 从 p 节点开始，向上遍历到根节点，将路径上的所有节点存入集合
3. 从 q 节点开始向上遍历，第一个出现在集合中的节点就是最近公共祖先

### Python 实现

```python
class TreeNode:
    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        parent = {root: None}

        # BFS 记录所有节点的父节点
        stack = [root]
        while stack:
            node = stack.pop()
            if node.left:
                parent[node.left] = node
                stack.append(node.left)
            if node.right:
                parent[node.right] = node
                stack.append(node.right)

        # 记录 p 到根节点的路径
        ancestors = set()
        while p:
            ancestors.add(p)
            p = parent[p]

        # 找 q 的祖先中第一个在 p 路径上的节点
        while q not in ancestors:
            q = parent[q]

        return q
```

### C++ 实现

```cpp
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
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
        while (p) {
            ancestors.insert(p);
            p = parent[p];
        }

        // 找 q 的第一个在 p 祖先中的节点
        while (ancestors.find(q) == ancestors.end()) {
            q = parent[q];
        }

        return q;
    }
};
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(n)，遍历所有节点 |
| 空间复杂度 | O(n)，存储父节点哈希表 |

---

## 解法二：递归（最优解）

### 思路

利用递归的特性：

1. 如果当前节点为空，或等于 p 或 q，直接返回当前节点
2. 递归搜索左右子树
3. 根据左右子树的返回值判断：
   - 左右都不为空：说明 p、q 分别在左右子树，当前节点就是 LCA
   - 只有一边不为空：LCA 在那一边
   - 都为空：当前子树不包含 p 或 q

### Python 实现

```python
class Solution:
    def lowestCommonAncestor(self, root: 'TreeNode', p: 'TreeNode', q: 'TreeNode') -> 'TreeNode':
        # 递归终止条件
        if not root or root == p or root == q:
            return root

        # 在左右子树中查找
        left = self.lowestCommonAncestor(root.left, p, q)
        right = self.lowestCommonAncestor(root.right, p, q)

        # 如果左右都找到了，说明当前节点是 LCA
        if left and right:
            return root

        # 否则返回非空的那个
        return left if left else right
```

### C++ 实现

```cpp
class Solution {
public:
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
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(n)，最坏情况遍历所有节点 |
| 空间复杂度 | O(n)，递归栈深度（最坏为链表） |

---

## 解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 存储父节点 | O(n) | O(n) | 直观，需要额外哈希表 |
| 递归 | O(n) | O(n) | 代码简洁，利用递归特性 |

**推荐使用递归解法**，代码简洁优雅，是面试中的经典解法。
