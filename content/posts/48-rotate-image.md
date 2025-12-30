---
title: "48. 旋转图像"
difficulty: "中等"
description: "给定一个 n × n 的二维矩阵 matrix 表示一个图像，将图像顺时针旋转 90 度。必须原地旋转图像。"
---

# 48. 旋转图像

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个 `n × n` 的二维矩阵 `matrix` 表示一个图像，将图像顺时针旋转 90 度。

必须**原地**旋转图像。

### 示例

```text
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
```

```text
输入：matrix = [[1,2],[3,4]]
输出：[[3,1],[4,2]]
```

## 解法一：转置+翻转（推荐）

### 思路

分两步进行：

1. **转置矩阵**：将矩阵的行和列互换
   - 对角线元素保持不变
   - `matrix[i][j]` 与 `matrix[j][i]` 交换

2. **水平翻转**：将转置后的矩阵水平翻转
   - 每行内的元素左右对称交换
   - `matrix[i][j]` 与 `matrix[i][n-1-j]` 交换

### Python

```python
from typing import List

def rotate(matrix: List[List[int]]) -> None:
    """
    转置+翻转解法

    时间复杂度: O(n^2)
    空间复杂度: O(1)
    """
    n = len(matrix)

    # 第一步：转置矩阵（沿对角线交换）
    for i in range(n):
        for j in range(i + 1, n):
            matrix[i][j], matrix[j][i] = matrix[j][i], matrix[i][j]

    # 第二步：水平翻转
    for i in range(n):
        for j in range(n // 2):
            matrix[i][j], matrix[i][n - 1 - j] = matrix[i][n - 1 - j], matrix[i][j]
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // 第一步：转置矩阵（沿对角线交换）
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }

        // 第二步：水平翻转
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n / 2; j++) {
                swap(matrix[i][j], matrix[i][n - 1 - j]);
            }
        }
    }
};
```

## 解法二：环状旋转

### 思路

将矩阵分为若干个环，逐层旋转：

1. 外层到内层，每层是一个环
2. 每个环由 4 条边组成，共 `n-2*layer` 个元素
3. 每次旋转 4 个元素，注意边界条件

### Python

```python
def rotate_circular(matrix: List[List[int]]) -> None:
    """
    环状旋转解法

    时间复杂度: O(n^2)
    空间复杂度: O(1)
    """
    n = len(matrix)
    layer = 0

    # 从外层到内层，逐层旋转
    while layer < n // 2:
        first, last = layer, n - 1 - layer

        # 旋转当前环上的所有元素
        for i in range(first, last):
            # 保存上边的元素
            top = matrix[first][i]

            # 左边 -> 上边
            matrix[first][i] = matrix[last - i][first]

            # 下边 -> 左边
            matrix[last - i][first] = matrix[last][last - i]

            # 右边 -> 下边
            matrix[last][last - i] = matrix[i][last]

            # 上边 -> 右边
            matrix[i][last] = top

        layer += 1
```

### C++

```cpp
void rotateCircular(vector<vector<int>>& matrix) {
    int n = matrix.size();
    int layer = 0;

    // 从外层到内层，逐层旋转
    while (layer < n / 2) {
        int first = layer;
        int last = n - 1 - layer;

        // 旋转当前环上的所有元素
        for (int i = first; i < last; i++) {
            int offset = i - first;

            // 保存上边的元素
            int top = matrix[first][i];

            // 左边 -> 上边
            matrix[first][i] = matrix[last - offset][first];

            // 下边 -> 左边
            matrix[last - offset][first] = matrix[last][last - offset];

            // 右边 -> 下边
            matrix[last][last - offset] = matrix[i][last];

            // 上边 -> 右边
            matrix[i][last] = top;
        }

        layer++;
    }
}
```

## 解法三：原地旋转（按元素计算）

### 思路

对于任意位置 `(i, j)` 的元素，旋转 90 度后新位置为 `(j, n-1-i)`：

1. 分层处理，避免重复旋转
2. 每层有 4 个位置需要交换
3. 从外向内逐层旋转

### Python

```python
def rotate_inplace(matrix: List[List[int]]) -> None:
    """
    原地旋转解法

    时间复杂度: O(n^2)
    空间复杂度: O(1)
    """
    n = len(matrix)

    for i in range(n // 2):
        for j in range(i, n - 1 - i):
            # 保存当前元素
            temp = matrix[i][j]

            # (j, n-1-i) -> (i, j)
            matrix[i][j] = matrix[n - 1 - j][i]

            # (n-1-i, n-1-j) -> (j, n-1-i)
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j]

            # (n-1-j, i) -> (n-1-i, n-1-j)
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i]

            # temp -> (n-1-j, i)
            matrix[j][n - 1 - i] = temp
```

### C++

```cpp
void rotateInplace(vector<vector<int>>& matrix) {
    int n = matrix.size();

    for (int i = 0; i < n / 2; i++) {
        for (int j = i; j < n - 1 - i; j++) {
            // 保存当前元素
            int temp = matrix[i][j];

            // (j, n-1-i) -> (i, j)
            matrix[i][j] = matrix[n - 1 - j][i];

            // (n-1-i, n-1-j) -> (j, n-1-i)
            matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];

            // (n-1-j, i) -> (n-1-i, n-1-j)
            matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];

            // temp -> (n-1-j, i)
            matrix[j][n - 1 - i] = temp;
        }
    }
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 转置+翻转 | O(n^2) | O(1) | 思路清晰，代码简洁 |
| 环状旋转 | O(n^2) | O(1) | 直观理解旋转过程 |
| 原地旋转 | O(n^2) | O(1) | 数学公式计算位置 |

## 总结

- **转置+翻转**是最常用的方法，代码简洁易懂
- **环状旋转**直观展示了矩阵旋转的物理过程
- **原地旋转**利用数学公式直接计算元素位置
- 所有方法都实现了 O(1) 空间复杂度，满足原地旋转要求
- 旋转矩阵是数组操作的经典题目，注意边界条件的处理
- 理解矩阵的坐标变换规律是解决这类问题的关键
