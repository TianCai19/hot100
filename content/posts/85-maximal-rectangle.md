---
title: "85. 最大矩形"
difficulty: "困难"
description: "给定一个 m x n 的二进制矩阵，目标是找出只包含 1 的最大矩形，并返回其面积。"
---

# 85. 最大矩形

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给定一个 m x n 的二进制矩阵 `matrix`，目标是找出只包含 1 的最大矩形，并返回其面积。

### 示例

```text
输入：matrix = [
  ["1","0","1","0","0"],
  ["1","0","1","1","1"],
  ["1","1","1","1","1"],
  ["1","0","0","1","0"]
]
输出：6
解释：最大矩形面积为 6（如下所示）
```

### 图示

```
矩阵：
1 0 1 0 0
1 0 1 1 1
1 1 1 1 1
1 0 0 1 0

最大矩形：
  1 1 1
  1 1 1
  1 1 1
```

## 解法一：动态规划 + 单调栈（推荐）

### 思路

将二维矩阵问题转化为多个一维柱状图问题：

1. 对每一行，计算该行中每个位置向上的连续 1 的个数（ heights 数组）
2. 将问题转换为「84. 柱状图中最大的矩形」
3. 使用单调栈计算每行的最大矩形面积
4. 维护全局最大面积

### Python

```python
from typing import List

def maximal_rectangle(matrix: List[List[str]]) -> int:
    """
    动态规划 + 单调栈解法

    时间复杂度: O(m*n)，m 和 n 分别是矩阵的行数和列数
    空间复杂度: O(n)，存储 heights 数组和栈
    """
    if not matrix or not matrix[0]:
        return 0

    rows, cols = len(matrix), len(matrix[0])
    heights = [0] * cols  # 记录每列的连续1的数量
    max_area = 0

    for row in range(rows):
        # 更新 heights 数组
        for col in range(cols):
            if matrix[row][col] == '1':
                heights[col] += 1
            else:
                heights[col] = 0

        # 计算当前行的最大矩形面积
        max_area = max(max_area, largest_rectangle_in_histogram(heights))

    return max_area

def largest_rectangle_in_histogram(heights: List[int]) -> int:
    """柱状图最大矩形面积（来自第84题）"""
    heights.append(0)
    heights.insert(0, 0)

    stack = []
    max_area = 0

    for i, h in enumerate(heights):
        while stack and heights[stack[-1]] > h:
            height = heights[stack.pop()]
            width = i - stack[-1] - 1 if stack else i
            max_area = max(max_area, height * width)
        stack.append(i)

    return max_area

# 测试
if __name__ == "__main__":
    matrix1 = [
        ["1","0","1","0","0"],
        ["1","0","1","1","1"],
        ["1","1","1","1","1"],
        ["1","0","0","1","0"]
    ]
    print(maximal_rectangle(matrix1))  # 输出: 6

    matrix2 = [["0"]]
    print(maximal_rectangle(matrix2))  # 输出: 0

    matrix3 = [["1"]]
    print(maximal_rectangle(matrix3))  # 输出: 1

    matrix4 = [
        ["1","0","1","0"],
        ["1","0","1","1"],
        ["1","1","1","1"]
    ]
    print(maximal_rectangle(matrix4))  # 输出: 6
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) {
            return 0;
        }

        int rows = matrix.size();
        int cols = matrix[0].size();
        vector<int> heights(cols, 0);
        int max_area = 0;

        for (int row = 0; row < rows; row++) {
            // 更新 heights 数组
            for (int col = 0; col < cols; col++) {
                if (matrix[row][col] == '1') {
                    heights[col] += 1;
                } else {
                    heights[col] = 0;
                }
            }

            // 计算当前行的最大矩形面积
            max_area = max(max_area, largestRectangleArea(heights));
        }

        return max_area;
    }

private:
    int largestRectangleArea(vector<int>& heights) {
        // 添加哨兵
        heights.push_back(0);
        heights.insert(heights.begin(), 0);

        stack<int> st;
        int max_area = 0;

        for (int i = 0; i < heights.size(); i++) {
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int height = heights[st.top()];
                st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                max_area = max(max_area, height * width);
            }
            st.push(i);
        }

        return max_area;
    }
};

// 测试
int main() {
    Solution solution;
    vector<vector<char>> matrix1 = {
        {'1','0','1','0','0'},
        {'1','0','1','1','1'},
        {'1','1','1','1','1'},
        {'1','0','0','1','0'}
    };
    cout << solution.maximalRectangle(matrix1) << endl;  // 输出: 6

    vector<vector<char>> matrix2 = {{'0'}};
    cout << solution.maximalRectangle(matrix2) << endl;  // 输出: 0

    vector<vector<char>> matrix3 = {{'1'}};
    cout << solution.maximalRectangle(matrix3) << endl;  // 输出: 1

    vector<vector<char>> matrix4 = {
        {'1','0','1','0'},
        {'1','0','1','1'},
        {'1','1','1','1'}
    };
    cout << solution.maximalRectangle(matrix4) << endl;  // 输出: 6

    return 0;
}
```

