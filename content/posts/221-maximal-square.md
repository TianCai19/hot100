---
title: "221. 最大正方形"
difficulty: "中等"
description: "在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。"
---

# 221. 最大正方形

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

在一个由 `'0'` 和 `'1'` 组成的二维矩阵内，找到只包含 `'1'` 的最大正方形，并返回其面积。

### 图示说明

给定一个由 `'0'` 和 `'1'` 组成的矩阵，我们需要找到其中最大的、只包含 `'1'` 的正方形子区域：

```
矩阵示例:                找到的最大正方形:
┌───┬───┬───┬───┬───┐    ┌───┬───┬───┬───┬───┐
│ 1 │ 0 │ 1 │ 0 │ 0 │    │ 1 │ 0 │   │   │   │
├───┼───┼───┼───┼───┤    ├───┼───┼───┼───┼───┤
│ 1 │ 0 │ 1 │ 1 │ 1 │    │ 1 │ 0 │ █ │ █ │   │
├───┼───┼───┼───┼───┤    ├───┼───┼───┼───┼───┤
│ 1 │ 1 │ 1 │ 1 │ 1 │    │ 1 │ 1 │ █ │ █ │ 1 │
├───┼───┼───┼───┼───┤    ├───┼───┼───┼───┼───┤
│ 1 │ 0 │ 0 │ 1 │ 0 │    │ 1 │ 0 │ 0 │ 1 │ 0 │
└───┴───┴───┴───┴───┘    └───┴───┴───┴───┴───┘

最大正方形: 2×2，面积 = 4
```

## 示例

### 示例 1

**输入矩阵：**
```
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
```

**可视化：** 最大正方形位置（用 `█` 标记）
```
1 0 ▓ ▓ 0
1 0 ▓ ▓ 1
1 1 1 1 1
1 0 0 1 0
```

**输出：** `4`（2×2 正方形的面积）

### 示例 2

**输入矩阵：**
```
0 1
1 0
```

**输出：** `1`（最大只能找到 1×1 的正方形）

### 示例 3

**输入矩阵：**
```
0
```

**输出：** `0`（没有正方形）

## 提示

- `m == matrix.length`
- `n == matrix[i].length`
- `1 <= m, n <= 300`
- `matrix[i][j]` 为 `'0'` 或 `'1'`

---

## 解法一：暴力解

### 思路

枚举所有可能的正方形左上角，然后逐步扩大边长判断是否全是 '1'。

### Python

```python
from typing import List

class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        if not matrix or not matrix[0]:
            return 0

        rows, cols = len(matrix), len(matrix[0])
        max_side = 0

        for i in range(rows):
            for j in range(cols):
                if matrix[i][j] == '1':
                    max_possible = min(rows - i, cols - j)
                    for k in range(1, max_possible + 1):
                        all_ones = True
                        for x in range(i, i + k):
                            for y in range(j, j + k):
                                if matrix[x][y] != '1':
                                    all_ones = False
                                    break
                            if not all_ones:
                                break
                        if all_ones:
                            max_side = max(max_side, k)
                        else:
                            break

        return max_side * max_side
```

### 复杂度分析

- **时间复杂度：** O((mn)² × min(m,n))，非常低效
- **空间复杂度：** O(1)

---

## 解法二：动态规划（推荐）

### 思路

定义 `dp[i][j]` 表示以 `(i, j)` 为**右下角**的最大正方形的边长。

**状态转移方程：**

```
dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1  (当 matrix[i][j] == '1')
```

**DP 数组依赖关系图：**

```
              j-1  j
            ┌────┬────┐
      i-1   │ A  │ B  │    A = dp[i-1][j-1] (左上)
            ├────┼────┤    B = dp[i-1][j]   (上方)
        i   │ C  │ ?  │    C = dp[i][j-1]   (左方)
            └────┴────┘    ? = dp[i][j]     (当前位置)

                    min(A, B, C) + 1
                         ↓
                    ┌────┴────┐
                    │   当前   │
                    │ dp[i][j] │
                    └─────────┘
```

