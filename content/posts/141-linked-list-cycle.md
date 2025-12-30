---
title: "141. 环形链表"
difficulty: "简单"
description: "给你一个链表的头节点 head，判断链表中是否有环。如果链表中存在环，则返回 true ；否则，返回 false。"
---

# 141. 环形链表

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给你一个链表的头节点 `head`，判断链表中是否有环。

如果链表中存在环，则返回 `true` ；否则，返回 `false` 。

如果链表中存在环，则称链表中有环。**进阶**：你能否不使用额外空间解决此问题？

### 示例

```text
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾节点指向索引 1 的节点（从头节点开始的第二个节点）
```

```text
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾节点指向头节点
```

```text
输入：head = [1], pos = -1
输出：false
解释：链表中没有环
```

## 解法一：快慢指针（推荐）

### 思路

使用快慢指针判断链表中是否有环：
- **慢指针**每次移动一步，**快指针**每次移动两步
- 如果链表中存在环，快指针最终会进入环中并与慢指针相遇
- 如果链表中不存在环，快指针会先到达链表尾部

这是一个经典问题，利用了相对速度的概念：在一个环中，两个不同速度的指针必然会相遇。

### Python

```python
from typing import Optional

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def has_cycle(head: Optional[ListNode]) -> bool:
    """
    快慢指针解法

    时间复杂度: O(n)，其中 n 是链表长度
    空间复杂度: O(1)
    """
    if not head or not head.next:
        return False

    slow = head  # 慢指针
    fast = head  # 快指针

    while fast and fast.next:
        slow = slow.next        # 慢指针走一步
        fast = fast.next.next   # 快指针走两步

        if slow == fast:        # 相遇，说明有环
            return True

    return False  # 快指针到达链表尾部，说明无环
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
    bool hasCycle(ListNode *head) {
        if (!head || !head->next) {
            return false;
        }

        ListNode *slow = head;  // 慢指针
        ListNode *fast = head;  // 快指针

        while (fast && fast->next) {
            slow = slow->next;          // 慢指针走一步
            fast = fast->next->next;    // 快指针走两步

            if (slow == fast) {         // 相遇，说明有环
                return true;
            }
        }

        return false;  // 快指针到达链表尾部，说明无环
    }
};
```

## 解法二：哈希集合

### 思路

使用哈希集合记录遍历过的节点：
- 遍历链表，将每个节点的地址存入集合
- 如果当前节点已经在集合中，说明链表有环
- 如果遍历到链表尾部（节点为 `null`），说明链表无环

### Python

```python
def has_cycle_hash(head: Optional[ListNode]) -> bool:
    """
    哈希集合解法

    时间复杂度: O(n)
    空间复杂度: O(n)
    """
    seen = set()
    current = head

    while current:
        if current in seen:
            return True
        seen.add(current)
        current = current.next

    return False
```

### C++

```cpp
#include <unordered_set>
using namespace std;

bool hasCycleHash(ListNode *head) {
    unordered_set<ListNode*> seen;
    ListNode *current = head;

    while (current) {
        if (seen.find(current) != seen.end()) {
            return true;
        }
        seen.insert(current);
        current = current.next;
    }

    return false;
}
```

## 解法三：标记法（破坏链表结构）

### 思路

通过修改节点的值或指针结构来标记已访问的节点：
- 在遍历过程中，将已访问节点的 `val` 设为特殊值（如 `None` 或特殊标记）
- 如果再次访问到已标记的节点，说明有环

这种方法会破坏链表结构，实际生产环境不推荐，但可以用于面试或特定场景。

### Python

```python
def has_cycle_mark(head: Optional[ListNode]) -> bool:
    """
    标记法（破坏链表结构）

    时间复杂度: O(n)
    空间复杂度: O(1)
    """
    current = head

    while current:
        if current.val is None:  # 检查是否被标记过
            return True
        current.val = None  # 标记当前节点
        current = current.next

    return False
```

### C++

```cpp
bool hasCycleMark(ListNode *head) {
    ListNode *current = head;

    while (current) {
        if (current->val == INT_MIN) {  // 使用特殊值标记
            return true;
        }
        current->val = INT_MIN;  // 标记当前节点
        current = current->next;
    }

    return false;
}
```

## 复杂度对比

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|------------|------------|------|
| 快慢指针 | O(n) | O(1) | **推荐**，满足进阶要求，不破坏结构 |
| 哈希集合 | O(n) | O(n) | 直观易懂，使用额外空间 |
| 标记法 | O(n) | O(1) | 空间最优，但破坏链表结构 |

## 总结

- **快慢指针是最优解**，完美满足进阶要求：O(n) 时间，O(1) 空间
- 快慢指针的核心思想：**相对速度**导致在环中必然相遇
- 关键点：必须检查 `fast` 和 `fast.next` 是否存在，避免空指针异常
- 哈希集合解法直观但空间复杂度不满足进阶要求
- 标记法虽然节省空间，但会破坏链表结构，实际应用中不推荐
- 这类问题体现了**双指针技巧**的威力，在链表问题中应用广泛
