"""
200. 岛屿数量
https://leetcode.com/problems/number-of-islands/
"""

from typing import List
from collections import deque


class Solution:
    """解法一：DFS（深度优先搜索）"""
    def numIslands_dfs(self, grid: List[List[str]]) -> int:
        """
        DFS 算法 - 深度优先搜索
        时间复杂度: O(M × N)，M = 行数，N = 列数
        空间复杂度: O(M × N)，最坏情况为全为陆地时的递归栈深度
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        # 遍历每个单元格
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    island_count += 1
                    # 从当前位置开始 DFS
                    self._dfs(grid, r, c)

        return island_count

    def _dfs(self, grid: List[List[str]], r: int, c: int):
        """
        深度优先搜索，访问并标记相邻的陆地
        """
        rows, cols = len(grid), len(grid[0])

        # 边界检查
        if r < 0 or r >= rows or c < 0 or c >= cols or grid[r][c] == '0':
            return

        # 标记当前陆地（视为已访问）
        grid[r][c] = '0'

        # 递归访问四个方向
        self._dfs(grid, r - 1, c)  # 上
        self._dfs(grid, r + 1, c)  # 下
        self._dfs(grid, r, c - 1)  # 左
        self._dfs(grid, r, c + 1)  # 右

    """解法二：BFS（广度优先搜索）"""
    def numIslands_bfs(self, grid: List[List[str]]) -> int:
        """
        BFS 算法 - 广度优先搜索
        时间复杂度: O(M × N)，M = 行数，N = 列数
        空间复杂度: O(min(M, N))，队列中最多存储一个岛屿的所有陆地
        """
        if not grid or not grid[0]:
            return 0

        rows, cols = len(grid), len(grid[0])
        island_count = 0

        # 四个方向：上、下、左、右
        directions = [(-1, 0), (1, 0), (0, -1), (0, 1)]

        # 遍历每个单元格
        for r in range(rows):
            for c in range(cols):
                if grid[r][c] == '1':
                    island_count += 1
                    # 从当前位置开始 BFS
                    queue = deque()
                    queue.append((r, c))
                    grid[r][c] = '0'  # 标记为已访问

                    # BFS 遍历
                    while queue:
                        cr, cc = queue.popleft()
                        # 检查四个方向
                        for dr, dc in directions:
                            nr, nc = cr + dr, cc + dc
                            # 边界检查和陆地检查
                            if (0 <= nr < rows and 0 <= nc < cols and
                                grid[nr][nc] == '1'):
                                queue.append((nr, nc))
                                grid[nr][nc] = '0'  # 标记为已访问

        return island_count


def copy_grid(grid: List[List[str]]) -> List[List[str]]:
    """复制网格"""
    return [row[:] for row in grid]


def test_solution():
    """测试所有解法"""
    print("=" * 60)
    print("测试岛屿数量")
    print("=" * 60)

    test_cases = [
        {
            "grid": [
                ["1", "1", "1", "1", "0"],
                ["1", "1", "0", "1", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "0", "0", "0"]
            ],
            "expected": 1,
            "description": "示例1：单个岛屿"
        },
        {
            "grid": [
                ["1", "1", "0", "0", "0"],
                ["1", "1", "0", "0", "0"],
                ["0", "0", "1", "0", "0"],
                ["0", "0", "0", "1", "1"]
            ],
            "expected": 3,
            "description": "示例2：三个岛屿"
        },
        {
            "grid": [],
            "expected": 0,
            "description": "空网格"
        },
        {
            "grid": [["0"]],
            "expected": 0,
            "description": "单个水格"
        },
        {
            "grid": [["1"]],
            "expected": 1,
            "description": "单个陆地"
        },
        {
            "grid": [
                ["1", "0"],
                ["0", "1"]
            ],
            "expected": 2,
            "description": "对角线岛屿"
        },
        {
            "grid": [
                ["1", "1"],
                ["1", "1"]
            ],
            "expected": 1,
            "description": "2x2 完整岛屿"
        },
        {
            "grid": [
                ["1", "1", "1"],
                ["1", "0", "1"],
                ["1", "1", "1"]
            ],
            "expected": 1,
            "description": "环形岛屿"
        },
        {
            "grid": [
                ["1", "1", "0", "1", "1"],
                ["0", "1", "0", "0", "0"],
                ["0", "0", "0", "1", "1"],
                ["1", "0", "0", "0", "0"]
            ],
            "expected": 4,
            "description": "复杂形状岛屿"
        },
        {
            "grid": [
                ["1", "0", "1", "0", "1"],
                ["0", "1", "0", "1", "0"],
                ["1", "0", "1", "0", "1"],
                ["0", "1", "0", "1", "0"]
            ],
            "expected": 10,
            "description": "棋盘格岛屿"
        }
    ]

    methods = [
        ("DFS", Solution().numIslands_dfs),
        ("BFS", Solution().numIslands_bfs)
    ]

    for method_name, method in methods:
        print(f"\n{'=' * 60}")
        print(f"测试方法: {method_name}")
        print(f"{'=' * 60}")

        passed = 0
        failed = 0

        for i, test_case in enumerate(test_cases, 1):
            grid = copy_grid(test_case["grid"])
            expected = test_case["expected"]
            description = test_case["description"]

            try:
                result = method(grid)

                if result == expected:
                    print(f"✓ 测试 {i} 通过: {description}")
                    print(f"  网格: {test_case['grid']}")
                    print(f"  岛屿数: {result}")
                    passed += 1
                else:
                    print(f"✗ 测试 {i} 失败: {description}")
                    print(f"  网格: {test_case['grid']}")
                    print(f"  期望: {expected}, 实际: {result}")
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

    # 生成大型测试网格
    sizes = [
        (10, 10),
        (50, 50),
        (100, 100),
        (200, 200)
    ]

    for rows, cols in sizes:
        print(f"\n测试规模: {rows} × {cols}")

        # 生成随机网格
        import random
        random.seed(42)
        grid = []
        for _ in range(rows):
            row = []
            for _ in range(cols):
                row.append('1' if random.random() > 0.5 else '0')
            grid.append(row)

        for name, method in [("DFS", Solution().numIslands_dfs),
                             ("BFS", Solution().numIslands_bfs)]:
            # 复制网格
            test_grid = copy_grid(grid)

            start_time = time.time()
            result = method(test_grid)
            elapsed_time = time.time() - start_time

            print(f"  {name}: {elapsed_time:.4f} 秒 (岛屿数: {result})")


def test_large_grid():
    """测试大型网格（内存和性能）"""
    print("\n" + "=" * 60)
    print("大型网格测试")
    print("=" * 60)

    import time

    # 创建 500x500 的网格
    size = 500
    print(f"\n创建 {size}×{size} 网格...")
    grid = [['0'] * size for _ in range(size)]

    # 在中心创建一个岛屿
    center = size // 2
    for i in range(center - 10, center + 10):
        for j in range(center - 10, center + 10):
            grid[i][j] = '1'

    # 创建多个分散的岛屿
    positions = [(50, 50), (50, 450), (450, 50), (450, 450)]
    for pr, pc in positions:
        for i in range(pr - 5, pr + 5):
            for j in range(pc - 5, pc + 5):
                if 0 <= i < size and 0 <= j < size:
                    grid[i][j] = '1'

    for name, method in [("DFS", Solution().numIslands_dfs),
                         ("BFS", Solution().numIslands_bfs)]:
        test_grid = copy_grid(grid)
        start_time = time.time()
        result = method(test_grid)
        elapsed_time = time.time() - start_time

        print(f"{name}: {elapsed_time:.4f} 秒 (岛屿数: {result})")


if __name__ == "__main__":
    test_solution()
    test_performance()
    test_large_grid()
