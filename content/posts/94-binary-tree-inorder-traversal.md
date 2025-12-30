---
title: "94. 二叉树的中序遍历"
difficulty: "简单"
description: "给定二叉树的根节点 root，返回它中序遍历的结果（中-左-右）。"
---

# 94. 二叉树的中序遍历

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给定二叉树的根节点 `root`，返回它中序遍历的结果。

中序遍历的顺序是：**左子树 → 根节点 → 右子树**

### 示例

```text
输入：root = [1,null,2,3]
     1
      \
       2
      /
     3

输出：[1,3,2]
```

## 解法一：递归遍历（推荐）

### 思路

递归是最直观的中序遍历方法：

1. 递归遍历左子树
2. 访问根节点
3. 递归遍历右子树

### Python

```python
from typing import List, Optional

# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val: int = 0, left: Optional['TreeNode'] = None, right: Optional['TreeNode'] = None):
        self.val = val
        self.left = left
        self.right = right

def inorder_traversal(root: Optional[TreeNode]) -> List[int]:
    """
    递归中序遍历

    时间复杂度: O(n)，每个节点访问一次
    空间复杂度: O(h)，递归栈深度等于树的高度 h
    """
    result = []

    def inorder(node: Optional[TreeNode]):
        if not node:
            return

        # 遍历左子树
        inorder(node.left)
        # 访问根节点
        result.append(node.val)
        # 遍历右子树
        inorder(node.right)

    inorder(root)
    return result

# 测试
if __name__ == "__main__":
    # 构建测试树：     1
    #               /   \
    #              2     3
    #             / \   /
    #            4   5 6
    root = TreeNode(1)
    root.left = TreeNode(2)
    root.right = TreeNode(3)
    root.left.left = TreeNode(4)
    root.left.right = TreeNode(5)
    root.right.left = TreeNode(6)

    print(inorder_traversal(root))  # 输出: [4, 2, 5, 1, 6, 3]
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
private:
    vector<int> result;

    void inorder(TreeNode* node) {
        if (!node) {
            return;
        }

        // 遍历左子树
        inorder(node->left);
        // 访问根节点
        result.push_back(node->val);
        // 遍历右子树
        inorder(node->right);
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        inorder(root);
        return result;
    }
};

// 测试
int main() {
    // 构建测试树：     1
    //               /   \
    //              2     3
    //             / \   /
    //            4   5 6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);

    Solution solution;
    vector<int> result = solution.inorderTraversal(root);

    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;  // 输出: 4 2 5 1 6 3

    return 0;
}
```

## 解法二：迭代遍历

### 思路

使用显式栈模拟递归过程：

1. 将根节点及其所有左子节点压入栈
2. 弹出栈顶节点，访问它
3. 将弹出的节点的右子树压入栈
4. 重复步骤1

### Python

```python
def inorder_iterative(root: Optional[TreeNode]) -> List[int]:
    """
    迭代中序遍历

    时间复杂度: O(n)
    空间复杂度: O(h)
    """
    result = []
    stack = []
    curr = root

    while curr or stack:
        # 找到最左边的节点
        while curr:
            stack.append(curr)
            curr = curr.left

        # 访问节点
        curr = stack.pop()
        result.append(curr.val)

        # 处理右子树
        curr = curr.right

    return result
```

### C++

```cpp
vector<int> inorderTraversalIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* curr = root;

    while (curr || !st.empty()) {
        // 找到最左边的节点
        while (curr) {
            st.push(curr);
            curr = curr->left;
        }

        // 访问节点
        curr = st.top();
        st.pop();
        result.push_back(curr->val);

        // 处理右子树
        curr = curr->right;
    }

    return result;
}
```

## 解法三：Morris 遍历

### 思路

Morris 遍历利用线索二叉树的思想，在 O(1) 空间内完成遍历：

1. 当前节点不为空时：
   - 如果当前节点左子树为空，访问当前节点，转向右子树
   - 如果当前节点左子树不为空，找到前驱节点（当前左子树的最右节点）
   - 如果前驱节点的右指针为空，将其指向当前节点，转向左子树
   - 如果前驱节点的右指针指向当前节点（形成环），恢复原状，访问当前节点，转向右子树

### Python

```python
def inorder_morris(root: Optional[TreeNode]) -> List[int]:
    """
    Morris 中序遍历

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    result = []
    curr = root
    predecessor = None

    while curr:
        if not curr.left:
            # 左子树为空，访问当前节点
            result.append(curr.val)
            curr = curr.right
        else:
            # 找到前驱节点
            predecessor = curr.left
            while predecessor.right and predecessor.right != curr:
                predecessor = predecessor.right

            if not predecessor.right:
                # 建立临时线索
                predecessor.right = curr
                curr = curr.left
            else:
                # 线索已存在，访问当前节点
                result.append(curr.val)
                predecessor.right = None  # 恢复指针
                curr = curr.right

    return result
```

### C++

```cpp
vector<int> inorderTraversalMorris(TreeNode* root) {
    vector<int> result;
    TreeNode* curr = root;
    TreeNode* predecessor = nullptr;

    while (curr) {
        if (!curr->left) {
            // 左子树为空，访问当前节点
            result.push_back(curr->val);
            curr = curr->right;
        } else {
            // 找到前驱节点
            predecessor = curr->left;
            while (predecessor->right && predecessor->right != curr) {
                predecessor = predecessor->right;
            }

            if (!predecessor->right) {
                // 建立临时线索
                predecessor->right = curr;
                curr = curr->left;
            } else {
                // 线索已存在，访问当前节点
                result.push_back(curr->val);
                predecessor->right = nullptr;  // 恢复指针
                curr = curr->right;
            }
        }
    }

    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 递归遍历 | O(n) | O(h) | 代码简洁，易于理解 |
| 迭代遍历 | O(n) | O(h) | 显式栈，不改变树结构 |
| Morris 遍历 | O(n) | O(1) | 空间最优，代码复杂 |

**说明**：
- `n` 是节点数，`h` 是树的高度
- 平衡二叉树的 `h = log₂n`，最坏情况下（链状）`h = n`
- Morris 遍历通过修改树结构实现了 O(1) 空间复杂度

## 总结

- **递归遍历**是最常用的方法，代码简洁直观
- **迭代遍历**使用显式栈模拟递归过程，便于理解遍历机制
- **Morris 遍历**展示了如何在 O(1) 空间内遍历二叉树，体现了巧妙的空间优化技巧
- 中序遍历的顺序是「左-根-右」，对二叉搜索树（BST）会得到有序序列
- 这三种方法的思想可以应用到前序和后序遍历