**关键理解：**
- 如果 `matrix[i][j] == '0'`，则 `dp[i][j] = 0`（不能构成正方形）
- 如果 `matrix[i][j] == '1'`，则 `dp[i][j]` 取决于三个位置的最小值：
  - 上方：`dp[i-1][j]`
  - 左方：`dp[i][j-1]`
  - 左上：`dp[i-1][j-1]`

**为什么取最小值？** 因为正方形需要三个方向都能延伸，受最短边限制。

**示例计算过程：**

原始矩阵：
```
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0
```

DP 数组（从 (1,1) 开始）：
```
     0  1  2  3  4  5     (列索引)
  0  0  0  0  0  0  0
  1  0  1  0  1  0  0
  2  0  1  0  1  1  1
  3  0  1  1  1  2  2  ← 最大边长 = 2
  4  0  1  0  0  1  0
```

以 (3,4) 位置为例，计算 `dp[3][4]`：
- `dp[2][4] = 1` (上方)
- `dp[3][3] = 1` (左方)
- `dp[2][3] = 1` (左上)
- `dp[3][4] = min(1, 1, 1) + 1 = 2`

这意味着可以形成边长为 2 的正方形！

### Python

```python
from typing import List

class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        if not matrix or not matrix[0]:
            return 0

        rows, cols = len(matrix), len(matrix[0])
        dp = [[0] * (cols + 1) for _ in range(rows + 1)]
        max_side = 0

        for i in range(1, rows + 1):
            for j in range(1, cols + 1):
                if matrix[i - 1][j - 1] == '1':
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1
                    max_side = max(max_side, dp[i][j])

        return max_side * max_side
```

### C++

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size(), cols = matrix[0].size();
        vector<vector<int>> dp(rows + 1, vector<int>(cols + 1, 0));
        int maxSide = 0;

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                if (matrix[i - 1][j - 1] == '1') {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                    maxSide = max(maxSide, dp[i][j]);
                }
            }
        }

        return maxSide * maxSide;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(m × n)
- **空间复杂度：** O(m × n)

---

## 解法三：动态规划 + 空间优化

### 思路

观察到 `dp[i][j]` 只依赖于上一行和当前行的前一个元素，可以用一维数组优化空间。

### Python

```python
from typing import List

class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        if not matrix or not matrix[0]:
            return 0

        rows, cols = len(matrix), len(matrix[0])
        dp = [0] * (cols + 1)
        max_side = 0
        prev = 0

        for i in range(1, rows + 1):
            for j in range(1, cols + 1):
                temp = dp[j]
                if matrix[i - 1][j - 1] == '1':
                    dp[j] = min(dp[j], dp[j - 1], prev) + 1
                    max_side = max(max_side, dp[j])
                else:
                    dp[j] = 0
                prev = temp
            prev = 0

        return max_side * max_side
```

### C++

```cpp
class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return 0;

        int rows = matrix.size(), cols = matrix[0].size();
        vector<int> dp(cols + 1, 0);
        int maxSide = 0;
        int prev = 0;

        for (int i = 1; i <= rows; i++) {
            for (int j = 1; j <= cols; j++) {
                int temp = dp[j];
                if (matrix[i - 1][j - 1] == '1') {
                    dp[j] = min({dp[j], dp[j - 1], prev}) + 1;
                    maxSide = max(maxSide, dp[j]);
                } else {
                    dp[j] = 0;
                }
                prev = temp;
            }
            prev = 0;
        }

        return maxSide * maxSide;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(m × n)
- **空间复杂度：** O(n)，仅使用一维数组

---

## 三种解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
|------|-----------|-----------|------|------|
| 暴力解 | O((mn)² × min(m,n)) | O(1) | 思路简单 | 超时，不可用 |
| 2D DP | O(mn) | O(mn) | 时间最优，易理解 | 空间较大 |
| 1D DP | O(mn) | O(n) | 时间空间双优 | 实现稍复杂 |

## 总结

- **核心状态：** `dp[i][j]` = 以 `(i,j)` 为右下角的最大正方形边长
- **状态转移：** `dp[i][j] = min(上, 左, 左上) + 1`
- **为什么取 min：** 正方形需要三个方向都能延伸，受最短边限制
- **空间优化技巧：** 2D DP → 1D DP，注意保存左上角的值
