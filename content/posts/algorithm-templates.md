---
title: "Python 算法模板速查"
difficulty: "文档"
description: "LeetCode 常用算法模板，直接套用"
---

# Python 算法模板速查

## 📊 拓扑排序

### Kahn 算法 (BFS)
```python
from collections import deque, defaultdict

def topological_sort(n, edges):
    """
    n: 节点数量 (0 到 n-1)
    edges: 边列表 [(u, v), ...] 表示 u -> v
    返回: 拓扑排序结果，若有环返回空列表
    """
    graph = defaultdict(list)
    indegree = [0] * n

    for u, v in edges:
        graph[u].append(v)
        indegree[v] += 1

    # 入度为0的节点入队
    queue = deque([i for i in range(n) if indegree[i] == 0])
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    return result if len(result) == n else []  # 有环则返回空

# 使用示例 - 课程表问题
# edges = [[1,0], [2,0], [3,1], [3,2]]  # 课程1依赖0，课程2依赖0...
# order = topological_sort(4, edges)
```

### DFS 版本
```python
def topological_sort_dfs(n, edges):
    """DFS 后序遍历 + 逆序"""
    graph = defaultdict(list)
    for u, v in edges:
        graph[u].append(v)

    # 0: 未访问, 1: 访问中, 2: 已完成
    state = [0] * n
    result = []
    has_cycle = False

    def dfs(node):
        nonlocal has_cycle
        if state[node] == 1:  # 发现环
            has_cycle = True
            return
        if state[node] == 2:
            return

        state[node] = 1
        for neighbor in graph[node]:
            dfs(neighbor)
            if has_cycle:
                return
        state[node] = 2
        result.append(node)

    for i in range(n):
        if state[i] == 0:
            dfs(i)
            if has_cycle:
                return []

    return result[::-1]
```

## 🔗 并查集 (Union-Find)

### 基础版本
```python
class UnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        """路径压缩"""
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        """按秩合并，返回是否合并成功"""
        px, py = self.find(x), self.find(y)
        if px == py:
            return False  # 已在同一集合
        if self.rank[px] < self.rank[py]:
            px, py = py, px
        self.parent[py] = px
        if self.rank[px] == self.rank[py]:
            self.rank[px] += 1
        return True

    def connected(self, x, y):
        return self.find(x) == self.find(y)

# 使用示例 - 检测图中是否有环
# uf = UnionFind(n)
# for u, v in edges:
#     if not uf.union(u, v):
#         print("有环!")
```

### 带权并查集
```python
class WeightedUnionFind:
    def __init__(self, n):
        self.parent = list(range(n))
        self.weight = [1.0] * n  # weight[i] 表示 i 到 parent[i] 的权重

    def find(self, x):
        if self.parent[x] != x:
            root = self.find(self.parent[x])
            self.weight[x] *= self.weight[self.parent[x]]
            self.parent[x] = root
        return self.parent[x]

    def union(self, x, y, w):
        """x / y = w"""
        px, py = self.find(x), self.find(y)
        if px == py:
            return
        # x -> px 权重为 weight[x]
        # y -> py 权重为 weight[y]
        # 需要 px -> py 权重为 w * weight[y] / weight[x]
        self.parent[px] = py
        self.weight[px] = w * self.weight[y] / self.weight[x]

    def query(self, x, y):
        """返回 x / y，不连通返回 -1"""
        if self.find(x) != self.find(y):
            return -1.0
        return self.weight[x] / self.weight[y]
```

## 🔍 二分查找

### 标准模板
```python
def binary_search(arr, target):
    """查找 target，返回索引或 -1"""
    left, right = 0, len(arr) - 1
    while left <= right:
        mid = (left + right) // 2
        if arr[mid] == target:
            return mid
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    return -1
```

### 左边界 (第一个 >= target)
```python
def lower_bound(arr, target):
    """返回第一个 >= target 的索引"""
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] < target:
            left = mid + 1
        else:
            right = mid
    return left

# bisect.bisect_left(arr, target) 等价
```

### 右边界 (第一个 > target)
```python
def upper_bound(arr, target):
    """返回第一个 > target 的索引"""
    left, right = 0, len(arr)
    while left < right:
        mid = (left + right) // 2
        if arr[mid] <= target:
            left = mid + 1
        else:
            right = mid
    return left

# bisect.bisect_right(arr, target) 等价
```

### 二分答案模板
```python
def binary_search_answer(check, lo, hi):
    """
    二分答案：找满足 check(x) 的最小/最大 x
    check: 判断函数
    """
    while lo < hi:
        mid = (lo + hi) // 2
        if check(mid):
            hi = mid      # 找最小满足条件的值
            # lo = mid + 1  # 找最大满足条件的值
        else:
            lo = mid + 1  # 找最小
            # hi = mid      # 找最大
    return lo
```

