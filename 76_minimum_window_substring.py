"""
76. 最小覆盖子串

滑动窗口 + 哈希表解法
"""

from typing import Dict
from collections import Counter, defaultdict


def min_window(s: str, t: str) -> str:
    """
    滑动窗口解法

    时间复杂度: O(|s| + |t|)
    空间复杂度: O(|Σ|)

    Args:
        s: 源字符串
        t: 目标字符串

    Returns:
        最小覆盖子串，如果不存在返回空字符串
    """
    if not s or not t or len(s) < len(t):
        return ""

    # 统计目标字符串 t 中每个字符的需求数量
    need: Dict[str, int] = Counter(t)
    # 字符集大小
    need_size = len(need)

    # 窗口中字符的实际数量
    window: Dict[str, int] = defaultdict(int)

    left = 0
    right = 0
    valid = 0
    # 记录最小覆盖子串的起始位置和长度
    start = 0
    min_len = float('inf')

    while right < len(s):
        # 扩张右边界
        c = s[right]
        if c in need:
            window[c] += 1
            if window[c] == need[c]:
                valid += 1

        # 当所有字符都满足需求时，尝试收缩左边界
        while valid == need_size:
            # 更新最小覆盖子串
            if right - left + 1 < min_len:
                start = left
                min_len = right - left + 1

            # 收缩左边界
            d = s[left]
            if d in need:
                if window[d] == need[d]:
                    valid -= 1
                window[d] -= 1
            left += 1

        right += 1

    return s[start:start + min_len] if min_len != float('inf') else ""


# 测试用例
def test_min_window():
    """测试最小覆盖子串函数"""

    # 测试用例1
    s1 = "ADOBECODEBANC"
    t1 = "ABC"
    expected1 = "BANC"
    result1 = min_window(s1, t1)
    print(f"测试1: {result1 == expected1} (预期: {expected1}, 实际: {result1})")

    # 测试用例2
    s2 = "a"
    t2 = "aa"
    expected2 = ""
    result2 = min_window(s2, t2)
    print(f"测试2: {result2 == expected2} (预期: {expected2}, 实际: {result2})")

    # 测试用例3
    s3 = "aabecodeddba"
    t3 = "ab"
    expected3 = "ab"
    result3 = min_window(s3, t3)
    print(f"测试3: {result3 == expected3} (预期: {expected3}, 实际: {result3})")

    # 测试用例4
    s4 = "cabwefgewcwaefgcf"
    t4 = "cae"
    expected4 = "cwae"
    result4 = min_window(s4, t4)
    print(f"测试4: {result4 == expected4} (预期: {expected4}, 实际: {result4})")

    # 测试用例5
    s5 = ""
    t5 = "a"
    expected5 = ""
    result5 = min_window(s5, t5)
    print(f"测试5: {result5 == expected5} (预期: {expected5}, 实际: {result5})")


if __name__ == "__main__":
    test_min_window()
    print("\n所有测试通过！" if all([
        min_window("ADOBECODEBANC", "ABC") == "BANC",
        min_window("a", "aa") == "",
        min_window("aabecodeddba", "ab") == "ab",
        min_window("cabwefgewcwaefgcf", "cae") == "cwae",
        min_window("", "a") == ""
    ]) else "有测试失败！")
