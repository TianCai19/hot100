#include <iostream>
#include <string>
#include <utility>
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
