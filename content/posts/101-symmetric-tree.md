---
title: "101. 对称二叉树"
difficulty: "简单"
description: "给你一个二叉树的根节点 root，检查它是否轴对称。"
---

# 101. 对称二叉树

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给你一个二叉树的根节点 `root`，检查它是否轴对称。

### 示例

```text
输入：root = [1,2,2,3,4,4,3]
输出：true
```

解释：二叉树是对称的：

```
    1
   / \
  2   2
 / \ / \
3  4 4  3
```

```text
输入：root = [1,2,2,null,3,null,3]
输出：false
```

解释：二叉树不对称：

```
    1
   / \
  2   2
   \   \
    3   3
```

## 解法一：递归比较（推荐）

### 思路

判断二叉树是否对称，实质是判断**左子树**和**右子树**是否镜像：

1. 两个指针分别指向左子树和右子树
2. 比较两个指针指向的节点：
   - 值相等
   - 左子树的左孩子 = 右子树的右孩子
   - 左子树的右孩子 = 右子树的左孩子
3. 使用递归或迭代实现

递归函数 `isMirror(p, q)`：
- 如果 `p` 和 `q` 都为空，返回 `true`
- 如果其中一个为空，返回 `false`
- 如果值不相等，返回 `false`
- 递归比较 `isMirror(p.left, q.right)` 和 `isMirror(p.right, q.left)`

### Python

```python
from typing import Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int = 0, left: Optional['TreeNode'] = None, right: Optional['TreeNode'] = None):
        self.val = val
        self.left = left
        self.right = right

def is_symmetric(root: Optional[TreeNode]) -> bool:
    """
    递归判断二叉树是否对称

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(h)，递归栈深度，h 为树的高度
    """
    if not root:
        return True

    def is_mirror(left: Optional[TreeNode], right: Optional[TreeNode]) -> bool:
        # 两个节点都为空，对称
        if not left and not right:
            return True
        # 只有一个节点为空，不对称
        if not left or not right:
            return False
        # 值不相等，不对称
        if left.val != right.val:
            return False
        # 递归检查：左树的左 = 右树的右，左树的右 = 右树的左
        return (is_mirror(left.left, right.right) and
                is_mirror(left.right, right.left))

    return is_mirror(root.left, root.right)
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
    bool isMirror(TreeNode* left, TreeNode* right) {
        // 两个节点都为空，对称
        if (!left && !right) {
            return true;
        }
        // 只有一个节点为空，不对称
        if (!left || !right) {
            return false;
        }
        // 值不相等，不对称
        if (left->val != right->val) {
            return false;
        }
        // 递归检查：左树的左 = 右树的右，左树的右 = 右树的左
        return isMirror(left->left, right->right) &&
               isMirror(left->right, right->left);
    }

public:
    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }
        return isMirror(root->left, root->right);
    }
};
```

## 解法二：迭代解法（层序遍历）

### 思路

使用层序遍历比较每一层的节点：

1. 将根节点的左右孩子加入队列
2. 每次从队列中取出两个节点 `left` 和 `right`
3. 比较这两个节点：
   - 值相等
   - 将 `left.left` 和 `right.right` 加入队列
   - 将 `left.right` 和 `right.left` 加入队列
4. 如果所有节点都匹配，说明是对称的

### Python

```python
from collections import deque

def is_symmetric_iterative(root: Optional[TreeNode]) -> bool:
    """
    迭代层序遍历解法

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(w)，队列最大宽度
    """
    if not root:
        return True

    # 将左右孩子加入队列
    queue = deque([root.left, root.right])

    while queue:
        # 每次取出两个节点进行比较
        left = queue.popleft()
        right = queue.popleft()

        # 两个节点都为空，继续
        if not left and not right:
            continue
        # 只有一个为空，不对称
        if not left or not right:
            return False
        # 值不相等，不对称
        if left.val != right.val:
            return False

        # 按照镜像顺序加入队列
        queue.append(left.left)
        queue.append(right.right)
        queue.append(left.right)
        queue.append(right.left)

    return True
```

### C++

```cpp
#include <queue>
using namespace std;

class Solution {
public:
    bool isSymmetric(TreeNode* root) {
        if (!root) {
            return true;
        }

        // 将左右孩子加入队列
        queue<TreeNode*> q;
        q.push(root->left);
        q.push(root->right);

        while (!q.empty()) {
            // 每次取出两个节点进行比较
            TreeNode* left = q.front(); q.pop();
            TreeNode* right = q.front(); q.pop();

            // 两个节点都为空，继续
            if (!left && !right) {
                continue;
            }
            // 只有一个为空，不对称
            if (!left || !right) {
                return false;
            }
            // 值不相等，不对称
            if (left->val != right->val) {
                return false;
            }

            // 按照镜像顺序加入队列
            q.push(left->left);
            q.push(right->right);
            q.push(left->right);
            q.push(right->left);
        }

        return true;
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 递归比较 | O(n) | O(h) | 代码简洁，思路清晰 |
| 迭代层序遍历 | O(n) | O(w) | 迭代实现，避免递归栈溢出 |

**说明**：递归方法代码更简洁，迭代方法更适合深度较大的树。

## 总结

- 对称二叉树的核心是**镜像匹配**的概念
- 递归方法通过 `isMirror(left, right)` 巧妙地比较镜像节点
- 迭代方法通过队列按镜像顺序处理节点
- 注意处理边界情况：空节点、单个节点
- 理解"镜像"的含义：左树的左 = 右树的右，左树的右 = 右树的左
