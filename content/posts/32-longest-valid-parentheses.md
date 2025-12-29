---
title: "32. 最长有效括号"
difficulty: "困难"
description: "给你一个只包含 '(' 和 ')' 的字符串，找出最长有效（格式正确且连续）括号子串的长度。"
---

# 32. 最长有效括号

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给你一个只包含 `'('` 和 `')'` 的字符串，找出最长有效（格式正确且连续）括号子串的长度。

### 示例

```text
输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
```

```text
输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
```

```text
输入：s = ""
输出：0
```

## 解法一：栈（推荐）

### 思路

使用栈来匹配括号，关键是如何计算有效括号的长度：

1. 栈底保存「最后一个未匹配的右括号的索引」，初始化为 -1
2. 遍历字符串：
   - 遇到 `'('`：将索引入栈
   - 遇到 `')'`：先弹出栈顶
     - 如果栈为空：说明当前 `')'` 没有匹配，将其索引入栈作为新的「分隔符」
     - 如果栈不为空：当前有效括号长度 = 当前索引 - 栈顶索引
3. 维护最大长度

### Python

```python
def longest_valid_parentheses(s: str) -> int:
    """
    栈解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    max_len = 0
    stack = [-1]  # 栈底为最后一个未匹配右括号的索引

    for i, char in enumerate(s):
        if char == '(':
            stack.append(i)
        else:
            stack.pop()
            if not stack:
                # 栈为空，当前右括号无法匹配
                stack.append(i)
            else:
                # 计算当前有效括号长度
                max_len = max(max_len, i - stack[-1])

    return max_len
```

### C++

```cpp
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        int maxLen = 0;
        stack<int> stk;
        stk.push(-1);  // 栈底为最后一个未匹配右括号的索引

        for (int i = 0; i < s.length(); i++) {
            if (s[i] == '(') {
                stk.push(i);
            } else {
                stk.pop();
                if (stk.empty()) {
                    // 栈为空，当前右括号无法匹配
                    stk.push(i);
                } else {
                    // 计算当前有效括号长度
                    maxLen = max(maxLen, i - stk.top());
                }
            }
        }

        return maxLen;
    }
};
```

## 解法二：动态规划

### 思路

定义 `dp[i]` 为以 `s[i]` 结尾的最长有效括号长度。

转移方程：
- 若 `s[i] == '('`：`dp[i] = 0`（以左括号结尾不可能有效）
- 若 `s[i] == ')'`：
  - 若 `s[i-1] == '('`：形如 `...()`，`dp[i] = dp[i-2] + 2`
  - 若 `s[i-1] == ')'`：形如 `...))`，需检查 `s[i - dp[i-1] - 1]`
    - 若为 `'('`：`dp[i] = dp[i-1] + 2 + dp[i - dp[i-1] - 2]`

### Python

```python
def longest_valid_parentheses_dp(s: str) -> int:
    """
    动态规划解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    if not s:
        return 0

    n = len(s)
    dp = [0] * n
    max_len = 0

    for i in range(1, n):
        if s[i] == ')':
            if s[i - 1] == '(':
                # 形如 ...()
                dp[i] = (dp[i - 2] if i >= 2 else 0) + 2
            elif i - dp[i - 1] - 1 >= 0 and s[i - dp[i - 1] - 1] == '(':
                # 形如 ...))
                dp[i] = dp[i - 1] + 2
                if i - dp[i - 1] - 2 >= 0:
                    dp[i] += dp[i - dp[i - 1] - 2]

            max_len = max(max_len, dp[i])

    return max_len
```

### C++

```cpp
int longestValidParenthesesDP(string s) {
    if (s.empty()) return 0;

    int n = s.length();
    vector<int> dp(n, 0);
    int maxLen = 0;

    for (int i = 1; i < n; i++) {
        if (s[i] == ')') {
            if (s[i - 1] == '(') {
                // 形如 ...()
                dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
            } else if (i - dp[i - 1] - 1 >= 0 && s[i - dp[i - 1] - 1] == '(') {
                // 形如 ...))
                dp[i] = dp[i - 1] + 2;
                if (i - dp[i - 1] - 2 >= 0) {
                    dp[i] += dp[i - dp[i - 1] - 2];
                }
            }
            maxLen = max(maxLen, dp[i]);
        }
    }

    return maxLen;
}
```

## 解法三：双指针（空间最优）

### 思路

不使用额外空间，通过两次遍历：

1. **从左向右**：统计左右括号数量，相等时更新最大长度，右括号多时重置
2. **从右向左**：统计左右括号数量，相等时更新最大长度，左括号多时重置

### Python

```python
def longest_valid_parentheses_two_pointers(s: str) -> int:
    """
    双指针解法

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    max_len = 0
    left = right = 0

    # 从左向右
    for char in s:
        if char == '(':
            left += 1
        else:
            right += 1

        if left == right:
            max_len = max(max_len, 2 * right)
        elif right > left:
            left = right = 0

    left = right = 0

    # 从右向左
    for char in reversed(s):
        if char == '(':
            left += 1
        else:
            right += 1

        if left == right:
            max_len = max(max_len, 2 * left)
        elif left > right:
            left = right = 0

    return max_len
```

### C++

```cpp
int longestValidParenthesesTwoPointers(string s) {
    int maxLen = 0;
    int left = 0, right = 0;

    // 从左向右
    for (char c : s) {
        if (c == '(') {
            left++;
        } else {
            right++;
        }

        if (left == right) {
            maxLen = max(maxLen, 2 * right);
        } else if (right > left) {
            left = right = 0;
        }
    }

    left = right = 0;

    // 从右向左
    for (int i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '(') {
            left++;
        } else {
            right++;
        }

        if (left == right) {
            maxLen = max(maxLen, 2 * left);
        } else if (left > right) {
            left = right = 0;
        }
    }

    return maxLen;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 栈 | O(n) | O(n) | 经典解法，易于理解 |
| 动态规划 | O(n) | O(n) | 状态转移需要细心处理 |
| 双指针 | O(n) | O(1) | 空间最优，需要两次遍历 |

## 总结

- **栈解法**是最直观的方法，利用栈底保存分隔符位置的技巧非常巧妙
- **动态规划**解法需要仔细处理各种边界情况
- **双指针**解法空间复杂度最优，但需要理解为什么要两次遍历（处理 `((()` 和 `())` 两种情况）
- 这道题是括号匹配问题的经典变体，考察了对栈和动态规划的深入理解
