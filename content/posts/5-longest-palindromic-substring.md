---
title: "最长回文子串"
difficulty: "中等"
description: "给你一个字符串 s，找到 s 中最长的回文子串。如果有多个最长的回文子串长度相同，返回任意一个。"
---

# 5. 最长回文子串

<DifficultyBadge difficulty="中等" />

## 题目描述

给你一个字符串 `s`，找到 `s` 中最长的**回文子串**。如果有多个最长的回文子串长度相同，返回任意一个。

**示例 1：**

```
输入: s = "babad"
输出: "bab"
解释: "aba" 也是答案，但"bab"长度相同
```

**示例 2：**

```
输入: s = "cbbd"
输出: "bb"
```

**示例 3：**

```
输入: s = "ac"
输出: "a" 或 "c"
```

## 解题思路

### 解法一：中心扩展法（推荐）

回文串的特点是**中心对称**，所以我们可以从每个字符或每两个字符之间开始，向两边扩展：

1. **奇数回文**：以单个字符为中心（"aba"）
2. **偶数回文**：以两个字符之间为中心（"aa"）
3. 对每个中心进行扩展，记录最长的回文

**时间复杂度：** O(n²)
**空间复杂度：** O(1)

### 解法二：动态规划

如果字符串长度为 `n`，创建一个 `n×n` 的 DP 表：

- `dp[i][j] = true` 表示 `s[i:j+1]` 是回文串
- 状态转移：`dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i+1][j-1])`

**时间复杂度：** O(n²)
**空间复杂度：** O(n²)

## 可视化示例

{<svg width="700" height="300" xmlns="http://www.w3.org/2000/svg">
  {/* 字符串 */}
  <text x="20" y="30" fontFamily="Arial" fontSize="14" fill="#fff">字符串: b a b a d</text>
  <text x="20" y="50" fontFamily="Arial" fontSize="14" fill="#fff">索引:   0 1 2 3 4</text>

  {/* 中心1 */}
  <text x="20" y="90" fontFamily="Arial" fontSize="12" fill="#3b82f6">中心1 (索引1): 'a'</text>
  <rect x="20" y="100" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="35" y="120" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">a</text>
  <path d="M 50 115 L 80 115" stroke="#3b82f6" strokeWidth="2" markerEnd="url(#arrowhead)"/>
  <rect x="80" y="100" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="95" y="120" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">b</text>
  <rect x="110" y="100" width="30" height="30" fill="#3b82f6" stroke="#fff" strokeWidth="1"/>
  <text x="125" y="120" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">a</text>
  <text x="20" y="145" fontFamily="Arial" fontSize="10" fill="#ccc">扩展: "bab", 长度=3</text>

  {/* 中心2 */}
  <text x="20" y="180" fontFamily="Arial" fontSize="12" fill="#10b981">中心2 (索引2): 'b'</text>
  <rect x="20" y="190" width="30" height="30" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="35" y="210" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">b</text>
  <rect x="50" y="190" width="30" height="30" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="65" y="210" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">a</text>
  <rect x="80" y="190" width="30" height="30" fill="#10b981" stroke="#fff" strokeWidth="1"/>
  <text x="95" y="210" fontFamily="Arial" fontSize="12" textAnchor="middle" fill="white">b</text>
  <text x="20" y="235" fontFamily="Arial" fontSize="10" fill="#ccc">扩展: "aba", 长度=3</text>

  {/* 结果 */}
  <text x="400" y="120" fontFamily="Arial" fontSize="16" fill="#fff">最长回文子串:</text>
  <text x="400" y="150" fontFamily="Arial" fontSize="20" fill="#f59e0b">"bab" 或 "aba"</text>
  <text x="400" y="180" fontFamily="Arial" fontSize="14" fill="#ccc">长度: 3</text>

  <defs>
    <marker id="arrowhead" markerWidth="10" markerHeight="7" refX="9" refY="3.5" orient="auto">
      <polygon points="0 0, 10 3.5, 0 7" fill="#fff"/>
    </marker>
  </defs>
</svg>}

## 代码实现

### Python 实现

```python
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
```

### C++ 实现

```cpp
#include <iostream>
#include <string>
using namespace std;

string longestPalindrome(string s) {
    /**
     * 解法一：中心扩展法
     * 时间复杂度：O(n²)
     * 空间复杂度：O(1)
     */
    if (s.length() < 2) return s;

    int start = 0;
    int max_len = 1;

    // 辅助函数：扩展回文
    auto expand = [&](int left, int right) -> pair<int, int> {
        // 当左右指针都在范围内且字符相等时，继续扩展
        while (left >= 0 && right < s.length() && s[left] == s[right]) {
            left--;
            right++;
        }
        // 返回扩展后的回文长度和起始位置
        return {right - left - 1, left + 1};
    };

    for (int i = 0; i < s.length(); i++) {
        // 奇数回文：以 s[i] 为中心
        auto [len1, left1] = expand(i, i);
        // 偶数回文：以 s[i] 和 s[i+1] 之间为中心
        auto [len2, left2] = expand(i, i + 1);

        // 取更长的回文
        if (len1 > max_len) {
            max_len = len1;
            start = left1;
        }
        if (len2 > max_len) {
            max_len = len2;
            start = left2;
        }
    }

    return s.substr(start, max_len);
}

// 测试用例
int main() {
    // 示例1
    string s1 = "babad";
    string result1 = longestPalindrome(s1);
    cout << "示例1: s = '" << s1 << "'" << endl;
    cout << "输出: '" << result1 << "' (长度: " << result1.length() << ")" << endl;

    // 示例2
    string s2 = "cbbd";
    string result2 = longestPalindrome(s2);
    cout << "\n示例2: s = '" << s2 << "'" << endl;
    cout << "输出: '" << result2 << "' (长度: " << result2.length() << ")" << endl;

    // 示例3
    string s3 = "ac";
    string result3 = longestPalindrome(s3);
    cout << "\n示例3: s = '" << s3 << "'" << endl;
    cout << "输出: '" << result3 << "' (长度: " << result3.length() << ")" << endl;

    // 额外测试
    string s4 = "aaaa";
    string result4 = longestPalindrome(s4);
    cout << "\n额外测试: s = '" << s4 << "'" << endl;
    cout << "输出: '" << result4 << "' (长度: " << result4.length() << ")" << endl;

    string s5 = "racecar";
    string result5 = longestPalindrome(s5);
    cout << "\n额外测试: s = '" << s5 << "'" << endl;
    cout << "输出: '" << result5 << "' (长度: " << result5.length() << ")" << endl;

    return 0;
}
```

## 复杂度分析

| 解法 | 时间复杂度 | 空间复杂度 | 特点 |
|------|-----------|-----------|------|
| 暴力枚举 | O(n³) | O(1) | 思路简单，性能极差 |
| 中心扩展 | O(n²) | O(1) | **推荐**，高效且易理解 |
| 动态规划 | O(n²) | O(n²) | 经典 DP，但空间大 |
| Manacher | O(n) | O(n) | 最优解，但实现复杂 |

## 关键总结

- **中心扩展**是最实用的解法，面试常考
- **回文问题**本质是找中心点并向两边扩展
- 类似的题目：回文链表、回文子串等
- Manacher 算法可以在 O(n) 时间内解决，但面试中较少要求