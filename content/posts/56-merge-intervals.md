---
title: "56. 合并区间"
difficulty: "中等"
description: "以数组 intervals 表示若干个区间的集合，其中每个区间 intervals[i] = [start_i, end_i] 。合并所有重叠的区间，并返回一个不重叠区间的数组，该数组需恰好覆盖输入中的所有区间。"
---

# 56. 合并区间

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

以数组 `intervals` 表示若干个区间的集合，其中每个区间 `intervals[i] = [start_i, end_i]` 。

合并所有重叠的区间，并返回一个不重叠区间的数组，该数组需恰好覆盖输入中的所有区间。

### 示例

```text
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠，将它们合并为 [1,6]。
```

```text
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 重叠（边界点接触），合并为 [1,5]。
```

## 解法一：排序后合并（推荐）

### 思路

1. **排序**：先按照区间的起始位置排序，这样重叠的区间会相邻
2. **遍历合并**：
   - 如果当前区间与前一个区间重叠，则合并它们（更新前一个区间的结束位置为两者的最大值）
   - 如果不重叠，则将前一个区间加入结果，开始新的区间
3. 遍历结束后，记得将最后一个区间加入结果

### Python

```python
from typing import List

def merge(intervals: List[List[int]]) -> List[List[int]]:
    """
    排序后合并区间

    时间复杂度: O(n log n)，排序的时间复杂度
    空间复杂度: O(1)，不计输出空间
    """
    if not intervals:
        return []

    # 按区间起始位置排序
    intervals.sort(key=lambda x: x[0])

    merged = []
    for interval in intervals:
        # 如果列表为空，或者当前区间不与前一个区间重叠
        if not merged or interval[0] > merged[-1][1]:
            merged.append(interval)
        else:
            # 当前区间与前一个区间重叠，合并它们
            merged[-1][1] = max(merged[-1][1], interval[1])

    return merged

# 测试用例
if __name__ == "__main__":
    test_cases = [
        ([[1,3],[2,6],[8,10],[15,18]], [[1,6],[8,10],[15,18]]),
        ([[1,4],[4,5]], [[1,5]]),
        ([[1,4],[2,3]], [[1,4]]),
        ([[]], []),
        ([[1,4],[0,4]], [[0,4]]),
        ([[1,4],[2,3],[5,7],[6,8]], [[1,4],[5,8]])
    ]

    for i, (input_intervals, expected) in enumerate(test_cases, 1):
        result = merge(input_intervals)
        print(f"测试用例 {i}: {'通过' if result == expected else '失败'}")
        print(f"  输入: {input_intervals}")
        print(f"  输出: {result}")
        print(f"  预期: {expected}\n")
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) {
            return {};
        }

        // 按区间起始位置排序
        sort(intervals.begin(), intervals.end(),
             [](const vector<int>& a, const vector<int>& b) {
                 return a[0] < b[0];
             });

        vector<vector<int>> merged;
        merged.push_back(intervals[0]);

        for (size_t i = 1; i < intervals.size(); i++) {
            // 如果当前区间与前一个区间重叠
            if (intervals[i][0] <= merged.back()[1]) {
                // 合并区间，更新结束位置
                merged.back()[1] = max(merged.back()[1], intervals[i][1]);
            } else {
                // 不重叠，添加新区间
                merged.push_back(intervals[i]);
            }
        }

        return merged;
    }
};

// 测试函数
void test_merge() {
    Solution solution;

    vector<pair<vector<vector<int>>, vector<vector<int>>>> test_cases = {
        {
            {{1,3},{2,6},{8,10},{15,18}},
            {{1,6},{8,10},{15,18}}
        },
        {
            {{1,4},{4,5}},
            {{1,5}}
        },
        {
            {{1,4},{2,3}},
            {{1,4}}
        },
        {
            {},
            {}
        },
        {
            {{1,4},{0,4}},
            {{0,4}}
        },
        {
            {{1,4},{2,3},{5,7},{6,8}},
            {{1,4},{5,8}}
        }
    };

    for (size_t i = 0; i < test_cases.size(); i++) {
        vector<vector<int>> result = solution.merge(test_cases[i].first);
        bool passed = (result == test_cases[i].second);

        cout << "测试用例 " << (i + 1) << ": " << (passed ? "通过" : "失败") << endl;
        cout << "  输入: [";
        for (const auto& interval : test_cases[i].first) {
            cout << "[" << interval[0] << "," << interval[1] << "]";
            if (&interval != &test_cases[i].first.back()) cout << ",";
        }
        cout << "]" << endl;

        cout << "  输出: [";
        for (const auto& interval : result) {
            cout << "[" << interval[0] << "," << interval[1] << "]";
            if (&interval != &result.back()) cout << ",";
        }
        cout << "]" << endl;

        cout << "  预期: [";
        for (const auto& interval : test_cases[i].second) {
            cout << "[" << interval[0] << "," << interval[1] << "]";
            if (&interval != &test_cases[i].second.back()) cout << ",";
        }
        cout << "]" << endl << endl;
    }
}

int main() {
    test_merge();
    return 0;
}
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 排序后合并 | O(n log n) | O(1) | 思路清晰，最优解 |

**说明**：
- 时间复杂度主要来自排序操作 O(n log n)
- 合并操作只需要一次遍历 O(n)
- 空间复杂度为 O(1)，不计输出空间

## 总结

- **关键点**：排序是解决区间合并问题的核心，将重叠的区间变为相邻
- **合并逻辑**：当前区间起始位置 ≤ 前一个区间结束位置时，两区间重叠
- **应用场景**：区间调度、任务合并、日程安排等经典问题