## 🌲 DFS / BFS 模板

### 网格 DFS
```python
def dfs_grid(grid, i, j, visited):
    """网格 DFS，适用于岛屿类问题"""
    m, n = len(grid), len(grid[0])
    if i < 0 or i >= m or j < 0 or j >= n:
        return
    if (i, j) in visited or grid[i][j] == '0':
        return

    visited.add((i, j))
    for di, dj in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        dfs_grid(grid, i + di, j + dj, visited)

# 四方向移动
DIRECTIONS = [(0, 1), (0, -1), (1, 0), (-1, 0)]
# 八方向移动
DIRECTIONS_8 = [(0, 1), (0, -1), (1, 0), (-1, 0),
                (1, 1), (1, -1), (-1, 1), (-1, -1)]
```

### 网格 BFS
```python
from collections import deque

def bfs_grid(grid, start):
    """网格 BFS，适用于最短路径"""
    m, n = len(grid), len(grid[0])
    queue = deque([start])
    visited = {start}
    distance = 0

    while queue:
        for _ in range(len(queue)):  # 层级遍历
            x, y = queue.popleft()
            for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and (nx, ny) not in visited:
                    if grid[nx][ny] == 'target':
                        return distance + 1
                    visited.add((nx, ny))
                    queue.append((nx, ny))
        distance += 1
    return -1
```

### 图 BFS (最短路)
```python
def bfs_shortest_path(graph, start, end):
    """无权图最短路径"""
    queue = deque([(start, [start])])
    visited = {start}

    while queue:
        node, path = queue.popleft()
        if node == end:
            return path
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append((neighbor, path + [neighbor]))
    return []
```

## 🔙 回溯模板

### 子集
```python
def subsets(nums):
    result = []

    def backtrack(start, path):
        result.append(path[:])  # 收集所有节点
        for i in range(start, len(nums)):
            path.append(nums[i])
            backtrack(i + 1, path)
            path.pop()

    backtrack(0, [])
    return result
```

### 组合
```python
def combine(n, k):
    result = []

    def backtrack(start, path):
        if len(path) == k:
            result.append(path[:])
            return
        # 剪枝: 还需要 k - len(path) 个元素
        for i in range(start, n - (k - len(path)) + 2):
            path.append(i)
            backtrack(i + 1, path)
            path.pop()

    backtrack(1, [])
    return result
```

### 全排列
```python
def permute(nums):
    result = []

    def backtrack(path, used):
        if len(path) == len(nums):
            result.append(path[:])
            return
        for i in range(len(nums)):
            if used[i]:
                continue
            used[i] = True
            path.append(nums[i])
            backtrack(path, used)
            path.pop()
            used[i] = False

    backtrack([], [False] * len(nums))
    return result
```

### 全排列 (有重复元素)
```python
def permuteUnique(nums):
    result = []
    nums.sort()  # 排序以便去重

    def backtrack(path, used):
        if len(path) == len(nums):
            result.append(path[:])
            return
        for i in range(len(nums)):
            if used[i]:
                continue
            # 去重: 相同元素，前一个没用过则跳过
            if i > 0 and nums[i] == nums[i-1] and not used[i-1]:
                continue
            used[i] = True
            path.append(nums[i])
            backtrack(path, used)
            path.pop()
            used[i] = False

    backtrack([], [False] * len(nums))
    return result
```

## 📈 动态规划模板

### 一维 DP
```python
# 爬楼梯 / 斐波那契
def climb_stairs(n):
    if n <= 2:
        return n
    dp = [0] * (n + 1)
    dp[1], dp[2] = 1, 2
    for i in range(3, n + 1):
        dp[i] = dp[i-1] + dp[i-2]
    return dp[n]

# 空间优化
def climb_stairs_opt(n):
    if n <= 2:
        return n
    prev, curr = 1, 2
    for _ in range(3, n + 1):
        prev, curr = curr, prev + curr
    return curr
```

### 二维 DP (路径问题)
```python
def unique_paths(m, n):
    dp = [[1] * n for _ in range(m)]
    for i in range(1, m):
        for j in range(1, n):
            dp[i][j] = dp[i-1][j] + dp[i][j-1]
    return dp[m-1][n-1]

# 空间优化
def unique_paths_opt(m, n):
    dp = [1] * n
    for _ in range(1, m):
        for j in range(1, n):
            dp[j] += dp[j-1]
    return dp[n-1]
```

### 背包 DP
```python
# 0-1 背包
def knapsack_01(weights, values, capacity):
    n = len(weights)
    dp = [0] * (capacity + 1)
    for i in range(n):
        for j in range(capacity, weights[i] - 1, -1):  # 逆序
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i])
    return dp[capacity]

# 完全背包
def knapsack_complete(weights, values, capacity):
    dp = [0] * (capacity + 1)
    for i in range(len(weights)):
        for j in range(weights[i], capacity + 1):  # 正序
            dp[j] = max(dp[j], dp[j - weights[i]] + values[i])
    return dp[capacity]
```

