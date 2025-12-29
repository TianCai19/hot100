# Definition for singly-linked list.
class ListNode:
    def __init__(self, val=0):
        self.val = val
        self.next = None


class Solution:
    def isPalindrome(self, head: ListNode) -> bool:
        """
        快慢指针 + 反转链表：时间 O(n)，空间 O(1)
        1. 用快慢指针找中点
        2. 反转后半部分链表
        3. 比较前后两半是否相同
        """
        # 第一步：用快慢指针找中点
        slow = fast = head
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next

        # 第二步：反转后半部分链表
        prev = None
        curr = slow
        while curr:
            next_temp = curr.next
            curr.next = prev
            prev = curr
            curr = next_temp

        # 第三步：比较前后两半
        left, right = head, prev
        result = True
        while right:  # 只需要比较到后半部分结束
            if left.val != right.val:
                result = False
                break
            left = left.next
            right = right.next

        return result


# ==================== 测试代码 ====================

def build_list(vals):
    """根据数组构建链表"""
    if not vals:
        return None
    dummy = ListNode(0)
    curr = dummy
    for val in vals:
        curr.next = ListNode(val)
        curr = curr.next
    return dummy.next


def list_to_str(head):
    """链表转字符串，用于打印"""
    vals = []
    while head:
        vals.append(str(head.val))
        head = head.next
    return " -> ".join(vals) if vals else "Empty"


def test():
    solution = Solution()

    # 测试用例 1: 回文链表
    print("=" * 50)
    print("测试用例 1:")
    head1 = build_list([1, 2, 2, 1])
    print(f"链表: {list_to_str(head1)}")
    result1 = solution.isPalindrome(head1)
    print(f"结果: {result1}")
    assert result1 is True, "测试用例 1 失败"
    print("✓ 通过")

    # 测试用例 2: 非回文链表
    print("\n" + "=" * 50)
    print("测试用例 2:")
    head2 = build_list([1, 2])
    print(f"链表: {list_to_str(head2)}")
    result2 = solution.isPalindrome(head2)
    print(f"结果: {result2}")
    assert result2 is False, "测试用例 2 失败"
    print("✓ 通过")

    # 测试用例 3: 单节点（回文）
    print("\n" + "=" * 50)
    print("测试用例 3 (单节点):")
    head3 = build_list([1])
    print(f"链表: {list_to_str(head3)}")
    result3 = solution.isPalindrome(head3)
    print(f"结果: {result3}")
    assert result3 is True, "测试用例 3 失败"
    print("✓ 通过")

    # 测试用例 4: 奇数长度回文
    print("\n" + "=" * 50)
    print("测试用例 4 (奇数长度回文):")
    head4 = build_list([1, 2, 3, 2, 1])
    print(f"链表: {list_to_str(head4)}")
    result4 = solution.isPalindrome(head4)
    print(f"结果: {result4}")
    assert result4 is True, "测试用例 4 失败"
    print("✓ 通过")

    # 测试用例 5: 非回文（奇数长度）
    print("\n" + "=" * 50)
    print("测试用例 5 (非回文):")
    head5 = build_list([1, 2, 3, 4, 5])
    print(f"链表: {list_to_str(head5)}")
    result5 = solution.isPalindrome(head5)
    print(f"结果: {result5}")
    assert result5 is False, "测试用例 5 失败"
    print("✓ 通过")

    print("\n" + "=" * 50)
    print("所有测试用例通过！")


if __name__ == "__main__":
    test()
