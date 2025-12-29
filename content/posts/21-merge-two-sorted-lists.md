---
title: "21. 合并两个有序链表"
difficulty: "简单"
description: "将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定链表的节点组成的。"
---

# 21. 合并两个有序链表

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

将两个升序链表合并为一个新的升序链表并返回。新链表是通过拼接给定链表的节点组成的。

### 示例

```text
输入：list1 = [1,2,4], list2 = [1,3,4]
输出：[1,1,2,3,4,4]
```

```text
输入：list1 = [], list2 = []
输出：[]
```

```text
输入：list1 = [], list2 = [0]
输出：[0]
```

## 解法一：迭代解法（推荐）

### 思路

使用双指针同时遍历两个链表：

1. 创建哑节点 `dummy` 作为新链表的头部
2. 使用指针 `prev` 跟踪新链表的末尾
3. 同时遍历两个链表：
   - 比较当前节点的值，将较小的节点接到新链表
   - 移动相应链表的指针
4. 当其中一个链表遍历完后，将另一个链表的剩余部分直接接上

### Python

```python
from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def merge_two_lists(list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
    """
    迭代解法

    时间复杂度: O(n + m)，其中 n 和 m 是两个链表的长度
    空间复杂度: O(1)
    """
    dummy = ListNode(0)
    prev = dummy

    while list1 and list2:
        if list1.val <= list2.val:
            prev.next = list1
            list1 = list1.next
        else:
            prev.next = list2
            list2 = list2.next
        prev = prev.next

    # 将剩余部分直接连接
    prev.next = list1 if list1 else list2

    return dummy.next
```

### C++

```cpp
#include <iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        /**
         * 迭代解法
         *
         * 时间复杂度: O(n + m)，其中 n 和 m 是两个链表的长度
         * 空间复杂度: O(1)
         */
        ListNode dummy(0);
        ListNode* prev = &dummy;

        while (list1 && list2) {
            if (list1->val <= list2->val) {
                prev->next = list1;
                list1 = list1->next;
            } else {
                prev->next = list2;
                list2 = list2->next;
            }
            prev = prev->next;
        }

        // 将剩余部分直接连接
        prev->next = list1 ? list1 : list2;

        return dummy.next;
    }
};
```

## 解法二：递归解法

### 思路

使用递归的方式解决：

1. 如果 `list1` 为空，返回 `list2`
2. 如果 `list2` 为空，返回 `list1`
3. 如果 `list1->val <= list2->val`，令 `list1->next = mergeTwoLists(list1->next, list2)`
4. 否则，令 `list2->next = mergeTwoLists(list1, list2->next)`
5. 返回当前较小的节点

### Python

```python
def merge_two_lists_recursive(list1: Optional[ListNode], list2: Optional[ListNode]) -> Optional[ListNode]:
    """
    递归解法

    时间复杂度: O(n + m)
    空间复杂度: O(n + m)，递归栈空间
    """
    if not list1:
        return list2
    if not list2:
        return list1

    if list1.val <= list2.val:
        list1.next = merge_two_lists_recursive(list1.next, list2)
        return list1
    else:
        list2.next = merge_two_lists_recursive(list1, list2.next)
        return list2
```

### C++

```cpp
ListNode* mergeTwoListsRecursive(ListNode* list1, ListNode* list2) {
    /**
     * 递归解法
     *
     * 时间复杂度: O(n + m)
     * 空间复杂度: O(n + m)，递归栈空间
     */
    if (!list1) {
        return list2;
    }
    if (!list2) {
        return list1;
    }

    if (list1->val <= list2->val) {
        list1->next = mergeTwoListsRecursive(list1->next, list2);
        return list1;
    } else {
        list2->next = mergeTwoListsRecursive(list1, list2->next);
        return list2;
    }
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 迭代解法 | O(n + m) | O(1) | 直观易懂，无需递归栈 |
| 递归解法 | O(n + m) | O(n + m) | 代码简洁，递归实现 |

**说明**：
- n 和 m 分别表示两个链表的长度
- 迭代解法更适合实际使用，避免递归栈溢出
- 递归解法更优雅，但可能有栈深度限制

## 总结

- **迭代解法**是最常用的方法，时间和空间效率都很高
- **递归解法**代码更简洁，但需要考虑递归深度限制
- 合并有序链表的本质是**归并排序**的一部分思想
- 关键点：始终比较当前节点，选择较小的那个，并移动相应指针
