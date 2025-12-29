---
title: "226. 翻转二叉树"
difficulty: "简单"
description: "给你一棵二叉树的根节点 root，翻转这棵二叉树，并返回其根节点。"
---

# 226. 翻转二叉树

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给你一棵二叉树的根节点 `root`，翻转这棵二叉树，并返回其根节点。

### 图示

原树：
```
    4
   / \
  2   7
 / \ / \
1  3 6  9
```

翻转后：
```
    4
   / \
  7   2
 / \ / \
9  6 3  1
```

## 示例

### 示例 1

- **输入：** `root = [4,2,7,1,3,6,9]`
- **输出：** `[4,7,2,9,6,3,1]`

### 示例 2

- **输入：** `root = [2,1,3]`
- **输出：** `[2,3,1]`

### 示例 3

- **输入：** `root = []`
- **输出：** `[]`

## 提示

- 树中节点数目范围在 `[0, 100]` 内
- `-100 <= Node.val <= 100`

---

## 解法一：递归（推荐）

### 思路

翻转二叉树的本质是**交换每个节点的左右子节点**。

<Mermaid>
graph TB
    A["Recursive invert root"] --> B["Invert left subtree"]
    A --> C["Invert right subtree"]
    A --> D["Swap left and right children"]
    B --> E["return invert(left)"]
    C --> F["return invert(right)"]
    D --> G["root.left, root.right = root.right, root.left"]
</Mermaid>

**核心思想：**
1. 递归翻转左子树
2. 递归翻转右子树
3. 交换左右子节点

### Python

```python
from typing import Optional

class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None

        # 递归翻转左右子树
        left = self.invertTree(root.left)
        right = self.invertTree(root.right)

        # 交换左右子节点
        root.left, root.right = right, left

        return root
```

### C++

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
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
```

### 复杂度分析

- **时间复杂度：** O(n)，每个节点访问一次
- **空间复杂度：** O(h)，h 为树的高度，递归栈深度

---

## 解法二：迭代（BFS 层序遍历）

### 思路

使用队列进行层序遍历，在遍历过程中交换每个节点的左右子节点。

### Python

```python
from typing import Optional
from collections import deque

class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None

        queue = deque([root])

        while queue:
            node = queue.popleft()
            # 交换左右子节点
            node.left, node.right = node.right, node.left

            # 将非空子节点加入队列
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        return root
```

### C++

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            // 交换左右子节点
            swap(node->left, node->right);

            // 将非空子节点加入队列
            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }

        return root;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n)，每个节点访问一次
- **空间复杂度：** O(w)，w 为树的最大宽度（队列大小）

---

## 解法三：迭代（DFS 前序遍历）

### 思路

使用栈进行前序遍历，在遍历过程中交换每个节点的左右子节点。

### Python

```python
from typing import Optional

class Solution:
    def invertTree(self, root: Optional[TreeNode]) -> Optional[TreeNode]:
        if not root:
            return None

        stack = [root]

        while stack:
            node = stack.pop()
            # 交换左右子节点
            node.left, node.right = node.right, node.left

            # 先压右左子节点（因为是前序遍历，栈后进先出）
            if node.left:
                stack.append(node.left)
            if node.right:
                stack.append(node.right)

        return root
```

### C++

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return nullptr;

        stack<TreeNode*> st;
        st.push(root);

        while (!st.empty()) {
            TreeNode* node = st.top();
            st.pop();

            // 交换左右子节点
            swap(node->left, node->right);

            // 先压右左子节点（因为是前序遍历，栈后进先出）
            if (node->left) st.push(node->left);
            if (node->right) st.push(node->right);
        }

        return root;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n)，每个节点访问一次
- **空间复杂度：** O(h)，h 为树的高度

---

## 三种解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
|------|-----------|-----------|------|------|
| 递归 | O(n) | O(h) | 代码简洁优雅 | 递归可能栈溢出 |
| BFS 迭代 | O(n) | O(w) | 不会栈溢出 | 空间可能较大 |
| DFS 迭代 | O(n) | O(h) | 避免递归 | 代码稍复杂 |

## 总结

- **最推荐：** 递归解法，代码最简洁直观
- **面试建议：** 可以先写递归，再讨论如何改写成迭代
- **经典名言：** "Google：我们 90% 的工程师使用你写的软件（Homebrew），但你解不出这道题？" —— Max Howell
- **本质理解：** 翻转二叉树 = 交换每个节点的左右子节点
