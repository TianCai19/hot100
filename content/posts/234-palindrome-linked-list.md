---
title: "234. 回文链表"
difficulty: "简单"
description: "给你一个单链表的头节点 head，请你判断该链表是否为回文链表。"
---

# 234. 回文链表

**难度：<DifficultyBadge>简单</DifficultyBadge>**

## 题目描述

给你一个单链表的头节点 `head`，请你判断该链表是否为回文链表。

### 图示

<Mermaid>
graph LR
    subgraph 回文链表示例
        N1((1)) --> N2((2)) --> N3((2)) --> N4((1))
    end
    style N1 fill:#9d4edd
    style N4 fill:#9d4edd
    style N2 fill:#4cc9f0
    style N3 fill:#4cc9f0
</Mermaid>

**示例：** `1 -> 2 -> 2 -> 1` 是回文链表（首尾对称）

## 示例

### 示例 1

<Mermaid>
graph LR
    H1((1)) --> H2((2)) --> H3((2)) --> H4((1))
    style H1 fill:#9d4edd
    style H4 fill:#9d4edd
    style H2 fill:#4cc9f0
    style H3 fill:#4cc9f0
</Mermaid>

- **输入：** `head = [1,2,2,1]`
- **输出：** `true`

### 示例 2

<Mermaid>
graph LR
    F1((1)) --> F2((2))
    style F1 fill:#ff6b6b
    style F2 fill:#4cc9f0
</Mermaid>

- **输入：** `head = [1,2]`
- **输出：** `false`

## 提示

- 链表中节点数目在范围 `[1, 10^5]` 内
- `0 <= Node.val <= 9`

**进阶：** 你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

---

## 解法一：数组 + 双指针

### 思路

将链表值复制到数组中，然后用双指针从两端向中间比较。

<Mermaid>
graph TB
    subgraph 链表转数组
        L[1->2->2->1] --> A[(1,2,2,1)]
    end
    subgraph 双指针比较
        A --> P1["左指针 →"]
        A --> P2["← 右指针"]
    end
</Mermaid>

### Python

```python
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        vals = []
        curr = head
        while curr:
            vals.append(curr.val)
            curr = curr.next

        left, right = 0, len(vals) - 1
        while left < right:
            if vals[left] != vals[right]:
                return False
            left += 1
            right -= 1

        return True
```

### C++

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        vector<int> vals;
        ListNode* curr = head;
        while (curr) {
            vals.push_back(curr->val);
            curr = curr->next;
        }

        int left = 0, right = vals.size() - 1;
        while (left < right) {
            if (vals[left] != vals[right]) {
                return false;
            }
            left++;
            right--;
        }

        return true;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n)
- **空间复杂度：** O(n)，需要额外数组存储所有节点值

---

## 解法二：递归

### 思路

递归为我们提供了一种优雅的方式来反向遍历节点。利用递归函数的堆栈特性，我们可以先递归到链表末尾，然后在回溯的过程中从后向前比较节点值。

核心思想：
- 使用外部指针 `front_pointer` 从前向后遍历
- 递归函数 `recursively_check` 从后向前访问节点
- 在递归回溯时比较 `front_pointer` 和当前节点的值

<Mermaid>
graph TB
    subgraph 递归调用栈
        A["recursively_check(1)"] --> B["recursively_check(2)"]
        B --> C["recursively_check(2)"]
        C --> D["recursively_check(1)"]
        D --> E["recursively_check(None)"]
    end
    subgraph 回溯比较
        E --> F["返回 True"]
        F --> G["比较 1 == front.val"]
        G --> H["比较 2 == front.next.val"]
        H --> I["比较 2 == front.next.next.val"]
    end
</Mermaid>

**注意：** 虽然递归代码很优雅，但空间复杂度仍然是 O(n)，因为递归调用栈会占用 n 个栈帧。而且在 Python 中，递归深度限制约为 1000，对于长链表可能会栈溢出。

### Python

```python
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        self.front_pointer = head

        def recursively_check(current_node=head):
            if current_node is not None:
                if not recursively_check(current_node.next):
                    return False
                if self.front_pointer.val != current_node.val:
                    return False
                self.front_pointer = self.front_pointer.next
            return True

        return recursively_check()
```

### C++

