---
title: "76. 最小覆盖子串"
difficulty: "困难"
description: "给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 \"\"。"
---

# 76. 最小覆盖子串

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给你一个字符串 `s`、一个字符串 `t`。

返回 `s` 中涵盖 `t` 所有字符的最小子串。如果 `s` 中不存在涵盖 `t` 所有字符的子串，则返回空字符串 `""`。

### 示例

```text
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串是 "BANC"
```

```text
输入：s = "a", t = "aa"
输出：""
```

## 解法一：滑动窗口 + 哈希表（推荐）

### 思路

滑动窗口是解决字符串子串问题的经典方法：

1. **初始化两个哈希表**：
   - `need`：记录目标字符串 `t` 中每个字符的需求数量
   - `window`：记录当前窗口中每个字符的实际数量

2. **扩张窗口**：
   - 移动右指针，扩展窗口
   - 更新 `window` 哈希表
   - 当某个字符的数量满足需求时，计数 `valid` 增加

3. **收缩窗口**：
   - 当 `valid == need.size()`（所有字符都满足需求）时，尝试收缩左指针
   - 更新最小覆盖子串的长度和起始位置
   - 收缩过程中更新 `window` 哈希表和 `valid`

4. **返回结果**：
   - 遍历结束后，返回最小覆盖子串

### Python

```python
from typing import Dict
from collections import Counter, defaultdict

def min_window(s: str, t: str) -> str:
    """
    滑动窗口解法

    时间复杂度: O(|s| + |t|)，其中 |s| 是字符串 s 的长度
    空间复杂度: O(|Σ|)，其中 Σ 是字符集的大小（最多 128 或 256 个 ASCII 字符）
    """
    if not s or not t or len(s) < len(t):
        return ""

    # 统计目标字符串 t 中每个字符的需求数量
    need: Dict[str, int] = Counter(t)
    # 字符集大小
    need_size = len(need)

    # 窗口中字符的实际数量
    window: Dict[str, int] = defaultdict(int)

    left = 0
    right = 0
    valid = 0
    # 记录最小覆盖子串的起始位置和长度
    start = 0
    min_len = float('inf')

    while right < len(s):
        # 扩张右边界
        c = s[right]
        if c in need:
            window[c] += 1
            if window[c] == need[c]:
                valid += 1

        # 当所有字符都满足需求时，尝试收缩左边界
        while valid == need_size:
            # 更新最小覆盖子串
            if right - left + 1 < min_len:
                start = left
                min_len = right - left + 1

            # 收缩左边界
            d = s[left]
            if d in need:
                if window[d] == need[d]:
                    valid -= 1
                window[d] -= 1
            left += 1

        right += 1

    return s[start:start + min_len] if min_len != float('inf') else ""
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        unordered_map<char, int> need, window;
        // 统计目标字符串 t 中每个字符的需求数量
        for (char c : t) {
            need[c]++;
        }

        int left = 0, right = 0;
        int valid = 0;
        int start = 0;
        int min_len = INT_MAX;
        int need_size = need.size();

        while (right < s.length()) {
            // 扩张右边界
            char c = s[right];
            if (need.find(c) != need.end()) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }

            // 当所有字符都满足需求时，尝试收缩左边界
            while (valid == need_size) {
                // 更新最小覆盖子串
                if (right - left + 1 < min_len) {
                    start = left;
                    min_len = right - left + 1;
                }

                // 收缩左边界
                char d = s[left];
                if (need.find(d) != need.end()) {
                    if (window[d] == need[d]) {
                        valid--;
                    }
                    window[d]--;
                }
                left++;
            }

            right++;
        }

        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};
```

## 解法二：优化的滑动窗口（预检查优化）

### 思路

在滑动窗口基础上，先对字符串 `s` 进行预检查，过滤掉不可能的字符，提高效率。

### Python

```python
def min_window_optimized(s: str, t: str) -> str:
    """
    优化的滑动窗口解法

    先进行预检查，只保留 s 中在 t 中出现的字符
    时间复杂度: O(|s| + |t|)
    空间复杂度: O(|Σ|)
    """
    if not s or not t or len(s) < len(t):
        return ""

    # 统计 t 中每个字符的需求数量
    t_count = Counter(t)
    required = len(t_count)

    # 预检查：过滤掉 s 中不在 t 中的字符
    filtered_s = []
    filtered_index = []
    for i, char in enumerate(s):
        if char in t_count:
            filtered_s.append(char)
            filtered_index.append(i)

    if not filtered_s:
        return ""

    # 滑动窗口
    window = Counter()
    left = 0
    right = 0
    formed = 0
    window_count = {}

    # 结果：[最小长度, 左边界索引, 右边界索引, 原始字符串起始位置]
    ans = float('inf'), None, None, None

    while right < len(filtered_s):
        character = filtered_s[right]
        window_count[character] = window_count.get(character, 0) + 1

        if window_count[character] == t_count[character]:
            formed += 1

        # 尝试并收缩窗口，直到它不再是必需的
        while left <= right and formed == required:
            character = filtered_s[left]

            # 更新最小窗口
            end_index = filtered_index[right]
            start_index = filtered_index[left]
            if end_index - start_index + 1 < ans[0]:
                ans = (end_index - start_index + 1, start_index, end_index, start_index)

            # 移除左侧字符
            window_count[character] -= 1
            if window_count[character] < t_count[character]:
                formed -= 1

            left += 1

        right += 1

    return "" if ans[0] == float('inf') else s[ans[1]:ans[2] + 1]
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 基础滑动窗口 | O(\|s\| + \|t\|) | O(\|Σ\|) | 标准实现，思路清晰 |
| 优化的滑动窗口 | O(\|s\| + \|t\|) | O(\|Σ\|) | 预过滤字符，常数因子更小 |

**说明**：其中 \|s\| 是字符串 s 的长度，\|t\| 是字符串 t 的长度，\|Σ\| 是字符集大小（ASCII 字符最多 256）。

## 总结

- **滑动窗口**是解决子串问题的通用方法，通过左右指针动态调整窗口大小
- **哈希表**用于快速统计字符需求和实际数量
- **双层循环**确保所有情况都被覆盖：外层扩张窗口，内层收缩窗口
- 关键在于正确处理 `valid` 计数，判断窗口是否满足条件
- 注意边界条件的处理，如空字符串、字符不存在等情况
