---
title: "17. 电话号码的字母组合"
difficulty: "中等"
description: "给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按任意顺序返回。"
---

# 17. 电话号码的字母组合

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个仅包含数字 `2-9` 的字符串，返回所有它能表示的字母组合。

答案可以按任意顺序返回。

数字到字母的映射（就像在电话按键上一样）如下：

```
2: abc
3: def
4: ghi
5: jkl
6: mno
7: pqrs
8: tuv
9: wxyz
```

### 示例

```text
输入：digits = "23"
输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]
```

```text
输入：digits = ""
输出：[]
```

```text
输入：digits = "2"
输出：["a", "b", "c"]
```

## 解法一：回溯算法（推荐）

### 思路

回溯算法是解决这类组合问题的经典方法：

1. 建立数字到字母的映射表
2. 使用递归函数 `backtrack(index, path)`：
   - `index`：当前处理的数字位置
   - `path`：当前已构建的字母组合
3. 当 `index == len(digits)` 时，将当前组合加入结果
4. 否则，遍历当前数字对应的所有字母，递归处理下一个数字

### Python

```python
from typing import List

def letter_combinations(digits: str) -> List[str]:
    """
    回溯算法解法

    时间复杂度: O(4^n)，其中 n 是 digits 的长度
    空间复杂度: O(n)，递归栈深度
    """
    if not digits:
        return []

    # 数字到字母的映射
    phone_map = {
        '2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxyz'
    }

    def backtrack(index: int, path: str):
        # 当前组合完成，添加到结果
        if index == len(digits):
            result.append(path)
            return

        # 获取当前数字对应的字母
        letters = phone_map[digits[index]]
        for letter in letters:
            # 选择当前字母
            backtrack(index + 1, path + letter)

    result: List[str] = []
    backtrack(0, "")
    return result
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

class Solution {
private:
    unordered_map<char, string> phone_map;
    vector<string> result;

    void backtrack(const string& digits, int index, string& path) {
        // 当前组合完成，添加到结果
        if (index == digits.length()) {
            result.push_back(path);
            return;
        }

        // 获取当前数字对应的字母
        char digit = digits[index];
        const string& letters = phone_map[digit];
        for (char letter : letters) {
            // 选择当前字母
            path.push_back(letter);
            backtrack(digits, index + 1, path);
            path.pop_back();  // 回溯
        }
    }

public:
    Solution() {
        // 初始化数字到字母的映射
        phone_map = {
            {'2', "abc"},
            {'3', "def"},
            {'4', "ghi"},
            {'5', "jkl"},
            {'6', "mno"},
            {'7', "pqrs"},
            {'8', "tuv"},
            {'9', "wxyz"}
        };
    }

    vector<string> letterCombinations(string digits) {
        if (digits.empty()) {
            return {};
        }

        result.clear();
        string path;
        backtrack(digits, 0, path);
        return result;
    }
};
```

## 解法二：迭代解法

### 思路

使用迭代的方式逐步构建结果：

1. 初始化结果为包含空字符串的列表：`[""]`
2. 遍历每个数字：
   - 对当前结果中的每个组合，添加该数字对应的每个字母
   - 生成新的组合列表
3. 最终结果即为所有字母组合

### Python

```python
def letter_combinations_iterative(digits: str) -> List[str]:
    """
    迭代解法

    时间复杂度: O(4^n)
    空间复杂度: O(4^n)
    """
    if not digits:
        return []

    phone_map = {
        '2': 'abc',
        '3': 'def',
        '4': 'ghi',
        '5': 'jkl',
        '6': 'mno',
        '7': 'pqrs',
        '8': 'tuv',
        '9': 'wxyz'
    }

    result = [""]

    for digit in digits:
        letters = phone_map[digit]
        new_result = []

        for combination in result:
            for letter in letters:
                new_result.append(combination + letter)

        result = new_result

    return result
```

### C++

```cpp
vector<string> letterCombinationsIterative(string digits) {
    if (digits.empty()) {
        return {};
    }

    unordered_map<char, string> phone_map = {
        {'2', "abc"},
        {'3', "def"},
        {'4', "ghi"},
        {'5', "jkl"},
        {'6', "mno"},
        {'7', "pqrs"},
        {'8', "tuv"},
        {'9', "wxyz"}
    };

    vector<string> result = {""};

    for (char digit : digits) {
        const string& letters = phone_map[digit];
        vector<string> new_result;

        for (const string& combination : result) {
            for (char letter : letters) {
                new_result.push_back(combination + letter);
            }
        }

        result = move(new_result);
    }

    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 回溯算法 | O(4^n) | O(n) | 递归实现，代码简洁 |
| 迭代解法 | O(4^n) | O(4^n) | 迭代实现，易于理解 |

**说明**：时间复杂度中的 4 是每个数字对应的最大字母数（例如 7 和 9 有 4 个字母）。

## 总结

- **回溯算法**是解决组合类问题的通用方法，代码简洁但需要理解递归思想
- **迭代解法**更直观，通过逐步构建结果列表
- 两种方法的时间复杂度相同，实际性能差异很小
- 注意处理空输入的特殊情况
