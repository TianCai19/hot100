---
title: "200. 岛屿数量"
difficulty: "中等"
description: "计算二维网格中由 '1'（陆地）组成的岛屿数量。"
---

# 200. 岛屿数量

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个由 `'1'`（陆地）和 `'0'`（水）组成的的二维网格 `grid`，请你计算网格中岛屿的数量。

岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接组成。

此外，你可以假设网格的四个边界都被水包围。

### 示例

**示例 1：**
```
输入：grid = [
  ["1","1","1","1","0"],
  ["1","1","0","1","0"],
  ["1","1","0","0","0"],
  ["0","0","0","0","0"]
]
输出：1
```

**示例 2：**
```
输入：grid = [
  ["1","1","0","0","0"],
  ["1","1","0","0","0"],
  ["0","0","1","0","0"],
  ["0","0","0","1","1"]
]
输出：3
```

### 提示

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 300`
- `grid[i][j]` 的值为 `'0'` 或 `'1'`

---

## 岛屿示意图

### 网格示例

```
示例 1 网格：          岛屿分布：
┌─────────────┐      ┌─────────────┐
│ 1 1 1 1 0  │      │ ■ ■ ■ ■ ~  │
│ 1 1 0 1 0  │  -->  │ ■ ■ ~ ■ ~  │
│ 1 1 0 0 0  │      │ ■ ■ ~ ~ ~  │
│ 0 0 0 0 0  │      │ ~ ~ ~ ~ ~  │
└─────────────┘      └─────────────┘
                     1 个岛屿

示例 2 网格：          岛屿分布：
┌─────────────┐      ┌─────────────┐
│ 1 1 0 0 0  │      │ ■ ■ ~ ~ ~  │
│ 1 1 0 0 0  │  -->  │ ■ ■ ~ ~ ~  │
│ 0 0 1 0 0  │      │ ~ ~ ■ ~ ~  │
│ 0 0 0 1 1  │      │ ~ ~ ~ ■ ■  │
└─────────────┘      └─────────────┘
                     3 个岛屿
```

### 连接规则

相邻陆地定义为：
- **水平相邻：** 左、右
- **竖直相邻：** 上、下

```
    上
左  ■  右
    下
```

---

## 解法一：DFS（深度优先搜索）

### 思路

使用深度优先搜索遍历整个网格：
1. 遍历网格中的每个单元格
2. 当遇到 `'1'`（陆地）时，计数器加一
3. 从该陆地开始，使用 DFS 访问所有相邻的陆地
4. 将访问过的陆地标记为 `'0'`（水），避免重复计数

**DFS 过程：**
```
遇到陆地 → 开始 DFS
  ↓
访问当前陆地 → 标记为 '0'
  ↓
向上下左右四个方向搜索
  ↓
遇到相邻陆地 → 递归 DFS
  ↓
直到没有相邻陆地 → 返回
```

### Python

```python
from typing import List

