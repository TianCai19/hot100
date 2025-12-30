---
title: "62. 不同路径"
difficulty: "中等"
description: "一个机器人位于一个 m x n 网格的左上角。机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。总共有多少条不同的路径？"
---

# 62. 不同路径

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

一个机器人位于一个 `m x n` 网格的左上角。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角。

总共有多少条不同的路径？

### 示例

```text
输入：m = 3, n = 7
输出：28
```

```text
输入：m = 2, n = 3
输出：3
```

**解释**：从左上角到右下角，总共有 3 条路径：
1. 右 → 右 → 下
2. 右 → 下 → 右
3. 下 → 右 → 右

## 解法一：动态规划（推荐）

### 思路

1. **状态定义**：`dp[i][j]` 表示到达位置 `(i, j)` 的路径数量
2. **状态转移**：
   - 位置 `(i, j)` 只能从上方 `(i-1, j)` 或左方 `(i, j-1)` 到达
   - 因此：`dp[i][j] = dp[i-1][j] + dp[i][j-1]`
3. **初始状态**：
   - 第一行和第一列的路径数都是 1（只能向右或向下走）
   - `dp[0][0] = 1`
4. **边界条件**：
   - 如果 `i == 0`，只能从左边到达：`dp[0][j] = 1`
   - 如果 `j == 0`，只能从上边到达：`dp[i][0] = 1`

### Python

```python
def unique_paths(m: int, n: int) -> int:
    """
    动态规划解法

    时间复杂度: O(m * n)
    空间复杂度: O(m * n)，可优化到 O(min(m, n))
    """
    # 创建 dp 表
    dp = [[0] * n for _ in range(m)]

    # 初始化第一行
    for j in range(n):
        dp[0][j] = 1

    # 初始化第一列
    for i in range(m):
        dp[i][0] = 1

    # 填表
    for i in range(1, m):
        for j in range(1, n):
            dp[i][j] = dp[i-1][j] + dp[i][j-1]

    return dp[m-1][n-1]

# 优化版本：使用一维数组
def unique_paths_optimized(m: int, n: int) -> int:
    """
    优化版本：使用一维数组

    时间复杂度: O(m * n)
    空间复杂度: O(n)
    """
    # dp[j] 表示到达第 i 行第 j 列的路径数
    dp = [1] * n  # 初始化为 1，第一行的所有位置都只能从左边到达

    for i in range(1, m):
        for j in range(1, n):
            dp[j] += dp[j-1]

    return dp[n-1]

# 测试用例
if __name__ == "__main__":
    test_cases = [
        (3, 7, 28),
        (2, 3, 3),
        (3, 3, 6),
        (1, 1, 1),
        (1, 5, 1),
        (5, 1, 1),
    ]

    for m, n, expected in test_cases:
        result = unique_paths(m, n)
        result_opt = unique_paths_optimized(m, n)
        print(f"m={m}, n={n}: {result} (预期: {expected})")
        print(f"  优化版本: {result_opt} (预期: {expected})")
        assert result == expected and result_opt == expected, "测试失败!"
        print()
```

### C++

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        // 创建 dp 表
        vector<vector<int>> dp(m, vector<int>(n, 0));

        // 初始化第一行
        for (int j = 0; j < n; j++) {
            dp[0][j] = 1;
        }

        // 初始化第一列
        for (int i = 0; i < m; i++) {
            dp[i][0] = 1;
        }

        // 填表
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }

        return dp[m-1][n-1];
    }

    int uniquePathsOptimized(int m, int n) {
        // 使用一维数组优化空间
        vector<int> dp(n, 1);  // 初始化为 1，第一行的所有位置都只能从左边到达

        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                dp[j] += dp[j-1];
            }
        }

        return dp[n-1];
    }
};

// 测试函数
void test_unique_paths() {
    Solution solution;

    vector<tuple<int, int, int>> test_cases = {
        {3, 7, 28},
        {2, 3, 3},
        {3, 3, 6},
        {1, 1, 1},
        {1, 5, 1},
        {5, 1, 1}
    };

    for (const auto& test : test_cases) {
        int m, n, expected;
        tie(m, n, expected) = test;

        int result = solution.uniquePaths(m, n);
        int result_opt = solution.uniquePathsOptimized(m, n);

        cout << "m=" << m << ", n=" << n << ": " << result << " (预期: " << expected << ")";
        cout << " | 优化版本: " << result_opt << " (预期: " << expected << ")";

        if (result == expected && result_opt == expected) {
            cout << " ✓" << endl;
        } else {
            cout << " ✗" << endl;
        }
    }
}

int main() {
    test_unique_paths();
    return 0;
}
```

## 解法二：组合数学

### 思路

从左上角到右下角，需要向下走 `(m-1)` 步，向右走 `(n-1)` 步，总共 `(m-1 + n-1)` 步。

问题转化为：在总步数中，选择哪些步是向下的（或向右的），这是一个组合问题：

```
答案 = C(m-1 + n-1, m-1) = C(m-1 + n-1, n-1)
```

### Python

```python
def unique_paths_combination(m: int, n: int) -> int:
    """
    组合数学解法

    时间复杂度: O(min(m, n))
    空间复杂度: O(1)
    """
    from math import comb

    # 从 m-1 + n-1 步中选 m-1 步向下
    return comb(m + n - 2, m - 1)

# 手动计算组合数（不使用 math.comb）
def unique_paths_combination_manual(m: int, n: int) -> int:
    """
    手动计算组合数

    时间复杂度: O(min(m, n))
    空间复杂度: O(1)
    """
    # 计算 C(a, b) = a! / (b! * (a-b)!)
    # 为避免大数计算，使用迭代方式
    a = m + n - 2
    b = min(m - 1, n - 1)

    result = 1
    for i in range(1, b + 1):
        result = result * (a - i + 1) // i

    return result
```

### C++

```cpp
// 组合数学解法
long long uniquePathsCombination(int m, int n) {
    // 计算 C(a, b) = a! / (b! * (a-b)!)
    // 使用 long long 防止溢出
    long long a = m + n - 2;
    long long b = min(m - 1, n - 1);

    long long result = 1;
    for (long long i = 1; i <= b; i++) {
        result = result * (a - i + 1) / i;
    }

    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 | O(m * n) | O(m * n) / O(n) | 直观易懂 |
| 组合数学 | O(min(m, n)) | O(1) | 数学解法，最优 |

## 总结

- **动态规划**：经典解法，思路清晰，易于理解和实现
- **组合数学**：数学解法，时间复杂度更优，直接计算组合数
- **实际应用**：路径规划、网格遍历、组合计数等场景
- **优化要点**：动态规划可用一维数组优化空间复杂度
