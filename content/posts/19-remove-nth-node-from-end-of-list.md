---
title: "19. 删除链表的倒数第 N 个结点"
difficulty: "中等"
description: "给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。"
---

# 19. 删除链表的倒数第 N 个结点

**难度：<DifficultyBadge>中等</DifficultyBadge>**

## 题目描述

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

### 示例

```text
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
解释：链表中有 5 个结点，删除倒数第 2 个结点后，链表变为 [1,2,3,5]
```

```text
输入：head = [1], n = 1
输出：[]
解释：链表中只有一个结点，删除后为空链表
```

```text
输入：head = [1,2], n = 1
输出：[1]
解释：删除倒数第 1 个结点（即尾结点）后，链表变为 [1]
```

## 解法一：快慢指针（推荐）

### 思路

使用快慢指针可以一次遍历解决问题：

1. 创建哑结点 `dummy`，指向头结点（处理删除头结点的情况）
2. 使用快慢指针，都指向哑结点
3. 让快指针先移动 `n` 步
4. 快慢指针同时移动，直到快指针到达链表末尾
5. 此时慢指针指向倒数第 `n` 个结点的前一个结点
6. 通过慢指针删除倒数第 `n` 个结点

### Python

```python
from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def remove_nth_from_end(head: Optional[ListNode], n: int) -> Optional[ListNode]:
    """
    快慢指针解法

    时间复杂度: O(L)，其中 L 是链表长度
    空间复杂度: O(1)
    """
    # 创建哑结点，简化边界情况处理
    dummy = ListNode(0, head)
    fast = dummy
    slow = dummy

    # 快指针先移动 n 步
    for _ in range(n + 1):
        fast = fast.next

    # 快慢指针同时移动
    while fast:
        fast = fast.next
        slow = slow.next

    # 删除倒数第 n 个结点
    slow.next = slow.next.next

    return dummy.next
```

### C++

```cpp
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 创建哑结点，简化边界情况处理
        ListNode* dummy = new ListNode(0, head);
        ListNode* fast = dummy;
        ListNode* slow = dummy;

        // 快指针先移动 n 步
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // 快慢指针同时移动
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }

        // 删除倒数第 n 个结点
        ListNode* to_delete = slow->next;
        slow->next = slow->next->next;
        delete to_delete;

        ListNode* result = dummy->next;
        delete dummy;
        return result;
    }
};
```

## 解法二：两次遍历

### 思路

两次遍历的方法更加直观：

1. 第一次遍历：计算链表长度 `L`
2. 第二次遍历：找到倒数第 `n` 个结点的前一个结点（位置 `L - n`）
3. 删除该结点

### Python

```python
def remove_nth_from_end_two_pass(head: Optional[ListNode], n: int) -> Optional[ListNode]:
    """
    两次遍历解法

    时间复杂度: O(L)
    空间复杂度: O(1)
    """
    dummy = ListNode(0, head)
    current = dummy

    # 第一次遍历：计算链表长度
    length = 0
    while current.next:
        current = current.next
        length += 1

    # 第二次遍历：找到要删除结点的前一个结点
    current = dummy
    for _ in range(length - n):
        current = current.next

    # 删除结点
    current.next = current.next.next

    return dummy.next
```

### C++

```cpp
ListNode* removeNthFromEndTwoPass(ListNode* head, int n) {
    ListNode* dummy = new ListNode(0, head);
    ListNode* current = dummy;

    // 第一次遍历：计算链表长度
    int length = 0;
    while (current->next) {
        current = current->next;
        length++;
    }

    // 第二次遍历：找到要删除结点的前一个结点
    current = dummy;
    for (int i = 0; i < length - n; i++) {
        current = current->next;
    }

    // 删除结点
    ListNode* to_delete = current->next;
    current->next = current->next->next;
    delete to_delete;

    ListNode* result = dummy->next;
    delete dummy;
    return result;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 快慢指针 | O(L) | O(1) | 一次遍历，代码更优雅 |
| 两次遍历 | O(L) | O(1) | 直观易懂，需要两次遍历 |

**说明**：L 表示链表长度。

## 总结

- **快慢指针**是解决链表倒数问题的经典方法，只需一次遍历
- **两次遍历**方法更直观，但需要遍历两次
- 两种方法都使用了哑结点来简化删除头结点的边界情况
- 注意处理链表长度为 `n` 的情况（删除头结点）
