from typing import List

def unique_paths(m: int, n: int) -> int:
    """
    动态规划解法

    时间复杂度: O(m * n)
    空间复杂度: O(m * n)，可优化到 O(min(m, n))
    """
    # 创建 dp 表
    dp = [[0] * n for _ in range(m)]

    # 初始化第一行
    for j in range(n):
        dp[0][j] = 1

    # 初始化第一列
    for i in range(m):
        dp[i][0] = 1

    # 填表
    for i in range(1, m):
        for j in range(1, n):
            dp[i][j] = dp[i-1][j] + dp[i][j-1]

    return dp[m-1][n-1]

# 优化版本：使用一维数组
def unique_paths_optimized(m: int, n: int) -> int:
    """
    优化版本：使用一维数组

    时间复杂度: O(m * n)
    空间复杂度: O(n)
    """
    # dp[j] 表示到达第 i 行第 j 列的路径数
    dp = [1] * n  # 初始化为 1，第一行的所有位置都只能从左边到达

    for i in range(1, m):
        for j in range(1, n):
            dp[j] += dp[j-1]

    return dp[n-1]

# 组合数学解法
def unique_paths_combination(m: int, n: int) -> int:
    """
    组合数学解法

    时间复杂度: O(min(m, n))
    空间复杂度: O(1)
    """
    from math import comb

    # 从 m-1 + n-1 步中选 m-1 步向下
    return comb(m + n - 2, m - 1)

# 手动计算组合数（不使用 math.comb）
def unique_paths_combination_manual(m: int, n: int) -> int:
    """
    手动计算组合数

    时间复杂度: O(min(m, n))
    空间复杂度: O(1)
    """
    # 计算 C(a, b) = a! / (b! * (a-b)!)
    # 为避免大数计算，使用迭代方式
    a = m + n - 2
    b = min(m - 1, n - 1)

    result = 1
    for i in range(1, b + 1):
        result = result * (a - i + 1) // i

    return result

# 测试用例
if __name__ == "__main__":
    test_cases = [
        (3, 7, 28),
        (2, 3, 3),
        (3, 3, 6),
        (1, 1, 1),
        (1, 5, 1),
        (5, 1, 1),
    ]

    for m, n, expected in test_cases:
        result = unique_paths(m, n)
        result_opt = unique_paths_optimized(m, n)
        result_comb = unique_paths_combination(m, n)
        result_comb_manual = unique_paths_combination_manual(m, n)
        print(f"m={m}, n={n}:")
        print(f"  动态规划: {result} (预期: {expected})")
        print(f"  优化版本: {result_opt} (预期: {expected})")
        print(f"  组合数学: {result_comb} (预期: {expected})")
        print(f"  组合数学(手动): {result_comb_manual} (预期: {expected})")
        assert result == expected and result_opt == expected and result_comb == expected and result_comb_manual == expected, "测试失败!"
        print()
