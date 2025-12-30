---
title: "64. 最小路径和"
difficulty: "中等"
description: "给定一个 m x n 的网格 grid，找到一条从左上角到右下角的路径，使得路径上所有单元格数值之和最小。只能向右或向下移动。"
---

# 64. 最小路径和

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个 `m x n` 的网格 `grid`，找到一条从左上角到右下角的路径，使得路径上所有单元格数值之和最小。

只能向右或向下移动。

### 示例

```text
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。
```

```text
输入：grid = [[1,2,3],[4,5,6]]
输出：12
```

## 解法一：动态规划（推荐）

### 思路

1. **状态定义**：`dp[i][j]` 表示从 `(0, 0)` 到 `(i, j)` 的最小路径和
2. **状态转移**：
   - 位置 `(i, j)` 可以从上方 `(i-1, j)` 或左方 `(i, j-1)` 到达
   - 因此：`dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`
3. **初始状态**：
   - `dp[0][0] = grid[0][0]`（起点）
   - 第一行：只能从左向右走，`dp[0][j] = dp[0][j-1] + grid[0][j]`
   - 第一列：只能从上向下走，`dp[i][0] = dp[i-1][0] + grid[i][0]`
4. **边界条件**：`grid` 不为空

### Python

```python
def min_path_sum(grid):
    """
    动态规划解法

    时间复杂度: O(m * n)
    空间复杂度: O(m * n)，可优化到 O(min(m, n))
    """
    if not grid or not grid[0]:
        return 0

    m, n = len(grid), len(grid[0])

    # 创建 dp 表
    dp = [[0] * n for _ in range(m)]
    dp[0][0] = grid[0][0]

    # 初始化第一行
    for j in range(1, n):
        dp[0][j] = dp[0][j-1] + grid[0][j]

    # 初始化第一列
    for i in range(1, m):
        dp[i][0] = dp[i-1][0] + grid[i][0]

    # 填表
    for i in range(1, m):
        for j in range(1, n):
            dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])

    return dp[m-1][n-1]

# 优化版本：原地修改 grid
def min_path_sum_optimized(grid):
    """
    优化版本：原地修改 grid 作为 dp 表

    时间复杂度: O(m * n)
    空间复杂度: O(1)
    """
    if not grid or not grid[0]:
        return 0

    m, n = len(grid), len(grid[0])

    # 初始化第一行
    for j in range(1, n):
        grid[0][j] += grid[0][j-1]

    # 初始化第一列
    for i in range(1, m):
        grid[i][0] += grid[i-1][0]

    # 填表
    for i in range(1, m):
        for j in range(1, n):
            grid[i][j] += min(grid[i-1][j], grid[i][j-1])

    return grid[m-1][n-1]

# 测试用例
if __name__ == "__main__":
    test_cases = [
        ([[1,3,1],[1,5,1],[4,2,1]], 7),
        ([[1,2,3],[4,5,6]], 12),
        ([[1]], 1),
        ([[1,2]], 3),
        ([[1],[2]], 3),
        ([[1,3,1,2],[4,5,1,3],[2,1,4,1]], 7),
    ]

    for i, (grid, expected) in enumerate(test_cases, 1):
        # 深拷贝 grid 用于两次测试
        import copy
        grid_copy1 = copy.deepcopy(grid)
        grid_copy2 = copy.deepcopy(grid)

        result1 = min_path_sum(grid_copy1)
        result2 = min_path_sum_optimized(grid_copy2)

        print(f"测试用例 {i}:")
        print(f"  输入: {grid}")
        print(f"  动态规划: {result1} (预期: {expected})")
        print(f"  优化版本: {result2} (预期: {expected})")

        assert result1 == expected and result2 == expected, "测试失败!"
        print()
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int m = grid.size();
        int n = grid[0].size();

        // 创建 dp 表
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];

        // 初始化第一行
        for (int j = 1; j < n; j++) {
            dp[0][j] = dp[0][j-1] + grid[0][j];
        }

        // 初始化第一列
        for (int i = 1; i < m; i++) {
            dp[i][0] = dp[i-1][0] + grid[i][0];
        }

        // 填表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1]);
            }
        }

        return dp[m-1][n-1];
    }

    int minPathSumOptimized(vector<vector<int>>& grid) {
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int m = grid.size();
        int n = grid[0].size();

        // 初始化第一行
        for (int j = 1; j < n; j++) {
            grid[0][j] += grid[0][j-1];
        }

        // 初始化第一列
        for (int i = 1; i < m; i++) {
            grid[i][0] += grid[i-1][0];
        }

        // 填表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
            }
        }

        return grid[m-1][n-1];
    }
};

// 测试函数
void test_min_path_sum() {
    Solution solution;

    vector<pair<vector<vector<int>>, int>> test_cases = {
        {
            {{1,3,1},{1,5,1},{4,2,1}},
            7
        },
        {
            {{1,2,3},{4,5,6}},
            12
        },
        {
            {{1}},
            1
        },
        {
            {{1,2}},
            3
        },
        {
            {{1},{2}},
            3
        },
        {
            {{1,3,1,2},{4,5,1,3},{2,1,4,1}},
            7
        }
    };

    for (size_t i = 0; i < test_cases.size(); i++) {
        vector<vector<int>> grid_copy1 = test_cases[i].first;
        vector<vector<int>> grid_copy2 = test_cases[i].first;
        int expected = test_cases[i].second;

        int result1 = solution.minPathSum(grid_copy1);
        int result2 = solution.minPathSumOptimized(grid_copy2);

        cout << "测试用例 " << (i + 1) << ":" << endl;
        cout << "  输入: [";
        for (size_t row = 0; row < test_cases[i].first.size(); row++) {
            cout << "[";
            for (size_t col = 0; col < test_cases[i].first[row].size(); col++) {
                cout << test_cases[i].first[row][col];
                if (col < test_cases[i].first[row].size() - 1) cout << ",";
            }
            cout << "]";
            if (row < test_cases[i].first.size() - 1) cout << ",";
        }
        cout << "]" << endl;

        cout << "  动态规划: " << result1 << " (预期: " << expected << ")";
        cout << " | 优化版本: " << result2 << " (预期: " << expected << ")";

        if (result1 == expected && result2 == expected) {
            cout << " ✓" << endl;
        } else {
            cout << " ✗" << endl;
        }
        cout << endl;
    }
}

int main() {
    test_min_path_sum();
    return 0;
}
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 | O(m * n) | O(m * n) | 直观易懂 |
| 原地修改 | O(m * n) | O(1) | 最优空间复杂度 |

## 总结

- **核心思想**：动态规划是解决网格路径问题的通用方法
- **状态转移**：`dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])`
- **优化技巧**：
  - 使用一维数组优化空间到 O(n)
  - 原地修改输入数组优化到 O(1)
- **应用场景**：路径规划、最短路径、成本最小化等问题
