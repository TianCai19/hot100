---
title: "114. 二叉树展开为链表"
difficulty: "中等"
description: "给你二叉树的根节点 root，请你将它展开为一个单链表。展开后的单链表应该同样使用 TreeNode，其中 right 指针指向下一个节点，左子节点始终为 null。展开后的单链表应该与二叉树的前序遍历顺序相同。"
---

# 114. 二叉树展开为链表

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你二叉树的根节点 `root`，请你将它展开为一个单链表。

展开后的单链表应该同样使用 `TreeNode`，其中 `right` 指针指向下一个节点，左子节点始终为 `null`。展开后的单链表应该与二叉树的前序遍历顺序相同。

### 示例

```text
输入：root = [1,2,3,4,5,6]
输出：[1,null,2,null,3,null,4,null,5,null,6]
```

![](https://assets.leetcode.com/uploads/2021/01/24/flatten.jpg)

```text
输入：root = []
输出：[]
```

```text
输入：root = [0]
输出：[0]
```

## 解法一：前序遍历 + 链表转换（推荐）

### 思路

使用前序遍历获得节点顺序，然后重新连接节点：

1. 前序遍历二叉树，将所有节点保存到列表中
2. 遍历列表，将每个节点的左指针设为 `null`，右指针指向下一个节点
3. 最后一个节点的右指针保持 `null`

### Python

```python
from typing import Optional, List

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

class Solution:
    def flatten(self, root: Optional[TreeNode]) -> None:
        """
        前序遍历 + 链表转换

        时间复杂度: O(n)，其中 n 是节点数
        空间复杂度: O(n)，存储所有节点
        """
        if not root:
            return

        # 前序遍历获取所有节点
        nodes: List[TreeNode] = []
        self._preorder(root, nodes)

        # 重新连接节点
        for i in range(len(nodes) - 1):
            nodes[i].left = None
            nodes[i].right = nodes[i + 1]

        # 最后一个节点的指针
        if nodes:
            nodes[-1].left = None
            nodes[-1].right = None

    def _preorder(self, node: TreeNode, nodes: List[TreeNode]) -> None:
        if not node:
            return

        nodes.append(node)
        self._preorder(node.left, nodes)
        self._preorder(node.right, nodes)
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
    void preorder(TreeNode* node, vector<TreeNode*>& nodes) {
        if (!node) return;

        nodes.push_back(node);
        preorder(node->left, nodes);
        preorder(node->right, nodes);
    }

public:
    void flatten(TreeNode* root) {
        if (!root) return;

        vector<TreeNode*> nodes;
        preorder(root, nodes);

        // 重新连接节点
        for (size_t i = 0; i < nodes.size() - 1; i++) {
            nodes[i]->left = nullptr;
            nodes[i]->right = nodes[i + 1];
        }

        // 最后一个节点
        if (!nodes.empty()) {
            nodes.back()->left = nullptr;
            nodes.back()->right = nullptr;
        }
    }
};
```

## 解法二：迭代前序遍历（空间优化）

### 思路

使用显式栈模拟递归，避免递归栈开销：

1. 使用栈保存待访问的节点
2. 弹出一个节点，将其右子节点入栈，左子节点也入栈
3. 重复直到栈为空

### Python

```python
def flatten_iterative(root: Optional[TreeNode]) -> None:
    """
    迭代前序遍历

    时间复杂度: O(n)
    空间复杂度: O(h)，其中 h 是树的高度
    """
    if not root:
        return

    stack = [root]
    prev = None

    while stack:
        node = stack.pop()

        if prev:
            prev.right = node
            prev.left = None

        # 先右后左，这样出栈时先访问左子树
        if node.right:
            stack.append(node.right)
        if node.left:
            stack.append(node.left)

        prev = node
```

### C++

```cpp
void flattenIterative(TreeNode* root) {
    if (!root) return;

    stack<TreeNode*> st;
    st.push(root);
    TreeNode* prev = nullptr;

    while (!st.empty()) {
        TreeNode* node = st.top();
        st.pop();

        if (prev) {
            prev->right = node;
            prev->left = nullptr;
        }

        // 先右后左
        if (node->right) {
            st.push(node->right);
        }
        if (node->left) {
            st.push(node->left);
        }

        prev = node;
    }
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 前序遍历 + 列表 | O(n) | O(n) | 思路清晰，易于理解 |
| 迭代前序遍历 | O(n) | O(h) | 空间更优，无额外列表 |

**说明**：其中 n 是节点数，h 是树的高度。

## 总结

- **前序遍历**是解决这类问题的关键，因为展开后的链表顺序就是前序遍历顺序
- 解法一代码更清晰，适合理解概念
- 解法二空间效率更高，实际应用中推荐使用
- 注意题目要求左子节点必须为 `null`
