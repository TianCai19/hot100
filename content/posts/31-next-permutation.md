---
title: "31. 下一个排列"
difficulty: "中等"
description: "整数数组的一个排列，如果按照字典序排序在它之后，则称它为下一个排列。给定一个整数数组，找出下一个排列。"
---

# 31. 下一个排列

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

整数数组的一个 **排列**（Permutation），如果按照字典序排序在它之后，则称它为 **下一个排列**（Next Permutation）。

给定一个整数数组，找出下一个排列。题目必须原地修改，且只使用常数级别的额外空间。

### 示例

```text
输入：nums = [1,2,3]
输出：[1,3,2]
解释：所有排列按字典序排列为：
     [1,2,3] → [1,3,2] → [2,1,3] → [2,3,1] → [3,1,2] → [3,2,1]
```

```text
输入：nums = [3,2,1]
输出：[1,2,3]
解释：这是最后一个排列，下一个排列是第一个排列（升序排列）
```

```text
输入：nums = [1,1,5]
输出：[1,5,1]
```

## 解法一：双指针贪心算法（推荐）

### 思路

寻找下一个排列的步骤：

1. **从右向左**找到第一个**降序**的相邻元素对 `(i, i+1)`，其中 `nums[i] < nums[i+1]`
2. 如果找到这样的 `i`，再从**右向左**找到第一个比 `nums[i]` 大的元素 `nums[j]`
3. 交换 `nums[i]` 和 `nums[j]`
4. 将 `i+1` 到末尾的部分**反转**（升序变为降序）

这相当于在尽可能靠右的位置做最小的增大。

### Python

```python
def next_permutation(nums):
    """
    下一个排列算法

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    n = len(nums)

    # 步骤1：从右向左找到第一个降序的相邻元素对
    # 即找到最大的索引 i，使得 nums[i] < nums[i+1]
    i = n - 2
    while i >= 0 and nums[i] >= nums[i + 1]:
        i -= 1

    # 如果找到了这样的 i
    if i >= 0:
        # 步骤2：从右向左找到第一个比 nums[i] 大的元素
        j = n - 1
        while nums[j] <= nums[i]:
            j -= 1

        # 步骤3：交换 nums[i] 和 nums[j]
        nums[i], nums[j] = nums[j], nums[i]

    # 步骤4：将 i+1 到末尾的部分反转（升序变为降序）
    # 即使 i < 0（没有找到），反转整个数组也是正确的
    left, right = i + 1, n - 1
    while left < right:
        nums[left], nums[right] = nums[right], nums[left]
        left += 1
        right -= 1

# 测试
if __name__ == "__main__":
    # 测试用例1
    nums1 = [1, 2, 3]
    next_permutation(nums1)
    print(nums1)  # [1, 3, 2]

    # 测试用例2
    nums2 = [3, 2, 1]
    next_permutation(nums2)
    print(nums2)  # [1, 2, 3]

    # 测试用例3
    nums3 = [1, 1, 5]
    next_permutation(nums3)
    print(nums3)  # [1, 5, 1]

    # 测试用例4
    nums4 = [1, 3, 2]
    next_permutation(nums4)
    print(nums4)  # [2, 1, 3]

    # 测试用例5（重复元素）
    nums5 = [2, 3, 1, 3, 3]
    next_permutation(nums5)
    print(nums5)  # [2, 3, 3, 1, 3]
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();

        // 步骤1：从右向左找到第一个降序的相邻元素对
        // 即找到最大的索引 i，使得 nums[i] < nums[i+1]
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // 如果找到了这样的 i
        if (i >= 0) {
            // 步骤2：从右向左找到第一个比 nums[i] 大的元素
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }

            // 步骤3：交换 nums[i] 和 nums[j]
            swap(nums[i], nums[j]);
        }

        // 步骤4：将 i+1 到末尾的部分反转（升序变为降序）
        // 即使 i < 0（没有找到），反转整个数组也是正确的
        reverse(nums.begin() + i + 1, nums.end());
    }
};

// 测试
int main() {
    Solution solution;

    // 测试用例1
    vector<int> nums1 = {1, 2, 3};
    solution.nextPermutation(nums1);
    for (int num : nums1) cout << num << " ";
    cout << endl;  // 1 3 2

    // 测试用例2
    vector<int> nums2 = {3, 2, 1};
    solution.nextPermutation(nums2);
    for (int num : nums2) cout << num << " ";
    cout << endl;  // 1 2 3

    // 测试用例3
    vector<int> nums3 = {1, 1, 5};
    solution.nextPermutation(nums3);
    for (int num : nums3) cout << num << " ";
    cout << endl;  // 1 5 1

    // 测试用例4
    vector<int> nums4 = {1, 3, 2};
    solution.nextPermutation(nums4);
    for (int num : nums4) cout << num << " ";
    cout << endl;  // 2 1 3

    // 测试用例5（重复元素）
    vector<int> nums5 = {2, 3, 1, 3, 3};
    solution.nextPermutation(nums5);
    for (int num : nums5) cout << num << " ";
    cout << endl;  // 2 3 3 1 3

    return 0;
}
```

## 解法二：使用 C++ 标准库（参考）

### 思路

C++ 标准库提供了 `next_permutation` 函数，可以直接使用。

### C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void nextPermutationStd(vector<int>& nums) {
    // C++ 标准库函数
    next_permutation(nums.begin(), nums.end());
}
```

**注意**：在实际面试中，建议实现算法解法，而不是直接调用标准库。

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 手动实现 | O(n) | O(1) | 算法核心解法 |
| 标准库 | O(n) | O(1) | 实用但面试不推荐 |

**说明**：`next_permutation` 标准库内部也是 O(n) 时间复杂度。

## 总结

- **下一个排列**是一个经典的算法问题，核心是理解**字典序**的规律
- 算法步骤：**找降序** → **找交换点** → **交换** → **反转**
- 注意边界情况的处理（完全降序时需要反转整个数组）
- 原地修改，常数级额外空间，时间复杂度 O(n)
- 这是解决**全排列**问题的基础算法之一
