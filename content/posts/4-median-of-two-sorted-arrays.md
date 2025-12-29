---
title: "4. 寻找两个正序数组的中位数"
difficulty: "困难"
description: "给定两个大小分别为 m 和 n 的正序数组 nums1 和 nums2，请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 O(log (m+n))。"
---

# 4. 寻找两个正序数组的中位数

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给定两个大小分别为 `m` 和 `n` 的正序（非递减）数组 `nums1` 和 `nums2`，请你找出这两个正序数组的中位数，并且要求算法的时间复杂度为 `O(log (m+n))`。

你可以假设 `nums1` 和 `nums2` 不会同时为空。

### 示例

```text
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并后的数组是 [1,2,3] ，中位数是 2 。
```

```text
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并后的数组是 [1,2,3,4] ，中位数是 (2 + 3) / 2 = 2.5 。
```

## 解法一：归并/模拟 + 二分查找思路（直观 vs log）

### 思路

- **直观归并**：两个数组均为有序，最简单的处理方式是合并得到一个大数组，再取中位数位置。但合并后需要额外 `O(m+n)` 空间，时间是 `O(m+n)`。
- **指针模拟**：只需维护两个下标指针 `i`/`j`，每次推进较小指针，直到走到中位数位置即可，空间为 `O(1)`，但时间仍是 `O(m+n)`。
- **二分查找**：由于要求 `O(log(m+n))`，我们转而将问题变换成“寻找第 k 小” 的元素，其中 `k=(m+n)/2` 或 `(m+n)/2+1`。每次比较两个数组的第 `k/2` 个元素，排除掉至少 `k/2` 个不可能是第 k 小的值，查找范围迅速减半，达到 `O(log(m+n))`。

下面的 Mermaid 图示简化展示了 A[k/2−1] 与 B[k/2−1] 比较后，如何排除红框区域，保留蓝框部分的过程。

<svg viewBox="0 0 760 220" role="img" aria-label="二分排除示意" xmlns="http://www.w3.org/2000/svg">
  <rect x="10" y="20" width="60" height="40" rx="6" fill="#ef4444" stroke="#fff" strokeWidth="2" />
  <rect x="80" y="20" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <rect x="150" y="20" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <rect x="220" y="20" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <text x="35" y="45" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">1</text>
  <text x="105" y="45" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">3</text>
  <text x="175" y="45" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">4</text>
  <text x="245" y="45" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">9</text>
  <text x="-2" y="45" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">A</text>

  <rect x="10" y="90" width="60" height="40" rx="6" fill="#ef4444" stroke="#fff" strokeWidth="2" />
  <rect x="80" y="90" width="60" height="40" rx="6" fill="#ef4444" stroke="#fff" strokeWidth="2" />
  <rect x="150" y="90" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <rect x="220" y="90" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <rect x="290" y="90" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <rect x="360" y="90" width="60" height="40" rx="6" fill="#22d3ee" stroke="#fff" strokeWidth="2" />
  <text x="35" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">1</text>
  <text x="105" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">2</text>
  <text x="175" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">3</text>
  <text x="245" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">4</text>
  <text x="315" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">5</text>
  <text x="385" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">6</text>
  <text x="-2" y="115" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">B</text>

  <text x="120" y="165" fill="#e5e7eb" fontSize="14" fontFamily="sans-serif">比较 k/2 位置 ➜ 排除 B[0..k/2-1]</text>
</svg>

### 归并模拟代码

### Python

```python
from typing import List

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        total_len = len(nums1) + len(nums2)
        target = total_len // 2
        i = j = 0
        prev = curr = 0

        for _ in range(target + 1):
            prev = curr
            if i < len(nums1) and (j >= len(nums2) or nums1[i] <= nums2[j]):
                curr = nums1[i]
                i += 1
            else:
                curr = nums2[j]
                j += 1

        if total_len % 2:
            return float(curr)
        return (prev + curr) / 2
```

### C++

```cpp
#include <vector>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int total = nums1.size() + nums2.size();
        int target = total / 2;
        int i = 0, j = 0;
        int prev = 0, curr = 0;

        for (int k = 0; k <= target; ++k) {
            prev = curr;
            if (i < nums1.size() && (j >= nums2.size() || nums1[i] <= nums2[j])) {
                curr = nums1[i++];
            } else {
                curr = nums2[j++];
            }
        }

        if (total % 2) {
            return curr;
        }
        return (prev + curr) / 2.0;
    }
};
```

### 复杂度

| 项目 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 归并/指针 | O(m+n) | O(1) |
| 二分化 k | O(log(m+n)) | O(1) |

## 解法二：划分数组（等价于二分查找，但描述更直观）

## 解法二：二分查找分割线

### 思路

使用二分查找在较短的数组上寻找一个分割，使得左右两边元素数量相等，并且左边最大值不大于右边最小值。该方法满足题目要求的 `O(log(min(m,n)))`，适用于性能敏感场景。

### Python

```python
from typing import List
import sys

class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        if len(nums1) > len(nums2):
            nums1, nums2 = nums2, nums1

        m, n = len(nums1), len(nums2)
        left, right = 0, m

        while left <= right:
            i = (left + right) // 2
            j = (m + n + 1) // 2 - i
            max_left_x = nums1[i - 1] if i > 0 else -sys.maxsize
            min_right_x = nums1[i] if i < m else sys.maxsize
            max_left_y = nums2[j - 1] if j > 0 else -sys.maxsize
            min_right_y = nums2[j] if j < n else sys.maxsize

            if max_left_x <= min_right_y and max_left_y <= min_right_x:
                if (m + n) % 2:
                    return float(max(max_left_x, max_left_y))
                return (max(max_left_x, max_left_y) + min(min_right_x, min_right_y)) / 2
            elif max_left_x > min_right_y:
                right = i - 1
            else:
                left = i + 1

        raise ValueError("Input arrays are not sorted.")
```

### C++

```cpp
#include <vector>
#include <limits>

using namespace std;

class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        if (nums1.size() > nums2.size()) {
            return findMedianSortedArrays(nums2, nums1);
        }

        int m = nums1.size(), n = nums2.size();
        int left = 0, right = m;

        while (left <= right) {
            int i = (left + right) / 2;
            int j = (m + n + 1) / 2 - i;

            int maxLeftX = (i == 0) ? numeric_limits<int>::min() : nums1[i - 1];
            int minRightX = (i == m) ? numeric_limits<int>::max() : nums1[i];
            int maxLeftY = (j == 0) ? numeric_limits<int>::min() : nums2[j - 1];
            int minRightY = (j == n) ? numeric_limits<int>::max() : nums2[j];

            if (maxLeftX <= minRightY && maxLeftY <= minRightX) {
                if ((m + n) % 2 == 1) {
                    return static_cast<double>(max(maxLeftX, maxLeftY));
                }
                return (max(maxLeftX, maxLeftY) + min(minRightX, minRightY)) / 2.0;
            } else if (maxLeftX > minRightY) {
                right = i - 1;
            } else {
                left = i + 1;
            }
        }

        throw invalid_argument("Input arrays are not sorted.");
    }
};
```

### 复杂度

| 项目 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 二分查找 | O(log(min(m,n))) | O(1) |

## 解法对比

| 解法 | 说明 | 时间复杂度 | 空间复杂度 |
|------|------|------------|------------|
| 归并/指针 | 直观模拟，操作最少，适合小规模 | O(m+n) | O(1) |
| 二分查找 / 划分 | 跳过不可能值，满足 log 复杂度 | O(log(min(m,n))) | O(1) |
