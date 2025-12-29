---
title: "两数相加"
difficulty: "中等"
description: "给你两个非空的链表，表示两个非负整数。数字最高位位于链表开始位置。每个节点都包含一个数字。数字以逆序的方式存储，这样每个节点就包含一个数字。请将这两个数相加，并以相同形式返回一个链表。"
---

# 2. 两数相加

<DifficultyBadge difficulty="中等" />

## 题目描述

给你两个非空的链表，表示两个非负整数。数字最高位位于链表开始位置。每个节点都包含一个数字。数字以**逆序**的方式存储，这样每个节点就包含一个数字。请将这两个数相加，并以相同形式返回一个链表。

你可以假设除了数字 0 之外，这两个数都不会以零开头。

**示例 1：**

```
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807
```

**示例 2：**

```
输入：l1 = [0], l2 = [0]
输出：[0]
```

**示例 3：**

```
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
```

## 解题思路

这道题本质上是**大整数加法**，难点在于用链表存储数字。

### 核心思路

1. **同步遍历**两个链表，从头到尾相加
2. **逐位相加**，考虑**进位**
3. 处理**不同长度**的链表
4. 处理最后的**进位**

### 关键点

- 使用**哑节点**简化操作
- 维护进位变量 `carry`
- 最后检查 `carry > 0` 并添加节点

## 可视化示例

{<svg width="700" height="180" xmlns="http://www.w3.org/2000/svg">
  {/* 链表1 */}
  <text x="20" y="30" fontFamily="Arial" fontSize="14" fill="#fff">链表1: [2, 4, 3]</text>
  <rect x="20" y="50" width="40" height="40" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="40" y="75" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">2</text>
  <rect x="60" y="50" width="40" height="40" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="80" y="75" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">4</text>
  <rect x="100" y="50" width="40" height="40" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="120" y="75" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">3</text>
  <path d="M 140 70 L 160 70" stroke="#fff" strokeWidth="2" markerEnd="url(#arrowhead)"/>

  {/* 链表2 */}
  <text x="20" y="120" fontFamily="Arial" fontSize="14" fill="#fff">链表2: [5, 6, 4]</text>
  <rect x="20" y="140" width="40" height="40" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="40" y="165" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">5</text>
  <rect x="60" y="140" width="40" height="40" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="80" y="165" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">6</text>
  <rect x="100" y="140" width="40" height="40" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="120" y="165" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">4</text>
  <path d="M 140 160 L 160 160" stroke="#fff" strokeWidth="2" markerEnd="url(#arrowhead)"/>

  {/* 结果 */}
  <text x="200" y="30" fontFamily="Arial" fontSize="14" fill="#fff">相加过程:</text>
  <text x="200" y="70" fontFamily="Arial" fontSize="12" fill="#ccc">2+5=7, carry=0</text>
  <text x="200" y="100" fontFamily="Arial" fontSize="12" fill="#ccc">4+6=10, carry=1, digit=0</text>
  <text x="200" y="130" fontFamily="Arial" fontSize="12" fill="#ccc">3+4+carry=8, carry=0</text>
  <text x="200" y="160" fontFamily="Arial" fontSize="14" fill="#fff">结果: [7, 0, 8]</text>

  <defs>
    <marker id="arrowhead" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
      <polygon points="0 0, 10 3.5, 0 7" fill="#fff"/>
    </marker>
  </defs>
</svg>}

## 代码实现

### Python 实现

```python
from typing import Optional

# 定义链表节点
class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

    def __repr__(self):
        return f"ListNode({self.val})"

def add_two_numbers(l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
    """
    解法：逐位相加 + 进位处理
    时间复杂度：O(max(m, n))，m 和 n 是两个链表的长度
    空间复杂度：O(max(m, n))
    """
    dummy = ListNode(0)  # 哑节点，简化操作
    current = dummy
    carry = 0

    while l1 or l2 or carry:
        # 获取当前位的值（如果链表还有节点）
        val1 = l1.val if l1 else 0
        val2 = l2.val if l2 else 0

        # 计算当前位的和
        total = val1 + val2 + carry
        carry = total // 10  # 计算进位

        # 创建新节点
        current.next = ListNode(total % 10)
        current = current.next

        # 移动到下一个节点
        if l1:
            l1 = l1.next
        if l2:
            l2 = l2.next

    return dummy.next

# 辅助函数：链表转列表
def list_to_linkedlist(nums):
    dummy = ListNode(0)
    current = dummy
    for num in nums:
        current.next = ListNode(num)
        current = current.next
    return dummy.next

# 辅助函数：链表转列表
def linkedlist_to_list(head: Optional[ListNode]):
    result = []
    current = head
    while current:
        result.append(current.val)
        current = current.next
    return result

# 测试用例
if __name__ == "__main__":
    # 示例1: [2,4,3] + [5,6,4] = [7,0,8]
    l1 = list_to_linkedlist([2, 4, 3])
    l2 = list_to_linkedlist([5, 6, 4])
    result1 = add_two_numbers(l1, l2)
    print(f"示例1: {linkedlist_to_list(result1)}")  # [7, 0, 8]

    # 示例2: [0] + [0] = [0]
    l1 = list_to_linkedlist([0])
    l2 = list_to_linkedlist([0])
    result2 = add_two_numbers(l1, l2)
    print(f"示例2: {linkedlist_to_list(result2)}")  # [0]

    # 示例3: [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    l1 = list_to_linkedlist([9, 9, 9, 9, 9, 9, 9])
    l2 = list_to_linkedlist([9, 9, 9, 9])
    result3 = add_two_numbers(l1, l2)
    print(f"示例3: {linkedlist_to_list(result3)}")  # [8, 9, 9, 9, 0, 0, 0, 1]

    # 额外测试: 不同长度
    l1 = list_to_linkedlist([1, 2, 3])
    l2 = list_to_linkedlist([4, 5])
    result4 = add_two_numbers(l1, l2)
    print(f"额外测试: {linkedlist_to_list(result4)}")  # [5, 7, 3]
```

