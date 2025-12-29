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
