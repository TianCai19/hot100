---
title: "148. 排序链表"
difficulty: "中等"
description: "给你链表的头结点 head，请将其按升序排列并返回排序后的链表。"
---

# 148. 排序链表

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你链表的头结点 `head`，请将其按升序排列并返回排序后的链表。

**要求：** 你可以在 O(n log n) 时间复杂度和常数级空间复杂度下解决此问题吗？

### 示例

```text
输入：head = [4,2,1,3]
输出：[1,2,3,4]
```

```text
输入：head = [-1,5,3,4,0]
输出：[-1,0,3,4,5]
```

### 合并过程示意

<Mermaid>
flowchart LR
    A[4->2->1->3] --> B[4->2]
    A --> C[1->3]
    B --> D[2->4]
    C --> E[1->3]
    D --> F[1->2->3->4]
    E --> F
</Mermaid>

## 提示

- 链表中节点数目在范围 `[0, 5 * 10^4]` 内。
- `-10^5 <= Node.val <= 10^5`

---

## 解法一：递归归并排序（推荐，易懂）

### 思路

链表适合归并排序：
1. 使用快慢指针找到中点并断开链表，分成左右两半。
2. 递归排序左右链表。
3. 合并两个有序链表。

### 面试讲解版

我会先说链表排序的最优复杂度是 O(n log n)，而归并天然适配链表：切分容易、合并只改指针。用快慢指针找中点，把链表一分为二，递归排序后再合并。合并过程就是“每次取较小节点接到结果链表尾部”，不需要额外数组。

如果面试官追问空间，我会补充：递归会用 O(log n) 栈空间；若严格要求 O(1) 额外空间，可以改成自底向上的迭代归并（下面的解法二），仍是 O(n log n)。

### Python

```python
from typing import Optional

class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

class Solution:
    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head

        mid = self._get_mid(head)
        right = mid.next
        mid.next = None

        left_sorted = self.sortList(head)
        right_sorted = self.sortList(right)

        return self._merge(left_sorted, right_sorted)

    def _get_mid(self, head: ListNode) -> ListNode:
        slow = head
        fast = head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow

    def _merge(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        tail = dummy

        while l1 and l2:
            if l1.val <= l2.val:
                tail.next = l1
                l1 = l1.next
            else:
                tail.next = l2
                l2 = l2.next
            tail = tail.next

        tail.next = l1 if l1 else l2
        return dummy.next
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
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        ListNode* mid = getMid(head);
        ListNode* right = mid->next;
        mid->next = nullptr;

        ListNode* leftSorted = sortList(head);
        ListNode* rightSorted = sortList(right);

        return merge(leftSorted, rightSorted);
    }

private:
    ListNode* getMid(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    ListNode* merge(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        return dummy.next;
    }
};
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(n log n) |
| 空间复杂度 | O(log n)，递归栈 |

---

## 解法二：自底向上归并（进阶，O(1) 额外空间）

### 思路

用迭代的方式做归并：
1. 从 `step = 1` 开始，每次把链表按 `step` 切成若干段，两两合并。
2. 每轮结束后 `step *= 2`，直到 `step >= n`。

这种方法避免递归栈，额外空间 O(1)。

### Python

```python
class Solution:
    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head

        length = 0
        node = head
        while node:
            length += 1
            node = node.next

        dummy = ListNode(0, head)
        step = 1
        while step < length:
            prev = dummy
            curr = dummy.next
            while curr:
                left = curr
                right = self._split(left, step)
                curr = self._split(right, step)
                merged_head, merged_tail = self._merge_iter(left, right)
                prev.next = merged_head
                prev = merged_tail
            step <<= 1

        return dummy.next

    def _split(self, head: Optional[ListNode], size: int) -> Optional[ListNode]:
        if not head:
            return None
        for _ in range(size - 1):
            if not head.next:
                break
            head = head.next
        next_head = head.next
        head.next = None
        return next_head

    def _merge_iter(self, l1: Optional[ListNode], l2: Optional[ListNode]):
        dummy = ListNode(0)
        tail = dummy
        while l1 and l2:
            if l1.val <= l2.val:
                tail.next = l1
                l1 = l1.next
            else:
                tail.next = l2
                l2 = l2.next
            tail = tail.next
        tail.next = l1 if l1 else l2
        while tail.next:
            tail = tail.next
        return dummy.next, tail
```

### C++

```cpp
class Solution {
public:
    ListNode* sortList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }

        int length = 0;
        for (ListNode* node = head; node; node = node->next) {
            length++;
        }

        ListNode dummy(0);
        dummy.next = head;
        for (int step = 1; step < length; step <<= 1) {
            ListNode* prev = &dummy;
            ListNode* curr = dummy.next;
            while (curr) {
                ListNode* left = curr;
                ListNode* right = split(left, step);
                curr = split(right, step);
                auto merged = mergeIter(left, right);
                prev->next = merged.first;
                prev = merged.second;
            }
        }

        return dummy.next;
    }

private:
    ListNode* split(ListNode* head, int size) {
        if (!head) {
            return nullptr;
        }
        for (int i = 1; i < size && head->next; ++i) {
            head = head->next;
        }
        ListNode* nextHead = head->next;
        head->next = nullptr;
        return nextHead;
    }

    pair<ListNode*, ListNode*> mergeIter(ListNode* l1, ListNode* l2) {
        ListNode dummy(0);
        ListNode* tail = &dummy;
        while (l1 && l2) {
            if (l1->val <= l2->val) {
                tail->next = l1;
                l1 = l1->next;
            } else {
                tail->next = l2;
                l2 = l2->next;
            }
            tail = tail->next;
        }
        tail->next = l1 ? l1 : l2;
        while (tail->next) {
            tail = tail->next;
        }
        return {dummy.next, tail};
    }
};
```

### 复杂度分析

| 复杂度 | 值 |
|--------|-----|
| 时间复杂度 | O(n log n) |
| 空间复杂度 | O(1) 额外空间 |

---

## 解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 递归归并 | O(n log n) | O(log n) | 易理解，写法简洁 |
| 自底向上归并 | O(n log n) | O(1) | 满足进阶空间要求 |

## 总结

- 链表排序首选归并思路，天然适配链表结构。
- 若强调 O(1) 额外空间，使用迭代自底向上归并。
