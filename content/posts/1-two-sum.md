---
title: "两数之和"
difficulty: "简单"
description: "给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那两个整数，并返回它们的数组下标。"
---

# 1. 两数之和

<DifficultyBadge difficulty="简单" />

## 题目描述

给定一个整数数组 `nums` 和一个目标值 `target`，请你在该数组中找出和为目标值的那两个整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

**示例 1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1]。
```

**示例 2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
```

**示例 3：**

```
输入：nums = [3,3], target = 6
输出：[0,1]
```

## 解题思路

### 解法一：暴力枚举（易懂）

最直观的解法是双重循环遍历数组，对于每个元素，检查数组中是否有另一个元素与它的和为目标值。

**时间复杂度：** O(n²)
**空间复杂度：** O(1)

### 解法二：哈希表优化（推荐）

利用哈希表（Python 中的 dict，C++ 中的 unordered_map）可以显著提升性能：

1. 遍历数组，对于每个元素 `num`
2. 计算 `complement = target - num`
3. 检查 `complement` 是否在哈希表中
   - 如果在，返回 `[hash_map[complement], i]`
   - 如果不在，将 `num` 及其索引存入哈希表

**时间复杂度：** O(n)
**空间复杂度：** O(n)

## 可视化示例

{<svg width="600" height="200" xmlns="http://www.w3.org/2000/svg">
  {/* 数组 */}
  <text x="50" y="30" fontFamily="Arial" fontSize="14" fill="#fff">数组 nums = [2, 7, 11, 15]</text>
  <text x="50" y="50" fontFamily="Arial" fontSize="14" fill="#fff">target = 9</text>

  {/* 步骤1 */}
  <rect x="50" y="80" width="100" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="100" y="100" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">i=0, num=2</text>
  <text x="100" y="120" fontFamily="Arial" fontSize="10" textAnchor="middle" fill="#ccc">查找 complement=7</text>
  <text x="100" y="135" fontFamily="Arial" fontSize="10" textAnchor="middle" fill="red">未找到</text>

  {/* 步骤2 */}
  <rect x="180" y="80" width="100" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="230" y="100" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">i=1, num=7</text>
  <text x="230" y="120" fontFamily="Arial" fontSize="10" textAnchor="middle" fill="#ccc">查找 complement=2</text>
  <text x="230" y="135" fontFamily="Arial" fontSize="10" textAnchor="middle" fill="green">找到！返回[0,1]</text>

  {/* 哈希表 */}
  <text x="400" y="30" fontFamily="Arial" fontSize="14" fill="#fff">哈希表状态：</text>
  <rect x="380" y="50" width="150" height="80" fill="#1f2937" stroke="#fff" strokeWidth="1"/>
  <text x="455" y="75" fontFamily="Arial" fontSize="11" textAnchor="middle" fill="#3b82f6">2 → 0</text>
  <text x="455" y="95" fontFamily="Arial" fontSize="11" textAnchor="middle" fill="#3b82f6">7 → 1</text>
</svg>}

## 代码实现

### Python 实现

```python
from typing import List

def two_sum(nums: List[int], target: int) -> List[int]:
    """
    解法二：哈希表优化
    时间复杂度：O(n)
    空间复杂度：O(n)
    """
    hash_map = {}  # 存储 {数值: 索引}

    for i, num in enumerate(nums):
        complement = target - num

        if complement in hash_map:
            return [hash_map[complement], i]

        hash_map[num] = i

    return []

# 测试用例
if __name__ == "__main__":
    # 示例1
    nums1 = [2, 7, 11, 15]
    target1 = 9
    print(f"示例1: nums={nums1}, target={target1}")
    print(f"输出: {two_sum(nums1, target1)}")  # [0, 1]

    # 示例2
    nums2 = [3, 2, 4]
    target2 = 6
    print(f"\n示例2: nums={nums2}, target={target2}")
    print(f"输出: {two_sum(nums2, target2)}")  # [1, 2]

    # 示例3
    nums3 = [3, 3]
    target3 = 6
    print(f"\n示例3: nums={nums3}, target={target3}")
    print(f"输出: {two_sum(nums3, target3)}")  # [0, 1]

    # 额外测试
    nums4 = [1, 2, 3, 4, 5]
    target4 = 8
    print(f"\n额外测试: nums={nums4}, target={target4}")
    print(f"输出: {two_sum(nums4, target4)}")  # [2, 4]
```

### C++ 实现

```cpp
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/**
 * 解法二：哈希表优化
 * 时间复杂度：O(n)
 * 空间复杂度：O(n)
 */
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> hash_map;  // 存储 {数值: 索引}

    for (int i = 0; i < nums.size(); i++) {
        int complement = target - nums[i];

        if (hash_map.find(complement) != hash_map.end()) {
            return {hash_map[complement], i};
        }

        hash_map[nums[i]] = i;
    }

    return {};
}

// 辅助函数：打印数组
void printVector(const vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i < vec.size() - 1) cout << ", ";
    }
    cout << "]";
}

// 测试用例
int main() {
    // 示例1
    vector<int> nums1 = {2, 7, 11, 15};
    int target1 = 9;
    cout << "示例1: nums = [2, 7, 11, 15], target = 9" << endl;
    cout << "输出: ";
    printVector(twoSum(nums1, target1));
    cout << endl << endl;

    // 示例2
    vector<int> nums2 = {3, 2, 4};
    int target2 = 6;
    cout << "示例2: nums = [3, 2, 4], target = 6" << endl;
    cout << "输出: ";
    printVector(twoSum(nums2, target2));
    cout << endl << endl;

    // 示例3
    vector<int> nums3 = {3, 3};
    int target3 = 6;
    cout << "示例3: nums = [3, 3], target = 6" << endl;
    cout << "输出: ";
    printVector(twoSum(nums3, target3));
    cout << endl << endl;

    // 额外测试
    vector<int> nums4 = {1, 2, 3, 4, 5};
    int target4 = 8;
    cout << "额外测试: nums = [1, 2, 3, 4, 5], target = 8" << endl;
    cout << "输出: ";
    printVector(twoSum(nums4, target4));
    cout << endl;

    return 0;
}
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 暴力枚举 | O(n²) | O(1) | 思路简单，但性能较差 |
| 哈希表 | O(n) | O(n) | **推荐**，高效且实用 |

## 关键总结

- **哈希表是解决两数之和问题的最优解法**
- 只需要一次遍历，时间复杂度从 O(n²) 优化到 O(n)
- 这是哈希表应用的经典案例，务必掌握
- 类似的题目还有"三数之和"、"四数之和"等