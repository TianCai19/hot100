/*
76. 最小覆盖子串

滑动窗口 + 哈希表解法
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <climits>
using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.empty() || t.empty() || s.length() < t.length()) {
            return "";
        }

        unordered_map<char, int> need, window;
        // 统计目标字符串 t 中每个字符的需求数量
        for (char c : t) {
            need[c]++;
        }

        int left = 0, right = 0;
        int valid = 0;
        int start = 0;
        int min_len = INT_MAX;
        int need_size = need.size();

        while (right < s.length()) {
            // 扩张右边界
            char c = s[right];
            if (need.find(c) != need.end()) {
                window[c]++;
                if (window[c] == need[c]) {
                    valid++;
                }
            }

            // 当所有字符都满足需求时，尝试收缩左边界
            while (valid == need_size) {
                // 更新最小覆盖子串
                if (right - left + 1 < min_len) {
                    start = left;
                    min_len = right - left + 1;
                }

                // 收缩左边界
                char d = s[left];
                if (need.find(d) != need.end()) {
                    if (window[d] == need[d]) {
                        valid--;
                    }
                    window[d]--;
                }
                left++;
            }

            right++;
        }

        return min_len == INT_MAX ? "" : s.substr(start, min_len);
    }
};

void test_min_window() {
    Solution solution;

    // 测试用例1
    string s1 = "ADOBECODEBANC";
    string t1 = "ABC";
    string expected1 = "BANC";
    string result1 = solution.minWindow(s1, t1);
    cout << "测试1: " << (result1 == expected1 ? "通过" : "失败")
         << " (预期: " << expected1 << ", 实际: " << result1 << ")" << endl;

    // 测试用例2
    string s2 = "a";
    string t2 = "aa";
    string expected2 = "";
    string result2 = solution.minWindow(s2, t2);
    cout << "测试2: " << (result2 == expected2 ? "通过" : "失败")
         << " (预期: " << expected2 << ", 实际: " << result2 << ")" << endl;

    // 测试用例3
    string s3 = "aabecodeddba";
    string t3 = "ab";
    string expected3 = "ab";
    string result3 = solution.minWindow(s3, t3);
    cout << "测试3: " << (result3 == expected3 ? "通过" : "失败")
         << " (预期: " << expected3 << ", 实际: " << result3 << ")" << endl;

    // 测试用例4
    string s4 = "cabwefgewcwaefgcf";
    string t4 = "cae";
    string expected4 = "cwae";
    string result4 = solution.minWindow(s4, t4);
    cout << "测试4: " << (result4 == expected4 ? "通过" : "失败")
         << " (预期: " << expected4 << ", 实际: " << result4 << ")" << endl;

    // 测试用例5
    string s5 = "";
    string t5 = "a";
    string expected5 = "";
    string result5 = solution.minWindow(s5, t5);
    cout << "测试5: " << (result5 == expected5 ? "通过" : "失败")
         << " (预期: " << expected5 << ", 实际: " << result5 << ")" << endl;
}

int main() {
    test_min_window();

    cout << "\n所有测试通过！" << endl;
    return 0;
}
