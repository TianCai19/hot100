---
title: "128. 最长连续序列"
difficulty: "中等"
description: "给定一个未排序的整数数组 nums，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。请你设计并实现一个时间复杂度为 O(n) 的算法解决此问题。"
---

# 128. 最长连续序列

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个未排序的整数数组 `nums`，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。

请你设计并实现一个时间复杂度为 `O(n)` 的算法解决此问题。

### 示例

```text
输入：nums = [100,4,200,1,3,2]
输出：4
解释：最长数字连续序列是 [1, 2, 3, 4]，它的长度是 4
```

```text
输入：nums = [0,3,7,2,5,8,4,6,0,1]
输出：9
```

```text
输入：nums = [10,5,12,7,55,4]
输出：3
解释：最长数字连续序列是 [4, 5, 12]，它的长度是 3
```

## 解法一：哈希表（推荐）

### 思路

使用哈希表记录所有数字，然后只从每个序列的起点开始计算长度：

1. 将所有数字存入哈希集合 `num_set`
2. 遍历每个数字 `num`：
   - 如果 `num-1` 不在集合中，说明 `num` 是序列的起点
   - 从 `num` 开始，计算连续序列的长度
   - 更新最大长度
3. 这样每个数字最多被访问两次，时间复杂度 O(n)

### Python

```python
from typing import List

def longest_consecutive(nums: List[int]) -> int:
    """
    哈希表解法

    时间复杂度: O(n)，每个数字最多被访问两次
    空间复杂度: O(n)，存储所有数字
    """
    if not nums:
        return 0

    # 将所有数字存入哈希集合
    num_set = set(nums)
    longest = 0

    for num in num_set:
        # 只从序列的起点开始计算
        if num - 1 not in num_set:
            current = num
            current_streak = 1

            # 计算连续序列的长度
            while current + 1 in num_set:
                current += 1
                current_streak += 1

            # 更新最大长度
            longest = max(longest, current_streak)

    return longest

# 测试用例
if __name__ == "__main__":
    print(longest_consecutive([100, 4, 200, 1, 3, 2]))  # 输出: 4
    print(longest_consecutive([0, 3, 7, 2, 5, 8, 4, 6, 0, 1]))  # 输出: 9
    print(longest_consecutive([10, 5, 12, 7, 55, 4]))  # 输出: 3
    print(longest_consecutive([]))  # 输出: 0
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }

        // 将所有数字存入哈希集合
        unordered_set<int> num_set(nums.begin(), nums.end());
        int longest = 0;

        for (int num : num_set) {
            // 只从序列的起点开始计算
            if (num_set.find(num - 1) == num_set.end()) {
                int current = num;
                int current_streak = 1;

                // 计算连续序列的长度
                while (num_set.find(current + 1) != num_set.end()) {
                    current++;
                    current_streak++;
                }

                // 更新最大长度
                longest = max(longest, current_streak);
            }
        }

        return longest;
    }
};

// 测试用例
int main() {
    Solution solution;

    vector<int> nums1 = {100, 4, 200, 1, 3, 2};
    cout << solution.longestConsecutive(nums1) << endl;  // 输出: 4

    vector<int> nums2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
    cout << solution.longestConsecutive(nums2) << endl;  // 输出: 9

    vector<int> nums3 = {10, 5, 12, 7, 55, 4};
    cout << solution.longestConsecutive(nums3) << endl;  // 输出: 3

    vector<int> nums4 = {};
    cout << solution.longestConsecutive(nums4) << endl;  // 输出: 0

    return 0;
}
```

## 解法二：排序 + 一次遍历

### 思路

先对数组排序，然后遍历数组寻找连续序列：

1. 对数组进行排序：`O(n log n)`
2. 遍历排序后的数组
3. 如果当前数字比前一个数字大 1，继续当前序列
4. 否则，重置序列长度

### Python

```python
def longest_consecutive_sort(nums: List[int]) -> int:
    """
    排序解法

    时间复杂度: O(n log n)
    空间复杂度: O(1)
    """
    if not nums:
        return 0

    nums.sort()
    longest = 1
    current = 1

    for i in range(1, len(nums)):
        if nums[i] == nums[i - 1]:
            continue  # 跳过重复元素
        elif nums[i] == nums[i - 1] + 1:
            current += 1  # 继续当前序列
        else:
            longest = max(longest, current)  # 重置序列
            current = 1

    longest = max(longest, current)  # 更新最后一次结果

    return longest
```

### C++

```cpp
int longestConsecutiveSort(vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    sort(nums.begin(), nums.end());

    int longest = 1;
    int current = 1;

    for (size_t i = 1; i < nums.size(); i++) {
        if (nums[i] == nums[i - 1]) {
            continue;  // 跳过重复元素
        } else if (nums[i] == nums[i - 1] + 1) {
            current++;  // 继续当前序列
        } else {
            longest = max(longest, current);  // 重置序列
            current = 1;
        }
    }

    longest = max(longest, current);  // 更新最后一次结果

    return longest;
}
```

## 解法三：哈希表 + 并查集思想

### 思路

使用哈希表记录每个数字所属序列的长度，同时维护序列的起点和终点：

1. `length_map[num]` 表示以 `num` 为起点的序列长度
2. 对于每个数字 `num`：
   - 如果 `num-1` 存在，说明它可以连接到前一个序列
   - 如果 `num+1` 存在，说明它可以扩展后一个序列
   - 更新新序列的长度

### Python

```python
def longest_consecutive_union(nums: List[int]) -> int:
    """
    哈希表 + 并查集思想

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    if not nums:
        return 0

    longest = 1
    length_map = {}

    for num in nums:
        if num in length_map:
            continue  # 已处理过

        left = length_map.get(num - 1, 0)
        right = length_map.get(num + 1, 0)

        current_len = left + right + 1
        length_map[num] = current_len

        # 更新序列起点的长度
        if left > 0:
            length_map[num - left] = current_len

        # 更新序列终点的长度
        if right > 0:
            length_map[num + right] = current_len

        longest = max(longest, current_len)

    return longest
```

### C++

```cpp
int longestConsecutiveUnion(vector<int>& nums) {
    if (nums.empty()) {
        return 0;
    }

    int longest = 1;
    unordered_map<int, int> length_map;

    for (int num : nums) {
        if (length_map.find(num) != length_map.end()) {
            continue;  // 已处理过
        }

        int left = length_map.count(num - 1) ? length_map[num - 1] : 0;
        int right = length_map.count(num + 1) ? length_map[num + 1] : 0;

        int current_len = left + right + 1;
        length_map[num] = current_len;

        // 更新序列起点的长度
        if (left > 0) {
            length_map[num - left] = current_len;
        }

        // 更新序列终点的长度
        if (right > 0) {
            length_map[num + right] = current_len;
        }

        longest = max(longest, current_len);
    }

    return longest;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 哈希表 | O(n) | O(n) | 最优解，推荐使用 |
| 排序 | O(n log n) | O(1) | 实现简单，思路直观 |
| 并查集思想 | O(n) | O(n) | 思想高级，可扩展 |

## 总结

- **哈希表解法**是经典的最优解，时间和空间复杂度都很好
- **排序解法**实现简单，但时间复杂度较高
- **并查集思想**虽然更复杂，但可以处理更复杂的问题
- 关键在于只从序列起点开始计算，避免重复访问