### C++ 实现

```cpp
#include <iostream>
using namespace std;

// 定义链表节点
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    /**
     * 解法：逐位相加 + 进位处理
     * 时间复杂度：O(max(m, n))，m 和 n 是两个链表的长度
     * 空间复杂度：O(max(m, n))
     */
    ListNode* dummy = new ListNode(0);  // 哑节点
    ListNode* current = dummy;
    int carry = 0;

    while (l1 != nullptr || l2 != nullptr || carry) {
        // 获取当前位的值（如果链表还有节点）
        int val1 = (l1 != nullptr) ? l1->val : 0;
        int val2 = (l2 != nullptr) ? l2->val : 0;

        // 计算当前位的和
        int total = val1 + val2 + carry;
        carry = total / 10;  // 计算进位

        // 创建新节点
        current->next = new ListNode(total % 10);
        current = current->next;

        // 移动到下一个节点
        if (l1 != nullptr) l1 = l1->next;
        if (l2 != nullptr) l2 = l2->next;
    }

    return dummy->next;
}

// 辅助函数：数组转链表
ListNode* listToLinkedList(const vector<int>& nums) {
    ListNode* dummy = new ListNode(0);
    ListNode* current = dummy;
    for (int num : nums) {
        current->next = new ListNode(num);
        current = current->next;
    }
    return dummy->next;
}

// 辅助函数：链表转数组
vector<int> linkedListToList(ListNode* head) {
    vector<int> result;
    ListNode* current = head;
    while (current != nullptr) {
        result.push_back(current->val);
        current = current->next;
    }
    return result;
}

// 辅助函数：打印链表
void printList(ListNode* head) {
    cout << "[";
    ListNode* current = head;
    while (current != nullptr) {
        cout << current->val;
        if (current->next != nullptr) cout << ", ";
        current = current->next;
    }
    cout << "]" << endl;
}

// 测试用例
int main() {
    // 示例1: [2,4,3] + [5,6,4] = [7,0,8]
    ListNode* l1 = listToLinkedList({2, 4, 3});
    ListNode* l2 = listToLinkedList({5, 6, 4});
    ListNode* result1 = addTwoNumbers(l1, l2);
    cout << "示例1: ";
    printList(result1);  // [7, 0, 8]

    // 示例2: [0] + [0] = [0]
    l1 = listToLinkedList({0});
    l2 = listToLinkedList({0});
    ListNode* result2 = addTwoNumbers(l1, l2);
    cout << "示例2: ";
    printList(result2);  // [0]

    // 示例3: [9,9,9,9,9,9,9] + [9,9,9,9] = [8,9,9,9,0,0,0,1]
    l1 = listToLinkedList({9, 9, 9, 9, 9, 9, 9});
    l2 = listToLinkedList({9, 9, 9, 9});
    ListNode* result3 = addTwoNumbers(l1, l2);
    cout << "示例3: ";
    printList(result3);  // [8, 9, 9, 9, 0, 0, 0, 1]

    // 额外测试: 不同长度
    l1 = listToLinkedList({1, 2, 3});
    l2 = listToLinkedList({4, 5});
    ListNode* result4 = addTwoNumbers(l1, l2);
    cout << "额外测试: ";
    printList(result4);  // [5, 7, 3]

    return 0;
}
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 逐位相加 | O(max(m, n)) | O(max(m, n)) | **标准解法**，处理进位优雅 |

## 关键总结

- **链表遍历**是基本功，务必熟练
- **哑节点**技巧可以简化链表操作
- **进位处理**要考虑边界情况（最后一个进位）
- 这是**链表专题**的经典题目