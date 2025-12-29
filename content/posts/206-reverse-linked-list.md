---
title: "206. 反转链表"
difficulty: "简单"
description: "反转单链表，返回反转后的链表头节点。"
---

# 206. 反转链表

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给你单链表的头节点 `head`，请你反转链表，并返回反转后的链表。

### 示例

**示例 1：**
```
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

**示例 2：**
```
输入：head = [1,2]
输出：[2,1]
```

**示例 3：**
```
输入：head = []
输出：[]
```

### 提示

- 链表中节点的数目范围是 `[0, 2000]`
- `-1000 <= Node.val <= 1000`

---

## 链表结构

单链表的节点结构：
```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next
```

### 链表反转示意图

原始链表：`1 → 2 → 3 → 4 → 5`

反转过程：
```
初始： 1 → 2 → 3 → 4 → 5 → None
       ↑    ↑
     prev  curr

Step 1: None ← 1 → 2 → 3 → 4 → 5 → None
              ↑    ↑
            prev  curr

Step 2: None ← 1 ← 2 → 3 → 4 → 5 → None
                   ↑    ↑
                 prev  curr

Step 3: None ← 1 ← 2 ← 3 → 4 → 5 → None
                      ↑    ↑
                    prev  curr

Step 4: None ← 1 ← 2 ← 3 ← 4 → 5 → None
                           ↑    ↑
                         prev  curr

Step 5: None ← 1 ← 2 ← 3 ← 4 ← 5 → None
                                ↑    ↑
                              prev  curr

最终：None ← 1 ← 2 ← 3 ← 4 ← 5
                      ↑
                   (新的头节点)
```

---

## 解法一：迭代法（双指针）

### 思路

使用两个指针：
- `prev` - 指向已经反转好的链表的头节点
- `curr` - 指向当前需要反转的节点

**反转步骤：**
1. 保存 `curr.next`（防止链表断裂）
2. 将 `curr.next` 指向 `prev`
3. `prev` 移动到 `curr`
4. `curr` 移动到下一个节点

### Python

```python
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def reverseList_iterative(self, head: ListNode) -> ListNode:
        """
        迭代法 - 双指针
        时间复杂度: O(n)，n 为链表长度
        空间复杂度: O(1)
        """
        prev = None  # 前一个节点（反转后链表的头）
        curr = head  # 当前节点

        while curr:
            # 1. 保存下一个节点
            next_temp = curr.next

            # 2. 反转指针
            curr.next = prev

            # 3. 移动指针
            prev = curr
            curr = next_temp

        # prev 最终指向新的头节点
        return prev
```

### C++

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* reverseList_iterative(ListNode* head) {
        /**
         * 迭代法 - 双指针
         * 时间复杂度: O(n)，n 为链表长度
         * 空间复杂度: O(1)
         */
        ListNode* prev = nullptr;  // 前一个节点（反转后链表的头）
        ListNode* curr = head;     // 当前节点

        while (curr) {
            // 1. 保存下一个节点
            ListNode* next_temp = curr->next;

            // 2. 反转指针
            curr->next = prev;

            // 3. 移动指针
            prev = curr;
            curr = next_temp;
        }

        // prev 最终指向新的头节点
        return prev;
    }
};
```

### 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|-------|------|
| 时间复杂度 | O(n) | 每个节点访问一次 |
| 空间复杂度 | O(1) | 只使用常数额外空间 |

---

## 解法二：递归法

### 思路

递归的思路是"先递归到链表末尾，然后从后向前反转指针"。

**递归步骤：**
1. 递归到链表的最后一个节点（作为新的头节点）
2. 在回溯过程中，每个节点执行反转操作
3. 将当前节点的 `next` 节点的 `next` 指向当前节点
4. 当前节点的 `next` 设为 `None`

### Python

```python
class Solution:
    def reverseList_recursive(self, head: ListNode) -> ListNode:
        """
        递归法
        时间复杂度: O(n)，n 为链表长度
        空间复杂度: O(n)，递归栈深度
        """
        # 基准条件：空链表或只有一个节点
        if not head or not head.next:
            return head

        # 递归处理子链表
        new_head = self.reverseList_recursive(head.next)

        # 反转指针
        head.next.next = head
        head.next = None

        return new_head
```

### C++

```cpp
class Solution {
public:
    ListNode* reverseList_recursive(ListNode* head) {
        /**
         * 递归法
         * 时间复杂度: O(n)，n 为链表长度
         * 空间复杂度: O(n)，递归栈深度
         */
        // 基准条件：空链表或只有一个节点
        if (!head || !head->next) {
            return head;
        }

        // 递归处理子链表
        ListNode* new_head = reverseList_recursive(head->next);

        // 反转指针
        head->next->next = head;
        head->next = nullptr;

        return new_head;
    }
};
```

### 复杂度分析

| 指标 | 复杂度 | 说明 |
|------|-------|------|
| 时间复杂度 | O(n) | 每个节点访问一次 |
| 空间复杂度 | O(n) | 递归栈深度为 n |

---

## 两种解法对比

| 特征 | 迭代法 | 递归法 |
|------|-------|-------|
| 实现难度 | 简单 | 中等 |
| 代码可读性 | 较清晰 | 需要理解递归过程 |
| 空间复杂度 | O(1) | O(n) |
| 性能 | 更优（无函数调用开销） | 稍差（递归栈开销） |
| 理解难度 | 简单 | 需要递归思维 |
| 推荐场景 | 生产环境 | 学习递归思想 |

## 总结

- **迭代法**是反转链表的标准方法，效率高，空间复杂度 O(1)
- **递归法**代码更简洁，但空间复杂度 O(n)
- **关键点：** 保存下一个节点、断开连接、重新连接
- **适用场景：** 迭代法在实际项目中更常用，递归法适合理解数据结构思想
