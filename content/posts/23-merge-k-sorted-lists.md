---
title: "23. 合并K个升序链表"
difficulty: "困难"
description: "给你一个链表数组，每个链表都已经按升序排列。请你将所有链表合并成一个升序链表并返回。"
---

# 23. 合并K个升序链表

**难度：<DifficultyBadge>困难</DifficultyBadge>**

## 题目描述

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并成一个升序链表并返回。

### 示例

```text
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：合并后的链表如上图所示。
```

```text
输入：lists = []
输出：[]
```

```text
输入：lists = [[]]
输出：[]
```

## 解法一：最小堆优先队列（推荐）

### 思路

使用最小堆（优先队列）可以高效地合并多个有序链表：

1. 维护一个最小堆，存储所有链表的当前头节点
2. 每次从堆中取出最小的节点，添加到结果链表
3. 将该节点的下一个节点加入堆中
4. 重复直到所有节点处理完毕

### Python

```python
from typing import List, Optional
import heapq

# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __lt__(self, other):
        # 为最小堆比较定义的小于操作符
        return self.val < other.val

def merge_k_lists(lists: List[Optional[ListNode]]) -> Optional[ListNode]:
    """
    最小堆解法

    时间复杂度: O(n log k)，其中 n 是总节点数，k 是链表数
    空间复杂度: O(k)，堆的大小
    """
    # 初始化最小堆，只保存非空链表的头节点
    min_heap = []
    for node in lists:
        if node:
            heapq.heappush(min_heap, node)

    # 创建一个虚拟头节点
    dummy = ListNode(0)
    current = dummy

    # 当堆不为空时
    while min_heap:
        # 取出最小节点
        smallest = heapq.heappop(min_heap)
        # 将其添加到结果链表
        current.next = smallest
        current = current.next

        # 如果该节点还有下一个节点，将其加入堆中
        if smallest.next:
            heapq.heappush(min_heap, smallest.next)

    return dummy.next

# 测试函数
def list_to_linkedlist(lst: List[int]) -> Optional[ListNode]:
    dummy = ListNode(0)
    current = dummy
    for val in lst:
        current.next = ListNode(val)
        current = current.next
    return dummy.next

def linkedlist_to_list(head: Optional[ListNode]) -> List[int]:
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result

# 测试
lists = [
    list_to_linkedlist([1, 4, 5]),
    list_to_linkedlist([1, 3, 4]),
    list_to_linkedlist([2, 6])
]
merged = merge_k_lists(lists)
print(linkedlist_to_list(merged))  # [1, 1, 2, 3, 4, 4, 5, 6]
```

### C++

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        // 自定义比较函数：最小堆
        auto cmp = [](ListNode* a, ListNode* b) {
            return a->val > b->val;
        };

        // 优先队列（最小堆）
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> min_heap(cmp);

        // 将所有非空链表的头节点加入堆中
        for (ListNode* node : lists) {
            if (node) {
                min_heap.push(node);
            }
        }

        // 创建虚拟头节点
        ListNode dummy(0);
        ListNode* current = &dummy;

        // 当堆不为空时
        while (!min_heap.empty()) {
            // 取出最小节点
            ListNode* smallest = min_heap.top();
            min_heap.pop();

            // 将其添加到结果链表
            current->next = smallest;
            current = current->next;

            // 如果该节点还有下一个节点，将其加入堆中
            if (smallest->next) {
                min_heap.push(smallest->next);
            }
        }

        return dummy.next;
    }
};

// 测试函数
ListNode* createLinkedList(const vector<int>& lst) {
    ListNode dummy(0);
    ListNode* current = &dummy;
    for (int val : lst) {
        current->next = new ListNode(val);
        current = current->next;
    }
    return dummy.next;
}

vector<int> linkedListToVector(ListNode* head) {
    vector<int> result;
    ListNode* current = head;
    while (current) {
        result.push_back(current->val);
        current = current->next;
    }
    return result;
}

int main() {
    vector<ListNode*> lists = {
        createLinkedList({1, 4, 5}),
        createLinkedList({1, 3, 4}),
        createLinkedList({2, 6})
    };

    Solution solution;
    ListNode* merged = solution.mergeKLists(lists);

    vector<int> result = linkedListToVector(merged);
    for (int val : result) {
        cout << val << " ";
    }
    cout << endl;  // 输出: 1 1 2 3 4 4 5 6

    return 0;
}
```

## 解法二：分治合并

### 思路

采用分治的思想，将链表两两合并：

1. 不断将链表数组分成两半
2. 递归地合并左半部分和右半部分
3. 合并两个有序链表
4. 时间复杂度：O(n log k)

### Python

```python
def merge_two_lists(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    """合并两个有序链表"""
    dummy = ListNode(0)
    current = dummy

    while l1 and l2:
        if l1.val < l2.val:
            current.next = l1
            l1 = l1.next
        else:
            current.next = l2
            l2 = l2.next
        current = current.next

    current.next = l1 if l1 else l2
    return dummy.next

def merge_k_lists_divide(lists: List[Optional[ListNode]]) -> Optional[ListNode]:
    """
    分治解法

    时间复杂度: O(n log k)
    空间复杂度: O(log k)，递归栈
    """
    if not lists or len(lists) == 0:
        return None
    if len(lists) == 1:
        return lists[0]

    # 分
    mid = len(lists) // 2
    left = merge_k_lists_divide(lists[:mid])
    right = merge_k_lists_divide(lists[mid:])

    # 治：合并
    return merge_two_lists(left, right)
```

### C++

```cpp
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(0);
    ListNode* current = &dummy;

    while (l1 && l2) {
        if (l1->val < l2->val) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }

    current->next = l1 ? l1 : l2;
    return dummy.next;
}

ListNode* mergeKListsDivide(vector<ListNode*>& lists, int start, int end) {
    if (start > end) return nullptr;
    if (start == end) return lists[start];

    int mid = start + (end - start) / 2;
    ListNode* left = mergeKListsDivide(lists, start, mid);
    ListNode* right = mergeKListsDivide(lists, mid + 1, end);

    return mergeTwoLists(left, right);
}

ListNode* mergeKListsDivide(vector<ListNode*>& lists) {
    if (lists.empty()) return nullptr;
    return mergeKListsDivide(lists, 0, lists.size() - 1);
}
```

## 解法三：顺序合并

### 思路

最直观的方法：将第一个链表与第二个链表合并，结果再与第三个链表合并，依此类推。

### Python

```python
def merge_k_lists_simple(lists: List[Optional[ListNode]]) -> Optional[ListNode]:
    """
    顺序合并

    时间复杂度: O(k * n)
    空间复杂度: O(1)
    """
    if not lists:
        return None

    result = None
    for node in lists:
        result = merge_two_lists(result, node)

    return result
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 最小堆 | O(n log k) | O(k) | 经典高效解法 |
| 分治合并 | O(n log k) | O(log k) | 递归实现 |
| 顺序合并 | O(k * n) | O(1) | 简单直观，但效率较低 |

**说明**：n 是总节点数，k 是链表数。最小堆和分治合并的时间复杂度更优。

## 总结

- **最小堆解法**是最常用的方法，每次只需 O(log k) 时间找到最小节点
- **分治合并**利用了合并两个有序链表的特性，时间复杂度同样优秀
- **顺序合并**实现最简单，但时间复杂度较高，不推荐
- 注意处理空链表和空数组的边界情况
