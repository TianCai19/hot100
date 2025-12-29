"""
215. 数组中的第 K 个最大元素
https://leetcode.com/problems/kth-largest-element-in-an-array/
"""

from typing import List
import heapq
import random


class Solution:
    """解法一：排序法"""
    def findKthLargest_sort(self, nums: List[int], k: int) -> int:
        """
        直接排序法
        时间复杂度: O(n log n)
        空间复杂度: O(1)
        """
        nums.sort(reverse=True)
        return nums[k - 1]

    """解法二：最小堆（推荐）"""
    def findKthLargest_heap(self, nums: List[int], k: int) -> int:
        """
        最小堆维护前 k 个最大元素
        时间复杂度: O(n log k)
        空间复杂度: O(k)
        """
        min_heap = []

        for num in nums:
            heapq.heappush(min_heap, num)
            if len(min_heap) > k:
                heapq.heappop(min_heap)

        return min_heap[0]

    """解法三：快速选择算法"""
    def findKthLargest_quickselect(self, nums: List[int], k: int) -> int:
        """
        基于快速排序的选择算法
        平均时间复杂度: O(n)
        最坏时间复杂度: O(n²)
        空间复杂度: O(1)
        """
        n = len(nums)
        target = n - k

        def partition(nums: List[int], left: int, right: int, pivot_index: int) -> int:
            pivot = nums[pivot_index]
            # 将基准元素移到末尾
            nums[pivot_index], nums[right] = nums[right], nums[pivot_index]
            store_index = left

            # 将所有比基准大的元素移到左边
            for i in range(left, right):
                if nums[i] < pivot:
                    nums[store_index], nums[i] = nums[i], nums[store_index]
                    store_index += 1

            # 将基准元素移回正确位置
            nums[right], nums[store_index] = nums[store_index], nums[right]
            return store_index

        def quickselect(nums: List[int], left: int, right: int) -> int:
            if left == right:
                return nums[left]

            # 随机选择基准元素
            pivot_index = random.randint(left, right)
            pivot_index = partition(nums, left, right, pivot_index)

            if pivot_index == target:
                return nums[pivot_index]
            elif pivot_index < target:
                return quickselect(nums, pivot_index + 1, right)
            else:
                return quickselect(nums, left, pivot_index - 1)

        return quickselect(nums, 0, n - 1)


def test_solution():
    """测试所有解法"""
    solution = Solution()

    test_cases = [
        {
            "nums": [3, 2, 1, 5, 6, 4],
            "k": 2,
            "expected": 5
        },
        {
            "nums": [3, 2, 3, 1, 2, 4, 5, 5, 6],
            "k": 4,
            "expected": 4
        },
        {
            "nums": [1],
            "k": 1,
            "expected": 1
        },
        {
            "nums": [2, 1],
            "k": 1,
            "expected": 2
        },
        {
            "nums": [2, 1],
            "k": 2,
            "expected": 1
        },
        {
            "nums": [3, 3, 3, 3, 3, 3],
            "k": 1,
            "expected": 3
        },
        {
            "nums": [-1, -2, -3],
            "k": 1,
            "expected": -1
        },
        {
            "nums": [-1, -2, -3],
            "k": 3,
            "expected": -3
        },
        {
            "nums": list(range(1, 11)),
            "k": 3,
            "expected": 8
        },
        {
            "nums": list(range(10, 0, -1)),
            "k": 5,
            "expected": 6
        }
    ]

    methods = [
        ("排序法", solution.findKthLargest_sort),
        ("最小堆", solution.findKthLargest_heap),
        ("快速选择", solution.findKthLargest_quickselect)
    ]

    for method_name, method in methods:
        print(f"\n{'='*60}")
        print(f"测试方法: {method_name}")
        print(f"{'='*60}")

        passed = 0
        failed = 0

        for i, test_case in enumerate(test_cases, 1):
            nums = test_case["nums"].copy()  # 防止修改原数组
            k = test_case["k"]
            expected = test_case["expected"]

            try:
                result = method(nums, k)

                if result == expected:
                    print(f"✓ 测试 {i} 通过")
                    print(f"  输入: nums={test_case['nums']}, k={k}")
                    print(f"  输出: {result}, 期望: {expected}")
                    passed += 1
                else:
                    print(f"✗ 测试 {i} 失败")
                    print(f"  输入: nums={test_case['nums']}, k={k}")
                    print(f"  输出: {result}, 期望: {expected}")
                    failed += 1
            except Exception as e:
                print(f"✗ 测试 {i} 出现异常: {e}")
                print(f"  输入: nums={test_case['nums']}, k={k}")
                failed += 1

        print(f"\n{'-'*60}")
        print(f"测试结果: {passed} 通过, {failed} 失败")
        print(f"{'-'*60}")

        if failed == 0:
            print(f"✓ {method_name} 所有测试通过!")

    print(f"\n{'='*60}")
    print("所有测试完成!")
    print(f"{'='*60}")


if __name__ == "__main__":
    test_solution()
