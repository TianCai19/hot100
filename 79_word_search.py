"""
79. 单词搜索

回溯算法解法
"""

from typing import List


def exist(board: List[List[str]], word: str) -> bool:
    """
    回溯算法解法

    时间复杂度: O(m * n * 4^k)
    空间复杂度: O(m * n)

    Args:
        board: 字符网格
        word: 目标单词

    Returns:
        网格中是否存在单词路径
    """
    m, n = len(board), len(board[0])

    def backtrack(row: int, col: int, index: int) -> bool:
        """
        从 (row, col) 开始搜索 word[index:]

        Args:
            row, col: 当前搜索位置
            index: 当前要匹配的字符在 word 中的索引

        Returns:
            bool: 是否找到剩余字符
        """
        # 所有字符都匹配成功
        if index == len(word):
            return True

        # 边界检查
        if row < 0 or row >= m or col < 0 or col >= n:
            return False

        # 字符匹配检查
        if board[row][col] != word[index]:
            return False

        # 标记当前单元格为已访问（使用特殊标记）
        temp = board[row][col]
        board[row][col] = '#'

        # 向四个方向搜索
        found = (
            backtrack(row - 1, col, index + 1) or  # 上
            backtrack(row + 1, col, index + 1) or  # 下
            backtrack(row, col - 1, index + 1) or  # 左
            backtrack(row, col + 1, index + 1)     # 右
        )

        # 回溯：恢复单元格状态
        board[row][col] = temp

        return found

    # 遍历每个单元格作为起点
    for i in range(m):
        for j in range(n):
            if backtrack(i, j, 0):
                return True

    return False


def exist_optimized(board: List[List[str]], word: str) -> bool:
    """
    优化的回溯算法（使用访问标记数组）

    时间复杂度: O(m * n * 4^k)
    空间复杂度: O(m * n)
    """
    m, n = len(board), len(board[0])
    visited = [[False] * n for _ in range(m)]

    def backtrack(row: int, col: int, index: int) -> bool:
        if index == len(word):
            return True

        if row < 0 or row >= m or col < 0 or col >= n:
            return False

        if visited[row][col] or board[row][col] != word[index]:
            return False

        # 标记当前单元格为已访问
        visited[row][col] = True

        # 向四个方向搜索
        found = (
            backtrack(row - 1, col, index + 1) or
            backtrack(row + 1, col, index + 1) or
            backtrack(row, col - 1, index + 1) or
            backtrack(row, col + 1, index + 1)
        )

        # 回溯：重置访问标记
        visited[row][col] = False

        return found

    for i in range(m):
        for j in range(n):
            if backtrack(i, j, 0):
                return True

    return False


# 测试用例
def test_exist():
    """测试单词搜索函数"""

    # 测试用例1
    board1 = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E']
    ]
    word1 = "ABCCED"
    result1 = exist([row[:] for row in board1], word1)  # 深拷贝避免修改
    print(f"测试1: {result1 == True} (预期: True, 实际: {result1})")

    # 测试用例2
    board2 = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E']
    ]
    word2 = "SEE"
    result2 = exist([row[:] for row in board2], word2)
    print(f"测试2: {result2 == True} (预期: True, 实际: {result2})")

    # 测试用例3
    board3 = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E']
    ]
    word3 = "ABCB"
    result3 = exist([row[:] for row in board3], word3)
    print(f"测试3: {result3 == False} (预期: False, 实际: {result3})")

    # 测试用例4
    board4 = [['a']]
    word4 = "a"
    result4 = exist([row[:] for row in board4], word4)
    print(f"测试4: {result4 == True} (预期: True, 实际: {result4})")

    # 测试用例5：长单词
    board5 = [
        ['A', 'A', 'A', 'A'],
        ['A', 'A', 'A', 'A'],
        ['A', 'A', 'A', 'A']
    ]
    word5 = "AAAAAAAAAAAA"
    result5 = exist([row[:] for row in board5], word5)
    print(f"测试5: {result5 == True} (预期: True, 实际: {result5})")

    # 测试用例6：验证优化版本
    board6 = [
        ['A', 'B', 'C', 'E'],
        ['S', 'F', 'C', 'S'],
        ['A', 'D', 'E', 'E']
    ]
    word6 = "ABCCED"
    result6 = exist_optimized([row[:] for row in board6], word6)
    print(f"测试6 (优化版本): {result6 == True} (预期: True, 实际: {result6})")


if __name__ == "__main__":
    test_exist()
    print("\n所有测试通过！")
