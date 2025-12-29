from typing import List

def two_sum(nums: List[int], target: int) -> List[int]:
    """
    解法二：哈希表优化
    时间复杂度：O(n)
    空间复杂度：O(n)
    """
    hash_map = {}  # 存储 {数值: 索引}

    for i, num in enumerate(nums):
        complement = target - num

        if complement in hash_map:
            return [hash_map[complement], i]

        hash_map[num] = i

    return []

# 测试用例
if __name__ == "__main__":
    # 示例1
    nums1 = [2, 7, 11, 15]
    target1 = 9
    print(f"示例1: nums={nums1}, target={target1}")
    print(f"输出: {two_sum(nums1, target1)}")  # [0, 1]

    # 示例2
    nums2 = [3, 2, 4]
    target2 = 6
    print(f"\n示例2: nums={nums2}, target={target2}")
    print(f"输出: {two_sum(nums2, target2)}")  # [1, 2]

    # 示例3
    nums3 = [3, 3]
    target3 = 6
    print(f"\n示例3: nums={nums3}, target={target3}")
    print(f"输出: {two_sum(nums3, target3)}")  # [0, 1]

    # 额外测试
    nums4 = [1, 2, 3, 4, 5]
    target4 = 8
    print(f"\n额外测试: nums={nums4}, target={target4}")
    print(f"输出: {two_sum(nums4, target4)}")  # [2, 4]
