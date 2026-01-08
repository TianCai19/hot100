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

## 🔤 字符串操作详解

### 大小写转换
```python
s = "Hello World"

s.upper()          # "HELLO WORLD" - 全部转大写
s.lower()          # "hello world" - 全部转小写
s.capitalize()    # "Hello world" - 首字母大写
s.title()         # "Hello World" - 每个单词首字母大写
s.swapcase()      # "hELLO wORLD" - 大小写互换

# 判断大小写
s.isupper()        # 是否全是大写
s.islower()        # 是否全是小写
s.istitle()        # 是否首字母大写格式
```

### 字符串查找和替换
```python
s = "Hello World, Hello Python"

# 查找
s.find("Hello")           # 0 - 首次出现位置，不存在返回-1
s.rfind("Hello")          # 13 - 最后一次出现位置
s.index("Hello")           # 0 - 同find()，但不存在会抛异常
s.rindex("Hello")          # 13 - 最后一次出现位置
s.count("Hello")           # 2 - 统计出现次数

# 替换
s.replace("Hello", "Hi")        # "Hi World, Hi Python" - 全局替换
s.replace("Hello", "Hi", 1)    # "Hi World, Hello Python" - 替换指定次数

# 检查开头结尾
s.startswith("Hello")      # True - 是否以指定字符串开头
s.endswith("Python")        # True - 是否以指定字符串结尾
```

### 字符串分割和连接
```python
s = "apple,banana,orange"

# 分割
s.split(",")               # ['apple', 'banana', 'orange'] - 按分隔符分割
s.rsplit(",", 1)           # ['apple,banana', 'orange'] - 从右侧开始分割
s.partition(",")           # ('apple', ',', 'banana,orange') - 分成三部分
s.rpartition(",")          # ('apple,banana', ',', 'orange') - 从右侧分区

# 连接
words = ["apple", "banana", "orange"]
",".join(words)             # "apple,banana,orange"
" ".join(words)             # "apple banana orange"
"\n".join(words)            # 换行符连接

# 去除空白
s = "  Hello World  "
s.strip()                  # "Hello World" - 去除两端空白
s.lstrip()                 # "Hello World  " - 去除左侧空白
s.rstrip()                 # "  Hello World" - 去除右侧空白
```

### 字符串格式化
```python
# f-string (Python 3.6+ 推荐)
name = "Alice"
age = 25
message = f"Hello {name}, you are {age} years old"

# format 方法
message = "Hello {}, you are {} years old".format(name, age)
message = "Hello {name}, you are {age} years old".format(name=name, age=age)

# % 格式化 (传统方式)
message = "Hello %s, you are %d years old" % (name, age)

# 对齐和填充
s = "Hello"
s.center(10)               # "   Hello   " - 居中对齐
s.ljust(10)                # "Hello     " - 左对齐
s.rjust(10)                # "     Hello" - 右对齐
s.zfill(10)                # "000000Hello" - 左侧补零

# 数字格式化
pi = 3.14159
f"{pi:.2f}"                # "3.14" - 保留两位小数
f"{pi:.3f}"               # "3.142" - 保留三位小数
f"{pi:e}"                 # "3.141590e+00" - 科学计数法
```

### 字符串验证和检查
```python
s = "Hello123"

# 字符类型检查
s.isdigit()                # False - 是否全为数字
s.isalpha()                # False - 是否全为字母
s.isalnum()                # True - 是否全为数字或字母
s.isspace()                # False - 是否全为空白字符
s.islower()                # False - 是否全为小写
s.isupper()                # False - 是否全为大写
s.istitle()                # False - 是否首字母大写格式

# 其他检查
s.isascii()                # True - 是否为ASCII字符
s.isdecimal()              # True - 是否为十进制字符
s.isnumeric()              # True - 是否为数字字符
s.isprintable()           # True - 是否可打印字符
```

### 字符串编码和解码
```python
# Unicode 编码
s = "Hello 世界"
s.encode('utf-8')          # b'Hello \xe4\xb8\x96\xe7\x95\x8c'
s.encode('gbk')            # GBK编码

# 解码
b = b'Hello \xe4\xb8\x96\xe7\x95\x8c'
b.decode('utf-8')          # "Hello 世界"

# 字符和ASCII码转换
ord('A')                   # 65 - 字符转ASCII
chr(65)                    # 'A' - ASCII码转字符
```

### 字符串实用方法
```python
s = "Hello World"

# 重复和反转
s * 3                      # "Hello WorldHello WorldHello World"
s[::-1]                    # "dlroW olleH" - 反转字符串

# 切片
s[0:5]                     # "Hello" - 切片 [start:end)
s[:5]                      # "Hello" - 从开始到位置5
s[6:]                      # "World" - 从位置6到结束
s[-1]                      # "d" - 最后一个字符
s[-3:]                     # "rld" - 最后三个字符

# 成员检查
"Hello" in s               # True - 检查子字符串
"hi" not in s              # True - 检查不在子字符串中

# 字符串比较
s1 == s2                   # 字符串相等比较
s1 < s2                    # 字典序比较

# 转换为列表/元组
list(s)                    # ['H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd']
tuple(s)                   # ('H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd')
```

### 字符串模板
```python
from string import Template

# 使用 Template 进行简单字符串替换
t = Template("Hello $name, you have $count messages")
result = t.substitute(name="Alice", count=5)
# "Hello Alice, you have 5 messages"

# 安全替换（缺少变量不报错）
result = t.safe_substitute(name="Bob")
# "Hello Bob, you have $count messages"
```

### 常用字符串操作组合技巧
```python
# 去除所有空白字符
import re
re.sub(r'\s+', '', s)

# 首字母大写
s.capitalize()

# 驼峰命名转下划线
import re
re.sub('(.)([A-Z][a-z]+)', r'\1_\2', 'CamelCase').lower()

# 下划线转驼峰
s = "snake_case_string"
parts = s.split('_')
result = parts[0] + ''.join(word.capitalize() for word in parts[1:])

# 统计每个字符出现次数
from collections import Counter
char_count = Counter(s)

# 查找最常见的字符
char_count.most_common(1)[0]

# 字符串去重（保持顺序）
from collections import OrderedDict
result = ''.join(OrderedDict.fromkeys(s).keys())

# 多字符替换
trans_table = str.maketrans('abc', '123')
s.translate(trans_table)  # a->1, b->2, c->3
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
