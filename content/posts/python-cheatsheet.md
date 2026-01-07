---
title: "Python LeetCode 常用语法速查"
difficulty: "文档"
description: "LeetCode 面试前快速复习 Python 常用语法和数据结构"
---

# Python LeetCode 常用语法速查

## 📦 数据结构

### 栈 (Stack)
```python
# 使用 list 实现栈
stack = []
stack.append(1)      # 入栈
stack.append(2)
top = stack.pop()   # 出栈：2
is_empty = not stack

# 使用 collections.deque (推荐，更高效)
from collections import deque
stack = deque()
stack.append(1)
stack.pop()
```

### 队列 (Queue)
```python
from collections import deque

# 双端队列 (推荐)
queue = deque([1, 2, 3])
queue.append(4)           # 右端添加
queue.appendleft(0)       # 左端添加
queue.pop()               # 右端删除
queue.popleft()           # 左端删除

# 单端队列
queue = deque()
queue.append(1)
queue.popleft()
```

### 优先队列 (堆)
```python
import heapq

# 最小堆
heap = []
heapq.heappush(heap, 3)
heapq.heappush(heap, 1)
heapq.heappush(heap, 2)
min_val = heapq.heappop(heap)  # 1

# 最大堆 (取负数)
max_heap = []
heapq.heappush(max_heap, -3)
heapq.heappush(max_heap, -1)
max_val = -heapq.heappop(max_heap)  # 3

# 已有列表转堆
arr = [3, 1, 2]
heapq.heapify(arr)

# 获取最小值不删除
min_val = heap[0]

# 堆大小
len(heap)
```

### 字典 (Dict) - LeetCode 常用模式
```python
# 计数统计
counter = {}
counter[x] = counter.get(x, 0) + 1
# 或使用 collections.Counter
from collections import Counter
counter = Counter(arr)

# 存在性检查
if key in dict: ...

# 默认值
dict.get(key, default_value)

# 遍历字典
for key, value in dict.items():
for key in dict.keys():
for value in dict.values():

# 按值排序
sorted_dict = sorted(dict.items(), key=lambda x: x[1])

# defaultdict (自动初始化默认值)
from collections import defaultdict
d = defaultdict(int)      # 默认值为 0
d = defaultdict(list)      # 默认值为 []
d = defaultdict(set)       # 默认值为 set()

# OrderedDict (Python 3.7+ dict 已有序)
from collections import OrderedDict
```

### 集合 (Set)
```python
s = set([1, 2, 3])
s.add(4)
s.remove(3)        # KeyError 如果不存在
s.discard(3)       # 不报错
4 in s             # O(1) 查找

# 集合运算
union = s1 | s2
intersection = s1 & s2
difference = s1 - s2

# 去重
unique = list(set(arr))
```

## 🔗 链表操作
```python
# 定义链表节点
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

# 反转链表
def reverseList(head):
    prev = None
    curr = head
    while curr:
        next_temp = curr.next
        curr.next = prev
        prev = curr
        curr = next_temp
    return prev

# 合并两个有序链表
def mergeTwoLists(l1, l2):
    dummy = ListNode()
    tail = dummy
    while l1 and l2:
        if l1.val < l2.val:
            tail.next = l1
            l1 = l1.next
        else:
            tail.next = l2
            l2 = l2.next
        tail = tail.next
    tail.next = l1 or l2
    return dummy.next
```

## 🌳 树操作
```python
# 定义二叉树节点
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

# BFS 遍历
def levelOrder(root):
    if not root: return []
    result = []
    queue = collections.deque([root])
    while queue:
        level_size = len(queue)
        level = []
        for _ in range(level_size):
            node = queue.popleft()
            level.append(node.val)
            if node.left: queue.append(node.left)
            if node.right: queue.append(node.right)
        result.append(level)
    return result

# DFS 遍历
def inorderTraversal(root):
    result = []
    stack = []
    current = root
    while stack or current:
        while current:
            stack.append(current)
            current = current.left
        current = stack.pop()
        result.append(current.val)
        current = current.right
    return result
```

