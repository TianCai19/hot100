---
title: "160. 相交链表"
difficulty: "简单"
description: "给你两个单链表的头节点 headA 和 headB，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 null。"
---

# 160. 相交链表

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给你两个单链表的头节点 `headA` 和 `headB`，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 `null`。

### 图示

<Mermaid>
graph LR
    subgraph 链表A
        A1((a1)) --> A2((a2))
    end
    subgraph 链表B
        B1((b1)) --> B2((b2)) --> B3((b3))
    end
    subgraph 公共部分
        C1((c1)) --> C2((c2)) --> C3((c3))
    end
    A2 --> C1
    B3 --> C1
</Mermaid>

**注意：**
- 题目数据保证整个链式结构中不存在环
- 函数返回结果后，链表必须保持其原始结构

## 示例

### 示例 1

<Mermaid>
graph LR
    A4((4)) --> A1((1)) --> C8((8)) --> C4((4)) --> C5((5))
    B5((5)) --> B6((6)) --> B1((1)) --> C8
    style C8 fill:#f96
    style C4 fill:#f96
    style C5 fill:#f96
</Mermaid>

- **输入：** intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
- **输出：** Intersected at '8'
- **解释：** 相交节点的值为 8。在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。

### 示例 2

- **输入：** intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
- **输出：** Intersected at '2'

### 示例 3

- **输入：** intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
- **输出：** No intersection

## 提示

- listA 中节点数目为 m
- listB 中节点数目为 n
- `1 <= m, n <= 3 * 10^4`
- `1 <= Node.val <= 10^5`
- `0 <= skipA <= m`
- `0 <= skipB <= n`

---

## 解法一：哈希集合

### 思路

用哈希集合存储链表 A 的所有节点，然后遍历链表 B，第一个在集合中出现的节点就是交点。

### Python

```python
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        visited = set()
        curr = headA
        while curr:
            visited.add(curr)
            curr = curr.next

        curr = headB
        while curr:
            if curr in visited:
                return curr
            curr = curr.next

        return None
```

### C++

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        unordered_set<ListNode *> visited;
        ListNode *temp = headA;
        while (temp != nullptr) {
            visited.insert(temp);
            temp = temp->next;
        }
        temp = headB;
        while (temp != nullptr) {
            if (visited.count(temp)) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(m + n)
- **空间复杂度：** O(m)，需要存储链表 A 的所有节点

---

## 解法二：双指针（推荐）

### 思路

两个指针分别从 A 和 B 出发，走完自己的链表后走对方的链表。如果有交点，它们会在交点相遇；如果没有交点，它们会同时到达 null。

**原理：** 设链表 A 的独有部分长度为 a，链表 B 的独有部分长度为 b，公共部分长度为 c。
- 指针 pA 走的路径：a + c + b
- 指针 pB 走的路径：b + c + a

两者路径长度相等，必然同时到达交点或末尾。

<Mermaid>
graph TB
    subgraph 第一轮
        PA1[pA: a1→a2→c1→c2→c3→null]
        PB1[pB: b1→b2→b3→c1→c2→c3→null]
    end
    subgraph 第二轮
        PA2[pA: b1→b2→b3→c1相遇]
        PB2[pB: a1→a2→c1相遇]
    end
</Mermaid>

### 正确性证明

**情况一：两个链表相交**
- 若 a = b，两指针同时到达交点
- 若 a ≠ b，指针 pA 移动 a+c+b 次，pB 移动 b+c+a 次后相遇

**情况二：两个链表不相交**
- 若 m = n，两指针同时到达末尾变为 null
- 若 m ≠ n，两指针各移动 m+n 次后同时变为 null

### Python

```python
class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        if not headA or not headB:
            return None

        pA, pB = headA, headB

        while pA != pB:
            pA = pA.next if pA else headB
            pB = pB.next if pB else headA

        return pA
```

### C++

```cpp
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        if (!headA || !headB) return nullptr;

        ListNode *pA = headA, *pB = headB;

        while (pA != pB) {
            pA = pA ? pA->next : headB;
            pB = pB ? pB->next : headA;
        }

        return pA;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(m + n)
- **空间复杂度：** O(1)，只使用两个指针

---

## 两种解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 优点 |
|------|-----------|-----------|------|
| 哈希集合 | O(m+n) | O(m) | 思路简单直观 |
| 双指针 | O(m+n) | O(1) | 空间最优 |
