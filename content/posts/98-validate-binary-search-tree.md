---
title: "98. 验证二叉搜索树"
difficulty: "中等"
description: "给你一个二叉树的根节点 root，判断其是否是一个有效的二叉搜索树（BST）。"
---

# 98. 验证二叉搜索树

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个二叉树的根节点 `root`，判断其是否是一个有效的二叉搜索树（BST）。

**有效的二叉搜索树定义为**：

1. 节点的左子树只包含小于当前节点的数
2. 节点的右子树只包含大于当前节点的数
3. 所有左子树和右子树自身也必须是二叉搜索树

### 示例

```text
输入：root = [2,1,3]
输出：true
```

解释：二叉搜索树的结构：

```
    2
   / \
  1   3
```

```text
输入：root = [5,1,4,null,null,3,6]
输出：false
```

解释：根节点为 5，右子树节点 3 小于根节点，不符合 BST 规则：

```
    5
   / \
  1   4
     / \
    3   6
```

## 解法一：递归验证（推荐）

### 思路

对于二叉搜索树，每个节点都有一个有效的取值范围：

1. 根节点的范围：`-∞ < root.val < +∞`
2. 左子树的范围：`-∞ < node.val < root.val`
3. 右子树的范围：`root.val < node.val < +∞`

使用递归遍历二叉树，携带上下界信息：

- `lower`：当前节点的下界
- `upper`：当前节点的上界
- 如果节点值不在 `[lower, upper]` 范围内，返回 `false`

### Python

```python
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int = 0, left: Optional['TreeNode'] = None, right: Optional['TreeNode'] = None):
        self.val = val
        self.left = left
        self.right = right

def is_valid_bst(root: Optional[TreeNode]) -> bool:
    """
    递归验证二叉搜索树

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(h)，递归栈深度，h 为树的高度
    """
    def validate(node: Optional[TreeNode], lower: int = float('-inf'), upper: int = float('inf')) -> bool:
        # 空节点是有效的 BST
        if not node:
            return True

        # 检查当前节点值是否在有效范围内
        if not (lower < node.val < upper):
            return False

        # 递归验证左子树和右子树
        return (validate(node.left, lower, node.val) and
                validate(node.right, node.val, upper))

    return validate(root)
```

### C++

```cpp
#include <climits>
using namespace std;

// Definition for a binary tree node.
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
    bool validate(TreeNode* node, long long lower, long long upper) {
        // 空节点是有效的 BST
        if (!node) {
            return true;
        }

        // 检查当前节点值是否在有效范围内
        if (node->val <= lower || node->val >= upper) {
            return false;
        }

        // 递归验证左子树和右子树
        return validate(node->left, lower, node->val) &&
               validate(node->right, node->val, upper);
    }

public:
    bool isValidBST(TreeNode* root) {
        return validate(root, LONG_MIN, LONG_MAX);
    }
};
```

## 解法二：中序遍历

### 思路

二叉搜索树的**中序遍历**结果是一个**严格递增**的序列：

```
左子树 -> 根节点 -> 右子树
```

通过中序遍历验证序列是否递增：

1. 初始化 `prev = -∞`
2. 中序遍历每个节点
3. 如果当前节点值不大于 `prev`，说明不是 BST
4. 更新 `prev = 当前节点值`

### Python

```python
def is_valid_bst_inorder(root: Optional[TreeNode]) -> bool:
    """
    中序遍历解法

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(h)，递归栈深度
    """
    def inorder(node: Optional[TreeNode]) -> bool:
        nonlocal prev
        if not node:
            return True

        # 中序遍历：左子树
        if not inorder(node.left):
            return False

        # 检查当前节点
        if prev is not None and node.val <= prev:
            return False
        prev = node.val

        # 中序遍历：右子树
        return inorder(node.right)

    prev = None
    return inorder(root)
```

### C++

```cpp
class Solution {
private:
    long long prev = LLONG_MIN;
    bool inorder(TreeNode* node) {
        if (!node) {
            return true;
        }

        // 中序遍历：左子树
        if (!inorder(node->left)) {
            return false;
        }

        // 检查当前节点
        if (node->val <= prev) {
            return false;
        }
        prev = node->val;

        // 中序遍历：右子树
        return inorder(node->right);
    }

public:
    bool isValidBST(TreeNode* root) {
        return inorder(root);
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 递归验证 | O(n) | O(h) | 直观，携带边界信息 |
| 中序遍历 | O(n) | O(h) | 利用 BST 中序遍历特性 |

**说明**：两种方法都需要 O(n) 时间，中序遍历方法利用了 BST 的特性，代码更简洁。

## 总结

- **递归验证**方法通过携带上下界信息，更直观易懂
- **中序遍历**方法利用 BST 的中序遍历序列递增特性，代码更优雅
- 注意处理整数的边界情况，使用 `float('-inf')` 或 `LONG_MIN/LONG_MAX`
- 理解二叉搜索树的本质特征是解决问题的关键
