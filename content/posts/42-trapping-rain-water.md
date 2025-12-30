---
title: "42. 接雨水"
difficulty: "困难"
description: "给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。"
---

# 42. 接雨水

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给定 `n` 个非负整数表示每个宽度为 `1` 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。

### 示例

```text
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：6 框住的雨水（蓝色部分）表示它们可以接的雨水容量。
```

下面是由数组 `[0,1,0,2,1,0,1,3,2,1,2,1]` 表示的高度图：

```text
    #
    #   #     #
  # # #   # # # #
# # # # # # # # # # # #
0 1 0 2 1 0 1 3 2 1 2 1
```

**可视化说明：**
- **#** 表示柱子（土地高度）
- **蓝色区域**表示可以接的雨水
- 柱子的高度就是数组中对应位置的值

**详细的接水过程：**

```text
位置:  0 1 2 3 4 5 6 7 8 9 10 11
高度:  0 1 0 2 1 0 1 3 2 1  2  1
接水:  ^ 1 ^ 1 1 ^ 1 1 1 1  1  1
       |  | | | | | | | | |  |  |
       1  1 1 1 1 1 1 1 1  1  1

总接水量 = 1+1+1+1+1+1 = 6
```

### 接水原理

每个位置能接多少雨水，取决于它左右两侧的最高柱子：
- 对于位置2（值为0），左边最高是1，右边最高是2，所以能接 `min(1,2) - 0 = 1` 单位水
- 对于位置5（值为0），左边最高是2，右边最高是3，所以能接 `min(2,3) - 0 = 2` 单位水
- ... 以此类推

```text
输入：height = [4,2,0,3,2,5]
输出：9
```

## 解法一：双指针（推荐）

### 思路

使用左右双指针遍历数组，在每个位置计算该位置能接的雨水：

1. 维护左右两个指针 `left` 和 `right`，分别指向数组两端
2. 维护左右两侧的最大高度 `left_max` 和 `right_max`
3. 移动指针时，矮的一侧必然可以确定其储水量：
   - 如果 `left_max <= right_max`，则左侧当前位置的储水量为 `left_max - height[left]`
   - 否则，右侧当前位置的储水量为 `right_max - height[right]`

### Python

```python
from typing import List

class Solution:
    def trap(self, height: List[int]) -> int:
        """
        双指针解法

        时间复杂度: O(n)
        空间复杂度: O(1)
        """
        if not height:
            return 0

        left, right = 0, len(height) - 1
        left_max, right_max = 0, 0
        water = 0

        while left < right:
            # 左侧最大高度
            if height[left] < height[right]:
                if height[left] >= left_max:
                    left_max = height[left]
                else:
                    water += left_max - height[left]
                left += 1
            else:
                # 右侧最大高度
                if height[right] >= right_max:
                    right_max = height[right]
                else:
                    water += right_max - height[right]
                right -= 1

        return water
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.empty()) {
            return 0;
        }

        int left = 0, right = height.size() - 1;
        int left_max = 0, right_max = 0;
        int water = 0;

        while (left < right) {
            // 左侧最大高度
            if (height[left] < height[right]) {
                if (height[left] >= left_max) {
                    left_max = height[left];
                } else {
                    water += left_max - height[left];
                }
                left++;
            } else {
                // 右侧最大高度
                if (height[right] >= right_max) {
                    right_max = height[right];
                } else {
                    water += right_max - height[right];
                }
                right--;
            }
        }

        return water;
    }
};
```

## 解法二：单调栈

### 思路

使用单调递减栈来保存柱子的索引：

1. 遍历数组，使用栈保存递减的柱子高度
2. 当遇到比栈顶更高的柱子时，说明形成了凹陷
3. 计算栈顶柱子能接的雨水

### Python

```python
def trap_stack(height: List[int]) -> int:
    """
    单调栈解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    if not height:
        return 0

    stack = []  # 存储索引，栈中高度递减
    water = 0

    for i, h in enumerate(height):
        # 当前柱子比栈顶高，形成凹陷
        while stack and h > height[stack[-1]]:
            top = stack.pop()
            if not stack:
                break

            # 距离
            distance = i - stack[-1] - 1
            # 高度差
            bounded_height = min(h, height[stack[-1]]) - height[top]
            water += distance * bounded_height

        stack.append(i)

    return water
```

### C++

```cpp
int trapStack(vector<int>& height) {
    if (height.empty()) {
        return 0;
    }

    stack<int> st;  // 存储索引，栈中高度递减
    int water = 0;

    for (int i = 0; i < height.size(); i++) {
        // 当前柱子比栈顶高，形成凹陷
        while (!st.empty() && height[i] > height[st.top()]) {
            int top = st.top();
            st.pop();
            if (st.empty()) {
                break;
            }

            // 距离
            int distance = i - st.top() - 1;
            // 高度差
            int bounded_height = min(height[i], height[st.top()]) - height[top];
            water += distance * bounded_height;
        }

        st.push(i);
    }

    return water;
}
```

## 解法三：动态规划

### 思路

预处理每个位置左右的最大高度：

1. 从左到右遍历，计算每个位置左侧的最大高度
2. 从右到左遍历，计算每个位置右侧的最大高度
3. 每个位置能接的雨水为 `min(left_max, right_max) - height[i]`

### Python

```python
def trap_dp(height: List[int]) -> int:
    """
    动态规划解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    if not height:
        return 0

    n = len(height)
    left_max = [0] * n
    right_max = [0] * n
    water = 0

    # 左侧最大高度
    left_max[0] = height[0]
    for i in range(1, n):
        left_max[i] = max(left_max[i - 1], height[i])

    # 右侧最大高度
    right_max[n - 1] = height[n - 1]
    for i in range(n - 2, -1, -1):
        right_max[i] = max(right_max[i + 1], height[i])

    # 计算每个位置的储水量
    for i in range(n):
        water += min(left_max[i], right_max[i]) - height[i]

    return water
```

### C++

```cpp
int trapDP(vector<int>& height) {
    if (height.empty()) {
        return 0;
    }

    int n = height.size();
    vector<int> left_max(n), right_max(n);
    int water = 0;

    // 左侧最大高度
    left_max[0] = height[0];
    for (int i = 1; i < n; i++) {
        left_max[i] = max(left_max[i - 1], height[i]);
    }

    // 右侧最大高度
    right_max[n - 1] = height[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        right_max[i] = max(right_max[i + 1], height[i]);
    }

    // 计算每个位置的储水量
    for (int i = 0; i < n; i++) {
        water += min(left_max[i], right_max[i]) - height[i];
    }

    return water;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 双指针 | O(n) | O(1) | 最优解，空间效率高 |
| 单调栈 | O(n) | O(n) | 直观但空间开销大 |
| 动态规划 | O(n) | O(n) | 容易理解，预处理冗余 |

## 总结

- **双指针**是最优解法，空间复杂度为 O(1)，适合对空间要求严格的场景
- **单调栈**和**动态规划**都容易理解，但需要额外的 O(n) 空间
- 三种解法的时间复杂度都是 O(n)，实际性能差异主要体现在空间使用上
- 关键思路是利用每个位置左右的最大高度来计算储水量
