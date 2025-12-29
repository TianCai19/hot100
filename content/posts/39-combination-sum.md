---
title: "39. 组合总和"
difficulty: "中等"
description: "给你一个无重复元素的整数数组 candidates 和一个目标整数 target，找出 candidates 中可以使数字和为目标数 target 的所有不同组合。"
---

# 39. 组合总和

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个**无重复元素**的整数数组 `candidates` 和一个目标整数 `target`，找出 `candidates` 中可以使数字和为目标数 `target` 的所有**不同组合**，并以列表形式返回。你可以按**任意顺序**返回这些组合。

`candidates` 中的**同一个**数字可以**无限制重复被选取**。如果至少一个数字的被选数量不同，则两种组合是不同的。

对于给定的输入，保证和为 `target` 的不同组合数少于 150 个。

### 示例

```text
输入：candidates = [2,3,6,7], target = 7
输出：[[2,2,3],[7]]
解释：
2 和 3 可以形成一组候选，2 + 2 + 3 = 7。注意 2 可以使用多次。
7 也是一个候选，7 = 7。
仅有这两种组合。
```

```text
输入：candidates = [2,3,5], target = 8
输出：[[2,2,2,2],[2,3,3],[3,5]]
```

```text
输入：candidates = [2], target = 1
输出：[]
```

## 解法一：回溯算法（推荐）

### 思路

使用回溯算法搜索所有可能的组合：

1. 定义递归函数 `backtrack(start, target, path)`：
   - `start`：从哪个位置开始选择（避免重复组合）
   - `target`：剩余需要凑的目标值
   - `path`：当前已选择的数字
2. 递归终止条件：
   - `target == 0`：找到一个有效组合
   - `target < 0`：当前组合超出目标，剪枝
3. 从 `start` 开始遍历候选数字，每个数字可以重复选取

### Python

```python
from typing import List

def combination_sum(candidates: List[int], target: int) -> List[List[int]]:
    """
    回溯算法解法

    时间复杂度: O(n^(target/min))，其中 min 是 candidates 中的最小值
    空间复杂度: O(target/min)，递归栈深度
    """
    def backtrack(start: int, target: int, path: List[int]):
        # 找到有效组合
        if target == 0:
            result.append(path[:])  # 复制当前路径
            return

        # 剪枝：目标值小于 0
        if target < 0:
            return

        # 从 start 开始遍历，避免重复组合
        for i in range(start, len(candidates)):
            # 选择当前数字
            path.append(candidates[i])
            # 递归，注意 i 不变（同一个数字可以重复选取）
            backtrack(i, target - candidates[i], path)
            # 回溯，撤销选择
            path.pop()

    result: List[List[int]] = []
    backtrack(0, target, [])
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

    void backtrack(vector<int>& candidates, int start, int target, vector<int>& path) {
        // 找到有效组合
        if (target == 0) {
            result.push_back(path);
            return;
        }

        // 剪枝：目标值小于 0
        if (target < 0) {
            return;
        }

        // 从 start 开始遍历，避免重复组合
        for (int i = start; i < candidates.size(); i++) {
            // 选择当前数字
            path.push_back(candidates[i]);
            // 递归，注意 i 不变（同一个数字可以重复选取）
            backtrack(candidates, i, target - candidates[i], path);
            // 回溯，撤销选择
            path.pop_back();
        }
    }

public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        result.clear();
        vector<int> path;
        backtrack(candidates, 0, target, path);
        return result;
    }
};
```

## 解法二：回溯 + 排序剪枝优化

### 思路

在回溯的基础上，先对数组排序，当当前数字大于剩余目标值时，可以提前终止循环：

1. 对 `candidates` 排序
2. 在循环中，如果 `candidates[i] > target`，直接 break

### Python

```python
def combination_sum_optimized(candidates: List[int], target: int) -> List[List[int]]:
    """
    回溯 + 排序剪枝优化

    时间复杂度: O(n^(target/min))
    空间复杂度: O(target/min)
    """
    def backtrack(start: int, target: int, path: List[int]):
        if target == 0:
            result.append(path[:])
            return

        for i in range(start, len(candidates)):
            # 剪枝：排序后，如果当前数字大于 target，后面的更大，直接终止
            if candidates[i] > target:
                break

            path.append(candidates[i])
            backtrack(i, target - candidates[i], path)
            path.pop()

    candidates.sort()  # 排序以便剪枝
    result: List[List[int]] = []
    backtrack(0, target, [])
    return result
```

### C++

```cpp
vector<vector<int>> combinationSumOptimized(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> path;

    // 排序以便剪枝
    sort(candidates.begin(), candidates.end());

    function<void(int, int)> backtrack = [&](int start, int target) {
        if (target == 0) {
            result.push_back(path);
            return;
        }

        for (int i = start; i < candidates.size(); i++) {
            // 剪枝：排序后，如果当前数字大于 target，后面的更大，直接终止
            if (candidates[i] > target) {
                break;
            }

            path.push_back(candidates[i]);
            backtrack(i, target - candidates[i]);
            path.pop_back();
        }
    };

    backtrack(0, target);
    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 基础回溯 | O(n^(t/m)) | O(t/m) | 标准回溯模板 |
| 排序剪枝 | O(n^(t/m)) | O(t/m) | 实际运行更快 |

**说明**：t 是 target，m 是 candidates 中的最小值，n 是 candidates 长度。

## 总结

- 本题是回溯算法的经典应用，属于「组合问题」
- 关键点：同一个数字可以无限次选取，所以递归时传入 `i` 而非 `i+1`
- 使用 `start` 参数避免产生重复组合（如 `[2,3]` 和 `[3,2]`）
- 排序后剪枝可以有效提升性能
- 记住回溯三部曲：选择 -> 递归 -> 撤销选择
