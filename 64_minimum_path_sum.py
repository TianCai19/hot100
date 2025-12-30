from typing import List

def min_path_sum(grid: List[List[int]]) -> int:
    """
    动态规划解法

    时间复杂度: O(m * n)
    空间复杂度: O(m * n)，可优化到 O(min(m, n))
    """
    if not grid or not grid[0]:
        return 0

    m, n = len(grid), len(grid[0])

    # 创建 dp 表
    dp = [[0] * n for _ in range(m)]
    dp[0][0] = grid[0][0]

    # 初始化第一行
    for j in range(1, n):
        dp[0][j] = dp[0][j-1] + grid[0][j]

    # 初始化第一列
    for i in range(1, m):
        dp[i][0] = dp[i-1][0] + grid[i][0]

    # 填表
    for i in range(1, m):
        for j in range(1, n):
            dp[i][j] = grid[i][j] + min(dp[i-1][j], dp[i][j-1])

    return dp[m-1][n-1]

# 优化版本：原地修改 grid
def min_path_sum_optimized(grid: List[List[int]]) -> int:
    """
    优化版本：原地修改 grid 作为 dp 表

    时间复杂度: O(m * n)
    空间复杂度: O(1)
    """
    if not grid or not grid[0]:
        return 0

    m, n = len(grid), len(grid[0])

    # 初始化第一行
    for j in range(1, n):
        grid[0][j] += grid[0][j-1]

    # 初始化第一列
    for i in range(1, m):
        grid[i][0] += grid[i-1][0]

    # 填表
    for i in range(1, m):
        for j in range(1, n):
            grid[i][j] += min(grid[i-1][j], grid[i][j-1])

    return grid[m-1][n-1]

# 测试用例
if __name__ == "__main__":
    test_cases = [
        ([[1,3,1],[1,5,1],[4,2,1]], 7),
        ([[1,2,3],[4,5,6]], 12),
        ([[1]], 1),
        ([[1,2]], 3),
        ([[1],[2]], 3),
        ([[1,3,1,2],[4,5,1,3],[2,1,4,1]], 7),
    ]

    for i, (grid, expected) in enumerate(test_cases, 1):
        # 深拷贝 grid 用于两次测试
        import copy
        grid_copy1 = copy.deepcopy(grid)
        grid_copy2 = copy.deepcopy(grid)

        result1 = min_path_sum(grid_copy1)
        result2 = min_path_sum_optimized(grid_copy2)

        print(f"测试用例 {i}:")
        print(f"  输入: {grid}")
        print(f"  动态规划: {result1} (预期: {expected})")
        print(f"  优化版本: {result2} (预期: {expected})")

        assert result1 == expected and result2 == expected, "测试失败!"
        print()
