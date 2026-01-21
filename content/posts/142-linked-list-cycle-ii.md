---
title: "142. 环形链表 II"
difficulty: "中等"
description: "给定一个链表的头节点 head，返回链表开始入环的第一个节点。如果链表无环，则返回 null。"
---

# 142. 环形链表 II

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给定一个链表的头节点 `head`，返回链表开始入环的第一个节点。如果链表无环，则返回 `null`。

**说明：** 不允许修改给定的链表。

### 示例

```text
输入：head = [3,2,0,-4], pos = 1
输出：返回索引 1 的节点
解释：链表中有一个环，其尾节点指向索引 1 的节点
```

```text
输入：head = [1,2], pos = 0
输出：返回索引 0 的节点
解释：链表中有一个环，其尾节点指向头节点
```

```text
输入：head = [1], pos = -1
输出：null
解释：链表中没有环
```

### 图示（入环示意）

<Mermaid>
flowchart LR;
    A((3)) --> B((2)) --> C((0)) --> D((-4));
    D --> B;
    style B fill:#90EE90;
    style D fill:#ff6b6b;
</Mermaid>

## 提示

- 链表中节点数目在范围 `[0, 10^4]` 内。
- `-10^5 <= Node.val <= 10^5`
- `pos` 为尾节点连接到的索引位置（从 0 开始），若为 `-1` 则无环。

---

## 解法一：快慢指针 + 入口定位（推荐）

### 思路

1. 用快慢指针判断是否存在环：
   - 慢指针每次走一步，快指针每次走两步。
   - 若相遇，说明有环；若快指针到达 `null`，说明无环。
2. 相遇后，将其中一个指针移到头结点，两个指针每次都走一步，
   再次相遇的位置就是入环点。

**直观解释：** 设头到入口距离为 `a`，入口到相遇点距离为 `b`，环长为 `c`。相遇时快指针走了 `2(a+b)`，慢指针走了 `a+b`，
所以 `a+b` 是 `c` 的整数倍，得到 `a` 与 `c-b` 等长。把一个指针放回头结点，两者同步走，必在入口相遇。

### 面试讲解版

面试时我会先说：用快慢指针先判环，这是 O(1) 空间的经典方案；一旦相遇，就能定位入口。核心理由是“相遇点到入口的距离 = 头到入口的距离”。做法很简单：一个指针回到头结点，另一个留在相遇点，两者同步走，下一次相遇就是入口。我会强调这一步并不需要额外结构，也不修改链表，满足进阶要求。

如果追问证明，我会用距离法：头到入口是 `a`，入口到相遇是 `b`，环长 `c`。快指针走两倍，说明 `a+b` 是环长的整数倍，所以 `a` 等于从相遇点再走到入口的距离 `c-b`。因此同步走必在入口相遇。

### Python

```python
from typing import Optional

class ListNode:
    def __init__(self, x: int, next: Optional['ListNode'] = None):
        self.val = x
        self.next = next

class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return None

        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                break
        else:
            return None

        finder = head
        while finder != slow:
            finder = finder.next
            slow = slow.next

        return finder
```

### C++

```cpp
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) {
            return nullptr;
        }

        ListNode *slow = head;
        ListNode *fast = head;

        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                break;
            }
        }

        if (!fast || !fast->next) {
            return nullptr;
        }

        ListNode *finder = head;
        while (finder != slow) {
            finder = finder->next;
            slow = slow->next;
        }

        return finder;
    }
};
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(n) |
| 空间复杂度 | O(1) |

---

## 解法二：哈希集合

### 思路

遍历链表，把访问过的节点地址放进集合：
- 如果当前节点已出现过，说明它就是入环点。
- 如果遍历到 `null`，说明无环。

### Python

```python
from typing import Optional

def detectCycleHash(head: Optional[ListNode]) -> Optional[ListNode]:
    seen = set()
    node = head
    while node:
        if node in seen:
            return node
        seen.add(node)
        node = node.next
    return None
```

### C++

```cpp
#include <unordered_set>
using namespace std;

ListNode* detectCycleHash(ListNode* head) {
    unordered_set<ListNode*> seen;
    ListNode* node = head;
    while (node) {
        if (seen.count(node)) {
            return node;
        }
        seen.insert(node);
        node = node->next;
    }
    return nullptr;
}
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(n) |
| 空间复杂度 | O(n) |

---

## 解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 快慢指针 + 入口定位 | O(n) | O(1) | **推荐**，不修改链表 |
| 哈希集合 | O(n) | O(n) | 思路直观，占用额外空间 |

## 总结

- **最优解**是快慢指针 + 入口定位，满足 O(1) 空间。
- 哈希集合更直观，但不符合进阶空间要求。
- 关键点是“相遇后重置指针”这一定位入口的技巧。
