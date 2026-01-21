---
title: "146. LRU 缓存"
difficulty: "中等"
description: "设计并实现一个满足 LRU(最近最少使用) 缓存机制的数据结构。"
---

# 146. LRU 缓存

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

设计并实现一个满足 LRU (最近最少使用) 缓存机制的数据结构。

实现 `LRUCache` 类：
- `LRUCache(int capacity)` 以正整数作为容量。
- `int get(int key)` 如果 key 存在返回对应 value，否则返回 -1。
- `void put(int key, int value)` 如果 key 存在则更新；否则插入新 key。
  超出容量时，移除最近最少使用的 key。

要求：`get` 和 `put` 操作均为 O(1)。

### 示例

```text
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1,1], [2,2], [1], [3,3], [2], [4,4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]
```

### 结构示意（最近使用在左）

<svg width="620" height="120" viewBox="0 0 620 120" xmlns="http://www.w3.org/2000/svg" role="img" aria-label="LRU cache list">
  <rect x="20" y="35" width="90" height="50" fill="#1f2937" stroke="#3b82f6" strokeWidth="2" rx="8" />
  <text x="65" y="65" textAnchor="middle" fill="#e5e7eb" fontSize="14">MRU</text>

  <rect x="130" y="35" width="90" height="50" fill="#111827" stroke="#4b5563" strokeWidth="2" rx="8" />
  <text x="175" y="65" textAnchor="middle" fill="#e5e7eb" fontSize="14">K3</text>

  <rect x="240" y="35" width="90" height="50" fill="#111827" stroke="#4b5563" strokeWidth="2" rx="8" />
  <text x="285" y="65" textAnchor="middle" fill="#e5e7eb" fontSize="14">K1</text>

  <rect x="350" y="35" width="90" height="50" fill="#111827" stroke="#4b5563" strokeWidth="2" rx="8" />
  <text x="395" y="65" textAnchor="middle" fill="#e5e7eb" fontSize="14">K4</text>

  <rect x="460" y="35" width="90" height="50" fill="#1f2937" stroke="#f97316" strokeWidth="2" rx="8" />
  <text x="505" y="65" textAnchor="middle" fill="#e5e7eb" fontSize="14">LRU</text>

  <line x1="110" y1="60" x2="130" y2="60" stroke="#9ca3af" strokeWidth="2" markerEnd="url(#arrow)" />
  <line x1="220" y1="60" x2="240" y2="60" stroke="#9ca3af" strokeWidth="2" markerEnd="url(#arrow)" />
  <line x1="330" y1="60" x2="350" y2="60" stroke="#9ca3af" strokeWidth="2" markerEnd="url(#arrow)" />
  <line x1="440" y1="60" x2="460" y2="60" stroke="#9ca3af" strokeWidth="2" markerEnd="url(#arrow)" />

  <defs>
    <marker id="arrow" markerWidth="10" markerHeight="10" refX="8" refY="3" orient="auto" markerUnits="strokeWidth">
      <path d="M0,0 L0,6 L9,3 z" fill="#9ca3af" />
    </marker>
  </defs>
</svg>

## 提示

- `1 <= capacity <= 3000`
- `0 <= key <= 10^4`
- `0 <= value <= 10^5`
- 最多调用 `get` 和 `put` 共 `2 * 10^5` 次。

---

## 解法一：哈希表 + 双向链表（推荐）

### 思路

- **哈希表**：O(1) 定位 key 对应的节点。
- **双向链表**：维护使用顺序，头部是最近使用，尾部是最久未使用。

操作规则：
- `get`：命中则将节点移动到头部。
- `put`：
  - 命中：更新值并移到头部。
  - 未命中：新节点加入头部；若超容量，删除尾部节点。

### 面试讲解版

我会先说 LRU 的本质是“按访问时间排序”，要做到 `get/put` 都是 O(1)，就必须同时解决两件事：O(1) 找节点、O(1) 调整节点顺序。哈希表解决定位，双向链表解决移动。然后说明约定：链表头是最近使用，尾是最久未使用。`get` 时命中就把节点挪到头部；`put` 时若是新节点插头部，超容量就删尾部。这样每一步都只改常数个指针，复杂度稳定。

