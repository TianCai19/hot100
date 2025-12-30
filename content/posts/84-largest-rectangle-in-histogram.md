---
title: "84. 柱状图中最大的矩形"
difficulty: "困难"
description: "给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子的宽度为 1，求在该柱状图中，能够勾勒出来的矩形的最大面积。"
---

# 84. 柱状图中最大的矩形

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子的宽度为 1，求在该柱状图中，能够勾勒出来的矩形的最大面积。

### 示例

```text
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形面积为 10（由高度为 5 和 6 的柱子组成）
```

### 图示

```
   ██
   ██   ██
   ██   ██
   ██ █ ██
   ██ █ ██
 █ ██ █ ██
 █ ██ █ ██
```

## 解法一：单调栈（推荐）

### 思路

使用单调栈维护一个递增的柱高序列：

1. 在柱状图两端各添加一个高度为 0 的柱子，避免边界判断
2. 使用单调递增栈存储柱子的索引
3. 遍历每个柱子：
   - 当当前柱子高度小于栈顶柱子高度时，弹出栈顶
   - 计算以弹出柱子为最小高度的矩形面积
   - 继续弹出直到栈顶高度小于当前高度
4. 将当前柱子索引压入栈中

关键公式：面积 = 弹出柱高度 × (当前索引 - 栈顶新索引 - 1)

### Python

```python
from typing import List

def largest_rectangle_area(heights: List[int]) -> int:
    """
    单调栈解法

    时间复杂度: O(n)，每个柱子最多入栈和出栈一次
    空间复杂度: O(n)，栈的大小
    """
    # 添加哨兵，避免边界判断
    heights.append(0)
    heights.insert(0, 0)

    stack = []  # 存储索引，栈中高度递增
    max_area = 0

    for i, h in enumerate(heights):
        # 当当前高度小于栈顶高度时，计算面积
        while stack and heights[stack[-1]] > h:
            height = heights[stack.pop()]  # 弹出柱子的高度
            # 计算宽度
            width = i - stack[-1] - 1 if stack else i
            max_area = max(max_area, height * width)
        stack.append(i)

    return max_area

# 测试
if __name__ == "__main__":
    print(largest_rectangle_area([2,1,5,6,2,3]))  # 输出: 10
    print(largest_rectangle_area([2,4]))  # 输出: 4
    print(largest_rectangle_area([0,0,0,0]))  # 输出: 0
    print(largest_rectangle_area([2,1,2]))  # 输出: 3
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // 添加哨兵，避免边界判断
        heights.push_back(0);
        heights.insert(heights.begin(), 0);

        stack<int> st;  // 存储索引，栈中高度递增
        int max_area = 0;

        for (int i = 0; i < heights.size(); i++) {
            // 当当前高度小于栈顶高度时，计算面积
            while (!st.empty() && heights[st.top()] > heights[i]) {
                int height = heights[st.top()];  // 弹出柱子的高度
                st.pop();
                // 计算宽度
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
    vector<int> heights1 = {2,1,5,6,2,3};
    cout << solution.largestRectangleArea(heights1) << endl;  // 输出: 10

    vector<int> heights2 = {2,4};
    cout << solution.largestRectangleArea(heights2) << endl;  // 输出: 4

    vector<int> heights3 = {0,0,0,0};
    cout << solution.largestRectangleArea(heights3) << endl;  // 输出: 0

    vector<int> heights4 = {2,1,2};
    cout << solution.largestRectangleArea(heights4) << endl;  // 输出: 3

    return 0;
}
```

## 解法二：暴力解法

### 思路

枚举所有可能的矩形：

1. 固定左边界，遍历右边界
2. 维护当前最小高度
3. 计算以该最小高度的矩形面积
4. 更新最大面积

时间复杂度较高，仅用于理解问题。

### Python

```python
def largest_rectangle_area_brute(heights: List[int]) -> int:
    """
    暴力解法

    时间复杂度: O(n^2)
    空间复杂度: O(1)
    """
    max_area = 0
    n = len(heights)

    for left in range(n):
        min_height = heights[left]
        for right in range(left, n):
            min_height = min(min_height, heights[right])
            max_area = max(max_area, min_height * (right - left + 1))

    return max_area
```

### C++

```cpp
int largestRectangleAreaBrute(vector<int>& heights) {
    int max_area = 0;
    int n = heights.size();

    for (int left = 0; left < n; left++) {
        int min_height = heights[left];
        for (int right = left; right < n; right++) {
            min_height = min(min_height, heights[right]);
            max_area = max(max_area, min_height * (right - left + 1));
        }
    }

    return max_area;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 单调栈 | O(n) | O(n) | 高效，推荐使用 |
| 暴力解法 | O(n^2) | O(1) | 易于理解，性能较差 |

**说明**：单调栈通过维护递增序列，避免了重复计算，将时间复杂度从 O(n^2) 优化到 O(n)。

## 总结

- **单调栈**是解决柱状图问题的经典方法，时间复杂度最优
- 哨兵技巧可以简化边界处理，避免空栈判断
- 关键在于理解弹出柱子时面积的计算方式
- 该方法可以扩展到其他类似问题（如最大矩形）
