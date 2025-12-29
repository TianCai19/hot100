from typing import List


class Solution:
    def maximalSquare(self, matrix: List[List[str]]) -> int:
        """
        动态规划：时间 O(mn)，空间 O(mn)
        dp[i][j] 表示以 (i,j) 为右下角的最大正方形边长
        状态转移: dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
        """
        if not matrix or not matrix[0]:
            return 0

        rows, cols = len(matrix), len(matrix[0])
        # dp[i][j] 表示以 (i,j) 为右下角的最大正方形边长
        dp = [[0] * (cols + 1) for _ in range(rows + 1)]
        max_side = 0

        for i in range(1, rows + 1):
            for j in range(1, cols + 1):
                if matrix[i - 1][j - 1] == '1':
                    # 取三个方向的最小值 + 1
                    dp[i][j] = min(dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]) + 1
                    max_side = max(max_side, dp[i][j])

        return max_side * max_side


# ==================== 测试代码 ====================

def print_matrix(matrix):
    """打印矩阵"""
    for row in matrix:
        print(" ".join(row))
    print()


def test():
    solution = Solution()

    # 测试用例 1
    print("=" * 50)
    print("测试用例 1:")
    matrix1 = [
        ["1", "0", "1", "0", "0"],
        ["1", "0", "1", "1", "1"],
        ["1", "1", "1", "1", "1"],
        ["1", "0", "0", "1", "0"]
    ]
    print("矩阵:")
    print_matrix(matrix1)
    result1 = solution.maximalSquare(matrix1)
    print(f"结果: {result1}")
    assert result1 == 4, "测试用例 1 失败"
    print("✓ 通过")

    # 测试用例 2
    print("\n" + "=" * 50)
    print("测试用例 2:")
    matrix2 = [
        ["0", "1"],
        ["1", "0"]
    ]
    print("矩阵:")
    print_matrix(matrix2)
    result2 = solution.maximalSquare(matrix2)
    print(f"结果: {result2}")
    assert result2 == 1, "测试用例 2 失败"
    print("✓ 通过")

    # 测试用例 3
    print("\n" + "=" * 50)
    print("测试用例 3:")
    matrix3 = [["0"]]
    print("矩阵:")
    print_matrix(matrix3)
    result3 = solution.maximalSquare(matrix3)
    print(f"结果: {result3}")
    assert result3 == 0, "测试用例 3 失败"
    print("✓ 通过")

    # 测试用例 4: 全1矩阵
    print("\n" + "=" * 50)
    print("测试用例 4 (全1矩阵):")
    matrix4 = [
        ["1", "1"],
        ["1", "1"]
    ]
    print("矩阵:")
    print_matrix(matrix4)
    result4 = solution.maximalSquare(matrix4)
    print(f"结果: {result4}")
    assert result4 == 4, "测试用例 4 失败"
    print("✓ 通过")

    # 测试用例 5: 单行
    print("\n" + "=" * 50)
    print("测试用例 5 (单行):")
    matrix5 = [["1", "1", "1", "1"]]
    print("矩阵:")
    print_matrix(matrix5)
    result5 = solution.maximalSquare(matrix5)
    print(f"结果: {result5}")
    assert result5 == 1, "测试用例 5 失败"
    print("✓ 通过")

    print("\n" + "=" * 50)
    print("所有测试用例通过！")


if __name__ == "__main__":
    test()
