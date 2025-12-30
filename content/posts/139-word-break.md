---
title: "139. 单词拆分"
difficulty: "中等"
description: "给你一个字符串 s 和一个字符串列表 wordDict 作为字典，判定 s 是否可以被拆分成一个或多个在字典中出现的单词。"
---

# 139. 单词拆分

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个字符串 `s` 和一个字符串列表 `wordDict` 作为字典，判定 `s` 是否可以被拆分成一个或多个在字典中出现的单词。

拆分时可以重复使用字典中的单词。你可以认为字典中没有重复的单词。

### 示例

```text
输入：s = "leetcode", wordDict = ["leet", "code"]
输出：true
解释：返回 true 因为 "leetcode" 可以被拆分成 "leet code"
```

```text
输入：s = "applepenapple", wordDict = ["apple", "pen"]
输出：true
解释：返回 true 因为 "applepenapple" 可以被拆分成 "apple pen apple"
注意你可以重复使用字典中的单词
```

```text
输入：s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
输出：false
```

## 解法一：动态规划（推荐）

### 思路

使用动态规划求解，状态定义如下：
- `dp[i]` 表示字符串 `s` 的前 `i` 个字符是否能被拆分成字典中的单词
- 初始化 `dp[0] = true`（空字符串可以被拆分）
- 状态转移：对于每个位置 `i`，检查所有 `j < i`，如果 `dp[j]` 为 `true` 且 `s[j:i]` 在字典中，则 `dp[i] = true`

### Python

```python
from typing import List

def word_break(s: str, wordDict: List[str]) -> bool:
    """
    动态规划解法

    时间复杂度: O(n^2)，其中 n 是字符串长度
    空间复杂度: O(n)
    """
    word_set = set(wordDict)  # 转为集合，提升查找效率
    n = len(s)
    dp = [False] * (n + 1)
    dp[0] = True  # 空字符串可以被拆分

    for i in range(1, n + 1):
        for j in range(i):
            if dp[j] and s[j:i] in word_set:
                dp[i] = True
                break  # 找到一个拆分即可，提前结束内层循环

    return dp[n]
```

### C++

```cpp
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> word_set(wordDict.begin(), wordDict.end());
        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[0] = true;  // 空字符串可以被拆分

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && word_set.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }

        return dp[n];
    }
};
```

## 解法二：记忆化回溯

### 思路

使用回溯法搜索所有可能的拆分方式，并通过记忆化避免重复计算：
1. 定义递归函数 `backtrack(start)`，表示从位置 `start` 开始是否能被拆分
2. 枚举所有可能的结束位置，检查子串是否在字典中
3. 使用记忆化数组存储已计算的结果

### Python

```python
def word_break_memo(s: str, wordDict: List[str]) -> bool:
    """
    记忆化回溯解法

    时间复杂度: O(n^2)
    空间复杂度: O(n)
    """
    word_set = set(wordDict)
    memo = {}

    def backtrack(start: int) -> bool:
        if start in memo:
            return memo[start]

        if start == len(s):
            return True

        for end in range(start + 1, len(s) + 1):
            word = s[start:end]
            if word in word_set and backtrack(end):
                memo[start] = True
                return True

        memo[start] = False
        return False

    return backtrack(0)
```

### C++

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_set<string> word_set;
    unordered_map<int, bool> memo;

    bool backtrack(const string& s, int start) {
        if (start == s.length()) {
            return true;
        }

        if (memo.find(start) != memo.end()) {
            return memo[start];
        }

        for (int end = start + 1; end <= s.length(); end++) {
            string word = s.substr(start, end - start);
            if (word_set.count(word) && backtrack(s, end)) {
                memo[start] = true;
                return true;
            }
        }

        memo[start] = false;
        return false;
    }

public:
    bool wordBreak(string s, vector<string>& wordDict) {
        word_set = unordered_set<string>(wordDict.begin(), wordDict.end());
        memo.clear();
        return backtrack(s, 0);
    }
};
```

## 解法三：BFS（广度优先搜索）

### 思路

将问题转化为图搜索问题：
- 每个位置是一个节点
- 如果子串 `s[i:j]` 在字典中，则从节点 `i` 到节点 `j` 有一条边
- 使用 BFS 检查是否能到达终点

### Python

```python
def word_break_bfs(s: str, wordDict: List[str]) -> bool:
    """
    BFS 解法

    时间复杂度: O(n^2)
    空间复杂度: O(n)
    """
    word_set = set(wordDict)
    n = len(s)
    visited = [False] * n
    queue = [0]  # 队列存储起始位置

    while queue:
        start = queue.pop(0)

        if visited[start]:
            continue
        visited[start] = True

        for end in range(start + 1, n + 1):
            if s[start:end] in word_set:
                if end == n:
                    return True
                queue.append(end)

    return False
```

### C++

```cpp
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
using namespace std;

bool wordBreakBFS(string s, vector<string>& wordDict) {
    unordered_set<string> word_set(wordDict.begin(), wordDict.end());
    int n = s.length();
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);

    while (!q.empty()) {
        int start = q.front();
        q.pop();

        if (visited[start]) {
            continue;
        }
        visited[start] = true;

        for (int end = start + 1; end <= n; end++) {
            string word = s.substr(start, end - start);
            if (word_set.count(word)) {
                if (end == n) {
                    return true;
                }
                q.push(end);
            }
        }
    }

    return false;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 动态规划 | O(n^2) | O(n) | 标准解法，易于理解和实现 |
| 记忆化回溯 | O(n^2) | O(n) | 递归实现，可能有重复子问题 |
| BFS | O(n^2) | O(n) | 图搜索思路，直观但实现稍复杂 |

## 总结

- **动态规划是最佳选择**，代码简洁，时间复杂度最优
- 核心思想：将问题分解为子问题，利用子问题的解构建原问题的解
- 状态转移是关键，需要仔细分析如何从子问题的解推导出当前问题的解
- 所有解法的本质都是搜索，但动态规划通过递推避免了重复计算
- 注意将字典转换为集合以提升查找效率
