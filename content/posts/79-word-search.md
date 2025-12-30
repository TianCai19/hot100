---
title: "79. 单词搜索"
difficulty: "中等"
description: "给定一个 m x n 二维字符网格 board 和一个字符串单词 word。如果 word 存在于网格中，返回 true；否则，返回 false。单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中相邻单元格是水平或垂直相邻的单元格。"
---

# 79. 单词搜索

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个 `m x n` 二维字符网格 `board` 和一个字符串单词 `word`。

如果 `word` 存在于网格中，返回 `true`；否则，返回 `false`。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中相邻单元格是水平或垂直相邻的单元格。

同一个单元格内的字母不允许被重复使用。

### 示例

```text
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
解释：网格中存在路径：A -> B -> C -> C -> E -> D
```

```text
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
输出：true
解释：网格中存在路径：S -> E -> E
```

```text
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
输出：false
```

## 解法一：回溯算法（推荐）

### 思路

使用回溯算法（深度优先搜索）遍历网格：

1. **起点搜索**：遍历网格中的每个单元格作为起点
2. **深度优先搜索**：
   - 检查当前单元格是否匹配当前字符
   - 标记当前单元格为已访问（避免重复使用）
   - 向四个方向递归搜索
   - 回溯时恢复单元格状态
3. **剪枝优化**：
   - 边界检查
   - 字符匹配检查
   - 访问标记检查

### Python

```python
from typing import List

def exist(board: List[List[str]], word: str) -> bool:
    """
    回溯算法解法

    时间复杂度: O(m * n * 4^k)，其中 m, n 是网格尺寸，k 是单词长度
    空间复杂度: O(m * n)，递归栈和访问标记
    """
    m, n = len(board), len(board[0])

    def backtrack(row: int, col: int, index: int) -> bool:
        """
        从 (row, col) 开始搜索 word[index:]

        Args:
            row, col: 当前搜索位置
            index: 当前要匹配的字符在 word 中的索引

        Returns:
            bool: 是否找到剩余字符
        """
        # 所有字符都匹配成功
        if index == len(word):
            return True

        # 边界检查
        if row < 0 or row >= m or col < 0 or col >= n:
            return False

        # 字符匹配检查
        if board[row][col] != word[index]:
            return False

        # 标记当前单元格为已访问（使用特殊标记）
        temp = board[row][col]
        board[row][col] = '#'

        # 向四个方向搜索
        found = (
            backtrack(row - 1, col, index + 1) or  # 上
            backtrack(row + 1, col, index + 1) or  # 下
            backtrack(row, col - 1, index + 1) or  # 左
            backtrack(row, col + 1, index + 1)     # 右
        )

        # 回溯：恢复单元格状态
        board[row][col] = temp

        return found

    # 遍历每个单元格作为起点
    for i in range(m):
        for j in range(n):
            if backtrack(i, j, 0):
                return True

    return False
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Solution {
private:
    int m, n;
    string word;

    bool backtrack(vector<vector<char>>& board, int row, int col, int index) {
        // 所有字符都匹配成功
        if (index == word.length()) {
            return true;
        }

        // 边界检查
        if (row < 0 || row >= m || col < 0 || col >= n) {
            return false;
        }

        // 字符匹配检查
        if (board[row][col] != word[index]) {
            return false;
        }

        // 标记当前单元格为已访问
        char temp = board[row][col];
        board[row][col] = '#';

        // 向四个方向搜索
        bool found = backtrack(board, row - 1, col, index + 1) ||  // 上
                     backtrack(board, row + 1, col, index + 1) ||  // 下
                     backtrack(board, row, col - 1, index + 1) ||  // 左
                     backtrack(board, row, col + 1, index + 1);    // 右

        // 回溯：恢复单元格状态
        board[row][col] = temp;

        return found;
    }

public:
    bool exist(vector<vector<char>>& board, string word) {
        m = board.size();
        n = board[0].size();
        this->word = word;

        // 遍历每个单元格作为起点
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (backtrack(board, i, j, 0)) {
                    return true;
                }
            }
        }

        return false;
    }
};
```

## 解法二：优化的回溯（添加访问标记数组）