## 解法二：暴力解法

### 思路

枚举所有可能的矩形：

1. 固定左上角 (row1, col1)
2. 固定右下角 (row2, col2)
3. 检查矩形内是否全为 1
4. 更新最大面积

时间复杂度较高，仅用于理解问题。

### Python

```python
def maximal_rectangle_brute(matrix: List[List[str]]) -> int:
    """
    暴力解法

    时间复杂度: O(m^2 * n^2)
    空间复杂度: O(1)
    """
    if not matrix or not matrix[0]:
        return 0

    rows, cols = len(matrix), len(matrix[0])
    max_area = 0

    for row1 in range(rows):
        for col1 in range(cols):
            if matrix[row1][col1] == '0':
                continue
            for row2 in range(row1, rows):
                for col2 in range(col1, cols):
                    # 检查矩形内是否全为1
                    all_ones = True
                    for r in range(row1, row2 + 1):
                        for c in range(col1, col2 + 1):
                            if matrix[r][c] == '0':
                                all_ones = False
                                break
                        if not all_ones:
                            break
                    if all_ones:
                        area = (row2 - row1 + 1) * (col2 - col1 + 1)
                        max_area = max(max_area, area)

    return max_area
```

## 解法三：暴力优化

### 思路

优化暴力解法：

1. 使用前缀和快速计算矩形内1的个数
2. 或者使用动态规划预处理每个位置为右下角的最大矩形

### Python

```python
def maximal_rectangle_dp(matrix: List[List[str]]) -> int:
    """
    动态规划预处理解法

    时间复杂度: O(m^2 * n)
    空间复杂度: O(m * n)
    """
    if not matrix or not matrix[0]:
        return 0

    rows, cols = len(matrix), len(matrix[0])
    # dp[row][col] 记录以 (row, col) 为右下角的连续1的左边界
    left = [[0] * cols for _ in range(rows)]
    max_area = 0

    for row in range(rows):
        for col in range(cols):
            if matrix[row][col] == '1':
                if col == 0:
                    left[row][col] = 0
                else:
                    left[row][col] = left[row][col - 1] + 1

                # 向上扩展，计算以 (row, col) 为右下角的最大矩形
                min_width = left[row][col]
                for k in range(row, -1, -1):
                    min_width = min(min_width, left[k][col])
                    if min_width == 0:
                        break
                    area = min_width * (row - k + 1)
                    max_area = max(max_area, area)

    return max_area
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 + 单调栈 | O(m*n) | O(n) | 高效，推荐使用 |
| 暴力解法 | O(m^2 * n^2) | O(1) | 易于理解，性能极差 |
| 暴力优化 | O(m^2 * n) | O(m*n) | 性能中等，较复杂 |

**说明**：解法一将二维问题转化为多个一维问题，时间复杂度最优。

## 总结

- 将**二维矩阵问题转化为一维柱状图问题**，这是关键思路
- 结合第84题的「柱状图中最大矩形」解法
- 使用**动态规划**维护每列的连续1的个数
- 单调栈在每行独立计算最大矩形面积
- 该思路可以应用到其他矩阵问题（如最大正方形）
