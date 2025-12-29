"""
206. 反转链表
https://leetcode.com/problems/reverse-linked-list/
"""

from typing import Optional, List


class ListNode:
    """链表节点"""
    def __init__(self, val: int = 0, next: Optional['ListNode'] = None):
        self.val = val
        self.next = next

    def __repr__(self):
        return f"ListNode({self.val})"

    def to_list(self) -> List[int]:
        """将链表转换为列表"""
        result = []
        node = self
        while node:
            result.append(node.val)
            node = node.next
        return result


class Solution:
    """解法一：迭代法（双指针）"""
    def reverseList_iterative(self, head: Optional[ListNode]) -> Optional[ListNode]:
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

    """解法二：递归法"""
    def reverseList_recursive(self, head: Optional[ListNode]) -> Optional[ListNode]:
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


def create_linked_list(values: List[int]) -> Optional[ListNode]:
    """根据列表创建链表"""
    if not values:
        return None

    head = ListNode(values[0])
    current = head
    for val in values[1:]:
        current.next = ListNode(val)
        current = current.next

    return head


def compare_linked_lists(l1: Optional[ListNode], l2: Optional[ListNode]) -> bool:
    """比较两个链表是否相等"""
    while l1 and l2:
        if l1.val != l2.val:
            return False
        l1 = l1.next
        l2 = l2.next

    return l1 is None and l2 is None


def test_solution():
    """测试所有解法"""
    print("=" * 60)
    print("测试反转链表")
    print("=" * 60)

    test_cases = [
        {
            "input": [1, 2, 3, 4, 5],
            "expected": [5, 4, 3, 2, 1],
            "description": "示例1：5个节点"
        },
        {
            "input": [1, 2],
            "expected": [2, 1],
            "description": "示例2：2个节点"
        },
        {
            "input": [],
            "expected": [],
            "description": "示例3：空链表"
        },
        {
            "input": [1],
            "expected": [1],
            "description": "单个节点"
        },
        {
            "input": [1, 2, 3],
            "expected": [3, 2, 1],
            "description": "3个节点"
        },
        {
            "input": [1, 2, 3, 4],
            "expected": [4, 3, 2, 1],
            "description": "4个节点"
        },
        {
            "input": list(range(1, 11)),
            "expected": list(range(10, 0, -1)),
            "description": "10个节点"
        },
        {
            "input": [0, 0, 0, 0],
            "expected": [0, 0, 0, 0],
            "description": "重复值"
        },
        {
            "input": [-1, -2, -3, -4],
            "expected": [-4, -3, -2, -1],
            "description": "负数"
        },
        {
            "input": [5, 3, 1, 2, 4],
            "expected": [4, 2, 1, 3, 5],
            "description": "乱序数组"
        }
    ]

    methods = [
        ("迭代法 (双指针)", Solution().reverseList_iterative),
        ("递归法", Solution().reverseList_recursive)
    ]

    for method_name, method in methods:
        print(f"\n{'=' * 60}")
        print(f"测试方法: {method_name}")
        print(f"{'=' * 60}")

        passed = 0
        failed = 0

        for i, test_case in enumerate(test_cases, 1):
            input_list = test_case["input"]
            expected_list = test_case["expected"]
            description = test_case["description"]

            try:
                # 创建输入链表
                head = create_linked_list(input_list)

                # 执行反转
                result_head = method(head)

                # 转换为列表
                result_list = result_head.to_list() if result_head else []

                # 验证结果
                if result_list == expected_list:
                    print(f"✓ 测试 {i} 通过: {description}")
                    print(f"  输入: {input_list}")
                    print(f"  输出: {result_list}")
                    passed += 1
                else:
                    print(f"✗ 测试 {i} 失败: {description}")
                    print(f"  输入: {input_list}")
                    print(f"  期望: {expected_list}")
                    print(f"  实际: {result_list}")
                    failed += 1
            except Exception as e:
                print(f"✗ 测试 {i} 出现异常: {description}")
                print(f"  异常: {e}")
                failed += 1

        print(f"\n{'-' * 60}")
        print(f"测试结果: {passed} 通过, {failed} 失败")
        print(f"{'-' * 60}")

        if failed == 0:
            print(f"✓ {method_name} 所有测试通过!")

    print(f"\n{'=' * 60}")
    print("所有测试完成!")
    print(f"{'=' * 60}")


def test_performance():
    """性能测试"""
    print("\n" + "=" * 60)
    print("性能测试")
    print("=" * 60)

    import time

    # 测试不同规模的链表（递归法对大数据有栈溢出风险）
    sizes = [100, 500, 1000]

    for size in sizes:
        print(f"\n测试规模: {size} 个节点")

        # 创建大链表
        values = list(range(1, size + 1))

        # 测试迭代法
        head = create_linked_list(values)
        start_time = time.time()
        result_head = Solution().reverseList_iterative(head)
        elapsed_time = time.time() - start_time
        print(f"  迭代法: {elapsed_time:.6f} 秒")

        # 测试递归法（仅对小规模测试，Python 默认递归限制约 1000）
        if size <= 800:
            head = create_linked_list(values)
            start_time = time.time()
            result_head = Solution().reverseList_recursive(head)
            elapsed_time = time.time() - start_time
            print(f"  递归法: {elapsed_time:.6f} 秒")
        else:
            print(f"  递归法: 跳过（{size} > 800，Python 递归限制）")


def test_memory_efficiency():
    """内存效率测试"""
    print("\n" + "=" * 60)
    print("内存效率测试")
    print("=" * 60)

    # 测试极端情况：超长链表
    # 递归法可能会导致栈溢出
    try:
        size = 100000
        print(f"\n创建 {size} 个节点的链表...")
        values = list(range(1, size + 1))
        head = create_linked_list(values)

        print("测试迭代法...")
        result = Solution().reverseList_iterative(head)
        print("✓ 迭代法成功处理大链表")

        # 重新创建链表
        head = create_linked_list(values)

        print("测试递归法...")
        result = Solution().reverseList_recursive(head)
        print("✓ 递归法成功处理大链表")

    except RecursionError:
        print("✗ 递归法栈溢出（预期行为）")
    except Exception as e:
        print(f"✗ 测试出现异常: {e}")


if __name__ == "__main__":
    test_solution()
    test_performance()
    test_memory_efficiency()