class Solution:
    def numIslands_dfs(self, grid: List[List[str]]) -> int:
        """
        DFS 算法 - 深度优先搜索
        时间复杂度: O(M × N)，M = 行数，N = 列数
        空间复杂度: O(M × N)，最坏情况为全为陆地时的递归栈深度
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        # 遍历每个单元格
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    island_count += 1
                    # 从当前位置开始 DFS
                    self._dfs(grid, r, c)

        return island_count

    def _dfs(self, grid: List[List[str]], r: int, c: int):
        """
        深度优先搜索，访问并标记相邻的陆地
        """
        rows, cols = len(grid), len(grid[0])

        # 边界检查
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == '0':
            return

        # 标记当前陆地（视为已访问）
        grid[r][c] = '0'

        # 递归访问四个方向
        self._dfs(grid, r - 1, c)  # 上
        self._dfs(grid, r + 1, c)  # 下
        self._dfs(grid, r, c - 1)  # 左
        self._dfs(grid, r, c + 1)  # 右
```

### C++

```cpp
#include <vector>
using namespace std;

class Solution {
private:
    int rows, cols;

    void dfs(vector<vector<char>>& grid, int r, int c) {
        // 边界检查
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == '0') {
            return;
        }

        // 标记当前陆地（视为已访问）
        grid[r][c] = '0';

        // 递归访问四个方向
        dfs(grid, r - 1, c);  // 上
        dfs(grid, r + 1, c);  // 下
        dfs(grid, r, c - 1);  // 左
        dfs(grid, r, c + 1);  // 右
    }

public:
    int numIslands_dfs(vector<vector<char>>& grid) {
        /**
         * DFS 算法 - 深度优先搜索
         * 时间复杂度: O(M × N)，M = 行数，N = 列数
         * 空间复杂度: O(M × N)，最坏情况为全为陆地时的递归栈深度
         */
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        rows = grid.size();
        cols = grid[0].size();
        int island_count = 0;

        // 遍历每个单元格
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    island_count++;
                    // 从当前位置开始 DFS
                    dfs(grid, r, c);
                }
            }
        }

        return island_count;
    }
};
```

### 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|-------|------|
| 时间复杂度 | O(M × N) | 每个单元格最多访问一次 |
| 空间复杂度 | O(M × N) | 最坏情况（全是陆地）递归栈深度为 M × N |

---

## 解法二：BFS（广度优先搜索）

### 思路

使用广度优先搜索遍历整个网格：
1. 遍历网格中的每个单元格
2. 当遇到 `'1'`（陆地）时，计数器加一
3. 从该陆地开始，使用 BFS 访问所有相邻的陆地
4. 将访问过的陆地标记为 `'0'`（水），避免重复计数

**BFS 过程：**
```
遇到陆地 → 开始 BFS
  ↓
加入队列 → 标记为 '0'
  ↓
取出队列头部
  ↓
检查四个方向 → 相邻陆地加入队列
  ↓
直到队列为空 → 完成一个岛屿
```

### Python

```python
from typing import List
from collections import deque

class Solution:
    def numIslands_bfs(self, grid: List[List[str]]) -> int:
        """
        BFS 算法 - 广度优先搜索
        时间复杂度: O(M × N)，M = 行数，N = 列数
        空间复杂度: O(min(M, N))，队列中最多存储一个岛屿的所有陆地
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        # 四个方向：上、下、左、右
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        # 遍历每个单元格
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    island_count += 1
                    # 从当前位置开始 BFS
                    queue = deque()
                    queue.append((r, c))
                    grid[r][c] = '0'  # 标记为已访问

                    # BFS 遍历
                    while queue:
                        cr, cc = queue.popleft()
                        # 检查四个方向
                        for dr, dc in directions:
                            nr, nc = cr + dr, cc + dc
                            # 边界检查和陆地检查
                            if (0 <= nr < rows and 0 <= nc < cols and
                                grid[nr][nc] == '1'):
                                queue.append((nr, nc))
                                grid[nr][nc] = '0'  # 标记为已访问

        return island_count
```

### C++

```cpp
#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int numIslands_bfs(vector<vector<char>>& grid) {
        /**
         * BFS 算法 - 广度优先搜索
         * 时间复杂度: O(M × N)，M = 行数，N = 列数
         * 空间复杂度: O(min(M, N))，队列中最多存储一个岛屿的所有陆地
         */
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        int rows = grid.size();
        int cols = grid[0].size();
        int island_count = 0;

        // 四个方向：上、下、左、右
        vector<pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        // 遍历每个单元格
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                if (grid[r][c] == '1') {
                    island_count++;
                    // 从当前位置开始 BFS
                    queue<pair<int, int>> q;
                    q.push({r, c});
                    grid[r][c] = '0';  // 标记为已访问

                    // BFS 遍历
                    while (!q.empty()) {
                        auto [cr, cc] = q.front();
                        q.pop();

                        // 检查四个方向
                        for (const auto& dir : directions) {
                            int nr = cr + dir.first;
                            int nc = cc + dir.second;

                            // 边界检查和陆地检查
                            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                                grid[nr][nc] == '1') {
                                q.push({nr, nc});
                                grid[nr][nc] = '0';  // 标记为已访问
                            }
                        }
                    }
                }
            }
        }

        return island_count;
    }
};
```

### 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|-------|------|
| 时间复杂度 | O(M × N) | 每个单元格最多访问一次 |
| 空间复杂度 | O(min(M, N)) | 队列中最多存储一个岛屿的所有陆地 |

---

## 两种解法对比

| 特征 | DFS | BFS |
|------|-----|-----|
| 实现方式 | 递归或显式栈 | 队列 |
| 空间效率 | 递归栈可能较深 | 队列更稳定 |
| 代码简洁性 | 递归代码更简洁 | 需要队列管理 |
| 性能 | 相同 | 相同 |
| 内存使用 | 可能出现栈溢出 | 更安全 |
| 遍历顺序 | 深度优先 | 广度优先 |

## 总结

- **DFS**和**BFS**都是解决岛屿问题的经典算法
- **核心思想：** 将二维网格视为图，每个陆地是图的节点
- **关键技巧：** 访问过的陆地标记为水，避免重复计数
- **时间复杂度：** 均为 O(M × N)，遍历整个网格一次
- **空间复杂度：** DFS 可能出现栈溢出，BFS 更安全
- **推荐使用：** BFS（更稳定）或显式栈的 DFS（避免递归栈溢出）
