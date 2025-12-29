def max_area(height: list[int]) -> int:
    """
    解法：双指针
    时间复杂度：O(n)
    空间复杂度：O(1)
    """
    left = 0
    right = len(height) - 1
    max_area = 0

    while left < right:
        # 计算当前面积
        current_area = min(height[left], height[right]) * (right - left)
        # 更新最大面积
        max_area = max(max_area, current_area)

        # 移动较短的那条边
        if height[left] < height[right]:
            left += 1
        else:
            right -= 1

    return max_area

# 测试用例
if __name__ == "__main__":
    # 示例1
    height1 = [1, 8, 6, 2, 5, 4, 8, 3, 7]
    result1 = max_area(height1)
    print(f"示例1: height = {height1}")
    print(f"输出: {result1}")  # 49

    # 示例2
    height2 = [1, 1]
    result2 = max_area(height2)
    print(f"\n示例2: height = {height2}")
    print(f"输出: {result2}")  # 1

    # 示例3
    height3 = [4, 3, 2, 1, 4]
    result3 = max_area(height3)
    print(f"\n示例3: height = {height3}")
    print(f"输出: {result3}")  # 16

    # 额外测试
    height4 = [1, 2, 1]
    result4 = max_area(height4)
    print(f"\n额外测试: height = {height4}")
    print(f"输出: {result4}")  # 2

    height5 = [2, 3, 4, 5, 18, 17, 6]
    result5 = max_area(height5)
    print(f"\n额外测试: height = {height5}")
    print(f"输出: {result5}")  # 17
