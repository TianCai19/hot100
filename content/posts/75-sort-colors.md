---
title: "75. 颜色分类"
difficulty: "中等"
description: "给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums，对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色的顺序排列。我们使用整数 0、1 和 2 分别表示红色、白色和蓝色。"
---

# 75. 颜色分类

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个包含红色、白色和蓝色、共 `n` 个元素的数组 `nums`，对它们进行排序，使得相同颜色的元素相邻，并按照**红色、白色、蓝色**的顺序排列。

我们使用整数 `0`、`1` 和 `2` 分别表示红色、白色和蓝色。

### 示例

```text
输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]
```

```text
输入：nums = [2,0,1]
输出：[0,1,2]
```

## 解法一：荷兰国旗问题（推荐）

### 思路

这是经典的**荷兰国旗问题**，使用**三指针**方法：

- `left`：0 的右边界（[0, left) 都是 0）
- `right`：2 的左边界（[right, n) 都是 2）
- `i`：当前遍历指针

遍历过程：
1. 如果 `nums[i] == 0`，与 `left` 交换，`left++`, `i++`
2. 如果 `nums[i] == 2`，与 `right` 交换，`right--`（注意：此时 i 不变，因为交换过来的元素还未处理）
3. 如果 `nums[i] == 1`，`i++`

这种方法只需要一次遍历，时间复杂度 O(n)。

### Python

```python
def sort_colors(nums):
    """
    荷兰国旗解法（三指针）

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    left, right = 0, len(nums) - 1
    i = 0

    while i <= right:
        if nums[i] == 0:
            # 当前元素是 0，交换到左边
            nums[left], nums[i] = nums[i], nums[left]
            left += 1
            i += 1
        elif nums[i] == 2:
            # 当前元素是 2，交换到右边
            nums[right], nums[i] = nums[i], nums[right]
            right -= 1
            # 注意：i 不变，因为交换过来的元素还未处理
        else:  # nums[i] == 1
            # 当前元素是 1，保持不变
            i += 1
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        /**
         * 荷兰国旗解法（三指针）
         *
         * 时间复杂度: O(n)
         * 空间复杂度: O(1)
         */
        int left = 0;
        int right = nums.size() - 1;
        int i = 0;

        while (i <= right) {
            if (nums[i] == 0) {
                // 当前元素是 0，交换到左边
                swap(nums[left], nums[i]);
                left++;
                i++;
            } else if (nums[i] == 2) {
                // 当前元素是 2，交换到右边
                swap(nums[right], nums[i]);
                right--;
                // 注意：i 不变，因为交换过来的元素还未处理
            } else {  // nums[i] == 1
                // 当前元素是 1，保持不变
                i++;
            }
        }
    }
};

// 测试函数
int main() {
    Solution s;

    vector<int> nums1 = {2, 0, 2, 1, 1, 0};
    s.sortColors(nums1);
    cout << "[";
    for (size_t i = 0; i < nums1.size(); i++) {
        cout << nums1[i];
        if (i < nums1.size() - 1) cout << ",";
    }
    cout << "] (expected: [0,0,1,1,2,2])" << endl;

    vector<int> nums2 = {2, 0, 1};
    s.sortColors(nums2);
    cout << "[";
    for (size_t i = 0; i < nums2.size(); i++) {
        cout << nums2[i];
        if (i < nums2.size() - 1) cout << ",";
    }
    cout << "] (expected: [0,1,2])" << endl;

    return 0;
}
```

## 解法二：两遍扫描计数

### 思路

这是一种更简单的方法：
1. 第一遍扫描：统计 0、1、2 的个数
2. 第二遍扫描：根据计数重新填充数组

时间复杂度 O(n)，但需要两遍扫描。

### Python

```python
def sort_colors_counting(nums):
    """
    两遍扫描计数法

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    # 第一遍：计数
    count = [0, 0, 0]  # count[0] = 0的个数，count[1] = 1的个数，count[2] = 2的个数
    for num in nums:
        count[num] += 1

    # 第二遍：根据计数重新填充
    index = 0
    for i in range(3):
        for _ in range(count[i]):
            nums[index] = i
            index += 1
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    void sortColorsCounting(vector<int>& nums) {
        /**
         * 两遍扫描计数法
         *
         * 时间复杂度: O(n)
         * 空间复杂度: O(1)
         */
        // 第一遍：计数
        array<int, 3> count = {0, 0, 0};  // count[0] = 0的个数，count[1] = 1的个数，count[2] = 2的个数
        for (int num : nums) {
            count[num]++;
        }

        // 第二遍：根据计数重新填充
        int index = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < count[i]; j++) {
                nums[index++] = i;
            }
        }
    }
};
```

## 解法三：使用 sort() 函数

### 思路

最简单的方法，直接调用 Python 或 C++ 的标准排序函数。

**注意**：虽然简单，但这种方法没有体现对荷兰国旗问题的理解，在面试中不建议使用。

### Python

```python
def sort_colors_builtin(nums):
    """
    使用内置 sort 函数

    时间复杂度: O(n log n)
    空间复杂度: O(1) 或 O(n)（取决于具体实现）
    """
    nums.sort()
```

### C++

```cpp
#include <algorithm>

void sortColorsBuiltin(vector<int>& nums) {
    /**
     * 使用内置 sort 函数
     *
     * 时间复杂度: O(n log n)
     * 空间复杂度: O(1)
     */
    sort(nums.begin(), nums.end());
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 荷兰国旗（三指针） | O(n) | O(1) | 最优解法，一次遍历 |
| 两遍扫描计数 | O(n) | O(1) | 简单直观，需要两遍 |
| sort() 函数 | O(n log n) | O(1) | 最简单，但性能最差 |

## 总结

- **荷兰国旗问题**是三指针应用的经典案例
- 关键在于理解三个指针的作用和边界
- 时间复杂度优化到 O(n)，是此类问题的最优解
- 计数法虽然简单，但需要两遍扫描
- 在面试中，荷兰国旗解法更能体现算法功底
