# Definition for singly-linked list.
class ListNode:
    def __init__(self, x):
        self.val = x
        self.next = None


class Solution:
    def getIntersectionNode(self, headA: ListNode, headB: ListNode) -> ListNode:
        """
        双指针法：时间 O(m+n)，空间 O(1)
        两个指针分别从 A 和 B 出发，走完自己的链表后走对方的链表
        如果有交点会在交点相遇，没有交点会同时到达 None
        """
        if not headA or not headB:
            return None

        pA, pB = headA, headB

        # 当 pA == pB 时停止（可能是交点，也可能同时为 None）
        while pA != pB:
            pA = pA.next if pA else headB
            pB = pB.next if pB else headA

        return pA


# ==================== 测试代码 ====================

def build_intersected_lists(listA_vals, listB_vals, skipA, skipB):
    """构建两个相交的链表"""
    if not listA_vals or not listB_vals:
        return None, None

    # 创建链表 A 的独有部分
    dummyA = ListNode(0)
    currA = dummyA
    for i in range(skipA):
        currA.next = ListNode(listA_vals[i])
        currA = currA.next

    # 创建公共部分
    common_head = None
    if skipA < len(listA_vals):
        common_head = ListNode(listA_vals[skipA])
        curr = common_head
        for i in range(skipA + 1, len(listA_vals)):
            curr.next = ListNode(listA_vals[i])
            curr = curr.next
        currA.next = common_head

    # 创建链表 B 的独有部分并连接到公共部分
    dummyB = ListNode(0)
    currB = dummyB
    for i in range(skipB):
        currB.next = ListNode(listB_vals[i])
        currB = currB.next
    currB.next = common_head

    return dummyA.next, dummyB.next


def list_to_str(head):
    """链表转字符串，用于打印"""
    vals = []
    while head:
        vals.append(str(head.val))
        head = head.next
    return " -> ".join(vals) if vals else "Empty"


def test():
    solution = Solution()

    # 测试用例 1
    print("=" * 50)
    print("测试用例 1:")
    headA, headB = build_intersected_lists(
        [4, 1, 8, 4, 5], [5, 6, 1, 8, 4, 5], 2, 3
    )
    print(f"链表 A: {list_to_str(headA)}")
    print(f"链表 B: {list_to_str(headB)}")
    result = solution.getIntersectionNode(headA, headB)
    print(f"结果: Intersected at '{result.val}'" if result else "No intersection")
    assert result and result.val == 8, "测试用例 1 失败"
    print("✓ 通过")

    # 测试用例 2
    print("\n" + "=" * 50)
    print("测试用例 2:")
    headA, headB = build_intersected_lists(
        [1, 9, 1, 2, 4], [3, 2, 4], 3, 1
    )
    print(f"链表 A: {list_to_str(headA)}")
    print(f"链表 B: {list_to_str(headB)}")
    result = solution.getIntersectionNode(headA, headB)
    print(f"结果: Intersected at '{result.val}'" if result else "No intersection")
    assert result and result.val == 2, "测试用例 2 失败"
    print("✓ 通过")

    # 测试用例 3: 无交点
    print("\n" + "=" * 50)
    print("测试用例 3 (无交点):")
    # 分别创建两个不相交的链表
    headA = ListNode(2)
    headA.next = ListNode(6)
    headA.next.next = ListNode(4)

    headB = ListNode(1)
    headB.next = ListNode(5)

    print(f"链表 A: {list_to_str(headA)}")
    print(f"链表 B: {list_to_str(headB)}")
    result = solution.getIntersectionNode(headA, headB)
    print(f"结果: Intersected at '{result.val}'" if result else "No intersection")
    assert result is None, "测试用例 3 失败"
    print("✓ 通过")

    print("\n" + "=" * 50)
    print("所有测试用例通过！")


if __name__ == "__main__":
    test()
