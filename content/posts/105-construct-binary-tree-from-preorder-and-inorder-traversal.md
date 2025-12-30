---
title: "105. 从前序与中序遍历序列构造二叉树"
difficulty: "中等"
description: "给定两个整数数组 preorder 和 inorder，其中 preorder 是二叉树的前序遍历，inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。"
---

# 105. 从前序与中序遍历序列构造二叉树

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定两个整数数组 `preorder` 和 `inorder`，其中 `preorder` 是二叉树的前序遍历，`inorder` 是同一棵树的中序遍历，请构造二叉树并返回其根节点。

### 示例

```text
输入：preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出：[3,9,20,null,null,15,7]
解释：二叉树结构：
    3
   / \
  9  20
    /  \
   15   7
```

## 解法一：递归（推荐）

### 思路

利用前序遍历和中序遍历的特点：

1. **前序遍历**：根节点 → 左子树 → 右子树
2. **中序遍历**：左子树 → 根节点 → 右子树

构造过程：
1. 前序遍历的第一个元素是当前子树的根节点
2. 在中序遍历中找到根节点的位置，划分左子树和右子树
3. 递归构造左子树和右子树

### Python

```python
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int = 0, left: 'Optional[TreeNode]' = None, right: 'Optional[TreeNode]' = None):
        self.val = val
        self.left = left
        self.right = right

def build_tree(preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
    """
    递归解法

    时间复杂度: O(n^2)，最坏情况下（退化为链表）
    空间复杂度: O(n)，递归栈和哈希表
    """
    # 为了快速查找在中序遍历中的位置，创建值到索引的映射
    index_map = {value: idx for idx, value in enumerate(inorder)}

    # 定义递归函数
    def helper(pre_start: int, pre_end: int, in_start: int, in_end: int) -> Optional[TreeNode]:
        # 递归结束条件
        if pre_start > pre_end or in_start > in_end:
            return None

        # 前序遍历的第一个元素是根节点
        root_val = preorder[pre_start]
        root = TreeNode(root_val)

        # 在中序遍历中找到根节点的位置
        inorder_root_idx = index_map[root_val]

        # 左子树的大小
        left_size = inorder_root_idx - in_start

        # 递归构造左子树
        root.left = helper(
            pre_start + 1,
            pre_start + left_size,
            in_start,
            inorder_root_idx - 1
        )

        # 递归构造右子树
        root.right = helper(
            pre_start + left_size + 1,
            pre_end,
            inorder_root_idx + 1,
            in_end
        )

        return root

    n = len(preorder)
    return helper(0, n - 1, 0, n - 1)
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    unordered_map<int, int> index_map;

    TreeNode* helper(const vector<int>& preorder, const vector<int>& inorder,
                     int pre_start, int pre_end, int in_start, int in_end) {
        // 递归结束条件
        if (pre_start > pre_end || in_start > in_end) {
            return nullptr;
        }

        // 前序遍历的第一个元素是根节点
        int root_val = preorder[pre_start];
        TreeNode* root = new TreeNode(root_val);

        // 在中序遍历中找到根节点的位置
        int inorder_root_idx = index_map[root_val];

        // 左子树的大小
        int left_size = inorder_root_idx - in_start;

        // 递归构造左子树
        root->left = helper(preorder, inorder,
                            pre_start + 1,
                            pre_start + left_size,
                            in_start,
                            inorder_root_idx - 1);

        // 递归构造右子树
        root->right = helper(preorder, inorder,
                             pre_start + left_size + 1,
                             pre_end,
                             inorder_root_idx + 1,
                             in_end);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 创建值到索引的映射（哈希表）
        for (int i = 0; i < inorder.size(); i++) {
            index_map[inorder[i]] = i;
        }

        int n = preorder.size();
        return helper(preorder, inorder, 0, n - 1, 0, n - 1);
    }
};
```

## 解法二：优化版本（使用索引）

### 思路

与方法一相同，但在实现上更简洁，直接使用索引范围：

### Python

```python
def build_tree_optimized(preorder: List[int], inorder: List[int]) -> Optional[TreeNode]:
    """
    优化版本：更简洁的递归实现

    时间复杂度: O(n)，每次递归都是 O(1) 操作
    空间复杂度: O(n)，递归栈
    """
    if not preorder or not inorder:
        return None

    # 创建哈希表：值 -> 在中序遍历中的索引
    inorder_index_map = {value: idx for idx, value in enumerate(inorder)}

    # 定义递归函数
    def recursive_build(pre_start: int, in_start: int, in_end: int) -> Optional[TreeNode]:
        # 递归结束条件
        if in_start > in_end:
            return None

        # 前序遍历的第一个元素是根节点
        root_val = preorder[pre_start]
        root = TreeNode(root_val)

        # 在中序遍历中找到根节点的位置
        inorder_idx = inorder_index_map[root_val]

        # 递归构造左子树
        root.left = recursive_build(pre_start + 1, in_start, inorder_idx - 1)

        # 递归构造右子树
        # 右子树在前序中的起始位置 = 当前根节点位置 + 左子树大小 + 1
        root.right = recursive_build(
            pre_start + (inorder_idx - in_start) + 1,
            inorder_idx + 1,
            in_end
        )

        return root

    return recursive_build(0, 0, len(inorder) - 1)
```

### C++

```cpp
class SolutionOptimized {
private:
    unordered_map<int, int> inorder_index_map;

    TreeNode* build(vector<int>& preorder, int pre_start, int in_start, int in_end) {
        if (in_start > in_end) {
            return nullptr;
        }

        int root_val = preorder[pre_start];
        TreeNode* root = new TreeNode(root_val);

        int inorder_idx = inorder_index_map[root_val];

        // 递归构造左子树
        root->left = build(preorder, pre_start + 1, in_start, inorder_idx - 1);

        // 递归构造右子树
        root->right = build(preorder,
                            pre_start + (inorder_idx - in_start) + 1,
                            inorder_idx + 1,
                            in_end);

        return root;
    }

public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        // 创建哈希表
        for (int i = 0; i < inorder.size(); i++) {
            inorder_index_map[inorder[i]] = i;
        }

        return build(preorder, 0, 0, inorder.size() - 1);
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 递归（方法一） | O(n^2) | O(n) | 使用范围参数，易于理解 |
| 递归（优化版） | O(n) | O(n) | 代码更简洁，效率更高 |

**说明**：
- 方法一的时间复杂度为 O(n^2) 是因为在递归过程中传递了前序和中序的边界参数
- 优化版本通过传递更少的参数，降低了时间复杂度到 O(n)
- 哈希表的使用将查找中序遍历位置的时间从 O(n) 降到 O(1)

## 总结

- 关键在于理解前序遍历和中序遍历的特性
- 前序遍历的第一个元素总是根节点
- 中序遍历中根节点左侧是左子树，右侧是右子树
- 使用哈希表优化查找效率
- 递归是解决这类问题的自然方法
- 边界条件的处理（空子树）至关重要
