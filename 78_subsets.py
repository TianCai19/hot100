"""
78. 子集

回溯算法解法
"""

from typing import List


def subsets(nums: List[int]) -> List[List[int]]:
    """
    回溯算法解法

    时间复杂度: O(n * 2^n)
    空间复杂度: O(n)

    Args:
        nums: 整数数组

    Returns:
        所有可能的子集
    """
    result: List[List[int]] = []

    def backtrack(index: int, path: List[int]):
        # 每个节点都是一个子集
        result.append(path.copy())

        # 遍历剩余元素
        for i in range(index, len(nums)):
            # 选择当前元素
            path.append(nums[i])
            # 递归处理剩余元素
            backtrack(i + 1, path)
            # 回溯：移除当前元素
            path.pop()

    backtrack(0, [])
    return result


def subsets_iterative(nums: List[int]) -> List[List[int]]:
    """
    迭代解法

    时间复杂度: O(n * 2^n)
    空间复杂度: O(n * 2^n)
    """
    result: List[List[int]] = [[]]

    for num in nums:
        # 当前已有的子集数量
        current_size = len(result)
        # 为每个已有子集添加当前元素，生成新子集
        for i in range(current_size):
            new_subset = result[i].copy()
            new_subset.append(num)
            result.append(new_subset)

    return result


def subsets_bitmap(nums: List[int]) -> List[List[int]]:
    """
    二进制位图解法

    时间复杂度: O(n * 2^n)
    空间复杂度: O(n * 2^n)
    """
    n = len(nums)
    result: List[List[int]] = []

    # 遍历所有可能的子集状态
    for mask in range(1 << n):
        subset: List[int] = []
        # 检查每一位是否被选中
        for i in range(n):
            if mask & (1 << i):
                subset.append(nums[i])
        result.append(subset)

    return result


# 测试用例
def test_subsets():
    """测试子集生成函数"""

    # 测试用例1
    nums1 = [1, 2, 3]
    expected1 = [[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]
    result1 = subsets(nums1)
    print(f"测试1: {sorted(result1) == sorted(expected1)}")

    # 测试用例2
    nums2 = [0]
    expected2 = [[], [0]]
    result2 = subsets(nums2)
    print(f"测试2: {sorted(result2) == sorted(expected2)}")

    # 测试用例3
    nums3 = []
    expected3 = [[]]
    result3 = subsets(nums3)
    print(f"测试3: {sorted(result3) == sorted(expected3)}")

    # 测试用例4：验证迭代解法
    nums4 = [1, 2]
    result4_iter = subsets_iterative(nums4)
    result4_backtrack = subsets(nums4)
    print(f"测试4 (迭代 vs 回溯): {sorted(result4_iter) == sorted(result4_backtrack)}")

    # 测试用例5：验证位图解法
    nums5 = [1, 2, 3]
    result5_bitmap = subsets_bitmap(nums5)
    result5_backtrack = subsets(nums5)
    print(f"测试5 (位图 vs 回溯): {sorted(result5_bitmap) == sorted(result5_backtrack)}")


if __name__ == "__main__":
    test_subsets()
    print("\n所有测试通过！")
