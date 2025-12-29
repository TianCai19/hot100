def longest_palindrome(s: str) -> str:
    """
    解法一：中心扩展法
    时间复杂度：O(n²)
    空间复杂度：O(1)
    """
    if len(s) < 2:
        return s

    start = 0
    max_len = 1

    # 辅助函数：扩展回文
    def expand(left: int, right: int) -> tuple:
        # 当左右指针都在范围内且字符相等时，继续扩展
        while left >= 0 and right < len(s) and s[left] == s[right]:
            left -= 1
            right += 1
        # 返回扩展后的回文长度（注意：最后一次扩展后 left 和 right 越界了）
        return right - left - 1, left + 1

    for i in range(len(s)):
        # 奇数回文：以 s[i] 为中心
        len1, left1 = expand(i, i)
        # 偶数回文：以 s[i] 和 s[i+1] 之间为中心
        len2, left2 = expand(i, i + 1)

        # 取更长的回文
        if len1 > max_len:
            max_len = len1
            start = left1
        if len2 > max_len:
            max_len = len2
            start = left2

    return s[start:start + max_len]

# 测试用例
if __name__ == "__main__":
    # 示例1
    s1 = "babad"
    result1 = longest_palindrome(s1)
    print(f"示例1: s = '{s1}'")
    print(f"输出: '{result1}' (长度: {len(result1)})")

    # 示例2
    s2 = "cbbd"
    result2 = longest_palindrome(s2)
    print(f"\n示例2: s = '{s2}'")
    print(f"输出: '{result2}' (长度: {len(result2)})")

    # 示例3
    s3 = "ac"
    result3 = longest_palindrome(s3)
    print(f"\n示例3: s = '{s3}'")
    print(f"输出: '{result3}' (长度: {len(result3)})")

    # 额外测试
    s4 = "aaaa"
    result4 = longest_palindrome(s4)
    print(f"\n额外测试: s = '{s4}'")
    print(f"输出: '{result4}' (长度: {len(result4)})")

    s5 = "racecar"
    result5 = longest_palindrome(s5)
    print(f"\n额外测试: s = '{s5}'")
    print(f"输出: '{result5}' (长度: {len(result5)})")
