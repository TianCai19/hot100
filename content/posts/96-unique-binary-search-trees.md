---
title: "96. 不同的二叉搜索树"
difficulty: "中等"
description: "给你一个整数 n，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的二叉搜索树有多少种？"
---

# 96. 不同的二叉搜索树

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个整数 `n`，求恰由 `n` 个节点组成且节点值从 `1` 到 `n` 互不相同的二叉搜索树有多少种？

### 示例

```text
输入：n = 3
输出：5
```

解释：以下是 n = 3 时所有可能的二叉搜索树：

```
     1         3     3      2      1
      \       /     /      / \      \
       3     2     1      1   3      2
      /     /       \          \    /
     2     1         2          3  1
```

```text
输入：n = 1
输出：1
```

## 解法一：动态规划（推荐）

### 思路

这是卡塔兰数的典型应用。二叉搜索树的特点是：

1. 左子树的所有节点值小于根节点
2. 右子树的所有节点值大于根节点
3. 左右子树也是二叉搜索树

动态规划思路：

- 设 `dp[i]` 为长度为 `i` 的序列能组成的二叉搜索树数量
- 以 `j` 为根节点（`1 ≤ j ≤ i`）：
  - 左子树由 `1...j-1` 组成，共 `dp[j-1]` 种
  - 右子树由 `j+1...i` 组成，共 `dp[i-j]` 种
- `dp[i] = Σ(dp[j-1] * dp[i-j])`，其中 `j` 从 `1` 到 `i`

### Python

```python
def num_trees(n: int) -> int:
    """
    动态规划解法（卡塔兰数）

    时间复杂度: O(n^2)
    空间复杂度: O(n)
    """
    if n == 0 or n == 1:
        return 1

    # dp[i] 表示长度为 i 的序列能组成的 BST 数量
    dp = [0] * (n + 1)
    dp[0] = 1  # 空树
    dp[1] = 1  # 单节点树

    for i in range(2, n + 1):
        # 以 j 为根节点，计算左子树和右子树的组合
        for j in range(1, i + 1):
            dp[i] += dp[j - 1] * dp[i - j]

    return dp[n]
```

### C++

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        if (n == 0 || n == 1) {
            return 1;
        }

        // dp[i] 表示长度为 i 的序列能组成的 BST 数量
        vector<int> dp(n + 1, 0);
        dp[0] = 1;  // 空树
        dp[1] = 1;  // 单节点树

        for (int i = 2; i <= n; i++) {
            // 以 j 为根节点，计算左子树和右子树的组合
            for (int j = 1; j <= i; j++) {
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }

        return dp[n];
    }
};
```

## 解法二：数学公式（卡塔兰数）

### 思路

该问题实际上是求第 `n` 个卡塔兰数：

```
C(0) = 1
C(n+1) = Σ(C(i) * C(n-i))，其中 i 从 0 到 n
```

也可以用闭公式计算：

```
C(n) = (2n)! / (n+1)! / n!
```

### Python

```python
import math

def num_trees_formula(n: int) -> int:
    """
    卡塔兰数公式解法

    时间复杂度: O(n)，使用数学公式计算
    空间复杂度: O(1)
    """
    # 第 n 个卡塔兰数: C(2n, n) / (n + 1)
    return math.comb(2 * n, n) // (n + 1)
```

### C++

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int numTrees(int n) {
        // 使用动态规划计算组合数
        vector<vector<long long>> C(2 * n + 1, vector<long long>(2 * n + 1, 0));

        // 预处理组合数 C(n, k)
        for (int i = 0; i <= 2 * n; i++) {
            C[i][0] = C[i][i] = 1;
            for (int j = 1; j < i; j++) {
                C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
            }
        }

        // 第 n 个卡塔兰数: C(2n, n) / (n + 1)
        return C[2 * n][n] / (n + 1);
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 | O(n^2) | O(n) | 直观易懂，容易实现 |
| 卡塔兰数公式 | O(n) | O(1) | 数学公式，速度快 |

**说明**：动态规划方法更直观，公式方法速度更快但需要处理大数问题。

## 总结

- 二叉搜索树计数问题是**卡塔兰数**的典型应用
- 动态规划通过拆分左右子树巧妙计算总数量
- 理解二叉搜索树的性质是解决问题的关键
- 对于大数据，动态规划更容易处理边界情况
