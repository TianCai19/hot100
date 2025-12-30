---
title: "72. 编辑距离"
difficulty: "中等"
description: "给你两个单词 word1 和 word2，请返回将 word1 转换成 word2 所使用的最少操作数。你可以对一个单词进行如下三种操作：插入一个字符、删除一个字符、替换一个字符。"
---

# 72. 编辑距离

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你两个单词 `word1` 和 `word2`，请返回将 `word1` 转换成 `word2` 所使用的最少操作数。

你可以对一个单词进行如下三种操作：
- **插入**一个字符
- **删除**一个字符
- **替换**一个字符

### 示例

```text
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
```

```text
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
```

## 解法一：动态规划（推荐）

### 思路

编辑距离问题是最经典的动态规划问题之一。

定义状态：
- `dp[i][j]` 表示将 `word1[0:i]` 转换为 `word2[0:j]` 的最少操作数

状态转移：
1. 如果 `word1[i-1] == word2[j-1]`：
   - 不需要操作：`dp[i][j] = dp[i-1][j-1]`
2. 如果 `word1[i-1] != word2[j-1]`：
   - 插入：`dp[i][j] = dp[i][j-1] + 1`
   - 删除：`dp[i][j] = dp[i-1][j] + 1`
   - 替换：`dp[i][j] = dp[i-1][j-1] + 1`
   - 取最小值：`dp[i][j] = min(插入, 删除, 替换)`

初始化：
- `dp[0][j] = j`（将空字符串转换为 word2[0:j] 需要 j 次插入）
- `dp[i][0] = i`（将 word1[0:i] 转换为空字符串需要 i 次删除）

### Python

```python
def min_distance(word1: str, word2: str) -> int:
    """
    动态规划解法

    时间复杂度: O(m*n)，其中 m 和 n 分别是 word1 和 word2 的长度
    空间复杂度: O(m*n)
    """
    m, n = len(word1), len(word2)

    # 创建 dp 数组，dp[i][j] 表示 word1[:i] 转换为 word2[:j] 的最少操作数
    dp = [[0] * (n + 1) for _ in range(m + 1)]

    # 初始化：当其中一个字符串为空时
    for i in range(m + 1):
        dp[i][0] = i  # 删除操作

    for j in range(n + 1):
        dp[0][j] = j  # 插入操作

    # 填充 dp 数组
    for i in range(1, m + 1):
        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                # 字符相同，不需要操作
                dp[i][j] = dp[i - 1][j - 1]
            else:
                # 字符不同，取三种操作的最小值
                # 1. 插入：dp[i][j-1] + 1
                # 2. 删除：dp[i-1][j] + 1
                # 3. 替换：dp[i-1][j-1] + 1
                dp[i][j] = min(
                    dp[i - 1][j] + 1,      # 删除
                    dp[i][j - 1] + 1,      # 插入
                    dp[i - 1][j - 1] + 1   # 替换
                )

    return dp[m][n]
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDistance(string word1, string word2) {
        /**
         * 动态规划解法
         *
         * 时间复杂度: O(m*n)
         * 空间复杂度: O(m*n)
         */
        int m = word1.length();
        int n = word2.length();

        // 创建 dp 数组
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 初始化：当其中一个字符串为空时
        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;  // 删除操作
        }

        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;  // 插入操作
        }

        // 填充 dp 数组
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    // 字符相同，不需要操作
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    // 字符不同，取三种操作的最小值
                    dp[i][j] = min({
                        dp[i - 1][j] + 1,      // 删除
                        dp[i][j - 1] + 1,      // 插入
                        dp[i - 1][j - 1] + 1   // 替换
                    });
                }
            }
        }

        return dp[m][n];
    }
};

// 测试函数
int main() {
    Solution s;

    cout << s.minDistance("horse", "ros") << " (expected: 3)" << endl;
    cout << s.minDistance("intention", "execution") << " (expected: 5)" << endl;

    return 0;
}
```

## 解法二：空间优化版动态规划

### 思路

观察到 `dp[i][j]` 只依赖于 `dp[i-1][j-1]`、`dp[i-1][j]` 和 `dp[i][j-1]`，我们可以使用滚动数组优化空间复杂度。

### Python

```python
def min_distance_optimized(word1: str, word2: str) -> int:
    """
    空间优化版动态规划

    时间复杂度: O(m*n)
    空间复杂度: O(min(m, n))
    """
    if len(word1) < len(word2):
        return min_distance(word2, word1)

    m, n = len(word1), len(word2)

    # 只保存前一行的结果
    prev = list(range(n + 1))

    for i in range(1, m + 1):
        curr = [i]  # 当前行的第一个值

        for j in range(1, n + 1):
            if word1[i - 1] == word2[j - 1]:
                curr.append(prev[j - 1])
            else:
                curr.append(min(prev[j], curr[j - 1], prev[j - 1]) + 1)

        prev = curr

    return prev[n]
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
public:
    int minDistanceOptimized(string word1, string word2) {
        /**
         * 空间优化版动态规划
         *
         * 时间复杂度: O(m*n)
         * 空间复杂度: O(min(m, n))
         */
        if (word1.length() < word2.length()) {
            return minDistance(word2, word1);
        }

        int m = word1.length();
        int n = word2.length();

        // 只保存前一行的结果
        vector<int> prev(n + 1);
        for (int j = 0; j <= n; j++) {
            prev[j] = j;
        }

        for (int i = 1; i <= m; i++) {
            vector<int> curr(n + 1);
            curr[0] = i;  // 当前行的第一个值

            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    curr[j] = prev[j - 1];
                } else {
                    curr[j] = min({prev[j], curr[j - 1], prev[j - 1]}) + 1;
                }
            }

            prev = curr;
        }

        return prev[n];
    }

private:
    // 辅助函数：标准动态规划
    int minDistance(string word1, string word2) {
        int m = word1.length();
        int n = word2.length();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        for (int i = 0; i <= m; i++) {
            dp[i][0] = i;
        }

        for (int j = 0; j <= n; j++) {
            dp[0][j] = j;
        }

        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                } else {
                    dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
                }
            }
        }

        return dp[m][n];
    }
};
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 | O(m*n) | O(m*n) | 标准解法，易于理解 |
| 空间优化 | O(m*n) | O(min(m, n)) | 节省空间，实用推荐 |

## 总结

- 编辑距离是**字符串匹配**的经典问题
- 动态规划通过子问题求解原问题，适合这类最优子结构问题
- 状态转移方程是关键：考虑插入、删除、替换三种操作
- 空间优化版本在实际应用中更有价值
- 该算法在**拼写检查**、**DNA序列比对**等领域有广泛应用