如果追问为什么不是数组/队列，我会强调数组移动代价是 O(n)，单链表无法 O(1) 删除任意节点，所以必须用双向链表。

### Python

```python
class Node:
    def __init__(self, key: int, value: int):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None

class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.cache = {}
        self.head = Node(0, 0)
        self.tail = Node(0, 0)
        self.head.next = self.tail
        self.tail.prev = self.head

    def _add(self, node: Node) -> None:
        node.prev = self.head
        node.next = self.head.next
        self.head.next.prev = node
        self.head.next = node

    def _remove(self, node: Node) -> None:
        node.prev.next = node.next
        node.next.prev = node.prev

    def _move_to_head(self, node: Node) -> None:
        self._remove(node)
        self._add(node)

    def _pop_tail(self) -> Node:
        node = self.tail.prev
        self._remove(node)
        return node

    def get(self, key: int) -> int:
        node = self.cache.get(key)
        if not node:
            return -1
        self._move_to_head(node)
        return node.value

    def put(self, key: int, value: int) -> None:
        node = self.cache.get(key)
        if node:
            node.value = value
            self._move_to_head(node)
            return

        new_node = Node(key, value)
        self.cache[key] = new_node
        self._add(new_node)

        if len(self.cache) > self.capacity:
            tail = self._pop_tail()
            del self.cache[tail.key]
```

### C++

```cpp
#include <unordered_map>
using namespace std;

struct Node {
    int key;
    int value;
    Node *prev;
    Node *next;
    Node(int k, int v) : key(k), value(v), prev(nullptr), next(nullptr) {}
};

class LRUCache {
public:
    LRUCache(int capacity) : capacity_(capacity) {
        head_ = new Node(0, 0);
        tail_ = new Node(0, 0);
        head_->next = tail_;
        tail_->prev = head_;
    }

    int get(int key) {
        auto it = cache_.find(key);
        if (it == cache_.end()) {
            return -1;
        }
        Node* node = it->second;
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        auto it = cache_.find(key);
        if (it != cache_.end()) {
            Node* node = it->second;
            node->value = value;
            moveToHead(node);
            return;
        }

        Node* node = new Node(key, value);
        cache_[key] = node;
        addNode(node);

        if ((int)cache_.size() > capacity_) {
            Node* tail = popTail();
            cache_.erase(tail->key);
            delete tail;
        }
    }

private:
    int capacity_;
    unordered_map<int, Node*> cache_;
    Node* head_;
    Node* tail_;

    void addNode(Node* node) {
        node->prev = head_;
        node->next = head_->next;
        head_->next->prev = node;
        head_->next = node;
    }

    void removeNode(Node* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node* node) {
        removeNode(node);
        addNode(node);
    }

    Node* popTail() {
        Node* node = tail_->prev;
        removeNode(node);
        return node;
    }
};
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(1) | 
| 空间复杂度 | O(n) |

---

## 解法二：Python OrderedDict（工程向）

### 思路

Python 的 `collections.OrderedDict` 内部就是“哈希 + 双向链表”，
因此可以直接用它来实现 LRU：
- 命中则 `move_to_end(key, last=False)` 移到头部
- 超容量时弹出尾部 `popitem(last=True)`

### Python

```python
from collections import OrderedDict

class LRUCache:
    def __init__(self, capacity: int):
        self.capacity = capacity
        self.data = OrderedDict()

    def get(self, key: int) -> int:
        if key not in self.data:
            return -1
        self.data.move_to_end(key, last=False)
        return self.data[key]

    def put(self, key: int, value: int) -> None:
        if key in self.data:
            self.data[key] = value
            self.data.move_to_end(key, last=False)
            return

        self.data[key] = value
        self.data.move_to_end(key, last=False)
        if len(self.data) > self.capacity:
            self.data.popitem(last=True)
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(1) 均摊 |
| 空间复杂度 | O(n) |

---

## 解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 哈希表 + 双向链表 | O(1) | O(n) | **推荐**，语言无关 |
| OrderedDict | O(1) 均摊 | O(n) | 实现短，但依赖语言特性 |

## 总结

- LRU 的关键是“**O(1) 查找 + O(1) 移动**”。
- 面试推荐自己写双向链表；工程中可用库简化实现。
