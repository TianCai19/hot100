from typing import List


class Solution:
    def dailyTemperatures(self, temperatures: List[int]) -> List[int]:
        """
        单调栈法：时间 O(n)，空间 O(n)
        维护单调递减栈，存储温度的索引
        当遇到更高温度时，弹出栈顶并计算天数差
        """
        n = len(temperatures)
        answer = [0] * n
        stack = []  # 单调递减栈，存储索引

        for i, temp in enumerate(temperatures):
            # 当栈不为空且当前温度 > 栈顶温度
            while stack and temp > temperatures[stack[-1]]:
                prev_index = stack.pop()
                answer[prev_index] = i - prev_index
            stack.append(i)

        return answer


# ==================== 测试代码 ====================

def test():
    solution = Solution()

    # 测试用例 1
    print("=" * 50)
    print("测试用例 1:")
    temps1 = [73, 74, 75, 71, 69, 72, 76, 73]
    print(f"温度: {temps1}")
    result1 = solution.dailyTemperatures(temps1)
    print(f"结果: {result1}")
    assert result1 == [1, 1, 4, 2, 1, 1, 0, 0], "测试用例 1 失败"
    print("✓ 通过")

    # 测试用例 2
    print("\n" + "=" * 50)
    print("测试用例 2:")
    temps2 = [30, 40, 50, 60]
    print(f"温度: {temps2}")
    result2 = solution.dailyTemperatures(temps2)
    print(f"结果: {result2}")
    assert result2 == [1, 1, 1, 0], "测试用例 2 失败"
    print("✓ 通过")

    # 测试用例 3
    print("\n" + "=" * 50)
    print("测试用例 3:")
    temps3 = [30, 60, 90]
    print(f"温度: {temps3}")
    result3 = solution.dailyTemperatures(temps3)
    print(f"结果: {result3}")
    assert result3 == [1, 1, 0], "测试用例 3 失败"
    print("✓ 通过")

    # 测试用例 4: 递减温度
    print("\n" + "=" * 50)
    print("测试用例 4 (递减温度):")
    temps4 = [90, 80, 70, 60]
    print(f"温度: {temps4}")
    result4 = solution.dailyTemperatures(temps4)
    print(f"结果: {result4}")
    assert result4 == [0, 0, 0, 0], "测试用例 4 失败"
    print("✓ 通过")

    # 测试用例 5: 相同温度
    print("\n" + "=" * 50)
    print("测试用例 5 (相同温度):")
    temps5 = [50, 50, 50]
    print(f"温度: {temps5}")
    result5 = solution.dailyTemperatures(temps5)
    print(f"结果: {result5}")
    assert result5 == [0, 0, 0], "测试用例 5 失败"
    print("✓ 通过")

    print("\n" + "=" * 50)
    print("所有测试用例通过！")


if __name__ == "__main__":
    test()
