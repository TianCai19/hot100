def length_of_longest_substring(s: str) -> int:
    """
    解法：滑动窗口 + 哈希表
    时间复杂度：O(n)
    空间复杂度：O(min(m, n))，其中 m 是字符集大小
    """
    # 记录每个字符最后出现的位置
    char_map = {}
    left = 0
    max_length = 0

    for right in range(len(s)):
        # 如果字符 s[right] 在窗口中已存在，移动左指针
        if s[right] in char_map and char_map[s[right]] >= left:
            # 左指针移动到重复字符的下一个位置
            left = char_map[s[right]] + 1

        # 更新字符最后出现的位置
        char_map[s[right]] = right

        # 更新最大长度
        max_length = max(max_length, right - left + 1)

    return max_length

# 测试用例
if __name__ == "__main__":
    # 示例1
    s1 = "abcabcbb"
    print(f"示例1: s = '{s1}'")
    print(f"输出: {length_of_longest_substring(s1)}")  # 3

    # 示例2
    s2 = "bbbbb"
    print(f"\n示例2: s = '{s2}'")
    print(f"输出: {length_of_longest_substring(s2)}")  # 1

    # 示例3
    s3 = "pwwkew"
    print(f"\n示例3: s = '{s3}'")
    print(f"输出: {length_of_longest_substring(s3)}")  # 3

    # 额外测试
    s4 = "dvdf"
    print(f"\n额外测试: s = '{s4}'")
    print(f"输出: {length_of_longest_substring(s4)}")  # 3

    s5 = "abba"
    print(f"\n额外测试: s = '{s5}'")
    print(f"输出: {length_of_longest_substring(s5)}")  # 2
