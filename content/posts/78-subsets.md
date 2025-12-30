---
title: "78. 子集"
difficulty: "中等"
description: "给你一个整数数组 nums，数组中的元素互不相同。返回该数组所有可能的子集（幂集）。解集不能包含重复的子集。"
---

# 78. 子集

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个整数数组 `nums`，数组中的元素互不相同。

返回该数组所有可能的子集（幂集）。解集不能包含重复的子集。

### 示例

```text
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

```text
输入：nums = [0]
输出：[[],[0]]
```

## 解法一：回溯算法（推荐）

### 思路

回溯算法是解决子集生成问题的经典方法：

1. **递归回溯**：从空集合开始，依次尝试添加每个元素
2. **状态管理**：使用 `path` 数组记录当前子集，`index` 记录当前遍历位置
3. **递归过程**：
   - 每进入一层递归，都将当前 `path` 加入结果集
   - 遍历剩余元素，递归生成包含该元素的子集
4. **回溯**：递归返回时，撤销选择，尝试下一个元素

### Python

```python
from typing import List

def subsets(nums: List[int]) -> List[List[int]]:
    """
    回溯算法解法

    时间复杂度: O(n * 2^n)，每个元素都有选/不选两种可能
    空间复杂度: O(n)，递归栈深度
    """
    result: List[List[int]] = []

    def backtrack(index: int, path: List[int]):
        # 每个节点都是一个子集
        result.append(path.copy())

        # 遍历剩余元素
        for i in range(index, len(nums)):
            # 选择当前元素
            path.append(nums[i])
            # 递归处理剩余元素
            backtrack(i + 1, path)
            # 回溯：移除当前元素
            path.pop()

    backtrack(0, [])
    return result
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
private:
    vector<vector<int>> result;

    void backtrack(const vector<int>& nums, int index, vector<int>& path) {
        // 每个节点都是一个子集
        result.push_back(path);

        // 遍历剩余元素
        for (int i = index; i < nums.size(); i++) {
            // 选择当前元素
            path.push_back(nums[i]);
            // 递归处理剩余元素
            backtrack(nums, i + 1, path);
            // 回溯：移除当前元素
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> path;
        backtrack(nums, 0, path);
        return result;
    }
};
```

## 解法二：迭代解法（数学归纳法）

### 思路

利用数学归纳法的思想：已知前 k 个元素的子集，生成前 k+1 个元素的子集：

1. 初始状态：空集合的子集只有空集合
2. 对于每个新元素，将它加入已有子集，生成新子集
3. 重复直到所有元素处理完毕

### Python

```python
def subsets_iterative(nums: List[int]) -> List[List[int]]:
    """
    迭代解法

    时间复杂度: O(n * 2^n)
    空间复杂度: O(n * 2^n)
    """
    result: List[List[int]] = [[]]

    for num in nums:
        # 当前已有的子集数量
        current_size = len(result)
        # 为每个已有子集添加当前元素，生成新子集
        for i in range(current_size):
            new_subset = result[i].copy()
            new_subset.append(num)
            result.append(new_subset)

    return result
```

### C++

```cpp
vector<vector<int>> subsetsIterative(vector<int>& nums) {
    vector<vector<int>> result = {{}};

    for (int num : nums) {
        int current_size = result.size();
        for (int i = 0; i < current_size; i++) {
            vector<int> new_subset = result[i];
            new_subset.push_back(num);
            result.push_back(new_subset);
        }
    }

    return result;
}
```

## 解法三：二进制位图法

### 思路

利用二进制位表示元素的选择状态：

- n 个元素对应 n 位二进制数
- 从 0 到 2^n - 1 的每个数字代表一种选择方案
- 第 i 位为 1 表示选择第 i 个元素，为 0 表示不选择

### Python

```python
def subsets_bitmap(nums: List[int]) -> List[List[int]]:
    """
    二进制位图解法

    时间复杂度: O(n * 2^n)
    空间复杂度: O(n * 2^n)
    """
    n = len(nums)
    result: List[List[int]] = []

    # 遍历所有可能的子集状态
    for mask in range(1 << n):
        subset: List[int] = []
        # 检查每一位是否被选中
        for i in range(n):
            if mask & (1 << i):
                subset.append(nums[i])
        result.append(subset)

    return result
```

### C++

```cpp
vector<vector<int>> subsetsBitmap(vector<int>& nums) {
    int n = nums.size();
    vector<vector<int>> result;

    // 遍历所有可能的子集状态
    for (int mask = 0; mask < (1 << n); mask++) {
        vector<int> subset;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                subset.push_back(nums[i]);
            }
        }
        result.push_back(subset);
    }

    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 回溯算法 | O(n * 2^n) | O(n) | 递归实现，代码简洁，深度遍历 |
| 迭代解法 | O(n * 2^n) | O(n * 2^n) | 逐层构建，直观易懂 |
| 二进制位图 | O(n * 2^n) | O(n * 2^n) | 数学思维，位运算高效 |

## 总结

- **回溯算法**是最直观的解法，通过递归深度遍历生成所有子集
- **迭代解法**利用数学归纳法，逐层构建子集集合
- **二进制位图法**将子集选择映射为二进制数，思维巧妙
- 三种方法的时间复杂度相同，实际性能相近
- 子集总数为 2^n（包括空集和全集）
- 回溯算法空间复杂度最优，适合内存敏感的场景
