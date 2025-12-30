---
title: "102. 二叉树的层序遍历"
difficulty: "中等"
description: "给你二叉树的根节点 root，返回其节点值的层序遍历（即逐层地，从左到右访问所有节点）。"
---

# 102. 二叉树的层序遍历

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你二叉树的根节点 `root`，返回其节点值的层序遍历（即逐层地，从左到右访问所有节点）。

### 示例

```text
输入：root = [3,9,20,null,null,15,7]
输出：[[3],[9,20],[15,7]]
```

```text
输入：root = [1]
输出：[[1]]
```

```text
输入：root = []
输出：[]
```

## 解法一：队列迭代（推荐）

### 思路

层序遍历使用队列（先进先出）来实现：

1. 创建一个队列，将根节点入队
2. 当队列不为空时：
   - 获取当前队列大小（即当前层的节点数）
   - 遍历当前层的所有节点
   - 将节点的子节点（左、右）加入队列
3. 每层的节点值组成一个列表加入结果

### Python

```python
from collections import deque
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int = 0, left: 'Optional[TreeNode]' = None, right: 'Optional[TreeNode]' = None):
        self.val = val
        self.left = left
        self.right = right

def level_order(root: Optional[TreeNode]) -> List[List[int]]:
    """
    使用队列进行层序遍历

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(n)，队列最多存储一层节点
    """
    if not root:
        return []

    result: List[List[int]] = []
    queue = deque([root])

    while queue:
        level_size = len(queue)
        current_level: List[int] = []

        for _ in range(level_size):
            node = queue.popleft()
            current_level.append(node.val)

            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)

        result.append(current_level)

    return result
```

### C++

```cpp
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
    vector<vector<int>> levelOrder(TreeNode* root) {
        if (!root) {
            return {};
        }

        vector<vector<int>> result;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;

            for (int i = 0; i < levelSize; i++) {
                TreeNode* node = q.front();
                q.pop();
                currentLevel.push_back(node->val);

                if (node->left) {
                    q.push(node->left);
                }
                if (node.right) {
                    q.push(node->right);
                }
            }

            result.push_back(currentLevel);
        }

        return result;
    }
};
```

## 解法二：递归解法

### 思路

使用递归同时传递层级信息：

1. 定义递归函数 `dfs(node, level)`
2. 如果节点为空，直接返回
3. 确保结果列表有足够的层级
4. 将当前节点值加入对应层级
5. 递归处理左子树和右子树

### Python

```python
def level_order_recursive(root: Optional[TreeNode]) -> List[List[int]]:
    """
    递归解法（本质是深度优先遍历，但按层级组织结果）

    时间复杂度: O(n)
    空间复杂度: O(h)，其中 h 是树的高度（递归栈）
    """
    if not root:
        return []

    def dfs(node: Optional[TreeNode], level: int):
        if not node:
            return

        # 确保结果列表有足够的层级
        if level >= len(result):
            result.append([])

        # 将节点值加入对应层级
        result[level].append(node.val)

        # 递归处理左右子树
        dfs(node.left, level + 1)
        dfs(node.right, level + 1)

    result: List[List[int]] = []
    dfs(root, 0)
    return result
```

### C++

```cpp
class SolutionRecursive {
private:
    void dfs(TreeNode* node, int level, vector<vector<int>>& result) {
        if (!node) {
            return;
        }

        // 确保结果列表有足够的层级
        if (level >= result.size()) {
            result.push_back(vector<int>());
        }

        // 将节点值加入对应层级
        result[level].push_back(node->val);

        // 递归处理左右子树
        dfs(node->left, level + 1, result);
        dfs(node->right, level + 1, result);
    }

public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> result;
        dfs(root, 0, result);
        return result;
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 队列迭代 | O(n) | O(n) | 直观，符合层序遍历思想 |
| 递归解法 | O(n) | O(h) | 代码简洁，深度优先遍历 |

**说明**：
- 队列迭代法：空间复杂度为 O(n)，因为队列最多存储一层节点
- 递归解法：空间复杂度为 O(h)，其中 h 是树的高度，取决于树的平衡性

## 总结

- **队列迭代法**是最符合层序遍历思想的方法，利用队列的先进先出特性
- **递归解法**通过传递层级参数，巧妙地将深度优先遍历结果按层级组织
- 两种方法的时间复杂度都是 O(n)，实际性能差异不大
- 注意处理空树的情况
