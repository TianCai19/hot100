---
title: "20. 有效的括号"
difficulty: "简单"
description: "给定一个只包含 '('，')'，'{'，'}'，'['，']' 的字符串 s，判断字符串是否有效。有效字符串需满足：左括号必须用相同类型的右括号闭合，左括号必须以正确的顺序闭合。"
---

# 20. 有效的括号

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给定一个只包含 `'('，')'，'{'，'}'，'['，']'` 的字符串 `s`，判断字符串是否有效。

有效字符串需满足：
- 左括号必须用相同类型的右括号闭合
- 左括号必须以正确的顺序闭合

### 示例

```text
输入：s = "()"
输出：true
```

```text
输入：s = "()[]{}"
输出：true
```

```text
输入：s = "(]"
输出：false
```

```text
输入：s = "([)]"
输出：false
```

```text
输入：s = "{[]}"
输出：true
```

## 解法一：栈（推荐）

### 思路

使用栈来匹配括号：

1. 遍历字符串中的每个字符
2. 如果是左括号（`(`、`[`、`{`），压入栈中
3. 如果是右括号（`)`、`]`、`}`）：
   - 检查栈是否为空（空栈表示没有对应的左括号）
   - 检查栈顶元素是否与当前右括号匹配
   - 如果不匹配，返回 `false`
4. 遍历结束后，如果栈为空则所有括号都匹配，返回 `true`

### Python

```python
def is_valid(s: str) -> bool:
    """
    栈解法

    时间复杂度: O(n)，其中 n 是字符串长度
    空间复杂度: O(n)，最坏情况下栈中存储所有左括号
    """
    # 使用字典建立右括号到左括号的映射
    bracket_map = {')': '(', ']': '[', '}': '{'}
    stack = []

    for char in s:
        if char in bracket_map:
            # 如果是右括号
            if not stack or stack[-1] != bracket_map[char]:
                # 栈为空或栈顶不匹配
                return False
            stack.pop()  # 匹配成功，弹出栈顶
        else:
            # 如果是左括号，压入栈中
            stack.append(char)

    # 遍历结束后栈为空表示所有括号都匹配
    return len(stack) == 0
```

### C++

```cpp
#include <iostream>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    bool isValid(string s) {
        unordered_map<char, char> bracket_map = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        stack<char> st;

        for (char c : s) {
            if (bracket_map.count(c)) {
                // 如果是右括号
                if (st.empty() || st.top() != bracket_map[c]) {
                    // 栈为空或栈顶不匹配
                    return false;
                }
                st.pop();  // 匹配成功，弹出栈顶
            } else {
                // 如果是左括号，压入栈中
                st.push(c);
            }
        }

        // 遍历结束后栈为空表示所有括号都匹配
        return st.empty();
    }
};
```

## 解法二：栈 + 替换法

### 思路

通过不断替换相邻的有效括号对来消解：

1. 重复以下过程直到字符串不再变化：
   - 查找 `"()"`, `"[]"`, `"{}"` 这些相邻的有效括号对
   - 将它们替换为空字符串
2. 如果最终字符串为空，则括号有效

这种方法直观但效率较低。

### Python

```python
def is_valid_replace(s: str) -> bool:
    """
    替换解法

    时间复杂度: O(n^2)
    空间复杂度: O(n)
    """
    # 持续替换有效的括号对
    while '()' in s or '[]' in s or '{}' in s:
        s = s.replace('()', '')
        s = s.replace('[]', '')
        s = s.replace('{}', '')

    return len(s) == 0
```

### C++

```cpp
bool isValidReplace(string s) {
    // 持续替换有效的括号对
    bool changed = true;
    while (changed) {
        changed = false;
        size_t pos;
        if ((pos = s.find("()")) != string::npos) {
            s.erase(pos, 2);
            changed = true;
        }
        if ((pos = s.find("[]")) != string::npos) {
            s.erase(pos, 2);
            changed = true;
        }
        if ((pos = s.find("{}")) != string::npos) {
            s.erase(pos, 2);
            changed = true;
        }
    }

    return s.empty();
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 栈解法 | O(n) | O(n) | 高效，一次遍历解决 |
| 替换解法 | O(n^2) | O(n) | 直观易懂，但效率较低 |

## 总结

- **栈解法**是解决括号匹配问题的标准方法，时间效率高
- **替换解法**更直观，但需要多次遍历字符串，效率较低
- 关键点是：右括号必须与最近且未匹配成功的左括号匹配
- 注意处理空字符串（应返回 `true`）和奇数长度的字符串（应返回 `false`）
