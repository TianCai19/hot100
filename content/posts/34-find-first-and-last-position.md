---
title: "34. 在排序数组中查找元素的第一个和最后一个位置"
difficulty: "中等"
description: "给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。请你找出给定目标值在数组中的开始位置和结束位置。"
---

# 34. 在排序数组中查找元素的第一个和最后一个位置

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个按照非递减顺序排列的整数数组 `nums`，和一个目标值 `target`。请你找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

你必须设计并实现时间复杂度为 `O(log n)` 的算法解决此问题。

### 示例

```text
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
```

```text
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
```

```text
输入：nums = [], target = 0
输出：[-1,-1]
```

## 解法一：两次二分查找（推荐）

### 思路

由于数组是有序的，可以使用两次二分查找分别找到：
1. **左边界**：第一个等于 target 的位置
2. **右边界**：最后一个等于 target 的位置

关键点：
- 查找左边界时，找到 target 后继续向左搜索
- 查找右边界时，找到 target 后继续向右搜索

### Python

```python
from typing import List

def search_range(nums: List[int], target: int) -> List[int]:
    """
    两次二分查找解法

    时间复杂度: O(log n)
    空间复杂度: O(1)
    """
    def find_left(nums: List[int], target: int) -> int:
        """查找左边界（第一个等于 target 的位置）"""
        left, right = 0, len(nums) - 1
        result = -1
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                result = mid
                right = mid - 1  # 继续向左搜索
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return result

    def find_right(nums: List[int], target: int) -> int:
        """查找右边界（最后一个等于 target 的位置）"""
        left, right = 0, len(nums) - 1
        result = -1
        while left <= right:
            mid = (left + right) // 2
            if nums[mid] == target:
                result = mid
                left = mid + 1  # 继续向右搜索
            elif nums[mid] < target:
                left = mid + 1
            else:
                right = mid - 1
        return result

    return [find_left(nums, target), find_right(nums, target)]
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        return {findLeft(nums, target), findRight(nums, target)};
    }

private:
    // 查找左边界（第一个等于 target 的位置）
    int findLeft(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                result = mid;
                right = mid - 1;  // 继续向左搜索
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }

    // 查找右边界（最后一个等于 target 的位置）
    int findRight(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        int result = -1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) {
                result = mid;
                left = mid + 1;  // 继续向右搜索
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return result;
    }
};
```

## 解法二：使用标准库

### 思路

利用标准库的二分查找函数：
- Python: `bisect_left` 和 `bisect_right`
- C++: `lower_bound` 和 `upper_bound`

### Python

```python
import bisect

def search_range_bisect(nums: List[int], target: int) -> List[int]:
    """
    使用 bisect 模块

    时间复杂度: O(log n)
    空间复杂度: O(1)
    """
    left = bisect.bisect_left(nums, target)

    # 检查 target 是否存在
    if left >= len(nums) or nums[left] != target:
        return [-1, -1]

    right = bisect.bisect_right(nums, target) - 1
    return [left, right]
```

### C++

```cpp
#include <algorithm>

vector<int> searchRangeSTL(vector<int>& nums, int target) {
    auto left = lower_bound(nums.begin(), nums.end(), target);

    // 检查 target 是否存在
    if (left == nums.end() || *left != target) {
        return {-1, -1};
    }

    auto right = upper_bound(nums.begin(), nums.end(), target) - 1;
    return {(int)(left - nums.begin()), (int)(right - nums.begin())};
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 两次二分查找 | O(log n) | O(1) | 手写实现，理解二分本质 |
| 标准库方法 | O(log n) | O(1) | 代码简洁，推荐实际使用 |

## 总结

- 本题是二分查找的经典变体，需要找边界而非单一位置
- 关键在于找到 target 后不立即返回，而是继续搜索边界
- 注意处理 target 不存在的情况
- 实际工程中推荐使用标准库函数
