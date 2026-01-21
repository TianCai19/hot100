"""
148. 排序链表
https://leetcode.com/problems/sort-list/
"""

from typing import Optional, List


class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

    def to_list(self) -> List[int]:
        result = []
        node = self
        while node:
            result.append(node.val)
            node = node.next
        return result


class Solution:
    def sortList(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return head

        mid = self._get_mid(head)
        right = mid.next
        mid.next = None

        left_sorted = self.sortList(head)
        right_sorted = self.sortList(right)

        return self._merge(left_sorted, right_sorted)

    def _get_mid(self, head: ListNode) -> ListNode:
        slow = head
        fast = head.next
        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
        return slow

    def _merge(self, l1: Optional[ListNode], l2: Optional[ListNode]) -> Optional[ListNode]:
        dummy = ListNode(0)
        tail = dummy

        while l1 and l2:
            if l1.val <= l2.val:
                tail.next = l1
                l1 = l1.next
            else:
                tail.next = l2
                l2 = l2.next
            tail = tail.next

        tail.next = l1 if l1 else l2
        return dummy.next


def build_list(values: List[int]) -> Optional[ListNode]:
    if not values:
        return None

    head = ListNode(values[0])
    node = head
    for val in values[1:]:
        node.next = ListNode(val)
        node = node.next
    return head


def test_solution() -> None:
    cases = [
        ([4, 2, 1, 3], [1, 2, 3, 4]),
        ([-1, 5, 3, 4, 0], [-1, 0, 3, 4, 5]),
        ([], []),
        ([1], [1]),
        ([2, 1], [1, 2]),
    ]

    solution = Solution()

    for i, (values, expected) in enumerate(cases, 1):
        head = build_list(values)
        result = solution.sortList(head)
        result_list = result.to_list() if result else []
        assert result_list == expected, f"case {i} failed: got {result_list}, expected {expected}"
        print(f"case {i} passed")


if __name__ == "__main__":
    test_solution()
