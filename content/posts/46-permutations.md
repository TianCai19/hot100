---
title: "46. 全排列"
difficulty: "中等"
description: "给定一个不含重复数字的数组 nums，返回其所有可能的全排列。可以按任意顺序返回答案。"
---

# 46. 全排列

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个不含重复数字的数组 `nums`，返回其所有可能的全排列。

可以按任意顺序返回答案。

### 示例

```text
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

```text
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```

```text
输入：nums = [1]
输出：[[1]]
```

## 解法一：回溯算法（推荐）

### 思路

使用回溯算法生成所有排列：

1. 使用 `path` 数组保存当前路径
2. 使用 `used` 数组标记哪些元素已经被使用
3. 当 `path` 的长度等于 `nums` 的长度时，保存结果
4. 遍历所有未使用的元素，递归添加到路径中

### Python

```python
from typing import List

def permute(nums: List[int]) -> List[List[int]]:
    """
    回溯算法解法

    时间复杂度: O(n!)，每个排列需要 O(n) 时间
    空间复杂度: O(n)，递归栈和 path、used 数组
    """
    result: List[List[int]] = []
    path: List[int] = []
    used = [False] * len(nums)

    def backtrack():
        # 当前路径长度等于数组长度，保存结果
        if len(path) == len(nums):
            result.append(path.copy())
            return

        # 遍历所有元素
        for i in range(len(nums)):
            # 如果当前元素已被使用，跳过
            if used[i]:
                continue

            # 选择当前元素
            used[i] = True
            path.append(nums[i])

            # 递归处理下一个位置
            backtrack()

            # 回溯：撤销选择
            path.pop()
            used[i] = False

    backtrack()
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
    vector<int> path;
    vector<bool> used;

    void backtrack(vector<int>& nums) {
        // 当前路径长度等于数组长度，保存结果
        if (path.size() == nums.size()) {
            result.push_back(path);
            return;
        }

        // 遍历所有元素
        for (int i = 0; i < nums.size(); i++) {
            // 如果当前元素已被使用，跳过
            if (used[i]) {
                continue;
            }

            // 选择当前元素
            used[i] = true;
            path.push_back(nums[i]);

            // 递归处理下一个位置
            backtrack(nums);

            // 回溯：撤销选择
            path.pop_back();
            used[i] = false;
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        used.assign(nums.size(), false);
        backtrack(nums);
        return result;
    }
};
```

## 解法二：库函数（Python）

### 思路

使用 Python 的 `itertools.permutations` 函数直接生成全排列。

### Python

```python
from itertools import permutations
from typing import List

def permute_itertools(nums: List[int]) -> List[List[int]]:
    """
    使用 itertools.permutations

    时间复杂度: O(n!)，底层实现与回溯相同
    空间复杂度: O(n)
    """
    return [list(p) for p in permutations(nums)]
```

## 解法三：交换法（回溯优化）

### 思路

通过交换元素位置来生成排列，避免使用额外的 `used` 数组：

1. 固定当前位置的元素
2. 递归排列剩余元素
3. 通过交换实现元素选择

### Python

```python
def permute_swap(nums: List[int]) -> List[List[int]]:
    """
    交换法回溯

    时间复杂度: O(n!)
    空间复杂度: O(n)，递归栈
    """
    result: List[List[int]] = []

    def backtrack(first: int = 0):
        # 当前所有元素已固定，保存结果
        if first == len(nums):
            result.append(nums.copy())
            return

        # 遍历剩余元素
        for i in range(first, len(nums)):
            # 将当前元素交换到当前位置
            nums[first], nums[i] = nums[i], nums[first]

            # 递归排列剩余元素
            backtrack(first + 1)

            # 回溯：交换回来
            nums[first], nums[i] = nums[i], nums[first]

    backtrack()
    return result
```

### C++

```cpp
vector<vector<int>> permuteSwap(vector<int>& nums) {
    vector<vector<int>> result;

    function<void(int)> backtrack = [&](int first) {
        // 当前所有元素已固定，保存结果
        if (first == nums.size()) {
            result.push_back(nums);
            return;
        }

        // 遍历剩余元素
        for (int i = first; i < nums.size(); i++) {
            // 将当前元素交换到当前位置
            swap(nums[first], nums[i]);

            // 递归排列剩余元素
            backtrack(first + 1);

            // 回溯：交换回来
            swap(nums[first], nums[i]);
        }
    };

    backtrack(0);
    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 回溯算法 | O(n!) | O(n) | 经典解法，代码清晰 |
| 库函数 | O(n!) | O(n) | 简洁但依赖库 |
| 交换法 | O(n!) | O(n) | 空间更优，无需 used 数组 |

## 总结

- **回溯算法**是解决排列组合问题的通用方法，思路清晰易懂
- **交换法**通过原地交换避免使用 `used` 数组，空间效率更高
- 所有解法的时间复杂度都是 O(n!)，因为全排列的数量就是 n!
- 关键在于理解回溯的"选择-递归-撤销"模式
- 注意在保存结果时要使用 `copy()` 或 `nums`（C++），避免引用问题