```cpp
class Solution {
private:
    ListNode* frontPointer;

public:
    bool recursivelyCheck(ListNode* currentNode) {
        if (currentNode != nullptr) {
            if (!recursivelyCheck(currentNode->next)) {
                return false;
            }
            if (frontPointer->val != currentNode->val) {
                return false;
            }
            frontPointer = frontPointer->next;
        }
        return true;
    }

    bool isPalindrome(ListNode* head) {
        frontPointer = head;
        return recursivelyCheck(head);
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n)，递归遍历整个链表
- **空间复杂度：** O(n)，递归调用栈占用 n 个栈帧

---

## 解法三：快慢指针 + 反转链表（推荐）

### 思路

1. **找中点：** 用快慢指针找到链表中点（慢指针每次走1步，快指针每次走2步）
2. **反转后半部分：** 反转中点之后的链表
3. **比较：** 同时遍历前半部分和反转后的后半部分，逐个比较
4. **恢复（可选）：** 反转后半部分恢复原链表

<Mermaid>
graph TB
    subgraph 第一步: 找中点
        SLOW["慢指针: 1→2"]
        FAST["快指针: 1→2→2→1"]
    end
    subgraph 第二步: 反转后半部分
        ORIG["原: 1→2→2→1"]
        REV["后: 1→2→1→2"]
    end
    subgraph 第三步: 比较
        COMP["1==1 ✓<br/>2==2 ✓"]
    end
</Mermaid>

### 反转链表核心代码

```python
def reverse_list(head):
    prev = None
    curr = head
    while curr:
        next_temp = curr.next
        curr.next = prev
        prev = curr
        curr = next_temp
    return prev
```

### Python

```python
class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        if head is None:
            return True

        # 第一步：找到前半部分链表的尾节点
        first_half_end = self.end_of_first_half(head)
        # 第二步：反转后半部分链表
        second_half_start = self.reverse_list(first_half_end.next)

        # 第三步：判断是否回文
        result = True
        first_position = head
        second_position = second_half_start
        while result and second_position is not None:
            if first_position.val != second_position.val:
                result = False
            first_position = first_position.next
            second_position = second_position.next

        # 第四步（可选）：还原链表并返回结果
        first_half_end.next = self.reverse_list(second_half_start)
        return result

    def end_of_first_half(self, head):
        fast = head
        slow = head
        while fast.next is not None and fast.next.next is not None:
            fast = fast.next.next
            slow = slow.next
        return slow

    def reverse_list(self, head):
        previous = None
        current = head
        while current is not None:
            next_node = current.next
            current.next = previous
            previous = current
            current = next_node
        return previous
```

### C++

```cpp
class Solution {
private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }

    ListNode* endOfFirstHalf(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) return true;

        // 第一步：找到前半部分链表的尾节点并反转后半部分链表
        ListNode* firstHalfEnd = endOfFirstHalf(head);
        ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

        // 第二步：判断是否回文
        ListNode* p1 = head;
        ListNode* p2 = secondHalfStart;
        bool result = true;
        while (result && p2 != nullptr) {
            if (p1->val != p2->val) {
                result = false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }

        // 第三步（可选）：还原链表并返回结果
        firstHalfEnd->next = reverseList(secondHalfStart);
        return result;
    }
};
```

### 复杂度分析

- **时间复杂度：** O(n)
- **空间复杂度：** O(1)，只使用常量级额外空间

---

## 三种解法对比

| 解法 | 时间复杂度 | 空间复杂度 | 优点 | 缺点 |
|------|-----------|-----------|------|------|
| 数组 + 双指针 | O(n) | O(n) | 思路简单，代码简洁 | 需要额外空间 |
| 递归 | O(n) | O(n) | 代码优雅，易理解 | 栈深度限制，空间仍为 O(n) |
| 快慢指针 + 反转 | O(n) | O(1) | 空间最优，满足进阶要求 | 代码稍复杂，会修改原链表结构 |

## 总结

- **入门推荐：** 数组 + 双指针，最直观易实现
- **学习递归：** 递归解法展示了如何利用栈的特性反向遍历
- **面试最优：** 快慢指针 + 反转链表，满足 O(1) 空间复杂度的进阶要求
- **实际建议：** 先说出简单解法，再逐步优化到最优解
