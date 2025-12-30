---
title: "53. 最大子数组和"
difficulty: "中等"
description: "给你一个整数数组 nums，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。"
---

# 53. 最大子数组和

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个整数数组 `nums`，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。

如果数组所有数字都是负数，最大子数组和为数组中的最大元素。

### 示例

```text
输入: nums = [-2,1,-3,4,-1,2,1,-5,4]
输出: 6
解释: 连续子数组 [4,-1,2,1] 的和最大，为 6
```

```text
输入: nums = [1]
输出: 1
```

```text
输入: nums = [5,4,-1,7,8]
输出: 23
```

## 解法一：Kadane算法（推荐）

### 思路

Kadane算法是解决最大子数组和问题的经典动态规划解法：

1. 定义 `dp[i]` 为以 `nums[i]` 结尾的最大子数组和
2. 状态转移方程：`dp[i] = max(nums[i], dp[i-1] + nums[i])`
   - 要么单独成新子数组（nums[i]）
   - 要么接续前一个子数组（dp[i-1] + nums[i]）
3. 维护全局最大值即为结果
4. 可以优化为 O(1) 空间复杂度

### Python

```python
from typing import List

def max_sub_array(nums: List[int]) -> int:
    """
    Kadane算法解法

    时间复杂度: O(n)，其中 n 是数组长度
    空间复杂度: O(1)
    """
    # 初始化当前最大和为第一个元素
    current_sum = nums[0]
    # 初始化全局最大和为第一个元素
    max_sum = nums[0]

    # 从第二个元素开始遍历
    for i in range(1, len(nums)):
        # 当前和要么是当前元素，要么是之前的和加上当前元素
        current_sum = max(nums[i], current_sum + nums[i])
        # 更新全局最大和
        max_sum = max(max_sum, current_sum)

    return max_sum

# 测试
if __name__ == "__main__":
    print(max_sub_array([-2,1,-3,4,-1,2,1,-5,4]))  # 输出: 6
    print(max_sub_array([1]))  # 输出: 1
    print(max_sub_array([5,4,-1,7,8]))  # 输出: 23
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // 初始化当前最大和为第一个元素
        int current_sum = nums[0];
        // 初始化全局最大和为第一个元素
        int max_sum = nums[0];

        // 从第二个元素开始遍历
        for (size_t i = 1; i < nums.size(); i++) {
            // 当前和要么是当前元素，要么是之前的和加上当前元素
            current_sum = max(nums[i], current_sum + nums[i]);
            // 更新全局最大和
            max_sum = max(max_sum, current_sum);
        }

        return max_sum;
    }
};

// 测试
int main() {
    vector<int> nums1 = {-2,1,-3,4,-1,2,1,-5,4};
    vector<int> nums2 = {1};
    vector<int> nums3 = {5,4,-1,7,8};

    Solution solution;
    cout << solution.maxSubArray(nums1) << endl;  // 输出: 6
    cout << solution.maxSubArray(nums2) << endl;  // 输出: 1
    cout << solution.maxSubArray(nums3) << endl;  // 输出: 23

    return 0;
}
```

## 解法二：动态规划

### 思路

标准的动态规划解法，使用 dp 数组存储状态：

1. 定义 `dp[i]` 为以 `nums[i]` 结尾的最大子数组和
2. `dp[0] = nums[0]`
3. `dp[i] = max(nums[i], dp[i-1] + nums[i])`
4. 返回 `max(dp)`

### Python

```python
def max_sub_array_dp(nums: List[int]) -> int:
    """
    动态规划解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    if not nums:
        return 0

    n = len(nums)
    dp = [0] * n
    dp[0] = nums[0]
    max_sum = dp[0]

    for i in range(1, n):
        dp[i] = max(nums[i], dp[i-1] + nums[i])
        max_sum = max(max_sum, dp[i])

    return max_sum
```

### C++

```cpp
int maxSubArrayDP(vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int n = nums.size();
    vector<int> dp(n);
    dp[0] = nums[0];
    int max_sum = dp[0];

    for (int i = 1; i < n; i++) {
        dp[i] = max(nums[i], dp[i-1] + nums[i]);
        max_sum = max(max_sum, dp[i]);
    }

    return max_sum;
}
```

## 解法三：分治法

### 思路

将数组分为左右两部分，最大子数组和可能在：
1. 左边部分
2. 右边部分
3. 跨越中间部分的子数组

### Python

```python
def max_sub_array_divide(nums: List[int]) -> int:
    """
    分治法解法

    时间复杂度: O(n*log(n))
    空间复杂度: O(log(n))，递归栈
    """
    def helper(left: int, right: int) -> tuple:
        # 返回 (最大子数组和, 前缀最大和, 后缀最大和, 总和)
        if left == right:
            return (nums[left], nums[left], nums[left], nums[left])

        mid = (left + right) // 2
        left_sum = helper(left, mid)
        right_sum = helper(mid + 1, right)

        # 合并结果
        cross_sum = left_sum[2] + right_sum[1]
        max_sum = max(left_sum[0], right_sum[0], cross_sum)

        return (max_sum, max(left_sum[1], left_sum[3] + right_sum[1]),
                max(right_sum[2], right_sum[3] + left_sum[2]),
                left_sum[3] + right_sum[3])

    return helper(0, len(nums) - 1)[0]
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| Kadane算法 | O(n) | O(1) | 最优解，工业级标准 |
| 动态规划 | O(n) | O(n) | 直观易懂，可扩展 |
| 分治法 | O(n*log(n)) | O(log(n)) | 思想经典，性能一般 |

**说明**：
- Kadane算法是最佳选择，时间 O(n)，空间 O(1)
- 动态规划思路清晰，便于理解问题本质
- 分治法展示了递归思想，但实际性能不如前两者

## 总结

- **Kadane算法**是解决最大子数组和的最优方法，必须掌握
- 核心思想：每个位置的最优解只依赖于前一个位置
- 处理全负数数组：算法自动选择最大的单个元素
- 应用广泛：股票买卖、最大子矩阵和等问题都基于此思想
