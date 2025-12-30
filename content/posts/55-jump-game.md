---
title: "55. 跳跃游戏"
difficulty: "中等"
description: "给你一个非负整数数组 nums，你最初位于数组的第一个下标。数组中的每个元素代表你在该位置可以跳跃的最大长度。判断你是否能够到达最后一个下标。"
---

# 55. 跳跃游戏

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个非负整数数组 `nums`，你最初位于数组的第一个下标。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

### 示例

```text
输入: nums = [2,3,1,1,4]
输出: true
解释: 可以先跳 1 步，从下标 0 到下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
```

```text
输入: nums = [3,2,1,0,4]
输出: false
解释: 无论怎样，总会到达下标为 3 的位置。但该位置的最大跳跃长度是 0 ，所以永远不可能到达最后一个下标。
```

## 解法一：贪心算法（推荐）

### 思路

贪心算法是解决跳跃游戏问题的最优方法：

1. 维护一个变量 `reach` 表示当前能到达的最远位置
2. 遍历数组，更新 `reach = max(reach, i + nums[i])`
3. 如果当前位置 `i` 超过了 `reach`，说明无法到达当前位置，更无法到达终点
4. 如果 `reach` 达到或超过数组末尾，返回 true

### Python

```python
from typing import List

def can_jump(nums: List[int]) -> bool:
    """
    贪心算法解法

    时间复杂度: O(n)，其中 n 是数组长度
    空间复杂度: O(1)
    """
    if not nums:
        return True

    n = len(nums)
    # 当前能到达的最远位置
    reach = 0

    for i in range(n):
        # 如果当前位置超出了当前最远可达位置，则失败
        if i > reach:
            return False

        # 更新最远可达位置
        reach = max(reach, i + nums[i])

        # 如果最远可达位置已经能到达终点，直接返回 true
        if reach >= n - 1:
            return True

    return reach >= n - 1

# 测试
if __name__ == "__main__":
    print(can_jump([2,3,1,1,4]))  # 输出: True
    print(can_jump([3,2,1,0,4]))  # 输出: False
    print(can_jump([0]))  # 输出: True
    print(can_jump([2,0,0]))  # 输出: True
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        if (nums.empty()) {
            return true;
        }

        int n = nums.size();
        // 当前能到达的最远位置
        int reach = 0;

        for (int i = 0; i < n; i++) {
            // 如果当前位置超出了当前最远可达位置，则失败
            if (i > reach) {
                return false;
            }

            // 更新最远可达位置
            reach = max(reach, i + nums[i]);

            // 如果最远可达位置已经能到达终点，直接返回 true
            if (reach >= n - 1) {
                return true;
            }
        }

        return reach >= n - 1;
    }
};

// 测试
int main() {
    vector<int> nums1 = {2,3,1,1,4};
    vector<int> nums2 = {3,2,1,0,4};
    vector<int> nums3 = {0};
    vector<int> nums4 = {2,0,0};

    Solution solution;
    cout << boolalpha;
    cout << solution.canJump(nums1) << endl;  // 输出: true
    cout << solution.canJump(nums2) << endl;  // 输出: false
    cout << solution.canJump(nums3) << endl;  // 输出: true
    cout << solution.canJump(nums4) << endl;  // 输出: true

    return 0;
}
```

## 解法二：动态规划

### 思路

使用动态规划从后往前思考：

1. 定义 `dp[i]` 表示能否到达位置 `i`
2. `dp[n-1] = true`（终点总是可达）
3. 从右往左遍历，对于每个位置 `i`，检查是否能跳到任意可达的位置 `j`
4. 如果能找到这样的 `j`，则 `dp[i] = true`

### Python

```python
def can_jump_dp(nums: List[int]) -> bool:
    """
    动态规划解法

    时间复杂度: O(n^2)
    空间复杂度: O(n)
    """
    if not nums:
        return True

    n = len(nums)
    # dp[i] 表示能否到达位置 i
    dp = [False] * n
    dp[n - 1] = True  # 终点总是可达

    for i in range(n - 2, -1, -1):
        # 检查从位置 i 能否跳到任意可达的位置
        for j in range(i + 1, min(i + nums[i] + 1, n)):
            if dp[j]:
                dp[i] = True
                break

    return dp[0]
```

### C++

```cpp
bool canJumpDP(vector<int>& nums) {
    if (nums.empty()) {
        return true;
    }

    int n = nums.size();
    vector<bool> dp(n, false);
    dp[n - 1] = true;  // 终点总是可达

    for (int i = n - 2; i >= 0; i--) {
        // 检查从位置 i 能否跳到任意可达的位置
        for (int j = i + 1; j <= min(i + nums[i], n - 1); j++) {
            if (dp[j]) {
                dp[i] = true;
                break;
            }
        }
    }

    return dp[0];
}
```

## 解法三：暴力递归（超时）

### 思路

尝试所有可能的跳跃路径：

1. 从当前位置出发，尝试跳到所有可能的位置
2. 使用递归遍历每条路径
3. 如果能到达终点，返回 true

这种方法会超时，仅作为思路参考。

### Python

```python
def can_jump_bruteforce(nums: List[int]) -> bool:
    """
    暴力递归解法（会超时）

    时间复杂度: O(n^n)
    空间复杂度: O(n)
    """
    from functools import lru_cache

    n = len(nums)

    @lru_cache(None)
    def can_reach(pos: int) -> bool:
        if pos >= n - 1:
            return True

        max_jump = min(nums[pos], n - pos - 1)
        for jump in range(1, max_jump + 1):
            if can_reach(pos + jump):
                return True

        return False

    return can_reach(0)
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 贪心算法 | O(n) | O(1) | 最优解，面试首选 |
| 动态规划 | O(n^2) | O(n) | 直观但性能较差 |
| 暴力递归 | O(n^n) | O(n) | 会超时，仅作思路参考 |

**说明**：
- 贪心算法是最佳选择，一次遍历即可解决问题
- 动态规划虽然直观，但 O(n^2) 的时间复杂度在大数据下会超时
- 暴力递归指数级时间复杂度，实际不可用

## 总结

- **贪心算法**是解决跳跃游戏的最优方法，时间 O(n)，空间 O(1)
- 核心思想：始终保持当前能到达的最远位置
- 关键判断：当前位置超出最远可达位置时直接返回失败
- 应用广泛：类似"能否达到"的问题都可以尝试贪心思路
