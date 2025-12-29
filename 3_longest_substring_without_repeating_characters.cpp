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
