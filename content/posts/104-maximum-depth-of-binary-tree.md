---
title: "104. 二叉树的最大深度"
difficulty: "简单"
description: "给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。"
---

# 104. 二叉树的最大深度

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给定一个二叉树，找出其最大深度。二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。

### 示例

```text
输入：[3,9,20,null,null,15,7]
    3
   / \
  9  20
    /  \
   15   7
输出：3
```

```text
输入：[1,null,2]
  1
   \
    2
输出：2
```

## 解法一：递归（推荐）

### 思路

使用递归计算左子树和右子树的最大深度：

1. 如果节点为空，返回深度 0
2. 递归计算左子树的最大深度
3. 递归计算右子树的最大深度
4. 返回 max(左子树深度, 右子树深度) + 1

### Python

```python
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int = 0, left: 'Optional[TreeNode]' = None, right: 'Optional[TreeNode]' = None):
        self.val = val
        self.left = left
        self.right = right

def max_depth(root: Optional[TreeNode]) -> int:
    """
    递归解法

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(h)，递归栈深度，其中 h 是树的高度
    """
    if not root:
        return 0

    # 递归计算左右子树的最大深度
    left_depth = max_depth(root.left)
    right_depth = max_depth(root.right)

    # 返回子树最大深度 + 1（当前节点）
    return max(left_depth, right_depth) + 1
```

### C++

```cpp
#include <iostream>
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
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        // 递归计算左右子树的最大深度
        int left_depth = maxDepth(root->left);
        int right_depth = maxDepth(root->right);

        // 返回子树最大深度 + 1（当前节点）
        return max(left_depth, right_depth) + 1;
    }
};
```

## 解法二：迭代（BFS）

### 思路

使用广度优先搜索，通过队列按层遍历：

1. 初始化队列，将根节点入队
2. 初始化深度计数器
3. 当队列不为空时：
   - 获取当前层的节点数
   - 遍历当前层所有节点
   - 将子节点入队
   - 深度计数器加 1

### Python

```python
from collections import deque

def max_depth_iterative(root: Optional[TreeNode]) -> int:
    """
    迭代解法（BFS）

    时间复杂度: O(n)
    空间复杂度: O(w)，其中 w 是树的最大宽度
    """
    if not root:
        return 0

    queue = deque([root])
    depth = 0

    while queue:
        depth += 1
        level_size = len(queue)

        for _ in range(level_size):
            node = queue.popleft()

            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

    return depth
```

### C++

```cpp
#include <queue>
using namespace std;

class SolutionIterative {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        queue<TreeNode*> q;
        q.push(root);
        int depth = 0;

        while (!q.empty()) {
            depth++;
            int levelSize = q.size();

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();

                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
        }

        return depth;
    }
};
```

## 解法三：迭代（DFS）

### 思路

使用深度优先搜索，通过栈来模拟递归：

1. 创建栈，存储节点和对应的深度
2. 初始化栈，包含根节点和深度 1
3. 当栈不为空时：
   - 弹出节点和深度
   - 更新最大深度
   - 将子节点和深度 + 1 入栈

### Python

```python
def max_depth_dfs(root: Optional[TreeNode]) -> int:
    """
    迭代解法（DFS）

    时间复杂度: O(n)
    空间复杂度: O(h)，栈的深度为树的高度
    """
    if not root:
        return 0

    max_depth = 0
    stack = [(root, 1)]  # 存储 (节点, 深度)

    while stack:
        node, depth = stack.pop()
        max_depth = max(max_depth, depth)

        if node.right:
            stack.append((node.right, depth + 1))
        if node.left:
            stack.append((node.left, depth + 1))

    return max_depth
```

### C++

```cpp
#include <stack>
#include <utility>
using namespace std;

class SolutionDFS {
public:
    int maxDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        int max_depth = 0;
        stack<pair<TreeNode*, int>> st;
        st.push(make_pair(root, 1));

        while (!st.empty()) {
            auto [node, depth] = st.top();
            st.pop();
            max_depth = max(max_depth, depth);

            if (node->right) {
                st.push(make_pair(node->right, depth + 1));
            }
            if (node->left) {
                st.push(make_pair(node->left, depth + 1));
            }
        }

        return max_depth;
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 递归 | O(n) | O(h) | 代码最简洁，最常用 |
| BFS 迭代 | O(n) | O(w) | 按层处理，易于理解 |
| DFS 迭代 | O(n) | O(h) | 手动管理栈，避免递归限制 |

**说明**：
- `h` 是树的高度，在最坏情况下（链状树）为 O(n)
- `w` 是树的最大宽度，完全二叉树时为 O(n/2) ≈ O(n)
- 平均情况下，递归和迭代的空间复杂度相近

## 总结

- **递归解法**是最简洁的方法，体现了二叉树递归的天然特性
- **BFS 迭代**按层遍历，直观地模拟了层序遍历的过程
- **DFS 迭代**手动管理栈，可以避免递归深度限制
- 理解这些方法有助于掌握树的基本遍历策略
