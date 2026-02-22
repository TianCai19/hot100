---
title: "169. 多数元素"
difficulty: "简单"
description: "给定一个大小为 n 的数组 nums，返回其中的多数元素。多数元素是指在数组中出现次数大于 ⌊n/2⌋ 的元素。"
---

# 169. 多数元素

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给定一个大小为 `n` 的数组 `nums`，返回其中的多数元素。多数元素是指在数组中出现次数大于 `⌊n/2⌋` 的元素。

你可以假设数组是非空的，并且给定的数组总是存在多数元素。

### 示例

```text
输入：nums = [3,2,3]
输出：3
```

```text
输入：nums = [2,2,1,1,1,2,2]
输出：2
```

## 解法一：Boyer-Moore 投票算法（推荐）

### 思路

维护两个变量：
- `candidate`：当前候选多数元素
- `count`：候选元素的“票数”

遍历数组时：
1. 当 `count == 0`，将当前数字设为新的候选者
2. 如果当前数字等于候选者，`count += 1`
3. 否则 `count -= 1`

由于多数元素出现次数超过一半，最终留下的候选者一定是多数元素。

### Python

```python
from typing import List


class Solution:
    def majorityElement(self, nums: List[int]) -> int:
        candidate = None
        count = 0

        for num in nums:
            if count == 0:
                candidate = num

            if num == candidate:
                count += 1
            else:
                count -= 1

        return candidate
```

### C++

```cpp
#include <vector>
using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0;
        int count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }

            if (num == candidate) {
                count++;
            } else {
                count--;
            }
        }

        return candidate;
    }
};
```

## 解法二：哈希计数

### 思路

用哈希表统计每个元素出现次数，一旦某个元素计数超过 `n/2`，即可返回。

### Python

```python
from collections import Counter
from typing import List


class SolutionHash:
    def majorityElement(self, nums: List[int]) -> int:
        threshold = len(nums) // 2
        counts = Counter(nums)

        for num, freq in counts.items():
            if freq > threshold:
                return num

        return -1
```

### C++

```cpp
#include <unordered_map>
#include <vector>
using namespace std;

class SolutionHash {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> counter;
        int threshold = nums.size() / 2;

        for (int num : nums) {
            counter[num]++;
            if (counter[num] > threshold) {
                return num;
            }
        }

        return -1;
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| Boyer-Moore 投票 | O(n) | O(1) | 最优解，常数空间 |
| 哈希计数 | O(n) | O(n) | 易理解，便于扩展 |

## 总结

- 本题最优解是 **Boyer-Moore 投票算法**，同时满足线性时间与常数空间。
- 哈希计数实现更直观，但需要额外空间。
- 该题是“抵消思想”的经典应用，常见于数组统计类问题。