## 🔄 滑动窗口
```python
def sliding_window(arr, k):
    window_sum = sum(arr[:k])
    result = [window_sum]
    for i in range(len(arr) - k):
        window_sum += arr[i + k] - arr[i]
        result.append(window_sum)
    return result

# 变长滑动窗口
def min_window_substring(s, t):
    from collections import Counter, defaultdict
    if not t or not s: return ""
    dict_t = Counter(t)
    required = len(dict_t)
    l, r = 0, 0
    formed = 0
    window_counts = defaultdict(int)
    ans = float("inf"), None, None

    while r < len(s):
        char = s[r]
        window_counts[char] += 1
        if char in dict_t and window_counts[char] == dict_t[char]:
            formed += 1
        while l <= r and formed == required:
            # 更新答案
            if r - l + 1 < ans[0]:
                ans = (r - l + 1, l, r)
            # 收缩窗口
            char = s[l]
            window_counts[char] -= 1
            if char in dict_t and window_counts[char] < dict_t[char]:
                formed -= 1
            l += 1
        r += 1
    return "" if ans[0] == float("inf") else s[ans[1]:ans[2]+1]
```

## 📊 图论常用
```python
# 邻接表
graph = defaultdict(list)
for u, v in edges:
    graph[u].append(v)
    graph[v].append(u)  # 无向图

# DFS
def dfs(node, visited):
    visited.add(node)
    for neighbor in graph[node]:
        if neighbor not in visited:
            dfs(neighbor, visited)

# BFS
from collections import deque
def bfs(start):
    visited = set([start])
    queue = deque([start])
    while queue:
        node = queue.popleft()
        for neighbor in graph[node]:
            if neighbor not in visited:
                visited.add(neighbor)
                queue.append(neighbor)

# 拓扑排序 (Kahn 算法)
def topologicalSort(n, prerequisites):
    from collections import deque, defaultdict
    graph = defaultdict(list)
    indegree = [0] * n

    for u, v in prerequisites:
        graph[u].append(v)
        indegree[v] += 1

    queue = deque([i for i in range(n) if indegree[i] == 0])
    result = []

    while queue:
        node = queue.popleft()
        result.append(node)
        for neighbor in graph[node]:
            indegree[neighbor] -= 1
            if indegree[neighbor] == 0:
                queue.append(neighbor)

    return result if len(result) == n else []
```

## 🔢 数组/字符串技巧
```python
# 双指针
def two_pointers(arr, target):
    left, right = 0, len(arr) - 1
    while left < right:
        if arr[left] + arr[right] == target:
            return [left, right]
        elif arr[left] + arr[right] < target:
            left += 1
        else:
            right -= 1

# 二分查找
def binary_search(arr, target):
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

# 前缀和
prefix = [0]
for num in arr:
    prefix.append(prefix[-1] + num)
# 子数组和 [i:j] = prefix[j] - prefix[i]

# 原地翻转
arr.reverse()
arr[::-1]

# 字符串反转
s = s[::-1]

# 字符计数
from collections import Counter
count = Counter(s)
```

## 🔄 常用内置函数
```python
# 排序
sorted(arr)                    # 返回新列表
arr.sort()                     # 原地排序
sorted(arr, reverse=True)      # 降序
sorted(arr, key=lambda x: x[1])  # 按第二列排序

# 枚举
for i, val in enumerate(arr):
    pass

# ZIP (同时遍历多个列表)
for a, b in zip(list1, list2):
    pass

# 范围
list(range(10))        # [0, 1, 2, ..., 9]
list(range(2, 10, 2))  # [2, 4, 6, 8]

# 列表生成式
[x**2 for x in range(10) if x % 2 == 0]
[(i, j) for i in range(3) for j in range(3)]

# 任意/所有
any(x > 5 for x in arr)
all(x > 0 for x in arr)

# 最大/最小 (带索引)
max_val = max(arr)
max_idx = arr.index(max(arr))
# 或者使用 enumerate
max_idx = max(range(len(arr)), key=arr.__getitem__)
```

## 🎯 常用模式总结

1. **计数模式**: `collections.Counter(arr)`
2. **分组模式**: `defaultdict(list)` 按键分组
3. **滑动窗口**: 固定窗口或变长窗口
4. **快慢指针**: 链表检测环、找中点
5. **左右指针**: 两数之和、三数之和
6. **二分查找**: 有序数组搜索
7. **DFS/BFS**: 图和树遍历
8. **并查集**: 检测环、最小生成树
9. **KMP**: 字符串匹配
10. **动态规划**: 状态转移表

## ⚡ 性能优化技巧

- **列表操作**:
  - `append()` O(1)，`insert(0, x)` O(n)
  - 用 `deque` 进行频繁的队首操作

- **集合/字典查找**: O(1)，比列表 O(n) 快得多

- **字符串拼接**:
  - 避免 `s = s + str`，用 `''.join(list)`

- **重复计算**: 用 `lru_cache` 缓存
```python
from functools import lru_cache

@lru_cache(None)
def fib(n):
    if n < 2: return n
    return fib(n-1) + fib(n-2)
```
