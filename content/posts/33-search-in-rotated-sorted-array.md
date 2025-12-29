---
title: "33. 搜索旋转排序数组"
difficulty: "中等"
description: "整数数组 nums 按升序排列，数组中的值互不相同。在传递给函数之前，nums 在预先未知的某个下标 k 上进行了旋转。给你旋转后的数组 nums 和一个整数 target，如果 nums 中存在这个目标值 target，则返回它的下标，否则返回 -1。"
---

# 33. 搜索旋转排序数组

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

整数数组 `nums` 按升序排列，数组中的值**互不相同**。

在传递给函数之前，`nums` 在预先未知的某个下标 `k`（`0 <= k < nums.length`）上进行了**旋转**，使数组变为 `[nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]`（下标从 0 开始计数）。

例如，`[0,1,2,4,5,6,7]` 在下标 3 处经旋转后可能变为 `[4,5,6,7,0,1,2]`。

给你旋转后的数组 `nums` 和一个整数 `target`，如果 `nums` 中存在这个目标值 `target`，则返回它的下标，否则返回 `-1`。

你必须设计一个时间复杂度为 `O(log n)` 的算法解决此问题。

### 示例

```text
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
```

```text
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
```

```text
输入：nums = [1], target = 0
输出：-1
```

## 解法一：二分查找（推荐）

### 思路

旋转数组的特点是：将数组从中间分开，**至少有一半是有序的**。

二分查找的关键是判断哪一半有序，然后确定 target 在哪一半：

1. 取中间位置 `mid`
2. 判断哪一半有序：
   - 若 `nums[left] <= nums[mid]`：左半部分有序
   - 否则：右半部分有序
3. 判断 target 在有序的那一半还是另一半：
   - 在有序区间内：收缩到该区间
   - 不在有序区间内：收缩到另一区间
4. 重复直到找到 target 或区间为空

### Python

```python
from typing import List

def search(nums: List[int], target: int) -> int:
    """
    二分查找解法

    时间复杂度: O(log n)
    空间复杂度: O(1)
    """
    left, right = 0, len(nums) - 1

    while left <= right:
        mid = (left + right) // 2

        if nums[mid] == target:
            return mid

        # 判断哪一半有序
        if nums[left] <= nums[mid]:
            # 左半部分有序
            if nums[left] <= target < nums[mid]:
                # target 在左半部分
                right = mid - 1
            else:
                # target 在右半部分
                left = mid + 1
        else:
            # 右半部分有序
            if nums[mid] < target <= nums[right]:
                # target 在右半部分
                left = mid + 1
            else:
                # target 在左半部分
                right = mid - 1

    return -1
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            // 判断哪一半有序
            if (nums[left] <= nums[mid]) {
                // 左半部分有序
                if (nums[left] <= target && target < nums[mid]) {
                    // target 在左半部分
                    right = mid - 1;
                } else {
                    // target 在右半部分
                    left = mid + 1;
                }
            } else {
                // 右半部分有序
                if (nums[mid] < target && target <= nums[right]) {
                    // target 在右半部分
                    left = mid + 1;
                } else {
                    // target 在左半部分
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};
```

## 解法二：先找旋转点再二分

### 思路

分两步：
1. 使用二分查找找到旋转点（最小值的索引）
2. 根据 target 与 `nums[0]` 的大小关系，确定在哪一段进行二分查找

### Python

```python
def search_two_step(nums: List[int], target: int) -> int:
    """
    先找旋转点再二分

    时间复杂度: O(log n)
    空间复杂度: O(1)
    """
    n = len(nums)

    # 找到旋转点（最小值索引）
    left, right = 0, n - 1
    while left < right:
        mid = (left + right) // 2
        if nums[mid] > nums[right]:
            left = mid + 1
        else:
            right = mid

    pivot = left  # 旋转点索引

    # 确定在哪一段二分查找
    if target >= nums[0]:
        left, right = 0, pivot - 1 if pivot > 0 else 0
    else:
        left, right = pivot, n - 1

    # 标准二分查找
    while left <= right:
        mid = (left + right) // 2
        if nums[mid] == target:
            return mid
        elif nums[mid] < target:
            left = mid + 1
        else:
            right = mid - 1

    return -1
```

### C++

```cpp
int searchTwoStep(vector<int>& nums, int target) {
    int n = nums.size();

    // 找到旋转点（最小值索引）
    int left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    int pivot = left;  // 旋转点索引

    // 确定在哪一段二分查找
    if (target >= nums[0]) {
        left = 0;
        right = pivot > 0 ? pivot - 1 : 0;
    } else {
        left = pivot;
        right = n - 1;
    }

    // 标准二分查找
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return -1;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 一次二分 | O(log n) | O(1) | 代码简洁，一次遍历 |
| 两次二分 | O(log n) | O(1) | 思路清晰，分步处理 |

## 总结

- **解法一**直接在旋转数组上二分，核心是判断哪一半有序
- **解法二**先找旋转点，再做标准二分，思路更清晰但代码稍长
- 注意边界条件：`nums[left] <= nums[mid]` 中的等号很重要，处理只有两个元素的情况
- 这是二分查找的经典变体，考察对二分查找的深入理解
- 相关题目：153. 寻找旋转排序数组中的最小值、81. 搜索旋转排序数组 II
