---
title: "无重复字符的最长子串"
difficulty: "中等"
description: "给定一个字符串 s，请你找出其中不含有重复字符的最长子串的长度。"
---

# 3. 无重复字符的最长子串

<DifficultyBadge difficulty="中等" />

## 题目描述

给定一个字符串 `s`，请你找出其中不含有重复字符的**最长子串**的长度。

**示例 1：**

```
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

**示例 2：**

```
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```

**示例 3：**

```
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
```

请注意，答案必须是**子串**的长度，"pwke" 是一个子序列，不是子串。

## 解题思路

这是**滑动窗口**的经典题目！

### 解法：滑动窗口 + 哈希表

使用双指针维护一个窗口，保证窗口内没有重复字符：

1. **右指针**不断向右扩展，尝试包含更多字符
2. **左指针**在遇到重复字符时向右移动，收缩窗口
3. 使用**哈希表**记录每个字符最后出现的位置
4. 每次更新窗口长度，取最大值

**时间复杂度：** O(n)，每个字符最多被访问两次
**空间复杂度：** O(min(m, n))，其中 m 是字符集大小

## 可视化示例

{<svg width="700" height="250" xmlns="http://www.w3.org/2000/svg">
  {/* 字符串 */}
  <text x="20" y="30" fontFamily="Arial" fontSize="14" fill="#fff">字符串: p w w k e w</text>
  <text x="20" y="50" fontFamily="Arial" fontSize="14" fill="#fff">索引:   0 1 2 3 4 5</text>

  {/* 步骤1 */}
  <text x="20" y="90" fontFamily="Arial" fontSize="12" fill="#3b82f6">步骤1: 左=0, 右=0, 窗口="p", 最大长度=1</text>
  <rect x="20" y="100" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="35" y="120" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">p</text>

  {/* 步骤2 */}
  <text x="20" y="150" fontFamily="Arial" fontSize="12" fill="#3b82f6">步骤2: 左=0, 右=1, 窗口="pw", 最大长度=2</text>
  <rect x="20" y="160" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="35" y="180" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">p</text>
  <rect x="50" y="160" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="65" y="180" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">w</text>

  {/* 步骤3 */}
  <text x="200" y="90" fontFamily="Arial" fontSize="12" fill="#10b981">步骤3: 发现重复 'w', 左指针移动到 1, 窗口="w"</text>
  <rect x="200" y="100" width="30" height="30" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="215" y="120" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">w</text>

  {/* 步骤4 */}
  <text x="200" y="150" fontFamily="Arial" fontSize="12" fill="#3b82f6">步骤4: 右=2, 左=1, 窗口="ww"</text>
  <rect x="200" y="160" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="215" y="180" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">w</text>
  <rect x="230" y="160" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="245" y="180" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">w</text>

  {/* 步骤5 */}
  <text x="200" y="210" fontFamily="Arial" fontSize="12" fill="#10b981">步骤5: 发现重复 'w', 左移动到 2, 窗口="w"</text>
  <rect x="200" y="220" width="30" height="30" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="215" y="240" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">w</text>

  {/* 最终结果 */}
  <text x="450" y="120" fontFamily="Arial" fontSize="14" fill="#fff">最终结果: "wke"</text>
  <text x="450" y="145" fontFamily="Arial" fontSize="14" fill="#fff">最大长度: 3</text>
</svg>}

## 代码实现

### Python 实现

```python
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
```

### C++ 实现

```cpp
#include <iostream>
#include <unordered_map>
#include <string>
using namespace std;

int lengthOfLongestSubstring(string s) {
    /**
     * 解法：滑动窗口 + 哈希表
     * 时间复杂度：O(n)
     * 空间复杂度：O(min(m, n))，其中 m 是字符集大小
     */
    // 记录每个字符最后出现的位置
    unordered_map<char, int> char_map;
    int left = 0;
    int max_length = 0;

    for (int right = 0; right < s.length(); right++) {
        // 如果字符 s[right] 在窗口中已存在，移动左指针
        if (char_map.find(s[right]) != char_map.end() && char_map[s[right]] >= left) {
            // 左指针移动到重复字符的下一个位置
            left = char_map[s[right]] + 1;
        }

        // 更新字符最后出现的位置
        char_map[s[right]] = right;

        // 更新最大长度
        max_length = max(max_length, right - left + 1);
    }

    return max_length;
}

// 测试用例
int main() {
    // 示例1
    string s1 = "abcabcbb";
    cout << "示例1: s = '" << s1 << "'" << endl;
    cout << "输出: " << lengthOfLongestSubstring(s1) << endl;  // 3

    // 示例2
    string s2 = "bbbbb";
    cout << "\n示例2: s = '" << s2 << "'" << endl;
    cout << "输出: " << lengthOfLongestSubstring(s2) << endl;  // 1

    // 示例3
    string s3 = "pwwkew";
    cout << "\n示例3: s = '" << s3 << "'" << endl;
    cout << "输出: " << lengthOfLongestSubstring(s3) << endl;  // 3

    // 额外测试
    string s4 = "dvdf";
    cout << "\n额外测试: s = '" << s4 << "'" << endl;
    cout << "输出: " << lengthOfLongestSubstring(s4) << endl;  // 3

    string s5 = "abba";
    cout << "\n额外测试: s = '" << s5 << "'" << endl;
    cout << "输出: " << lengthOfLongestSubstring(s5) << endl;  // 2

    return 0;
}
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 暴力枚举 | O(n³) | O(1) | 思路简单，性能极差 |
| 滑动窗口 | O(n) | O(min(m, n)) | **推荐**，高效实用 |

## 关键总结

- **滑动窗口**是字符串处理的强大技巧
- **双指针**可以避免不必要的计算
- 这是**哈希表应用**的经典案例
- 类似题目：最小覆盖子串、找到字符串中所有字母异位词等