### 思路

使用额外的 `visited` 数组记录访问状态，避免修改原始网格：

1. 创建 `visited` 布尔矩阵记录访问状态
2. 深度优先搜索时检查和更新访问标记
3. 回溯时重置访问标记

### Python

```python
def exist_optimized(board: List[List[str]], word: str) -> bool:
    """
    优化的回溯算法（使用访问标记数组）

    时间复杂度: O(m * n * 4^k)
    空间复杂度: O(m * n)，访问标记数组 + 递归栈
    """
    m, n = len(board), len(board[0])
    visited = [[False] * n for _ in range(m)]

    def backtrack(row: int, col: int, index: int) -> bool:
        if index == len(word):
            return True

        if row < 0 or row >= m or col < 0 or col >= n:
            return False

        if visited[row][col] or board[row][col] != word[index]:
            return False

        # 标记当前单元格为已访问
        visited[row][col] = True

        # 向四个方向搜索
        found = (
            backtrack(row - 1, col, index + 1) or
            backtrack(row + 1, col, index + 1) or
            backtrack(row, col - 1, index + 1) or
            backtrack(row, col + 1, index + 1)
        )

        # 回溯：重置访问标记
        visited[row][col] = False

        return found

    for i in range(m):
        for j in range(n):
            if backtrack(i, j, 0):
                return True

    return False
```

## 解法三：优化的起点选择（提前剪枝）

### 思路

在开始搜索前，先统计每个字符的出现次数：

1. 如果单词中的某个字符在网格中不存在，直接返回 false
2. 如果单词首字符在网格中出现次数过少，可能提前剪枝
3. 优化搜索顺序，优先选择匹配度高的起点

### Python

```python
from collections import Counter

def exist_with_pruning(board: List[List[str]], word: str) -> bool:
    """
    优化起点选择的回溯算法

    时间复杂度: O(m * n * 4^k)
    空间复杂度: O(m * n)
    """
    m, n = len(board), len(board[0])

    # 统计网格中所有字符
    board_chars = []
    for row in board:
        board_chars.extend(row)
    board_counter = Counter(board_chars)

    # 统计单词中所有字符
    word_counter = Counter(word)

    # 提前剪枝：检查单词中的字符是否都在网格中存在
    for char, count in word_counter.items():
        if board_counter[char] < count:
            return False

    visited = [[False] * n for _ in range(m)]

    def backtrack(row: int, col: int, index: int) -> bool:
        if index == len(word) - 1:
            return True

        if row < 0 or row >= m or col < 0 or col >= n:
            return False

        if visited[row][col] or board[row][col] != word[index]:
            return False

        visited[row][col] = True

        found = (
            backtrack(row - 1, col, index + 1) or
            backtrack(row + 1, col, index + 1) or
            backtrack(row, col - 1, index + 1) or
            backtrack(row, col + 1, index + 1)
        )

        visited[row][col] = False

        return found

    # 优化起点选择：只从与单词首字符匹配的单元格开始
    first_char = word[0]
    for i in range(m):
        for j in range(n):
            if board[i][j] == first_char:
                if backtrack(i, j, 0):
                    return True

    return False
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 基础回溯 | O(m * n * 4^k) | O(m * n) | 修改原网格，代码简洁 |
| 标记数组回溯 | O(m * n * 4^k) | O(m * n) | 保持原网格，状态清晰 |
| 优化起点回溯 | O(m * n * 4^k) | O(m * n) | 提前剪枝，减少搜索空间 |

**说明**：其中 m、n 是网格的尺寸，k 是单词长度，4^k 表示每个字符最多有 4 个方向选择。

## 总结

- **回溯算法**是解决矩阵路径问题的经典方法，通过深度优先搜索探索所有可能路径
- **状态标记**是关键：可以使用原网格修改或额外的访问数组
- **剪枝优化**很重要：边界检查、字符匹配、访问标记等
- **时间复杂度**较高，但实际表现良好，特别是对于较短的单词
- 注意处理**回溯**过程，确保访问状态正确恢复
- 可以通过**字符频率分析**进行提前剪枝，减少不必要的搜索
