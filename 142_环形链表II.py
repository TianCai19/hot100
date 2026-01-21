"""
142. 环形链表 II
https://leetcode.com/problems/linked-list-cycle-ii/
"""

from typing import Optional, List, Tuple


class ListNode:
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

    def __repr__(self) -> str:
        return f"ListNode({self.val})"


class Solution:
    def detectCycle(self, head: Optional[ListNode]) -> Optional[ListNode]:
        if not head or not head.next:
            return None

        slow = head
        fast = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                break
        else:
            return None

        finder = head
        while finder != slow:
            finder = finder.next
            slow = slow.next

        return finder


def build_cycle_list(values: List[int], pos: int) -> Tuple[Optional[ListNode], Optional[ListNode]]:
    if not values:
        return None, None

    nodes = [ListNode(val) for val in values]
    for i in range(len(nodes) - 1):
        nodes[i].next = nodes[i + 1]

    entry = None
    if pos != -1:
        entry = nodes[pos]
        nodes[-1].next = entry

    return nodes[0], entry


def test_solution() -> None:
    cases = [
        ([3, 2, 0, -4], 1, 2),
        ([1, 2], 0, 1),
        ([1], -1, None),
        ([1, 2, 3, 4, 5], 2, 3),
        ([1, 2, 3], -1, None),
    ]

    solution = Solution()

    for i, (values, pos, expected_val) in enumerate(cases, 1):
        head, entry = build_cycle_list(values, pos)
        result = solution.detectCycle(head)
        result_val = result.val if result else None
        expected = expected_val
        assert result_val == expected, f"case {i} failed: got {result_val}, expected {expected}"
        print(f"case {i} passed: entry = {result_val}")


if __name__ == "__main__":
    test_solution()
