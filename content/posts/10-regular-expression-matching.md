---
title: "10. 正则表达式匹配"
difficulty: "困难"
description: "实现支持 '.' 和 '*' 的正则表达式匹配，'.' 匹配任意单个字符，'*' 匹配零个或多个前一个元素。"
---

# 10. 正则表达式匹配

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

实现一个支持 `'.'` 和 `'*'` 的正则表达式匹配。给定输入字符串 `s` 和模式 `p`：

- `'.'` 匹配任意单个字符。
- `'*'` 匹配零个或多个前一个元素。

匹配要求覆盖整个输入字符串（不能是部分匹配）。

### 示例

```text
输入：s = "aa", p = "a"
输出：false
```

```text
输入：s = "aa", p = "a*"
输出：true
解释：'*' 可匹配前一个 'a' 的多次出现。
```

```text
输入：s = "ab", p = ".*"
输出：true
```

## 解法一：递归 + 备忘（自顶向下）

### 思路

- 定义函数 `dfs(i, j)` 表示 `s[i:]` 与 `p[j:]` 是否匹配。
- 首先判定首字符是否匹配：`first = i < len(s) and (s[i] == p[j] or p[j] == '.')`。
- 如果 `p[j+1]` 是 `'*'`，有两种选择：
  1. 跳过 `'*'` 组合（匹配 0 次）：`dfs(i, j+2)`；
  2. 消费一个字符（若首字符匹配）：`first and dfs(i+1, j)`。
- 否则，直接匹配当前字符：`first and dfs(i+1, j+1)`。
- 使用备忘录避免重复子问题，时间 `O(mn)`。

### Python

```python
from functools import lru_cache

class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        @lru_cache(None)
        def dfs(i: int, j: int) -> bool:
            if j == len(p):
                return i == len(s)

            first = i < len(s) and (s[i] == p[j] or p[j] == ".")

            if j + 1 < len(p) and p[j + 1] == "*":
                return dfs(i, j + 2) or (first and dfs(i + 1, j))
            return first and dfs(i + 1, j + 1)

        return dfs(0, 0)
```

### C++

```cpp
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<int>> memo(m + 1, vector<int>(n + 1, -1));

        function<bool(int, int)> dfs = [&](int i, int j) -> bool {
            if (memo[i][j] != -1) return memo[i][j];
            bool ans;
            if (j == n) {
                ans = (i == m);
            } else {
                bool first = (i < m) && (s[i] == p[j] || p[j] == '.');
                if (j + 1 < n && p[j + 1] == '*') {
                    ans = dfs(i, j + 2) || (first && dfs(i + 1, j));
                } else {
                    ans = first && dfs(i + 1, j + 1);
                }
            }
            memo[i][j] = ans;
            return ans;
        };

        return dfs(0, 0);
    }
};
```

### 复杂度

| 项目 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| 递归 + 备忘 | O(mn) | O(mn) 递归栈 + 备忘表 |

## 解法二：动态规划（自底向上）

### 思路

- `dp[i][j]` 表示 `s[i:]` 与 `p[j:]` 是否匹配，反向填表可避免递归栈。
- 边界：`dp[m][n] = True`（空串匹配空模式）；从尾部开始遍历 `i=m..0`、`j=n-1..0`。
- 状态转移同递归：判断 `p[j+1]=='*'` 处理“跳过”与“消耗”两种情况，否则直接匹配当前字符。
- 最终答案为 `dp[0][0]`。

### Python

```python
class Solution:
    def isMatchDP(self, s: str, p: str) -> bool:
        m, n = len(s), len(p)
        dp = [[False] * (n + 1) for _ in range(m + 1)]
        dp[m][n] = True

        for i in range(m, -1, -1):
            for j in range(n - 1, -1, -1):
                first = i < m and (s[i] == p[j] or p[j] == ".")
                if j + 1 < n and p[j + 1] == "*":
                    dp[i][j] = dp[i][j + 2] or (first and dp[i + 1][j])
                else:
                    dp[i][j] = first and dp[i + 1][j + 1]
        return dp[0][0]
```

### C++

```cpp
#include <string>
#include <vector>

using namespace std;

class SolutionDP {
public:
    bool isMatch(string s, string p) {
        int m = s.size(), n = p.size();
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
        dp[m][n] = true;

        for (int i = m; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                bool first = (i < m) && (s[i] == p[j] || p[j] == '.');
                if (j + 1 < n && p[j + 1] == '*') {
                    dp[i][j] = dp[i][j + 2] || (first && dp[i + 1][j]);
                } else {
                    dp[i][j] = first && dp[i + 1][j + 1];
                }
            }
        }
        return dp[0][0];
    }
};
```

### 复杂度

| 项目 | 时间复杂度 | 空间复杂度 |
|------|------------|------------|
| DP | O(mn) | O(mn) |

## 解法对比

| 解法 | 思路 | 时间复杂度 | 空间复杂度 |
|------|------|------------|------------|
| 递归 + 备忘 | 顶到底搜索，分支处理 `*` 跳过/消耗 | O(mn) | O(mn) |
| 动态规划 | 反向填表，避免递归栈 | O(mn) | O(mn) |