### 区间 DP
```python
def interval_dp(arr):
    """区间 DP 模板，如戳气球、合并石子"""
    n = len(arr)
    dp = [[0] * n for _ in range(n)]

    # 枚举区间长度
    for length in range(2, n + 1):
        for i in range(n - length + 1):
            j = i + length - 1
            for k in range(i, j):  # 枚举分割点
                dp[i][j] = max(dp[i][j], dp[i][k] + dp[k+1][j] + cost(i, j, k))

    return dp[0][n-1]
```

## 📚 单调栈

### 下一个更大元素
```python
def next_greater_element(nums):
    """返回每个元素右边第一个比它大的元素，没有则 -1"""
    n = len(nums)
    result = [-1] * n
    stack = []  # 存索引，单调递减栈

    for i in range(n):
        while stack and nums[i] > nums[stack[-1]]:
            result[stack.pop()] = nums[i]
        stack.append(i)

    return result
```

### 柱状图最大矩形
```python
def largest_rectangle_area(heights):
    heights = [0] + heights + [0]  # 哨兵
    stack = [0]
    max_area = 0

    for i in range(1, len(heights)):
        while heights[i] < heights[stack[-1]]:
            h = heights[stack.pop()]
            w = i - stack[-1] - 1
            max_area = max(max_area, h * w)
        stack.append(i)

    return max_area
```

## 🪟 滑动窗口

### 固定窗口
```python
def fixed_window(arr, k):
    """固定大小为 k 的滑动窗口"""
    window_sum = sum(arr[:k])
    result = [window_sum]

    for i in range(k, len(arr)):
        window_sum += arr[i] - arr[i - k]
        result.append(window_sum)

    return result
```

### 变长窗口
```python
def variable_window(s, target):
    """
    变长滑动窗口模板
    找满足某条件的最短/最长子串
    """
    from collections import defaultdict

    window = defaultdict(int)
    left = 0
    result = float('inf')  # 或 0

    for right in range(len(s)):
        # 扩展窗口
        window[s[right]] += 1

        # 收缩窗口
        while valid(window, target):  # 满足条件时收缩
            result = min(result, right - left + 1)
            window[s[left]] -= 1
            left += 1

    return result if result != float('inf') else -1
```

## 🔢 前缀和

### 一维前缀和
```python
def prefix_sum(nums):
    prefix = [0]
    for num in nums:
        prefix.append(prefix[-1] + num)
    return prefix

# 区间和 [i, j] = prefix[j+1] - prefix[i]
```

### 二维前缀和
```python
def prefix_sum_2d(matrix):
    m, n = len(matrix), len(matrix[0])
    prefix = [[0] * (n + 1) for _ in range(m + 1)]

    for i in range(1, m + 1):
        for j in range(1, n + 1):
            prefix[i][j] = (prefix[i-1][j] + prefix[i][j-1]
                          - prefix[i-1][j-1] + matrix[i-1][j-1])
    return prefix

# 子矩阵和 (r1,c1) 到 (r2,c2)
# = prefix[r2+1][c2+1] - prefix[r1][c2+1] - prefix[r2+1][c1] + prefix[r1][c1]
```

## 🎯 常用技巧

### 快慢指针 (链表)
```python
def find_cycle(head):
    """检测链表环"""
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
        if slow == fast:
            return True
    return False

def find_middle(head):
    """找链表中点"""
    slow = fast = head
    while fast and fast.next:
        slow = slow.next
        fast = fast.next.next
    return slow
```

### 位运算
```python
# 常用操作
n & (n - 1)      # 消除最低位的 1
n & (-n)         # 获取最低位的 1
n ^ n = 0        # 自身异或为 0
a ^ b ^ b = a    # 异或两次恢复

# 统计 1 的个数
def count_bits(n):
    count = 0
    while n:
        n &= n - 1
        count += 1
    return count
```

### 字典树 (Trie)
```python
class Trie:
    def __init__(self):
        self.children = {}
        self.is_end = False

    def insert(self, word):
        node = self
        for ch in word:
            if ch not in node.children:
                node.children[ch] = Trie()
            node = node.children[ch]
        node.is_end = True

    def search(self, word):
        node = self._search_prefix(word)
        return node is not None and node.is_end

    def startsWith(self, prefix):
        return self._search_prefix(prefix) is not None

    def _search_prefix(self, prefix):
        node = self
        for ch in prefix:
            if ch not in node.children:
                return None
            node = node.children[ch]
        return node
```
