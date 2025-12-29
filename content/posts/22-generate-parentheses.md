---
title: "22. 括号生成"
difficulty: "中等"
description: "数字 n 代表生成括号的对数，请你生成所有有可能的并且有效的括号组合。"
---

# 22. 括号生成

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

数字 `n` 代表生成括号的对数，请你生成所有有可能的并且有效的括号组合。

有效的括号组合需要满足：
- 左括号必须用相同类型的右括号闭合
- 左括号必须以正确的顺序闭合

### 示例

```text
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
```

```text
输入：n = 1
输出：["()"]
```

## 解法一：回溯算法（推荐）

### 思路

使用回溯算法构建有效的括号序列：

1. **状态跟踪**：维护两个计数器 `left` 和 `right`
   - `left`：已使用的左括号数量
   - `right`：已使用的右括号数量

2. **递归构建**：
   - 如果 `left < n`，可以添加左括号：`backtrack(s + '(', left + 1, right)`
   - 如果 `right < left`，可以添加右括号：`backtrack(s + ')', left, right + 1)`
   - 当 `left == n && right == n` 时，生成一个有效组合

3. **剪枝优化**：
   - 右括号的数量不能超过左括号（保证有效性）
   - 左括号数量不能超过 n（保证数量正确）

### Python

```python
from typing import List

def generate_parentheses(n: int) -> List[str]:
    """
    回溯算法解法

    时间复杂度: O(4^n / sqrt(n))，卡特兰数
    空间复杂度: O(n)，递归栈深度
    """
    result = []

    def backtrack(s: str, left: int, right: int):
        # 当字符串长度达到 2n 时，添加结果
        if len(s) == 2 * n:
            result.append(s)
            return

        # 可以添加左括号
        if left < n:
            backtrack(s + '(', left + 1, right)

        # 可以添加右括号（但不能超过左括号数量）
        if right < left:
            backtrack(s + ')', left, right + 1)

    backtrack('', 0, 0)
    return result
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    vector<string> result;

    void backtrack(string& s, int left, int right, int n) {
        // 当字符串长度达到 2n 时，添加结果
        if (s.length() == 2 * n) {
            result.push_back(s);
            return;
        }

        // 可以添加左括号
        if (left < n) {
            s.push_back('(');
            backtrack(s, left + 1, right, n);
            s.pop_back();  // 回溯
        }

        // 可以添加右括号（但不能超过左括号数量）
        if (right < left) {
            s.push_back(')');
            backtrack(s, left, right + 1, n);
            s.pop_back();  // 回溯
        }
    }

public:
    vector<string> generateParentheses(int n) {
        string s;
        backtrack(s, 0, 0, n);
        return result;
    }
};
```

## 解法二：动态规划

### 思路

使用动态规划的思想：

1. **状态定义**：`dp[i]` 表示 `n = i` 时所有有效的括号组合
2. **状态转移**：
   - 遍历所有可能的分割点 `j`
   - 组合形式：`(dp[j]) + (dp[i-1-j])`
   - 其中 `j` 从 0 到 `i-1`
3. **初始状态**：`dp[0] = [""]`

### Python

```python
def generate_parentheses_dp(n: int) -> List[str]:
    """
    动态规划解法

    时间复杂度: O(4^n / sqrt(n))
    空间复杂度: O(4^n / sqrt(n))
    """
    if n == 0:
        return [""]

    dp = [None] * (n + 1)
    dp[0] = [""]

    for i in range(1, n + 1):
        cur = []
        # 遍历所有可能的分割
        for j in range(i):
            left_part = dp[j]
            right_part = dp[i - 1 - j]

            for left in left_part:
                for right in right_part:
                    cur.append("(" + left + ")" + right)
        dp[i] = cur

    return dp[n]
```

### C++

```cpp
vector<string> generateParenthesesDP(int n) {
    /**
     * 动态规划解法
     *
     * 时间复杂度: O(4^n / sqrt(n))
     * 空间复杂度: O(4^n / sqrt(n))
     */
    if (n == 0) {
        return {""};
    }

    vector<vector<string>> dp(n + 1);
    dp[0] = {""};

    for (int i = 1; i <= n; i++) {
        vector<string> cur;
        // 遍历所有可能的分割
        for (int j = 0; j < i; j++) {
            const auto& left_part = dp[j];
            const auto& right_part = dp[i - 1 - j];

            for (const string& left : left_part) {
                for (const string& right : right_part) {
                    cur.push_back("(" + left + ")" + right);
                }
            }
        }
        dp[i] = move(cur);
    }

    return dp[n];
}
```

## 解法三：闭合括号生成

### 思路

另一种回溯变种，每次递归生成一个完整的括号对：

1. 每次递归生成一对完整的括号 `()()`
2. 在这对括号内部和之后继续递归
3. 遍历所有可能的插入位置

### Python

```python
def generate_parentheses_closed(n: int) -> List[str]:
    """
    闭合括号生成解法

    时间复杂度: O(4^n / sqrt(n))
    空间复杂度: O(n)
    """
    result = []

    def backtrack(s: str, pos: int, total: int):
        if pos == total:
            result.append(s)
            return

        # 递归生成
        if pos < total:
            backtrack(s + '()', pos + 1, total)

    backtrack('', 0, n)
    return result
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 回溯算法 | O(4^n / sqrt(n)) | O(n) | 经典解法，清晰易懂 |
| 动态规划 | O(4^n / sqrt(n)) | O(4^n / sqrt(n)) | 结构化思维，可扩展 |
| 闭合括号 | O(4^n / sqrt(n)) | O(n) | 思路独特，简洁 |

**说明**：时间复杂度中的 `4^n / sqrt(n)` 是卡特兰数，表示 n 对括号的所有可能组合数。

## 总结

- **回溯算法**是最直观的方法，通过维护左右括号数量保证有效性
- **动态规划**展示了如何将问题分解为子问题
- 关键思想：**剪枝**（保证 `right < left`）和**状态跟踪**
- 这类问题都可以通过**回溯模板**解决：选择 → 递归 → 回溯
- 结果数量符合**卡特兰数**：C(2n, n) / (n + 1)
